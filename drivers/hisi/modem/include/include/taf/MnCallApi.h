/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallApi.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��22��
  ����޸�   : 2007��8��22��
  ��������   : �µ�API�ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
  2.��    ��   : 2008��10��20��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:A32D14153,����ʱ���û���δ�����绰�ʹ���������,��AMR���ʱ任û���ϱ�

  3.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : ֧��UUS1
******************************************************************************/
#ifndef  MN_CALL_API_H
#define  MN_CALL_API_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafAppSsa.h"
#include "pslog.h"
#include "vos.h"

#include  "AtMnInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
/* �����и��� */
#define    MN_CALL_MAX_NUM              (7)

/* ��ѡ���Ƿ���ڵı�־ */
#define MN_CALL_OPTION_EXIST            (1)
#define MN_CALL_OPTION_NOT_EXIST        (0)

#define MN_CALL_MAX_EMC_NUM             (50)
#define MN_CALL_ECC_NUM_VALID_SIM_PRESENT (1)
#define MN_CALL_ECC_NUM_VALID_SIM_ABSENT  (0)
#define MN_CALL_ECC_NUM_INVALID_CATEGORY  (0)

/* 10.5.4.8 Called party subaddress */
#define MN_CALL_MAX_SUBADDR_INFO_LEN     (20)

#define MN_CALL_RPT_CFG_MAX_SIZE        (8)
#define     MN_CALL_NET_RAT_TYPE_WCDMA      (0)           /* ��ǰפ��ΪW */
#define     MN_CALL_NET_RAT_TYPE_GSM        (1)           /* ��ǰפ��ΪG */
#define     MN_CALL_NET_RAT_TYPE_LTE        (2)           /* ��ǰפ��ģΪL */

#define TAF_CALL_DTMF_MIN_ONLENGTH              (65)                            /* DTMF����Сʱ�� */
#define TAF_CALL_DTMF_DEFAULT_ONLENGTH          (60000)                         /* Ĭ��DTMF��ʱ��60s */

#define TAF_CALL_DTMF_DEFAULT_OFFLENGTH          (75)                           /* stop dtmf ack��start dtmf req֮��ʱ��������70����С��600����,Ĭ��75���� */

#define TAF_CALL_MAX_BC_NUM                             (2)                     /* ���BC���� */
#define TAF_CALL_MIN_BC_NUM                             (1)                     /* ��СBC���� */

#if (FEATURE_ON == FEATURE_ECALL)
#define  TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH           (120000)                /* 120s */
#define  TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH         (5000)                  /* 5s */
#define  TAF_CALL_T2_TIMER_LENGTH                       (3600000)               /* ʱ��Ϊ1Сʱ */
/* T9��ʱ��ʱ�������ã�Ĭ������Ϊ1Сʱ��������ʱ����Χ: 1 hour<= T9 <= 12 hours */
#define  TAF_CALL_ONE_HOUR_TIMER_LENGTH                 (3600000)
#define  TAF_CALL_T9_MIN_TIMER_LENGTH                   (1)                     /* T9��Сʱ��Ϊ1Сʱ */
#define  TAF_CALL_T9_MAX_TIMER_LENGTH                   (12)                    /* T9���ʱ��Ϊ12��Ϣ */
#endif
/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
/* Added by f62575 for AT Project, 2011-11-1, begin */


/*****************************************************************************
 ö����    : NAS_CC_STATE_INFO_STRU
 �ṹ˵��  : CC�ڲ�״̬�ṹ
*****************************************************************************/
enum NAS_CC_CALL_STATE_ENUM                                                     /* Call state value (octet 2)               */
{                                                                               /* Bits 6 5 4 3 2 1                         */
    NAS_CC_CALL_STATE_U0                                    =  0,               /*      0 0 0 0 0 0 UO - null               */
    NAS_CC_CALL_STATE_U0_1                                  =  2,               /*      0 0 0 0 1 0 U0.1- MM con pending    */
    NAS_CC_CALL_STATE_U0_2                                  = 34,               /*      1 0 0 0 1 0 U0.2- CC prompt present */
    NAS_CC_CALL_STATE_U0_3                                  = 35,               /*      1 0 0 0 1 1 U0.3- Wait for network  */
    NAS_CC_CALL_STATE_U0_4                                  = 36,               /*      1 0 0 1 0 0 U0.4- CC-Est present    */
    NAS_CC_CALL_STATE_U0_5                                  = 37,               /*      1 0 0 1 0 1 U0.5- CC-Est confirmed  */
    NAS_CC_CALL_STATE_U0_6                                  = 38,               /*      1 0 0 1 1 0 U0.6- Recall present    */
    NAS_CC_CALL_STATE_U1                                    =  1,               /*      0 0 0 0 0 1 U1 - call initiated     */
    NAS_CC_CALL_STATE_U3                                    =  3,               /*      0 0 0 0 1 1 U3 - MO call proc       */
    NAS_CC_CALL_STATE_U4                                    =  4,               /*      0 0 0 1 0 0 U4 - call delivered     */
    NAS_CC_CALL_STATE_U6                                    =  6,               /*      0 0 0 1 1 0 U6 - call present       */
    NAS_CC_CALL_STATE_U7                                    =  7,               /*      0 0 0 1 1 1 U7 - call received      */
    NAS_CC_CALL_STATE_U8                                    =  8,               /*      0 0 1 0 0 0 U8 - connect request    */
    NAS_CC_CALL_STATE_U9                                    =  9,               /*      0 0 1 0 0 1 U9 - MT call Cnf        */
    NAS_CC_CALL_STATE_U10                                   = 10,               /*      0 0 1 0 1 0 U10- active             */
    NAS_CC_CALL_STATE_U11                                   = 11,               /*      0 0 1 0 1 1 U11- disconnect REQ     */
    NAS_CC_CALL_STATE_U12                                   = 12,               /*      0 0 1 1 0 0 U12- disconnect IND     */
    NAS_CC_CALL_STATE_U19                                   = 19,               /*      0 1 0 0 1 1 U19- release REQ        */
    NAS_CC_CALL_STATE_U26                                   = 26,               /*      0 1 1 0 1 0 U26- MO modify          */
    NAS_CC_CALL_STATE_U27                                   = 27,               /*      0 1 1 0 1 1 U27- MT modify          */
    NAS_CC_CALL_STATE_BUTT
};
typedef VOS_UINT8   NAS_CC_CALL_STATE_ENUM_U8;

enum MN_CALL_ALS_LINE_NO_ENUM
{
    MN_CALL_ALS_LINE_NO_1               = 1,
    MN_CALL_ALS_LINE_NO_2               = 2,
    MN_CALL_ALS_LINE_NO_MAX,
    MN_CALL_ALS_LINE_NO_BUTT
};
typedef VOS_UINT8 MN_CALL_ALS_LINE_NO_ENUM_U8;

/* Table 10.5.100/3GPP TS 24.008: Auxiliary states information element        */
enum NAS_CC_HOLD_AUX_STATE_ENUM                                                 /* Hold aux state (octet 3)          */
{                                                                               /* Bits 4 3                          */
    NAS_CC_HOLD_AUX_S_IDLE                                  = 0,                /*      0 0 idle                     */
    NAS_CC_HOLD_AUX_S_HOLD_REQ                              = 1,                /*      0 1 hold request             */
    NAS_CC_HOLD_AUX_S_CALL_HELD                             = 2,                /*      1 0 call held                */
    NAS_CC_HOLD_AUX_S_RETRIEVE_REQ                          = 3,                /*      1 1 retrieve request         */
    NAS_CC_HOLD_AUX_S_BUTT
};                                                                              /* defined in 24.083 [27].           */
typedef VOS_UINT8   NAS_CC_HOLD_AUX_STATE_ENUM_U8;

/* Table 10.5.101/3GPP TS 24.008: Auxiliary states information element        */
enum NAS_CC_MPTY_AUX_STATE_ENUM                                                 /* Multi party aux state (octet 3)   */
{                                                                               /* Bits 2 1                          */
    NAS_CC_MPTY_AUX_S_IDLE                                  = 0,                /*      0 0 idle                     */
    NAS_CC_MPTY_AUX_S_MPTY_REQ                              = 1,                /*      0 1 MPTY request             */
    NAS_CC_MPTY_AUX_S_CALL_IN_MPTY                          = 2,                /*      1 0 call in MPTY             */
    NAS_CC_MPTY_AUX_S_SPLIT_REQ                             = 3,                /*      1 1 split request            */
    NAS_CC_MPTY_AUX_S_BUTT
};                                                                              /* defined in 24.084 [28].           */
typedef VOS_UINT8   NAS_CC_MPTY_AUX_STATE_ENUM_U8;


/* Added by f62575 for AT Project, 2011-11-1, end */

enum TAF_CALL_VOICE_DOMAIN_ENUM
{
    TAF_CALL_VOICE_DOMAIN_3GPP   = 0,
    TAF_CALL_VOICE_DOMAIN_IMS    = 1,

    TAF_CALL_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT8   TAF_CALL_VOICE_DOMAIN_ENUM_UINT8;






typedef struct
{
    VOS_UINT8                           ucCallId;           /* ����ID */
    VOS_UINT8                           ucTi;               /* ����ID */
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;        /* ����Э��״̬ */
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldAuxState;     /* ���б��ָ���״̬ */
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyAuxState;     /* �෽���и���״̬ */
    VOS_UINT8                           aucReserve1[3];
} NAS_CC_STATE_INFO_STRU;

/*****************************************************************************
 ö����    : AT_CC_STATE_QRY_CNF_STRU
 �ṹ˵��  : CC�ظ�AT״̬��ѯ�ظ��ӿ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;                              /* ��Ϣ�� */
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT8                           ucCallNum;                              /* ���и��� */
    VOS_UINT8                           aucCallExist[MN_CALL_MAX_NUM];
    NAS_CC_STATE_INFO_STRU              astCcStateInfoList[MN_CALL_MAX_NUM];                          /* ��Ϣ���� */
} AT_CC_STATE_QRY_CNF_MSG_STRU;


typedef VOS_UINT8  MN_CALL_ID_T;

enum MN_CALL_TYPE_ENUM
{
    MN_CALL_TYPE_VOICE,                                                         /* normal voice call */
    MN_CALL_TYPE_VIDEO,                                                         /* video call */
    MN_CALL_TYPE_FAX,                                                           /* group 3 fax */
    MN_CALL_TYPE_CS_DATA,                                                       /* CS data call*/
    MN_CALL_TYPE_EMERGENCY = 9,                                                 /* emergency call */
    MN_CALL_TYPE_MIEC,                                                          /* manually initiated ecall */
    MN_CALL_TYPE_AIEC,                                                          /* automatic initiated ecall */
    MN_CALL_TYPE_TEST,                                                          /* test ecall */
    MN_CALL_TYPE_RECFGURATION,                                                  /* reconfiguration call */
    MN_CALL_TYPE_PSAP_ECALL,                                                    /* ����PSAP�غ��ĺ������� */
    MN_CALL_TYPE_BUTT
};
typedef VOS_UINT8  MN_CALL_TYPE_ENUM_U8;

/* �������е�Category,3gpp 31102�ж���*/
typedef enum MN_CALL_EMER_CATEGORY_TYPE
{
    MN_CALL_EMER_CATEGORG_POLICE            = 0x01,
    MN_CALL_EMER_CATEGORG_AMBULANCE         = 0x02,
    MN_CALL_EMER_CATEGORG_FIRE_BRIGADE      = 0x04,
    MN_CALL_EMER_CATEGORG_MARINE_GUARD      = 0x08,
    MN_CALL_EMER_CATEGORG_MOUNTAIN_RESCUE   = 0x10,
    MN_CALL_EMER_CATEGORG_MAN_INIT_ECALL    = 0x20,
    MN_CALL_EMER_CATEGORG_AUTO_INIT_ECALL   = 0x40,

    MN_CALL_EMER_CATEGORG_MAX               = 0x80
}MN_CALL_EMER_CATEGORY_TYPE_ENUM;
typedef VOS_UINT8 MN_CALL_EMER_CATEGORG_TYPE_ENUM_U8;

enum MN_CALL_EX_STATE_ENUM
{
    MN_CALL_S_ACTIVE,                                                           /* active */
    MN_CALL_S_HELD,                                                             /* held */
    MN_CALL_S_DIALING,                                                          /* dialing (MO call) */
    MN_CALL_S_ALERTING,                                                         /* alerting (MO call) */
    MN_CALL_S_INCOMING,                                                         /* incoming (MT call) */
    MN_CALL_S_WAITING,                                                          /* waiting (MT call) */
    MN_CALL_S_IDLE,                                                             /* idle */
    MN_CALL_S_CCBS_WAITING_ACTIVE,                                              /*CCBS�ȴ�����̬*/
    MN_CALL_S_CCBS_WAITING_RECALL,                                              /*CCBS�ȴ��غ�̬*/
    MN_CALL_S_UNKNOWN,                                                          /* unknown state */

