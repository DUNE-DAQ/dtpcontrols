# eveyrthing to do with ipbus connection to the device goes here...

import os
import string
import uhal
from ctypes import cdll

def find_conn_file():
    path = os.environ.get('DTPCONTROLS_SHARE')
    name = 'dtp_connections.xml'
    result = []

    for dir in path.split(':'):
        for root, ds, fs in os.walk(dir):
            if name in fs:
                result.append(os.path.join(root, name))

    if len(result)>1:
        print("Multiple connection files!")

    return result[0]


def connectionManager(conn_file):

    uhal.setLogLevelTo(uhal.LogLevel.WARNING)
    conn_file = "file://"+conn_file

    try:
        cdll.LoadLibrary("libuhallibs.so")
        manager = uhal.ConnectionManager(conn_file, ['ipbusflx-2.0'])
    except OSError:
        manager = uhal.ConnectionManager(conn_file)

    return manager


def softReset(ctrlNode):

    print("Soft reset")
    ctrlNode.getNode("csr.ctrl.soft_rst").write(1)
    ctrlNode.getClient().dispatch()
    csrVal = ctrlNode.getNode("csr.ctrl.soft_rst").read()
    ctrlNode.getClient().dispatch()
    print("CSR value after reset = ", csrVal)

    print("Master reset")
    ctrlNode.getNode("csr.ctrl.mst_rst").write(1)
    ctrlNode.getClient().dispatch()
    ctrlNode.getNode("csr.ctrl.mst_rst").write(0)
    ctrlNode.getClient().dispatch()

