# This is the WCH MCU CherryUSB demo project

## USB Device

```
cd examples/usb_device/xxx

make
or
1、make BOARD=ch582evt    // Building the USB device demo for ch582
2、make BOARD=ch32v307evt // Building the USB device demo for ch32v307

When BOARD is not specified, the default is to build the ch32v307 USB device demo for you.
```

## USB Host

```
cd examples/usb_host

make
or
1、make BOARD=ch582evt    // Building the USB host demo for ch582
2、make BOARD=ch32v307evt // Building the USB host demo for ch32v307

When the BOARD is not specified, the ch32v307 USB host demo will be built for you by default
```
## Examples of successful testing
### Full speed and high speed device
```
cdc_acm
cdc_msc
cdc_multitude
dfu
hid_cdc_msc
hid_custom
hid_kbd
hid_mouse
msc_ram
```

### Full speed host
```
hid
msc
```

### High speed host
```
Currently, some high-speed MSC devices may fail in testing.
```

###  Content waiting for repair
```
1、Under high-speed and full speed hosts, some MSC devices may fail to enumerate.
2、Synchronous transmission of hosts and devices.
```