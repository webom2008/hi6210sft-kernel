/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_version.c
  �� �� ��   : ����
  ��    ��   : c61362
  ��������   : 2012��3��2��
  ����޸�   :
  ��������   : ������ϲ������װ�Ľӿڲ�
  �޸���ʷ   :
  1.��    ��   : 2012��3��2��
    ��    ��   : c61362
    �޸�����   : �½�Drvinterface.c

  2.��    ��   : 2013��2��19��
    ��    ��   : ��ϲ 220237
    �޸�����   : ��Drvinterface.c�������

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BSP.h"
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "board_diff.h"
#include "sys_config.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_VOID WriteChipVersion(BSP_U32 ulAddress, BSP_U32 ucType);
extern BSP_VOID GetPlatformInfo(unsigned int *u32PlatformInfo);
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : BSP_CheckModuleSupport
 ��������  : ��ѯģ���Ƿ�֧��
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 �������  : ��
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_MODULE_SUPPORT_E enRet = BSP_MODULE_SUPPORT;

    if(enModuleType >= BSP_MODULE_TYPE_BUTTOM)
    {
        return BSP_MODULE_UNSUPPORT;
    }

    switch(enModuleType)
    {
        case BSP_MODULE_TYPE_SD:
            break;
        case BSP_MODULE_TYPE_CHARGE:
#if (FEATURE_CHARGE == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_WIFI:
#if (FEATURE_WIFI == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_OLED:
#if (FEATURE_OLED == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HIFI:
#if (FEATURE_HIFI == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_POWER_ON_OFF:
#if (FEATURE_POWER_ON_OFF == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HSIC:
#if defined(FEATURE_HSIC_SLAVE)
#if (FEATURE_HSIC_SLAVE == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
#else
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HSIC_NCM:
            /*todo*/
#ifdef USB_HSIC_SUPPORT_NCM
            enRet = BSP_MODULE_SUPPORT;
#else
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_LOCALFLASH:
#if defined (FEATURE_FLASH_LESS)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        default:
            enRet = BSP_MODULE_UNSUPPORT;
            break;
    }

    return enRet;
#endif

#if (defined BSP_CORE_APP)

    BSP_MODULE_SUPPORT_E enRet = BSP_MODULE_SUPPORT;

    switch(enModuleType)
    {
        case BSP_MODULE_TYPE_LOCALFLASH:

            enRet = BSP_MODULE_SUPPORT;

            break;
        default:
            enRet = BSP_MODULE_UNSUPPORT;
            break;
    }

    return enRet;

#endif
}

/*****************************************************************************
 �� �� ��  : BSP_WriteChipVersion
 ��������  : д��оƬ�İ汾��
 �������  : ��
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
BSP_VOID BSP_WriteChipVersion(BSP_U32 ulAddress, BSP_U32 ucType)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    WriteChipVersion(ulAddress, ucType);
#endif

#if (defined BSP_CORE_APP)
    return;   /* ��׮ */
#endif
}

BSP_S32 BSP_GetSupportBands( BAND_INFO_T *pBandInfo)
{
    return 0;
}


BSP_BOOL BSP_HwIsSupportWifi(BSP_VOID)
{
    return 0;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

