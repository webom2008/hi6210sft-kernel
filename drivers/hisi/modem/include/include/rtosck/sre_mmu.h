/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dai4TlBVBFwOWTchUiOJxeE2wLdYyzQH7bxMqpVN8PSJBz2SkZe8/R3vqPuDVSL3eRcCf
iuACuPF273ydsJiweg0V5uYDiA/YMCCCeRuu/gYxAlc9blR458CAxlyMKocqZw==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_mmu.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������mmuģ��Ķ���ͷ�ļ��� \n
 */
 /**@defgroup SRE_mmu MMU
  *@ingroup SRE_kernel
 */

#ifndef _SRE_MMU_H
#define _SRE_MMU_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define MMU_VA_T VOID*
#define MMU_PA_T VOID*

/**
 * @ingroup SRE_mmu
 * �����룺�����ַ�������ַ�򳤶ȷ�page���롣
 *
 * ֵ: 0x02001201
 *
 * �������: �����������ַ�������ַ�������Ƿ�page���롣
 */
#define OS_ERRNO_MMU_NOT_PAGE_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1)

/**
 * @ingroup SRE_mmu
 * �����룺���ȷ�section���롣
 *
 * ֵ: 0x02001202
 *
 * �������: ��鳤���Ƿ�section���롣
 */
#define OS_ERRNO_MMU_NOT_SECT_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x2)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽һ��ҳ���ڴ档
 *
 * ֵ: 0x02001203
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_LEVEL1_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3)

/**
 * @ingroup SRE_mmu
 * �����룺ӳ�������ַ�ռ��Ѿ�ӳ����߲����Ѿ�ӳ�䡣
 *
 * ֵ: 0x02001204
 *
 * �������: �����ӳ��������ַ�ռ��Ƿ��Ѿ�ӳ��򲿷��Ѿ�ӳ�䡣
 */
#define OS_ERRNO_MMU_ADDR_MAPPED                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽����ҳ���ڴ档
 *
 * ֵ: 0x02001205
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_LEVEL2_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x5)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽ҳ��ӳ����Ϣ�ڴ档
 *
 * ֵ: 0x02001206
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_MAP_INFO_MEMORY                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x6)

/**
 * @ingroup SRE_mmu
 * �����룺ӳ����ڴ��������õ�ַ�����
 *
 * ֵ: 0x02001209
 *
 * �������: �����ε�ַ�ͳ����Ƿ����
 */
#define OS_ERRNO_MMU_ADDR_OVERFLOW                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x09)

/**
 * @ingroup SRE_mmu
 * �����룺�����ַδӳ�䡣
 *
 * ֵ: 0x02001210
 *
 * �������: ��������ַ�Ƿ�ӳ���MMU��ʼ����ַ�Ƿ�����ڴ�������е�ַ��
 */
#define OS_ERRNO_MMU_ADDR_NOT_MAPPED                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x10)

/**
 * @ingroup SRE_mmu
 * �����룺ҳ����ʱ�ڴ�ռ䲻�㡣
 *
 * ֵ: 0x02001211
 *
 * �������: ���ÿռ��㹻��0�ŷ�����
 */
#define OS_ERRNO_MMU_DEOPTIMIZE_FAIL                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x11)

/**
 * @ingroup SRE_mmu
 * �����룺ATTRIBUTE�������
 *
 * ֵ: 0x02001217
 *
 * �������: ���ATTRIBUTE�����Ƿ�Ϊ���Ժ��һ�֡�
 */
#define OS_ERRNO_MMU_ATTRIBUTE_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x17)

/**
 * @ingroup SRE_mmu
 * �����룺ACCESS�������
 *
 * ֵ: 0x02001218
 *
 * �������: ���д�����Ƿ���϶����ԣ�����ִ�������Ƿ���϶����ԡ�
 */
#define OS_ERRNO_MMU_ACCESS_ERR                                  SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x18)

/**
 * @ingroup SRE_mmu
 * �����룺��δ���
 *
 * ֵ: 0x0200121b
 *
 * �������: �����Ρ�
 */
#define OS_ERRNO_MMU_PARAM_INVALID                              SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1b)

