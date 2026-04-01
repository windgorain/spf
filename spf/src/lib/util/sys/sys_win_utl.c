/******************************************************************************
* Copyright (C),    LiXingang
* Author:      LiXingang  Version: 1.0  Date: 2013-6-4
* Description: 
* History:     
******************************************************************************/
#include "bs.h"

#include "utl/sys_utl.h"
#include "utl/file_utl.h"
#include "utl/txt_utl.h"

#include "sys_os_utl.h"

#ifdef IN_WINDOWS

char * _SYS_OS_GetSelfFileName(void)
{
    static char szFileName[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;
    UINT uiLen;

    if (bExist == TRUE)
    {
        return szFileName;
    }

    uiLen = GetModuleFileName(NULL, szFileName, sizeof(szFileName));

    if (uiLen == sizeof(szFileName))
    {
        szFileName[0] = '\0';
        return NULL;
    }

    bExist = TRUE;

    return szFileName;
}

char * _SYS_OS_GetSelfFilePath(void)
{
    static CHAR szFileName[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;
    UINT uiLen;
    CHAR *pcSplit;

    if (bExist == TRUE)
    {
        return szFileName;
    }

    uiLen = GetModuleFileName(NULL, szFileName, sizeof(szFileName));

    if (uiLen == sizeof(szFileName)) {
        szFileName[0] = '\0';
        return NULL;
    }

    pcSplit = strrchr(szFileName, '\\');
    if (NULL == pcSplit) {
        szFileName[0] = '\0';
        return NULL;
    }

    *pcSplit = '\0';
    bExist = TRUE;

    return szFileName;
}

#if 0

int _SYS_OS_AutoStartFile(char *pcRegName, char *filepath, char *workpath, BOOL_T bSelfStart, char *arg)
{
    BS_STATUS eRet = BS_OK;
    HKEY   RegKey;   
    char info[512];
    CHAR *pcRegPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    if (arg == NULL) {
        arg = "";
    }

    RegKey=NULL;
    
    if (BS_OK != RegOpenKeyEx(HKEY_LOCAL_MACHINE, pcRegPath, 0, KEY_ALL_ACCESS|KEY_WOW64_64KEY, &RegKey)) {
        BS_WARNNING(("Can't open reg"));
        return BS_CAN_NOT_OPEN;
    }

    if (bSelfStart) {
        snprintf(info, sizeof(info), "%s %s", filepath, arg);
        if (BS_OK != RegSetValueEx(RegKey, pcRegName, 0, REG_SZ, info, strlen(info))) {
            BS_WARNNING(("Can't reg file start"));
            eRet = BS_CAN_NOT_WRITE;
        }
    } else {
        if(BS_OK != RegDeleteValue(RegKey, pcRegName)) {
            eRet = BS_CAN_NOT_WRITE;
        }
    }

    RegCloseKey(RegKey);

    return eRet;
}
#endif

int _SYS_OS_AutoStartFile(char *pcRegName, char *filepath, char *workpath, BOOL_T bSelfStart, char *arg)
{
    char command[1024];

    if (bSelfStart) {
        
        snprintf(command, sizeof(command),
                "schtasks /create /tn \"%s\" /tr \"%s\" /sc onstart /ru SYSTEM /f",
                pcRegName, filepath);
    } else {
        snprintf(command, sizeof(command), "schtasks /delete /tn \"%s\" /f", pcRegName);
    }
    
    if (0 == system(command)) {
        return 0;
    }

    return BS_ERR;
}

#endif

