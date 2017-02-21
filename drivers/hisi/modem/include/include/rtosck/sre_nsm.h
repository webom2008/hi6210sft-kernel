/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DannTIsMO1Rlb7E6huEjiBi2GwEf1TMAEhigMyHIF2mQ7wv/k3Rb1nNyQxx1DXFvLYWHv
YFZ8jRdZOLWTX3jEAWYbD6MdnV+O6Dea6Flg16w6cBTNK0q/ghq5fjpNQMnBzQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file SRE_nsm.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* �����������ռ�ģ�����ͷ�ļ��� \n
*/

/**
 * @defgroup SRE_nsm  �����ռ�
 * @ingroup SRE_kernel
 */

#ifndef _SRE_NSM_H
#define _SRE_NSM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_nsm
 * �����ռ�����룺��ηǷ�������ָ��ΪNULL��
 *
 * ֵ: 0x02001b01
 *
 * ���������ȷ��ָ��ǿա�
 */
#define OS_ERRNO_NSM_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x01)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺����������ռ��С�Ƿ���
 *
 * ֵ: 0x02001b02
 *
 * ��������������ռ����ô�С�������С�������ռ��С��
 */

#define OS_ERRNO_NSM_SPACE_SIZE_ILLEG                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x02)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ��׵�ַδ4�ֽڶ��롣
 *
 * ֵ: 0x02001b03
 *
 * ��������������ռ��׵�ַ��4�ֽڶ��롣
 */
#define OS_ERRNO_NSM_ADDR_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x03)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ��Сδ4�ֽڶ��롣
 *
 * ֵ: 0x02001b04
 *
 * ��������������ռ��С��4�ֽڶ��롣
 */
#define OS_ERRNO_NSM_SIZE_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x04)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ�������
 *
 * ֵ: 0x02001b05
 *
 * �����������Ӽ�¼ʱ��ȷ�������ռ����㹻�Ŀռ�洢��
 */
#define OS_ERRNO_NSM_MEM_FULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x05)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ��м�¼��������
 *
 * ֵ: 0x02001b06
 *
 * ����������������ռ�����Ӽ�¼ʱ��ȷ����¼��Ψһ��
 */
#define OS_ERRNO_NSM_OBJ_RENAME                             SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x06)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺ɾ��������¼ʱ����Ӧ��¼�����ڡ�
 *
 * ֵ: 0x02001b07
 *
 * ���������ɾ��������¼ʱ����ȷ����Ӧ��¼���ڡ�
 */
#define OS_ERRNO_NSM_DEL_NOT_FIND                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x07)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ��ж�Ӧ��¼�����ڡ�
 *
 * ֵ: 0x02001b08
 *
 * ���������ȷ���ÿռ�������Ӧ��¼��
 */
#define OS_ERRNO_NSM_FIND_FAILURE                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x08)

/**
 * �����ռ䴴���ṹ�嶨�塣
 *
 * �����ռ䴴���ṹ�嶨�塣
 */
typedef struct tagNsmModInfo
{
    VOID  *pStart;               /**< �����ռ���ʼ��ַ                              */
    UINT32 uwSize;               /**< �����ռ��ڴ�ռ��С                          */
}NSM_MOD_INFO_S;

/**
 * @ingroup  SRE_nsm
 * @brief ��ѯ���������¼��
 *
 * @par ����:
 * ͨ������ռ��uwSpaceID��������uwNameId���������ռ��в��Ҷ�Ӧ�ļ�¼����ͨ��ppAddr��puwSizeָ�뷵�����ַ�ʹ�С��
 *
 * @attention
 * <ul>
 * <li>�ޡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 * @param  ppAddr        [OUT] ����#VOID ** ���������������׵�ַ��
 * @param  puwSize       [OUT] ����#UINT32 *������������������ڴ�ռ��С��
 *
 * @retval #OS_ERRNO_NSM_FIND_FAILURE           0x02001b08�������ռ��ж�Ӧ��¼�����ڡ�
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #SRE_OK                              0x00000000����¼���ҳɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg | SRE_NSUnReg
 */
extern UINT32 SRE_NSFind (UINT32 uwSpaceID,  UINT32 uwNameId, VOID **ppAddr, UINT32 *puwSize);

/**
 * @ingroup  SRE_nsm
 * @brief ������������¼��
 *
 * @par ����:
 * ͨ�����������uwNameId�����������׵�ַpAddr�����������СuwSize���������ռ�uwSpaceID�����һ����¼��
 *
 * @attention
 * <ul>
 * <li>�ޡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 * @param  pAddr         [IN]  ����#VOID *  �����������׵�ַ��
 * @param  uwSize        [IN]  ����#UINT32  ��������������ڴ�ռ��С��
 *
 * @retval #OS_ERRNO_NSM_MEM_FULL               0x02001b05�������ռ�������
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #OS_ERRNO_NSM_OBJ_RENAME             0x02001b06�������ռ��м�¼��������
 * @retval #SRE_OK                              0x00000000����¼��ӳɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSUnReg
 */
extern UINT32 SRE_NSReg (UINT32 uwSpaceID, UINT32 uwNameId, VOID *pAddr, UINT32 uwSize);

/**
 * @ingroup  SRE_nsm
 * @brief ɾ�����������¼��
 *
 * @par ����:
 * ͨ�����������uwNameId���������ռ�uwSpaceID��ɾ����Ӧ�ļ�¼��
 *
 * @attention
 * <ul>
 * <li>�ޡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 *
 * @retval #OS_ERRNO_NSM_DEL_NOT_FIND           0x02001b07��ɾ��������¼ʱ����Ӧ��¼�����ڡ�
 * @retval #SRE_OK                              0x00000000����¼ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg
 */

extern UINT32 SRE_NSUnReg (UINT32 uwSpaceID, UINT32 uwNameId);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_NSM_H */

/**
 * History:
 * 2013-03-22 l00211012: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

