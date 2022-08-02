#!/usr/bin/env python

from __future__ import print_function, absolute_import
from pkg_resources import parse_version

import click
import time
import os

import uhal

from dtpcontrols import core as controls

from dtpcontrols.toolbox import dumpSubRegs, printRegTable, printDictTable, readStreamProcessorStatus
import optionValidators

#INITIALSE---------------------------------------------------------------------

class HFObject(object):
    def __init__(self):
        super(HFObject, self).__init__()

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def get_devices(ctx, args, incomplete):
    connection_file = controls.find_connection_file()
    print ("Connection file is : " + connection_file)
    devs = uhal.ConnectionManager(connection_file).getDevices()
    #devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

#extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}
extra_autocompl = {'shell_complete': get_devices} if parse_version(click.__version__) >= parse_version('8.1') else {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}

@click.group(context_settings=CONTEXT_SETTINGS, invoke_without_command=True)
@click.option('-e', '--exception-stack', 'aExcStack', is_flag=True, help="Display full exception stack")
@click.option('-c', '--connection', type=click.Path(exists=True), default=controls.find_connection_file()[6:])
@click.argument('device', **extra_autocompl)
@click.pass_context
@click.version_option(version='ultimate')
def cli(ctx, aExcStack, connection, device):
    obj = ctx.obj
    obj.mPrintExceptionStack = aExcStack
    hw = uhal.ConnectionManager("file://"+connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)
    obj.mHW = hw
    obj.podNode = hw.getNode()
    # Extract info from InfoNode
    infoNode = obj.podNode.get_info_node()
    config_info = infoNode.get_firmware_config_info()
    #id_info = infoNode.get_firmware_id_info()

    printDictTable(config_info)
    #printRegTable(id_info)
    
    #obj.mIdInfo = id_info
    obj.mConfigInfo = config_info

# -----------------------------------------------------------------------------
@cli.command('init')
@click.pass_obj
def init(obj):
    obj.podNode.reset()
    print("\n RESET DONE!!")
    print("\n Initilisation complete.")

# Command group link------------------------------------------------------------
@cli.group('link', invoke_without_command=True)
@click.option('-i', '--ids', default='all', callback=optionValidators.validate_link_ids)
@click.pass_obj
def link(obj, ids):
    """
    Partition specific commands

    ID: Id of the selected partition
    """
    obj.mLinkIds = ids
    try:
        obj.mLinkNodes = [obj.podNode.get_link_processor_node(i) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))
dpr_mux_choices = {
    'reset': (0, 0),
    'playback': (0, 1),
    'sink': (1, 0),
    'passthrough': (1, 1)
}
# ------------------------------------------------------------------------------
@link.command('config')
@click.option('--dr-on/--dr-off', 'dr_on', help='Enable data-reception block', default=None)
@click.option('--dpr-mux', 'dpr_mux', type=click.Choice(list(dpr_mux_choices.keys()),), help='Configure DPR mux', default=None)
@click.option('--drop-empty/--keep-empty', 'drop_empty', help='Drop empty hit packets', default=None)
@click.pass_obj
def link_config(obj, dr_on, dpr_mux, drop_empty):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())

        if dpr_mux:
            dprNode = ln.get_data_router_node().get_dpr_node()
            print("Configuring DPR mux : ", dpr_mux)
            dprNode.set_mux_in(dpr_mux_choices[dpr_mux][0], True)
            dprNode.set_mux_out(dpr_mux_choices[dpr_mux][1], True)
        
        if dr_on is not None:
            print("Configuring data-reception : ", str(dr_on))
            drNode = ln.get_data_router_node().get_data_reception_node()
            drNode.getNode("csr.ctrl.en").write(dr_on)
            drNode.getClient().dispatch()

        if drop_empty is not None:
            strmArrayNode = ln.get_stream_proc_array_node()
            strmNode = strmArrayNode.get_stream_proc_node()

            for i in range(obj.mConfigInfo['n_port']):
                print("Setting drop empty to {} on stream {} ".format(drop_empty, i))
                strmArrayNode.stream_select(i)
                strmNode.getNode('csr.ctrl.drop_empty').write(drop_empty)
            ln.getClient().dispatch()

        print('<< Link Processor ', ln.getId())

