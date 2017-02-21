
#ifndef __DRV_VERSION_H__
#define __DRV_VERSION_H__
#include "drv_global.h"
/* Ӳ����Ʒ��Ϣ���� */
#define HW_VER_INVALID              (BSP_U16)0xFFFF

/* Porting���P500����� */
#define HW_VER_PRODUCT_PORTING      (BSP_U16)0xFFFE
#define HW_VER_PRODUCT_PV500        (BSP_U16)0xFFFD

/* ���԰� */
#define HW_VER_PRODUCT_UDP          (BSP_U16)0xFFFC

/* Stick */
#define HW_VER_PRODUCT_E392S_U      (BSP_U16)HW_VER_INVALID
#define HW_VER_PRODUCT_E3276S_150   (BSP_U16)0x0201

/* E5 */
#define HW_VER_PRODUCT_E5_SBM       (BSP_U16)0x0001

/*E5776*/
#define HW_VER_PRODUCT_E5776_EM     (BSP_U16)0x0000

/*Epad, S10 101u */
#define HW_VER_PRODUCT_S10_101U     (BSP_U16)0x0401

/*Epad, S10 102u */
#define HW_VER_PRODUCT_S10_102U      (BSP_U16)0x0406

/*Epad, S10 LTE */
#define HW_VER_PRODUCT_S10_101L     (BSP_U16)0x0501

/*Epad, S10 Modem */
#define HW_VER_PRODUCT_S10_MODEM     (BSP_U16)0x0000

/*Epad, S10 Temp */
#define HW_VER_PRODUCT_S10_TEMP     (BSP_U16)0x0005

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

typedef struct {
    BSP_U32   bandGU;         	/*֧�ֵ�GUƵ��*/
    BSP_U32   bamdLTELow;         /*֧��LTEƵ�Σ�B1~B32*/
    BSP_U32   bamdLTEHigh;        /*֧��LTEƵ�Σ�B33~B64*/
}BAND_INFO_T;

typedef struct {
    BSP_U16  index;         /*Ӳ���汾����ֵ(��汾��1+��汾��2)�����ֲ�ͬ��Ʒ*/
    BSP_U16   hwIdSub;         /*Ӳ���Ӱ汾�ţ����ֲ�Ʒ�Ĳ�ͬ�İ汾*/
    BSP_CHAR* name;           /*�ڲ���Ʒ��*/
    BSP_CHAR* namePlus;       /*�ڲ���Ʒ��PLUS*/
    BSP_CHAR* hwVer;          /*Ӳ���汾����*/
    BSP_CHAR* dloadId;        /*������ʹ�õ�����*/
    BSP_CHAR* productId;      /*�ⲿ��Ʒ��*/
    BAND_INFO_T  band;            /*��Ʒ֧�ֵ�Ƶ��*/
    BAND_INFO_T  bandDiv;         /*��Ʒ֧�ֵķּ�*/
    BSP_CHAR reserve[4];      /*Ԥ��*/
}PRODUCT_INFO_T;

typedef struct  tagUE_SW_BUILD_VER_INFO_STRU
{
    BSP_U16 ulVVerNo;        /* V���� */
    BSP_U16 ulRVerNo;        /*  R����*/
    BSP_U16 ulCVerNo;        /* C����*/
    BSP_U16 ulBVerNo;         /* B����*/
    BSP_U16 ulSpcNo;          /* SPC����*/
    BSP_U16 ulCustomVer;     /* �ͻ��趨�Ʋ���, ���Ӳ���ӿڵ�8bit PCB��,��8bitHW��*/
    BSP_U32 ulProductNo;     /* such as porting,CPE, ... */
    BSP_S8 acBuildDate[BUILD_DATE_LEN];  /* build����,*/
    BSP_S8 acBuildTime[BUILD_TIME_LEN];  /* buildʱ��*/
} UE_SW_BUILD_VER_INFO_STRU; /* �ڲ��汾*/

