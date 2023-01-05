 /********************************** (C) COPYRIGHT  *******************************
 * File Name          : cpuport.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/05/12
 * Description        : WCH Qingke V4A cpu port for rt-thread
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include <rthw.h>
#include <rtthread.h>
#include "cpuport.h"
#include "CH58x_common.h"

#ifndef RT_USING_SMP
volatile rt_ubase_t  rt_interrupt_from_thread = 0;
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
#endif

struct rt_hw_stack_frame
{
    rt_ubase_t epc;        /* epc - epc    - program counter                     */
    rt_ubase_t ra;         /* x1  - ra     - return address for jumps            */
    rt_ubase_t t0;         /* x5  - t0     - temporary register 0                */
    rt_ubase_t t1;         /* x6  - t1     - temporary register 1                */
    rt_ubase_t t2;         /* x7  - t2     - temporary register 2                */
    rt_ubase_t s0_fp;      /* x8  - s0/fp  - saved register 0 or frame pointer   */
    rt_ubase_t s1;         /* x9  - s1     - saved register 1                    */
    rt_ubase_t a0;         /* x10 - a0     - return value or function argument 0 */
    rt_ubase_t a1;         /* x11 - a1     - return value or function argument 1 */
    rt_ubase_t a2;         /* x12 - a2     - function argument 2                 */
    rt_ubase_t a3;         /* x13 - a3     - function argument 3                 */
    rt_ubase_t a4;         /* x14 - a4     - function argument 4                 */
    rt_ubase_t a5;         /* x15 - a5     - function argument 5                 */
    rt_ubase_t a6;         /* x16 - a6     - function argument 6                 */
    rt_ubase_t a7;         /* x17 - s7     - function argument 7                 */
    rt_ubase_t s2;         /* x18 - s2     - saved register 2                    */
    rt_ubase_t s3;         /* x19 - s3     - saved register 3                    */
    rt_ubase_t s4;         /* x20 - s4     - saved register 4                    */
    rt_ubase_t s5;         /* x21 - s5     - saved register 5                    */
    rt_ubase_t s6;         /* x22 - s6     - saved register 6                    */
    rt_ubase_t s7;         /* x23 - s7     - saved register 7                    */
    rt_ubase_t s8;         /* x24 - s8     - saved register 8                    */
    rt_ubase_t s9;         /* x25 - s9     - saved register 9                    */
    rt_ubase_t s10;        /* x26 - s10    - saved register 10                   */
    rt_ubase_t s11;        /* x27 - s11    - saved register 11                   */
    rt_ubase_t t3;         /* x28 - t3     - temporary register 3                */
    rt_ubase_t t4;         /* x29 - t4     - temporary register 4                */
    rt_ubase_t t5;         /* x30 - t5     - temporary register 5                */
    rt_ubase_t t6;         /* x31 - t6     - temporary register 6                */
};

/*
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct rt_hw_stack_frame *frame;
    rt_uint8_t         *stk;
    int                i;

    stk  = stack_addr + sizeof(rt_ubase_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, REGBYTES);
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame *)stk;

    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++)
    {
        ((rt_ubase_t *)frame)[i] = 0xdeadbeef;
    }

    frame->ra      = (rt_ubase_t)texit;
    frame->a0      = (rt_ubase_t)parameter;
    frame->epc     = (rt_ubase_t)tentry;

    return stk;
}

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 * #endif
 */
__attribute__((section(".highcode")))
void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to)
{
    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_interrupt_from_thread = from;
    }
    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    /* switch just in sw_handler */
    PFIC_SetPendingIRQ(SWI_IRQn);
}

/* shutdown CPU */
void rt_hw_cpu_shutdown(void)
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}


extern void SysTick_Handler(void);
extern void TMR0_IRQHandler(void);
extern void GPIOA_IRQHandler(void);
extern void GPIOB_IRQHandler(void);
extern void SPI0_IRQHandler(void);
extern void BB_IRQHandler(void);
extern void LLE_IRQHandler(void);
extern void USB_IRQHandler(void);
extern void USB2_IRQHandler(void);
extern void TMR1_IRQHandler(void);
extern void TMR2_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void RTC_IRQHandler(void);
extern void ADC_IRQHandler(void);
extern void PWMX_IRQHandler(void);
extern void TMR3_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void UART3_IRQHandler(void);
extern void WDOG_BAT_IRQHandler(void);

typedef void (*user_irq_handler_t)(void);

__attribute__((section("wch_user_vectors")))
user_irq_handler_t wch_user_irq_table[] =
{
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   SysTick_Handler,             /* SysTick Handler */
   0,
   0,                           /* SW Handler */
   0,
  /* External Interrupts */
   TMR0_IRQHandler   ,          /* 0:  TMR0 */
   GPIOA_IRQHandler,            /* GPIOA */
   GPIOB_IRQHandler ,           /* GPIOB */
   SPI0_IRQHandler  ,           /* SPI0 */
   BB_IRQHandler   ,            /* BLEB */
   LLE_IRQHandler ,             /* BLEL */
   USB_IRQHandler  ,            /* USB */
   USB2_IRQHandler,
   TMR1_IRQHandler ,            /* TMR1 */
   TMR2_IRQHandler,             /* TMR2 */
   UART0_IRQHandler ,           /* UART0 */
   UART1_IRQHandler,            /* UART1 */
   RTC_IRQHandler,              /* RTC */
   ADC_IRQHandler,              /* ADC */
   0,
   PWMX_IRQHandler,             /* PWMX */
   TMR3_IRQHandler,             /* TMR3 */
   UART2_IRQHandler,            /* UART2 */
   UART3_IRQHandler,            /* UART3 */
   WDOG_BAT_IRQHandler,         /* WDOG_BAT */
};

__attribute__((section(".highcode")))
void user_interrupt_handler(uint32_t mcause)
{
    uint32_t irq_num;
    irq_num = mcause & 0x7f;
    if(wch_user_irq_table[irq_num] != NULL)
    {
        rt_interrupt_enter();
        wch_user_irq_table[irq_num]();
        rt_interrupt_leave();
    }
}
