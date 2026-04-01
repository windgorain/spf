/*================================================================
*   Created by LiXingang
*   Description: 
*
================================================================*/
#ifndef _MPLS_UTL_H
#define _MPLS_UTL_H
#include "utl/endian_utl.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define MPLS_LABEL(_hdr) ((_hdr)->flag >> 12)
#define MPLS_EXP(_hdr) (((_hdr)->flag >> 9) & 0x7)
#define MPLS_BOTTOM(_hdr) (((_hdr)->flag >> 8) & 0x1)
#define MPLS_TTL(_hdr) ((_hdr)->flag & 0xff)

#define MPLS_SET_LABEL(_hdr, _label) ((_hdr)->flag |= (_label << 12))
#define MPLS_SET_EXP(_hdr, _exp) ((_hdr)->flag | (((_exp) & 0x7) << 9))
#define MPLS_SET_BOTTOM(_hdr, _bottom) ((_hdr)->flag | (((_bottom) & 0x1) << 8))
#define MPLS_SET_TTL(_hdr, _ttl) ((_hdr)->flag | ((_ttl) & 0xff))

typedef struct {
    U32 flag;
}MPLS_HEAD_S;

#ifdef __cplusplus
}
#endif
#endif 
