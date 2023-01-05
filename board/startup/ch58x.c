#include "CH58x_common.h"

void usb_dc_low_level_init(void)
{
    extern void USB_IRQHandler(void);
    PFIC_EnableIRQ(USB_IRQn);
    PFIC_EnableFastINT0(USB_IRQn, (uint32_t)(void *)USB_IRQHandler);
}

void usb_hc_low_level_init(void)
{
    PFIC_EnableIRQ(USB2_IRQn);
}

void board_init(void)
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);

#if (DEBUG == 1)
    /**
     * Use UART1 to debug GPIOA8--RX // GPIOA9--TX
     */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
#endif

    TMR0_TimerInit(FREQ_SYS / 1000);
    TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END);
    PFIC_EnableIRQ(TMR0_IRQn);
    PFIC_SetPriority(TMR0_IRQn, 20);
}

volatile uint32_t timer_count_user = 0;

__INTERRUPT
__HIGH_CODE
void TMR0_IRQHandler(void)
{
    /*!< Timer 0 IRQ */
    if (TMR0_GetITFlag(TMR0_3_IT_CYC_END)) {
        /*!< Clear Pending flag */
        TMR0_ClearITFlag(TMR0_3_IT_CYC_END);

        /*!< Updata the ms count */
        timer_count_user++;
        /*!< Set timing time 1ms */
        R32_TMR0_CNT_END = GetSysClock() / 1000;
        R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
        R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN;

        /*!< Enable interrupt */
        TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END);
    }
}

uint32_t chey_board_millis(void)
{
    return timer_count_user;
}