import collections
from .texttable import Texttable
from . import termui
import click
from rich import print as rprint
from rich.table import Table


# -----------------------------------------------------------------------------
def dumpSubRegs(node):
    regs = {}
    for i in sorted(node.getNodes()):
        regs[i] = node.getNode(i).read()
    node.getClient().dispatch()

    return {k: v.value() for k, v in regs.items()}


# -----------------------------------------------------------------------------
def dumpReg(node):
    v = node.read()
    node.getClient().dispatch()
    return {node.getId(): v.value()}


# -----------------------------------------------------------------------------
def readTpgStatus(node):

    row_names = [
        'upck >> hsc',
        'hsc  >> psub',
        'psub >> fir ',
        'fir  >> hf',
        'hf   >> hsc',
        'hsc  >> cr_if'
    ]

    flag_map = collections.OrderedDict([
        ('v', 'valid'),
        ('u', 'user'),
        ('l', 'last')
    ])

    probes = {}
    for i in range(4):
        node.getNode('sel.chain').write(i)
        node.getClient().dispatch()
        probes[i] = dumpSubRegs(node.getNode('csr.mon'))

    hdr = ['probe']+['{}'.format(k) for k in range(4)]
    tpg_table = Texttable(max_width=0)
    tpg_table.header(hdr)
    tpg_table.set_deco(Texttable.HEADER | Texttable.BORDER | Texttable.VLINES)
    tpg_table.set_chars(['-', '|', '+', '-'])
    for k in range(6):
        lbl = 'p'+str(k)

        flags = ''.join([f for f, l in flag_map.items() if probes[i][lbl+'.'+l]])

        row = [lbl+': '+row_names[k]]+['{} [{}] ({}) {}'.format(probes[i][lbl+'.pkt_ctr'], 'rdy' if probes[i][lbl+'.ready'] else 'bsy', flags, probes[i][lbl+'.last_err']) for i in range(4)]
        tpg_table.add_row(row)
    tbl = tpg_table.draw()
    tbl = tbl.replace('[rdy]', '['+termui.kGreen+'rdy'+termui.kReset+']')
    tbl = tbl.replace('[bsy]', '['+termui.kRed+'bsy'+termui.kReset+']')
    return tbl


# -----------------------------------------------------------------------------
def readStreamProcessorStatus(node, nproc):

    row_names = [
        'upck >> hsc',
        'hsc  >> psub',
        'psub >> fir ',
        'fir  >> hf',
        'hf   >> hsc',
        'hsc  >> cr_if'
    ]

    flag_map = collections.OrderedDict([
        ('v', 'valid'),
        ('u', 'user'),
        ('l', 'last')
    ])

    strmSelNode = node.getNode('csr.ctrl.stream_sel')
    strmCapNode = node.getNode('csr.ctrl.cap_ctrs')
    strmCsrNode = node.getNode('stream_proc.csr')
    strmCapNode.write(1)
    strmCapNode.write(0)
    strmCapNode.getClient().dispatch()

    probes = {}
    for i in range(nproc):
        strmSelNode.write(i)
        node.getClient().dispatch()
        probes[i] = dumpSubRegs(strmCsrNode.getNode('mon'))

    hdr = ['probe']+['{}'.format(k) for k in range(nproc)]
    tpg_table = Texttable(max_width=0)
    tpg_table.header(hdr)
    tpg_table.set_deco(Texttable.HEADER | Texttable.BORDER | Texttable.VLINES)
    tpg_table.set_chars(['-', '|', '+', '-'])
    for k in range(6):
        lbl = 'p'+str(k)

        flags = ''.join([f for f, l in flag_map.items() if probes[i][lbl+'.'+l]])

        row = [lbl+': '+row_names[k]]+['{} [{}] ({}) {}'.format(probes[i][lbl+'.pkt_ctr'], 'rdy' if probes[i][lbl+'.ready'] else 'bsy', flags, probes[i][lbl+'.last_err']) for i in range(4)]
        tpg_table.add_row(row)
    tbl = tpg_table.draw()
    tbl = tbl.replace('[rdy]', '['+termui.kGreen+'rdy'+termui.kReset+']')
    tbl = tbl.replace('[bsy]', '['+termui.kRed+'bsy'+termui.kReset+']')
    return tbl


