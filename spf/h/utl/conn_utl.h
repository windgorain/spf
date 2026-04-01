/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2014-8-1
* Description: 
* History:     
******************************************************************************/

#ifndef __CONN_UTL_H_
#define __CONN_UTL_H_

#include "utl/mypoll_utl.h"

#ifdef __cplusplus
    extern "C" {
#endif 

typedef struct tagCONN_S CONN_S;
typedef CONN_S * CONN_HANDLE;

enum {
    CONN_TYPE_NONE = 0,
    CONN_TYPE_TCP,
    CONN_TYPE_SSL,
    CONN_TYPE_KCP,
};

typedef enum {
    CONN_USER_DATA_INDEX_0 = 0,
    CONN_USER_DATA_INDEX_1,

    CONN_USER_DATA_INDEX_MAX
}CONN_USER_DATA_INDEX_E;


typedef int (*PF_CONN_EVENT_NOTIFY)(CONN_S *conn, U32 event, USER_HANDLE_S *ud);

typedef struct tagCONN_S {
    U8 conn_type;   
    int fd;
    void *handle;  
    MYPOLL_HANDLE hPollHandle;

    PF_CONN_EVENT_NOTIFY event_notify;
    USER_HANDLE_S event_ud;
    HANDLE ahUserData[CONN_USER_DATA_INDEX_MAX];
}CONN_S;

void CONN_Init(OUT CONN_S *conn, U8 conn_type);
void CONN_Fini(CONN_S *conn);

CONN_S * CONN_New(U8 conn_type);
VOID CONN_Free(IN CONN_S * hConn);

void CONN_SetFD(CONN_S *conn, int fd);
void CONN_SetType(CONN_S *conn, U8 conn_type);
void CONN_SetHandle(CONN_S *conn, void *handle);
void * CONN_GetHandle(CONN_S *conn);
VOID CONN_SetPoller(IN CONN_S * hConn, IN MYPOLL_HANDLE hPollHandle);
MYPOLL_HANDLE CONN_GetPoller(IN CONN_S * hConn);
VOID CONN_SetUserData(IN CONN_S * hConn, IN CONN_USER_DATA_INDEX_E eIndex, IN HANDLE hUserData);
HANDLE CONN_GetUserData(IN CONN_S * hConn, IN CONN_USER_DATA_INDEX_E eIndex);
INT CONN_GetFD(IN CONN_S * hConn);

BS_STATUS CONN_SetEvent(CONN_S * hConn, UINT uiEvent, PF_CONN_EVENT_NOTIFY pfFunc, USER_HANDLE_S *ud);

void CONN_UnsetEvent(CONN_S * hConn);

BS_STATUS CONN_AddEvent(IN CONN_S * hConn, IN UINT uiEvent);

BS_STATUS CONN_DelEvent(IN CONN_S * hConn, IN UINT uiEvent);

BS_STATUS CONN_ClearEvent(IN CONN_S * hConn);

BS_STATUS CONN_ModifyEvent(IN CONN_S * hConn, IN UINT uiEvent);

int CONN_SetTimtoutTime(CONN_S * conn, U32 seconds );

int CONN_SetEventResetTime(CONN_S * conn, BOOL_T enable);


INT CONN_Read(IN CONN_S * hConn, OUT UCHAR *pucBuf, IN UINT uiBufLen);


INT CONN_Write(IN CONN_S * hConn, IN VOID *pBuf, IN UINT uiLen);


INT CONN_WriteAll(IN CONN_S * hConn, IN UCHAR *pucBuf, IN UINT uiLen);

INT CONN_WriteString(IN CONN_S * hConn, IN CHAR *pcString);

INT CONN_SslPending(IN CONN_S * hConn);

#ifdef __cplusplus
    }
#endif 

#endif 


