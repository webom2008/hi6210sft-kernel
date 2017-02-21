/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3DaoJKLOkHnsHop7n+e+dpNEZbcEUANAhREkDhyi9k9JiD8innzTXtzoD3G9IhJgTHUk7k
ETG2NI2nqdzZcPC3BMtcGARKklVHocpE39IMocylCJhLsvboEP3ws+F39pdOlQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_hw.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ�����ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_hw ��ʵ��֧��
   *@ingroup SRE_kernel
 */

#ifndef _SRE_HW_H
#define _SRE_HW_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_hw
 * �ڴ�����룺����ʵ����������ʱ����Ĳ���ΪNULL
 *
 * ֵ: 0x02002000
 *
 * �������: ��ȷ������Ĳ�����ΪNULL
 */
#define OS_ERRNO_HW_START_PARAM_CFG_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x00)

/**
 * @ingroup SRE_hw
 * �ڴ�����룺����ʵ����������ʱ��ʵ���ڸ��������ò�һ��
 *
 * ֵ: 0x02002001
 *
 * �������: ��ȷ��ʵ�������к����õ���������һ��
 */
#define OS_ERRNO_HW_START_PARAM_INCONSISTENT                  SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x01)

/**
 * @ingroup SRE_hw
 * �ڴ�����룺������ʱ��δ��#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ���������������
 *
 * ֵ: 0x02002002
 *
 * �������: ��ȷ������#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ���������������
 */
#define OS_ERRNO_HW_START_PARAM_NOT_CFG                       SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x02)

/**
 * @ingroup SRE_hw
 * �ڴ�����룺�豸ID����
 *
 * ֵ: 0x02002003
 *
 * �������: �豸ID��ȡֵ[0 ,2]
 */
#define OS_ERRNO_HW_DEVICE_ID_ERR                             SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x03)

/**
 * @ingroup SRE_hw
 * �ڴ�����룺uwCommVmid�����������
 *
 * ֵ: 0x02002004
 *
 * �������: COMM VMID��ȡֵ��Χ[0 ,7]
 */
#define OS_ERRNO_HW_VMID_ID_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x04)

/**
 * @ingroup SRE_Hw
 * Ӳ�������Ϣ��
 *
 */
typedef struct tagHwModInfo
{
    UINT32 uwGiccCtrlOffset;      /**< оƬGIC CPU Interface��ַƫ�ƣ�Cortex_AXϵ��оƬ��Ч */
} HW_MOD_INFO_S;

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**@ingroup SRE_Hw
 * ���������ṹ�嶨��
 */

typedef struct tagStartParam
{
    UINT16 usInstID;              /**< ʵ��ID���������������������չ             */
    UINT16 usReserved;            /**< ���� */
    UINT16 usGHwSemStartID;       /**< ��ʵ�������Global Hwsem��ʼ����ID */
    UINT16 usGHwSemNum;           /**< ��ʵ�������Global Hwsem����*/
    UINT16 usCpuLHwSemStartID;    /**< ��ʵ�������CPU(SD6183 DSP2) cluster Local Hwsem��ʼ����ID */
    UINT16 usCpuLHwSemNum;        /**< ��ʵ�������CPU(SD6183 DSP2) cluster Local Hwsem����*/
    UINT16 usHacLHwSemStartID;    /**< ��ʵ�������HACCC cluster Local Hwsem��ʼ����ID */
    UINT16 usHacLHwSemNum;        /**< ��ʵ�������HACCC cluster Local Hwsem����*/
    UINT16 usDsp0LHwSemStartID;   /**< ��ʵ�������DSP0 cluster Local Hwsem��ʼ����ID */
    UINT16 usDsp0LHwSemNum;       /**< ��ʵ�������DSP0 cluster Local Hwsem����*/
    UINT16 usDsp1LHwSemStartID;   /**< ��ʵ�������DSP1 cluster Local Hwsem��ʼ����ID */
    UINT16 usDsp1LHwSemNum;       /**< ��ʵ�������DSP1 cluster Local hwsem����*/
    UINT16 usNorGMsgmBufStart;    /**< ��ʵ�������Global MSGM��ͨ��Ϣ������ʼ��ַ(SD6183��Ч)*/
    UINT16 usNorGMsgmBufLen;      /**< ��ʵ�������Global MSGM��ͨ��Ϣ���峤��(SD6183��Ч)*/
    UINT16 usNorLMsgmBufStart;    /**< ��ʵ�������Local MSGM��ͨ��Ϣ������ʼ��ַ(SD6183��Ч)*/
    UINT16 usNorLMsgmBufLen;      /**< ��ʵ�������Local MSGM��ͨ��Ϣ���峤��(SD6183��Ч)*/
 } START_PARAM_S;
#elif ((OS_HARDWARE_PLATFORM == OS_HIDSP))

/**@ingroup SRE_Hw
 * ���������ṹ�嶨��
 */
typedef struct tagStartParam
{
    UINT16 usInstID;             /**< ʵ��ID���������������������չ     */
    UINT16 usReserved;           /**< ���� */
    UINT16 usGHwSemStartID;      /**< ��ʵ�������Global Hwsem��ʼ����ID */
    UINT16 usGHwSemNum;          /**< ��ʵ�������Global Hwsem����*/
    UINT16 usDsp0LHwSemStartID;  /**< ��ʵ�������DSP cluster0 Local Hwsem��ʼ����ID */
    UINT16 usDsp0LHwSemNum;      /**< ��ʵ�������DSP cluster0 Local Hwsem����*/
    UINT16 usDsp1LHwSemStartID;  /**< ��ʵ�������DSP cluster1 Local Hwsem��ʼ����ID */
    UINT16 usDsp1LHwSemNum;      /**< ��ʵ�������DSP cluster1 Local Hwsem����*/
    UINT16 usDsp2LHwSemStartID;  /**< ��ʵ�������DSP cluster2 Local Hwsem��ʼ����ID */
    UINT16 usDsp2LHwSemNum;      /**< ��ʵ�������DSP cluster2 Local Hwsem����*/
    UINT16 usHacLHwSemStartID;   /**< ��ʵ�������HACCC cluster Local Hwsem��ʼ����ID */
    UINT16 usHacLHwSemNum;       /**< ��ʵ�������HACCC cluster Local Hwsem����*/
 } START_PARAM_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_HIDSP) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