# -----------------------------------------------------------------------------
def readSinkStatus(node):

    reg_map = collections.OrderedDict([
        ('en', 'ctrl.en'),
        ('fifo_mode', 'ctrl.fifo_mode'),
        ('rdy_mode', 'ctrl.rdy_mode'),
        ('empty', 'stat.empty'),
        ('err', 'stat.err'),
        ('full', 'stat.full'),
        ('count', 'count')
    ])

    sinks = {}
    for i in range(4):
        sinks[i] = dumpSubRegs(node.getNode('sink'+str(i)+'.csr'))
        sinks[i].update(dumpReg(node.getNode('sink'+str(i)+'.buf.count')))

    hdr = ['reg']+['{}'.format(k) for k in range(4)]
    sink_table = Texttable(max_width=0)
    sink_table.header(hdr)
    sink_table.set_deco(Texttable.HEADER | Texttable.BORDER | Texttable.VLINES)
    sink_table.set_chars(['-', '|', '+', '-'])
    for k, l in reg_map.items():
        row = [k]+[sinks[i][l] for i in range(4)]
        sink_table.add_row(row)

    return sink_table.draw()


# ------------------------------------------------------------------------------
def printRegTable(aRegs, **kwargs):
    rprint( dict_to_hextable(aRegs, **kwargs) )
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
def formatRegTable(aRegs, aHeader=True, aSort=True):

    lRegTable = Texttable(max_width=0)
    lRegTable.set_deco(Texttable.VLINES | Texttable.BORDER | Texttable.HEADER)
    lRegTable.set_chars(['-', '|', '+', '-'])
    if aHeader:
        lRegTable.header( ['name', 'value'] )

    lRegs = sorted(aRegs) if aSort else aRegs
    for k in lRegs:
        lRegTable.add_row( [str(k), hex(aRegs[k])] )

    return lRegTable.draw()
# ------------------------------------------------------------------------------

# -----------------------------------------------------------------------------
def dump_sub_regs(node, names: list = None):

    if names is None:
        names = sorted(node.getNodes())
    regs = OrderedDict()
    for i in names:
        regs[i] = node.getNode(i).read()
        node.getClient().dispatch()

    return {k: hex(v.value()) for k, v in regs.items()}

# -----------------------------------------------------------------------------
def dump_reg(node):
    v = node.read()
    node.getClient().dispatch()
    return {node.getId(): v.value()}

# -----------------------------------------------------------------------------
def dict_to_table( vals: dict, **kwargs):
    t = Table(**kwargs)
    t.add_column('name')
    t.add_column('value', style='green')
    for k,v in vals.items():
        t.add_row(k,str(v))

    return t

# -----------------------------------------------------------------------------
def dict_to_hextable( vals: dict, **kwargs):
    t = Table(**kwargs)
    t.add_column('name')
    t.add_column('value', style='green')
    for k,v in vals.items():
        t.add_row(k,hex(v))

    return t


# ------------------------------------------------------------------------------
def printDictTable(aDict, aHeader=True, aSort=True, aFmtr=None):
    rprint(dict_to_table(aDict) )
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
def formatDictTable(aDict, aHeader=True, aSort=True, aFmtr=str):
    lDictTable = Texttable(max_width=0)
    lDictTable.set_deco(Texttable.VLINES | Texttable.BORDER | Texttable.HEADER)
    lDictTable.set_chars(['-', '|', '+', '-'])
    if aHeader:
        lDictTable.header( ['name', 'value'] )

    for k in (sorted(aDict) if aSort else aDict):
        v = aDict[k]
        lDictTable.add_row( [str(k), aFmtr(v) if aFmtr else v])

    return lDictTable.draw()
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
def gen_range_validator(first, last):
    """
    Utility function to generate validators for integer number lists with range check

    """
    def validate_channels(ctx, param, value):
        return _validate_range_impl(value, first, last)

    return validate_channels

# ------------------------------------------------------------------------------
def validate_link_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_links']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def validate_proc_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_port']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def validate_chan_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_mux']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def _validate_range_impl(value, first, last):
        if value is None:
            return None

        if value == 'all':
            return list(range(first, last))
        elif value == 'none':
            return []

        if not value[0].isdigit():
            raise click.ClickException('Malformed option (comma separated list expected): %s' % value)

        _sep  = ','
        _dash = '-'

        numbers = []
        items = value.split(_sep)
        for item in items:
            nums = item.split(_dash)
            if len(nums) == 1:
                # single number
                numbers.append(int(item))
            elif len(nums) == 2:
                i = int(nums[0])
                j = int(nums[1])
                if i > j:
                    raise click.ClickException('Invalid interval '+item)
                numbers.extend(list(range(i, j+1)))
            else:
                raise click.ClickException('Malformed option (comma separated list expected): %s' % value)

        out_of_range = [n for n in numbers if (n < first or n >= last)]
        if any(out_of_range):
            raise click.ClickException('Values out of range %s-%s: %s' % (first, last, out_of_range))

        return numbers
