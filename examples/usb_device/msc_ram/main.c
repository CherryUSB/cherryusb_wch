#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "msc_ram_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device msc ram example\n");
    extern void msc_ram_init(void);
    msc_ram_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    // Everything is interrupt driven so just loop here
    while (1) {
    }
    return 0;
}
