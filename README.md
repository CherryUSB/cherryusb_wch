# CherryUSB wch

仅支持从机！！！！

- **makefile 版本仅支持 v0.10.x**
- **mrs_project 为目前最新版本 v1.5.0，不再使用 makefile构建，cherryusb 从外部导入，建议放在 mrs_project 目录下**

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