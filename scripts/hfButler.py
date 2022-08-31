#!/usr/bin/env python

from pkg_resources import parse_version

import click
import time
import os

import dtpcontrols.toolbox as toolbox
import dtpcontrols.setup as setup
import dtpcontrols.dpr as dpr
import dtpcontrols.dr as dr
import dtpcontrols.cr as cr
import dtpcontrols.wibulator as wibulator

from dtpcontrols.toolbox import dumpSubRegs, printRegTable, printDictTable, readStreamProcessorStatus

class HFObject(object):
    """docstring for HFObject"""
    def __init__(self):
        super(HFObject, self).__init__()

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def get_devices(ctx, args, incomplete):
    devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

extra_autocompl = {'shell_complete': get_devices} if parse_version(click.__version__) >= parse_version('8.1') else {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}

@click.group(context_settings=CONTEXT_SETTINGS, invoke_without_command=True)
@click.option('-e', '--exception-stack', 'aExcStack', is_flag=True, help="Display full exception stack")
@click.option('-c', '--connection', type=click.Path(exists=True), default=setup.find_conn_file())
@click.argument('device', **extra_autocompl)
@click.pass_context
@click.version_option(version='ultimate')
def cli(ctx, aExcStack, connection, device):
    obj = ctx.obj

    obj.mPrintExceptionStack = aExcStack
    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)
    obj.mHW = hw
    obj.podNode = hw.getNode()

    info = obj.podNode.getNode('info')
    obj.mIdInfo = dumpSubRegs(info.getNode('id'))
    obj.mConfigInfo = dumpSubRegs(info.getNode('config'))

    printRegTable(obj.mIdInfo)
    printDictTable(obj.mConfigInfo)


# -----------------------------------------------------------------------------
@cli.command('init')
@click.pass_obj
def init(obj):
    ctrlNode = obj.podNode.getNode('ctrl')
    setup.softReset(ctrlNode)


# ------------------------------------------------------------------------------
@cli.group('link', invoke_without_command=True)
@click.option('-i', '--ids', default='all', callback=toolbox.validate_link_ids)
@click.pass_obj
def link(obj, ids):
    """
    Partition specific commands

    ID: Id of the selected partition
    """
    obj.mLinkIds = ids
    try:
        obj.mLinkNodes = [obj.podNode.getNode('linkproc{}'.format(i)) for i in ids]
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
            dprNode = ln.getNode('drtr.dpr')
            print("Configuring DPR mux :", dpr_mux)
            dpr.setup(dprNode, *dpr_mux_choices[dpr_mux])
        
        if dr_on is not None:
            print("Configuring data-reception :", str(dr_on))
            drNode = ln.getNode('drtr.dr')
            dr.enable(drNode, dr_on)

        if drop_empty is not None:
            strmArrayCsrNode = ln.getNode('stream_procs.csr')
            strmNode = ln.getNode('stream_procs.stream_proc')

            for i in range(obj.mConfigInfo['n_port']):
                print("Setting drop empty to {} on stream {}".format(drop_empty, i))
                ln.getNode('stream_procs.csr.ctrl.stream_sel').write(i)
                ln.getNode('stream_procs.stream_proc.csr.ctrl.drop_empty').write(drop_empty)
            ln.getClient().dispatch()

        print('<< Link Processor', ln.getId())
        print()


