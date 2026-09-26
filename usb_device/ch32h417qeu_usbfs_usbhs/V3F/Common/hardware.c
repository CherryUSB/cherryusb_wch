/********************************** (C) COPYRIGHT  *******************************
* File Name          : hardware.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2025/03/01
* Description        : This file provides all the hardware firmware functions.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "hardware.h"
#include "usbd_core.h"

void USBHS_RCC_Init(FunctionalState sta)
{
    if (sta)
    {
        /* Enable UTMI Clock */
        RCC_UTMIcmd(ENABLE);
        /* Enable USBHS Clock */
        RCC_HBPeriphClockCmd(RCC_HBPeriph_USBHS, ENABLE);
    }
    else
    {
        RCC_HBPeriphClockCmd(RCC_HBPeriph_USBHS, DISABLE);
        RCC_UTMIcmd(DISABLE);
        if((RCC->PLLCFGR & RCC_SYSPLL_SEL) != RCC_SYSPLL_USBHS)
        {
            RCC_USBHS_PLLCmd(DISABLE);
        }
    }
}

void USBFS_RCC_Init(void)
{
    RCC_USBFSCLKConfig(RCC_USBFSCLKSource_USBHSPLL);
    RCC_USBFS48ClockSourceDivConfig(RCC_USBFS_Div10);
    RCC_HBPeriphClockCmd(RCC_HBPeriph_OTG_FS, ENABLE);
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOA, ENABLE);
}

void usb_dc_low_level_init(uint8_t busid)
{
    if(busid == 0)
    {
        printf("usbfs init\r\n");
        USBFS_RCC_Init();
        NVIC_EnableIRQ(USBFS_IRQn);
    }
    else
    {
        printf("usbhs init\r\n");
        USBHS_RCC_Init(ENABLE);
        NVIC_EnableIRQ(USBHS_IRQn);
    }

}

void usb_dc_low_level_deinit(uint8_t busid)
{
    if(busid == 0)
    {
        NVIC_DisableIRQ(USBFS_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(USBHS_IRQn);
        USBHS_RCC_Init(DISABLE);
    }
}

void USBFS_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void USBFS_IRQHandler(void)
{
    USBD_IRQHandler(0);
}

void USBHS_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void USBHS_IRQHandler(void)
{
    USBD_IRQHandler(1);
}
/*********************************************************************
 * @fn      Hardware
 *
 * @brief   Resets the CRC Data register (DR).
 *
 * @return  none
 */
void Hardware(void)
{
    printf("cherryusb test\r\n");

    if((RCC->PLLCFGR & RCC_SYSPLL_SEL) != RCC_SYSPLL_USBHS)
    {
        /* Initialize USBHS 480M PLL */
        RCC_USBHS_PLLCmd(DISABLE);
        RCC_USBHSPLLCLKConfig(RCC_USBHSPLLSource_HSE);
        RCC_USBHSPLLReferConfig(RCC_USBHSPLLRefer_25M);
        RCC_USBHSPLLClockSourceDivConfig(RCC_USBHSPLL_IN_Div1);
        RCC_USBHS_PLLCmd(ENABLE);
        while (!(RCC->CTLR & RCC_USBHS_PLLRDY));
    }
    extern struct usbd_dc_driver wch_usbfs_dc_driver;
    extern struct usbd_dc_driver wch_usbhs_dc_driver;

    usbd_register_dc_driver(0, &wch_usbfs_dc_driver);
    usbd_register_dc_driver(1, &wch_usbhs_dc_driver);
    extern void cdc_acm_init(uint8_t busid, uintptr_t reg_base);
    extern void cdc_acm_data_send_with_dtr_test(uint8_t busid);

    cdc_acm_init(0, USBFS_BASE);
    cdc_acm_init(1, USBHS_BASE);
    while (1)
    {
        cdc_acm_data_send_with_dtr_test(0);
        cdc_acm_data_send_with_dtr_test(1);
    }
}
