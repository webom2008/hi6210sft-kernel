/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Das1lVTLVwJbptML4ycWpjrEkbMh3OL06DGhGXFikzg8HbeiVyOo88mX9I5Dc9VoN7/FA
dDZBLOkAOZQUczFmCGbWATOkniUECOQSSUKGDnlrQ/8hEdCcQeBJaHq2tsACHw==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_hw_ecc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������ECCģ���ⲿͷ�ļ��� \n
 */

 /**@defgroup SRE_ecc ECC
   *@ingroup SRE_inspect
 */

#ifndef _SRE_HW_ECC_H
#define _SRE_HW_ECC_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 *@ingroup SRE_ecc
 * �Ĵ�����Ϣ�ṹ
 *
 * ����:�쳣����ʱ����ļĴ�����Ϣ
 *
 * ע��:���¼Ĵ�������ȥ������ǰ׺��uw��������ӦоƬ�ֲ��еļĴ�������
 */
typedef struct tagTensilicaEccRegInfo
{
    UINT32 uwMESR;          /**< ECC״̬�Ĵ���                          */
    UINT32 uwMECR;          /**< ECCУ��Ĵ���                          */
    UINT32 uwMEVADDR;       /**< ECC��ַ�Ĵ���                          */
    UINT32 uwMEPC;          /**< ECC�쳣ʱPC                            */
    UINT32 uwMEPS;          /**< ECC�쳣ʱPS                            */
    UINT32 uwMESAVE;        /**< ECC�쳣�������ݻ���Ĵ���              */
}ECC_REGS_S;


/**
*@ingroup SRE_ecc
*@brief �û�ECC�ɾ�������Ĵ�����ԭ�Ͷ��塣
*
*@par ����: �ޡ�
*@attention
* <ul>
* <li>������SD6108��SD6181��SD6182��SD6157ƽ̨��</li>
* </ul>
*
*@param  pstRegs [IN] ����#ECC_REGS_S *��ָ��ECC�쳣�ӹܺ󱣴��ECC�Ĵ�����Ϣ�ṹ�塣
*
*@retval �ޡ�
*@par ����:
*<li>sre_hw_ecc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
*@since UniDSP V200R003C06
*@see �ޡ�
*/
typedef VOID (* OS_ECC_CORRECTED_HOOK)(ECC_REGS_S *pstRegs);

/**
 *@ingroup SRE_ecc
 *@brief ECCʹ�ܺ�����
 *
 *@par ����:
 *ʹ��ECCģ�鹦�ܡ�
 *@attention
 * <ul>
 * <li>������SD6108��SD6181��SD6182��SD6157ƽ̨��</li>
 * </ul>
 *
 *@param ��
 *
 *@retval #SRE_OK 0x00000000���ɹ���
 *
 *@par ����:
 * <ul><li>sre_hw_ecc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since UniDSP V100R001C02
 *@see SRE_EccDisable
 */
extern UINT32 SRE_EccEnable(VOID);

/**
 *@ingroup SRE_ecc
 *@brief ECC��ֹ������
 *
 *@par ����:
 *��ֹECCģ�鹦�ܡ�
 *@attention
 * <ul>
 * <li>������SD6108��SD6181��SD6182��SD6157ƽ̨��</li>
 * </ul>
 *
 *@param ��
 *
 *@retval #SRE_OK 0x00000000���ɹ���
 *@par ����:
 * <ul><li>sre_hw_ecc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since UniDSP V100R001C02
 *@see SRE_EccEnable
 */
 extern UINT32 SRE_EccDisable(VOID);



/**
 *@ingroup SRE_ecc
 *@brief ע���û�ECC�ɾ�������Ĵ����ӡ�
 *
 *@par ����:
 *ע���û�ECC�ɾ�������Ĵ����ӡ�
 *@attention
 * <ul>
 * <li>֧�ֹ����ظ�ע�ᡣ</li>
 * <li>�������ΪNULL��ɾ����ע�ṳ�ӡ�</li>
 * <li>������SD6108��SD6181��SD6182��SD6157ƽ̨��</li>
 * </ul>
 *
 *@param pfnHook [IN] ����#OS_ECC_CORRECTED_HOOK���û�ECC�ɾ�������Ĵ����Ӻ���ԭ�͡�
 *
 *@retval #SRE_OK 0x00000000���ɹ���
 *
 *@par ����:
 *<ul><li>sre_hw_ecc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since UniDSP V200R003C06
 *@see ��
 */
extern UINT32 SRE_EccCorrectedHookAdd(OS_ECC_CORRECTED_HOOK pfnHook);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* _SRE_HW_ECC_H */
/*
 * History: \n
 * 2009-7-24, q00144072, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
