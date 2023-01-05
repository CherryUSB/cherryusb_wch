/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_flash.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description
 *******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
 * Function Name  : GetUniqueID
 * Description    : 获取芯片唯一ID，小端模式，6B-ID， 2B-CKS
 * Input          : buf: 存储8字节，前6字节（小端）ID，后2字节（小端）校验和
 * Return         : None
 *******************************************************************************/
void GetUniqueID(PUINT8 buf)
{
    PUINT8 pID;
    UINT8 i;

    pID = (PUINT8)ROM_UUID_ADDR;
    for (i = 0; i < 8; i++)
    {
        *buf++ = *pID++;
    }
}

/*******************************************************************************
 * Function Name  : GetMACAddress
 * Description    : 获取网络MAC，小端模式，6B-MAC
 * Input          : buf: 存储6字节，6字节（小端）物理 MAC
 * Return         : None
 *******************************************************************************/
void GetMACAddress(PUINT8 buf)
{
    PUINT8 pMAC;
    UINT8 i;

    pMAC = (PUINT8)ROM_MAC_ADDR;
    for (i = 0; i < 6; i++)
    {
        *buf++ = *pMAC++;
    }
}

/*******************************************************************************
* Function Name  : CodeFlash_BlockEarse
* Description    : CodeFlash 块擦除，一次擦除512B
* Input          : addr: 32位地址，需要512对齐
* Return         : FAILED  - 错误
                   SUCCESS - 成功
*******************************************************************************/
UINT8 CodeFlash_BlockEarse(UINT32 addr)
{
    UINT16 status = 0;

    if (addr & (0x200 - 1))
        return FAILED;

    R32_FLASH_ADDR = addr;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10 | RB_ROM_DATA_WE | RB_ROM_CODE_WE;
    R8_FLASH_COMMAND = ROM_CMD_ERASE;
    status = R16_FLASH_STATUS;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if (status == RB_ROM_ADDR_OK)
        return SUCCESS;
    else
        return FAILED;
}

/*******************************************************************************
* Function Name  : CodeFlash_WriteDW
* Description    : CodeFlash 双字写，地址需4字节对齐
* Input          : addr: 32位地址，需要4对齐
                    dat: 32位写入数据
* Return         : FAILED  - 错误
                   SUCCESS - 成功
*******************************************************************************/
UINT8 CodeFlash_WriteDW(UINT32 addr, UINT32 dat)
{
    UINT16 status = 0;

    if (addr & (4 - 1))
        return FAILED;

    R32_FLASH_ADDR = addr;
    R32_FLASH_DATA = dat;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10 | RB_ROM_DATA_WE | RB_ROM_CODE_WE;
    R8_FLASH_COMMAND = ROM_CMD_PROG;
    status = R16_FLASH_STATUS;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if (status == RB_ROM_ADDR_OK)
        return SUCCESS;
    else
        return FAILED;
}

/*******************************************************************************
* Function Name  : CodeFlash_WriteBuf
* Description    : CodeFlash 连续多个双字写入
* Input          : addr: 32位地址，需要4对齐
                   pdat: 待写入数据缓存区首地址
                    len: 待写入数据字节长度
* Return         : FAILED  - 错误
                   SUCCESS - 成功
*******************************************************************************/
UINT8 CodeFlash_WriteBuf(UINT32 addr, PUINT32 pdat, UINT16 len)
{
    UINT32 add = addr;
    PUINT32 p32 = pdat;
    UINT16 status = 0, i;

    if (addr & (4 - 1))
        return FAILED;

    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10 | RB_ROM_DATA_WE | RB_ROM_CODE_WE;
    for (i = 0; i < len; i += 4)
    {
        R32_FLASH_ADDR = add;
        R32_FLASH_DATA = *p32++;
        R8_FLASH_COMMAND = ROM_CMD_PROG;
        add += 4;
        status = R16_FLASH_STATUS;
        if (status != RB_ROM_ADDR_OK)
            break;
    }
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if (status == RB_ROM_ADDR_OK)
        return SUCCESS;
    else
        return FAILED;
}

/*******************************************************************************
* Function Name  : DataFlash_BlockEarse
* Description    : DataFlash 块擦除，一次擦除512B
* Input          : addr: 32位地址，需要512对齐
* Return         : FAILED  - 错误
                   SUCCESS - 成功
*******************************************************************************/
UINT8 DataFlash_BlockEarse(UINT32 addr)
{
    if (addr & (0x200 - 1))
        return FAILED;
    if (addr >= DATA_FLASH_SIZE)
        return FAILED;

    return (CodeFlash_BlockEarse(DATA_FLASH_ADDR + addr));
}

/*******************************************************************************
* Function Name  : DataFlash_WriteDW
* Description    : DataFlash 双字写，地址需4字节对齐
* Input          : addr: 32位地址，需要4对齐
                    dat: 32位写入数据
* Return         : FAILED  - 错误
                   SUCCESS - 成功
*******************************************************************************/
UINT8 DataFlash_WriteDW(UINT32 addr, UINT32 dat)
{

    if (addr & (4 - 1))
        return FAILED;
    if (addr >= DATA_FLASH_SIZE)
        return FAILED;

    return (CodeFlash_WriteDW(DATA_FLASH_ADDR + addr, dat));
}
