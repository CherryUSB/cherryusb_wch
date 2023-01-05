#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "cdc_acm_multi_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device cdc acm multitude example\n");
    extern void cdc_acm_multi_init(void);
    cdc_acm_multi_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    // Everything is interrupt driven so just loop here
    while (1) {
    }
    return 0;
}