# ------------------------------------------------------------------------------
@link.command('mask')
@click.option('-p', '--pipes', callback=optionValidators.validate_proc_ids, default='all')
@click.option('-c', '--chans', callback=optionValidators.validate_chan_ids, default='all')
@click.argument('action', type=click.Choice(['disable','enable']))
@click.pass_obj
def link_mask(obj, pipes, chans, action):

    en_dsbl = True
    if action == 'disable':
        en_dsbl = False

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayNode = ln.get_stream_proc_array_node()
        strmNode = strmArrayNode.get_stream_proc_node()

        print('Configuring channel masks in pipelines ', ', '.join((str(p) for p in pipes)))
        mask_w = 0x0
        for b in chans:
            mask_w |= (1 << b)

        for p in pipes:
            strmArrayNode.stream_select(p)
            strmNode.set_channel_mask_all(mask_w)
            #strmNode.set_mask_channel_00to31(mask_w & 0xffffffff, mask_en_dsbl=en_dsbl)
            #strmNode.set_mask_channel_32to63((mask_w >> 32) & 0xffffffff, mask_en_dsbl=en_dsbl)
            ln.getClient().dispatch()

        mask_r = []
        for p in pipes:
            strmArrayNode.stream_select(p)
            mask_r += [(strmNode.get_channel_mask_all(dispatch = True))]
            ln.getClient().dispatch()

        for p, (m_h, m_l) in zip(pipes, mask_r):
            print(p, 'Channel mask: 0x%016x' % ((m_h.value() << 32) | m_l.value()))

# ------------------------------------------------------------------------------
@link.command('hitfinder')
@click.option('-p', '--pipes', callback=optionValidators.validate_proc_ids, default='all')
@click.option('-t', '--threshold', type=click.IntRange(0, 0x7fff), default=None)
@click.pass_obj
def link_hitfinder(obj, pipes, threshold):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayNode = ln.get_stream_proc_array_node()
        strmNode = strmArrayNode.get_stream_proc_node()

        for p in pipes:
            strmArrayNode.stream_select(p)
            strmNode.set_threshold(threshold)
            print(p, 'Hit Threshold set to', threshold)
        ln.getClient().dispatch()

# ------------------------------------------------------------------------------
@link.command('watch')
@click.pass_obj
@click.option('-r/-R', '--show-dr/--hide-dr', 'dr', default=True)
@click.option('-b/-B', '--show-dpr/--hide-dpr', 'dpr', default=True)
@click.option('-s/-S', '--show-sp/--hide-sp', 'sp', default=True)
def link_watch(obj, dr, dpr, sp):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayNode = ln.get_stream_proc_array_node()        
        drNode = ln.get_data_router_node().get_data_reception_node()
        dprNode = ln.get_data_router_node().get_dpr_node()

        if dr:
            print('--- dr ---')
            regs = controls.get_child_registers(drNode)
            printDictTable(regs, False)

        if dpr:
            print('--- dpr.csr ---')
            regs = controls.get_child_registers(dprNode.getNode("csr"))
            printDictTable(regs, False)

        if sp:
            print(readStreamProcessorStatus(strmArrayNode, obj.mConfigInfo['n_port']))

        # for p in pipes:
            # strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)


# -----------------------------------------------------------------------------
@cli.group('wtor', invoke_without_command=True, chain=True)
@click.pass_obj
@click.option('-i', '--ids', default='all', callback=optionValidators.validate_link_ids)
def wtor(obj, ids):
    obj.mWibtorIds = ids
    try:
        obj.mWibtorNodes = [obj.podNode.get_wibulator_node(i) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))
        

# -----------------------------------------------------------------------------
@wtor.command('config')
@click.argument('pattern', type=click.Path(exists=True))
@click.option('-t', '--trim-length', type=int, help='Trim pattern length', default=None)
@click.option('-i', '--pad-idles', is_flag=True, help='Pad pattern with idles', default=None)
@click.pass_obj
def wtor_config(obj, pattern, trim_length, pad_idles):
    p = controls.load_WIB_pattern_from_file(str(pattern))

    print('Pattern file:', pattern)
    print('      length:', len(p))

    if trim_length is not None:
        print('Trimming pattern to length', trim_length)
        p = p[:trim_length]
    if pad_idles:
        print('Padding pattern with idles')

        kch_idle = 0x0000000000BC

        wSize = obj.mWibtorNodes[0].get_size()

        if len(p) < wSize:
            p += [kch_idle]*(wSize-len(p))

    for wn in obj.mWibtorNodes:
        print('>> Wibulator', wn.getId())
        wn.write_pattern(p)


# -----------------------------------------------------------------------------
@wtor.command('fire')
@click.option('-l/-s', '--loop/--single', help='Configure loop mode', default=None)
@click.pass_obj
def wtor_fire(obj, loop):

    for wn in obj.mWibtorNodes:
        print('>> Wibulator', wn.getId())

        if not loop is None:
            wn.getNode('csr.ctrl.chain').write(loop)
            wn.getClient().dispatch()
            
        print('Fire!!!')
        wn.fire()