/**
 * @ingroup  SRE_mmu
 * @brief ���ַתʵ��ַ��
 *
 * @par ����:
 * ���ַתʵ��ַ��
 *
 * @attention
 * <ul>
 * <li>83ƽ̨�����Ϊδӳ���ַ��������쳣��</li>
 * <li>AXƽ̨�����Ϊδӳ���ַ���᷵�ش����룬��ѯ���������ַΪ�����ַ����</li>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ���á�</li>
 * </ul>
 *
 * @param  pVAddr  [IN] ����#MMU_VA_T�������ַ��
 * @param  ppPAddr  [OUT] ����#MMU_PA_T��ת����������ַ��
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b�����Ϊ�ա�
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210����ַδӳ�䡣
 * @retval #SRE_OK                           0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuVA2PA(MMU_VA_T pVAddr, MMU_PA_T *ppPAddr);

/**
 * @ingroup  SRE_mmu
 * @brief ʵ��ַת���ַ��
 *
 * @par ����:
 * ʵ��ַת���ַ��
 *
 * @attention
 * <ul>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ�MMUģʽ�µ��á�</li>
 * <li>AXƽ̨�����Ϊδӳ���ַ���᷵�ش����룬��ѯ���������ַΪ�����ַ����</li>
 * </ul>
 *
 * @param  pPAddr  [IN] ����#MMU_PA_T�������ַ��
 * @param  ppVAddr [OUT] ����#MMU_VA_T��ת����������ַ��
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b�����Ϊ�ա�
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210����ַδӳ�䡣
 * @retval #SRE_OK                           0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuPA2VA(MMU_PA_T pPAddr, MMU_VA_T *ppVAddr);

/**
 * @ingroup  SRE_mmu
 * @brief ӳ�������ַ�������ַ��
 *
 * @par ����:
 * ���ݴ������pVStart��pPStart��uwLen�������⡢�����ַӳ�䣬������uwAttr�����ڴ����ԡ�
 *
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ�����е�ַӳ�䡣</li>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ���á�</li>
 * <li>AXƽ̨����κͷ����OSʹ�õ��ڴ���ӳ�䷽ʽ���������ַ�������ַһ�¡�</li>
 * <li>AXƽ̨��ַӳ��ʱ����uwVirtAddr��ʼ��page�������ӳ�䡣ĳһҳӳ�䲻�ɹ�ʱ���Ѿ�ӳ��ɹ��ĵ�ַ����ӳ���ϵ��</li>
 * <li>83ƽ̨��ַӳ��ʱ������ӳ��ɴ�ҳ��</li>
 * </ul>
 *
 * @param  pVStart       [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  pPStart       [IN] ����#MMU_PA_T��ӳ�������ַ��ʼ��ַ��
 * @param  uwLen         [IN] ����#UINT32��ӳ����ڴ��С��
 * @param  uwAttr        [IN] ����#UINT32���ڴ����ԣ�83ƽ̨uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_NOT_SECT_ALIGNED       0x02001202������������ȷ�section���롣
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203��δ���뵽һ��ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204�����������ַ�Ѿ�ӳ�����
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205��δ���뵽����ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206��δ���뵽ҳ��ӳ����Ϣ�ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MEM_FREE_SH_DAMAGED        0x02000311���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern UINT32 SRE_MmuAssign(MMU_VA_T pVStart, MMU_PA_T pPStart,
                                  UINT32 uwLen, UINT32 uwAttr);

#if(OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-�ɶ���
 */
#define OS_MMU_STATE_READ                                      0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-��д��
 *
 * �����Ժ�����ʱ��Ҫ����OS_MMU_STATE_READ����
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-��ִ�С�
 *
 * �����Ժ�����ʱ��Ҫ����OS_MMU_STATE_READ����
 */
#define OS_MMU_STATE_EXE                                       0x4

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-strong ordered��
 */
#define OS_MMU_STATE_STRONGLY_ORDERED                          0x8

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-shared device��
 */
#define OS_MMU_STATE_SHARED_DEVICE                             0x10

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-device��
 */
#define OS_MMU_STATE_DEVICE                                    0x20

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-����cache��
 */
#define OS_MMU_STATE_CACHE_OFF                                 0x40

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wbwa��
 */
#define OS_MMU_STATE_CACHE_WBWA                                0x80

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wbnwa��
 */
#define OS_MMU_STATE_CACHE_WBNWA                               0x100

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wtnwa��
 */
#define OS_MMU_STATE_CACHE_WTNWA                               0x200

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-shareable��
 */
#define OS_MMU_STATE_SHARE                                     0x400

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-ACCESS��
 */
#define OS_MMU_STATEMASK_ACCESS                                (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-Normal��
 */
#define OS_MMU_STATEMASK_NORMAL                                (OS_MMU_STATE_CACHE_OFF | OS_MMU_STATE_CACHE_WBWA | OS_MMU_STATE_CACHE_WBNWA | OS_MMU_STATE_CACHE_WTNWA)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-ATTRIBUTES��
 */
#define OS_MMU_STATEMASK_ATTRIBUTES                            (OS_MMU_STATEMASK_NORMAL | OS_MMU_STATE_STRONGLY_ORDERED | OS_MMU_STATE_SHARED_DEVICE | OS_MMU_STATE_DEVICE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-SHARE��
 */
#define OS_MMU_STATEMASK_SHARE                                 OS_MMU_STATE_SHARE

/**
 * @ingroup SRE_mmu
 * �����룺MMUģ���ʼ���ڴ�ӳ����Ϣ�ظ���
 *
 * ֵ: 0x02001207
 *
 * �������: ���MMU��ʼ���ڴ�ӳ����Ϣ�Ƿ��ظ���
 */
