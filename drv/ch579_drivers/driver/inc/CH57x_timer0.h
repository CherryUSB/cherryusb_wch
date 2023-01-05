


#ifndef __CH57x_TIMER0_H__
#define __CH57x_TIMER0_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

#define	DataBit_25	(1<<25)	 


/**
  * @brief  TMR0 interrupt bit define
  */

#define	TMR0_3_IT_CYC_END 		0x01				// 周期结束标志：捕捉-超时，定时-周期结束，PWM-周期结束
#define	TMR0_3_IT_DATA_ACT		0x02				// 数据有效标志：捕捉-新数据，PWM-有效电平结束
#define	TMR0_3_IT_FIFO_HF 		0x04				// FIFO 使用过半：捕捉- FIFO>=4， PWM- FIFO<4
#define	TMR1_2_IT_DMA_END 		0x08				// DMA 结束，支持TMR1和TMR2
#define	TMR0_3_IT_FIFO_OV 		0x10				// FIFO 溢出：捕捉- FIFO满， PWM- FIFO空
	 
	 
/**
  * @brief  Configuration PWM effective level repeat times
  */
typedef enum
{
	PWM_Times_1 = 0,					// PWM 有效输出重复1次数
	PWM_Times_4,						// PWM 有效输出重复4次数
	PWM_Times_8,						// PWM 有效输出重复8次数
	PWM_Times_16,						// PWM 有效输出重复16次数
}PWM_RepeatTsTypeDef;	


/**
  * @brief  Configuration Cap mode
  */
typedef enum
{
	CAP_NULL = 0,						// 不捕捉
	Edge_To_Edge,						// 任意边沿之间
	FallEdge_To_FallEdge,				// 下降沿到下降沿
	RiseEdge_To_RiseEdge,				// 上升沿到上升沿
}CapModeTypeDef;	



// 定时和计数
void TMR0_TimerInit( UINT32 t );									/* 定时功能初始化 */	 
void TMR0_EXTSingleCounterInit( UINT32 c );							/* 外部信号计数功能初始化 */
#define  TMR0_GetCurrentCount()		R32_TMR0_COUNT	 				/* 获取当前计数值，最大67108864 */

// PWM功能
#define TMR0_PWMCycleCfg( cyc )	    (R32_TMR0_CNT_END=cyc)			/* PWM0 通道输出波形周期配置, 最大67108864 */
void TMR0_PWMInit( PWMX_PolarTypeDef pr, PWM_RepeatTsTypeDef ts );	/* PWM 输出初始化 */	 
#define TMR0_PWMActDataWidth( d )   (R32_TMR0_FIFO = d)			/* PWM0 有效数据脉宽, 最大67108864 */
	 
// 捕捉脉宽
#define TMR0_CAPTimeoutCfg( cyc )   (R32_TMR0_CNT_END=cyc)			/* CAP0 捕捉电平超时配置, 最大33554432 */
void TMR0_CapInit( CapModeTypeDef cap );							/* 外部信号捕捉功能初始化 */
#define TMR0_CAPGetData()			R32_TMR0_FIFO					/* 获取脉冲数据 */
#define TMR0_CAPDataCounter()		R8_TMR0_FIFO_COUNT				/* 获取当前已捕获数据个数 */


#define TMR0_Disable()				(R8_TMR0_CTRL_MOD &= ~RB_TMR_COUNT_EN)		/* 关闭 TMR0 */
// refer to TMR0 interrupt bit define
#define	TMR0_ITCfg(s,f)				((s)?(R8_TMR0_INTER_EN|=f):(R8_TMR0_INTER_EN&=~f))		/* TMR0 相应中断位开启与关闭 */
// refer to TMR0 interrupt bit define
#define TMR0_ClearITFlag(f)         (R8_TMR0_INT_FLAG = f)			/* 清除中断标志 */
#define TMR0_GetITFlag(f)           (R8_TMR0_INT_FLAG&f)			/* 查询中断标志状态 */


	 
#ifdef __cplusplus
}
#endif

#endif  // __CH57x_TIMER0_H__	

