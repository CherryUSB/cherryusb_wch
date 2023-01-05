#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "hid_keyboard_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device hid keyboard example\n");
    extern void hid_keyboard_init(void);
    hid_keyboard_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    static uint32_t wait_ct = 100000;
    // Everything is interrupt driven so just loop here
    while (1) {
        extern void hid_keyboard_test(void);
        hid_keyboard_test();
        while (wait_ct--) {
        }
        uint8_t sendbuffer[8] = { 0 };
        usbd_ep_start_write(HID_INT_EP, sendbuffer, 8);
        wait_ct = 400000;
        while (wait_ct--) {
        }
    }
    return 0;
}