/* ��ǰ�汾�Ƿ�֧��ĳ��ģ�� */
typedef enum tagBSP_MODULE_SUPPORT_E
{
    BSP_MODULE_SUPPORT     = 0,
    BSP_MODULE_UNSUPPORT   = 1,
    BSP_MODULE_SUPPORT_BUTTOM
}BSP_MODULE_SUPPORT_E;

/* ��ѯ��ģ������ */
typedef enum tagBSP_MODULE_TYPE_E
{
    BSP_MODULE_TYPE_SD = 0x0,
    BSP_MODULE_TYPE_CHARGE,
    BSP_MODULE_TYPE_WIFI,
    BSP_MODULE_TYPE_OLED,
    BSP_MODULE_TYPE_HIFI,
    BSP_MODULE_TYPE_POWER_ON_OFF,
    BSP_MODULE_TYPE_HSIC,
    BSP_MODULE_TYPE_HSIC_NCM,
    BSP_MODULE_TYPE_LOCALFLASH,

    BSP_MODULE_TYPE_BUTTOM
}BSP_MODULE_TYPE_E;

typedef enum{
     BOARD_TYPE_LTE_ONLY    = 0,
     BOARD_TYPE_GUL
}BOARD_TYPE_E;

typedef enum{
     BOARD_TYPE_BBIT        = 0,
     BOARD_TYPE_SFT,
     BOARD_TYPE_ASIC,
     BOARD_TYPE_MAX
}BOARD_ACTUAL_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     PV500_V9R1ES_CHIP,

     V8R1_PILOT_CHIP     = 0x8,
     V8R2_PILOT_CHIP

}BSP_CHIP_TYPE_E;

/*�������*/
typedef enum
{
    VER_BOOTLOAD = 0,
    VER_BOOTROM =1,
    VER_NV =2 ,
    VER_VXWORKS =3,
    VER_DSP =4 ,
    VER_PRODUCT_ID =5 ,
    VER_WBBP =6 ,
    VER_PS =7,
    VER_OAM =8,
    VER_GBBP =9 ,
    VER_SOC =10,
    VER_HARDWARE =11,
    VER_SOFTWARE =12,
    VER_MEDIA =13,
    VER_APP =14,
    VER_ASIC =15,
    VER_RF =16,
    VER_PMU =17,
    VER_PDM = 18,
    VER_PRODUCT_INNER_ID = 19,
    VER_INFO_NUM =20
}COMP_TYPE_I;

/*****************************************************************************
* �� �� ��  : BSP_HwGetVerMain
* ��������  : ��ȡ��Ʒ�汾��
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
BSP_U16 BSP_HwGetVerMain(BSP_VOID);

/*****************************************************************************
* �� �� ��  : BSP_GetProductName
* ��������  : ��ȡ��Ʒ����
* �������  : char* pProductName,�ַ���ָ�룬��֤��С��32�ֽ�
*             BSP_U32 ulLength,����������
* �������  : ��
* �� �� ֵ  : 0����ȷ����0: ʧ��
* �޸ļ�¼  :
*****************************************************************************/
BSP_S32 BSP_GetProductName (char * pProductName, unsigned int ulLength);

/*****************************************************************************
* �� �� ��  : BSP_GetBuildVersion
*
* ��������  :
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011-3-29 wuzechun creat
*
*****************************************************************************/
const UE_SW_BUILD_VER_INFO_STRU* BSP_GetBuildVersion(BSP_VOID);


/*****************************************************************************
* �� �� ��  : BSP_HwGetHwVersion
* ��������  : ��ȡӲ���汾����
* �������  : BSP_CHAR* pHwVersion,�ַ���ָ�룬��֤��С��32�ֽ�
* �������  : ��
* �� �� ֵ  : ��
* �޸ļ�¼  :
*****************************************************************************/
BSP_S32 BSP_HwGetHwVersion (char* pFullHwVersion, BSP_U32 ulLength);


