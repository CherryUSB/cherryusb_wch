/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_usbhost.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description
 *******************************************************************************/

#include "CH57x_common.h"

/*****************************************************************************
 * Function Name  : InitRootDevice
 * Description    : 初始化指定ROOT-HUB端口的USB设备
 * Input          : DataBuf: 枚举过程中存放的描述符信息缓存区
 * Return         :
 *******************************************************************************/
UINT8 InitRootDevice(PUINT8 DataBuf)
{
    UINT8 i, s;
    UINT8 cfg, dv_cls, if_cls;

    PRINT("Reset host port\n");
    ResetRootHubPort(); // 检测到设备后,复位相应端口的USB总线
    for (i = 0, s = 0; i < 100; i++)
    { // 等待USB设备复位后重新连接,100mS超时
        mDelaymS(1);
        if (EnableRootHubPort() == ERR_SUCCESS)
        { // 使能端口
            i = 0;
            s++;
            if (s > 100)
                break; // 已经稳定连接100mS
        }
    }
    if (i)
    { // 复位后设备没有连接
        DisableRootHubPort();
        PRINT("Disable host port because of disconnect\n");
        return (ERR_USB_DISCON);
    }
    SetUsbSpeed(ThisUsbDev.DeviceSpeed); // 设置当前USB速度

    PRINT("GetDevDescr: ");
    s = CtrlGetDeviceDescr(DataBuf); // 获取设备描述符
    if (s == ERR_SUCCESS)
    {
        for (i = 0; i < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength; i++)
            PRINT("x%02X ", (UINT16)(DataBuf[i]));
        PRINT("\n");

        ThisUsbDev.DeviceVID = ((PUSB_DEV_DESCR)DataBuf)->idVendor; //保存VID PID信息
        ThisUsbDev.DevicePID = ((PUSB_DEV_DESCR)DataBuf)->idProduct;
        dv_cls = ((PUSB_DEV_DESCR)DataBuf)->bDeviceClass;

        s = CtrlSetUsbAddress(((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue);
        if (s == ERR_SUCCESS)
        {
            ThisUsbDev.DeviceAddress = ((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue; // 保存USB地址

            PRINT("GetCfgDescr: ");
            s = CtrlGetConfigDescr(DataBuf);
            if (s == ERR_SUCCESS)
            {
                for (i = 0; i < ((PUSB_CFG_DESCR)DataBuf)->wTotalLength; i++)
                    PRINT("x%02X ", (UINT16)(DataBuf[i]));
                PRINT("\n");
                /* 分析配置描述符,获取端点数据/各端点地址/各端点大小等,更新变量endp_addr和endp_size等 */
                cfg = ((PUSB_CFG_DESCR)DataBuf)->bConfigurationValue;
                if_cls = ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceClass; // 接口类代码

                if ((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_STORAGE))
                { // 是USB存储类设备,基本上确认是U盘
#ifdef FOR_ROOT_UDISK_ONLY
                    CH579DiskStatus = DISK_USB_ADDR;
                    return (ERR_SUCCESS);
                }
                else
                    return (ERR_USB_UNSUPPORT);
#else
                    s = CtrlSetUsbConfig(cfg); // 设置USB设备配置
                    if (s == ERR_SUCCESS)
                    {
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = USB_DEV_CLASS_STORAGE;
                        PRINT("USB-Disk Ready\n");
                        SetUsbSpeed(1); // 默认为全速
                        return (ERR_SUCCESS);
                    }
                }
                else if ((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_PRINTER) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass == 0x01)
                {                              // 是打印机类设备
                    s = CtrlSetUsbConfig(cfg); // 设置USB设备配置
                    if (s == ERR_SUCCESS)
                    {
                        //	需保存端点信息以便主程序进行USB传输
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = USB_DEV_CLASS_PRINTER;
                        PRINT("USB-Print Ready\n");
                        SetUsbSpeed(1); // 默认为全速
                        return (ERR_SUCCESS);
                    }
                }
                else if ((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_HID) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass <= 0x01)
                {   // 是HID类设备,键盘/鼠标等
                    //  从描述符中分析出HID中断端点的地址
                    //  保存中断端点的地址,位7用于同步标志位,清0
                    if_cls = ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceProtocol;
                    s = CtrlSetUsbConfig(cfg); // 设置USB设备配置
                    if (s == ERR_SUCCESS)
                    {
                        //	    					Set_Idle( );
                        //	需保存端点信息以便主程序进行USB传输
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        if (if_cls == 1)
                        {
                            ThisUsbDev.DeviceType = DEV_TYPE_KEYBOARD;
                            //	进一步初始化,例如设备键盘指示灯LED等
                            PRINT("USB-Keyboard Ready\n");
                            SetUsbSpeed(1); // 默认为全速
                            return (ERR_SUCCESS);
                        }
                        else if (if_cls == 2)
                        {
                            ThisUsbDev.DeviceType = DEV_TYPE_MOUSE;
                            //	为了以后查询鼠标状态,应该分析描述符,取得中断端口的地址,长度等信息
                            PRINT("USB-Mouse Ready\n");
                            SetUsbSpeed(1); // 默认为全速
                            return (ERR_SUCCESS);
                        }
                        s = ERR_USB_UNSUPPORT;
                    }
                }
                else
                {                              // 可以进一步分析
                    s = CtrlSetUsbConfig(cfg); // 设置USB设备配置
                    if (s == ERR_SUCCESS)
                    {
                        //	需保存端点信息以便主程序进行USB传输
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = DEV_TYPE_UNKNOW;
                        SetUsbSpeed(1);       // 默认为全速
                        return (ERR_SUCCESS); /* 未知设备初始化成功 */
                    }
                }
#endif
            }
        }
    }

    PRINT("InitRootDev Err = %02X\n", (UINT16)s);
#ifdef FOR_ROOT_UDISK_ONLY
    CH579DiskStatus = DISK_CONNECT;
#else
    ThisUsbDev.DeviceStatus = ROOT_DEV_FAILED;
#endif
    SetUsbSpeed(1); // 默认为全速
    return (s);
}