    MN_CALL_S_WAITING_ACCEPT,                                                   /* ��״̬ΪSRVCC����ǰ�û�����ʧ�ܣ��ɹ�����GU�·���connect */

    MN_CALL_S_BUTT
};
typedef VOS_UINT8  MN_CALL_STATE_ENUM_U8;
enum TAF_CALL_SUB_STATE_ENUM
{
    TAF_CALL_SUB_STATE_NULL,
    TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK,                                    /* ata�������ϱ�ok��������connect ack��״̬*/
    TAF_CALL_SUB_STATE_BUTT
};
typedef VOS_UINT8 TAF_CALL_SUB_STATE_ENUM_UINT8;


enum MN_CALL_MPTY_STATE_ENUM
{
    MN_CALL_NOT_IN_MPTY,
    MN_CALL_IN_MPTY,
    MN_CALL_MPYT_STATE_BUTT
};
typedef VOS_UINT8  MN_CALL_MPTY_STATE_ENUM_U8;


/* call direction */
enum MN_CALL_DIR_ENUM
{
    MN_CALL_DIR_MO,                                                             /* MO CALL */
    MN_CALL_DIR_MT,                                                             /* MT CALL */
    MN_CALL_DIR_CCBS,                                                            /*CCBS CALL*/
    MN_CALL_DIR_BUTT
};
typedef VOS_UINT8  MN_CALL_DIR_ENUM_U8;

/* see 3GPP 27.007 +CBST, para speed */
enum MN_CALL_CS_DATA_SPEED_ENUM
{
    MN_CALL_CSD_SPD_AUTOBAUD                                = 0,
    MN_CALL_CSD_SPD_300_V21                                 = 1,
    MN_CALL_CSD_SPD_1K2_V22                                 = 2,
    MN_CALL_CSD_SPD_2K4_V22BIS                              = 4,
    MN_CALL_CSD_SPD_2K4_V26TER                              = 5,
    MN_CALL_CSD_SPD_4K8_V32                                 = 6,
    MN_CALL_CSD_SPD_9K6_V32                                 = 7,
    MN_CALL_CSD_SPD_9K6_V34                                 = 12,
    MN_CALL_CSD_SPD_14K4_V34                                = 14,
    MN_CALL_CSD_SPD_19K2_V34                                = 15,
    MN_CALL_CSD_SPD_28K8_V34                                = 16,
    MN_CALL_CSD_SPD_33K6_V34                                = 17,
    MN_CALL_CSD_SPD_1K2_V120                                = 34,
    MN_CALL_CSD_SPD_2K4_V120                                = 36,
    MN_CALL_CSD_SPD_4K8_V120                                = 38,
    MN_CALL_CSD_SPD_9K6_V120                                = 39,
    MN_CALL_CSD_SPD_14K4_V120                               = 43,
    MN_CALL_CSD_SPD_19K2_V120                               = 47,
    MN_CALL_CSD_SPD_28K8_V120                               = 48,
    MN_CALL_CSD_SPD_38K4_V120                               = 49,
    MN_CALL_CSD_SPD_48K_V120                                = 50,
    MN_CALL_CSD_SPD_56K_V120                                = 51,
    MN_CALL_CSD_SPD_300_V110                                = 65,
    MN_CALL_CSD_SPD_1K2_V110                                = 66,
    MN_CALL_CSD_SPD_2K4_V110                                = 68,
    MN_CALL_CSD_SPD_4K8_V110                                = 70,
    MN_CALL_CSD_SPD_9K6_V110                                = 71,
    MN_CALL_CSD_SPD_14K4_V110                               = 75,
    MN_CALL_CSD_SPD_19K2_V110                               = 79,
    MN_CALL_CSD_SPD_28K8_V110                               = 80,
    MN_CALL_CSD_SPD_38K4_V110                               = 81,
    MN_CALL_CSD_SPD_48K_V110                                = 82,
    MN_CALL_CSD_SPD_56K_FTM                                 = 83,
    MN_CALL_CSD_SPD_64K_FTM                                 = 84,
    MN_CALL_CSD_SPD_56K_BT                                  = 115,
    MN_CALL_CSD_SPD_64K_BT                                  = 116,
    MN_CALL_CSD_SPD_32K_PIAFS                               = 120,
    MN_CALL_CSD_SPD_64K_PIAFS                               = 121,
    MN_CALL_CSD_SPD_64K_MULTI                               = 134,
    MN_CALL_CSD_SPD_BUTT
};
typedef VOS_UINT8   MN_CALL_CS_DATA_SPEED_ENUM_U8;


/* see 3GPP 27.007 +CBST, para name */
enum MN_CALL_CS_DATA_NAME_ENUM
{
    MN_CALL_CSD_NAME_ASYNC_UDI,                                                 /* data circuit asynchronous (UDI or 3.1 kHz modem) */
    MN_CALL_CSD_NAME_SYNC_UDI,                                                  /* data circuit synchronous (UDI or 3.1 kHz modem)  */
    MN_CALL_CSD_NAME_ASYNC_RDI,                                                 /* data circuit asynchronous (RDI) */
    MN_CALL_CSD_NAME_SYNC_RDI,                                                   /* data circuit synchronous (RDI) */
    MN_CALL_CSD_NAME_BUTT
};
typedef VOS_UINT8   MN_CALL_CS_DATA_NAME_ENUM_U8;


/* see 3GPP 27.007 +CBST, para CE(Connection element) */
enum MN_CALL_CS_DATA_CE_ENUM
{
    MN_CALL_CSD_CE_T,                                                           /* transparent  */
    MN_CALL_CSD_CE_NT,                                                          /* non-transparent  */
    MN_CALL_CSD_CE_BOTH_T,                                                      /* both, transparent preferred  */
    MN_CALL_CSD_CE_BOTH_NT,                                                      /* both, non-transparent preferred  */
    MN_CALL_CSD_CE_BUTT
};
typedef VOS_UINT8   MN_CALL_CS_DATA_CE_ENUM_U8;

/* for CS DATA service configration */
typedef struct
{
    MN_CALL_CS_DATA_SPEED_ENUM_U8       enSpeed;
    MN_CALL_CS_DATA_NAME_ENUM_U8        enName;
    MN_CALL_CS_DATA_CE_ENUM_U8          enConnElem;
    VOS_UINT8                           aucReserved[5];
} MN_CALL_CS_DATA_CFG_STRU;


enum MN_CALL_CS_DATA_SPD_SIMPLE_ENUM
{
    MN_CALL_CSD_SPD_300,
    MN_CALL_CSD_SPD_1K2,
    MN_CALL_CSD_SPD_2K4,
    MN_CALL_CSD_SPD_4K8,
    MN_CALL_CSD_SPD_9K6,
    MN_CALL_CSD_SPD_12K,
    MN_CALL_CSD_SPD_14K4,
    MN_CALL_CSD_SPD_19K2,
    MN_CALL_CSD_SPD_28K8,
    MN_CALL_CSD_SPD_31K2,
    MN_CALL_CSD_SPD_32K,
    MN_CALL_CSD_SPD_33K6,
    MN_CALL_CSD_SPD_38K4,
    MN_CALL_CSD_SPD_48K,
    MN_CALL_CSD_SPD_56K,
    MN_CALL_CSD_SPD_64K,
    MN_CALL_CSD_SPD_SIMPLE_BUTT
};
typedef VOS_UINT8   MN_CALL_CS_DATA_SPD_SIMPLE_ENUM_U8;

 /* for report CS DATA service configration */
 typedef struct
 {
    MN_CALL_CS_DATA_SPD_SIMPLE_ENUM_U8 enSpeed;
    MN_CALL_CS_DATA_NAME_ENUM_U8       enName;
    MN_CALL_CS_DATA_CE_ENUM_U8         enConnElem;
    VOS_UINT8                          aucReserved1[5];
 } MN_CALL_CS_DATA_CFG_INFO_STRU;


/* 3GPP 27.007 +CMOD */
enum MN_CALL_MODE_ENUM
{
    MN_CALL_MODE_SINGLE,                                                        /* single mode  */
    MN_CALL_MODE_AVF,                                                            /* alternating voice/fax */
    MN_CALL_MODE_BUTT
};
typedef VOS_UINT8   MN_CALL_MODE_ENUM_U8;


enum MN_CALL_CLIR_CFG_ENUM
{
    MN_CALL_CLIR_AS_SUBS,                                                       /* CLIR AS SUBSCRIBE */
    MN_CALL_CLIR_INVOKE,                                                        /* CLIR invocation */
    MN_CALL_CLIR_SUPPRESS,                                                       /* CLIR suppression  */
    MN_CALL_CLIR_BUTT
};
typedef VOS_UINT8 MN_CALL_CLIR_CFG_ENUM_U8;


typedef struct
{
    VOS_BOOL                            bEnable;                                /* if enable cug */
    VOS_BOOL                            bSuppressPrefer;                        /* suppress preferential CUG */
    VOS_BOOL                            bSuppressOA;                            /* suppress OA(Outgoing Access) */
    VOS_BOOL                            bIndexPresent;
    VOS_UINT32                          ulIndex;                                /* CUG Index */
    VOS_UINT8                           aucReserved[4];
} MN_CALL_CUG_CFG_STRU;


/* 3GPP 27.007 +CHLD */
enum MN_CALL_SUPS_CMD_ENUM
{
    MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB,                                          /* Releases all held calls or sets User Determined User Busy (UDUB) for a waiting call */
    MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH,                                          /* Releases all active calls (if any exist) and accepts the other (held or waiting) call */
    MN_CALL_SUPS_CMD_REL_CALL_X,                                                /* Releases a specific active call X */
    MN_CALL_SUPS_CMD_REL_ALL_CALL,                                              /* Releases all active call and held call and waiting call */
    MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH,                                         /* Places all active calls (if any exist) on hold and accepts the other (held or waiting) call */
    MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,                                          /* Places all active calls on hold except call X with which communication shall be supported */
    MN_CALL_SUPS_CMD_BUILD_MPTY,                                                /* Adds a held call to the conversation */
    MN_CALL_SUPS_CMD_ECT,                                                       /* Connects the two calls and disconnects the subscriber from both calls (ECT) */
    MN_CALL_SUPS_CMD_DEFLECT_CALL,                                              /* Redirect an incoming or a waiting call to the specified followed by SEND directory number */
    MN_CALL_SUPS_CMD_ACT_CCBS,                                                  /* Activates the Completion of Calls to Busy Subscriber Request */
    MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL,                               /* Releases all calls (if any exist) except waiting call */
    MN_CALL_SUPS_CMD_REL_HELD,                                                  /* Releases all held calls*/
    MN_CALL_SUPS_CMD_REL_ACTIVE,                                                /* Releases all active calls */
    MN_CALL_SUPS_CMD_REL_ECALL,                                                 /* Releases eCall*/
    MN_CALL_SUPS_CMD_BUTT
};
typedef VOS_UINT8   MN_CALL_SUPS_CMD_ENUM_U8;

/* Call relate SS Command Execute Result */
enum MN_CALL_SS_RESULT_ENUM
{
    MN_CALL_SS_RES_SUCCESS,
    MN_CALL_SS_RES_FAIL,
    MN_CALL_SS_RES_BUTT
};
typedef VOS_UINT8   MN_CALL_SS_RESULT_ENUM_U8;

