# 这是WCH MCU CherryUSB demo 工程

## USB Device

```
cd examples/usb_device/xxx

make
或者
1、make BOARD=ch582evt    // 构建ch582的usb device demo
2、make BOARD=ch32v307evt // 构建ch32v307的usb device demo

当不指定BOARD的时候，默认将为你构建ch32v307的usb device demo
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

## 成功测试的示例
### 全速和高速设备
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

### 全速主机
```
hid
msc
```

### 高速主机
```
目前测试有些U盘可能会失败。
```

###  等待修复的内容
```
1、高速和全速主机下，有一些U盘可能会枚举失败.
2、主机和设备的同步传输.
```