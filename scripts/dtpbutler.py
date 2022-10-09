#!/usr/bin/env python

from __future__ import print_function, absolute_import
from pkg_resources import parse_version

import click
import time
import os

import uhal

from rich import print as rprint
from rich.table import Table
from dtpcontrols import core as controls

from dtpcontrols.toolbox import dumpSubRegs, printRegTable, printDictTable, readStreamProcessorStatus
from dtpcontrols.toolbox import dump_sub_regs, dict_to_table, print_dict_table, print_reg_table, read_stream_processor_status
import optionValidators

#INITIALSE---------------------------------------------------------------------

class DTPObject(object):
    def __init__(self):
        super(DTPObject, self).__init__()

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def get_devices(ctx, args, incomplete):
    connection_file = controls.find_connection_file()
    print ("Connection file is : " + connection_file)
    devs = uhal.ConnectionManager(connection_file).getDevices()
    #devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

def get_connection_manager(conn_file: str):
    from ctypes import cdll

    try:
        cdll.LoadLibrary("libuhallibs.so")
        manager = uhal.ConnectionManager(conn_file, ['ipbusflx-2.0'])
    except OSError:
        manager = uhal.ConnectionManager(conn_file)

    return manager

#extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}
extra_autocompl = {'shell_complete': get_devices} if parse_version(click.__version__) >= parse_version('8.1') else {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}

@click.group(context_settings=CONTEXT_SETTINGS, invoke_without_command=True)
@click.option('-v', '--version', 'show_version', is_flag=True, default=False, help="Print firmware version")
@click.option('-e', '--exception-stack', 'show_exc_stack', is_flag=True, help="Display full exception stack")
@click.option('-t', '--timeout', 'timeout', type=int, default=None, help="IPBus timeout")
@click.option('-l', '--loglevel', 'loglevel', type=click.Choice(['DEBUG', 'INFO', 'WARNING', 'ERROR']), default='WARNING', help="Ipbus logging verbosity")
@click.option('-c', '--connection', type=click.Path(exists=True), default=controls.find_connection_file()[6:])
@click.argument('device', **extra_autocompl)
@click.pass_context
@click.version_option(version='ultimate')
def cli(ctx, show_version, show_exc_stack, timeout, loglevel, connection, device):
    
    obj = ctx.obj
    
    obj.mPrintExceptionStack = show_exc_stack

    if loglevel:
        uhal.setLogLevelTo(getattr(uhal.LogLevel, loglevel))

    hw = get_connection_manager("file://"+connection).getDevice(str(device))

    if timeout:
        hw.setTimeoutPeriod(timeout)

    obj.mHW = hw
    obj.podctrl = controls.DTPPodController(hw)

    # Extract info from InfoNode
    infoNode = obj.podctrl.get_info_node()
    config_info = infoNode.get_firmware_config_info()
    id_info = infoNode.get_firmware_id_info()

    if show_version:
        print_dict_table(config_info)
        print_reg_table(id_info)
    
    obj.mIdInfo = id_info
    obj.mConfigInfo = config_info

# -----------------------------------------------------------------------------
@cli.command('init')
@click.pass_obj
def init(obj):
    obj.podctrl.reset()
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
        obj.mLinkNodes = [obj.podctrl.get_link_processor_node(i) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))

        
# ------------------------------------------------------------------------------
dpr_mux_choices = {
    'reset': (0, 0),
    'playback': (0, 1),
    'sink': (1, 0),
    'passthrough': (1, 1)
}
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
            drNode.enable(dr_on)

        if drop_empty is not None:
            strmArrayNode = ln.get_stream_proc_array_node()
            strmNode = strmArrayNode.get_stream_proc_node()

            for i in range(obj.mConfigInfo['n_port']):
                print("Setting drop empty to {} on stream {} ".format(drop_empty, i))
                strmArrayNode.stream_select(i)
                strmNode.drop_empty(True)

        print('<< Link Processor ', ln.getId())

