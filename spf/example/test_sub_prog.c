/*********************************************************
*   Copyright (C) LiXingang
*
********************************************************/
#include "utl/ulc_user.h"

noinline int test2(int a)
{
    BPF_Print("Hello test2! \n");
    a ++;
    return a;
}

noinline int test(int a)
{
    BPF_Print("Hello test! \n");
    a ++;
    return test2(a);
}

SEC(".spf.cmd/main")
int main()
{
    BPF_Print("start \n");
    BPF_Print("a=%d \n", test(0));
    return 0;
}


