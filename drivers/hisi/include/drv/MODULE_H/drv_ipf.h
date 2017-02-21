
#ifndef __DRV_IPF_H__
#define __DRV_IPF_H__

/**************************************************************************
  ͷ�ļ�����
**************************************************************************/
#include "DrvInterface.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**************************************************************************
  �궨��
**************************************************************************/
/*�����붨��*/
#define IPF_SUCCESS                         BSP_OK
#define IPF_ERROR                           BSP_ERROR
#define BSP_ERR_IPF_INVALID_PARA            BSP_DEF_ERR(BSP_MODU_IPF, 0)
#define BSP_ERR_IPF_BDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 1)
#define BSP_ERR_IPF_CDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 2)
#define BSP_ERR_IPF_RDQ_EMPTY               BSP_DEF_ERR(BSP_MODU_IPF, 3)
#define BSP_ERR_IPF_FILTER_NOT_ENOUGH       BSP_DEF_ERR(BSP_MODU_IPF, 4)
#define BSP_ERR_IPF_NOT_INIT                BSP_DEF_ERR(BSP_MODU_IPF, 5)
#define BSP_ERR_IPF_RESUME_TIMEOUT          BSP_DEF_ERR(BSP_MODU_IPF, 6)
#define BSP_ERR_IPF_SEMTAKE_TIMEOUT         BSP_DEF_ERR(BSP_MODU_IPF, 7)
#define BSP_ERR_IPF_ADQ0_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 8)
#define BSP_ERR_IPF_ADQ1_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 9)
#define BSP_ERR_IPF_ALLOC_MEM_FAIL          BSP_DEF_ERR(BSP_MODU_IPF, 10)
#define BSP_ERR_IPF_CCORE_RESETTING         BSP_DEF_ERR(BSP_MODU_IPF, 11)
#define BSP_ERR_IPF_INVALID_DLRD            BSP_DEF_ERR(BSP_MODU_IPF, 12)
#define BSP_ERR_IPF_INVALID_ULRD            BSP_DEF_ERR(BSP_MODU_IPF, 13)

#define IPF_ULBD_DESC_SIZE         64   /* ����BD���� */
#define IPF_ULRD_DESC_SIZE         64   /* ����BD���� */
#define IPF_DLBD_DESC_SIZE         64   /* ����BD���� */
#define IPF_DLRD_DESC_SIZE         64   /* ����BD���� */
#define IPF_ULAD0_DESC_SIZE        64   /* ����ADQ0��AD���� */
#define IPF_ULAD1_DESC_SIZE        64   /* ����ADQ1��AD���� */
#define IPF_DLAD0_DESC_SIZE        64   /* ����ADQ0��AD���� */
#define IPF_DLAD1_DESC_SIZE        64   /* ����ADQ1��AD���� */
#define IPF_DLCD_DESC_SIZE         1024 /* �Ϻ����� */
#define IPF_FILTER_CHAIN_MAX_NUM   8    /* IPF�������������� */

/**************************************************************************
  ö�ٶ���
**************************************************************************/
/*ADQʹ��ö��ֵ*/
typedef enum tagIPF_ADQEN_E
{
    IPF_NONE_ADQ_EN = 0,    /*��ʹ��ADQ*/
    IPF_ONLY_ADQ0_EN = 1,   /*��ʹ��ADQ0*/
    IPF_ONLY_ADQ1_EN = 2,   /*��ʹ��ADQ1*/
    IPF_BOTH_ADQ_EN = 3,    /*ʹ��ADQ0��ADQ1*/

    IPF_ADQEN_BUTT          /*�߽�ֵ*/
}IPF_ADQEN_E;

/*ADSize*/
typedef enum tagIPF_ADSIZE_E
{
    IPF_ADSIZE_32 = 0,  /* AD���д�СΪ32 */
    IPF_ADSIZE_64,      /* AD���д�СΪ64 */
    IPF_ADSIZE_128,     /* AD���д�СΪ128 */
    IPF_ADSIZE_256,     /* AD���д�СΪ256*/

    IPF_ADSIZE_MAX
}IPF_ADSIZE_E;

/* ����ģʽ */
typedef enum tagIPF_MODE_E
{
    IPF_MODE_FILTERANDTRANS = 0,    /* ���˲����� */
    IPF_MODE_FILTERONLY,            /* ֻ���� */
    IPF_MODE_TRANSONLY,             /* ֻ���� */

    IPF_MODE_MAX                    /* �߽�ֵ */
}IPF_MODE_E;

/* BURST��󳤶� */
typedef enum tagIPF_BURST_E
{
    IPF_BURST_16 = 0,           /* BURST16 */
    IPF_BURST_8,                /* BURST8 */
    IPF_BURST_4,                /* BURST4 */

    IPF_BURST_MAX               /* BURST4 ���Ĵ���һ�� */
}IPF_BURST_E;