#define OS_ERRNO_MMU_INIT_ADDR_OVERLAPPED                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x7)

/**
 * @ingroup SRE_mmu
 * �����룺���Ȳ���ϲ�Ϊ��ҳ��
 *
 * ֵ: 0x02001212
 *
 * �������: �����������ַ�ͳ����Ƿ���ȷ��
 */
#define OS_ERRNO_MMU_OPTIMIZE_NO_NEED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x12)

/**
 * @ingroup SRE_mmu
 * �����룺0�ŷ���ӳ��������ַ�������ַ��һ�¡�
 *
 * ֵ: 0x02001214
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�����ַ�������ַ�Ƿ�һ�¡�
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_FLAT                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x14)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣδ��������0�ŷ�����Ϣ��
 *
 * ֵ: 0x02001215
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�Ƿ��������ӳ����Ϣ�С�
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_INCLUDE                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x15)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣ0�ŷ����ڴ����Բ�һ�¡�
 *
 * ֵ: 0x02001216
 *
 * �������: ����ʼ��ʱ�ڴ���������Ƿ�һ�¡�
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_DIFFERENT                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x16)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣ0�ŷ�������δ���óɿ�cache��
 *
 * ֵ: 0x02001219
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�����Ƿ����wbwa��wbnwa��
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_ERR                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x19)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣδ���û�ӳ��������ʼ��ַ��Ԫ�ظ������ó�0��
 *
 * ֵ: 0x0200121a
 *
 * �������: ���config��������MMU��ʼ��ӳ����Ϣ�Ƿ����ã����ӳ��������ʼ��ַ��Ԫ�ظ����Ƿ�����Ϊ0��
 */
#define OS_ERRNO_MMU_INIT_INFO_NOT_CONFIG                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1a)

/**
 * @ingroup SRE_mmu
 * mmu�û�������Ϣ�Ľṹ�嶨�塣
 *
 * mmu�û�������Ϣ��
 */
typedef struct tagVirtPhysMem
{
    UINT32 uwVirtualAddr;                                   /**< �����ַ */
    UINT32 uwPhysicalAddr;                                  /**< �����ַ */
    UINT32 uwLen;                                           /**< ����     */
    UINT32 uwInitialStateMask;                              /**< ״̬���� */
    UINT32 uwInitialState;                                  /**< ״̬     */
} VIRT_PHYS_MEM_S;

/**
 * @ingroup SRE_mmu
 * MMUģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����MMUģ�����������Ϣ��
 */
typedef struct tagMmuModInfo
{
    UINT32 uwMmuInitAddr;                                   /**< MMU��ʼ���ṹ�������׵�ַ       */
    UINT32 uwMmuInitNum ;                                   /**< MMU��ʼ���ṹ������Ԫ�ظ���     */
} MMU_MOD_INFO_S;

/**
 * @ingroup  SRE_mmu
 * @brief �ڴ��������á�
 *
 * @par ����:
 * ���������ַuwVirtAddr������uwLen���ڴ�����ΪuwState��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>����������0�ŷ����ڴ����ԡ�</li>
 * <li>uwLenΪ0ʱ�������ڴ��������á�</li>
 * <li>�ڴ���������ʱ����uwVirtAddr��ʼ��section��page����������á�ĳһҳ�ڴ��������ò��ɹ�ʱ���Ѿ����óɹ��ı����������ԡ�</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] ����#UINT32�������ַ��ʼ��ַ��
 * @param  uwLen       [IN] ����#UINT32�������ڴ����Գ��ȡ�
 * @param  uwStateMask [IN] ����#UINT32���ڴ��������룬����ƽ̨�����ã���ǰΪ��Ч�������ɺ��ԡ�
 * @param  uwState     [IN] ����#UINT32���ڴ����ԡ�
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210�����������ַδӳ�����
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MMU_DEOPTIMIZE_FAIL        0x02001211��ҳ����ʱ�ڴ治�㡣
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #SRE_OK                              0x00000000���ڴ��������óɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuStateSet(UINT32 uwVirtAddr, UINT32 uwLen, UINT32 uwStateMask, UINT32 uwState);

/**
 * @ingroup  SRE_mmu
 * @brief ʹ��MMU��
 *
 * @par ����:
 * ʹ��MMU��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * </ul>
 *
 * @param ��
 *
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210�������ַδӳ�䡣
 * @retval #SRE_OK                              0x00000000��MMUʹ�ܳɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuDisable
 */
extern UINT32 SRE_MmuEnable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief ����MMU��
 *
 * @par ����:
 * ����MMU��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * </ul>
 *
 * @param ��
 *
 * @retval #SRE_OK                              0x00000000��MMU���ܳɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuEnable
 */
