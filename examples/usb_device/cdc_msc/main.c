#include "usbd_core.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */
#include "cdc_acm_msc_template.c"

int main(void)
{
    extern void board_init(void);
    board_init();
    printf("CherryUSB device cdc msc example\n");
    extern void cdc_acm_msc_init(void);
    cdc_acm_msc_init();

    // Wait until configured
    while (!usb_device_is_configured()) {
    }

    // Everything is interrupt driven so just loop here
    while (1) {
        extern void cdc_acm_data_send_with_dtr_test(void);
        cdc_acm_data_send_with_dtr_test();
    }
    return 0;
}