/*ADQ�ձ�־ö��ֵ*/
typedef enum tagIPF_ADQ_EMPTY_E
{
    IPF_EMPTY_ADQ0 = 0x1,                               /*�̰�����ADQ0��*/
    IPF_EMPTY_ADQ1 = 0x2,                               /*��������ADQ1��*/
    IPF_EMPTY_ADQ = (IPF_EMPTY_ADQ0+IPF_EMPTY_ADQ1),    /*�������ж���*/

    IPF_EMPTY_MAX                                       /*�߽�ֵ*/
}IPF_ADQ_EMPTY_E;

typedef enum tagIPF_AD_TYPE_E
{
    IPF_AD_0 = 0,       /*��ʶADQ0*/
    IPF_AD_1,           /*��ʶADQ1*/

    IPF_AD_MAX          /*�߽�ֵ*/
}IPF_AD_TYPE_E;
/* IPF״̬��ʶ */
typedef enum tagIPF_RESTORE_STATE_E
{
    IPF_STATE_UNRESTORE = 0,   /* δ�ָ� */
    IPF_STATE_RESTORING,       /* �ָ��� */
    IPF_STATE_RESTORED,        /* �ѻָ� */

    IPF_STATE_MAX
}IPF_RESTORE_STATE_E;

/* IP���� */
typedef enum tagIPF_IP_TYPE_E
{
    IPF_IPTYPE_V4 = 0,  /* IPV4 */
    IPF_IPTYPE_V6,      /* IPV6 */

    IPF_IPTYPE_MAX      /* �߽�ֵ */
}IPF_IP_TYPE_E;

/* ͨ������ */
typedef enum tagIPF_CHANNEL_TYPE_E
{
    IPF_CHANNEL_UP  = 0,    /* ����ͨ�� */
    IPF_CHANNEL_DOWN,       /* ����ͨ�� */

    IPF_CHANNEL_MAX         /* �߽�ֵ */
}IPF_CHANNEL_TYPE_E;

typedef enum tagIPF_FILTER_CHAIN_TYPE_E
{
    IPF_MODEM0_ULFC = 0,
    IPF_MODEM1_ULFC,
    IPF_MODEM0_DLFC,
    IPF_MODEM1_DLFC,

    IPF_MODEM_MAX = 8
}IPF_FILTER_CHAIN_TYPE_E;

/*�ñ�������C�˸�λʱ������IPF����*/
typedef enum tagIPF_FORRESET_CONTROL_E
{
    IPF_FORRESET_CONTROL_ALLOW,     /*��������*/
    IPF_FORRESET_CONTROL_FORBID,    /*��ֹ����*/

    IPF_FORRESET_CONTROL_MAX
}IPF_FORRESET_CONTROL_E;

/**************************************************************************
  ���Ͷ���
**************************************************************************/
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
typedef BSP_S32 (*BSP_IPF_WakeupUlCb)(BSP_VOID);
typedef BSP_S32 (*BSP_IPF_AdqEmptyUlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);
#else
typedef BSP_S32 (*BSP_IPF_WakeupDlCb)(BSP_VOID);
typedef BSP_S32 (*BSP_IPF_AdqEmptyDlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);
#endif

/**************************************************************************
  STRUCT����
**************************************************************************/
/* BD������ */
typedef struct tagIPF_BD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32InPtr;
    BSP_U32 u32OutPtr;
    BSP_U16 u16Resv;
    BSP_U16 u16UsrField1;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
} IPF_BD_DESC_S;

/* RD������ */
typedef struct tagIPF_RD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32InPtr;
    BSP_U32 u32OutPtr;
    BSP_U16 u16Result;
    BSP_U16 u16UsrField1;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
} IPF_RD_DESC_S;

/* AD������ */
typedef struct tagIPF_AD_DESC_S
{
    BSP_U32 u32OutPtr0;
    BSP_U32 u32OutPtr1;
}IPF_AD_DESC_S;

/* CD������ */
typedef struct tagIPF_CD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32Ptr;
}IPF_CD_DESC_S;

/* ͨ�����ƽṹ�� */
typedef struct tagIPF_CHL_CTRL_S
{
    BSP_BOOL bDataChain;          /* �����Ƿ�Ϊ���� */
    BSP_BOOL bEndian;             /* ��С��ָʾ */
    IPF_MODE_E eIpfMode;          /* ģʽ���� */
    BSP_U32 u32WrrValue;          /* WRRֵ */
} IPF_CHL_CTRL_S;

