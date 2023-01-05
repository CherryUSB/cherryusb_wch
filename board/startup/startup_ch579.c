extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

extern void TMR0_IRQHandler(void);  // 0:  TMR0
extern void GPIO_IRQHandler(void);  // 1:  GPIO
extern void SLAVE_IRQHandler(void); // 2:  SLAVE
extern void SPI0_IRQHandler(void);  // 3:  SPI0
extern void BB_IRQHandler(void);    // 4:  BB
extern void LLE_IRQHandler(void);   // 5:  LLE
extern void USB_IRQHandler(void);   // 6:  USB
extern void ETH_IRQHandler(void);   // 7:  ETH
extern void TMR1_IRQHandler(void);  // 8:  TMR1
extern void TMR2_IRQHandler(void);  // 9:  TMR2
extern void UART0_IRQHandler(void); // 10:  UART0
extern void UART1_IRQHandler(void); // 11:  UART1
extern void RTC_IRQHandler(void);   // 12:  RTC
extern void ADC_IRQHandler(void);   // 13:  ADC
extern void SPI1_IRQHandler(void);  // 14:  SPI1
extern void LED_IRQHandler(void);   // 15:  LED
extern void TMR3_IRQHandler(void);  // 16:  TMR3
extern void UART2_IRQHandler(void); // 17:  UART2
extern void UART3_IRQHandler(void); // 18:  UART3
extern void WDT_IRQHandler(void);   // 19:  WDT
typedef void (*Function)(void);
extern unsigned int _Stack_Top;

__attribute__((section("vectors"))) Function VectorArray[] = {
    (Function)&_Stack_Top,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    //外设中断
    TMR0_IRQHandler,  // 0:  TMR0
    GPIO_IRQHandler,  // 1:  GPIO
    SLAVE_IRQHandler, // 2:  SLAVE
    SPI0_IRQHandler,  // 3:  SPI0
    BB_IRQHandler,    // 4:  BB
    LLE_IRQHandler,   // 5:  LLE
    USB_IRQHandler,   // 6:  USB
    ETH_IRQHandler,   // 7:  ETH
    TMR1_IRQHandler,  // 8:  TMR1
    TMR2_IRQHandler,  // 9:  TMR2
    UART0_IRQHandler, // 10:  UART0
    UART1_IRQHandler, // 11:  UART1
    RTC_IRQHandler,   // 12:  RTC
    ADC_IRQHandler,   // 13:  ADC
    SPI1_IRQHandler,  // 14:  SPI1
    LED_IRQHandler,   // 15:  LED
    TMR3_IRQHandler,  // 16:  TMR3
    UART2_IRQHandler, // 17:  UART2
    UART3_IRQHandler, // 18:  UART3
    WDT_IRQHandler    // 19:  WDT
};