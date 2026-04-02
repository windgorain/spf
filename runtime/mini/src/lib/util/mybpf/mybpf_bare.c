/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include <sys/mman.h>
#include "bs.h"
#include "utl/bpf_helper_utl.h"
#include "utl/arch_utl.h"
#include "utl/mybpf_bare.h"
#include "utl/mybpf_prog_def.h"
#include "utl/mmap_utl.h"

static void * g_mini_bss[2048];

static int _runbpf_run_bare(void *data, int len, void **tmp_helpers, MYBPF_PARAM_S *p)
{
    MYBPF_AOT_PROG_CTX_S ctx = {0};
    int (*fn)(U64,U64,U64,U64,U64,void*);

    g_mini_bss[0] = (char*)g_mini_bss + 16;

    ctx.base_helpers = BpfHelper_BaseHelper();
    ctx.sys_helpers = BpfHelper_SysHelper();
    ctx.user_helpers = BpfHelper_UserHelper();
    ctx.tmp_helpers = (const void **)tmp_helpers;
    ctx.global_map_data = g_mini_bss;

    fn = mmap(0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if ((! fn) || (fn==(void*)-1)) {
        RETURNI(BS_ERR, "Can't map prog");
    }

    memcpy(fn, data, len);
    mprotect(fn, len, PROT_READ | PROT_EXEC);

    int ret = fn(p->p[0], p->p[1], p->p[2], p->p[3], p->p[4], &ctx);

    munmap(fn, len);

    return ret;
}

static int _mybpf_bare_check_depends(MYBPF_BARE_HDR_S *hdr, const void **tmp_helpers)
{
    MYBPF_BARE_SUB_HDR_S *shdr = (void*)(hdr + 1);

    int depend_count = ntohl(shdr->depends_count);
    if (depend_count == 0) {
        return 0;
    }

    int *helpers = (void*)(shdr + 1);

    for (int i=0; i<depend_count; i++) {
        int helper_id = ntohl(helpers[i]);
        void *fn = BpfHelper_GetFuncExt(helper_id, tmp_helpers);
        if (! fn) {
            RETURNI(BS_NOT_SUPPORT, "Not support helper %d", helper_id);
        }
    }

    return 0;
}

static int _mybpf_bare_check(MYBPF_BARE_HDR_S *hdr)
{
    if (hdr->magic != htonl(MYBPF_BARE_MAGIC)) {
        /* 魔数不对 */
        RETURNI(BS_NOT_MATCHED, "Magic not match");
    }

    if ((! hdr->arch) || (hdr->arch != ARCH_LocalArch())) {
        RETURNI(BS_NOT_SUPPORT, "Jit arch not matched");
    }

    return _mybpf_bare_check_depends(hdr, NULL);
}

int MYBPF_RunBareMain(void *mem, MYBPF_PARAM_S *p)
{
    MYBPF_BARE_HDR_S *hdr = mem;
    MYBPF_BARE_SUB_HDR_S *shdr = (void*)((char*)hdr + ntohs(hdr->hdr_size));

    if (_mybpf_bare_check(hdr) < 0) {
        return -1;
    }

    int shdr_len = ntohs(shdr->sub_hdr_size) + (sizeof(int) * ntohl(shdr->depends_count));
    void *prog_begin = (char*)shdr + shdr_len;

    return _runbpf_run_bare(prog_begin, ntohl(shdr->sub_size) - shdr_len, NULL, p);
}

