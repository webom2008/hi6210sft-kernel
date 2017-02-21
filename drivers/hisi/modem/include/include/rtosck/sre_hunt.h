/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DarO29rxIXESQDaPZcfemc3RIahcAVv/y+GVavueUkW3g2DpzzbIDSTgrb5H+Bii0UwM5
3uc0a1gzCQoLSu2H2QBVHG5XQ/XH49K9ulpHF6rLFuGTWZckU0S92T92Ev+0tA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
  * @file sre_hunt.h
  *
  * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * ������PID��ȡ�Ķ���ͷ�ļ���\n
  */

#ifndef _SRE_HUNT_H
#define _SRE_HUNT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**@defgroup sre_hunt Hunt����
  *@ingroup SRE_comm
  */

/**
 * @ingroup sre_hunt
 * HUNT�����룺HUNTģ���ʼ��ʧ�ܡ�
 *
 * ֵ: 0x02001f00
 *
 * ���������ȷ�����빲��̬fsc�ڴ����˽��fsc�ڴ�����Ƿ�ʧ�ܡ�
 */
#define OS_ERRNO_HUNT_INIT_ERROR            SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x00)

/**
 * @ingroup sre_hunt
 * HUNT�����룺������������ж�ʱ���߳���������
 *
 * ֵ: 0x02001f01
 *
 * ���������������������ж�ʱ��ȷ���߳���������Ψһ��
 */
#define OS_ERRNO_HUNT_THREAD_NAME_REPEAT    SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x01)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ���߳�ID���߳�����ȡ�߳�PIDʱ�����߳�δ��������ɾ����
 *
 * ֵ: 0x02001f02
 *
 * ���������ȷ���߳��Ѵ�����δ��ɾ����
 */
#define OS_ERRNO_HUNT_THREAD_NOT_CREAT      SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x02)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ���߳�ID���߳�����ȡ�߳�PIDʱ����ηǷ���
 *
 * ֵ: 0x02001f03
 *
 * ���������ȷ��ָ��ǿգ��Լ��˺źϷ���
 */
#define OS_ERRNO_HUNT_ILLEGAL_INPUT         SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x03)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ���߳�ID���߳�����ȡ�߳�PIDʱ��Hunt����û�г�ʼ����
 *
 * ֵ: 0x02001f04
 *
 * ���������ȷ���߳����ں˵�hunt���ѳ�ʼ����
 */
#define OS_ERRNO_HUNT_NOT_INIT              SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x04)

/**
* @ingroup sre_hunt
* @brief ͨ��ָ���˵��߳�(�������ж�)����ȡ��PID��
*
* @par ����:
* ͨ��ָ���˵��߳�(�������ж�)����ȡ�߳�PID��
* @attention
* <ul>
* <li>���˵���#SRE_HuntMature����øýӿڣ�����Ŀ�ĺ��Ƿ����#SRE_HuntMature����������ˣ���������в�ѯ����������һֱ�ȴ���</li>
* <li>���˵���#SRE_HuntMature֮ǰ���øýӿڣ�����עĿ�ĺ��Ƿ����#SRE_HuntMature��ֱ�ӽ��в�ѯ������</li>
* </ul>
*
* @param ucCoreID  [IN] ����Ϊ#UINT8���߳����ں˺�[0,OS_MAX_CORE_NUM-1]��
* @param pThreadName [IN] ����Ϊ#CHAR*���߳������ȷ�Χ[1,15]��
* @param puwPID [OUT] ����Ϊ#UINT32*���߳�PID��
*
* @retval #OS_ERRNO_HUNT_THREAD_NOT_CREAT 0x02001f02�����߳�δ��������ɾ����
* @retval #OS_ERRNO_HUNT_ILLEGAL_INPUT    0x02001f03����ηǷ���
* @retval #OS_ERRNO_HUNT_NOT_INIT         0x02001f04��hunt����û�г�ʼ����
* @retval #SRE_OK                         0x00000000����ȡPID�ɹ���
* @par ����:
* <ul><li>sre_hunt.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HuntMature
*/
extern UINT32 SRE_HuntByName(UINT8 ucCoreID, CHAR *pThreadName, UINT32 *puwPID);

/**
* @ingroup sre_hunt
* @brief ��Ǳ������е���������ж��Ѵ�����ɣ�OS��IDLE���⣩�������˿��Գɹ���ѯ���˵�PID��
*
* @par ����:
* ���ϱ���mature��־��ͬʱ�ñ�־��ʹ�ñ����ڵ���#SRE_HuntByNameʱ�����Ŀ�ĺ�û����������һֱ�ȴ���ֱ��Ŀ�ĺ�������mature��־�ŷ��ز�ѯ�����
* @attention
* <ul>
* <li>�����ڱ������е���������жϣ�OS��IDLE���⣩�������֮����á�</li>
* </ul>
*
* @param �ޡ�
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_hunt.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HuntByName
*/
extern VOID SRE_HuntMature(VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_HUNT_H */

 /**
  * History:
  * 2010-03-10 z00134877: Create this file.
  *
  * vi: set expandtab ts=4 sw=4 tw=80:
  */