extern UINT32 SRE_MmuDisable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief ҳ��ϲ���
 *
 * @par ����:
 * �ϲ�uwVirtAddr��ʼ������ΪuwLen���ڴ�ռ�ҳ��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>�ýӿڱ�����ε�ַ�ռ䣬�������ַ�������ڴ�����һ�µ��ڴ���кϲ���</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] ����#UINT32���ϲ���ʼ��ַ��
 * @param  uwLen       [IN] ����#UINT32���ϲ����ȡ�
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201����ʼ��ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MMU_OPTIMIZE_NO_NEED       0x02001212�����Ȳ���ϲ�Ϊ��ҳ��
 * @retval #SRE_OK                              0x00000000���ϲ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuOptimize(UINT32 uwVirtAddr, UINT32 uwLen);

/************************************************HIDSP interface*************************************************/
#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)
/************************* Permission ����(���Խ������) *********************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-�ɶ���
 */
#define OS_MMU_STATE_READ                                      0x4

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-��д��
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-��ִ�С�
 */
#define OS_MMU_STATE_EXE                                       0x1

/**************************** Share����(Ϊ0��ʾ���ɹ���) *********************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ湲������-�ɹ���
 */
#define OS_MMU_STATE_SHARED                                    0x8

/*************************** Speculative ���� (Ϊ0��ʾ����Ͷ��)***************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�Ͷ������-��Ͷ����
 */
#define OS_MMU_STATE_SPEC                                      0x10

/***************************** Cache   ���� (���º�ֻ��ѡ��һ��)**************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-����cache����buffer��
 */
#define OS_MMU_STATE_NONCACHE_NONBUFFER                        0x0

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-����cache��buffer��
 */
#define OS_MMU_STATE_NONCACHE_BUFFERABLE                       0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-writeback,no allocate��
 */
#define OS_MMU_STATE_WRITEBACK_NOALLOC                         0x3

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-writeback, writeallocate��
 */
#define OS_MMU_STATE_WRITEBACK_ALLOC                           0x7

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-writethrough��
 */
#define OS_MMU_STATE_WRITETHROUGH                              0x2

/**
 * @ingroup SRE_mmu
 * TLB��Ч����ʱָ������Ч��ʽ:ҳ��Ч��context��Ч����ЧALL.
 *
 * TLB��Ч��ʽ��
 */
typedef enum
{
    NON_INV     = 0      ,              /**< none opreation   */
    PAGE_INV    = 1      ,              /**< page invalidate    */
    CONTEXT_INV = 2      ,              /**< context invalidate */
    ALL_INV     = 3      ,              /**< all invalidate     */
    RESERVED    = 4
}OS_TLB_INV_POLICY;

/**
 * @ingroup SRE_mmu
 * MMU��3��ģʽ:BYPASSģʽ��MMUģʽ��BACKDOORģʽ.
 *
 * MMUģʽ��
 */
typedef enum
{
    SYS_MODE_BYPASS     = 0b00,         /**< BYPASSģʽ*/
    SYS_MODE_MMU        = 0b01,         /**< MMUģʽ*/
    SYS_MODE_BACKDOOR   = 0b11          /**< BACKDOORģʽ*/
}OS_SYS_MODE_E;


/**
 * @ingroup SRE_mmu
 * MMU��8��ӳ���С��ʽ:4K��8K��16K��64K��256K��1M��4M��16M.
 *
 * MMUӳ���ҳ��С��
 */
typedef enum
{
    MMU_PAGE_4K    = 0b0000,
    MMU_PAGE_8K    = 0b0001,
    MMU_PAGE_16K   = 0b0010,
    MMU_PAGE_64K   = 0b0011,
    MMU_PAGE_256K  = 0b0100,
    MMU_PAGE_1M    = 0b0101,
    MMU_PAGE_4M    = 0b0110,
    MMU_PAGE_16M   = 0b0111,
    MMU_INVALID    = 0b1000,
}MMU_PAGE_SIZE_E;

/**
 * @ingroup SRE_mmu
 * TLB����������:L1 ITLB��L1 DTLB��L2 TLB.
 *
 * TLB���͡�
 */
typedef enum
{
    L1_ITLB         ,            /**< L1_ITLB*/
    L1_DTLB         ,            /**< L1_DTLB*/
    L2_TLB                       /**< L2_TLB */
}OS_TLB_TYPE;

/**
 * @ingroup SRE_mmu
 * һ��TLB�������ֶ�.
 *
 * һ��TLB�������ֶ�.
 */
typedef struct tagL1TlbVirInput
{
    UINT32          uwContextID : 8;
    MMU_PAGE_SIZE_E uwPageSize  : 4;
    UINT32          uwVirAddr   : 20;
}L1_TLB_VIR_INPUT_S;

/**
 * @ingroup SRE_mmu
 * һ��ITLB�������ֶ�.
 *
 * һ��TLB�������ֶ�.
 */
typedef struct tagL1ITlbPhyInput
{
    UINT32                  uwEn     : 1;
    UINT32                  uwPermit : 3;
    UINT32                  uwRsv0   : 3;
    UINT32                  uwShare  : 1;
    UINT32                  uwSpec   : 1;
    UINT32                  uwCA     : 2;
    UINT32                  uwRsv1   : 1;
    UINT32                  uwPhyAddr: 20;
}L1_ITLB_PHY_INPUT_S;

