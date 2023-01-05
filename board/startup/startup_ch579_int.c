#include "CH57x_clk.h"

extern int main(void);
extern unsigned int _lvmdata, _sdata, _edata, _sbss, _ebss;

void _copydata(unsigned int *form, unsigned int *section_begin, unsigned int *section_end)
{
    unsigned int *p = section_begin;
    while (p < section_end) {
        *(p++) = *(form++);
    }
}

void _bssinit(unsigned int *startbss, unsigned int *endbss)
{
    unsigned int *p = startbss;
    while (p < endbss) {
        *(p++) = 0;
    }
}

void Reset_Handler(void)
{
    _bssinit(&_sbss, &_ebss);
    _copydata(&_lvmdata, &_sdata, &_edata);
    SystemInit();
    main();
}
void NMI_Handler(void)
{
    while (1)
        ;
}
void HardFault_Handler(void)
{
    while (1)
        ;
}
void SVC_Handler(void)
{
    while (1)
        ;
}
void PendSV_Handler(void)
{
    while (1)
        ;
}
void SysTick_Handler(void)
{
}

__attribute__((weak)) void TMR0_IRQHandler(void)
{
} // 0:  TMR0
__attribute__((weak)) void GPIO_IRQHandler(void)
{
} // 1:  GPIO
__attribute__((weak)) void SLAVE_IRQHandler(void)
{
} // 2:  SLAVE
__attribute__((weak)) void SPI0_IRQHandler(void)
{
} // 3:  SPI0
__attribute__((weak)) void BB_IRQHandler(void)
{
} // 4:  BB
__attribute__((weak)) void LLE_IRQHandler(void)
{
} // 5:  LLE
__attribute__((weak)) void USB_IRQHandler(void)
{
} // 6:  USB
__attribute__((weak)) void ETH_IRQHandler(void)
{
} // 7:  ETH
__attribute__((weak)) void TMR1_IRQHandler(void)
{
} // 8:  TMR1
__attribute__((weak)) void TMR2_IRQHandler(void)
{
} // 9:  TMR2
__attribute__((weak)) void UART0_IRQHandler(void)
{
} // 10:  UART0
__attribute__((weak)) void UART1_IRQHandler(void)
{
} // 11:  UART1
__attribute__((weak)) void RTC_IRQHandler(void)
{
} // 12:  RTC
__attribute__((weak)) void ADC_IRQHandler(void)
{
} // 13:  ADC
__attribute__((weak)) void SPI1_IRQHandler(void)
{
} // 14:  SPI1
__attribute__((weak)) void LED_IRQHandler(void)
{
} // 15:  LED
__attribute__((weak)) void TMR3_IRQHandler(void)
{
} // 16:  TMR3
__attribute__((weak)) void UART2_IRQHandler(void)
{
} // 17:  UART2
__attribute__((weak)) void UART3_IRQHandler(void)
{
} // 18:  UART3
__attribute__((weak)) void WDT_IRQHandler(void)
{
} // 19:  WDT