/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_clk.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description
 *******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
 * Function Name  : SystemInit
 * Description    : 系统时钟默认初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void SystemInit(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = (2 << 6) | 0x08; // 32M -> Fsys
}

/*******************************************************************************
* Function Name  : SetSysClock
* Description    : 重设系统运行时钟
* Input          : sc: 系统时钟源选择
                    refer to SYS_CLKTypeDef
* Return         : None
*******************************************************************************/
void SetSysClock(SYS_CLKTypeDef sc)
{
    switch (sc)
    {
    case CLK_SOURCE_LSI:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_CK32K_CONFIG &= ~RB_CLK_OSC32K_XT;
        R16_CLK_SYS_CFG = (3 << 6) | 0x08;
        break;
    case CLK_SOURCE_LSE:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT;
        R16_CLK_SYS_CFG = (3 << 6) | 0x08;
        break;
    case CLK_SOURCE_HSE_32MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (2 << 6) | 0x08;
        break;
    case CLK_SOURCE_HSE_16MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (0 << 6) | 0x02;
        break;
    case CLK_SOURCE_HSE_8MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (0 << 6) | 0x04;
        break;
    case CLK_SOURCE_HSI_32MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = (2 << 6) | 0x08;
        break;
    case CLK_SOURCE_HSI_16MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = (0 << 6) | 0x02;
        break;
    case CLK_SOURCE_HSI_8MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = (0 << 6) | 0x04;
        break;
    case CLK_SOURCE_PLL_40MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (1 << 6) | 12;
        break;
    case CLK_SOURCE_PLL_32MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (1 << 6) | 15;
        break;
    case CLK_SOURCE_PLL_24MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (1 << 6) | 20;
        break;
    case CLK_SOURCE_PLL_20MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (1 << 6) | 24;
        break;
    case CLK_SOURCE_PLL_16MHz:
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (1 << 6) | 30;
        break;
    default:
        break;
    }
}

/*******************************************************************************
* Function Name  : HClk32M_Select
* Description    : 32M 高频时钟来源
* Input          : hc:
                    Clk32M_HSI   -   选择内部32M
                    Clk32M_HSE   -   选择外部32M
* Return         : None
*******************************************************************************/
void HClk32M_Select(HClk32MTypeDef hc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    if (hc == Clk32M_HSI)
        R16_CLK_SYS_CFG &= ~RB_CLK_OSC32M_XT;
    else
        R16_CLK_SYS_CFG |= RB_CLK_OSC32M_XT;
}

/*******************************************************************************
* Function Name  : LClk32K_Select
* Description    : 32K 低频时钟来源
* Input          : hc:
                    Clk32K_LSI   -   选择内部32K
                    Clk32K_LSE   -   选择外部32K
* Return         : None
*******************************************************************************/
void LClk32K_Select(LClk32KTypeDef hc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    if (hc == Clk32K_LSI)
        R8_CK32K_CONFIG &= ~RB_CLK_OSC32K_XT;
    else
        R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT;
}

/*******************************************************************************
 * Function Name  : HSE_Calibration_LSI
 * Description    : 外部32M时钟校准内部32K时钟
 * Input          : None
 * Return         : None
 *******************************************************************************/
void HSE_Calibration_LSI(void)
{
    UINT16 a1, a2, a, cnt;

    cnt = 0;
    a = 0;
    a2 = 0;
    while (1)
    {
        cnt++;
        a1 = a2;
        SingleCalibrat(3); // 粗调
        a2 = R16_INT32K_TUNE;
        if ((a1 > a2) ? ((a1 - a2) <= 3) : ((a2 - a1) <= 3))
            a++;
        else
            a = 0;
        if (a > 3 || cnt > 5)
            break;
    }

    cnt = 0;
    while (1)
    {
        cnt++;
        a1 = a2;
        SingleCalibrat(1); // 微调
        a2 = R16_INT32K_TUNE;
        if ((a1 > a2) ? ((a1 - a2) <= 1) : ((a2 - a1) <= 1))
            a++;
        else
            a = 0;
        if (a > 2 || cnt > 5)
            break;
    }
}

/*******************************************************************************
 * Function Name  : SingleCalibrat
 * Description    : 单次校准
 * Input          : step：步进大小
 * Return         : None
 *******************************************************************************/
void SingleCalibrat(UINT8 step)
{
    UINT16 i, j;
    UINT16 c1, c2;
    UINT16 rev;
    UINT8 st = step;

    rev = R16_CLK_SYS_CFG;
    j = 5 * 16000000 / 32000; // 标称值(需要降频)
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT | (0 << 6) | 0x02; // 16M

    /* 校准 */
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_OSC_CAL_CTRL = RB_OSC_CNT_EN;
    c2 = 0xffff;

    while (1)
    {
        while (!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT))
            ;
        i = R16_OSC_CAL_CNT; // 实时校准后采样值

        while (R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT)
            ;
        while (!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT))
            ;
        i = R16_OSC_CAL_CNT; // 实时校准后采样值

        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if (i > j)
        {
            R16_INT32K_TUNE += st; // 说明 RC 频率偏低
            c1 = c2;
            c2 = i - j;
        }
        else
        {
            R16_INT32K_TUNE -= st; // 说明 RC 频率偏高
            c1 = c2;
            c2 = j - i;
        }

        if (c1 < c2)
        {
            R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
            R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            if (i > j)
                R16_INT32K_TUNE -= st; // 反向校回去
            else
                R16_INT32K_TUNE += st; // 反向校回去
            break;
        }
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = rev;
    R8_OSC_CAL_CTRL = 0;
}

