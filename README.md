# This is the WCH MCU CherryUSB demo project

## USB Device

```
cd examples/usb_device/xxx

make
or
1、make BOARD=ch582evt    // Building the USB device demo for ch582
2、make BOARD=ch32v307evt // Building the USB device demo for ch32v307

When BOARD is not specified, the default is to build the ch32v307 USB device demo for you.
Note that when using the ch32v307 usb device, remove the const modifier in front of the descriptor array in the demo.
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