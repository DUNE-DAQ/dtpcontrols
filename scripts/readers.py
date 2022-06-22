import collections
from texttable import Texttable
import termui
from dtpcontrols import core as controls

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
        probes[i] = controls.get_child_registers(strmCsrNode.getNode('mon'))

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


