/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_XDP_DEF_H_
#define _MYBPF_XDP_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XDP_FLAGS_SKB_MODE
#define XDP_FLAGS_UPDATE_IF_NOEXIST	(1U << 0)
#define XDP_FLAGS_SKB_MODE		(1U << 1)
#define XDP_FLAGS_DRV_MODE		(1U << 2)
#define XDP_FLAGS_HW_MODE		(1U << 3)
#define XDP_FLAGS_REPLACE		(1U << 4)
#define XDP_FLAGS_MODES			(XDP_FLAGS_SKB_MODE | XDP_FLAGS_DRV_MODE | XDP_FLAGS_HW_MODE)
#endif


typedef struct xdp_buff {
	void *data;     
	void *data_end; 
	void *data_meta;
	
    
	unsigned int ingress_ifindex; 
	unsigned int rx_queue_index;  
}MYBPF_XDP_BUFF_S;

#ifdef __cplusplus
}
#endif
#endif 
