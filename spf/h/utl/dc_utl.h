/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2008-11-25
* Description: 
* History:     
******************************************************************************/

#ifndef __DC_UTL_H_
#define __DC_UTL_H_

#include "utl/mkv_utl.h"

#ifdef __cplusplus
    extern "C" {
#endif 

#define DC_X_DATA_MAX_NUM 32

typedef struct {
	CHAR *pcKey;
	CHAR *pcValue;
}KEY_VALUE_S;

typedef struct {
	UINT uiNum;
	KEY_VALUE_S astKeyValue[DC_X_DATA_MAX_NUM];
}DC_DATA_S;

typedef enum {
    DC_TYPE_XML,
    DC_TYPE_MYSQL,

    DC_TYPE_MAX
}DC_TYPE_E;

typedef struct {
    CHAR *pcHost;
    CHAR *pcUserName;
    CHAR *pcPassWord;
    CHAR *pcDbName;
    USHORT usPort;      
}DC_MYSQL_PARAM_S;

typedef int (*PF_DC_WALK_TBL_CB_FUNC)(IN CHAR *pszTblName, IN HANDLE hUserHandle);
typedef int (*PF_DC_WALK_OBJECT_CB_FUNC)(IN DC_DATA_S *pstKey, IN HANDLE hUserHandle);

HANDLE DC_CreateXML(char *filename);
HANDLE DC_CreateMysql(DC_MYSQL_PARAM_S *param);

VOID      DC_CloseInstance(IN HANDLE hDcHandle);

int DC_AddTbl(HANDLE hDcHandle, CHAR *pcTableName);
VOID DC_DelTbl(IN HANDLE hDcHandle, IN CHAR *pcTableName);
UINT DC_GetObjectNum(IN HANDLE hDcHandle, IN CHAR *pcTableName);
int DC_AddObject(HANDLE hDcHandle, char *pcTableName, DC_DATA_S *pstKey);
BOOL_T DC_IsObjectExist(IN HANDLE hDcHandle, IN CHAR *pcTableName, IN DC_DATA_S *pstKey);
VOID DC_DelObject(IN HANDLE hDcHandle, IN CHAR *pcTableName, IN DC_DATA_S *pstKey);
int DC_SetFieldValueAsUint(HANDLE hDcHandle, char *pcTableName, DC_DATA_S *pstKey, char *pcFieldName, U32 uiValue);
int DC_SetFieldValueAsString(HANDLE hDcHandle, char *pcTableName, DC_DATA_S *pstKey, char *pcFieldName, char *pcValue);
int DC_GetFieldValueAsUint(HANDLE hDcHandle, char *pcTableName, DC_DATA_S *pstKey, char *pcFieldName, OUT U32 *puiValue);
int DC_CpyFieldValueAsString(HANDLE hDcHandle, char *pcTableName, DC_DATA_S *pstKey, char *pcFieldName, OUT char *pcValue, int value_size);
VOID DC_WalkTable(IN HANDLE hDcHandle, IN PF_DC_WALK_TBL_CB_FUNC pfWalkFunc, IN HANDLE hUserHandle);
VOID DC_WalkObject(IN HANDLE hDcHandle, IN CHAR *pcTableName, IN PF_DC_WALK_OBJECT_CB_FUNC pfWalkFunc, IN HANDLE hUserHandle);
CHAR * DC_GetKeyValueByName(IN DC_DATA_S *pstKey, IN CHAR *pcKeyName);
BS_STATUS DC_Save(IN HANDLE hDcHandle);

#ifdef __cplusplus
    }
#endif 

#endif 