/*****************************************************************************
* �� �� ��  : BSP_GetSupportBands
*
* ��������  : ��ȡ֧�ֵ�Ƶ��
*
* �������  : BAND_INFO_T *pBandInfo,Ƶ����Ϣ�ṹ��ָ��
* �������  :
*
 �� �� ֵ  : 0����ȷ����0: ʧ��
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 BSP_GetSupportBands( BAND_INFO_T *pBandInfo);

/*****************************************************************************
* �� �� ��  : BSP_HwIsSupportWifi
* ��������  : ��ӡӲ���汾��Ϣ,��׮
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
* ����˵��  : ��
*****************************************************************************/
BSP_BOOL BSP_HwIsSupportWifi(BSP_VOID);


/********************************************************************************************************
 �� �� ��  : getHwVersionIndex
 ��������  : ��ȡ��HKADC��ȡ��Ӳ��ID����ƴװ���Ӳ������ֵ
 �������  : ��
 �������  : Ӳ��ID������ֵ

 �� �� ֵ  : ��-1:  �����ɹ���
             -1������ʧ�ܡ�
 ע    ��  : �ýӿڽ���c���ṩ
********************************************************************************************************/
extern int getHwVersionIndex(void);

/*****************************************************************************
 �� �� ��  : getHwProductID
 ��������  :
 �������  : ��
 �������  : modem NV������ֵ
             �ֻ��壺����product ID
			 ���ֻ��壺����Ӳ��board ID
******************************************************************************/
extern int getHwProductID(void);
#define DRV_GET_HW_VERSION_INDEX()       getHwProductID()

/*****************************************************************************
 �� �� ��  : VerifySIMLock
 ��������  : �жϵ�ǰ�������Ƿ���ȷ .
 �������  : imei       - ����IMEI��
             unlockcode - ������
 �������  : �ޡ�
 �� �� ֵ  : 1��   �����ɹ�
             0:    ����ʧ��
*****************************************************************************/
extern int VerifySL(char* UnlockCode, char* Key);
#define DRV_CARDLOCK_MD5_VERIFY(unlockcode, imei)  VerifySL(unlockcode, imei)


extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()

/*****************************************************************************
 �� �� ��  : BSP_CheckModuleSupport
 ��������  : ��ѯģ���Ƿ�֧��
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 �������  : ��
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType);

#define DRV_GET_BATTERY_SUPPORT()   BSP_CheckModuleSupport(BSP_MODULE_TYPE_CHARGE)

#define DRV_GET_WIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_WIFI)

#define DRV_GET_SD_SUPPORT()        BSP_CheckModuleSupport(BSP_MODULE_TYPE_SD)

#define DRV_GET_OLED_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_OLED)

#define DRV_GET_HIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HIFI)

#define DRV_GET_HSIC_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HSIC)


/*****************************************************************************
 �� �� ��  : BSP_InitPlatformVerInfo
 ��������  : ��ʼ��оƬ�İ汾��
 �������  : ��
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
extern BSP_VOID BSP_InitPlatformVerInfo(BSP_VOID);
#define DRV_INIT_PLATFORM_VER() BSP_InitPlatformVerInfo()


extern BSP_S32  DRV_START_MODEGET(void);

/*****************************************************************************
 �� �� ��  : BSP_GetPlatformInfo
 ��������  : ��ȡоƬ�İ汾��
 �������  : ��
 �������  : u32PlatformInfo:оƬ�İ汾��
 �� �� ֵ  : void
 ע    ��  : �ýӿڽ���c���ṩ
*****************************************************************************/
extern BSP_VOID BSP_GetPlatformInfo(unsigned int *u32PlatformInfo);
#define DRV_GET_PLATFORM_INFO(u32PlatformInfo) BSP_GetPlatformInfo(u32PlatformInfo)


