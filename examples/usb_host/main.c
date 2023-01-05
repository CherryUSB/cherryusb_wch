#include "rtthread.h"
#include "usbh_core.h"
#include "usbh_hid.h"
ALIGN(RT_ALIGN_SIZE)
static char task1_stack[2048];
static struct rt_thread task1_thread;

extern int usbh_hid_connect(struct usbh_hubport *hport, uint8_t intf);
extern int usbh_hid_disconnect(struct usbh_hubport *hport, uint8_t intf);

const struct usbh_class_driver hid_raw_class_driver = {
    .driver_name = "hid",
    .connect = usbh_hid_connect,
    .disconnect = usbh_hid_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info hid_raw_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = USB_DEVICE_CLASS_HID,
    .subclass = HID_SUBCLASS_NONE,
    .protocol = HID_PROTOCOL_NONE,
    .vid = 0x00,
    .pid = 0x00,
    .class_driver = &hid_raw_class_driver
};

uint8_t hid_buffer[128];
struct usbh_urb hid_intout_urb;
struct usbh_urb hid_intin_urb;
struct usbh_urb hid_kbd_intin_urb;

volatile bool out_ok = false;
volatile bool in_ok = false;
volatile bool kbd_ok = false;
volatile bool enum_ok = false;

void usbh_hid_run(struct usbh_hid *hid_class)
{
    if (hid_class->intf ==
        (hid_class->hport->config.config_desc.bNumInterfaces - 1)) {
        enum_ok = true;
        out_ok = true;
        in_ok = true;
        kbd_ok = true;
        rt_kprintf("Enum ok\r\n");
    }
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
    if (hid_class->intf ==
        (hid_class->hport->config.config_desc.bNumInterfaces - 1)) {
        enum_ok = false;
        rt_kprintf("Detach ok\r\n");
    }
}

static void ch_usbh_hid_out_callback(void *arg, int nbytes)
{
    out_ok = true;
    rt_kprintf("hid out nbytes:%d\r\n", nbytes);
}

static void ch_usbh_hid_in_callback(void *arg, int nbytes)
{
    in_ok = true;

    // if (nbytes > 0) {
    //     for (size_t i = 0; i < nbytes; i++) {
    //         USB_LOG_RAW("0x%02x ", hid_buffer[i]);
    //     }
    // }

    // rt_kprintf("hid in nbytes:%d\r\n", nbytes);
}

static void ch_usbh_kbd_in_callback(void *arg, int nbytes)
{
    kbd_ok = true;

    if (nbytes > 0) {
        for (size_t i = 0; i < nbytes; i++) {
            USB_LOG_RAW("0x%02x ", hid_buffer[i]);
        }
    }

    USB_LOG_RAW("hid in nbytes:%d\r\n", nbytes);
}

int ch_hid_test(void)
{
    if (enum_ok == false) {
        return -1;
    }

    out_ok = false;
    in_ok = false;
    kbd_ok = false;

    int ret;
    struct usbh_hid *hid_class = (struct usbh_hid *)usbh_find_class_instance("/dev/input1");
    struct usbh_hid *hid_kbd_class = (struct usbh_hid *)usbh_find_class_instance("/dev/input0");
    if (hid_class == NULL) {
        USB_LOG_RAW("do not find /dev/input1\r\n");
        return -1;
    }

    if (hid_kbd_class == NULL) {
        USB_LOG_RAW("do not find /dev/input0\r\n");
        return -1;
    }

    memset(hid_buffer, 0, 128);

    // usbh_int_urb_fill(&hid_intout_urb, hid_class->intout, hid_buffer, 32, 0,
    //                   ch_usbh_hid_out_callback, hid_class);
    // ret = usbh_submit_urb(&hid_intout_urb);

    // while (out_ok == false) {
    // }
    // out_ok = false;
    // usbh_int_urb_fill(&hid_intin_urb, hid_class->intin, hid_buffer, 32, 0,
    //                   ch_usbh_hid_in_callback, hid_class);
    // ret = usbh_submit_urb(&hid_intin_urb);

    // while (in_ok == false) {
    //     static uint32_t ct = 0;
    //     ct++;
    //     if (ct > 200000) {
    //         ct = 0;
    //         break;
    //     }
    // }
    // in_ok = false;
    usbh_int_urb_fill(&hid_kbd_intin_urb, hid_kbd_class->intin, hid_buffer, 8,
                      0, ch_usbh_kbd_in_callback, hid_kbd_class);
    ret = usbh_submit_urb(&hid_kbd_intin_urb);

    // kbd_ok = false;

    return ret;
}

void task1_entry(void *parameter)
{
    extern int usbh_initialize(void);
    rt_kprintf("Start usb host task...\r\n");
    usbh_initialize();
    while (1) {
        ch_hid_test();
        rt_thread_delay(10);
    }
}

int main()
{
    rt_enter_critical();
    rt_thread_init(&task1_thread,
                   "task1",
                   task1_entry,
                   RT_NULL,
                   &task1_stack[0],
                   sizeof(task1_stack),
                   6, 20);
    rt_exit_critical();
    rt_thread_startup(&task1_thread);
    return 0;
}

void msh_test_print(void)
{
    rt_kprintf("this is a test for msh.\n");
}
MSH_CMD_EXPORT(msh_test_print, this is a msh test);