# -----------------------------------------------------------------------------
@cli.command('flowmaster')
@click.option('--src-sel', type=click.Choice(['gbt', 'wibtor']), help='Input source selection', default=None)
@click.option('--sink-sel', type=click.Choice(['hits']+['link'+str(i) for i in range(5)]), help='Sink input selection', default=None)
@click.pass_obj
def flowmaster(obj, src_sel, sink_sel):

    fmNode = obj.podNode.get_flowmaster_node()

    src_map = {'gbt': 0, 'wibtor': 1}
    sink_map = {'hits': (0, 0) }
    sink_map.update({ 'link'+str(d): (1, d) for d in range(obj.mConfigInfo['n_links']) })

    if src_sel:
        if src_sel == 'gbt':
            fmNode.set_source_gbt()
        elif src_sel == 'wibtor':
            fmNode.set_source_wtor()
        else:
            print("Invalid source")
    if sink_sel is not None:
        fmNode.sink_select(sink_sel)
        fmNode.getClient().dispatch()

# -----------------------------------------------------------------------------
@cli.command('cr-if')
@click.option('--on/--off', 'cr_on', help='Enable central-router interface block', default=None)
@click.option('--drop-empty/--keep-empty', 'drop_empty', help='Drop empty hit packets', default=None)
@click.pass_obj
def cr_if(obj, cr_on, drop_empty):

    crNode = obj.podNode.get_crif_node()
    if cr_on is not None:
        crNode.getNode('csr.ctrl.en').write(0x01)
        crNode.getNode('csr.ctrl.drop_empty').write(0x01)
        obj.mHW.dispatch()
        
    if drop_empty is not None:
        crNode.getNode('csr.ctrl.drop_empty').write(0x01)
        crNode.getClient.dispatch()

    print('--- cr_if.csr ---')
    regs = controls.get_child_registers(crNode.getNode("csr"))
    printRegTable(regs, False)

# -----------------------------------------------------------------------------
@cli.command('capture-sink')
@click.option('--path', type=click.Path(exists=False), help='Capture file path', default='b33_dump.txt')
@click.option('--timeout', type=float, help='Capture timeout', default=10)
@click.option('--drop-idles', is_flag=True, help='Drop idle words', default=None)
@click.pass_obj
def capture_sink(obj, path, timeout, drop_idles):

    osNode = obj.podNode.get_output_sink_node()

    print('Capturing axis32bsink data')
    osNode.getNode('csr.ctrl.en').write(0)
    osNode.getNode('csr.ctrl.clear').write(1)
    osNode.getNode('csr.ctrl.clear').write(0)
    if drop_idles:
        osNode.getNode('csr.pattern_kchar').write(0x1)
        osNode.getNode('csr.pattern_data').write(0xbc)
        osNode.getNode('csr.ctrl.filter').write(0x1)
    else:
        osNode.getNode('csr.pattern_kchar').write(0x0)
        osNode.getNode('csr.pattern_data').write(0x0)
        osNode.getNode('csr.ctrl.filter').write(0x0)
    osNode.getClient().dispatch()
    osNode.getNode('csr.ctrl.en').write(1)
    osNode.getClient().dispatch()

    sleep = 0.1
    max_iter = int(timeout//sleep)
    for i in range(max_iter):
        full = osNode.getNode('csr.stat.full').read()
        count = osNode.getNode('buf.count').read()
        osNode.getClient().dispatch() 
        if full.value():
            break
        print("FIFO counts",int(count))
        if i == (max_iter - 1):
            print('Capture Timeout!!!')
        time.sleep(sleep)

    osNode.getNode('csr.ctrl.en').write(0)
    count = osNode.getNode('buf.count').read()
    osNode.getClient().dispatch()

    print('Reading out %s frames' % count)
    d = osNode.getNode('buf.data').readBlock(2*int(count))
    osNode.getClient().dispatch()
    dd = controls.format_32b_to_36b(d)
    print("heRE")
    data = [((w >> 32) & 0x1, w & 0xffffffff) for w in dd]
    with open(path, 'w') as lFile:
        for i, (k, d) in enumerate(data):
            lFile.write('0x{1:08x} {0}\n'.format(k, d)) 
            print ('%04d' % i, k, '0x%08x' % d)
#MAIN-------------------------------------------------------------------------

if __name__ == '__main__':
    cli(obj=HFObject(), complete_var='_HFBUTLER_COMPLETE')