/* Call relate SS Error Code */
enum MN_CALL_SS_ERR_CODE_ENUM
{
    MN_CALL_ERR_SS_UNSPECIFIC                      = 0,                         /* UNSPECIFIC Error*/
    MN_CALL_ERR_SS_ILLEGAL_SUBSCRIBER              = 9,                         /* IllegalSubscriber */
    MN_CALL_ERR_SS_ILLEGAL_EQUIPMENT               = 12,                        /* IllegalEquipment */
    MN_CALL_ERR_SS_CALL_BARRED                     = 13,                        /* CallBarred */
    MN_CALL_ERR_SS_FORWARDING_VIOLATION            = 14,                        /* ForwardingViolation */
    MN_CALL_ERR_SS_ILLEGALSS_OPERATION             = 16,                        /* IllegalSS-Operation */
    MN_CALL_ERR_SS_ERROR_STATUS                    = 17,                        /* SS-ErrorStatus */
    MN_CALL_ERR_SS_NOT_AVAILABLE                   = 18,                        /* SS-NotAvailable */
    MN_CALL_ERR_SS_SUBSCRIPTION_VIOLATION          = 19,                        /* SS-SubscriptionViolation */
    MN_CALL_ERR_SS_INCOMPATIBILITY                 = 20,                        /* SS-Incompatibility */
    MN_CALL_ERR_SS_FACILITY_NOT_SUPPORT            = 21,                        /* FacilityNotSupported */
    MN_CALL_ERR_SS_ABSENT_SUBSCRIBER               = 27,                        /* AbsentSubscriber */
    MN_CALL_ERR_SS_INCOMPATIBLE_TERMINAL           = 28,                        /* IncompatibleTerminal */
    MN_CALL_ERR_SS_SHORT_TERM_DENIAL               = 29,                        /* ShortTermDenial */
    MN_CALL_ERR_SS_LONG_TERM_DENIAL                = 30,                        /* LongTermDenial */
    MN_CALL_ERR_SS_SYSTEM_FAILURE                  = 34,                        /* SystemFailure */
    MN_CALL_ERR_SS_DATA_MISSING                    = 35,                        /* DataMissing */
    MN_CALL_ERR_SS_UNEXPECTED_DATA_VALUE           = 36,                        /* SystemFailure */
    MN_CALL_ERR_SS_FORWARDING_FAILED               = 47,                        /* ForwardingFailed */
    MN_CALL_ERR_SS_RESOURCE_LIMITATION             = 51,                        /* ResourceLimitation */
    MN_CALL_ERR_SS_DEFLECTION_TO_SERVED_SUBSCRIBER = 123,                       /* DeflectionToServedSubscriber  */
    MN_CALL_ERR_SS_SPECIAL_SERVICE_CODE            = 124,                       /* specialServiceCode */
    MN_CALL_ERR_SS_INVALID_DEFLECTED_TO_NUM        = 125,                       /* InvalidDeflectedToNumber */
    MN_CALL_ERR_SS_MAX_NUM_MPTY_EXCEEDED           = 126,                       /* MaxNumberOfMPTY-ParticipantsExceeded */
    MN_CALL_ERR_SS_RESOURCE_NOT_AVAILABLE          = 127,                        /* resourcesNotAvailable */
    MN_CALL_ERR_SS_BUTT
};
typedef VOS_UINT8   MN_CALL_SS_ERR_CODE_ENUM_U8;

/* Call Control Protocol Cause Value */
enum MN_CALL_CC_CAUSE_ENUM
{
    MN_CALL_INVALID_CAUSE                                   = 0,                /*   0. invalid cause value*/
    MN_CALL_UNASSIGNED_CAUSE                                = 1,                /*   1. Unassigned (unallocated) number            */
    MN_CALL_NO_ROUTE_TO_DEST                                = 3,                /*   3. No route to destination                    */
    MN_CALL_CHANNEL_UNACCEPTABLE                            = 6,                /*   6. Channel unacceptable                       */
    MN_CALL_OPERATOR_DETERMINED_BARRING                     = 8,                /*   8. Operator determined barring                */
    MN_CALL_NORMAL_CALL_CLEARING                            = 16,               /*  16. Normal call clearing                       */
    MN_CALL_USER_BUSY                                       = 17,               /*  17. User busy                                  */
    MN_CALL_NO_USER_RESPONDING                              = 18,               /*  18. No user responding                         */
    MN_CALL_USER_ALERTING_NO_ANSWER                         = 19,               /*  19. User alerting, no answer                   */
    MN_CALL_CALL_REJECTED                                   = 21,               /*  21. Call rejected                              */
    MN_CALL_NUMBER_CHANGED                                  = 22,               /*  22. Number changed                             */
    MN_CALL_PRE_EMPTION                                     = 25,               /*  25. Pre-emption                                */
    MN_CALL_NON_SELECTED_USER_CLEARING                      = 26,               /*  26. Non selected user clearing                 */
    MN_CALL_DESTINATION_OUT_OF_ORDER                        = 27,               /*  27. Destination out of order                   */
    MN_CALL_INVALID_NUMBER_FORMAT                           = 28,               /*  28. Invalid number format                      */
    MN_CALL_FACILITY_REJECTED                               = 29,               /*  29. Facility rejected                          */
    MN_CALL_RESPONSE_TO_STATUS_ENQUIRY                      = 30,               /*  30. Response to STATUS ENQUIRY                 */
    MN_CALL_NORMAL_UNSPECIFIED                              = 31,               /*  31. Normal, unspecified                        */
    MN_CALL_NO_CIRCUIT_CHANNEL_AVAILABLE                    = 34,               /*  34. No circuit/channel available               */
    MN_CALL_NETWORK_OUT_OF_ORDER                            = 38,               /*  38. Network out of order                       */
    MN_CALL_TEMPORARY_FAILURE                               = 41,               /*  41. Temporary failure                          */
    MN_CALL_SWITCHING_EQUIPMENT_CONGESTION                  = 42,               /*  42. Switching equipment congestion             */
    MN_CALL_ACCESS_INFORMATION_DISCARDED                    = 43,               /*  43. Access information discarded               */
    MN_CALL_REQUESTED_CIRCUIT_CHANNEL_NOT_AVAILABLE         = 44,               /*  44. requested circuit/channel not available    */
    MN_CALL_RESOURCES_UNAVAILABLE_UNSPECIFIED               = 47,               /*  47. Resources unavailable, unspecified         */
    MN_CALL_QUALITY_OF_SERVICE_UNAVAILABLE                  = 49,               /*  49. Quality of service unavailable             */
    MN_CALL_REQUESTED_FACILITY_NOT_SUBSCRIBED               = 50,               /*  50. Requested facility not subscribed          */
    MN_CALL_INCOMING_CALL_BARRED_WITHIN_CUG                 = 55,               /*  55. Incoming calls barred within the CUG       */
    MN_CALL_BEARER_CAPABILITY_NOT_AUTHORISED                = 57,               /*  57. Bearer capability not authorized           */
    MN_CALL_BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE       = 58,               /*  58. Bearer capability not presently available  */
    MN_CALL_SERVICE_OR_OPTION_NOT_AVAILABLE                 = 63,               /*  63. Service or option not available, unspec    */
    MN_CALL_BEARER_SERVICE_NOT_IMPLEMENTED                  = 65,               /*  65. Bearer service not implemented             */
    MN_CALL_ACM_GEQ_ACMMAX                                  = 68,               /*  68. ACM equal to or greater than ACMmax        */
    MN_CALL_REQUESTED_FACILITY_NOT_IMPLEMENTED              = 69,               /*  69. Requested facility not implemented         */
    MN_CALL_ONLY_RESTRICTED_DIGITAL_INFO_BC_AVAILABLE       = 70,               /*  70. Only restricted digital info BC available  */
    MN_CALL_SERVICE_OR_OPTION_NOT_IMPLEMENTED               = 79,               /*  79. Service or option not implemented, unspec  */
    MN_CALL_INVALID_TRANSACTION_ID_VALUE                    = 81,               /*  81. Invalid transaction identifier value       */
    MN_CALL_USER_NOT_MEMBER_OF_CUG                          = 87,               /*  87. User not member of CUG                     */
    MN_CALL_INCOMPATIBLE_DESTINATION                        = 88,               /*  88. Incompatible destination Incompatible para */
    MN_CALL_INVALID_TRANSIT_NETWORK_SELECTION               = 91,               /*  91. Invalid transit network selection          */
    MN_CALL_SEMANTICALLY_INCORRECT_MESSAGE                  = 95,               /*  95. Semantically incorrect message             */
    MN_CALL_INVALID_MANDATORY_INFORMATION                   = 96,               /*  96. Invalid mandatory information              */
    MN_CALL_MESSAGE_TYPE_NON_EXISTENT                       = 97,               /*  97. Msg type non-existent or not implemented   */
    MN_CALL_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STATE     = 98,               /*  98. Msg type not compatible with protocol state*/
    MN_CALL_IE_NON_EXISTENT_OR_NOT_IMPLEMENTED              = 99,               /*  99. IE non-existent or not implemented         */
    MN_CALL_CONDITIONAL_IE_ERROR                            = 100,              /* 100. Conditional IE error                       */
    MN_CALL_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE      = 101,              /* 101. Message not compatible with protocol state */
    MN_CALL_RECOVERY_ON_TIMER_EXPIRY                        = 102,              /* 102. Recovery on timer expiry Timer number      */
    MN_CALL_PROTOCOL_ERROR_UNSPECIFIED                      = 111,              /* 111. Protocol error, unspecified                */
    MN_CALL_INTERWORKING_UNSPECIFIED                        = 127,               /* 127. Interworking, unspecified                  */
    MN_CALL_CC_CAUSE_BUTT
};
typedef VOS_UINT8   MN_CALL_CC_CAUSE_ENUM_U8;


/* the reason for no num of the incoming call */
enum MN_CALL_NO_CLI_CAUSE_ENUM
{
    MN_CALL_NO_CLI_UNAVAL,                                                      /* num unavailable */
    MN_CALL_NO_CLI_USR_REJ,                                                     /* user reject to provide num */
    MN_CALL_NO_CLI_INTERACT,                                                    /* interact by other service */
    MN_CALL_NO_CLI_PAYPHONE,                                                     /* Pay Phone */
    MN_CALL_NO_CLI_BUTT
};
typedef VOS_UINT8  MN_CALL_NO_CLI_CAUSE_ENUM_U8;

/* 3GPP 27.007 +CSSI/+CSSU */
enum MN_CALL_SS_NOTIFY_CODE_ENUM
{
    MN_CALL_SS_NTFY_UNCOND_FWD_ACTIVE,                                          /* unconditional call forwarding is active  */
    MN_CALL_SS_NTFY_COND_FWD_ACTIVE,                                            /* some of the conditional call forwardings are active  */
    MN_CALL_SS_NTFY_BE_FORWORDED,                                               /* call has been forwarded  */
    MN_CALL_SS_NTFY_IS_WAITING,                                                 /* call is waiting */
    MN_CALL_SS_NTFY_MO_CUG_INFO,                                                /* this is a CUG call (also <index> present)  */
    MN_CALL_SS_NTFY_OUTGOING_BARRED,                                            /* outgoing calls are barred */
    MN_CALL_SS_NTFY_INCOMING_BARRED,                                            /* incoming calls are barred  */
    MN_CALL_SS_NTFY_CLIR_SUPPRESS_REJ,                                          /* CLIR suppression rejected */
    MN_CALL_SS_NTFY_BE_DEFLECTED,                                               /* call has been deflected  */
    MN_CALL_SS_NTFY_FORWORDED_CALL,                                             /* this is a forwarded call (MT call setup)  */
    MN_CALL_SS_NTFY_MT_CUG_INFO,                                                /* this is a CUG call (also <index> present) (MT call setup)  */
    MN_CALL_SS_NTFY_ON_HOLD,                                                    /* call has been put on hold (during a voice call)  */
    MN_CALL_SS_NTFY_RETRIEVED,                                                  /* call has been retrieved (during a voice call) */
    MN_CALL_SS_NTFY_ENTER_MPTY,                                                 /* multiparty call entered (during a voice call) */
    MN_CALL_SS_NTFY_DEFLECTED_CALL,                                             /* this is a deflected call (MT call setup)  */
    MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER,                                     /* Explicit Call Transfer (ECT) Supplementary Service*/
    MN_CALL_SS_NTFY_CCBS_RECALL,                                                /*this is a CCBS recall*/
    MN_CALL_SS_NTFY_CCBS_BE_RECALLED,                                            /*call has been CCBS recalled*/
    MN_CALL_SS_NTFY_BUTT
};
typedef  VOS_UINT8  MN_CALL_SS_NOTIFY_CODE_ENUM_U8;


/* Call Number Type  */
/* ��䷽ʽ����
  ----------------------------------------------------------------
  |   8   |   7   |   6   |   5   |   4   |   3   |   2   |   1   |
  ----------------------------------------------------------------
  |   1   |    Type of number     | Numbering plan identification |
  ----------------------------------------------------------------
*/
enum MN_CALL_EXIT_ENUM
{
    MN_CALL_IS_EXIT     =0x80,                                                        /*000: unknown */
    MN_CALL_EXIT_BUTT
};
typedef VOS_UINT8   MN_CALL_EXIT_ENUM_U8;

