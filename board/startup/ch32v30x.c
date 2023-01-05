#include "debug.h"

void usb_dc_low_level_init(void)
{
    RCC_USBCLK48MConfig(RCC_USBCLK48MCLKSource_USBPHY);
    RCC_USBHSPLLCLKConfig(RCC_HSBHSPLLCLKSource_HSE);
    RCC_USBHSConfig(RCC_USBPLL_Div2);
    RCC_USBHSPLLCKREFCLKConfig(RCC_USBHSPLLCKREFCLK_4M);
    RCC_USBHSPHYPLLALIVEcmd(ENABLE);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHS, ENABLE);
    NVIC_EnableIRQ(USBHS_IRQn);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, ENABLE);
    //EXTEN->EXTEN_CTR |= EXTEN_USBD_PU_EN;
    NVIC_EnableIRQ(OTG_FS_IRQn);

    Delay_Us(100);
}

void usb_hc_low_level_init(void)
{
#ifdef CH32V30x_D8C
    RCC_USBCLK48MConfig(RCC_USBCLK48MCLKSource_USBPHY);
    RCC_USBHSPLLCLKConfig(RCC_HSBHSPLLCLKSource_HSE);
    RCC_USBHSConfig(RCC_USBPLL_Div2);
    RCC_USBHSPLLCKREFCLKConfig(RCC_USBHSPLLCKREFCLK_4M);
    RCC_USBHSPHYPLLALIVEcmd(ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHS, ENABLE);
#else
    if (SystemCoreClock == 144000000) {
        RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLCLK_Div3);
    } else if (SystemCoreClock == 96000000) {
        RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLCLK_Div2);
    } else if (SystemCoreClock == 48000000) {
        RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLCLK_Div1);
    }
#endif
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, ENABLE);
    NVIC_EnableIRQ(OTG_FS_IRQn);
    NVIC_EnableIRQ(USBHS_IRQn);
    static uint32_t wait_ct = 20000;
    while (wait_ct--) {
    }
}

void TIM3_Init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    /* Enable timer3 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Initialize timer3 */
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Enable updating timer3 interrupt */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    /* Configure timer3 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable timer3 */
    TIM_Cmd(TIM3, ENABLE);

    /* Enable timer3 interrupt */
    NVIC_EnableIRQ(TIM3_IRQn);
}

void board_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    TIM3_Init(9, SystemCoreClock / 1000 - 1);
}

volatile uint32_t millis_count = 0;

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != 0) {
        millis_count++;
        /* Clear interrupt flag */
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

uint32_t chey_board_millis(void)
{
    return millis_count;
}