/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_basefun.h
*
*  Project Code: VISPV100R007
*   Module Name: PUBLIC  
*  Date Created: 2008-9-20
*        Author: w60786
*   Description: VISP�ڲ�����������vos����ԭ������ͳһ�ŵ����ļ��У������Ʒ����������Щ������
*                VISPͷ�ļ�ʱ�������Ӵ������⡣
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-9-20    w60786          Create the first version.
*
*******************************************************************************/

#ifndef _TCPIP_BASEFUN_H_
#define _TCPIP_BASEFUN_H_

#ifdef  __cplusplus
extern "C"{
#endif

#if (TCPIP_VOS_FUNC_TYPE != VOS_FUNC_TYPE_SAFE)
/*lint -function(memcpy, VOS_Mem_Copy)*/
extern VOS_UINT32 VOS_Mem_Copy( VOS_VOID * pDestPtr,
                                const VOS_VOID * pSrcPtr,
                                SIZE_T uvCopyLen );
extern CHAR*  VOS_strncpy( CHAR * pcdst, const CHAR * pcsrc, VOS_UINT32 n );
/*lint -function(strncat, VOS_StrNCat) */
extern CHAR * VOS_StrNCat(CHAR * pscDest, CHAR * pscSrc, SIZE_T uvCount);
#else
extern VOS_UINT32 VOS_Mem_Copy_Safe( VOS_VOID *pDestPtr, SIZE_T uvDestSize,
                                            const VOS_VOID *pSrcPtr, SIZE_T uvCopyLen );
extern CHAR* VOS_strncpy_Safe(CHAR * pscDest, VOS_UINT32 uvDestSize,
                                         const CHAR * pscSrc, VOS_UINT32 uvCount);
extern CHAR * VOS_StrNCat_Safe(CHAR * pscDest, SIZE_T uvDestSize,
                                         const CHAR * pscSrc, SIZE_T uvCount);
#endif
extern VOS_INT32 VOS_nsprintf(CHAR *pscOBuf,
                                   VOS_UINT32 ulMaxStrLen,
                                   const CHAR *pscFormat, ...);

/*lint -function(memset, VOS_Mem_Set)*/ 
extern VOS_UINT32 VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, SIZE_T uvSetLen );
extern VOS_UINT32 VOS_strlen( const CHAR * pcstr );
/*lint -function(strlen, VOS_StrLen)*/
extern CHAR * VOS_StrRChr(CHAR* pscStr, CHAR scChar);

/*lint -sem(VOS_Mem_Zero, 1p)*/
extern VOS_UINT32 VOS_Mem_Zero( CHAR * pBufPtr, SIZE_T ulSetLen );

extern LONG atoul(CHAR *Sour, ULONG * pTemp);

/*lint -function(strncmp, VOS_StrNCmp) */
extern VOS_INT    VOS_StrNCmp(CHAR * pscStr1, CHAR * pscStr2, SIZE_T ulCount);

/*lint -function(strcmp, VOS_StrICmp) */
extern VOS_INT    VOS_StrICmp(CHAR * pscS1, CHAR * pscS2);

/*lint -function(strlen, VOS_StrLen)*/
extern VOS_UINT32 VOS_StrLen(CHAR * pscStr);

/*lint -sem(VOS_Mem_GetRef, 1p, 2p)*/
extern VOS_UINT32 VOS_Mem_GetRef( VOS_VOID * pBuf, VOS_UINT32 * pulRetRef );

/*lint -sem(VOS_Mem_Cmp, 1p,2p,4p)*/
extern VOS_UINT32 VOS_Mem_Cmp( const VOS_VOID * pDestPtr,const VOS_VOID * pSrcPtr,
                                        SIZE_T uvCmpLen, VOS_INT32* plRetResult );
/*This needs to be here since other module is using this declaration */
extern VOS_INT32 VOS_sscanf(const CHAR *pscIBuf, const CHAR *pfmt, ...);

extern VOS_INT32  VOS_atol( const CHAR * pcStr, VOS_INT32 * pnVal );

/* ��־������� */
#define P0(message) message
#define P1(message,_p1) message,_p1
#define P2(message,_p1,_p2)  message,_p1,_p2
#define P3(message,_p1,_p2,_p3) message,_p1,_p2,_p3
#define P4(message,_p1,_p2,_p3,_p4)  message,_p1,_p2,_p3,_p4
#define P5(message,_p1,_p2,_p3,_p4,_p5)message,_p1,_p2,_p3,_p4,_p5
#define P6(message,_p1,_p2,_p3,_p4,_p5,_p6) message,_p1,_p2,_p3,_p4,_p5,_p6 
#define P7(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7 
#define P8(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8 
#define P9(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9
#define P10(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10
#define P11(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11
#define P12(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12
#define P13(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13
#define P14(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14
#define P15(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15
#define P16(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16
#define P17(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17
#define P18(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18
#define P19(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19
#define P20(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20


/*STR:Ŀ�ĵ�ַ
  LEN:�����û���������
  FORMAT_PARAM:����һ����ʽ�ַ����Լ�0����������*/
#define TCPIP_SNPRINTF(STR, LEN, FORMAT_PARAM) (((LEN) > 0) ? TCPIP_nsprintf((STR), (LEN), FORMAT_PARAM) : 0)
/* ����ַ�����ƴ�Ӳ�����
   1. ����ȡdst���û��桢����src�ַ������ȡ����뻺�泤�ȵ���Сֵ��
   2. �����뻺�泤��Ϊ0ʱ��ȡdst���û��桢����src�ַ��������еĽ�Сֵ
*/
#define FREE_LEN(DSTR, DSTLEN)      ((DSTLEN) - VOS_strlen(DSTR) - 1)
#define SRC_LEN(SSTR)               (VOS_strlen(SSTR))
#define CAT_LEN(DSTR, DSTLEN, SSTR) ((FREE_LEN(DSTR, DSTLEN) > SRC_LEN(SSTR)) ? SRC_LEN(SSTR) : FREE_LEN(DSTR, DSTLEN))

#define TCPIP_STRNCAT_S(DSTR, DSTLEN, SSTR)  (TCPIP_StrNCat((DSTR), (DSTLEN), (SSTR), (CAT_LEN(DSTR, DSTLEN, SSTR))))
/* End added */

extern ULONG TCPIP_Safe_Mem_Copy(VOID *pDstStr, ULONG ulDstLen, VOID *pSrcstr, ULONG ulCopyLen);
extern CHAR *TCPIP_Safe_Strncpy(CHAR *pDstStr, ULONG ulDstLen, CHAR *pSrcstr, ULONG ulCopyLen);
extern CHAR *TCPIP_Safe_StrNCat(CHAR *pDstStr, ULONG ulDstLen, CHAR *pSrcstr, ULONG ulCopyLen);

#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*_TCPIP_BASEFUN_H_*/

