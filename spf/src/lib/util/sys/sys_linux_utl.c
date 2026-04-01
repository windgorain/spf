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


#ifdef IN_LINUX

static char * _sys_os_get_self_file_path(OUT char *path, int size)
{
    int n;
    char *pcSplit;

    path[0] = '\0';

    n = readlink("/proc/self/exe", path, size);
    if (n < 0) {
        return NULL;
    }

    path[n] = '\0';

    pcSplit = strrchr(path, '/');
    if (NULL == pcSplit) {
        return NULL;
    }

    *pcSplit = '\0';
    
    return path;
}

static int _sys_os_create_service(char *pcRegName, char *filepath, char *workpath, char *arg)
{
    char tmp[256];

    snprintf(tmp, sizeof(tmp), "/etc/systemd/system/%s.service", pcRegName);

    FILE *fp = fopen(tmp, "wb+");
    if (! fp) {
        return BS_ERR;
    }

    fprintf(fp, "[Unit]\n"
            "Description=%s\n"
            "After=network.target\n\n", pcRegName);

    fprintf(fp, "[Service]\n"
        "LimitCORE=0\n"
            "WorkingDirectory=%s\n"
            "ExecStartPre=\n"
            "ExecStart=%s\n"
            "ExecStopPost=\n"
            "KillMode=process\n"
            "Restart=on-failure\n"
            "RestartSec=60s\n\n",
            workpath, filepath);

    fprintf(fp, "[Install]\n"
            "WantedBy=multi-user.target\n");

    fclose(fp);

    return 0;
}



char * _SYS_OS_GetSelfFileName(void)
{
    static CHAR szFileName[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;
    INT n;

    if (bExist == TRUE) {
        return szFileName;
    }

    n = readlink("/proc/self/exe", szFileName, FILE_MAX_PATH_LEN);
    if (n < 0) {
        return NULL;
    }

    szFileName[n] = '\0';
    bExist = TRUE;
    
    return szFileName;
}


CHAR * _SYS_OS_GetSelfFilePath(void)
{
    static CHAR szFilePath[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;

    if (bExist == TRUE) {
        return szFilePath;
    }

    _sys_os_get_self_file_path(szFilePath, sizeof(szFilePath));
    bExist = TRUE;
    
    return szFilePath;
}


int _SYS_OS_AutoStartFile(char *pcRegName, char *filepath, char *workpath, BOOL_T bSelfStart, char *arg)
{
    int ret = 0;
    char tmp[256];

    if (bSelfStart) {
        if (_sys_os_create_service(pcRegName, filepath, workpath, arg) < 0) {
            return BS_ERR;
        }
        snprintf(tmp, sizeof(tmp), "systemctl enable %s", pcRegName);
        ret = system(tmp);
    } else {
        snprintf(tmp, sizeof(tmp), "systemctl disable %s", pcRegName);
        ret = system(tmp);
        snprintf(tmp, sizeof(tmp), "rm -fr /etc/systemd/system/%s.service", pcRegName);
        ret |= system(tmp);
    }

    return ret;
}

#endif