/* Type of Number,5,6,7bit of the MN_CALL_NUM_TYPE_ENUM_U8 */
enum MN_CALL_TON_ENUM
{
    MN_CALL_TON_UNKNOWN,                                                        /*000: unknown */
    MN_CALL_TON_INTERNATIONAL,                                                  /*001: international number */
    MN_CALL_TON_NATIONAL,                                                       /*010: national number */
    MN_CALL_TON_NETWORK_SPEC,                                                   /*011: network specific number */
    MN_CALL_TON_SHORT_CODE,                                                      /*100: dedicated access, short code */
    MN_CALL_TON_BUTT
};
typedef VOS_UINT8   MN_CALL_TON_ENUM_U8;

/* Numbering plan identification,1,2,3,4bit fo the MN_CALL_NUM_TYPE_ENUM_U8 */
enum MN_CALL_NPI_ENUM
{
    MN_CALL_NPI_UNKNOWN = 0,                                                    /*0000: unknown */
    MN_CALL_NPI_ISDN,                                                           /*0001: ISDN/telephony numbering plan  */
    MN_CALL_NPI_DATA = 3,                                                       /*0011: data numbering plan  */
    MN_CALL_NPI_TELEX = 4,                                                      /*0100: telex numbering plan  */
    MN_CALL_NPI_NATIONAL = 8,                                                   /*1000: national numbering plane */
    MN_CALL_NPI_PRIVATE,                                                         /*1001: private numbering plan */
    MN_CALL_NPI_BUTT
};
typedef VOS_UINT8   MN_CALL_NPI_ENUM_U8;
typedef VOS_UINT8   MN_CALL_NUM_TYPE_ENUM_U8;

/* Call Number Structure */
#define MN_CALL_MAX_BCD_NUM_LEN         20
typedef struct
{
    MN_CALL_NUM_TYPE_ENUM_U8            enNumType;
    VOS_UINT8                           ucNumLen;
    VOS_UINT8                           ucReserved[2];
    VOS_UINT8                           aucBcdNum[MN_CALL_MAX_BCD_NUM_LEN];
} MN_CALL_BCD_NUM_STRU;


enum MN_CALL_ECT_CALL_STATE_ENUM
{
    MN_CALL_ECT_STATE_ALERTING,
    MN_CALL_ECT_STATE_ACTIVE,
    MN_CALL_ECT_STATE_BUTT
};
typedef VOS_UINT8  MN_CALL_ECT_CALL_STATE_ENUM_U8;

enum MN_CALL_ECT_RDN_ENUM
{
    MN_CALL_ECT_RDN_PRESENTATION_ALLOWED_ADDR,                                  /* presentationAllowedAddress */
    MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED,                                    /* presentationRestricted */
    MN_CALL_ECT_RDN_NUM_NOT_AVAILABLE,                                          /* numberNotAvailableDueToInterworking */
    MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED_ADDR,                                /* presentationRestrictedAddress */
    MN_CALL_ECT_RDN_BUTT
};
typedef VOS_UINT8  MN_CALL_ECT_RDN_ENUM_U8;

typedef struct
{

    MN_CALL_ECT_CALL_STATE_ENUM_U8      enEctCallState;
    MN_CALL_ECT_RDN_ENUM_U8             enEctRdnType;
    VOS_UINT8                           aucReserved[2];

    union
    {
        MN_CALL_BCD_NUM_STRU            stPresentationAllowedAddr;
        MN_CALL_BCD_NUM_STRU            stPresentationRestrictedAddr;
    }rdn;

}MN_CALL_ECT_IND_STRU;

typedef struct
{
    MN_CALL_SS_NOTIFY_CODE_ENUM_U8      enCode;
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulCugIndex;                             /* CUG Index��is valid while Code is MO_CUG_INFO or MT_CUG_INFO */
    MN_CALL_ECT_IND_STRU                stEctIndicator;                         /* */
} MN_CALL_SS_NOTIFY_STRU;

/* ����CSSN������,�����ȥ���� */
enum MN_CALL_SET_CSSN_TYPE_ENUM
{
    MN_CALL_SET_CSSN_DEACT,
    MN_CALL_SET_CSSN_ACT,
    MN_CALL_SET_CSSN_BUTT
};
typedef VOS_UINT32 MN_CALL_SET_CSSN_TYPE_ENUM_U32;

enum MN_CALL_CUUS1_FLG_ENUM
{
    MN_CALL_CUUS1_DISABLE,
    MN_CALL_CUUS1_ENABLE,
    MN_CALL_CUUS1_BUTT
};
typedef VOS_UINT32 MN_CALL_CUUS1_FLG_ENUM_U32;


/* ����UUS1������,�����ȥ���� */
enum MN_CALL_SET_UUS1_TYPE_ENUM
{
    MN_CALL_SET_UUS1_ACT,
    MN_CALL_SET_UUS1_DEACT,
    MN_CALL_SET_UUS1_BUTT
};
typedef VOS_UINT32 MN_CALL_SET_UUS1_TYPE_ENUM_U32;

/* ���û��ϱ�UUS1����Ϣ����,�������м�����Ϣ,�������ANY,��Ĭ��Ϊ
����SETUP,PROGRESS��Ϣֻ���ϱ�,�������� */
enum MN_CALL_UUS1_MSG_TYPE_ENUM
{
    MN_CALL_UUS1_MSG_ANY,
    MN_CALL_UUS1_MSG_SETUP,
    MN_CALL_UUS1_MSG_ALERT,
    MN_CALL_UUS1_MSG_CONNECT,
    MN_CALL_UUS1_MSG_DISCONNECT,
    MN_CALL_UUS1_MSG_RELEASE,
    MN_CALL_UUS1_MSG_RELEASE_COMPLETE,
    MN_CALL_UUS1_MSG_PROGRESS,
    MN_CALL_UUS1_MSG_BUTT
};
typedef VOS_UINT32 MN_CALL_UUS1_MSG_TYPE_ENUM_U32;

#define MN_CALL_MAX_UUS1_MSG_NUM        (7)
#define MN_CALL_MAX_CSSN_MSG_NUM        (2)

/*The user-user is a type 4 information element with a minimum length of 3 octets
and a maximum length of either 35 or 131 octets. In the SETUP message the
user-user information element has a maximum size of 35 octets in a
GSM PLMN. In the USER INFORMATION, ALERTING, CONNECT, DISCONNECT,
PROGRESS, RELEASE and RELEASE COMPLETE messages the user-user information
element has a maximum size of 131 octets in a GSM PLMN.*/

#define MN_CALL_MIN_UUIE_LEN                    (3)
#define MN_CALL_MAX_UUIE_LEN                    (131)
#define MN_CALL_MAX_SETUP_UUIE_CONTEND_LEN      (33)
#define MN_CALL_MAX_OTHER_UUIE_CONTEND_LEN      (129)
#define MN_CALL_MIN_UUIE_CONTEND_LEN            (1)
#define MN_CALL_UUIE_HEADER_LEN                 (2)

/* �˴���UUIE������Э���й涨��UUIE����,������������ */
/********************************************************
  |  8 |  7  | 6 |  5 |  4 |  3 |  2 |  1   |
  |    |     User-user IEI                  | octet 1
  |         Length of user-user contents    | octet 2                           |
  |      User-user protocol discriminator   | octet 3
  |     User-user information               | octet 4*
  |       ...............                   |
  |       ...............                   | octet N*
*********************************************************/
#define MN_CALL_UUS_IEI                         (0x7E)
#define MN_CALL_IEI_POS                         (0x00)
#define MN_CALL_LEN_POS                         (0x01)
#define MN_CALL_PD_POS                          (0x02)
#define MN_CALL_CONTENT_POS                     (0x03)

typedef struct
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType;
    VOS_UINT8                           aucUuie[MN_CALL_MAX_UUIE_LEN];
    VOS_UINT8                           aucReserved1;
}MN_CALL_UUS1_INFO_STRU;


/* Call Event */
enum MN_CALL_EVENT_ENUM
{
    MN_CALL_EVT_ORIG                = 0x00,                                     /* originate a MO Call */
    MN_CALL_EVT_CALL_PROC           = 0x01,                                     /* Call is Proceeding */
    MN_CALL_EVT_ALERTING            = 0x02,                                     /* Alerting,MO Call */
    MN_CALL_EVT_CONNECT             = 0x03,                                     /* Call Connect */
    MN_CALL_EVT_RELEASED            = 0x04,                                     /* Call Released */
    MN_CALL_EVT_INCOMING            = 0x05,                                     /* Incoming Call */
    MN_CALL_EVT_SS_CMD_PROGRESS     = 0x06,                                     /* Call Related Command is in progress */
    MN_CALL_EVT_SS_CMD_RSLT         = 0x07,                                     /* Call Related Command is Completed */
    MN_CALL_EVT_SS_NOTIFY           = 0x08,                                     /* SS Notify */
    MN_CALL_EVT_START_DTMF_CNF      = 0x09,                                     /* Start DTMF tempooralily response */
    MN_CALL_EVT_STOP_DTMF_CNF       = 0x0b,                                     /* Stop DTMF tempooralily response */
    MN_CALL_EVT_CCBS_POSSIBLE       = 0x0d,                                     /* ���Լ���CCBS*/
    MN_CALL_EVT_TIME_EXPIRED        = 0x0e,                                     /*��ʱ*/
    MN_CALL_EVT_UUS1_INFO           = 0x0f,                                     /* UUS1��Ϣ�ϱ� */
    MN_CALL_EVT_GET_CDUR_CNF        = 0x10,                                     /* ͨ��ʱ�� */
    MN_CALL_EVT_CLCC_INFO           = 0x11,                                     /* ��ǰ���к��е���Ϣ */
    MN_CALL_EVT_ALL_RELEASED        = 0x12,                                     /* Call All Released */
    MN_CALL_EVT_SET_UUS1_INFO_CNF   = 0x13,                                     /* �����û���������1��Ϣ */
    MN_CALL_EVT_QRY_UUS1_INFO_CNF   = 0x14,                                     /* ��ѯ�û���������1��Ϣ */
    MN_CALL_EVT_SET_ALS_CNF         = 0x15,                                     /* ���õ�ǰ��·�� */
    MN_CALL_EVT_QRY_ALS_CNF         = 0x16,                                     /* ��ѯ��ǰ��·�� */

    MN_CALL_EVT_ECC_NUM_IND         = 0x17,

    MN_CALL_EVT_HOLD                = 0x18,                                     /* Call Hold ���б��� */
    MN_CALL_EVT_RETRIEVE            = 0x19,                                     /* Call Retrieve ���лָ� */

    MN_CALL_EVT_CLPR_SET_CNF        = 0x1a,
    MN_CALL_EVT_ERR_IND             = 0x1b,

    MN_CALL_EVT_CHANNEL_INFO_IND    = 0x1c,

    MN_CALL_EVT_XLEMA_CNF           = 0x1d,

    MN_CALL_EVT_SET_CSSN_CNF        = 0x1e,

    MN_CALL_EVT_CALL_ORIG_CNF       = 0x1f,
    MN_CALL_EVT_SUPS_CMD_CNF        = 0x20,

    MN_CALL_EVT_START_DTMF_RSLT     = 0x22,
    MN_CALL_EVT_STOP_DTMF_RSLT      = 0x23,

    MN_CALL_EVT_QRY_ECALL_INFO_CNF  = 0x24,
    MN_CALL_EVT_BUTT
};
typedef  VOS_UINT32  MN_CALL_EVENT_ENUM_U32;

/* ��ԭ�е�ö�ٶ�����е��� */
#define TAF_CS_CAUSE_CC_NW_SECTION_BEGIN    (0x0000)
#define TAF_CS_CAUSE_CALL_BEGIN             (0x0400)
#define TAF_CS_CAUSE_IMS_BEGIN              (0x0800)
#define TAF_CS_CAUSE_IMSA_BEGIN             (0x0C00)