typedef struct tagIPF_CONFIG_ULPARAM_S
{
    BSP_U16 u16Len;         /* ��������Դ���� */
    BSP_U16 u16Attribute;   /* ����IP������ */
    BSP_U32 u32Data;        /* ��������Դ��ַ */
    BSP_U16 u16UsrField1;   /* Usr field ��1 ,͸�� */
    BSP_U16 u16Reserved;    /* Ԥ�� */
    BSP_U32 u32UsrField2;   /* Usr field ��2 ,͸�� */
    BSP_U32 u32UsrField3;   /* Usr field ��3 ,͸��*/
}IPF_CONFIG_ULPARAM_S;

/* ͳ�Ƽ�����Ϣ�ṹ�� */
typedef struct tagIPF_FILTER_STAT_S
{
    BSP_U32 u32UlCnt0;
    BSP_U32 u32UlCnt1;
    BSP_U32 u32UlCnt2;
    BSP_U32 u32DlCnt0;
    BSP_U32 u32DlCnt1;
    BSP_U32 u32DlCnt2;
}IPF_FILTER_STAT_S;

#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
/* ���������ṹ�� */
typedef struct tagIPF_COMMON_PARA_S
{
    BSP_BOOL bAdReport;             /* �ϡ�����ͨ��AD�ϱ�ѡ�� */
    BSP_BOOL bMultiModeEn;          /* ��ͨ����̬ҵ��ģʽʹ�� */
    BSP_BOOL bMultiFilterChainEn;   /* ��ͨ�����������ʹ�� */
    BSP_BOOL bEspSpiDisable;        /* ESP SPI�Ƿ����ƥ������ź� */
    BSP_BOOL bAhSpiDisable;         /* AH SPI�Ƿ����ƥ������ź� */
    BSP_BOOL bEspAhSel;             /* 0ѡESP��1ѡAH */
    BSP_BOOL bIpv6NextHdSel;        /* IPV6 Next Headerѡ�� */
    IPF_BURST_E eMaxBurst;          /* BURST��󳤶� */
    BSP_BOOL bSpWrrModeSel;         /* SP��WRRģʽ����ѡ��*/
    BSP_BOOL bSpPriSel;             /* SP���ȼ�ѡ�� */
    BSP_BOOL bFltAddrReverse;       /* �������е�ַ�Ĵ�����С������˳�� 0��ʾ��� */
    BSP_BOOL bFilterSeq;            /* ����������˳��ָʾ */
} IPF_COMMON_PARA_S;

/* ƥ������Ϣ */
typedef struct tagIPF_MATCH_INFO_S
{
    BSP_U8 u8SrcAddr[16];
    BSP_U8 u8DstAddr[16];
    BSP_U8 u8DstMsk[16];
    union
    {
        struct
        {
            BSP_U32 u16SrcPortLo:16;
            BSP_U32 u16SrcPortHi:16;
        }Bits;
        BSP_U32 u32SrcPort;
    } unSrcPort;
    union
    {
        struct
        {
            BSP_U32 u16DstPortLo:16;
            BSP_U32 u16DstPortHi:16;
        }Bits;
        BSP_U32 u32DstPort;
    } unDstPort;
    union
    {
        struct
        {
            BSP_U32 u8TrafficClass:8;
            BSP_U32 u8TrafficClassMask:8;
            BSP_U32 u16Reserve:16;
        }Bits;
        BSP_U32 u32TrafficClass;
    }unTrafficClass;
    BSP_U32 u32LocalAddressMsk;
    union
    {
        BSP_U32 u32NextHeader;
        BSP_U32 u32Protocol;
    }unNextHeader;
    BSP_U32 u32FlowLable;
    union
    {
        struct
        {
            BSP_U32 u16Type:16;
            BSP_U32 u16Code:16;
        }Bits;
        BSP_U32 u32CodeType;
    } unFltCodeType;
    union
    {
        struct
        {
            BSP_U32 u16NextIndex:16;
            BSP_U32 u16FltPri:16;
        }Bits;
        BSP_U32 u32FltChain;
    } unFltChain;
    BSP_U32 u32FltSpi;
    union
    {
        struct
        {
            BSP_U32 FltEn:1;
            BSP_U32 FltType:1;
            BSP_U32 Resv1:2;
            BSP_U32 FltSpiEn:1;
            BSP_U32 FltCodeEn:1;
            BSP_U32 FltTypeEn:1;
            BSP_U32 FltFlEn:1;
            BSP_U32 FltNhEn:1;
            BSP_U32 FltTosEn:1;
            BSP_U32 FltRPortEn:1;
            BSP_U32 FltLPortEn:1;
            BSP_U32 FltRAddrEn:1;
            BSP_U32 FltLAddrEn:1;
            BSP_U32 Resv2:2;
            BSP_U32 FltBid:6;
            BSP_U32 Resv3:10;
        }Bits;
        BSP_U32 u32FltRuleCtrl;
    }unFltRuleCtrl;
}IPF_MATCH_INFO_S;

