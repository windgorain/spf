/*================================================================
*   Created by LiXingang
*   Description: 
*
================================================================*/
#ifndef _NETLINK_UTL_H
#define _NETLINK_UTL_H
#include "netlink_def.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    int nl_fd;
    int gen_family_id;
}NETLINK_S;

typedef int (*PF_NETLINK_DO)(NETLINK_S *nl, int cmd, void *data, int data_len);

void NetLink_Init(NETLINK_S *nl);
int NetLink_Open(NETLINK_S *nl, char *nl_gen_name);
void NetLink_Close(NETLINK_S *nl);
int NetLink_SendMsg(NETLINK_S *nl, unsigned int msg_type, void *data, int datalen, void *recv_buf, int buf_size);
int NetLink_DoExt(char *nl_name, PF_NETLINK_DO do_func, int cmd, void *data, int data_len);
int NetLink_Do(PF_NETLINK_DO do_func, int cmd, void *data, int data_len);

#ifdef __cplusplus
}
#endif
#endif 
