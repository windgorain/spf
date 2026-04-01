/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_XDP_RET_H_
#define _MYBPF_XDP_RET_H_

#ifdef __cplusplus
extern "C" {
#endif


enum {
	MYBPF_XDP_ABORTED = 0,
	MYBPF_XDP_DROP,
	MYBPF_XDP_PASS,
	MYBPF_XDP_TX,       
	MYBPF_XDP_REDIRECT, 
};

#ifdef __cplusplus
}
#endif
#endif 
