/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2008-10-23
* Description: 
* History:     
******************************************************************************/
#include "bs.h"

#include "utl/sys_utl.h"
#include "utl/file_utl.h"
#include "utl/txt_utl.h"

#include "sys_os_utl.h"

BOOL_T SYS_IsInstanceExist(IN VOID *pszName)
{
#ifdef IN_WINDOWS
	HANDLE hMutex;
    hMutex = CreateMutex(FALSE, FALSE, pszName);
    if(hMutex != NULL)
	{
		DWORD err=GetLastError();
        if(err==ERROR_ALREADY_EXISTS) { 
            CloseHandle(hMutex);
			return TRUE;
		}
	}
#endif
	return FALSE;
}

#ifdef IN_WINDOWS

typedef NTSTATUS (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);


static BOOL _GetRealWindowsVersion(DWORD* pdwMajor, DWORD* pdwMinor, DWORD* pdwBuild)
{
    HMODULE hNtdll;
    RtlGetVersionPtr RtlGetVersionFunc;
    RTL_OSVERSIONINFOW osvi = {0};
    
    hNtdll = GetModuleHandleW(L"ntdll.dll");
    if (hNtdll == NULL) {
        return FALSE;
    }
    
    RtlGetVersionFunc = (RtlGetVersionPtr)GetProcAddress(hNtdll, "RtlGetVersion");
    if (RtlGetVersionFunc == NULL) {
        return FALSE;
    }
    
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if (RtlGetVersionFunc(&osvi) != 0) {
        return FALSE;
    }
    
    if (pdwMajor) *pdwMajor = osvi.dwMajorVersion;
    if (pdwMinor) *pdwMinor = osvi.dwMinorVersion;
    if (pdwBuild) *pdwBuild = osvi.dwBuildNumber;
    
    return TRUE;
}

static SYS_OS_VER_E _sys_get_os_win_ver()
{
    SYS_OS_VER_E eVer;
    DWORD major, minor, build;

    if (! _GetRealWindowsVersion(&major, &minor, &build)) {
        return SYS_OS_VER_WIN_OLD;
    }

    switch (major) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: { eVer = SYS_OS_VER_WIN_OLD; break; }

        case 5: {
            switch(minor) {  
                case 0: { eVer = SYS_OS_VER_WIN2000; break; }
                case 1: { eVer = SYS_OS_VER_WINXP; break;  }
                case 2: { eVer = SYS_OS_VER_WIN_SERVER2003; break; }
                default: { eVer = SYS_OS_VER_WIN_SERVER2003; break; }
            }
            break;
        }

        case 6: {
            switch(minor) {
                case 0: { eVer = SYS_OS_VER_WIN_VISTA; break; }
                case 1: { eVer = SYS_OS_VER_WIN7; break; }
                case 2: { eVer = SYS_OS_VER_WIN8; break; }
                case 3: { eVer = SYS_OS_VER_WIN8_1; break; }
                default: { eVer = SYS_OS_VER_WIN_LATTER; break; }
            }
            break;
        }

        case 10: {
            if (minor == 0) {
                if (build < 22000) {
                    eVer = SYS_OS_VER_WIN10;
                } else {
                    eVer = SYS_OS_VER_WIN11;
                }
            } else {
                eVer = SYS_OS_VER_WIN_LATTER;
            }
            break;
        }

        default: { eVer = SYS_OS_VER_WIN_LATTER; break; }
    }  
    
    return eVer;
}  

static SYS_OS_BIT_E sys_GetOsWinBits(void)
{
    SYSTEM_INFO si;

    GetNativeSystemInfo(&si);
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        return SYS_OS_BIT_64;
    }

    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
        return SYS_OS_BIT_UNKNOWN;
    }

    return SYS_OS_BIT_32;
}

#endif

SYS_OS_VER_E SYS_GetOsVer(void)
{
    static int eVer = SYS_OS_VER_OTHER;

    if (eVer > SYS_OS_VER_OTHER) {
        return eVer;
    }

#ifdef IN_WINDOWS
    eVer = _sys_get_os_win_ver();
#endif

    return eVer;
}

#ifdef IN_WINDOWS
SYS_OS_BIT_E SYS_GetOsBit(void)
{
    return sys_GetOsWinBits();
}
#endif

#ifdef IN_WINDOWS

VOID SYS_HideProcess(void)
{
    HINSTANCE hInst = LoadLibrary("KERNEL32.DLL"); 
	if(hInst) 
	{            
		typedef DWORD (WINAPI *MYFUNC)(DWORD,DWORD);          
		MYFUNC RegisterServiceProcessFun = NULL;     
		RegisterServiceProcessFun = (MYFUNC)GetProcAddress(hInst, "RegisterServiceProcess");
		if(RegisterServiceProcessFun)     
		{             
			RegisterServiceProcessFun(GetCurrentProcessId(),1);     
		}     
		FreeLibrary(hInst); 
	}
}
#endif


BS_STATUS SYS_SetStartFile(char *reg_name, char *filepath, char *workpath, BOOL_T start, char *arg)
{
    return _SYS_OS_AutoStartFile(reg_name, filepath, workpath, start, arg);
}


BS_STATUS SYS_SetStartSelf(char *reg_name, BOOL_T start, char *arg)
{
    if (reg_name[0] == '\0') {
        return BS_ERR;
    }

    char * self_file_path = SYS_GetSelfFileName();

    if (! self_file_path) {
        BS_WARNNING(("Can't get self file name"));
        return BS_ERR;
    }

    return _SYS_OS_AutoStartFile(reg_name, self_file_path, SYS_GetSelfFilePath(), start, arg);
}


CHAR * SYS_GetSelfFileName(void)
{
    return _SYS_OS_GetSelfFileName();
}


CHAR * SYS_GetSelfFilePath(void)
{
    return _SYS_OS_GetSelfFilePath();
}

#ifdef IN_WINDOWS

HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 
    HWND hwndFound;         
    char pszNewWindowTitle[MY_BUFSIZE]; 
    
    char pszOldWindowTitle[MY_BUFSIZE]; 
    
 
    
 
    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
 
    
 
    wsprintf(pszNewWindowTitle, "%d/%d",
        GetTickCount(),
        GetCurrentProcessId());
 
    
 
    SetConsoleTitle(pszNewWindowTitle);
 
    
 
    Sleep(40);
 
    
 
    hwndFound = FindWindow(NULL, pszNewWindowTitle);
 
    
 
    SetConsoleTitle(pszOldWindowTitle);
 
    return(hwndFound);
}

void ShowCmdWin(int show)
{
    ShowWindow(GetConsoleHwnd(), show);
}

#endif

#ifdef IN_MAC
void ShowCmdWin(int show)
{
}
#endif

#ifdef IN_LINUX
void ShowCmdWin(int show)
{
}
#endif