/*add by shenwei*/
/*****************************************************************************
* �� �� ��  : BSP_OM_GetBoardType
*
* ��������  : ��ȡ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP��������ö��
*
* ����˵��  : ��
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
static INLINE_ALWAYS BOARD_TYPE_E BSP_OM_GetBoardType(BSP_VOID)
{
	return BOARD_TYPE_GUL;
}
#else
BOARD_TYPE_E BSP_OM_GetBoardType(BSP_VOID);
#endif
#define DRV_GET_BOARDTYPE()   BSP_OM_GetBoardType()

/*****************************************************************************
* �� �� ��  : BSP_OM_GetBoardActualType
*
* ��������  : ��ȡ������������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP��������ö��
*             BBIT/SFT/ASIC
*
* ����˵��  : �ýӿڽ���C���ṩ��A��ͨ��DTS������ƽ̨
*
*****************************************************************************/
#if defined (BSP_CORE_APP)
BOARD_ACTUAL_TYPE_E BSP_OM_GetBoardActualType(BSP_VOID);
#else
extern BOARD_ACTUAL_TYPE_E g_eBoardActualType;
static INLINE_ALWAYS BOARD_ACTUAL_TYPE_E BSP_OM_GetBoardActualType(BSP_VOID)
{
	return g_eBoardActualType;
}
#endif
#define DRV_GET_BOARDACTUALTYPE()   BSP_OM_GetBoardActualType()

/*****************************************************************************
* �� �� ��  : BSP_OM_GetChipType
*
* ��������  : ��ȡоƬ����
*
* �������  : BSP_VOID
*
* �������  : ��
*
* �� �� ֵ  : оƬ����
*             PV500_CHIP:PV500оƬ
*             V7R1_CHIP: V7R1оƬ
*             V8R1_PILOT_CHIP: V8R1оƬ
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_CHIP_TYPE_E BSP_OM_GetChipType(BSP_VOID);
#define DRV_GET_CHIPTYPE()    BSP_OM_GetChipType()

/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ���ص�ǰ��Ʒ����
 �������   : ��
 �������   : ��
 �� �� ֵ   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern BSP_U32 BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_MemVersionCtrl
 ��������  : ����汾��д�ӿڡ�
 �������  : pcData����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��ַ��
                     ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ�ĵ�ַ��
             ucLength����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��С��
                       ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ���ַ�����������'\0'����
             ucType���汾��ϢID��
                     0�� BOOTLOAD��
                     1�� BOOTROM��
                     2�� NV��
                     3�� VXWORKS��
                     4�� DSP��
                     5�� CDROMISO��
                     6�� PHY��
                     7�� PS��
                     8�� COM��
                     9�� RF��
                     10��SOC��
                     11��HARDWARE��
                     12��SOFTWARE��
                     13��MEDIA��
                     14��APP��
                     15��INFO_NUM��
             ucMode��0����ȡָ��ID������汾��Ϣ��1��д��ָ��ID������汾��Ϣ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_MemVersionCtrl(signed char *pcData, unsigned char ucLength, unsigned char ucType, unsigned char ucMode);
#define DRV_MEM_VERCTRL(pcData,ucLength,ucType,ucMode)  \
			BSP_MNTN_MemVersionCtrl(pcData,ucLength,ucType,ucMode)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetFullHwVersion
 ��������  : Ӳ�������汾���ӿڡ�
 �������  : pFullHwVersion��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��׵�ַ��
             ulLength      ��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetFullHwVersion(char * pFullHwVersion,unsigned int ulLength);
#define  DRV_GET_FULL_HW_VER(pFullHwVersion,ulLength)  \
			BSP_MNTN_GetFullHwVersion(pFullHwVersion,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetProductIdInter
 ��������  : ��Ʒ���������汾���ӿڡ�
 �������  : pProductIdInter��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��׵�ַ��
             ulLength       ��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetProductIdInter(char * pProductIdInter, unsigned int ulLength);
#define  DRV_GET_PRODUCTID_INTER_VER(pProductIdInter,ulLength)  \
			BSP_MNTN_GetProductIdInter(pProductIdInter,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_VersionQueryApi
 ��������  : ��ѯ��������İ汾�š�
 �������  : ppVersionInfo��������İ汾��Ϣ��ַ��
 �������  : ucLength�������ص����ݵ��ֽ�����
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_VersionQueryApi(void ** ppVersionInfo, unsigned int * ulLength);
#define  DRV_VER_QUERY(ppVersionInfo,ulLength)  \
			BSP_MNTN_VersionQueryApi (ppVersionInfo,ulLength)

#endif

