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

#ifdef IN_MAC
#include <mach-o/dyld.h>


char * _SYS_OS_GetSelfFileName(void)
{
    static CHAR szFileName[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;
    UINT n = FILE_MAX_PATH_LEN;

    if (bExist == TRUE) {
        return szFileName;
    }

    _NSGetExecutablePath(szFileName, &n);
    
    return szFileName;
}


CHAR * _SYS_OS_GetSelfFilePath(void)
{
    static CHAR szFilePath[FILE_MAX_PATH_LEN + 1] = "";
    static BOOL_T bExist = FALSE;
    UINT n = FILE_MAX_PATH_LEN;
    CHAR *pcSplit;

    if (bExist == TRUE) {
        return szFilePath;
    }

    _NSGetExecutablePath(szFilePath, &n);

    pcSplit = strrchr(szFilePath, '/');
    if (NULL == pcSplit) {
        szFilePath[0] = '\0';
        return "";
    }

    *pcSplit = '\0';
    bExist = TRUE;
    
    return szFilePath;
}

static int _sys_os_create_plist(char *pcRegName, char *filepath, char *workpath, char *arg)
{
    char tmp[256];

    snprintf(tmp, sizeof(tmp), "/Library/LaunchDaemons/%s.plist", pcRegName);

    FILE *fp = fopen(tmp, "wb+");
    if (! fp) {
        return BS_ERR;
    }

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
            "<plist version=\"1.0\">\n"
            "<dict>\n"
            "<!-- 唯一的服务标识符，通常使用反向域名格式 -->\n"
            "<key>Label</key>\n");
    
    fprintf(fp, "<string>%s</string>\n\n", pcRegName);

    fprintf(fp, "<!-- 指定要执行的程序路径和参数 -->\n"
            "<key>ProgramArguments</key>\n"
            "<array>\n"
            "<!-- 第一项为程序的绝对路径 -->\n");

    fprintf(fp, "<string>%s</string>\n", filepath);

    if (arg) {
        fprintf(fp, "<string>%s</string>\n", arg);
    }

    fprintf(fp, "</array>\n\n");

#if 0
    fprintf(fp, "<!-- 在加载时立即运行程序 -->\n"
            "<key>RunAtLoad</key>\n"
            "<true/>\n\n");
#endif

    fprintf(fp, "<!-- （可选）保持程序活跃，如果程序意外退出，launchd会重新启动它 -->\n"
            "<key>KeepAlive</key>\n"
            "<dict>\n"
            "<!-- 手动停止不重启 -->\n"
            "<key>SuccessfulExit</key>\n"
            "<false/>\n"
            "</dict>\n\n");

    if (workpath) {
        fprintf(fp, "<!-- （可选）指定程序的工作目录 -->\n"
                "<key>WorkingDirectory</key>\n"
                "<string>%s</string>\n\n", workpath);
    }

    fprintf(fp, "<!-- （可选）标准输出和错误日志的路径 -->\n"
            "<key>StandardOutPath</key>\n"
            "<string>/var/log/xnetc.log</string>\n"
            "<key>StandardErrorPath</key>\n"
            "<string>/var/log/xnetc.error.log</string>\n"
            "</dict>\n"
            "</plist>\n");

    fclose(fp);

    snprintf(tmp, sizeof(tmp), "chown root:wheel /Library/LaunchDaemons/%s.plist", pcRegName);
    if (system(tmp) < 0) {
        return (BS_ERR);
    }

    snprintf(tmp, sizeof(tmp), "chmod 644 /Library/LaunchDaemons/%s.plist", pcRegName);
    if (system(tmp) < 0) {
        return (BS_ERR);
    }

    return 0;
}


int _SYS_OS_AutoStartFile(char *pcRegName, char *filepath, char *workpath, BOOL_T bSelfStart, char *arg)
{
    char tmp[256];

    if (bSelfStart) {
        if (_sys_os_create_plist(pcRegName, filepath, workpath, arg) < 0) {
            return BS_ERR;
        }
        snprintf(tmp, sizeof(tmp), "launchctl load -w /Library/LaunchDaemons/%s.plist > /dev/null 2>&1", pcRegName);
        system(tmp);
        snprintf(tmp, sizeof(tmp), "launchctl enable system/%s", pcRegName);
        system(tmp);
    } else {
        snprintf(tmp, sizeof(tmp), "launchctl disable system/%s", pcRegName);
        system(tmp);
        snprintf(tmp, sizeof(tmp), "rm -f /Library/LaunchDaemons/%s.plist", pcRegName);
        system(tmp);
    }

    return 0;
}

#endif