/*******************************************************************************
* Function Name  : RTCInitTime
* Description    : RTC时钟初始化当前时间
* Input          : h: 配置时间 - 小时
                    MAX_H = 393192
                   m: 配置时间 - 分钟
                    MAX_M = 59
                   s: 配置时间 - 秒
                    MAX_S = 59
* Return         : None
*******************************************************************************/
void RTC_InitTime(UINT32 h, UINT16 m, UINT16 s)
{
    UINT32 t;
    UINT16 day, sec2, t32k;

    day = h / 24;
    sec2 = (h % 24) * 1800 + m * 30 + s / 2;
    t32k = (s & 1) ? (0x8000) : (0);
    t = sec2;
    t = t << 16 | t32k;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1; // 进入安全模式
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R32_RTC_TRIG = day;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_HI;
    R32_RTC_TRIG = t;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
}

/*******************************************************************************
* Function Name  : RTC_GetTime
* Description    : 获取当前时间
* Input          : ph: 获取到的时间 - 小时
                    MAX_H = 393192
                   pm: 获取到的时间 - 分钟
                    MAX_M = 59
                   ps: 获取到的时间 - 秒
                    MAX_S = 59
* Return         : None
*******************************************************************************/
void RTC_GetTime(PUINT32 ph, PUINT16 pm, PUINT16 ps)
{
    UINT32 t;
    UINT16 day, sec2, t32k;

    day = R32_RTC_CNT_DAY & 0x3FFF;
    sec2 = R16_RTC_CNT_2S;
    t32k = R16_RTC_CNT_32K;

    t = sec2 * 2 + ((t32k < 0x8000) ? 0 : 1); //
    *ph = day * 24 + t / 3600;
    *pm = t % 3600 / 60;
    *ps = t % 60;
}

/*******************************************************************************
* Function Name  : RTC_SetCycle32k
* Description    : 基于LSE/LSI时钟，配置当前RTC 周期数
* Input          : cyc: 配置周期计数初值 - cycle
                    MAX_CYC = 0xA8BFFFFF = 2831155199
* Return         : None
*******************************************************************************/
void RTC_SetCycle32k(UINT32 cyc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R32_RTC_TRIG = cyc;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
}

/*******************************************************************************
 * Function Name  : RTC_GetCycle32k
 * Description    : 基于LSE/LSI时钟，获取当前RTC 周期数
 * Input          : None
 * Return         : 返回当前周期数，MAX_CYC = 0xA8BFFFFF = 2831155199
 *******************************************************************************/
UINT32 RTC_GetCycle32k(void)
{
    UINT32 i;

    do
    {
        i = R32_RTC_CNT_32K;
    } while (i != R32_RTC_CNT_32K);

    return (i);
}

/*******************************************************************************
* Function Name  : RTC_TMRFunCfg
* Description    : RTC定时模式配置
* Input          : t:
                    refer to RTC_TMRCycTypeDef
* Return         : None
*******************************************************************************/
void RTC_TMRFunCfg(RTC_TMRCycTypeDef t)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_RTC_MODE_CTRL &= ~(RB_RTC_TMR_EN | RB_RTC_TMR_MODE);
    R8_RTC_MODE_CTRL |= RB_RTC_TMR_EN | (t);
}

/*******************************************************************************
 * Function Name  : RTC_TRIGFunCfg
 * Description    : RTC时间触发模式配置
 * Input          : cyc: 相对当前时间的触发间隔时间，基于LSE/LSI时钟周期数
 * Return         : None
 *******************************************************************************/
void RTC_TRIGFunCfg(UINT32 cyc)
{
    UINT32 t;

    t = RTC_GetCycle32k() + cyc;
    if (t & 0xFFFF)
        t = t + 0x10000;
    if (t >= ((UINT32)MAX_2_SEC << 16))
        t = t - ((UINT32)MAX_2_SEC << 16);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R32_RTC_TRIG = t;
    R8_RTC_MODE_CTRL |= RB_RTC_TRIG_EN;
}

/*******************************************************************************
 * Function Name  : RTC_ModeFunDisable
 * Description    : RTC 模式功能关闭
 * Input          : m: 需要关闭的当前模式
 * Return         : None
 *******************************************************************************/
void RTC_ModeFunDisable(RTC_MODETypeDef m)
{
    UINT8 i = 0;

    if (m & RTC_TRIG_MODE)
        i |= RB_RTC_TRIG_EN;
    if (m & RTC_TMR_MODE)
        i |= RB_RTC_TMR_EN;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_RTC_MODE_CTRL &= ~(i);
}

/*******************************************************************************
* Function Name  : RTC_GetITFlag
* Description    : 获取RTC中断标志
* Input          : f:
                    refer to RTC_EVENTTypeDef
* Return         : 中断标志状态:
                    0     -  	未发生事件
                   (!0)   -  	发生事件
*******************************************************************************/
UINT8 RTC_GetITFlag(RTC_EVENTTypeDef f)
{
    if (f == RTC_TRIG_EVENT)
        return (R8_RTC_FLAG_CTRL & RB_RTC_TRIG_FLAG);
    else
        return (R8_RTC_FLAG_CTRL & RB_RTC_TMR_FLAG);
}

/*******************************************************************************
* Function Name  : RTC_ClearITFlag
* Description    : 清除RTC中断标志
* Input          : f:
                    refer to RTC_EVENTTypeDef
* Return         : None
*******************************************************************************/
void RTC_ClearITFlag(RTC_EVENTTypeDef f)
{
    switch (f)
    {
    case RTC_TRIG_EVENT:
        R8_RTC_FLAG_CTRL = RB_RTC_TRIG_CLR;
        break;
    case RTC_TMR_EVENT:
        R8_RTC_FLAG_CTRL = RB_RTC_TMR_CLR;
        break;
    default:
        break;
    }
}
