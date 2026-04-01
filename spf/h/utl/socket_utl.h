/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      LiXingang  Version: 1.0  Date: 2009-6-16
* Description: 
* History:     
******************************************************************************/

#ifndef __SOCKET_UTL_H_
#define __SOCKET_UTL_H_

#ifdef __cplusplus
    extern "C" {
#endif 

#include "utl/net.h"
#include "utl/socket_in.h"


#define SOCKET_E_READ_PEER_CLOSE 0
#define SOCKET_E_ERR        -1
#define SOCKET_E_CREATE_ERR -2
#define SOCKET_E_SEND_ERR -3
#define SOCKET_E_RECV_ERR -4

#ifdef IN_WINDOWS
#define SOCKET_E_AGAIN      -WSAEWOULDBLOCK
#ifndef EAGAIN 
#define EAGAIN SOCKET_E_AGAIN
#endif
#endif

#ifdef IN_UNIXLIKE
#define SOCKET_E_AGAIN      -EAGAIN
#endif

extern int _Socket_Create(int family, int type, int protocol, const char *filename, int line);
extern BS_STATUS Socket_Close(IN INT iSocketId);
extern int Socket_Connect(IN INT iSocketId, IN UINT ulIp, IN USHORT usPort);
extern int Socket_Connect2(int fd, UINT ulIp, USHORT usPort);
extern int Socket_UnixSocketClient(char *path, int type, int flags);
extern BOOL_T Socket_IsIPv4(IN CHAR *pcIpOrName);
extern BOOL_T Socket_N_IsIPv4(IN CHAR *pcName, IN UINT uiLen);
int Socket_SetSockOpt(int sock, int level, int opt, void *data, int opt_len);
extern BS_STATUS Socket_Ioctl(IN INT iSocketId, INT lCmd, void *argp);
int Socket_EnablePktInfo(int fd, int on);

extern UINT Socket_Ipsz2IpNetWitchCheck(IN CHAR *pcIP);
extern UINT Socket_Ipsz2IpNet(char *pcIP);
extern UINT Socket_Ipsz2IpHost(IN CHAR *pcIP);

extern UINT Socket_NameToIpNet(IN CHAR *szIpOrHostName);

extern UINT Socket_NameToIpHost (IN CHAR *szIpOrHostName);

extern CHAR * Socket_IpToName (IN UINT ulIp);
CHAR * Socket_Ip2Name(IN UINT ip, OUT char *buf, IN int buf_size);

extern int Socket_GetLocalIpPortNet(IN INT iSocketId, OUT UINT *pulIp, OUT USHORT *pusPort);

extern int Socket_GetLocalIpPort(IN INT iSocketId, OUT UINT *pulIp, OUT USHORT *pusPort);

extern int Socket_GetPeerIpPortNet(IN INT iSocketId, OUT UINT *pulIp, OUT USHORT *pusPort);

extern int Socket_GetPeerIpPort(IN INT iSocketId, OUT UINT *pulIp, OUT USHORT *pusPort);
extern USHORT Socket_GetHostPort(IN INT iSocketId);
extern UINT Socket_GetFamily(IN INT iSocketId);
extern BS_STATUS Socket_Bind(IN INT iSocketId, IN UINT ulIp, IN USHORT usPort);

extern BS_STATUS Socket_Listen(IN INT iSocketId, UINT ulLocalIp, IN USHORT usPort, IN UINT uiBacklog);
extern int _Socket_Accept(int fd, OUT struct sockaddr *pstAddr, INOUT INT *piLen, char *filename, int line);
#define Socket_Accept(a,b,c) _Socket_Accept(a,b,c,__FILE__,__LINE__)

extern INT Socket_Write(IN INT iSocketId, IN VOID *data, IN UINT ulLen, IN UINT ulFlag);
extern int Socket_Write2(int fd, void *data, U32 len, U32 flag);
extern int Socket_WriteString(int fd, char *buf, unsigned int flag);

extern BS_STATUS Socket_WriteUntilFinish(IN INT iSocketId, IN UCHAR *pucBuf, IN UINT ulLen, IN UINT ulFlag);

extern int Socket_GetLastErrno(void);


extern INT Socket_Read(IN INT iSocketId, OUT void *buf, IN UINT uiBufLen, IN UINT uiFlag);


extern int Socket_Read2(int iSocketId, OUT void *buf, UINT uiLen, OUT UINT *puiReadLen, UINT ulFlag);

extern int Socket_Recv2(int iSocketId, OUT void *buf, UINT uiLen, UINT ulFlag);

extern BS_STATUS Socket_SendTo
(
    IN INT iSocketId,
    IN VOID *pBuf,
    IN UINT ulBufLen,
    IN UINT ulToIp,
    IN USHORT usToPort
);
extern int Socket_RecvFrom
(
    IN INT iSocketId,
    OUT VOID *pBuf,
    IN UINT ulBufLen,
    OUT UINT *pulFromIp,
    OUT USHORT *pusFromPort
);
int Socket_RecvFromExt(int fd, OUT void *buf, int buf_size, OUT U32 *sip, OUT U16 *sport, OUT U32 *dip);
extern BS_STATUS Socket_SetRecvBufSize(IN INT iSocketId, IN UINT ulBufLen);
extern BS_STATUS Socket_SetSendBufSize(IN INT iSocketId, IN UINT ulBufLen);
extern BS_STATUS _Socket_Pair(UINT uiType, OUT INT aiFd[2], const char *filename, int line);
extern BS_STATUS Socket_SetNoBlock(IN INT iSocketID, IN BOOL_T bNoBlock);
extern BS_STATUS Socket_SetNoDelay(IN INT iSocketID, IN BOOL_T bNoDelay);
extern int Socket_SetReuseAddr(int fd, int reuse);

extern int Socket_ConnectUnixSocket(int fd, char *path);

extern INT Socket_Dup(IN INT iFd);


extern INT Socket_Inheritable(IN INT iFd);

int _Socket_OpenUdp(UINT ip, USHORT port, const char *file, int line);
int _Socket_UdpClient(UINT ip, USHORT port, const char *file, int line);
int _Socket_TcpServer(UINT ip, USHORT port, const char *file, int line);
int _Socket_UnixServer(char *path, int type, const char *file, int line);
int _Socket_UnixClient(char *path, int type, int no_block, const char *file, int line);

#define Socket_Create(family,type,proto) _Socket_Create(family,type,proto,__FILE__,__LINE__)
#define Socket_Pair(type,fds) _Socket_Pair(type,fds,__FILE__,__LINE__)
#define Socket_OpenUdp(ip,port) _Socket_OpenUdp((ip),(port),__FILE__,__LINE__)
#define Socket_UdpClient(ip,port) _Socket_UdpClient((ip),(port),__FILE__,__LINE__)
#define Socket_TcpServer(ip,port) _Socket_TcpServer((ip),(port),__FILE__,__LINE__)
#define Socket_UnixServer(path,type) _Socket_UnixServer((path),(type),__FILE__,__LINE__)
#define Socket_UnixClient(path,type,no_block) _Socket_UnixClient((path),(type),(no_block),__FILE__,__LINE__)

#ifdef __cplusplus
    }
#endif 

#endif 

