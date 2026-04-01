/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2009-4-3
* Description: 
* History:     
******************************************************************************/

#ifndef __RAND_UTL_H_
#define __RAND_UTL_H_

U32 RAND_Get(void);

U32 RAND_Uniform(U32 upper);

U32 RAND_RangeGet(U32 min, U32 max);

U32 RAND_GetNonZero(void);

U16 RAND_GetNonZero16(void);

void RAND_Mem(OUT void *buf, U32 len);


static inline UINT RAND_FastGet(U32 *seedp)
{
    *seedp = (*seedp) * 1103515245 + 12345;
    return *seedp;
}

static inline U64 RAND_FastGet64(U64 *seedp)
{
    *seedp = (*seedp) * 2862933555777941757ULL + 1;
    return *seedp;
}

#endif 