enum TAF_CS_CAUSE_ENUM
{
    TAF_CS_CAUSE_SUCCESS                                            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 0),

    /* CS�������ϱ��Ĵ���ԭ��ֵ */
    TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE                             = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 1),   /*   1. Unassigned (unallocated) number            */
    TAF_CS_CAUSE_CC_NW_NO_ROUTE_TO_DEST                             = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 3),   /*   3. No route to destination                    */
    TAF_CS_CAUSE_CC_NW_CHANNEL_UNACCEPTABLE                         = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 6),   /*   6. Channel unacceptable                       */
    TAF_CS_CAUSE_CC_NW_OPERATOR_DETERMINED_BARRING                  = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 8),   /*   8. Operator determined barring                */
    TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING                         = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 16),  /*  16. Normal call clearing                       */
    TAF_CS_CAUSE_CC_NW_USER_BUSY                                    = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 17),  /*  17. User busy                                  */
    TAF_CS_CAUSE_CC_NW_NO_USER_RESPONDING                           = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 18),  /*  18. No user responding                         */
    TAF_CS_CAUSE_CC_NW_USER_ALERTING_NO_ANSWER                      = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 19),  /*  19. User alerting, no answer                   */
    TAF_CS_CAUSE_CC_NW_CALL_REJECTED                                = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 21),  /*  21. Call rejected                              */
    TAF_CS_CAUSE_CC_NW_NUMBER_CHANGED                               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 22),  /*  22. Number changed                             */
    TAF_CS_CAUSE_CC_NW_PRE_EMPTION                                  = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 25),  /*  25. Pre-emption                                */
    TAF_CS_CAUSE_CC_NW_NON_SELECTED_USER_CLEARING                   = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 26),  /*  26. Non selected user clearing                 */
    TAF_CS_CAUSE_CC_NW_DESTINATION_OUT_OF_ORDER                     = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 27),  /*  27. Destination out of order                   */
    TAF_CS_CAUSE_CC_NW_INVALID_NUMBER_FORMAT                        = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 28),  /*  28. Invalid number format                      */
    TAF_CS_CAUSE_CC_NW_FACILITY_REJECTED                            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 29),  /*  29. Facility rejected                          */
    TAF_CS_CAUSE_CC_NW_RESPONSE_TO_STATUS_ENQUIRY                   = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 30),  /*  30. Response to STATUS ENQUIRY                 */
    TAF_CS_CAUSE_CC_NW_NORMAL_UNSPECIFIED                           = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 31),  /*  31. Normal, unspecified                        */
    TAF_CS_CAUSE_CC_NW_NO_CIRCUIT_CHANNEL_AVAILABLE                 = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 34),  /*  34. No circuit/channel available               */
    TAF_CS_CAUSE_CC_NW_NETWORK_OUT_OF_ORDER                         = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 38),  /*  38. Network out of order                       */
    TAF_CS_CAUSE_CC_NW_TEMPORARY_FAILURE                            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 41),  /*  41. Temporary failure                          */
    TAF_CS_CAUSE_CC_NW_SWITCHING_EQUIPMENT_CONGESTION               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 42),  /*  42. Switching equipment congestion             */
    TAF_CS_CAUSE_CC_NW_ACCESS_INFORMATION_DISCARDED                 = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 43),  /*  43. Access information discarded               */
    TAF_CS_CAUSE_CC_NW_REQUESTED_CIRCUIT_CHANNEL_NOT_AVAILABLE      = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 44),  /*  44. requested circuit/channel not available    */
    TAF_CS_CAUSE_CC_NW_RESOURCES_UNAVAILABLE_UNSPECIFIED            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 47),  /*  47. Resources unavailable, unspecified         */
    TAF_CS_CAUSE_CC_NW_QUALITY_OF_SERVICE_UNAVAILABLE               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 49),  /*  49. Quality of service unavailable             */
    TAF_CS_CAUSE_CC_NW_REQUESTED_FACILITY_NOT_SUBSCRIBED            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 50),  /*  50. Requested facility not subscribed          */
    TAF_CS_CAUSE_CC_NW_INCOMING_CALL_BARRED_WITHIN_CUG              = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 55),  /*  55. Incoming calls barred within the CUG       */
    TAF_CS_CAUSE_CC_NW_BEARER_CAPABILITY_NOT_AUTHORISED             = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 57),  /*  57. Bearer capability not authorized           */
    TAF_CS_CAUSE_CC_NW_BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE    = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 58),  /*  58. Bearer capability not presently available  */
    TAF_CS_CAUSE_CC_NW_SERVICE_OR_OPTION_NOT_AVAILABLE              = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 63),  /*  63. Service or option not available, unspec    */
    TAF_CS_CAUSE_CC_NW_BEARER_SERVICE_NOT_IMPLEMENTED               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 65),  /*  65. Bearer service not implemented             */
    TAF_CS_CAUSE_CC_NW_ACM_GEQ_ACMMAX                               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 68),  /*  68. ACM equal to or greater than ACMmax        */
    TAF_CS_CAUSE_CC_NW_REQUESTED_FACILITY_NOT_IMPLEMENTED           = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 69),  /*  69. Requested facility not implemented         */
    TAF_CS_CAUSE_CC_NW_ONLY_RESTRICTED_DIGITAL_INFO_BC_AVAILABLE    = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 70),  /*  70. Only restricted digital info BC available  */
    TAF_CS_CAUSE_CC_NW_SERVICE_OR_OPTION_NOT_IMPLEMENTED            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 79),  /*  79. Service or option not implemented, unspec  */
    TAF_CS_CAUSE_CC_NW_INVALID_TRANSACTION_ID_VALUE                 = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 81),  /*  81. Invalid transaction identifier value       */
    TAF_CS_CAUSE_CC_NW_USER_NOT_MEMBER_OF_CUG                       = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 87),  /*  87. User not member of CUG                     */
    TAF_CS_CAUSE_CC_NW_INCOMPATIBLE_DESTINATION                     = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 88),  /*  88. Incompatible destination Incompatible para */
    TAF_CS_CAUSE_CC_NW_INVALID_TRANSIT_NETWORK_SELECTION            = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 91),  /*  91. Invalid transit network selection          */
    TAF_CS_CAUSE_CC_NW_SEMANTICALLY_INCORRECT_MESSAGE               = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 95),  /*  95. Semantically incorrect message             */
    TAF_CS_CAUSE_CC_NW_INVALID_MANDATORY_INFORMATION                = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 96),  /*  96. Invalid mandatory information              */
    TAF_CS_CAUSE_CC_NW_MESSAGE_TYPE_NON_EXISTENT                    = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 97),  /*  97. Msg type non-existent or not implemented   */
    TAF_CS_CAUSE_CC_NW_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STATE  = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 98),  /*  98. Msg type not compatible with protocol state*/
    TAF_CS_CAUSE_CC_NW_IE_NON_EXISTENT_OR_NOT_IMPLEMENTED           = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 99),  /*  99. IE non-existent or not implemented         */
    TAF_CS_CAUSE_CC_NW_CONDITIONAL_IE_ERROR                         = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 100), /* 100. Conditional IE error                       */
    TAF_CS_CAUSE_CC_NW_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE   = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 101), /* 101. Message not compatible with protocol state */
    TAF_CS_CAUSE_CC_NW_RECOVERY_ON_TIMER_EXPIRY                     = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 102), /* 102. Recovery on timer expiry Timer number      */
    TAF_CS_CAUSE_CC_NW_PROTOCOL_ERROR_UNSPECIFIED                   = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 111), /* 111. Protocol error, unspecified                */
    TAF_CS_CAUSE_CC_NW_INTERWORKING_UNSPECIFIED                     = (TAF_CS_CAUSE_CC_NW_SECTION_BEGIN + 127), /* 127. Interworking, unspecified                  */

    /* ƽ̨�ڲ��Ĵ���ԭ��ֵ */
    TAF_CS_CAUSE_INVALID_PARAMETER                                  = (TAF_CS_CAUSE_CALL_BEGIN + 1),            /* �������� */
    TAF_CS_CAUSE_SIM_NOT_EXIST                                      = (TAF_CS_CAUSE_CALL_BEGIN + 2),            /* USIM�������� */
    TAF_CS_CAUSE_SIM_PIN_NEED                                       = (TAF_CS_CAUSE_CALL_BEGIN + 3),            /* ��ҪSIM����PIN�� */
    TAF_CS_CAUSE_NO_CALL_ID                                         = (TAF_CS_CAUSE_CALL_BEGIN + 4),            /* Call Id ����ʧ�� */
    TAF_CS_CAUSE_NOT_ALLOW                                          = (TAF_CS_CAUSE_CALL_BEGIN + 5),            /* ���б���ֹ */
    TAF_CS_CAUSE_STATE_ERROR                                        = (TAF_CS_CAUSE_CALL_BEGIN + 6),            /* ��ǰ����״̬�쳣 */
    TAF_CS_CAUSE_FDN_CHECK_FAILURE                                  = (TAF_CS_CAUSE_CALL_BEGIN + 8),            /* FDN���ʧ�� */
    TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY                        = (TAF_CS_CAUSE_CALL_BEGIN + 9),            /* CALL CONTROLҵ���޸��˺��в�����UE��֧���޸ĺ�Ĳ��� */
    TAF_CS_CAUSE_CALL_CTRL_TIMEOUT                                  = (TAF_CS_CAUSE_CALL_BEGIN + 10),           /* CALL CONTROLҵ��ȴ�USIM����Ӧ��ʱ */
    TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED                              = (TAF_CS_CAUSE_CALL_BEGIN + 11),           /* CALL CONTROLҵ��USIM��ֹ���� */
    TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER                        = (TAF_CS_CAUSE_CALL_BEGIN + 13),           /* CALL CTRLҵ�����ʧ�ܻ�����Ϣʧ�ܶ���Ϊ�������� */
    TAF_CS_CAUSE_DTMF_BUF_FULL                                      = (TAF_CS_CAUSE_CALL_BEGIN + 14),           /* DTMF�������� */
    TAF_CS_CAUSE_DTMF_REPEAT_STOP                                   = (TAF_CS_CAUSE_CALL_BEGIN + 15),           /* �ظ���STOP DTMF���� */
    TAF_CS_CAUSE_DTMF_REJ                                           = (TAF_CS_CAUSE_CALL_BEGIN + 16),           /* ����ܾ�START DTMF���� */
    TAF_CS_CAUSE_CALL_ON_HOLD                                       = (TAF_CS_CAUSE_CALL_BEGIN + 17),           /* ���б����� */
    TAF_CS_CAUSE_CALL_RELEASE                                       = (TAF_CS_CAUSE_CALL_BEGIN + 18),           /* �����ͷ� */
    TAF_CS_CAUSE_POWER_OFF                                          = (TAF_CS_CAUSE_CALL_BEGIN + 19),           /* ���ػ� */
    TAF_CS_CAUSE_NOT_IN_SPEECH_CALL                                 = (TAF_CS_CAUSE_CALL_BEGIN + 20),           /* ��ǰû�п���ͨ�� */
    TAF_CS_CAUSE_SIM_INVALID                                        = (TAF_CS_CAUSE_CALL_BEGIN + 21),           /* ����Ч */

    TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE                           = (TAF_CS_CAUSE_CALL_BEGIN + 22),           /* ҵ����ѡ��ʧ�� */
    TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED                     = (TAF_CS_CAUSE_CALL_BEGIN + 23),           /* ҵ����ѡ�񻺴泬ʱ */
    /* TAF_CS_CAUSE_DOMAIN_SELECTION_POWER_OFFɾ����ͳһ��TAF_CS_CAUSE_POWER_OFF */

    TAF_CS_CAUSE_ECALL_MODE_NOT_ALLOWED                             = (TAF_CS_CAUSE_CALL_BEGIN + 26),           /* ECALL����ģʽ������ */
    TAF_CS_CAUSE_ECALL_CACHE_MSG_FAIL                               = (TAF_CS_CAUSE_CALL_BEGIN + 27),           /* ������Ϣʧ�� */
    TAF_CS_CAUSE_ECALL_LOWERPOWER_POWER_ON_FAIL                     = (TAF_CS_CAUSE_CALL_BEGIN + 28),           /* �±�״̬�¿���ʧ�� */
    TAF_CS_CAUSE_CALL_NUMBER_NOT_EXIST                              = (TAF_CS_CAUSE_CALL_BEGIN + 29),

    TAF_CS_CAUSE_NO_RF                                              = (TAF_CS_CAUSE_CALL_BEGIN + 30),

    TAF_CS_CAUSE_UNKNOWN                                            = (TAF_CS_CAUSE_CALL_BEGIN + 0xFF),         /* δ֪���� */

    /* IMS�Ĵ���ԭ��ֵ */
    TAF_CS_CAUSE_IMS_MULTIPLE_CHOICES                               = (TAF_CS_CAUSE_IMS_BEGIN + 300),
    TAF_CS_CAUSE_IMS_MOVED_PERMANENTLY                              = (TAF_CS_CAUSE_IMS_BEGIN + 301),
    TAF_CS_CAUSE_IMS_MOVED_TEMPORARILY                              = (TAF_CS_CAUSE_IMS_BEGIN + 302),
    TAF_CS_CAUSE_IMS_USE_PROXY                                      = (TAF_CS_CAUSE_IMS_BEGIN + 305),
    TAF_CS_CAUSE_IMS_ALTERNATIVE_SERVICE                            = (TAF_CS_CAUSE_IMS_BEGIN + 380),
    TAF_CS_CAUSE_IMS_BAD_REQUEST                                    = (TAF_CS_CAUSE_IMS_BEGIN + 400),
    TAF_CS_CAUSE_IMS_UNAUTHORIZED                                   = (TAF_CS_CAUSE_IMS_BEGIN + 401),
    TAF_CS_CAUSE_IMS_PAYMENT_REQUIRED                               = (TAF_CS_CAUSE_IMS_BEGIN + 402),
    TAF_CS_CAUSE_IMS_FORBIDDEN                                      = (TAF_CS_CAUSE_IMS_BEGIN + 403),
    TAF_CS_CAUSE_IMS_NOT_FOUND                                      = (TAF_CS_CAUSE_IMS_BEGIN + 404),
    TAF_CS_CAUSE_IMS_METHOD_NOT_ALLOWED                             = (TAF_CS_CAUSE_IMS_BEGIN + 405),
    TAF_CS_CAUSE_IMS_NOT_ACCEPTABLE                                 = (TAF_CS_CAUSE_IMS_BEGIN + 406),
    TAF_CS_CAUSE_IMS_PROXY_AUTHENTICATION_REQUIRED                  = (TAF_CS_CAUSE_IMS_BEGIN + 407),
    TAF_CS_CAUSE_IMS_REQUEST_TIMEOUT                                = (TAF_CS_CAUSE_IMS_BEGIN + 408),
    TAF_CS_CAUSE_IMS_CONFLICT_DEPRECATED                            = (TAF_CS_CAUSE_IMS_BEGIN + 409),
    TAF_CS_CAUSE_IMS_GONE                                           = (TAF_CS_CAUSE_IMS_BEGIN + 410),
    TAF_CS_CAUSE_IMS_CONDITIONAL_REQUEST_FAILED                     = (TAF_CS_CAUSE_IMS_BEGIN + 412),
    TAF_CS_CAUSE_IMS_REQUEST_ENTITY_TOO_LARGE                       = (TAF_CS_CAUSE_IMS_BEGIN + 413),
    TAF_CS_CAUSE_IMS_REQUEST_URI_TOO_LONG                           = (TAF_CS_CAUSE_IMS_BEGIN + 414),
    TAF_CS_CAUSE_IMS_UNSUPPORTED_MEDIA_TYPE                         = (TAF_CS_CAUSE_IMS_BEGIN + 415),
    TAF_CS_CAUSE_IMS_UNSUPPORTED_URI_SCHEME                         = (TAF_CS_CAUSE_IMS_BEGIN + 416),
    TAF_CS_CAUSE_IMS_UNKNOWN_RESOURCE_PRIORITY                      = (TAF_CS_CAUSE_IMS_BEGIN + 417),
    TAF_CS_CAUSE_IMS_BAD_EXTENSION                                  = (TAF_CS_CAUSE_IMS_BEGIN + 420),
    TAF_CS_CAUSE_IMS_EXTENSION_REQUIRED                             = (TAF_CS_CAUSE_IMS_BEGIN + 421),
    TAF_CS_CAUSE_IMS_SESSION_INTERVAL_TOO_SMALL                     = (TAF_CS_CAUSE_IMS_BEGIN + 422),
    TAF_CS_CAUSE_IMS_INTERVAL_TOO_BRIEF                             = (TAF_CS_CAUSE_IMS_BEGIN + 423),
    TAF_CS_CAUSE_IMS_BAD_LOCATION_INFORMATION                       = (TAF_CS_CAUSE_IMS_BEGIN + 424),
    TAF_CS_CAUSE_IMS_USE_IDENTITY_HEADER                            = (TAF_CS_CAUSE_IMS_BEGIN + 428),
    TAF_CS_CAUSE_IMS_PROVIDE_REFERRER_IDENTITY                      = (TAF_CS_CAUSE_IMS_BEGIN + 429),
    TAF_CS_CAUSE_IMS_FLOW_FAILED                                    = (TAF_CS_CAUSE_IMS_BEGIN + 430),
    TAF_CS_CAUSE_IMS_ANONYMITY_DISALLOWED                           = (TAF_CS_CAUSE_IMS_BEGIN + 433),
    TAF_CS_CAUSE_IMS_BAD_IDENTITY_INFO                              = (TAF_CS_CAUSE_IMS_BEGIN + 436),
    TAF_CS_CAUSE_IMS_UNSUPPORTED_CERTIFICATE                        = (TAF_CS_CAUSE_IMS_BEGIN + 437),
    TAF_CS_CAUSE_IMS_INVALID_IDENTITY_HEADER                        = (TAF_CS_CAUSE_IMS_BEGIN + 438),
    TAF_CS_CAUSE_IMS_FIRST_HOP_LACKS_OUTBOUND_SUPPORT               = (TAF_CS_CAUSE_IMS_BEGIN + 439),
    TAF_CS_CAUSE_IMS_MAX_BREADTH_EXCEEDED                           = (TAF_CS_CAUSE_IMS_BEGIN + 440),
    TAF_CS_CAUSE_IMS_BAD_INFO_PACKEAGE                              = (TAF_CS_CAUSE_IMS_BEGIN + 469),
    TAF_CS_CAUSE_IMS_CONSENT_NEEDED                                 = (TAF_CS_CAUSE_IMS_BEGIN + 470),
    TAF_CS_CAUSE_IMS_TEMPORARILY_UNAVAILABLE                        = (TAF_CS_CAUSE_IMS_BEGIN + 480),
    TAF_CS_CAUSE_IMS_CALL_TRANSACTION_DOES_NOT_EXIST                = (TAF_CS_CAUSE_IMS_BEGIN + 481),
    TAF_CS_CAUSE_IMS_LOOP_DETECTED                                  = (TAF_CS_CAUSE_IMS_BEGIN + 482),
    TAF_CS_CAUSE_IMS_TOO_MANY_HOPS                                  = (TAF_CS_CAUSE_IMS_BEGIN + 483),
    TAF_CS_CAUSE_IMS_ADDRESS_INCOMPLETE                             = (TAF_CS_CAUSE_IMS_BEGIN + 484),
    TAF_CS_CAUSE_IMS_AMBIGUOUS                                      = (TAF_CS_CAUSE_IMS_BEGIN + 485),
    TAF_CS_CAUSE_IMS_BUSY_HERE                                      = (TAF_CS_CAUSE_IMS_BEGIN + 486),
    TAF_CS_CAUSE_IMS_REQUEST_TERMINATED                             = (TAF_CS_CAUSE_IMS_BEGIN + 487),
    TAF_CS_CAUSE_IMS_NOT_ACCEPTABLE_HERE                            = (TAF_CS_CAUSE_IMS_BEGIN + 488),
    TAF_CS_CAUSE_IMS_BAD_EVENT                                      = (TAF_CS_CAUSE_IMS_BEGIN + 489),
    TAF_CS_CAUSE_IMS_REQUEST_PENDING                                = (TAF_CS_CAUSE_IMS_BEGIN + 491),
    TAF_CS_CAUSE_IMS_UNDECIPHERABLE                                 = (TAF_CS_CAUSE_IMS_BEGIN + 493),
    TAF_CS_CAUSE_IMS_SECURITY_AGREEMENT_REQUIRED                    = (TAF_CS_CAUSE_IMS_BEGIN + 494),
    TAF_CS_CAUSE_IMS_SERVER_INTERNAL_ERROR                          = (TAF_CS_CAUSE_IMS_BEGIN + 500),
    TAF_CS_CAUSE_IMS_NOT_IMPLEMENTED                                = (TAF_CS_CAUSE_IMS_BEGIN + 501),
    TAF_CS_CAUSE_IMS_BAD_GATEWAY                                    = (TAF_CS_CAUSE_IMS_BEGIN + 502),
    TAF_CS_CAUSE_IMS_SERVICE_UNAVAILABLE                            = (TAF_CS_CAUSE_IMS_BEGIN + 503),
    TAF_CS_CAUSE_IMS_SERVER_TIME_OUT                                = (TAF_CS_CAUSE_IMS_BEGIN + 504),
    TAF_CS_CAUSE_IMS_VERSION_NOT_SUPPORTED                          = (TAF_CS_CAUSE_IMS_BEGIN + 505),
    TAF_CS_CAUSE_IMS_MESSAGE_TOO_LARGE                              = (TAF_CS_CAUSE_IMS_BEGIN + 513),
    TAF_CS_CAUSE_IMS_PRECONDITION_FAILURE                           = (TAF_CS_CAUSE_IMS_BEGIN + 580),
    TAF_CS_CAUSE_IMS_BUSY_EVERYWHERE                                = (TAF_CS_CAUSE_IMS_BEGIN + 600),
    TAF_CS_CAUSE_IMS_DECLINE                                        = (TAF_CS_CAUSE_IMS_BEGIN + 603),
    TAF_CS_CAUSE_IMS_DOES_NOT_EXIST_ANYWHERE                        = (TAF_CS_CAUSE_IMS_BEGIN + 604),
    TAF_CS_CAUSE_IMS_GLOBAL_NOT_ACCEPTABLE                          = (TAF_CS_CAUSE_IMS_BEGIN + 606),

    /* IMSA�Ĵ���ԭ��ֵ */
    TAF_CS_CAUSE_IMSA_ERROR                                         = (TAF_CS_CAUSE_IMSA_BEGIN + 1),            /* һ����� */
    TAF_CS_CAUSE_IMSA_NOT_SUPPORTED_CMD                             = (TAF_CS_CAUSE_IMSA_BEGIN + 2),            /* IMSA��֧�ָ����� */
    TAF_CS_CAUSE_IMSA_ALLOC_ENTITY_FAIL                             = (TAF_CS_CAUSE_IMSA_BEGIN + 3),            /* IMSA�������ʵ��ʧ�� */
    TAF_CS_CAUSE_IMSA_RETRY_VIA_CS                                  = (TAF_CS_CAUSE_IMSA_BEGIN + 4),            /* ͨ��CS���ٳ��Դ˺��� */
    TAF_CS_CAUSE_IMSA_TIMEOUT                                       = (TAF_CS_CAUSE_IMSA_BEGIN + 5),            /* ����ִ�г�ʱ */
    TAF_CS_CAUSE_IMSA_NOT_SUPPORTED_CALL_TYPE                       = (TAF_CS_CAUSE_IMSA_BEGIN + 6),            /* ��֧�ֵĺ������� */
    TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE                         = (TAF_CS_CAUSE_IMSA_BEGIN + 7),            /* ���ж�Ӧ�ķ��񲻿��� */
    TAF_CS_CAUSE_IMSA_SRVCCING_BUFF_MSG_FAIL                        = (TAF_CS_CAUSE_IMSA_BEGIN + 8),            /* SRVCC�����л�����Ϣʧ�� */
    TAF_CS_CAUSE_IMSA_SRVCC_SUCC                                    = (TAF_CS_CAUSE_IMSA_BEGIN + 9),            /* SRVCC�ɹ� */
    TAF_CS_CAUSE_IMSA_SRVCC_ABNORMAL                                = (TAF_CS_CAUSE_IMSA_BEGIN + 10),           /* SRVCC�쳣������ػ��� */
    TAF_CS_CAUSE_IMSA_SRVCC_ABNORMAL_DEREG                          = (TAF_CS_CAUSE_IMSA_BEGIN + 11),           /* SRVCC�����г���DEREG */

    TAF_CS_CAUSE_BUTT                                               = (0xFFFF)
};
typedef  VOS_UINT32  TAF_CS_CAUSE_ENUM_UINT32;

