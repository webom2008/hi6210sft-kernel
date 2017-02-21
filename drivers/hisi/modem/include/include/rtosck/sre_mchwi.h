/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dao3X42PYbfHsVFaIAc3PM3AEXlSR5QiNlDgkQGv7QzKliOnSZCe8JU9xvK0g6yfcuV1J
TJg6QEFc0HN7TC+ilrodaEINyg6jZpBt/KRjLF2uMiB7H1C+ynGvP6Ql4+5U0A==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file sre_mchwi.h
*
* Copyright(C), 2008-2008, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ���������Ӳ�ж϶���ͷ�ļ��� \n
*/

/** @defgroup SRE_mchwi �˼�Ӳ�ж�
   *@ingroup SRE_interrupt
*/

#ifndef _SRE_MCHWI_H
#define _SRE_MCHWI_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_mchwi
 * �˼��жϴ����룺�˼��жϴ�����Ŀ�ĺ˺���Ч
 *
 * ֵ: 0x02001480
 *
 * ���������Ŀ�ĺ˺ŷǱ��ˣ�������Ч��Χ��
 */
#define OS_ERRNO_MCHWI_DST_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x80)

/**
 * @ingroup SRE_mchwi
 * �˼��жϴ����룺6181��6108ƽ̨�£����ͺ˼��ж�ʱ���������������
 *
 * ֵ: 0x02001486
 *
 * �������: �ȵ���������пɴ洢�˼��ж�ʱ�ٷ��͡�
 *
 */
#define OS_ERRNO_IPC_SHQ_FULL                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x86)

/**
 * @ingroup SRE_mchwi
 * �˼��жϴ����룺6181��6108ƽ̨�£���ʼ���׶Σ����벻���㹻����Ϣ������пռ䡣
 *
 * ֵ: 0x02001487
 *
 * �������: Ϊ����̬�������ø����ڴ�ռ䡣
 *
 */
#define OS_ERRNO_MCDDR_NO_MEMORY                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x87)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
/*
 * History: \n
 * 2009-06-26, t00145304, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
