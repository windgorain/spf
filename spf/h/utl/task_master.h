/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2012-8-19
* Description: 
* History:     
******************************************************************************/

#ifndef __TASK_MASTER_H_
#define __TASK_MASTER_H_

#include "utl/vclock_utl.h"

#ifdef __cplusplus
    extern "C" {
#endif 

typedef struct tag_TASK_MASTER_S * TASK_MASTER_HANDLE;

typedef void (*PF_TASK_MASTER_FUNC)(void *ud);

TASK_MASTER_HANDLE TASK_Master_Create(char *name, IN UINT uiTime);

BS_STATUS TASK_Master_SetEvent(TASK_MASTER_HANDLE hTaskMaster, UINT uiEventOffset, 
    IN PF_TASK_MASTER_FUNC pfFunc, IN USER_HANDLE_S *pstUserHandle);

BS_STATUS TASK_Master_EventInput(TASK_MASTER_HANDLE hTaskMaster, UINT uiEventOffset );

BS_STATUS TASK_Master_MsgInput(TASK_MASTER_HANDLE hTaskMaster, PF_TASK_MASTER_FUNC pfFunc, IN void *ud);

VCLOCK_HANDLE TASK_Master_AddTimer(TASK_MASTER_HANDLE hTaskMaster, UINT uiTime,    
    UINT flag, PF_TIME_OUT_FUNC pfFunc, USER_HANDLE_S *pstUserHandle);

VOID TASK_Master_DelTimer(IN TASK_MASTER_HANDLE hTaskMaster, IN VCLOCK_HANDLE hTimerHandle);

VOID TASK_Master_RefreshTimer(IN TASK_MASTER_HANDLE hTaskMaster, IN VCLOCK_HANDLE hTimerHandle);

#ifdef __cplusplus
    }
#endif 

#endif 


