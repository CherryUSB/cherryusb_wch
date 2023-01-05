/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_pwr.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description
 *******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
* Function Name  : PWR_DCDCCfg
* Description    : 启用内部DC/DC电源，用于节约系统功耗
* Input          : s:
                    ENABLE  - 打开DCDC电源
                    DISABLE - 关闭DCDC电源
* Return         : None
*******************************************************************************/
void PWR_DCDCCfg(UINT8 s)
{
    if (s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN &= ~(RB_PWR_DCDC_EN | RB_PWR_DCDC_PRE); // 旁路 DC/DC
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN |= RB_PWR_DCDC_PRE;
        DelsyUs(10);
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN |= RB_PWR_DCDC_EN;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
    }
}

/*******************************************************************************
* Function Name  : PWR_UnitModCfg
* Description    : 可控单元模块的电源控制
* Input          : s:
                    ENABLE  - 打开
                    DISABLE - 关闭
                   unit:
                    please refer to unit of controllable power supply
* Return         : None
*******************************************************************************/
void PWR_UnitModCfg(UINT8 s, UINT8 unit)
{
    if (s == DISABLE) //关闭
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if (unit & UNIT_ETH_PHY)
            R8_SLP_WAKE_CTRL &= ~RB_SLP_ETH_WAKE;
        R8_HFCK_PWR_CTRL &= ~(unit & 0x1c);
        R8_CK32K_CONFIG &= ~(unit & 0x03);
    }
    else //打开
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if (unit & UNIT_ETH_PHY)
            R8_SLP_WAKE_CTRL |= RB_SLP_ETH_WAKE;
        R8_HFCK_PWR_CTRL |= (unit & 0x1c);
        R8_CK32K_CONFIG |= (unit & 0x03);
    }
}

/*******************************************************************************
* Function Name  : PWR_PeriphClkCfg
* Description    : 外设时钟控制位
* Input          : s:
                    ENABLE  - 打开外设时钟
                    DISABLE - 关闭外设时钟
                   perph:
                    please refer to Peripher CLK control bit define
* Return         : None
*******************************************************************************/
void PWR_PeriphClkCfg(UINT8 s, UINT16 perph)
{
    if (s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL |= perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL &= ~perph;
    }
}

/*******************************************************************************
* Function Name  : PWR_PeriphWakeUpCfg
* Description    : 睡眠唤醒源配置
* Input          : s:
                    ENABLE  - 打开此外设睡眠唤醒功能
                    DISABLE - 关闭此外设睡眠唤醒功能
                   perph:
                    RB_SLP_USB_WAKE	    -  USB 为唤醒源
                    RB_SLP_ETH_WAKE	    -  ETH 为唤醒源
                    RB_SLP_RTC_WAKE	    -  RTC 为唤醒源
                    RB_SLP_GPIO_WAKE	-  GPIO 为唤醒源
                    RB_SLP_BAT_WAKE	    -  BAT 为唤醒源
                    ALL     -  以上所有
* Return         : None
*******************************************************************************/
void PWR_PeriphWakeUpCfg(UINT8 s, UINT16 perph)
{
    if (s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL &= ~perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL |= perph;
    }
}

/*******************************************************************************
 * Function Name  : LowPower_Idle
 * Description    : 低功耗-Idle模式
 * Input          : None
 * Return         : None
 *******************************************************************************/
void LowPower_Idle(void)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk; // sleep
    __WFI();
}

/*******************************************************************************
 * Function Name  : LowPower_Halt_1
 * Description    : 低功耗-Halt_1模式
 * Input          : None
 * Return         : None
 *******************************************************************************/
void LowPower_Halt_1(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL &= ~RB_SLP_ROM_PWR_DN; // flash待机
    R8_SAFE_ACCESS_SIG = 0;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * Function Name  : LowPower_Halt_2
 * Description    : 低功耗-Halt_2模式
 * Input          : None
 * Return         : None
 *******************************************************************************/
void LowPower_Halt_2(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL |= RB_SLP_ROM_PWR_DN; // flash停机
    R8_SAFE_ACCESS_SIG = 0;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Sleep
* Description    : 低功耗-Sleep模式
* Input          : rm:
                    RB_PWR_RAM2K	-	最后2K SRAM 供电
                    RB_PWR_RAM14K	-	0x20004000 - 0x20007800 14K SRAM 供电
                    RB_PWR_EXTEND	-	USB和RF 单元保留区域供电
                   NULL	-	以上单元都断电
* Return         : None
*******************************************************************************/
void LowPower_Sleep(UINT8 rm)
{
    //	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    //    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    //    R16_CLK_SYS_CFG = (R16_CLK_SYS_CFG&0xff00)|8;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN &= (RB_PWR_DCDC_EN | RB_PWR_DCDC_PRE);
    R16_POWER_PLAN |= RB_PWR_PLAN_EN | RB_PWR_MUST_0010 | RB_PWR_MUST_1 | RB_PWR_CORE | rm;
    R8_SAFE_ACCESS_SIG = 0;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Shutdown
* Description    : 低功耗-Shutdown模式
* Input          : rm:
                    RB_PWR_RAM2K	-	最后2K SRAM 供电
                   NULL	-	以上单元都断电
* Return         : None
*******************************************************************************/
void LowPower_Shutdown(UINT8 rm)
{
    //	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    //    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    //    R16_CLK_SYS_CFG = (R16_CLK_SYS_CFG&0xff00)|8;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN &= (RB_PWR_DCDC_EN | RB_PWR_DCDC_PRE);
    R16_POWER_PLAN |= RB_PWR_PLAN_EN | RB_PWR_MUST_0010 | RB_PWR_MUST_1 | rm;
    R8_SAFE_ACCESS_SIG = 0;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}
