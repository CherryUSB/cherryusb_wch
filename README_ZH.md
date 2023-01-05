# 这是WCH MCU CherryUSB demo 工程

## USB Device

```
cd examples/usb_device/xxx

make
或者
1、make BOARD=ch582evt    // 构建ch582的usb device demo
2、make BOARD=ch32v307evt // 构建ch32v307的usb device demo

当不指定BOARD的时候，默认将为你构建ch32v307的usb device demo
注意在使用ch32v307 usb device的时候，要将demo中描述符数组前面的const修饰符去掉。
```

## USB Host

```
cd examples/usb_host

make
或者
1、make BOARD=ch582evt    // 构建ch582的usb host demo
2、make BOARD=ch32v307evt // 构建ch32v307的usb host demo

当不指定BOARD的时候，默认将为你构建ch32v307的usb host demo
```