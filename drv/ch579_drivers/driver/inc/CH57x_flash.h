

#ifndef __CH57x_FLASH_H__
#define __CH57x_FLASH_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

#define ROM_UUID_ADDR 0x40608 // chip UID address ( ID-48bit + CKS-16bit )
#define ROM_MAC_ADDR 0x40608  // NET MAC address 48bit

    // 获取唯一ID
    void GetUniqueID(PUINT8 buf); /* 获取芯片唯一ID，小端模式，6B-ID， 2B-CKS */

    // 获取网络MAC
    void GetMACAddress(PUINT8 buf); /* 获取网络MAC，小端模式，6B-MAC */

    // CodeFlash 操作
    UINT8 CodeFlash_BlockEarse(UINT32 addr);                         /* CodeFlash 块擦除，一次擦除512B */
    UINT8 CodeFlash_WriteDW(UINT32 addr, UINT32 dat);                /* CodeFlash 32bit写，地址需4字节对齐 */
    UINT8 CodeFlash_WriteBuf(UINT32 addr, PUINT32 pdat, UINT16 len); /* CodeFlash 连续多个32bit写，地址需4字节对齐 */

    // DataFlash 操作
    UINT8 DataFlash_BlockEarse(UINT32 addr);          /* DataFlash 块擦除，一次擦除512B */
    UINT8 DataFlash_WriteDW(UINT32 addr, UINT32 dat); /* DataFlash 32bit写，地址需4字节对齐 */

#ifdef __cplusplus
}
#endif

#endif // __CH57x_FLASH_H__