typedef struct tagL1DTlbPhyInput
{
    UINT32                  uwEn     : 1;
    UINT32                  uwPermit : 3;
    UINT32                  uwRsv0   : 3;
    UINT32                  uwShare  : 1;
    UINT32                  uwSpec   : 1;
    UINT32                  uwCA     : 3;
    UINT32                  uwPhyAddr: 20;
}L1_DTLB_PHY_INPUT_S;

/**
 * @ingroup SRE_mmu
 * �����룺MMUģʽ���ô���
 *
 * ֵ: 0x0200121c
 *
 * �������: MMUģʽ����ֻ����BYPASS,MMU����ģʽ��
 */
#define OS_ERRNO_MMU_MODE_INVALID                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1c)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ���ݲ�ѯʱindex����
 *
 * ֵ: 0x0200121d
 *
 * �������: TLB��ѯʱindex��Ч��Χ��0~31��
 */
#define OS_ERRNO_MMU_TLB_INDEX_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1d)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ���ʹ���
 *
 * ֵ: 0x0200121e
 *
 * �������: TLB ���ʹ���ֻ����L1 ITLB,L1 DTLB,L2 TLB���֡�
 */
#define OS_ERRNO_MMU_TLB_TYPE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1e)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ��Ч���ԷǷ���
 *
 * ֵ: 0x0200121f
 *
 * �������: TLB ��Ч���ԷǷ���ֻ����PAGE_INV,LINE_INV,ALL_INV���֡�
 */
#define OS_ERRNO_MMU_TLB_INV_POLICY_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1f)

/**
 * @ingroup SRE_mmu
 * �����룺TLB way number�Ƿ���
 *
 * ֵ: 0x02001220
 *
 * �������: WAY numberֻ����0~7��
 */
#define OS_ERRNO_MMU_WAY_NUMBER_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x20)

/**
 * @ingroup SRE_mmu
 * �����룺��ȡ�Ķ�Ӧindex��L1TLB������Ч��
 *
 * ֵ: 0x02001221
 *
 * �������: ȷ����index������ȷ�Լ���Ӧ��TLB����δ����Ч�����滻��
 */
#define OS_ERRNO_MMU_TLB_DATA_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x21)

/**
 * @ingroup SRE_mmu
 * �����룺Page Size�Ƿ���
 *
 * ֵ: 0x02001222
 *
 * �������: �޸�Page Size��
 */
#define OS_ERRNO_MMU_PAGE_SIZE_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x22)

/**
 * @ingroup SRE_mmu
 * �����룺SYSTEM MODE�Ƿ���
 *
 * ֵ: 0x02001223
 *
 * �������: ֻ��ΪSUPER_MODE����USER_MODE��
 */
#define OS_ERRNO_MMU_SYS_MODE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x23)

/**
 * @ingroup SRE_mmu
 * �����룺���õ��ڴ����ԷǷ���
 *
 * ֵ: 0x02001224
 *
 * �������: ʹ��OS�ṩ�����Ժ������ڴ�����ԡ�
 */
#define OS_ERRNO_MMU_PAGEMAP_STATE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x24)

/**
 * @ingroup SRE_mmu
 * �����룺�����ַ�������ַ�򳤶ȷ�page���롣
 *
 * ֵ: 0x02001225
 *
 * �������: �����������ַ�������ַ�������Ƿ�page���롣
 */
#define OS_ERRNO_MMU_NOT_PAGE_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x25)

/**
 * @ingroup SRE_mmu
 * �����룺ӳ����ڴ��������õ�ַ�����
 *
 * ֵ: 0x02001226
 *
 * �������: �����ε�ַ�ͳ����Ƿ����
 */
#define OS_ERRNO_MMU_ADDR_OVERFLOW                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x26)

/**
 * @ingroup SRE_mmu
 * �����룺MMUģʽ�£�ʵ��ַת���ַʧ�ܡ�
 *
 * ֵ: 0x02001227
 *
 * �������: MMUģʽ�£�ʵ��ַδ����ӳ�䡣
 */
#define OS_ERRNO_MMU_PA2VA_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x27)

/**
 * @ingroup SRE_mmu
 * �����룺��ַת���ӿڣ���������ַ�������ַ��4�ֽڶ��롣
 *
 * ֵ: 0x02001228
 *
 * �������: �����������ַ�������ַ�Ƿ�4�ֽڶ��롣
 */
#define OS_ERRNO_MMU_NOT_WORD_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x28)

/**
 * @ingroup SRE_mmu
 * �����룺����ҳ���ڴ治����
 *
 * ֵ: 0x02001229
 *
 * �������: �������ҳ��ռ�
 */
#define OS_ERRNO_MMU_SIZE_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x29)