# ------------------------------------------------------------------------------
@link.command('mask')
@click.option('-p', '--pipes', callback=optionValidators.validate_proc_ids, default='all')
@click.option('-c', '--chans', callback=optionValidators.validate_chan_ids, default='all')
@click.argument('action', type=click.Choice(['disable','enable']))
@click.pass_obj
def link_mask(obj, pipes, chans, action):


    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayNode = ln.get_stream_proc_array_node()
        strmNode = strmArrayNode.get_stream_proc_node()

        print('Configuring channel masks in pipelines ', ', '.join((str(p) for p in pipes)))
        mask_w = 0x0
        for b in chans:
            mask_w |= (1 << b)

        if action == 'disable':
            mask_w = ~mask_w            

        for p in pipes:
            strmArrayNode.stream_select(p)
            strmNode.set_channel_mask_all(mask_w)
            #mask for channel 00to31 is mask_w & 0xffffffff
            #mask for channel 32to63 is (mask_w >> 32) & 0xffffffff
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
@link.command('pedsub')
@click.option('-p', '--pipes', callback=optionValidators.validate_proc_ids, default='all')
@click.option('--cap-on/--cap-off', 'cp', default=False)
@click.pass_obj
def link_pedsub(obj, pipes, cp):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())

        strmArrayNode = ln.get_stream_proc_array_node()
        strmNode = strmArrayNode.get_stream_proc_node()

        # capture pedestals
        for p in pipes:
            strmArrayNode.stream_select(p)
            strmNode.capture_pedestal(cp)
            print(p, 'Capturing pedestal value', cp)
        ln.getClient().dispatch()

# ------------------------------------------------------------------------------
@link.command('watch')
@click.pass_obj
@click.option('-r/-R', '--show-dr/--hide-dr', 'dr', default=True)
@click.option('-b/-B', '--show-dpr/--hide-dpr', 'dpr', default=True)
@click.option('-s/-S', '--show-sp/--hide-sp', 'sp', default=True)
@click.option('-f/-F', '--show-flow/--hide-flow', 'fm', default=True)
def link_watch(obj, dr, dpr, sp, fm):

    for ln in obj.mLinkNodes:

        rprint()
        rprint(f"[bold]--- Link Processor {ln.getId()} ---[/bold]")
        rprint()

        strmArrayNode = ln.get_stream_proc_array_node()        
        drNode = ln.get_data_router_node().get_data_reception_node()
        dprNode = ln.get_data_router_node().get_dpr_node()
        fmNode = obj.podctrl.get_flowmaster_node()


        grid = Table.grid()
        for _ in range(dr+dpr):
            grid.add_column()

        row = []
        if dr:
            regs = dump_sub_regs(drNode)
            row += [dict_to_table(regs, title="dr")]

        if dpr:
            regs = dump_sub_regs(dprNode.getNode("csr"))
            row += [dict_to_table(regs, title='dpr.csr')]

        if fm: 
            regs = dump_sub_regs(fmNode)
            row += [dict_to_table(regs, title="fm")]

        grid.add_row(*row)
        rprint(grid)

        if sp:
            rprint(read_stream_processor_status(strmArrayNode, obj.mConfigInfo['n_port'], title="pipelines"))



# -----------------------------------------------------------------------------
@cli.group('wtor', invoke_without_command=True, chain=True)
@click.pass_obj
@click.option('-i', '--ids', default='all', callback=optionValidators.validate_link_ids)
def wtor(obj, ids):
    obj.mWibtorIds = ids
    try:
        obj.mWibtorNodes = [obj.podctrl.get_wibulator_node(i) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))
        

