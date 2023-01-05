#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "hid_custom_inout_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device hid custom example\n");
    extern void hid_custom_keyboard_init(void);
    hid_custom_keyboard_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    // Everything is interrupt driven so just loop here
    while (1) {
        extern void hid_custom_test(void);
        hid_custom_test();
    }
    return 0;
}