# ------------------------------------------------------------------------------
@link.command('mask')
@click.option('-p', '--pipes', callback=toolbox.validate_proc_ids, default='all')
@click.option('-c', '--chans', callback=toolbox.validate_chan_ids, default='all')
@click.argument('action', type=click.Choice(['disable','enable']))
@click.pass_obj
def link_mask(obj, pipes, chans, action):



    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayCsrNode = ln.getNode('stream_procs.csr')
        strmCsrNode = ln.getNode('stream_procs.stream_proc.csr')

        print('Configuring channel masks in pipelines', ', '.join((str(p) for p in pipes)))
        mask_w = 0x0
        for b in chans:
            mask_w |= (1 << b)

        if action == 'disable':
            mask_w = ~mask_w

        for p in pipes:
            strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)

            strmCsrNode.getNode('mask.ch-00-31').write(mask_w & 0xffffffff)
            strmCsrNode.getNode('mask.ch-32-63').write((mask_w >> 32) & 0xffffffff)
        ln.getClient().dispatch()

        mask_r = []
        for p in pipes:
            strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)
            mask_r += [(
                strmCsrNode.getNode('mask.ch-00-31').read(),
                strmCsrNode.getNode('mask.ch-32-63').read()
            )]
        ln.getClient().dispatch()

        for p, (m_h, m_l) in zip(pipes, mask_r):
            print(p, 'Channel mask: 0x%016x' % ((m_h.value() << 32) | m_l.value()))


# ------------------------------------------------------------------------------
@link.command('hitfinder')
@click.option('-p', '--pipes', callback=toolbox.validate_proc_ids, default='all')
@click.option('-t', '--threshold', type=click.IntRange(0, 0x7fff), default=None)
@click.pass_obj
def link_hitfinder(obj, pipes, threshold):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())
        strmArrayCsrNode = ln.getNode('stream_procs.csr')
        strmCsrNode = ln.getNode('stream_procs.stream_proc.csr')

        for p in pipes:
            strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)

            strmCsrNode.getNode('hitfinder.threshold').write(threshold)
            print(p, 'Hit Threshold set to', threshold)

        ln.getClient().dispatch()


# ------------------------------------------------------------------------------
@link.command('pedsub')
@click.option('-p', '--pipes', callback=toolbox.validate_proc_ids, default='all')
@click.option('--cap-on/--cap-off', 'cp', default=False)
@click.pass_obj
def link_pedsub(obj, pipes, cp):

    for ln in obj.mLinkNodes:
        print('>> Link Processor', ln.getId())

        strmArrayCsrNode = ln.getNode('stream_procs.csr')
        strmCsrNode = ln.getNode('stream_procs.stream_proc.csr')

        # capture pedestals
        for p in pipes:
            strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)
            strmCsrNode.getNode('pedsub.pedsub_adj').write(cp)

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
        strmArrayNode = ln.getNode('stream_procs')
        drNode = ln.getNode('drtr.dr')
        dprNode = ln.getNode('drtr.dpr')

        if dr:
            print('--- dr ---')
            regs = dumpSubRegs(drNode)
            printRegTable(regs, False)

        if dpr:
            print('--- dpr.csr ---')
            regs = dumpSubRegs(dprNode.getNode("csr"))
            printRegTable(regs, False)

        if sp:
            print(readStreamProcessorStatus(strmArrayNode, obj.mConfigInfo['n_port']))

        # for p in pipes:
            # strmArrayCsrNode.getNode('ctrl.stream_sel').write(p)


# -----------------------------------------------------------------------------
@cli.group('wtor', invoke_without_command=True, chain=True)
@click.pass_obj
@click.option('-i', '--ids', default='all', callback=toolbox.validate_link_ids)
def wtor(obj, ids):
    obj.mWibtorIds = ids
    try:
        obj.mWibtorNodes = [obj.podNode.getNode('wibtor{}'.format(i)) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))
        

# -----------------------------------------------------------------------------
@wtor.command('config')
@click.argument('pattern', type=click.Path(exists=True))
@click.option('-t', '--trim-length', type=int, help='Trim pattern length', default=None)
@click.option('-i', '--pad-idles', is_flag=True, help='Pad pattern with idles', default=None)
@click.pass_obj
def wtor_config(obj, pattern, trim_length, pad_idles):

    p = wibulator.loadWIBPatternFromFile(pattern)

    print('Pattern file:', pattern)
    print('      length:', len(p))

    if trim_length is not None:
        print('Trimming pattern to length', trim_length)
        p = p[:trim_length]
    if pad_idles:
        print('Padding pattern with idles')

        kch_idle = 0x0000000000BC

        wSize = wibulator.getSize(obj.mWibtorNodes[0])

        if len(p) < wSize:
            p += [kch_idle]*(wSize-len(p))

    for wn in obj.mWibtorNodes:
        print('>> Wibulator', wn.getId())
        wibulator.writePattern(wn, p)