/**
 * @ingroup SRE_mmu
 * �����룺L2TLB setindex number�Ƿ���
 *
 * ֵ: 0x02001230
 *
 * �������: setindexֻ����0~127��
 */
#define OS_ERRNO_MMU_SET_NUMBER_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x30)

/**
 * @ingroup  SRE_mmu
 * @brief ����ϵͳģʽ��
 *
 * @par ����:
 * ֧��MMU��BYPASS����ģʽ��
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  enSysMode  [IN] ����#UINT32��ϵͳģʽ��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_MmuModeSet(OS_SYS_MODE_E enSysMode);

/**
 * @ingroup  SRE_mmu
 * @brief ��ȡL1 ITLB���ݡ�
 *
 * @par ����:
 * ��ȡL1 ITLB���ݡ�
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  uwTlbIndx  [IN] ����#UINT32��TLB index, ��Χ��0~31
 * @param  pstL1TlbVir  [OUT] ����#L1_TLB_VIR_INPUT_S*, ITLB�����ַ��Ϣ
 * @param  pstL1ITlbPhy  [OUT] ����#L1_ITLB_PHY_INPUT_S*��ITLB�����ַ��Ϣ
 *
 * @retval #SRE_OK ��ȡ�ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_L1ITlbEntryRead(UINT32 uwTlbIndx, L1_TLB_VIR_INPUT_S *pstL1TlbVir, L1_ITLB_PHY_INPUT_S *pstL1ITlbPhy);

/**
 * @ingroup  SRE_mmu
 * @brief ��ȡL1 DTLB���ݡ�
 *
 * @par ����:
 * ��ȡL1 DTLB���ݡ�
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  uwTlbIndx     [IN] ����#UINT32��TLB index, ��Χ��0~31
 * @param  pstL1TlbVir   [OUT] ����#L1_TLB_VIR_INPUT_S*, DTLB�����ַ��Ϣ
 * @param  pstL1DTlbPhy  [OUT] ����#L1_DTLB_PHY_INPUT_S*��DTLB�����ַ��Ϣ
 *
 * @retval SRE_OK ��ȡ�ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_L1DTlbEntryRead(UINT32 uwTlbIndx, L1_TLB_VIR_INPUT_S *pstL1TlbVir, L1_DTLB_PHY_INPUT_S *pstL1DTlbPhy);

/**
 * @ingroup  SRE_mmu
 * @brief ��ЧL1 TLB��
 *
 * @par ����:
 * ��ЧL1 TLB��
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  enTlbType    [IN] ����#OS_TLB_TYPE��ITLB����DTLB����L2 TLB
 * @param  enInvPolicy  [IN] ����#OS_TLB_INV_POLICY��page inv,context inv,all inv
 * @param  uwVirAddr    [IN] ����#UINT32�������ַ,���page inv��ʽ��Ч
 * @param  uwContextID  [IN] ����#UINT32��context ID�����page inv��context inv��Ч
 *
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_TlbInv(OS_TLB_TYPE enTlbType , OS_TLB_INV_POLICY enInvPolicy,
                           UINT32 uwVirAddr , UINT32 uwContextID);

typedef struct tagPageMemAttr
{
    UINT32      enPermit : 3;
    UINT32      uwShare  : 1;
    UINT32      uwSpec   : 1;
    UINT32      enCA     : 3;
    UINT32      uwRsv    : 24;

}PAGE_MEM_ATTR_S;

/**
 * @ingroup  SRE_mmu
 * @brief ӳ�������ַ�������ַ��
 *
 * @par ����:
 * ���ݴ������uwVirtAddr��uwPhysAddr��enPageSize�������⡢�����ַӳ�䣬������pstAttr�����ڴ����ԡ�
 *
 * @attention
 * <ul>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>��ַӳ��ʱ��ÿ��ӳ��һҳ��enPageSize����Ϊ8��size֮һ��</li>
 * <li>uwTransTblAddrΪҳ���׵�ַ��ÿ��ҳ��Ϊ4M,�׵�ַΪ1M���롣/li>
 * </ul>
 *
 * @param  uwTransTblAddr  [IN] ����#UINT32��ҳ���׵�ַ��
 * @param  pVStart         [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  pPStart         [IN] ����#MMU_PA_T��ӳ�������ַ��ʼ��ַ��
 * @param  enPageSize      [IN] ����#MMU_PAGE_SIZE_E��ӳ��Page���͡�
 * @param  uwAttr          [IN] ����#UINT32���ڴ����ԣ�uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #SRE_OK         0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */

extern UINT32 SRE_MmuSingleMap(UINT32 uwTransTblAddr, MMU_VA_T pVStart, MMU_PA_T pPStart,
                            MMU_PAGE_SIZE_E enPageSize,  UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief ӳ�������ַ�������ַ��
 *
 * @par ����:
 * ӳ��������uwPageNum��page size��ͬ��ΪenPageSize��ҳ��������uwAttr�����ڴ����ԡ�
 *
 * @attention
 * <ul>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>��ַӳ��ʱ��enPageSize����Ϊ8��size֮һ��</li>
 * <li>uwTransTblAddrΪҳ���׵�ַ��ÿ��ҳ��Ϊ4M,�׵�ַΪ1M���롣/li>
 * </ul>
 *
 * @param  uwTransTblAddr  [IN] ����#UINT32��ҳ���׵�ַ��
 * @param  uwVirtAddr      [IN] ����#UINT32��ӳ�������ַ��ʼ��ַ��
 * @param  uwPhysAddr      [IN] ����#UINT32��ӳ�������ַ��ʼ��ַ��
 * @param  enPageSize      [IN] ����#MMU_PAGE_SIZE_E��ӳ���ҳ���͡�
 * @param  uwPageNum       [IN] ����#UINT32��ӳ���ҳ��Ŀ��
 * @param  uwAttr          [IN] ����#UINT32���ڴ����ԣ�uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuGroupMap(UINT32 uwTransTblAddr, MMU_VA_T pVStart, MMU_PA_T pPStart,
                               MMU_PAGE_SIZE_E enPageSize, UINT32 uwPageNum, UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief �ڴ��������á�
 *
 * @par ����:
 * ���û���ַΪuwTransTblAddr��ҳ�������ַuwVirtAddr������uwLen���ڴ�����ΪpstAttr��
 *
 * @attention
 * <ul>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>�ڴ���������ʱ����uwVirtAddr��ʼ��section��page����������á�ĳһҳ�ڴ��������ò��ɹ�ʱ���Ѿ����óɹ��ı����������ԡ�</li>
 * </ul>
 *
 * @param  uwTransTblAddr   [IN] ����#UINT32��ҳ���׵�ַ��
 * @param  uwVirtAddr       [IN] ����#UINT32�������ַ��ʼ��ַ��
 * @param  uwLen            [IN] ����#UINT32�������ڴ����Գ��ȡ�
 * @param  uwAttr           [IN] ����#UINT32���ڴ����ԣ�uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #SRE_OK          0x00000000���ڴ��������óɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuStateSet(UINT32 uwTransTblAddr,UINT32 uwVirtAddr, UINT32 uwLen, UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief Backdoorģʽ��ȡL2TLB����
 *
 * @par ����:
 * Backdoorģʽ��ȡL2TLB����
 *
 * @attention
 * <ul>
 * <li>�ڽ���backdoorģʽ֮ǰ��ϵͳ��Ҫ��������Ϊbypassģʽ</li>
 * </ul>
 *
 * @param  uwSetIndex       [IN] ����#UINT32��set index��
 * @param  uwWayIndex       [IN] ����#UINT32��way index��
 * @param  puwMmuPbaInfo    [OUT] ����#UINT32 *,read PBA ��
 * @param  puwMmuVbaInfo    [OUT] ����#UINT32 *,read VBA��
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuBackDoorGet(UINT32 uwSetIndex, UINT32 uwWayIndex, UINT32 *puwMmuPbaInfo, UINT32 *puwMmuVbaInfo);

typedef struct tagDefMmuMemAttr
{
    UINT32      uwShared     : 1;
    UINT32      uwNonDes     : 1;
    UINT32      uwCA         : 3;
    UINT32      uwRsv0       : 27;
}DEF_MMU_MEM_ATTR_S;
/**
 * @ingroup  SRE_mmu
 * @brief Data����Ĭ���������á�
 *
 * @par ����:
 * BYPASSģʽ�£�ȫ���ݿռ���Ч��
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  uwTrdID          [IN] ����#UINT32���߳�ID,0/1
 * @param  uwAttr           [IN] ����#UINT32��Ĭ�����ԣ�uwAttr��ЧbitλΪ(bit4-0)�� bit0:shareable ; bit1:speculative; bit4-2:cache attributes;
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_DataDefaultAttrSet(UINT32 uwTrdID, UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief Text����Ĭ���������á�
 *
 * @par ����:
 * BYPASSģʽ�£�ȫ����ռ���Ч��
 *
 * @attention
 * <ul>
 * <li>ϵͳ���봦��BYPASSģʽ��MMUģʽ�£�Ҫ�����еĴ������page table����ӳ��</li>
 * </ul>
 *
 * @param  uwAttr           [IN] ����#UINT32��Ĭ�����ԣ�uwAttr��ЧbitλΪ(bit4-0)�� bit0:shareable ; bit1:speculative; bit4-2:cache attributes;
 *
 * @retval #SRE_OK
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_TextDefaultAttrSet(UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief ����L2 TLB���ҵ�˳��
 *
 * @par ����:
 * ����L2 TLB���ҵ�˳��
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  uwOrdValue           [IN] ����#UINT32�����ȼ�˳��
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_L2TlbOrdSet(UINT32 uwOrdValue);

/**
 * @ingroup  SRE_mmu
 * @brief ����ҳ���׵�ַ
 *
 * @par ����:
 * ����super��user״̬��ҳ�����ַ
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  enMode           [IN] ����#OS_SYSTEM_MODE��SUPER����USERģʽ��
 * @param  uwBaseAddr       [IN] ����#UINT32��ҳ�����ַ��
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
typedef enum
{
    SUPER_MODE         ,
    USER_MODE
}OS_SYSTEM_MODE;
extern UINT32 SRE_MmuBaseSet(OS_SYSTEM_MODE enMode, UINT32 uwBaseAddr);

/**
 * @ingroup  SRE_mmu
 * @brief ����ITLB Context ID Mask
 *
 * @par ����:
 * ����ITLB Context ID Mask
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  uwMsk       [IN] ����#UINT32��Context ID Mask��
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_ITlbCIdMsk(UINT32 uwCidMsk);

/**
 * @ingroup  SRE_mmu
 * @brief ���ö���ҳ�����ַ�ʹ�С
 *
 * @par ����:
 * ����ITLB Context ID Mask
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  uwBaseAddr       [IN] ����#UINT32������ҳ�����ַ
 * @param  uwSize           [IN] ����#UINT32����С
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuL2ArgSet(UINT32 uwBaseAddr, UINT32 uwSize);

/**
 * @ingroup  SRE_mmu
 * @brief TLB Preload & preload lock & unlock��
 *
 * @par ����:
 * TLB Preload & preload lock & unlock
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  enTlbType    [IN] ����#OS_TLB_TYPE��ITLB����DTLB
 * @param  uwVirAddr    [IN] ����#UINT32�������ַ
 *
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
OS_SEC_ALW_INLINE INLINE  UINT32 SRE_TlbPreload(UINT32 uwVirAddr)
{
    __asm__ __volatile__("mmupf@agl %0 " :: "r"(uwVirAddr));

    return SRE_OK;
}

OS_SEC_ALW_INLINE INLINE UINT32 SRE_TlbPreloadLock(UINT32 uwVirAddr)
{
    __asm__ __volatile__("mmupflck@agl %0 "  :: "r"(uwVirAddr));

    return SRE_OK;
}

OS_SEC_ALW_INLINE INLINE UINT32 SRE_TlbUnlock(UINT32 uwVirAddr)
{
    __asm__ __volatile__("mmuulck@agl %0 "  :: "r"(uwVirAddr));

    return SRE_OK;
}
typedef  struct tagSecAttr{
    UINT32 uwSecVA;
    UINT32 uwSecPA;
    UINT32 uwSecSize;
    UINT32 uwSecAttr;
}SEC_ATTR_S;

typedef  struct tagSlaveCoreBootPara
{
    UINT32  uwCoreId;               /*  ȡֵ��Χ0~33*/
    UINT32  uwCIDR;                 /*  context ID ��8bit��Ч*/
    UINT32  uwPageTblAddr;
    UINT32  uwPageL2TblAddr;
    UINT32  uwPageL2Len;
    BOOL    bMmuMapFlag;            /* TRUE:��ʾ��Ҫ���ú���vector heap stack secinfo;False:�û�ͨ���ڴ���ط�ʽ���ã��˴���������*/
    SEC_ATTR_S  stIntVectorSec;     /*�߳������������ã�ָ��vecbase����12bit����*/
    SEC_ATTR_S  stSysHeapSec;
    SEC_ATTR_S  stSysStackSec;      /*�߳������������ã�ָ��SP=��ʼ��ַ+size*/
    UINT32 uwSecNum;                /*stSecInfo�ṹ�����*/
    SEC_ATTR_S  stSecInfo[0];
}SLAVE_CORE_BOOTPARA_S;

