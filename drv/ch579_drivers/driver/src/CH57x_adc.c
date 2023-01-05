/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_adc.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description
 *******************************************************************************/

#include "CH57x_common.h"

signed short RoughCalib_Value = 0;
const signed short PGA_1_4_OFFECT[] = {
    54, 53, 51, 49, 47, 46, 44, 42, 41,
    39, 37, 35, 34, 32, 30, 28, 27, 25, 23, 22, 20,
    18, 16, 15, 13, 11, 9, 8, 6, 4, 2, 1,
    -1, -3, -4, -6, -8, -10, -11, -13, -15, -17, -18,
    -20, -22, -23, -25, -27, -29, -30, -32, -34, -36, -37, -39,
    -41, -42, -44, -46, -48, -49, -51, -53, -55, -56};

const signed short PGA_1_2_OFFECT[] = {
    54, 53, 51, 49, 48, 46, 44, 43, 41,
    39, 38, 36, 34, 33, 31, 29, 28, 26, 24, 23, 21,
    19, 18, 16, 15, 13, 11, 10, 8, 6, 5, 3, 1, 0,
    -2, -4, -5, -7, -9, -10, -12, -14, -15, -17, -19,
    -20, -22, -24, -25, -27, -29, -30, -32, -34, -35, -37, -39,
    -40, -42, -44, -45, -47, -49, -50, -52};

const signed short PGA_0_OFFECT[] = {
    53, 51, 50, 48, 46, 45, 43, 42, 40,
    38, 37, 35, 34, 32, 30, 29, 27, 26, 24, 22, 21,
    19, 18, 16, 14, 13, 11, 10, 8, 6, 5, 3, 2, 0,
    -2, -3, -5, -6, -8, -10, -11, -13, -14, -16, -18, -19,
    -21, -22, -24, -26, -27, -29, -30, -32, -34, -35, -37, -38,
    -40, -42, -43, -45, -46, -48, -50};

const signed short PGA_2_OFFECT[] = {
    51, 49, 48, 46, 45, 43, 41, 40, 38, 37, 35, 33, 32, 30,
    29, 27, 25, 24, 22, 21, 19, 17, 16, 14, 13, 11,
    9, 8, 6, 5, 3, 1, 0,
    -2, -3, -5, -7, -8, -10, -11, -13, -15, -16, -18, -19,
    -21, -23, -24, -26, -27, -29, -31, -32, -34, -35, -37, -39,
    -40, -42, -43, -45, -47, -48, -50, -51, -53};

/*******************************************************************************
 * Function Name  : ADC_DataCalib_Rough
 * Description    : 采样数据粗调,获取偏差值
 *                  注意，使用粗调校准，必须保证 PA5(AIN1)设置为浮空输入模式，管脚外部不要有电压
 * Input          : None
 * Return         : 偏差值
 *******************************************************************************/
void ADC_DataCalib_Rough(void) // 采样数据粗调,获取偏差值
{
    UINT16 i;
    UINT32 sum = 0;

    ADC_ChannelCfg(1);
    R8_ADC_CFG |= RB_ADC_OFS_TEST; // 进入测试模式
    R8_ADC_CONVERT = RB_ADC_START;
    while (R8_ADC_CONVERT & RB_ADC_START)
        ;
    for (i = 0; i < 16; i++)
    {
        R8_ADC_CONVERT = RB_ADC_START;
        while (R8_ADC_CONVERT & RB_ADC_START)
            ;
        sum += (~R16_ADC_DATA) & RB_ADC_DATA;
    }
    sum = (sum + 8) >> 4;
    R8_ADC_CFG &= ~RB_ADC_OFS_TEST; // 关闭测试模式

    RoughCalib_Value = (2048 - sum);
}

void ADC_DataCalib_Fine(PUINT16 dat, ADC_SignalPGATypeDef ga) // 采样数据细调
{
    UINT16 d = *dat;

    switch (ga)
    {
    case ADC_PGA_1_4: // y=0.973x+55.188  y = x + k(x)   k(x) = 55.188-0.027x
        *dat = d + PGA_1_4_OFFECT[d >> 6];
        break;

    case ADC_PGA_1_2: // y=0.974x+55.26  y = x + k(x)   k(x) = 55.26-0.026x
        *dat = d + PGA_1_2_OFFECT[d >> 6];
        break;

    case ADC_PGA_0: // y=0.975x+53.63  y = x + k(x)   k(x) = 53.63-0.025x
        *dat = d + PGA_0_OFFECT[d >> 6];
        break;

    case ADC_PGA_2: // y=0.975x+51.58  y = x + k(x)   k(x) = 51.58-0.025x
        *dat = d + PGA_2_OFFECT[d >> 6];
        break;
    }
}

