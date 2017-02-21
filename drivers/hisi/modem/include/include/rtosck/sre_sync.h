/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DaiI/AGxAjWI2fcyNBRmQd4LYmwfEbhglLkcgzP0eUSpCnslhyuH+a1QaTM83SPsHWs0K
2hS/Mnzaiw2nVBVc/ply+Qs7kEnWjdrcDV4oYuFBpEI6HIIrwkG0kEKCBgY3PQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file sre_sync.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ������ �˼�ͬ���Ķ���ͷ�ļ��� \n
*/

/** @defgroup SRE_sync �˼�ͬ������
 *@ingroup SRE_comm
 */

#ifndef _SRE_SYNC_H
#define _SRE_SYNC_H

#include "sre_base.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  SRE_sync
 * �˼�ͬ����Ϣ��ģʽ----����ģʽ��
 */
#define OS_SYNC_BARRIER_MODE_COUNT                          0

/**
 * @ingroup  SRE_sync
 * �˼�ͬ����Ϣ��ģʽ----��ģʽ��
 */
#define OS_SYNC_BARRIER_MODE_CHNID                          1

/**
 * @ingroup  SRE_sync
 * ϵͳ�˼�ͬ����Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagSyncBarrier
{
    volatile UINT32 vuwLock;        /**< ����Դ���˼以������         */
    volatile UINT16 vuwMode;        /**< ͬ��ģʽ����ģʽ�����ģʽ�� */
    volatile UINT16 vusGateValue;   /**< ͬ����ֵ�����Լ���Ƿ����еĺ˶��Ѿ�ͬ����     */
    volatile UINT32 vuwRealValue;   /**< ʵʱֵ��ÿ����ͬ��ʱ�����޸ĸ�ֵ�����к�ͬ���󣬸�ֵ����Ϊ��ʼֵ��  */
    volatile UINT32 vuwInitValue;   /**< ��ʼֵ����ʼ�����к�ͬ���󣬸�ֵ������ʵʱֵ�� */
} OS_SYNC_BARRIER_S;

#if(OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup  SRE_sync
 * @brief spinlock������
 *
 * @par ����:
 * ʹ��spinlock���ܶ��ٽ���Դ���м�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6183ƽ̨��</li>
 * <li>����ĵ�ַ��Ӧ�������ַ������32�ֽڶ����GLOBAL LL2��ַ�����Ҹõ�ַ����Cache�����⣬�õ�ַ�����ݱ��뱻���㣬����᲻��Ч��</li>
 * <li>������������ַΪNULL����ֱ�ӷ��ء�</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] ����#volatile UINT32 *��ִ�м��������ĵ�ַ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplIrqLock
 */
extern VOID SRE_SplLock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief spinunlock������
 *
 * @par ����:
 * ʹ��spinunlock���ܶ��ٽ���Դ���н�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6183ƽ̨��</li>
 * <li>����ĵ�ַ��Ӧ�������ַ������32�ֽڶ����GLOBAL LL2��ַ�����Ҹõ�ַ����Cache�����⣬�õ�ַ�����ݱ��뱻���㣬����᲻��Ч��</li>
 * <li>������������ַΪNULL����ֱ�ӷ��ء�</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] ����#volatile UINT32 *��ִ�м��������ĵ�ַ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplIrqUnlock
 */
extern VOID SRE_SplUnlock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief ���ж������½���spinlock������
 *
 * @par ����:
 * ʹ��spinlock�����ڹ��ж������¶��ٽ���Դ���м�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6183ƽ̨��</li>
 * <li>����ĵ�ַ��Ӧ�������ַ������32�ֽڶ����GLOBAL LL2��ַ�����Ҹõ�ַ����Cache�����⣬�õ�ַ�����ݱ��뱻���㣬����᲻��Ч��</li>
 * <li>������������ַΪNULL����ֱ�ӷ��ء�</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] ����#volatile UINT32 *��ִ�м��������ĵ�ַ��
 *
 * @retval �ر�ȫ���ж�ǰ���ж�״ֵ̬
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplLock
 */
extern UINT32 SRE_SplIrqLock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief ���ж���������spinunlock������
 *
 * @par ����:
 * ʹ��spinunlock�����ڿ��ж������¶��ٽ���Դ���н�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6183ƽ̨��</li>
 * <li>����ĵ�ַ��Ӧ�������ַ������32�ֽڶ����GLOBAL LL2��ַ�����Ҹõ�ַ����Cache�����⣬�õ�ַ�����ݱ��뱻���㣬����᲻��Ч��</li>
 * <li>������������ַΪNULL����ֱ�ӷ��ء�</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] ����#volatile UINT32 *��ִ�м��������ĵ�ַ��
 * @param  uwIntSave   [INT] ����#UINT32��ִ�й��ж������¼��������ķ���ֵ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplUnlock
 */
extern VOID SRE_SplIrqUnlock(volatile UINT32 *pvuwAddress, UINT32 uwIntSave);

#endif


/**
 * @ingroup  SRE_sync
 * @brief ָ���ķ�ʽ�ȴ����ͬ����
 *
 * @par ����:
 * ��˲�������ָ����ģʽ���ж��ͬ����
 *
 * @attention
 * <ul>
 *<li>ȫ�ֱ������pstBarrier�뱣���ڲ���cache�Ĺ����ڴ��С�</li>
 *<li>ʵʱֵ�����ʼֵȡֵ��ͬ��</li>
 *<li>����Դȡֵ���ޣ��������ֵַ��</li>
 *<li>ͬ����ֵȡֵ���ޣ�������ͬ��ǰ����жԱȡ�</li>
 *<li>���ֺ˼�ͬ��ģʽ:OS_SYNC_BARRIER_MODE_COUNT��ʾ����ģʽ��OS_SYNC_BARRIER_MODE_CHNID��ʾ��ģʽ��</li>
 *<li>���ں�������32����ƽ̨(��SD6183)����֧�ֺ�ģʽ��ͬ��</li>
 *<li>����ģʽ(#OS_SYNC_BARRIER_MODE_COUNT)��:��ʼֵΪ�ܹ���Ҫͬ���ĺ�����</li>
 *<li>ָ����ģʽ(#OS_SYNC_BARRIER_MODE_CHNID)��:32λ�ĳ�ʼֵ���������32���˽���ͬ����ÿһλ����һ���ˣ�����:��ʼֵΪ0x03����ʾ��0�ͺ�1֮��ĺ˼�ͬ����</li>
 * </ul>

 * @param  pstBarrier   [IN] ����#volatile OS_SYNC_BARRIER_S *���˼�ͬ���ṹ����Ϣ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_WaitForAllCores
 */
extern VOID SRE_SyncBarrierWait(volatile OS_SYNC_BARRIER_S *pstBarrier);

/**
 * @ingroup  SRE_sync
 * @brief �ȴ����к�ͬ������Ϊ��ʵ����������ȴ��ĺ���Ϊ��ʵ���ڵ����кˡ�
 *
 * @par ����:
 * ��˲�����һ���˵ȴ������������ڴ�ͬ����
 *
 * @attention
 * <ul>
 * <li>ϵͳ�������еĺ˾��ڴ�ͬ����</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sync.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SyncBarrierWait
 */
extern VOID SRE_WaitForAllCores(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif // _SRE_SYNC_H

/**
 * History:
 * 2008-04-30 h00133330: Create this file.
 * 2009-03-10 z00134877: change this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */


