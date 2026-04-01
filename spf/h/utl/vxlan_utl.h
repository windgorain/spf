/*================================================================
*   Created by LiXingang
*   Description: 
*
================================================================*/
#ifndef _VXLAN_UTL_H
#define _VXLAN_UTL_H

#include "utl/net.h"
#include "utl/eth_utl.h"
#include "utl/ip_utl.h"
#include "utl/udp_utl.h"
#include "utl/vxlan_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

BOOL_T VXLAN_Valid(IN VXLAN_HEAD_S *vxlan_header);
VXLAN_HEAD_S * VXLAN_GetVxlanHeader(IN void *pkt_buf, IN int buf_len, IN NET_PKT_TYPE_E pkt_type);
int VXLAN_GetInnerPktType(IN VXLAN_HEAD_S *vxlan_header, int is_ip_vxlan);
char * VXLAN_Header2String(VXLAN_HEAD_S *vxlan_header, OUT CHAR *info, UINT infosize);
void * VXLAN_GetInnerIPPkt(VXLAN_HEAD_S *vxlan_header, int buf_len, int is_ip_vxlan);
int VXLAN_GetPktInfo(IP_HEAD_S *ip, int buf_len, OUT VXLAN_PKT_INFO_S *info);
void VXLAN_BuildHdr(U32 vni, OUT VXLAN_HEAD_S *vxlan_hdr);

#ifdef __cplusplus
}
#endif
#endif 
