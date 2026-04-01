/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2014-11-16
* Description: node id pool
* History:     
******************************************************************************/

#ifndef __NAP_UTL_H_
#define __NAP_UTL_H_

#include "utl/rcu_utl.h"

#ifdef __cplusplus
    extern "C" {
#endif 

#define NAP_INVALID_ID    0 
#define NAP_INVALID_INDEX ((UINT)(INT)-1)

enum {
    NAP_EV_FREE = 0,
    NAP_EV_RCUFREE
};

typedef void* NAP_HANDLE;

typedef void (*PF_NAP_EV_NOTIFY)(NAP_HANDLE hNAPHandle, void *node, U32 event);

typedef struct {
    void *memcap;    
    UINT uiMaxNum;   
    UINT uiNodeSize;
}NAP_PARAM_S;

NAP_HANDLE NAP_ArrayCreate(NAP_PARAM_S *p);
NAP_HANDLE NAP_PtrArrayCreate(NAP_PARAM_S *p);
NAP_HANDLE NAP_HashCreate(NAP_PARAM_S *p);
NAP_HANDLE NAP_AvlCreate(NAP_PARAM_S *p);

VOID NAP_SetRcu(NAP_HANDLE hNAPHandle, RCU_S *rcu);
VOID NAP_SetEvNotify(NAP_HANDLE hNAPHandle, PF_NAP_EV_NOTIFY notify_func);

BS_STATUS NAP_EnableSeq(HANDLE hNAPHandle, U64 seq_mask, UINT uiSeqCount);
UINT NAP_GetNodeSize(IN NAP_HANDLE hNapHandle);
void NAP_AutoIndexRange(NAP_HANDLE nap, U32 min, U32 max);

VOID * NAP_Alloc(IN NAP_HANDLE hNapHandle);
VOID * NAP_ZAlloc(IN NAP_HANDLE hNapHandle);

VOID * NAP_AllocByIndex(NAP_HANDLE hNapHandle, UINT uiSpecIndex);
VOID * NAP_ZAllocByIndex(IN NAP_HANDLE hNapHandle, IN UINT uiSpecIndex);
VOID * NAP_AllocByID(NAP_HANDLE hNapHandle, U64 spec_id);
VOID * NAP_ZAllocByID(NAP_HANDLE hNapHandle, U64 spec_id);
VOID NAP_Free(IN NAP_HANDLE hNapHandle, IN VOID *pstNode);
VOID NAP_FreeByID(NAP_HANDLE hNapHandle, U64 id);
VOID NAP_FreeByIndex(IN NAP_HANDLE hNapHandle, IN UINT index);
VOID NAP_FreeAll(IN NAP_HANDLE hNapHandle);
void NAP_FreeRcu(IN NAP_HANDLE hNapHandle, IN VOID *pstNode);
VOID * NAP_GetNodeByID(NAP_HANDLE hNAPHandle, U64 id);
VOID * NAP_GetNodeByIndex(IN NAP_HANDLE hNAPHandle, IN UINT uiIndex);
U64 NAP_GetIDByNode(IN NAP_HANDLE hNAPHandle, IN VOID *pstNode);
U64 NAP_GetIDByIndex(IN NAP_HANDLE hNAPHandle, UINT index);
UINT NAP_GetIndexByID(IN NAP_HANDLE hNAPHandle, U64 id);
UINT NAP_GetIndexByNode(IN NAP_HANDLE hNAPHandle, void *node);
VOID NAP_Destory(IN NAP_HANDLE hNAPHandle);
void * NAP_GetMemCap(NAP_HANDLE hNAPHandle);

UINT NAP_GetNextIndex(IN NAP_HANDLE hNAPHandle, IN UINT uiCurrentIndex);
U64 NAP_GetNextID(IN NAP_HANDLE hNAPHandle, U64 curr_id);
UINT NAP_GetCount(IN NAP_HANDLE hNAPHandle);

#ifdef __cplusplus
    }
#endif 

#endif 


