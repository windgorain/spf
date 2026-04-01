/*================================================================
*   Created by LiXingang
*   Version: 1.0  Date: 2007-5-13
*   Description: 
*
================================================================*/

#ifndef __ETH_UTL_H_
#define __ETH_UTL_H_

#include "utl/net.h"
#include "utl/data2hex_utl.h"
#include "utl/eth_def.h"

#ifdef __cplusplus
    extern "C" {
#endif 

typedef struct {
    USHORT usHeadLen;
    UCHAR ucPktFmt;
    UCHAR ucReserved;
    USHORT usType;          
    USHORT usPktLenOrType;  
    USHORT usVlanId;        
}ETH_PKT_INFO_S;


BS_STATUS ETH_GetEthHeadInfo(IN UCHAR *pucData, IN UINT uiDataLen, OUT ETH_PKT_INFO_S *pstHeadInfo);
VOID ETH_Mac2String(IN UCHAR *pucMac, IN CHAR cSplit, OUT CHAR szMacString[ETH_MAC_ADDR_STRING_LEN + 1]);
BS_STATUS ETH_String2Mac(IN CHAR *pcMacString, OUT UCHAR *pucMac);

static inline int ETH_GetEthSrcMacString(IN UCHAR *pucData, IN UINT uiDataLen, char* buf) 
{
    if (uiDataLen < sizeof(ETH_HEADER_S)) return BS_ERR;

    ETH_HEADER_S *pstHeader = (ETH_HEADER_S*)pucData;

    ETH_Mac2String((UCHAR*)(pstHeader->stSMac.aucMac), ':', buf);

    return BS_OK;
}

static inline void ETH_SetMacAddr(OUT U8 *mac, U8 m0, U8 m1, U8 m2, U8 m3, U8 m4, U8 m5)
{
    mac[0] = m0;
    mac[1] = m1;
    mac[2] = m2;
    mac[3] = m3;
    mac[4] = m4;
    mac[5] = m5;
}

static inline void ETH_ClearMacAddr(OUT U8 *mac)
{
    mac[0] = 0;
    mac[1] = 0;
    mac[2] = 0;
    mac[3] = 0;
    mac[4] = 0;
    mac[5] = 0;
}

#ifdef __cplusplus
    }
#endif 

#endif 