/*******************************************************************************
* Function Name  : ADC_ExtSingleChSampInit
* Description    : 外部信号单通道采样初始化
* Input          : sp:
                    refer to ADC_SampClkTypeDef
                   ga:
                    refer to ADC_SignalPGATypeDef
* Return         : None
*******************************************************************************/
void ADC_ExtSingleChSampInit(ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga)
{
    R8_ADC_CFG = RB_ADC_POWER_ON | RB_ADC_BUF_EN | (sp << 6) | (ga << 4);
}

/*******************************************************************************
* Function Name  : ADC_ExtDiffChSampInit
* Description    : 外部信号差分通道采样初始化
* Input          : sp:
                    refer to ADC_SampClkTypeDef
                   ga:
                    refer to ADC_SignalPGATypeDef
* Return         : None
*******************************************************************************/
void ADC_ExtDiffChSampInit(ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga)
{
    R8_ADC_CFG = RB_ADC_POWER_ON | RB_ADC_DIFF_EN | (sp << 6) | (ga << 4);
}

/*******************************************************************************
 * Function Name  : ADC_InterTSSampInit
 * Description    : 内置温度传感器采样初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void ADC_InterTSSampInit(void)
{
    R8_TEM_SENSOR |= RB_TEM_SEN_PWR_ON;
    R8_ADC_CHANNEL = CH_INTE_VTEMP;
    R8_ADC_CFG = RB_ADC_POWER_ON | (2 << 4);
}

/*******************************************************************************
 * Function Name  : ADC_InterBATSampInit
 * Description    : 内置电池电压采样初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void ADC_InterBATSampInit(void)
{
    R8_ADC_CHANNEL = CH_INTE_VBAT;
    R8_ADC_CFG = RB_ADC_POWER_ON | RB_ADC_BUF_EN | (2 << 4);
}

/*******************************************************************************
 * Function Name  : TouchKey_ChSampInit
 * Description    : 触摸按键通道采样初始化
 * Input          : None
 * Return         : None
 *******************************************************************************/
void TouchKey_ChSampInit(void)
{
    R8_ADC_CFG = RB_ADC_POWER_ON | RB_ADC_BUF_EN | (2 << 4);
    R8_TKEY_CTRL = RB_TKEY_PWR_ON;
}

/*******************************************************************************
 * Function Name  : ADC_ExcutSingleConver
 * Description    : ADC执行单次转换
 * Input          : None
 * Return         : ADC转换后的数据
 *******************************************************************************/
UINT16 ADC_ExcutSingleConver(void)
{
    R8_ADC_CONVERT = RB_ADC_START;
    while (R8_ADC_CONVERT & RB_ADC_START)
        ;

    return (R16_ADC_DATA & RB_ADC_DATA);
}

/*******************************************************************************
 * Function Name  : TouchKey_ExcutSingleConver
 * Description    : TouchKey转换后数据
 * Input          : d:  Touchkey充放电时间，高4bit-放电时间，整个8bit-充电时间
 * Return         : 当前TouchKey等效数据
 *******************************************************************************/
UINT16 TouchKey_ExcutSingleConver(UINT8 d)
{
    R8_TKEY_CTRL = RB_TKEY_PWR_ON;
    R8_TKEY_CNT = d;
    while (R8_TKEY_CTRL & RB_TKEY_ACTION)
        ;

    return (R16_ADC_DATA & RB_ADC_DATA);
}

/*******************************************************************************
 * Function Name  : ADC_GetCurrentTS
 * Description    : 获取当前采样的温度值（℃）
 * Input          : ts_v：当前温度传感器采样输出
 * Return         : 转换后的温度值（℃）
 *******************************************************************************/
UINT8 ADC_GetCurrentTS(UINT16 ts_v)
{
    UINT16 vol_ts;
    UINT16 D85_tem, D85_vol, D25;

    vol_ts = (ts_v * 1060) >> 11;
    D85_tem = (UINT16)((*((PUINT32)ROM_TMP_85C_ADDR) >> 16) & 0x00ff);
    D85_vol = *((PUINT16)ROM_TMP_85C_ADDR);
    D25 = *((PUINT32)ROM_TMP_25C_ADDR);

    return (D85_tem - (D85_vol - vol_ts + 8) * 16 / D25);
}