/* [10.5.4.8] Called party subaddress */
/*============================================================================*/
/* Table 10.5.119/3GPP TS 24.008: Called party subaddress */
typedef enum                                                                    /* Type of subaddress (octet 3)      */
{                                                                               /* Bits 7 6 5                        */
    MN_CALL_SUBADDR_NSAP                = 0,                                    /*      0 0 0 NSAP                   */
    MN_CALL_USER_SPEC                   = 2                                     /*      0 1 0 User specified         */
}MN_CALL_TYPE_OF_SUBADDR_ENUM;                                                  /* All other values are reserved     */
typedef VOS_UINT8   MN_CALL_TYPE_OF_SUBADDR_ENUM_UINT8;

/* [10.5.4.9] Calling party BCD number */
/*============================================================================*/
/* Table 10.5.120/3GPP TS 24.008: Calling party BCD number */
typedef enum                                                                    /* Presentation indicator (octet 3a) */
{                                                                               /* Bits 7 6                          */
    MN_CALL_PRESENTATION_ALLOWED                             = 0,               /*      0 0 Presentation allowed     */
    MN_CALL_PRESENTATION_RESTRICTED                          = 1,               /*      0 1 Presentation restricted  */
    MN_CALL_PRESENTATION_NOT_AVAILABLE                       = 2,               /*      1 0 Number not available     */
    MN_CALL_PRESENTATION_RESERVED                            = 3                /*      1 1 Reserved                 */
}MN_CALL_PRESENTATION_IND_ENUM;
typedef VOS_UINT8   MN_CALL_PRESENTATION_IND_ENUM_UINT8;


