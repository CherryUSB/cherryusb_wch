#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "hid_mouse_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device hid mouse example\n");
    extern void hid_mouse_init(void);
    hid_mouse_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    // Everything is interrupt driven so just loop here
    while (1) {
        extern void hid_mouse_test(void);
        hid_mouse_test();
    }
    return 0;
}