|| (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup  SRE_hw
 * @brief ����ʵ������������
 *
 * @par ����:
 * ����pstStartParam����������ʵ������������OS���ݸ����ý�Hwsem��MSGM������Դ��ʵ�����зֶι���
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6182/SD6157/SD6183ƽ̨��</li>
 * <li>�û�������#SRE_HardBootInit������DDR������غ���øú����������ʼ��ʧ�ܡ�</li>
 * <li>ʵ�������õ���Դ�ֶβ����ص����úϷ������û���֤��</li>
 * <li>OS�̶�ʹ��0��Ӳ���ź�����Ϊʵ���以�⣬�û�����ͨ����API��0��Ӳ���ź������ø�OS��</li>
 * </ul>
 *
 * @param  pstStartParam   [IN] ����#START_PARAM_S������������
 *
 * @retval #OS_ERRNO_HW_START_PARAM_CFG_NULL          0x02002000������ʵ����������ʱ����Ĳ���ΪNULL��
 * @retval #OS_ERRNO_HW_START_PARAM_INCONSISTENT      0x02002001������ʵ����������ʱ��ʵ���ڸ��������ò�һ�¡�
 * @retval #OS_ERRNO_HW_START_PARAM_NOT_CFG           0x02002002��������ʱ��δ��#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ��������������á�
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_START_ID_INVALID   0x02002425������ʵ����������ʱ�����ȫ��Ӳ���ź�����ʼID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_NUM_INVALID        0x02002426������ʵ����������ʱ�����ȫ��Ӳ���ź��������Ƿ�
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_REGION_INVALID     0x02002427������ʵ����������ʱ���õ�ȫ��Ӳ���ź�������Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_START_ID_INVALID 0x02002428������ʵ����������ʱ����ľֲ�Ӳ���ź�����ʼID����
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_NUM_INVALID      0x02002429������ʵ����������ʱ����ľֲ�Ӳ���ź��������Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_REGION_INVALID   0x0200242a������ʵ����������ʱ���õľֲ�Ӳ���ź�������Ƿ���
 * @retval #OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN   0x02002b3f������ʵ����������ʱ�����MSGM������ʼ��ַ�򳤶ȷ�4�ֽڶ��롣
 * @retval #OS_ERRNO_MSGM_CFG_START_ADDR_INVALID      0x02002b40������ʵ����������ʱ�����MSGM������ʼ��ַ�Ƿ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID       0x02002b41������ʵ����������ʱ�����MSGM���г��ȷǷ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID    0x02002b42������ʵ����������ʱ�����MSGM������ʼ��ַ�ͳ��Ⱦ���������Ƿ���
 * @retval #SRE_OK                                    0x00000000�������������óɹ���
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 **/
extern UINT32 SRE_StartParamCfg(START_PARAM_S  *pstStartParam);
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup sre_hwsem
 * �豸���
 */
typedef enum _tagOsDevice
{
    OS_DEVICE_HWSEM_ID = 0,/**< Ӳ���ź���ID*/
    OS_DEVICE_MSGM_ID = 1, /**< MSGM ID     */
    OS_DEVICE_TIMER_ID = 2 /**< ȫ�ֶ�ʱ��ID*/
} OS_DEVICE_TYPE_E;

/**
 * @ingroup SRE_hw
 * @brief Comm VMID���ýӿڡ�
 *
 * @par ����:
 * ����COMM VMID��ʹ��VMID��顣
 * @attention
 * <ul>
 * <li>������SD6183ƽ̨��</li>
 * </ul>
 *
 * @param uwDeviceID    [IN] ����#UINT32���豸ID��ȡֵ��Χ[0,2],����ο�#OS_DEVICE_TYPE_E��
 * @param uwCommVmid    [IN] ����#UINT32��Comm Vmidֵ��ȡֵ��Χ[0,7]��
 *
 * @retval #OS_ERRNO_HW_VMID_ID_ERR      0x02002004��uwCommVmid�����������
 * @retval #OS_ERRNO_HW_DEVICE_ID_ERR    0x02002003���豸ID����
 * @retval #SRE_OK      0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_CommVmidSet(UINT32 uwDeviceID, UINT32 uwCommVmid);
#endif
#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_hw
 * @brief ARM��DSB����
 *
 * @par ����:
 * ARM��DSB���ܣ��ȴ��ڴ������ϣ��ڴ����δ����֮ǰ��CPU������������ڴ�ͼĴ�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DMB
 **/
#ifndef _WIN32
#define SRE_DSB() OS_EMBED_ASM("dsb")
#else
#define SRE_DSB()
#endif

/**
 * @ingroup  SRE_hw
 * @brief ARM��DMB����
 *
 * @par ����:
 * ARM��DMB���ܣ��ȴ��ڴ������ϣ��ڴ����δ����֮ǰ��CPU������������ڴ档
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DSB
 **/
#ifndef _WIN32
#define SRE_DMB() OS_EMBED_ASM("dmb")
#else
#define SRE_DMB()
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */

/**
 * History:
 * 2013-05-10 w00181871: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

