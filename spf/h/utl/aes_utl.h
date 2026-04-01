/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0  Date: 2007-8-18
* Description: 
* History:     
******************************************************************************/
#ifndef _AES_UTL_H
#define _AES_UTL_H
#ifdef __cplusplus
extern "C"
{
#endif

#define AES_IV_SIZE 16 


#define AES_CIPHER_LEN(clear_len) NUM_UP_ALIGN((clear_len) + 1, 16)
#define AES_CIPHER_PAD_LEN(clear_len) (NUM_ALIGN_DIFF((clear_len + 1), 16) + 1)


typedef struct {
    U8 *key;  
    U8 *iv;   
    U16 bits; 
    U8 enc: 1; 
    U8 need_padding: 1; 
}AES_PARAM_S;

void * AES_GetSysKey(void);
void * AES_GetSysIv(void);

int AES_Cipher(AES_PARAM_S *p, U8 *in, int in_size, U8 *out);
int AES_Cipher128(UCHAR *key, UCHAR *iv, UCHAR *in, int in_size, UCHAR *out, int do_encrypt);
int AES_Cipher256(void *key, void *iv, void *in, int in_size, void *out, int do_encrypt);
int AES_Cipher128NoPad(UCHAR *key, UCHAR *iv, UCHAR *in, int in_size, UCHAR *out, int do_encrypt);
int AES_Cipher256NoPad(UCHAR *key, UCHAR *iv, UCHAR *in, int in_size, UCHAR *out, int do_encrypt);

#ifdef __cplusplus
}
#endif
#endif 
