/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0  Date: 2012-8-1
* Description: 
* History:     
******************************************************************************/
#include "bs.h"

#include "utl/time_utl.h"
#include "utl/rand_utl.h"

#ifdef HAVE_ARC4RANDOM

static void _rand_init(void)
{
    
}


static U32 _rand_num(void)
{
    return arc4random();
}


static U32 _rand_uniform(U32 max)
{
    return arc4random_uniform(max);
}


static void _rand_buf(void *buf, U32 nbytes)
{
    arc4random_buf(buf, nbytes);
}

#elif defined(IN_WINDOWS)

static BCRYPT_ALG_HANDLE g_rand_winds_rng = NULL;

static void _rand_init(void)
{
    if (g_rand_winds_rng) {
        return;
    }

    BCryptOpenAlgorithmProvider(&g_rand_winds_rng, BCRYPT_RNG_ALGORITHM, NULL, 0);
}

static U32 _rand_num()
{
    U32 result;
    BCryptGenRandom(g_rand_winds_rng, (PUCHAR)&result, sizeof(result), 0);
    return result;
}


static U32 _rand_uniform(U32 max)
{
    if (max <= 1) return 0;
    
    
    U32 limit = (UINT32_MAX / max) * max;
    U32 r;
    
    do {
        r = _rand_num();
    } while (r >= limit);  
    
    return r % max;
}


static void _rand_buf(void *buf, U32 nbytes)
{
    BCryptGenRandom(g_rand_winds_rng, buf, nbytes, 0);
}

#else 

static void _rand_init(void)
{
    srand(time(NULL));
}

static U32 _rand_num()
{
    U32 r1 = rand();
    U32 r2 = rand();

    
    return (r1 & 0xffff) | (r2 << 16);
}

static U32 _rand_uniform(U32 max)
{
    if (max <= 1) return 0;
    
    
    U32 limit = (UINT32_MAX / max) * max;
    U32 r;
    
    do {
        r = _rand_num();
    } while (r >= limit);  
    
    return r % max;
}

static void _rand_buf(void *buf, U32 nbytes)
{
    U8 *b = buf;

    for (int i=0; i<nbytes; i++) {
        b[i] = rand();
    }
}

#endif


U32 RAND_Get(void)
{
    return _rand_num();
}


U32 RAND_Uniform(U32 upper)
{
    return _rand_uniform(upper);
}


U32 RAND_RangeGet(U32 min, U32 max)
{
    U32 range = (max - min) + 1;
    U32 r = _rand_uniform(range);
    return min + r;
}


void RAND_Mem(OUT void *buf, U32 len)
{
    _rand_buf(buf, len);
}


U32 RAND_GetNonZero(void)
{
    U32 r;
    do { r = RAND_Get(); }while (r == 0);
    return r;
}


U16 RAND_GetNonZero16(void)
{
    U16 num;
    do { num = RAND_Get(); }while (num == 0);
    return num;
}

CONSTRUCTOR(init) {
    _rand_init();
}