/* Added by f62575 for STK&DCM Project, 2012/09/18, begin */
/*****************************************************************************
 �ṹ��    : MN_CALL_SUBADDR_STRU
 �ṹ˵��  : �����ӵ�ַ���ýṹ

  1.��    ��   : 2012��09��18��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;
    VOS_UINT8                           Octet3;
    VOS_UINT8                           SubAddrInfo[MN_CALL_MAX_SUBADDR_INFO_LEN];
    VOS_UINT8                           ucReserved;
}MN_CALL_SUBADDR_STRU;
/* Added by f62575 for STK&DCM Project, 2012/09/18, end */

#define MN_CALL_MAX_CALLED_BCD_NUM_LEN      (40)                                /* 3GPP TS 24.008 10.5.4.7 */
#define MN_CALL_MAX_CALLED_ASCII_NUM_LEN    (MN_CALL_MAX_CALLED_BCD_NUM_LEN * 2)

typedef struct
{
    MN_CALL_NUM_TYPE_ENUM_U8            enNumType;
    VOS_UINT8                           ucNumLen;
    VOS_UINT8                           aucBcdNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN];
    VOS_UINT8                           aucReserved[2];
}MN_CALL_CALLED_NUM_STRU;


typedef struct
{
    VOS_BOOL                            bExist;
    VOS_UINT8                           ucEmergencyCat;
    VOS_UINT8                           aucReserve[3];
}MN_CALL_EMERGENCY_CAT_STRU;





typedef struct
{
    VOS_UINT8                           ucIsUser;
    VOS_UINT8                           ucDiscCallFlag;
    VOS_UINT8                           aucReserved[2];
}MN_CALL_DISC_DIR;

/* Call Info Structure */
typedef struct
{
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    /* Modified by f62575 for STK&DCM Project, 2012/09/18, begin */
    MN_OPERATION_ID_T                   opId;                                   /* op ID */
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    /* Modified by f62575 for STK&DCM Project, 2012/09/18, end */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;                            /* MPTY State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_MODE_ENUM_U8                enCallMode;                             /* Call Mode */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* Call Direction(MO/MT) */
    MN_CALL_PRESENTATION_IND_ENUM_UINT8 enCallingPI;

    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;
    VOS_UINT8                           aucReserved1;

    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;                          /* Data Configuration */
    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number */
    /* Added by f62575 for STK&DCM Project, 2012/09/18, begin */
    MN_CALL_SUBADDR_STRU                stSubCallNumber;                        /* Call SubAddress */
    /* Added by f62575 for STK&DCM Project, 2012/09/18, end */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number */
    MN_CALL_SUBADDR_STRU                stCalledSubAddr;                        /* Called SubAddress */
    MN_CALL_BCD_NUM_STRU                stRedirectNumber;                       /* Redirect Number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Redirect Call SubAddress */

    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd;                          /* Call Management Command */
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult;                             /* the result of the last Call Management Command */
    MN_CALL_SS_ERR_CODE_ENUM_U8         enSsErrCode;                            /* SS Error Code */
    VOS_UINT8                           ucRabId;                                /* RAB ID */
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause;                           /* Cause of the NO CLI */
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNo;                            /* ALS Line number: 1 or 2,default is 1*/

    /* VOS_TRUE:ata�첽�ϱ�ok������connect���ϱ�ok����������connect ack��
       VOS_FALSE:ataͬ���ϱ�������connect����յ�����connect ack�����ϱ�ok */
    VOS_UINT8                           ucAtaReportOkAsyncFlag;

    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    MN_CALL_SS_NOTIFY_STRU              stSsNotify;                             /* SS Notify */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */
    TAF_SS_CCBS_FEATURE_STRU            stCcbsFeature;                          /* CCBS feature info*/
    MN_CALL_UUS1_INFO_STRU              stUusInfo;
    VOS_UINT32                          ulCurCallTime;
    VOS_UINT32                          ulTotalCallTime;                        /*�ۼ�ͨ��ʱ��*/
    VOS_UINT32                          ulPreCallTime;                          /*�ϴ�ͨ��ʱ��*/

    MN_CALL_DISC_DIR                    stDiscDir;                              /* �Ҷϵ绰�ķ��� */


    VOS_UINT8                           aucCurcRptCfg[MN_CALL_RPT_CFG_MAX_SIZE];        /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                           aucUnsolicitedRptCfg[MN_CALL_RPT_CFG_MAX_SIZE]; /* �����������õ������ϱ���ʶ */
} MN_CALL_INFO_STRU;


typedef struct
{
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_CLIR_CFG_ENUM_U8            enClirCfg;                              /* CLIR Configuration */
    MN_CALL_MODE_ENUM_U8                enCallMode;                             /* Call Mode */
    VOS_UINT8                           ucCsCallRetryFlg;                       /* CS CALL�Ƿ���ٳ��Ա��:��CS����ã���CS��δ���Թ�����ʱ����ʾCS������ٳ��� VOS_TRUE�������������ʾCS�򲻿����ٳ��� VOS_FALSE */
    MN_CALL_CALLED_NUM_STRU             stDialNumber;                           /* Call Number */
    MN_CALL_CUG_CFG_STRU                stCugCfg;                               /* CUG Configuration */
    MN_CALL_CS_DATA_CFG_STRU            stDataCfg;                              /* Data Configuration */
    MN_CALL_SUBADDR_STRU                stSubaddr;                              /* Subaddress */

    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;                         /* Emergency Catory */

    VOS_UINT8                           ucImsInvitePtptFlag;                    /* IMS ���������ͨ����� */
    VOS_UINT8                           aucReserved[3];
} MN_CALL_ORIG_PARAM_STRU;


typedef struct
{
    MN_CALL_CC_CAUSE_ENUM_U8            enEndCause;                             /* End Cause */
} MN_CALL_END_PARAM_STRU;


typedef struct
{
    VOS_UINT32                          ulReserved;
} MN_CALL_ANS_PARAM_STRU;

/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */

typedef struct
{
    MN_CALL_ID_T                        CallId;                                 /* ����ID��0: ������ǰĬ�Ϻ��� */
    VOS_CHAR                            cKey;                                   /* DTMF Key ֻ��START_DTMFʱ��ע */
    VOS_UINT16                          usOnLength;                             /* DTMF����ʱ��(��λms)��0: ����ֹͣDTMF */

    VOS_UINT16                          usOffLength;                            /* stop dtmf req��start dtmf req���͵�ʱ����(��λms)
                                                                                 ����70msС��600ms */
    VOS_UINT8                           aucReserved[2];
} TAF_CALL_DTMF_PARAM_STRU;
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

typedef struct
{
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd;                          /* Call Management Command */
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    VOS_UINT8                           ucReserved[2];
    MN_CALL_BCD_NUM_STRU                stRedirectNum;                          /* Redirect Number */
} MN_CALL_SUPS_PARAM_STRU;


typedef struct
{
    VOS_UINT32                          ulActNum;                               /* ��Ҫ���õ�CSSN�ĸ��� */
    MN_CALL_SET_CSSN_TYPE_ENUM_U32      aenSetType[MN_CALL_MAX_CSSN_MSG_NUM];   /* aenSetType[0]:CSSI�Ƿ���Ҫ���enSetType[1]:CSSU�Ƿ���Ҫ���� */
}MN_CALL_SET_CSSN_REQ_STRU;



typedef struct
{
    MN_CALL_CUUS1_FLG_ENUM_U32          enCuus1IFlg;                            /* CUUS1I��־ */
    MN_CALL_CUUS1_FLG_ENUM_U32          enCuus1UFlg;                            /* CUUS1U��־ */
    VOS_UINT32                          ulActNum;                             /*��Ҫ���õ�UUS1�ĸ���*/
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType[MN_CALL_MAX_UUS1_MSG_NUM];  /*Ҫ���õ��û���������1����*/
    MN_CALL_UUS1_INFO_STRU              stUus1Info[MN_CALL_MAX_UUS1_MSG_NUM]; /*���õ��û�����������Ϣ*/
}MN_CALL_UUS1_PARAM_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32  enEvent;    /*�ظ����¼�����*/
    MN_CLIENT_ID_T          ClientId;   /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;       /*����ID*/
    VOS_UINT8               ucReserved; /* �����ֶ� */
    VOS_UINT32              ulRet;      /*�ظ����*/
}TAF_PH_SET_UUS1_INFO_CNF_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32  enEvent;                                /*�ظ����¼�����*/
    MN_CLIENT_ID_T          ClientId;                               /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;                                   /*����ID*/
    VOS_UINT8               ucReserved;                             /* �����ֶ� */
    VOS_UINT32              ulRet;                                  /*�ظ����*/
    VOS_UINT32              ulActNum;                               /*�û���������1�ĸ���*/
    MN_CALL_UUS1_INFO_STRU  stUus1Info[MN_CALL_MAX_UUS1_MSG_NUM];   /*�û���������1����Ϣ*/
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      aenSetType[MN_CALL_MAX_UUS1_MSG_NUM];  /*Ҫ���õ��û���������1���� */
}TAF_PH_QRY_UUS1_INFO_CNF_STRU;


typedef struct
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;          /*Ҫʹ�õ���·��*/
    VOS_UINT8                           aucReserved[3];     /*�����ֶ�*/
}MN_CALL_SET_ALS_PARAM_STRU;


typedef struct
{
    MN_CALL_EVENT_ENUM_U32  enEvent;    /*�ظ����¼�����*/
    MN_CLIENT_ID_T          ClientId;   /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;       /*����ID*/
    VOS_UINT8               ucReserved; /* �����ֶ� */
    VOS_UINT32              ulRet;      /*�ظ����*/
}MN_CALL_SET_ALS_CNF_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32          enEvent;                                    /*�ظ����¼�����*/
    MN_CLIENT_ID_T                  ClientId;                                   /*�˿ں�*/
    MN_OPERATION_ID_T               OpId;                                       /*����ID*/
    VOS_UINT8                       ucReserved1;                                /* �����ֶ� */
    VOS_UINT32                      ulRet;                                      /*�ظ����*/
    MN_CALL_ALS_LINE_NO_ENUM_U8     enAlsLine;                                  /*��ǰʹ�õ���·��*/
    VOS_UINT8                       aucReserved2[3];                            /* �����ֶ� */
}MN_CALL_QRY_ALS_CNF_STRU;
typedef struct
{
    VOS_UINT8                           ucIndex;                                /* ���ƽ������������� */
    VOS_UINT8                           ucTotal;                                /* ���ƽ������������� */
    VOS_UINT8                           ucCategory;                             /* �������������� */
    VOS_UINT8                           ucSimPresent;                           /* �������������п�ʱ��Ч�����޿�ʱ��Ч��1�п�ʱ��Ч��0�޿�ʱ��Ч */
    MN_CALL_BCD_NUM_STRU                stEccNum;                               /* ���������� */
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} MN_CALL_ECC_LIST_INFO_STRU;


typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* Call Direction(MO/MT) */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;                            /* MPTY State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_CHAR                            aucReserved[2];                         /* �����ֶ� */
    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number */
    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
}MN_CALL_INFO_PARAM_STRU;


typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /* �¼��� */
    MN_CLIENT_ID_T                      clientId;                               /* �û�ID */
    VOS_UINT8                           ucNumOfCalls;                           /* ��������ͨ���ĸ��� */
    VOS_CHAR                            ucReserved;                             /* �����ֶ� */
    MN_CALL_INFO_PARAM_STRU             astCallInfos[MN_CALL_MAX_NUM];           /* ��������ͨ������Ϣ */
} MN_CALL_INFO_QRY_CNF_STRU;
typedef struct
{
    VOS_UINT8                           ucIndex;                                /* ���ƽ������������� */
    VOS_UINT8                           ucTotal;                                /* ���ƽ������������� */
    VOS_UINT8                           ucCategory;                             /* �������������� */
    VOS_UINT8                           ucSimPresent;                           /* �������������п�ʱ��Ч�����޿�ʱ��Ч��1�п�ʱ��Ч��0�޿�ʱ��Ч */
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    MN_CALL_BCD_NUM_STRU                stEccNum;                               /* ���������� */
}MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucCategory;                             /* �������������� */
    VOS_UINT8                           ucValidSimPresent;                      /* �������������п�ʱ��Ч�����޿�ʱ��Ч��1�п�ʱ��Ч��0�޿�ʱ��Ч */
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           ucEccNumLen;
    VOS_UINT8                           aucEccNum[MN_CALL_MAX_BCD_NUM_LEN];
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} MN_CALL_CUSTOM_ECC_NUM_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /* �¼��� */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulEccNumCount;
    MN_CALL_CUSTOM_ECC_NUM_STRU         astCustomEccNumList[MN_CALL_MAX_EMC_NUM];
} MN_CALL_ECC_NUM_INFO_STRU;