# -----------------------------------------------------------------------------
@wtor.command('fire')
@click.option('-l/-s', '--loop/--single', help='Configure loop mode', default=None)
@click.pass_obj
def wtor_fire(obj, loop):

    for wn in obj.mWibtorNodes:
        print('>> Wibulator', wn.getId())

        if not loop is None:
            wibulator.loop(wn, loop)
            
        print('Fire!!!')
        wibulator.fire(wn)


# -----------------------------------------------------------------------------
@cli.command('flowmaster')
@click.option('--src-sel', type=click.Choice(['gbt', 'wibtor']), help='Input source selection', default=None)
@click.option('--out-sel', type=click.Choice(['sink', 'cr']), help='Input source selection', default=None)
@click.option('--sink-sel', type=click.Choice(['hits']+['link'+str(i) for i in range(5)]), help='Sink input selection', default=None)
@click.pass_obj
def flowmaster(obj, src_sel, sink_sel, out_sel):

    fmNode = obj.podNode.getNode('flowmaster')

    src_map = {'gbt': 0, 'wibtor': 1}
    outflow_map = {'sink': 0, 'cr': 1}
    sink_map = {'hits': (0, 0) }
    sink_map.update({ 'link'+str(d): (1, d) for d in range(5) })

    if src_sel:
        fmNode.getNode('csr.ctrl.gbt_src').write(src_map[src_sel])
    if out_sel:
        fmNode.getNode('csr.ctrl.out_sel').write(outflow_map[out_sel])
    if sink_sel is not None:
        fmNode.getNode('csr.ctrl.sink_src').write(sink_map[sink_sel][0])
        fmNode.getNode('csr.ctrl.sink_link').write(sink_map[sink_sel][1])
    fmNode.getClient().dispatch()


# -----------------------------------------------------------------------------
@cli.command('cr-if')
@click.option('--on/--off', 'cr_on', help='Enable central-router interface block', default=None)
@click.option('--drop-empty/--keep-empty', 'drop_empty', help='Drop empty hit packets', default=None)
@click.pass_obj
def cr_if(obj, cr_on, drop_empty):

    crNode = obj.podNode.getNode('cr_if')
    if cr_on is not None:
        cr.enable(crNode, cr_on)

    if drop_empty is not None:
        cr.drop(crNode, drop_empty)

    print('--- cr_if.csr ---')
    regs = dumpSubRegs(crNode.getNode("csr"))
    printRegTable(regs, False)

# -----------------------------------------------------------------------------
@cli.command('capture-sink')
@click.option('--path', type=click.Path(exists=False), help='Capture file path', default='b33_dump.txt')
@click.option('--timeout', type=float, help='Capture timeout', default=10)
@click.option('--drop-idles', is_flag=True, help='Drop idle words', default=None)
@click.pass_obj
def capture_sink(obj, path, timeout, drop_idles):

    osNode = obj.podNode.getNode('outsink')

    print('Capturing axis32bsink data')
    osNode.getNode('csr.ctrl.en').write(0)
    osNode.getNode('csr.ctrl.clear').write(1)
    osNode.getNode('csr.ctrl.clear').write(0)
    if drop_idles:
        osNode.getNode('csr.pattern_data').write(0xbc)
        osNode.getNode('csr.ctrl.filter').write(0x1)
    else:
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
    data = [((w >> 32) & 0x1, w & 0xffffffff) for w in wibulator.format32bto36b(d)]
    with open(path, 'w') as lFile:
        for i, (k, d) in enumerate(data):
            lFile.write('0x{1:08x} {0}\n'.format(k, d)) 
            print ('%04d' % i, k, '0x%08x' % d)



if __name__ == '__main__':
    cli(obj=HFObject(), complete_var='_HFBUTLER_COMPLETE')
