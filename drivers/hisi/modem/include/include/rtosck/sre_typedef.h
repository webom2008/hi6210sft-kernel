/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DahojZ3dUrV7+zZqiMXIfr/uL7ZmGXoivhj4hY2OP2bL8SS8nhR+WOqItQR62pw9imk3d
H1yMNfRMEsFXNC/nmV1Eq8ZdUo2/OccWwZEQYRdRIlIdjIyFEy/gtPuBn2Y8WQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_typedef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ��������������������ͺ����ݽṹ�� \n
 */

#ifndef _SRE_TYPEDEF_H
#define _SRE_TYPEDEF_H

#include "sre_buildef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#ifndef _WIN32
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))
#define INLINE                                              static inline
#ifndef OS_EMBED_ASM
#define OS_EMBED_ASM                                        __asm__ __volatile__
#endif
#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
#ifndef INLINE
#define INLINE                                              static inline
#endif
#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
#ifndef OS_EMBED_ASM
#define OS_EMBED_ASM     __asm
#endif
#endif
#else
#ifndef INLINE
#define INLINE                                              static __inline
#endif

#ifndef OS_EMBED_ASM
#define OS_EMBED_ASM     __asm
#endif

#endif
#ifndef SRE_TYPE_DEF
#define SRE_TYPE_DEF

/* type definitions */
typedef unsigned char                                       UINT8;
typedef unsigned short                                      UINT16;
typedef unsigned int                                        UINT32;
typedef signed char                                         INT8;
typedef signed short                                        INT16;
typedef signed int                                          INT32;
typedef float                                               FLOAT;
typedef double                                              DOUBLE;
typedef char                                                CHAR;
typedef unsigned char                                       UCHAR;
typedef unsigned int                                        BOOL;
typedef unsigned long long                                  UINT64;
typedef signed long long                                    INT64;
typedef unsigned int                                        UINTPTR;
typedef signed int                                          INTPTR;
typedef int                                                 INT;

#define VOID                                                void

#endif  /*end of #ifndef SRE_TYPE_DEF*/

#ifndef FALSE
#define FALSE                                               ((BOOL)0)
#endif

#ifndef TRUE
#define TRUE                                                ((BOOL)1)
#endif

#ifndef NULL
#define NULL                                                ((VOID *)0)
#endif

#ifdef  YES
#undef  YES
#endif
#define YES                                                 (1)

#ifdef  NO
#undef  NO
#endif
#define NO                                                  (0)

#define OS_NULL_BYTE                                        ((UINT8)0xff)
#define OS_NULL_SHORT                                       ((UINT16)0xffff)
#define OS_NULL_INT                                         ((UINT32)0xffffffff)
#define NULL_DWORD                                          ((UINT32)0xFFFFFFFF)

#ifndef SRE_OK
#define SRE_OK                                          (0)
#endif

#define OS_FAIL                                             (1)
#define OS_ERROR                                            (UINT32)(-1)
#define OS_INVALID                                          (-1)

typedef VOID    (* OS_VOID_FUNC)();

/**
 * @ingroup  SRE_sys
 * ϵͳʱ�䶨��ṹ��
 */
typedef struct tagSysTime
{
    UINT16  uwYear;    /**< �꣬ϵͳʱ��ȡֵΪ1970 ~ 2038��1970 ~ 2100 */
    UINT8   ucMonth;   /**< �£�ȡֵΪ 1 - 12 */
    UINT8   ucDay;     /**< �գ�ȡֵΪ 1 - 31 */
    UINT8   ucHour;    /**< ʱ��ȡֵΪ 0 - 23 */
    UINT8   ucMinute;  /**< �֣�ȡֵΪ 0 - 59 */
    UINT8   ucSecond;  /**< �룬ȡֵΪ 0 - 59 */
    UINT8   ucWeek;    /**< ���ڣ�ȡֵΪ 0 - 6  */
} SYS_TIME_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TYPEDEF_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

