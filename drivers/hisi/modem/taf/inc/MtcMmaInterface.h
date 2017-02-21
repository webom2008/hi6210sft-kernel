

#ifndef _MTCMMAINTERFACE_H_
#define _MTCMMAINTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MTC_MMA_MAX_EQUPLMN_NUM         (18)                                    /* ��Ч��PLMN�������� */
#define MTC_MMA_TDS_ARFCN_MAX_NUM       (9)                                     /* TDDƵ���б������� */
#define MTC_MMA_LTE_ARFCN_MAX_NUM       (8)                                     /* LTEƵ���б������� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum MTC_MMA_MSG_ID_ENUM
{
    /* ��Ϣ���� */                         /* ��ϢID */                         /* ��ע */
    /* MTC --> MMA */
    ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY = 0x0001,                                /* _H2ASN_MsgChoice MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU */

    ID_MTC_MMA_NCELL_INFO_IND           = 0x0003,                          /* _H2ASN_MsgChoice MTC_MMA_NCELL_INFO_IND_STRU */
	
    ID_MTC_MMA_PS_TRANSFER_IND         = 0x0005,
    /* MMA --> MTC */
    ID_MMA_MTC_POWER_STATE_IND          = 0x0002,                               /* _H2ASN_MsgChoice MMA_MTC_POWER_STATE_IND_STRU */
    ID_MMA_MTC_RAT_MODE_IND             = 0x0004,                               /* _H2ASN_MsgChoice MMA_MTC_RAT_MODE_IND_STRU */

    ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND  = 0x0006,                               /* _H2ASN_MsgChoice MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU */

    ID_MMA_MTC_EPLMN_INFO_IND           = 0x0008,                               /* _H2ASN_MsgChoice MMA_MTC_EPLMN_INFO_IND_STRU*/

    ID_MMA_MTC_REG_STATUS_IND           = 0x000a,                               /* _H2ASN_MsgChoice MMA_MTC_REG_STATUS_IND_STRU */
    ID_MMA_MTC_MSG_ID_BUTT
};
typedef VOS_UINT32  MTC_MMA_MSG_ID_ENUM_UINT32;

/*****************************************************************************
ö����    : MTC_MODEM_POWER_STATE_ENUM
�ṹ˵��  : MTCģ�鿪��״̬ö��

  1.��    ��   : 2013��08��13��
    ��    ��   : ���±�/j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
enum MTC_MODEM_POWER_STATE_ENUM
{
    MTC_MODEM_POWER_OFF                 = 0x00,
    MTC_MODEM_POWER_ON                  = 0x01,

    MTC_MODEM_POWER_STATE_BUTT
};
typedef VOS_UINT8  MTC_MODEM_POWER_STATE_ENUM_UINT8;


enum MTC_RATMODE_ENUM
{
    MTC_RATMODE_GSM                     = 0x00,
    MTC_RATMODE_WCDMA                   = 0x01,
    MTC_RATMODE_LTE                     = 0x02,
    MTC_RATMODE_TDS                     = 0x03,
    MTC_RATMODE_BUTT
};
typedef VOS_UINT8 MTC_RATMODE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
} MTC_MMA_PLMN_ID_STRU;


typedef struct
{
    VOS_UINT8                           ucEquPlmnNum;                           /* ��ǰEquPLMN�ĸ��� */
    VOS_UINT8                           aucReserved[3];
    MTC_MMA_PLMN_ID_STRU                astEquPlmnAddr[MTC_MMA_MAX_EQUPLMN_NUM];/* ��ǰEquPLMN�б� */
}MTC_MMA_EPLMN_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU              stMsgHeader;                                   /*_H2ASN_Skip*/
    VOS_UINT32                   bitOpCurrCampPlmnId:1;

    VOS_UINT32                   bitOpEplmnInfo:1;
    VOS_UINT32                   bitSpare:30;

    MTC_MMA_PLMN_ID_STRU         stCurrCampPlmnId;                              /* ������д��ǰפ��С����PLMN������������߹ػ��ȷ�פ��״̬��ͳһ��дȫ0xff */

    MTC_MMA_EPLMN_INFO_STRU      stEplmnInfo;

} MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           enSolutionCfg;                          /* PS��Ǩ�Ʒ��� */
    VOS_UINT8                           ucCause;                                /* PS���л�ԭ��ֵ */
    VOS_UINT8                           aucReserved[2];                         /*����λ*/
} MTC_MMA_PS_TRANSFER_IND_STRU;


/*******************************************************************************
 �ṹ��    : MMA_MTC_POWER_STATE_IND_STRU
 �ṹ˵��  : ID_MMA_MTC_POWER_STATE_IND����Ϣ�ṹ

 1.��    ��   : 2013��08��12��
   ��    ��   : ���±�/j00174725
   �޸�����   : ������
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState;                           /* ��ǰ���ػ�״̬ */
    VOS_UINT8                           aucReserved[3];
} MMA_MTC_POWER_STATE_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_RATMODE_ENUM_UINT8              enRatMode;                              /* ��ǰ����ģʽ */
    VOS_UINT8                           aucReserved[3];
} MMA_MTC_RAT_MODE_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_MMA_PLMN_ID_STRU                stPlmnId;                               /* ��ǰפ������ */
    MTC_RATMODE_ENUM_UINT8              enRatMode;                              /* ��ǰ����ģʽ */
    VOS_UINT8                           ucIsForbiddenPlmnFlag;                  /* ��ǰפ�������Ƿ�Ϊ��ֹ�����ʶ */
    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucPsSupportFlg;                         /* ��ǰ�����Ƿ�֧��PS�� */
} MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU;
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0��ʾTDDƵ�㲻���� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausTdsArfcnList[MTC_MMA_TDS_ARFCN_MAX_NUM];
}MTC_MMA_TDS_NCELL_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          ausLteArfcnList[MTC_MMA_LTE_ARFCN_MAX_NUM];
}MTC_MMA_LTE_NCELL_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_MMA_TDS_NCELL_INFO_STRU         stTdsNcellInfo;
    MTC_MMA_LTE_NCELL_INFO_STRU         stLteNcellInfo;
}MTC_MMA_NCELL_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_MMA_EPLMN_INFO_STRU             stEplmnInfo;
}MMA_MTC_EPLMN_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           ucIsUsimValidFlg;                       /* ��ʶ���Ƿ���Ч��1:��Ч��0:��Ч*/
    VOS_UINT8                           aucReserved[3];
} MMA_MTC_REG_STATUS_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    MTC_MMA_MSG_ID_ENUM_UINT32          enMsgID;                                /*_H2ASN_MsgChoice_Export MTC_MMA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTC_MMA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} MTC_MMA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTC_MMA_MSG_DATA                    stMsgData;
} MtcMmaInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MtcMmaInterface.h */
