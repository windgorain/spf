/******************************************************************************
* Copyright (C), LiXingang
* Author:      LiXingang  Version: 1.0  Date: 2011-3-24
* Description: 
* History:     
******************************************************************************/

#ifndef __MYPOLL_UTL_H_
#define __MYPOLL_UTL_H_

#include "utl/rcu_utl.h"

#ifdef __cplusplus
    extern "C" {
#endif 

typedef struct tag_MYPOLL_CTRL_S *MYPOLL_HANDLE;


#ifdef IN_LINUX
#include <sys/epoll.h>
#define MYPOLL_EVENT_IN  EPOLLIN
#define MYPOLL_EVENT_OUT EPOLLOUT
#define MYPOLL_EVENT_ERR EPOLLERR
#define MYPOLL_EVENT_HUP EPOLLHUP
#else
#define MYPOLL_EVENT_IN  0x1
#define MYPOLL_EVENT_OUT 0x2
#define MYPOLL_EVENT_ERR 0x4
#define MYPOLL_EVENT_HUP 0x10
#endif

#define MYPOLL_EVENT_AGED   0x80000000 

#define MYPOLL_EVENT_ALL (MYPOLL_EVENT_IN | MYPOLL_EVENT_OUT | MYPOLL_EVENT_ERR)
#define MYPOLL_EVENT_ERRHUP (MYPOLL_EVENT_HUP | MYPOLL_EVENT_ERR)  
#define MYPOLL_EVENT_CLOSE (MYPOLL_EVENT_HUP | MYPOLL_EVENT_ERR | MYPOLL_EVENT_AGED)  


typedef int (*PF_MYPOLL_EV_NOTIFY)(MYPOLL_HANDLE mypoller, int fd, UINT uiEvent, USER_HANDLE_S *uh);
typedef int (*PF_MYPOLL_USER_EVENT_FUNC)(MYPOLL_HANDLE hMyPoll, UINT uiEvent, USER_HANDLE_S *uh);
typedef int (*PF_MYPOLL_SIGNAL_FUNC)(int signum);
typedef void (*PF_MYPOLL_TIMEOUT_FUNC)(MYPOLL_HANDLE mypoller, void *ud);

MYPOLL_HANDLE MyPoll_Create(void);
VOID MyPoll_Destory(MYPOLL_HANDLE hMypoll);
void MyPoll_SetRcu(MYPOLL_HANDLE mypoller, RCU_S *rcu);
int MyPoll_EnableTimer(MYPOLL_HANDLE mypoller, int ms );
void MyPoll_DisableTimer(MYPOLL_HANDLE mypoller);
int MyPoll_NotifyCloseFd(MYPOLL_HANDLE mypoller, int fd);
BS_STATUS MyPoll_SetEvent(MYPOLL_HANDLE hMypoll, int fd, UINT uiEvent, PF_MYPOLL_EV_NOTIFY pfNotifyFunc, USER_HANDLE_S *uh );
void * MyPoll_GetEvNotifyFunc(MYPOLL_HANDLE hMypoll, int fd);
BS_STATUS MyPoll_AddEvent(MYPOLL_HANDLE hMypoll, int fd, UINT uiEvent);
BS_STATUS MyPoll_DelEvent(MYPOLL_HANDLE hMypoll, int fd, UINT uiEvent);
BS_STATUS MyPoll_ClearEvent(MYPOLL_HANDLE hMypoll, int fd);
BS_STATUS MyPoll_ModifyEvent(MYPOLL_HANDLE hMypoll, int fd, UINT uiEvent);
int MyPoll_SetTimeoutTime(MYPOLL_HANDLE mypoller, int fd, U32 seconds);
int MyPoll_SetEventResetTime(MYPOLL_HANDLE mypoller, int fd, BOOL_T enable);
BS_STATUS MyPoll_ModifyUserHandle(MYPOLL_HANDLE hMypoll, int fd, USER_HANDLE_S *uh);
USER_HANDLE_S * MyPoll_GetUserHandle(MYPOLL_HANDLE hMypoll, int fd);
void MyPoll_Del(MYPOLL_HANDLE hMypoll, int fd);
int MyPoll_AddTimeoutProcesser(MYPOLL_HANDLE hMypoll, PF_MYPOLL_TIMEOUT_FUNC func, void *ud);
void MyPoll_DelTimeoutProcesser(MYPOLL_HANDLE hMypoll, PF_MYPOLL_TIMEOUT_FUNC func);
BS_STATUS MyPoll_SetSignalProcessor(MYPOLL_HANDLE hMypoll, int signo, PF_MYPOLL_SIGNAL_FUNC pfFunc);
BS_STATUS MyPoll_SetUserEventProcessor(MYPOLL_HANDLE hMypoll, PF_MYPOLL_USER_EVENT_FUNC pfFunc, USER_HANDLE_S *uh);
BS_STATUS MyPoll_PostUserEvent(MYPOLL_HANDLE hMypoll, UINT uiEvent);
BS_STATUS MyPoll_Trigger(MYPOLL_HANDLE hMyPoll);
int MyPoll_Run(MYPOLL_HANDLE hMypoll);
void MyPoll_Restart(MYPOLL_HANDLE hMypoll);

#ifdef __cplusplus
    }
#endif 

#endif 


