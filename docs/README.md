# dtpcontrols

This package contains python tools for control of the DUNE Trigger Primitive firmware.

## Control API

The entry point for control of the firmware is the DTPPodNode, which should be created using a uhal::HwInterface :

```C++
uhal::ConnectionManager cm( conn_file_name , {"ipbusflx-2.0"});
uhal::HwInterface flx = cm.getDevice( device_name );
DTPPodNode dtp_pod_node ( flx.getNode() );
```

The DTPPodNode provides methods to navigate the firmware node structure, such as `get_control_node()` etc.  These methods return firmware nodes of various types, which provide further navigation methods, as well as methods that control/configure the firmware.

However, all high level actions can be instigated via methods on DTPPodNode. The C++ applications in test/apps can be used as examples. 

DTPPodNode is not currently thread safe.

## Python tools

hfButler.py provides control, test and diagnostic functions.  Some examples of usage are given below.

Note that the first argument is the device to control. These examples control TPG firmware in one half FELIX.

* reset and configure TPG FW with the internal wibulator data source
```
hfButler.py flx-0-p2-hf init
hfButler.py flx-0-p2-hf cr-if --on --drop-empty
hfButler.py flx-0-p2-hf flowmaster --src-sel wibtor --sink-sel hits
hfButler.py flx-0-p2-hf link hitfinder -t 20
hfButler.py flx-0-p2-hf link mask enable -c 1-63
hfButler.py flx-0-p2-hf link config --dr-on --dpr-mux passthrough --drop-empty
```

* to configure for external data, replace the relevant line above with
```
hfButler.py flx-0-p2-hf flowmaster --src-sel gbt --sink-sel hits
```

* configure the wibulator data source to send patterns.  Note the last line will cause the wiulator to fire in one-shot mode.
```
hfButler.py flx-0-p2-hf wtor -i 0 config dtp-patterns/FixedHits/A/FixedHits_A_wib_axis_32b.txt
hfButler.py flx-0-p2-hf wtor -i 0 fire -l
```

## C++ tools

The following tools test the C++ code in standalone mode (ie. outside dunedaq).  Only basic functionality is provided so far.

* reset TP firmware
```
dtpcontrols_test_reset
```

* configure TP firmware
```
dtpcontrols_test_reset
```

* enable TP production
```
dtpcontrols_test_enable
```

* monitor TP processing
```
dtpcontrols_test_monitor
```