# -----------------------------------------------------------------------------
@wtor.command('config')
@click.argument('pattern', type=click.Path(exists=True))
@click.option('-t', '--trim-length', type=int, help='Trim pattern length', default=None)
@click.option('-i', '--pad-idles', is_flag=True, help='Pad pattern with idles', default=None)
@click.pass_obj
def wtor_config(obj, pattern, trim_length, pad_idles):
    p = controls.read_WIB_pattern_from_file(str(pattern))

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
@click.option('--out-mode', type=click.Choice(['drain', 'flow', 'gate']), help='Enable outflow', default=None)
@click.option('--sink-sel', type=click.Choice(['hits']+['link'+str(i) for i in range(5)]+['link-all']), help='Sink input selection', default=None)
@click.pass_obj
def flowmaster(obj, src_sel, out_mode, sink_sel):

    fmNode = obj.podctrl.get_flowmaster_node()

    src_map = {'gbt': 0, 'wibtor': 1}
    sink_map = {'hits': (0, 0) }
    sink_map.update({ 'link'+str(d): (1, d) for d in range(obj.mConfigInfo['n_links']) })
    if src_sel is not None:
        if src_sel == 'gbt':
            fmNode.set_source_gbt()
        elif src_sel == 'wibtor':
            fmNode.set_source_wtor()
        else:
            print("Invalid source")

    if out_mode == 'drain':
        fmNode.set_outflow(0)
    elif out_mode == 'flow':
        fmNode.set_outflow(1)
    elif out_mode == 'gate':
        fmNode.set_outflow(2)
    else:
            print("Invalid mode")

    if sink_sel is not None:
        if sink_sel == 'hits':
            fmNode.set_sink_hits()
            fmNode.getClient().dispatch()
        if (sink_sel[:4] == 'link'):
            if sink_sel[4:] == '-all':
                for l in range(obj.mConfigInfo['n_links']):
                    fmNode.set_sink_link(l)               
                    fmNode.getClient().dispatch()
                    print(l)
            if sink_sel[4] in [str(lnk) for lnk in range(obj.mConfigInfo['n_links'])]:
                fmNode.set_sink_link(int(sink_sel[-1]))
                fmNode.getClient().dispatch()

# -----------------------------------------------------------------------------
@cli.command('cr-if')
@click.option('--on/--off', 'cr_on', help='Enable central-router interface block', default=None)
@click.option('--drop-empty/--keep-empty', 'drop_empty', help='Drop empty hit packets', default=None)
@click.pass_obj
def cr_if(obj, cr_on, drop_empty):

    crNode = obj.podctrl.get_crif_node()
    if cr_on is not None:
        crNode.enable()
        crNode.set_drop_empty()
        
    if drop_empty is not None:
        crNode.set_drop_empty()

    row=[]
    cr_csr = crNode.getNode('csr')
    for sn in cr_csr.getNodes(r"[^\.]*"):
        regs = dump_sub_regs(cr_csr.getNode(sn))
        row.append(dict_to_table(regs, title=sn))

    g = Table.grid()
    for i in sn:
        g.add_column()
    g.add_row(*row)
    rprint(g)

# -----------------------------------------------------------------------------
@cli.command('capture-sink')
@click.option('--path', type=click.Path(exists=False), help='Capture file path', default='b33_dump.txt')
@click.option('--timeout', type=float, help='Capture timeout', default=10)
@click.option('--drop-idles', is_flag=True, help='Drop idle words', default=None)
@click.pass_obj
def capture_sink(obj, path, timeout, drop_idles):

    osNode = obj.podctrl.get_output_sink_node()

    print('Capturing axis32bsink data')
    osNode.disable()
    osNode.clear()
    if drop_idles:
        osNode.drop_idles()
    else:
        osNode.keep_idles()
    osNode.enable()

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

    data = [((w >> 32) & 0x1, w & 0xffffffff) for w in dd]
    with open(path, 'w') as lFile:
        for i, (k, d) in enumerate(data):
            lFile.write('0x{1:08x} {0}\n'.format(k, d)) 
            rprint ('%04d' % i, k, '0x%08x' % d)


@cli.command('ipy')
@click.pass_obj
def ipy(obj):

    import importlib
    spam_loader = importlib.util.find_spec('IPython')
    if spam_loader is None:
        rprint("[red]IPython not found[/red]")
        return

    import IPython
    IPython.embed(colors="neutral")

#MAIN-------------------------------------------------------------------------

if __name__ == '__main__':
    cli(obj=DTPObject(), complete_var='_DTPBUTLER_COMPLETE')