/**
 * @ingroup  SRE_mmu
 * @brief
 *
 * @par ����:������������������
 *
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  pstCoreBootPara    [IN] ����#OS_TLB_TYPE��ITLB����DTLB
 *
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_SlavePreBoot(SLAVE_CORE_BOOTPARA_S  *pstCoreBootPara);

/**
 * @ingroup  SRE_mmu
 * @brief
 *
 * @par ����:�����˺�ΪuwCoreId�ĺ˵�wakeup�ж�
 *
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  uwCoreId    [IN] ����#UINT32���˺ţ������̺߳�
 * @param  uwWakeupIntPri    [IN] ����#UINT32���ж����ȼ�
 *
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_CoreWakeUp(UINT32 uwCoreId,  UINT32 uwWakeupIntPri);

/**
 * @ingroup  SRE_mmu
 * @brief
 *
 * @par ����: �����˺�ΪuwCoreId�ĺ˵�boot�ж�
 *
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @param  uwCoreId    [IN] ����#UINT32���˺ţ������̺߳�
 * @param  uwWakeupIntPri    [IN] ����#UINT32���ж����ȼ�
 *
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_CoreBootInt(UINT32 uwCoreId,  UINT32 uwWakeupIntPri);


#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MMU_H */

/**
 * History:
 * 2013-02-18 h00213062: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

