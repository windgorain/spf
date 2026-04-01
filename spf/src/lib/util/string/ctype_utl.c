/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include "bs.h"
#include "utl/ctype_utl.h"




BOOL_T CTYPE_CheckInRange(char *string, int string_len, char *range)
{
    for (int i=0; i<string_len; i++) {
        if (! strchr(range, string[i])) {
            return FALSE;
        }
    }

    return TRUE;
}


BOOL_T CTYPE_IsDomainName(char *string, int string_len)
{
    for (int i=0; i<string_len; i++) {
        char c = string[i];
        if (ISNumOrLetter(c) || (c == '-') || (c == '.')) {
            continue;
        }
        return FALSE;
    }

    return TRUE;
}


BOOL_T CTYPE_IsNumString(char *str, int str_len)
{
    if ((NULL == str) || (str_len == 0)) {
        return FALSE;
    }

    
    if (*str == '-') {
        str++;
        str_len --;
    }

    if (str_len == 0) {
        return FALSE;
    }

    for (int i=0; i<str_len; i++) {
        if ((str[i] < '0') || (str[i] > '9')) {
            return FALSE;
        }
    }

    return TRUE;
}


BOOL_T CTYPE_IsNumOrLetter(char *str, int str_len)
{
    if ((NULL == str) || (str_len == 0)) {
        return FALSE;
    }

    for (int i=0; i<str_len; i++) {
        if (! ISNumOrLetter(str[i])) {
            return FALSE;
        }
    }

    return TRUE;
}