/* Filter������Ϣ�ṹ�� */
typedef struct tagIPF_FILTER_CONFIG_S
{
    BSP_U32 u32FilterID;            /* ��16λ��ʾPS ID;��16λ��ʾPSʹ���˲������ͣ�����������չ */
    IPF_MATCH_INFO_S stMatchInfo;   /* ��������Ӧ����Ϣ */
} IPF_FILTER_CONFIG_S;

typedef struct tagIPF_CONFIG_DLPARAM_S
{
    BSP_U16 u16Len;
    BSP_U16 u16Attribute;
    BSP_U32 u32Data;
    BSP_U16 u16UsrField1;
    BSP_U16 u16Reserved;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
}IPF_CONFIG_DLPARAM_S;
#endif
/**************************************************************************
  ��������
**************************************************************************/
extern BSP_S32 BSP_IPF_ConfigTimeout(BSP_U32 u32Timeout);
extern BSP_S32 BSP_IPF_ConfigUpFilter(BSP_U32 u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara);
extern BSP_U32 BSP_IPF_GetUlDescNum(BSP_VOID);
extern BSP_U32 BSP_IPF_GetUlBDNum(BSP_VOID);
extern BSP_S32 BSP_IPF_UlStateIdle(BSP_VOID);
extern BSP_S32 BSP_IPF_SetPktLen(BSP_U32 u32MaxLen, BSP_U32 u32MinLen);
extern BSP_S32 BSP_IPF_GetStat(IPF_FILTER_STAT_S *pstFilterStat);
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
extern BSP_S32 BSP_IPF_Init(IPF_COMMON_PARA_S *pstCommPara);
extern BSP_S32 BSP_IPF_ConfigUlChannel(IPF_CHL_CTRL_S *pstCtrl);
extern BSP_S32 BSP_IPF_ConfigDlChannel(IPF_CHL_CTRL_S *pstCtrl);
extern BSP_S32 BSP_IPF_SetFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, IPF_FILTER_CONFIG_S *pstFilterInfo, BSP_U32 u32FilterNum);
extern BSP_S32 BSP_IPF_GetFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, BSP_U32 u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo);
extern BSP_S32 BSP_IPF_ConfigDownFilter(BSP_U32 u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara);
extern BSP_S32 BSP_IPF_ChannelEnable(IPF_CHANNEL_TYPE_E eChanType, BSP_BOOL bFlag);
extern BSP_U32 BSP_IPF_GetDlDescNum(BSP_VOID);
extern BSP_U32 BSP_IPF_GetDlBDNum(BSP_U32* pu32CDNum);
extern BSP_S32 BSP_IPF_DlStateIdle(BSP_VOID);
extern BSP_S32 BSP_IPF_RegisterWakeupUlCb(BSP_IPF_WakeupUlCb pFnWakeupUl);
extern BSP_VOID BSP_IPF_GetUlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd);
extern BSP_S32 BSP_IPF_GetUlAdNum(BSP_U32* pu32AD0Num, BSP_U32* pu32AD1Num);
extern BSP_S32 BSP_IPF_ConfigUlAd(IPF_AD_TYPE_E eAdType, BSP_U32 u32AdNum, IPF_AD_DESC_S *pstAdDesc);
extern BSP_S32 BSP_IPF_RegisterAdqEmptyUlCb(BSP_IPF_AdqEmptyUlCb pAdqEmptyUl);
extern BSP_S32 BSP_IPF_ConfigADThr(BSP_U32 u32UlADThr,BSP_U32 u32DlADThr);
#else
extern BSP_S32 BSP_IPF_RegisterWakeupDlCb(BSP_IPF_WakeupDlCb pFnWakeupDl);
extern BSP_VOID BSP_IPF_GetDlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd);
extern BSP_U32 BSP_IPF_GetUlRdNum(BSP_VOID);
extern BSP_U32 BSP_IPF_GetDlRdNum(BSP_VOID);
extern BSP_S32 BSP_IPF_GetDlAdNum(BSP_U32* pu32AD0Num, BSP_U32* pu32AD1Num);
extern BSP_S32 BSP_IPF_ConfigDlAd(IPF_AD_TYPE_E eAdType, BSP_U32 u32AdNum, IPF_AD_DESC_S *pstAdDesc);
extern BSP_S32 BSP_IPF_RegisterAdqEmptyDlCb(BSP_IPF_AdqEmptyDlCb pAdqEmptyDl);
extern BSP_S32 BSP_IPF_GetUsedDlAd(IPF_AD_TYPE_E eAdType, BSP_U32 *pu32AdNum, IPF_AD_DESC_S *pstAdDesc);
extern BSP_VOID BSP_IPF_DlRegReInit(BSP_VOID);
extern BSP_VOID BSP_IPF_SetControlFLagForCcoreReset(IPF_FORRESET_CONTROL_E flagvalue);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/* __DRV_IPF_H__ */