enum MN_CALL_CODEC_TYPE_ENUM
{
    MN_CALL_CODEC_TYPE_AMR,                 /* amr */
    MN_CALL_CODEC_TYPE_EFR,                 /* enhanced full rate */
    MN_CALL_CODEC_TYPE_FR,                  /* full rate */
    MN_CALL_CODEC_TYPE_HR,                  /* half rate */
    MN_CALL_CODEC_TYPE_AMR2,
    /* Added by z40661 for AMR-WB , 2012-02-09, begin */
    MN_CALL_CODEC_TYPE_AMRWB,
    /* Added by z40661 for AMR-WB , 2012-02-09, end */
    MN_CALL_CODEC_TYPE_G711,

    MN_CALL_CODEC_TYPE_BUTT                 /* invalid value */
};
typedef VOS_UINT8  MN_CALL_CODEC_TYPE_ENUM_U8;

enum MN_CALL_RADIO_MODE_ENUM
{
    MN_CALL_RADIO_MODE_GSM,
    MN_CALL_RADIO_MODE_WCDMA,
    MN_CALL_RADIO_MODE_IMS_EUTRAN,
    MN_CALL_RADIO_MODE_BUTT
};
typedef VOS_UINT8  MN_CALL_RADIO_MODE_ENUM_U8;

enum MN_CALL_CHANNEL_RATE_ENUM
{
    MN_CALL_CHANNEL_RATE_475,                   /* rate 4.75kbps/s */
    MN_CALL_CHANNEL_RATE_515,                   /* rate 5.15kbps/s */
    MN_CALL_CHANNEL_RATE_59,                    /* rate 5.9kbps/s */
    MN_CALL_CHANNEL_RATE_67,                    /* rate 6.7kbps/s */
    MN_CALL_CHANNEL_RATE_74,                    /* rate 7.4kbps/s */
    MN_CALL_CHANNEL_RATE_795,                   /* rate 7.95kbps/s */
    MN_CALL_CHANNEL_RATE_102,                   /* rate 10.2kbps/s */
    MN_CALL_CHANNEL_RATE_122,                   /* rate 12.2kbps/s */
    MN_CALL_CHANNEL_RATE_BUTT                   /* invalid value */
};
typedef VOS_UINT8  MN_CALL_CHANNEL_RATE_ENUM_U8;


enum TAF_CALL_TYPE_ENUM
{
    TAF_CALL_TYPE_NORMAL_CALL,
    TAF_CALL_TYPE_ECALL,
    TAF_CALL_TYPE_BUTT
};
typedef VOS_UINT16 TAF_CALL_TYPE_ENUM_UINT16;

typedef struct
{
    MN_CALL_RADIO_MODE_ENUM_U8          enMode;       /*GSM|WCDMA*/
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;  /* codec type */
    TAF_CALL_TYPE_ENUM_UINT16           enCallType;   /* eCall type */
} MN_CALL_CHANNEL_PARAM_STRU;

typedef struct
{
    VOS_BOOL                             bChannelEnable;    /*GSM|WCDMA*/
    MN_CALL_CHANNEL_PARAM_STRU           stChannelParam;        /* channel rate */
} MN_CALL_CHANNEL_INFO_STRU;

enum MN_CALL_CHANNEL_EVENT_ENUM
{
    MN_CALL_EVT_CHANNEL_OPEN,                                                   /* open codec channel */
    MN_CALL_EVT_CHANNEL_CLOSE,                                                  /* close codec channel */
    MN_CALL_EVT_CHANNEL_PARA_CHANGE,

    MN_CALL_EVT_CHANNEL_LOCAL_ALERTING,
    MN_CALL_EVT_TYPE_BUFF                                                       /* reserved value */
};
typedef  VOS_UINT32  MN_CALL_CHANNEL_EVENT_ENUM_U32;


typedef union
{
    MN_CALL_ORIG_PARAM_STRU             stOrig;
    MN_CALL_END_PARAM_STRU              stEnd;
    MN_CALL_ANS_PARAM_STRU              stAns;
    TAF_CALL_DTMF_PARAM_STRU            stDtmf;
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtCmd;
    MN_CALL_UUS1_PARAM_STRU             stUus1Info;   /* ����UUS1��Ϣ�ṹ */
    MN_CALL_SET_ALS_PARAM_STRU          stSetAls;     /* ����ALS NO�ṹ   */

    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU stEccNumReq;

    MN_CALL_SET_CSSN_REQ_STRU           stCssnReq;
} MN_CALL_APP_REQ_PARM_UNION;

/* Ӧ��������Ϣ�Ľṹ */
typedef struct
{
    VOS_MSG_HEADER
    MN_CALL_APP_REQ_ENUM_UINT32         enReq;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        callId;
    MN_CALL_APP_REQ_PARM_UNION          unParm;
} MN_CALL_APP_REQ_MSG_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /* �¼��� */
    MN_CLIENT_ID_T                      usClientId;
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucCallId[MN_CALL_MAX_NUM];
    VOS_UINT8                           aucCurcRptCfg[MN_CALL_RPT_CFG_MAX_SIZE];        /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                           aucUnsolicitedRptCfg[MN_CALL_RPT_CFG_MAX_SIZE]; /* �����������õ������ϱ���ʶ */
} MN_CALL_EVT_HOLD_STRU;


typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /* �¼��� */
    MN_CLIENT_ID_T                      usClientId;
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucCallId[MN_CALL_MAX_NUM];
    VOS_UINT8                           aucCurcRptCfg[MN_CALL_RPT_CFG_MAX_SIZE];        /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                           aucUnsolicitedRptCfg[MN_CALL_RPT_CFG_MAX_SIZE]; /* �����������õ������ϱ���ʶ */
} MN_CALL_EVT_RETRIEVE_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPI                 :1;
    VOS_UINT32                          bitOpNoCLICause         :1;
    VOS_UINT32                          bitOpRedirectNum        :1;
    VOS_UINT32                          bitOpRedirectSubaddr    :1;
    VOS_UINT32                          bitOpSpare              :28;
    MN_CALL_PRESENTATION_IND_ENUM_UINT8 enPI;
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCLICause;
    VOS_UINT8                           aucRsv[2];
    MN_CALL_BCD_NUM_STRU                stRedirectNum;                          /* BCD number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Subaddress */
}MN_CALL_REDIRECT_INFO;


typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /*�ظ����¼�����*/
    VOS_UINT32                          ulRet;
    AT_APPCTRL_STRU                     stAppCtrl;
    MN_CALL_REDIRECT_INFO               stRedirectInfo;
}MN_CALL_CLPR_GET_CNF_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEventId;          /* �¼�����   */

    AT_APPCTRL_STRU                     stAppCtrl;          /* Ӧ�ÿ���ͷ */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;            /* ������     */
} MN_CALL_EVT_ERR_IND_STRU;
typedef struct
{
    MN_CALL_EVENT_ENUM_U32  enEvent;        /*�ظ����¼�����*/
    TAF_PH_ERR_CODE         ulRet;          /*�ظ����*/
    MN_CLIENT_ID_T          ClientId;       /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;           /*����ID*/
    VOS_UINT8               ucReserved[3];  /* �����ֶ� */
} MN_CALL_SET_CSSN_CNF_STRU;

typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEvent;                                /* �¼��� */
    MN_CLIENT_ID_T                      usClientId;

    VOS_UINT8                           ucIsLocalAlertingFlag;                  /* �Ƿ�Ϊ���ز��Ż�������ʶ1:���ز��Ż�������0:�������*/   
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
    
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucRsv[3];
} MN_CALL_EVT_CHANNEL_INFO_STRU;
enum TAF_CALL_DTMF_STATE_ENUM
{
    TAF_CALL_DTMF_IDLE                  = 0,                                    /* ��ǰDTMF���� */
    TAF_CALL_DTMF_WAIT_START_CNF,                                               /* ������START�����ȴ��ظ� */
    TAF_CALL_DTMF_WAIT_STOP_CNF,                                                /* ������STOP�����ȴ��ظ� */
    TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF,                                           /* ��ʱ����ʱ�Զ�����STOP�����ȴ��ظ� */
    TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT,                                      /* ����DTMF��ʱ����ȴ���ʱ */
    TAF_CALL_DTMF_WAIT_OFF_LENGTH_TIME_OUT,                                     /* �յ�stop dtmf ack����ʱ����ʱ�ٴ�������start dtmf req */

    TAF_CALL_DTMF_STATE_BUTT
};
typedef VOS_UINT8 TAF_CALL_DTMF_STATE_ENUM_UINT8;


typedef struct
{
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[1];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* ������ */

    MN_CALL_ID_T                        callId;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT8                           ucDtmfCnt;
    VOS_UINT8                           aucReserved2[1];

} TAF_CALL_EVT_DTMF_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ��Ϣ�� */
    VOS_UINT8                           aucReserve1[2];                         /* ���� */
    VOS_UINT16                          usClientId;                             /* Client ID */
    VOS_UINT8                           ucOpId;                                 /* Operation ID */
    VOS_UINT8                           aucReserve2[1];                         /* ���� */
}MN_CALL_QRY_ECALL_INFO_REQ_STRU;
typedef struct
{
    MN_CALL_ID_T                        ucCallId;                               /* ��ǰ��call ID */
    MN_CALL_TYPE_ENUM_U8                enEcallType;                            /* eCall�������� */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* ����״̬ */
    VOS_UINT8                           aucReserved[1];                         /* ���� */
    MN_CALL_CALLED_NUM_STRU             stDialNumber;                           /* ���к��� */
}MN_CALL_ECALL_INFO_PARA_STRU;
typedef struct
{
    VOS_UINT8                           ucNumOfEcall;                           /* ��ǰeCall���и��� */
    VOS_UINT8                           aucReserved[3];                         /* ���� */
    MN_CALL_ECALL_INFO_PARA_STRU        astEcallInfos[MN_CALL_MAX_NUM];         /* eCall��Ϣ���� */
}MN_CALL_ECALL_INFO_STRU;
typedef struct
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_ECALL_INFO_STRU             stEcallInfo;
}MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/


/* Orignate Call */
VOS_UINT32  MN_CALL_Orig(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        *pCallId,
    const MN_CALL_ORIG_PARAM_STRU       *pstOrigParam
);

/* End Call */
VOS_UINT32  MN_CALL_End(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU        *pstEndParam
);

/* Answer Call */
VOS_UINT32  MN_CALL_Answer(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pAnsParam
);

/* Send DTMF */
VOS_UINT32  TAF_CALL_SendDtmf(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CALL_DTMF_PARAM_STRU     *pstDtmfParam
);

/* Call Management Command*/
VOS_UINT32  MN_CALL_Sups(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);

/* Get All Call Info */
VOS_UINT32  MN_CALL_GetCallInfos(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
);

VOS_UINT32 MN_CALL_SetAlsLineNo(
    TAF_UINT8                           ucIndex,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine
);

VOS_UINT32 MN_CALL_CheckUus1ParmValid(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

VOS_VOID  MN_CALL_SetUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_UUS1_PARAM_STRU            *pstUus1Info
);

VOS_VOID  MN_CALL_QryUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);
VOS_VOID  MN_CALL_SetAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_ALS_PARAM_STRU         *pstAls
);
VOS_VOID  MN_CALL_QryAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);
VOS_UINT32  MN_CALL_SendAppRequest(
    MN_CALL_APP_REQ_ENUM_UINT32         enReq,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_APP_REQ_PARM_UNION    *punParam
);

VOS_UINT32  MN_CALL_QryCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
);

VOS_VOID MN_CALL_RcvTafEccNumReq(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
);
VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID);


VOS_VOID MN_CALL_RcvAtClprGetReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg);


/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : ��ȡGMM�ĵ�ǰ��������
                  HSS 4100 V200R001 ����
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : GMM��������
                  GMM_RABM_CURNET_3G    //3G����
                  GMM_RABM_CURNET_2G    //2G����
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_GetCurNetwork(VOS_VOID);

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

#endif /* MN_CALL_API_H */
