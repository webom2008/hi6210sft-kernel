/******************************************************************************

                  ��Ȩ���� (C), 2011-2031, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RcmPhyInterface.h
  �� �� ��   : ����
  ��    ��   : ���� 138719
  ��������   : 2014��1��20��
  ����޸�   :
  ��������   : RCM��PHY�Ľӿ�ͷ�ļ�,�ӿ��е�ʱ�䶼����32K��clockΪ��λ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��20��
    ��    ��   : ���� 138719
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __RCMPHYINTERFACE_H__
#define __RCMPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "Hi_Config.h"
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*���֧�ֵ�RF��Ŀ*/
#define RCM_RF_SUPPORT_NUM                      ( RCM_RF_ID_BUTT )

/*���֧�ֵ�PHY mode��Ŀ*/
#define RCM_MODE_SUPPORT_NUM                    ( RCM_MODE_ID_BUTT )

/*���֧�ֵ�MODEM��Ŀ*/
#define RCM_MODEM_SUPPORT_NUM                   ( RCM_MODEM_ID_BUTT )

/* �����������size */
#define RCM_PHY_ASSIGN_BUF_SIZE                 ( 32 )

/* ������ʱ�������ڣ���32Kʱ��Ϊ��λ��������2��ָ�� */
#define RCM_CLOCK_PERIOD                        ( ((VOS_UINT32)0x1)<<31 )

/* ������ʱƵ�� */
#define RCM_CLOCK_FREQUENCY                     ( 32768 )

/* ��Ч��ʱ ͬʱ��Ϊ���ʱ�� */
#define RCM_CLOCK_INVALID_VALUE                 ( 0xffffffff )

/* ���κ��ۻ�����ռ����,��ռͳ��������Чֵ(��PSҵ��ͳһ���ֵ) */
#define RCM_PRMPT_TH_INVALID_VALUE              ( RCM_CLOCK_INVALID_VALUE )

/* ʱ��msת��Ϊ32K�ļ��� �������С��0x20000 ms*/
#define RCM_MsToClock( M_uhwTime )              ( (VOS_INT32)( ( ((VOS_UINT32)M_uhwTime) *RCM_CLOCK_FREQUENCY)/1000 ))

/* GPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_GPHY_TASK_ID_BEGIN_NUM              ( 0 )

/* WPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_WPHY_TASK_ID_BEGIN_NUM              ( 100 )

/* TPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_TPHY_TASK_ID_BEGIN_NUM              ( 200 )

/* LPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_LPHY_TASK_ID_BEGIN_NUM              ( 300 )

/* һ��ɾ��������ID������ */
#define RCM_REL_TASK_ID_MAX_NUM                 ( 32 )

/* Ϊ�������������ľ��ȣ�PHY����RCM������ֵ����ı��� */
#define EXTEND_PERIOD_TASK_TIMES                ( ((VOS_UINT32)0x1)<<7 )

/* ����������������λ */
#define RCM_GetTaskPeriod( M_uwPeriod )         ( (((VOS_UINT32)M_uwPeriod) & (~( EXTEND_PERIOD_TASK_TIMES - 1 )))>>7 )

/* ����������������λ */
#define RCM_GetTaskRemainder( M_uwPeriod )      ( ((VOS_UINT32)M_uwPeriod) & ( EXTEND_PERIOD_TASK_TIMES - 1 )  )

/* ������������ԣ������ȼ����Ƿ��ռ��: GPHY */
#define RCM_GPHY_TASK_PROPERTY_TABLE  \
    { RCM_GPHY_TASK_START,                  RCM_TASK_PRIORITY_BUTT, RCM_PREEMPT_BUTT },\
    { RCM_GPHY_TASK_SEARCHING_MEA,          RCM_TASK_PRIORITY_3,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_SEARCHING_FBSB,         RCM_TASK_PRIORITY_3,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_SEARCHING_BCCH_PART,    RCM_TASK_PRIORITY_3,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE,   RCM_TASK_PRIORITY_3,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_PAGE_NORMAL,       RCM_TASK_PRIORITY_2,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_IDLE_PAGE_EXT,          RCM_TASK_PRIORITY_2,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_IDLE_PAGE_REORG,        RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD, RCM_TASK_PRIORITY_7,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE, RCM_TASK_PRIORITY_3_7,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BASIC_CBCH,        RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_EXT_CBCH,          RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_NCELL_FB,          RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_NCELL_SB,          RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_CELL_RESELECT,     RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_MEA,            RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_FBSB,           RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_BCCH,           RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_WMEA,     RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_TMEA,     RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_LMEA,     RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_WMEA,           RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_TMEA,           RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_BG_LMEA,           RCM_TASK_PRIORITY_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_FULLLIST_MEA,      RCM_TASK_PRIORITY_5,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_TUNING_RACH,            RCM_TASK_PRIORITY_1,    RCM_PREEMPT_NO  },\
    { RCM_GPHY_TASK_TUNING_PRACH,           RCM_TASK_PRIORITY_1,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_PBCCH,                  RCM_TASK_PRIORITY_5,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_PPCH,                   RCM_TASK_PRIORITY_5,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_TUNING_SINGLE_BLOCK,    RCM_TASK_PRIORITY_1,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_DCH_CS,                 RCM_TASK_PRIORITY_1,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_DCH_PS,                 RCM_TASK_PRIORITY_5,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_LOST_NET,               RCM_TASK_PRIORITY_1,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_INACTIVE,               RCM_TASK_PRIORITY_1,    RCM_PREEMPT_NO   },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL,  RCM_TASK_PRIORITY_1_6,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH,    RCM_TASK_PRIORITY_3_5,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_RESEL, RCM_TASK_PRIORITY_2_5,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_BG,    RCM_TASK_PRIORITY_8,    RCM_PREEMPT_YES  },\
    { RCM_GPHY_TASK_END,                    RCM_TASK_PRIORITY_BUTT, RCM_PREEMPT_BUTT }


/* ������������ԣ������ȼ����Ƿ��ռ��: WPHY */
#define RCM_WPHY_TASK_PROPERTY_TABLE  \
    { RCM_WPHY_TASK_LIST,                  RCM_TASK_PRIORITY_BUTT, RCM_PREEMPT_BUTT },\
    { RCM_WPHY_TASK_FREE,                  RCM_TASK_PRIORITY_3,    RCM_PREEMPT_YES  },\
    { RCM_WPHY_TASK_CPICH_PI,              RCM_TASK_PRIORITY_2,    RCM_PREEMPT_NO   },\
    { RCM_WPHY_TASK_CPICH_MEAS,            RCM_TASK_PRIORITY_4,    RCM_PREEMPT_YES  },\
    { RCM_WPHY_TASK_DPCH,                  RCM_TASK_PRIORITY_5,    RCM_PREEMPT_YES  },\
    { RCM_WPHY_TASK_END,                   RCM_TASK_PRIORITY_BUTT, RCM_PREEMPT_BUTT }


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RCM_PHY_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM <-> PHY �ӿ���ϢID
*****************************************************************************/
enum RCM_PHY_MSG_ID_ENUM
{
    ID_PHY_RCM_TASK_APPLY_REQ               = 0x1801,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_APPLY_REQ_STRU */
    ID_PHY_RCM_TASK_REL_REQ                 = 0x1802,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_REL_REQ_STRU */
    ID_PHY_RCM_TASK_RELALL_REQ              = 0x1803,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RELALL_REQ_STRU */
    ID_PHY_RCM_TASK_PREEMPT_ACK             = 0x1804,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_PREEMPT_ACK_STRU */
    ID_PHY_RCM_TASK_RESUME_ACK              = 0x1805,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RESUME_ACK_STRU */
    ID_PHY_RCM_AWAKE_REQ                    = 0x1807,                           /* _H2ASN_MsgChoice PHY_RCM_AWAKE_REQ_STRU */
    ID_PHY_RCM_SLEEP_REQ                    = 0x1808,                           /* _H2ASN_MsgChoice PHY_RCM_SLEEP_REQ_STRU */
    ID_PHY_RCM_ASSIGN_ACK                   = 0x1809,                           /* _H2ASN_MsgChoice PHY_RCM_ASSIGN_ACK_STRU */
    ID_PHY_RCM_CLOCK_CAL_ACK                = 0x180a,                           /* _H2ASN_MsgChoice PHY_RCM_CLOCK_CAL_ACK_STRU */
    ID_PHY_RCM_GET_MSGLISTADDR_REQ          = 0x180c,                           /* _H2ASN_MsgChoice PHY_RCM_GET_MSGLISTADDR_REQ_STRU */
    ID_PHY_RCM_PERIOD_TASK_COMPLETE_REQ     = 0x180d,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_COMPLETE_REQ_STRU */

    ID_RCM_PHY_TASK_APPLY_CNF               = 0x1881,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_APPLY_CNF_STRU */
    ID_RCM_PHY_TASK_REL_CNF                 = 0x1882,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_REL_CNF_STRU */
    ID_RCM_PHY_TASK_RELALL_CNF              = 0x1883,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RELALL_CNF_STRU */
    ID_RCM_PHY_TASK_PREEMPT_IND             = 0x1884,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_PREEMPT_IND_STRU */
    ID_RCM_PHY_TASK_RESUME_IND              = 0x1885,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RESUME_IND_STRU */
    ID_RCM_PHY_ASSIGN_IND                   = 0x1889,                           /* _H2ASN_MsgChoice RCM_PHY_ASSIGN_IND_STRU */
    ID_RCM_PHY_CLOCK_CAL_IND                = 0x188a,                           /* _H2ASN_MsgChoice RCM_PHY_CLOCK_CAL_IND_STRU */
    ID_RCM_PHY_OVERTIME_IND                 = 0x188b,                           /* _H2ASN_MsgChoice RCM_PHY_OVERTIME_IND_STRU */
    ID_RCM_PHY_GET_MSGLISTADDR_CNF          = 0x188c,                           /* _H2ASN_MsgChoice RCM_PHY_GET_MSGLISTADDR_CNF_STRU */
    ID_RCM_PHY_PERIOD_TASK_COMPLETE_CNF     = 0x188d,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_COMPLETE_CNF_STRU */

    ID_RCM_PHY_MSG_BUTT

};
typedef VOS_UINT16 RCM_PHY_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PREEMPT_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM�������Ƿ�ɱ���ռ��־
*****************************************************************************/
enum RCM_PREEMPT_FLAG_ENUM
{
    RCM_PREEMPT_YES                     = 0,                                    /* ������ռ */
    RCM_PREEMPT_NO                         ,                                    /* ��������ռ */
    RCM_PREEMPT_BUTT
};
typedef VOS_UINT16 RCM_PREEMPT_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PRIORITY_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM���������ȼ� ������������ֵΪ���ȼ�1~8(200~900)�������ȼ���RCM�ڲ�ʹ��
*****************************************************************************/
enum RCM_TASK_PRIORITY_ENUM
{
    RCM_TASK_PRIORITY_HIGHEST           = 1 ,                                   /* ����������ȼ� 1~99���ڶ�ռ */
    RCM_TASK_PRIORITY_CALA_HIGHEST      = 100,                                  /* ���ȼ�100 �������ȼ��ܹ������������ֵ RCM����õ� */
    RCM_TASK_PRIORITY_1                 = 200,                                  /* ���ȼ�200 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_1_5               = 250,                                  /* ���ȼ�250 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_1_6               = 260,                                  /* ���ȼ�260 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_2                 = 300,                                  /* ���ȼ�300 */
    RCM_TASK_PRIORITY_2_5               = 350,                                  /* ���ȼ�350 */
    RCM_TASK_PRIORITY_3                 = 400,                                  /* ���ȼ�400 */
    RCM_TASK_PRIORITY_3_5               = 450,                                  /* ���ȼ�450 */
    RCM_TASK_PRIORITY_3_7               = 470,                                  /* ���ȼ�470 */
    RCM_TASK_PRIORITY_4                 = 500,                                  /* ���ȼ�500 */
    RCM_TASK_PRIORITY_4_5               = 550,                                  /* ���ȼ�550 */
    RCM_TASK_PRIORITY_5                 = 600,                                  /* ���ȼ�600 */
    RCM_TASK_PRIORITY_5_5               = 650,                                  /* ���ȼ�650 */
    RCM_TASK_PRIORITY_6                 = 700,                                  /* ���ȼ�700 */
    RCM_TASK_PRIORITY_7                 = 800,                                  /* ���ȼ�800 */
    RCM_TASK_PRIORITY_8                 = 900,                                  /* ���ȼ�900 */
    RCM_TASK_PRIORITY_LOWEST            = 1000,                                 /* ����������ȼ� RCMʹ�� */
    RCM_TASK_PRIORITY_BUTT
};
typedef VOS_UINT16 RCM_TASK_PRIORITY_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PHY_TASK_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PHY ��RCM��ע�������ID
*****************************************************************************/
enum RCM_PHY_TASK_ID_ENUM
{
    RCM_GPHY_TASK_START                     = RCM_GPHY_TASK_ID_BEGIN_NUM,       /* ������������� */
    RCM_GPHY_TASK_SEARCHING_MEA             ,                                   /* 1�������� */
    RCM_GPHY_TASK_SEARCHING_FBSB            ,                                   /* 2����ͬ�� */
    RCM_GPHY_TASK_SEARCHING_BCCH_PART       ,                                   /* 3������㲥�����ֶ� */
    RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE      ,                                   /* 4������㲥��ȫ�� */
    RCM_GPHY_TASK_IDLE_PAGE_NORMAL          ,                                   /* 5��Ѱ������ */
    RCM_GPHY_TASK_IDLE_PAGE_EXT             ,                                   /* 6����չѰ������ */
    RCM_GPHY_TASK_IDLE_PAGE_REORG           ,                                   /* 7Reorg̬��Ѱ�� */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD    ,                                   /* 8������С��ϵͳ��Ϣ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE    ,                                   /* 9������ϵͳ��Ϣ */
    RCM_GPHY_TASK_IDLE_BASIC_CBCH           ,                                   /* 10BASIC����CBSҵ�� */
    RCM_GPHY_TASK_IDLE_EXT_CBCH             ,                                   /* 11EXT����CBSҵ�� */
    RCM_GPHY_TASK_IDLE_NCELL_FB             ,                                   /* 12����FB */
    RCM_GPHY_TASK_IDLE_NCELL_SB             ,                                   /* 13����SB */
    RCM_GPHY_TASK_IDLE_CELL_RESELECT        ,                                   /* 14С����ѡ */
    RCM_GPHY_TASK_IDLE_BG_MEA               ,                                   /* 15�����Ѳ��� */
    RCM_GPHY_TASK_IDLE_BG_FBSB              ,                                   /* 16������ͬ�� */
    RCM_GPHY_TASK_IDLE_BG_BCCH              ,                                   /* 17�����ѽ�㲥 */
    RCM_GPHY_TASK_IDLE_INTERRAT_WMEA        ,                                   /* 18��ϵͳW���� */
    RCM_GPHY_TASK_IDLE_INTERRAT_TMEA        ,                                   /* 19��ϵͳT���� */
    RCM_GPHY_TASK_IDLE_INTERRAT_LMEA        ,                                   /* 20��ϵͳL���� */
    RCM_GPHY_TASK_IDLE_BG_WMEA              ,                                   /* 21������W���� */
    RCM_GPHY_TASK_IDLE_BG_TMEA              ,                                   /* 22������T���� */
    RCM_GPHY_TASK_IDLE_BG_LMEA              ,                                   /* 23������L���� */
    RCM_GPHY_TASK_IDLE_FULLLIST_MEA         ,                                   /* 24FULLIS���� */
    RCM_GPHY_TASK_TUNING_RACH               ,                                   /* 25������� */
    RCM_GPHY_TASK_TUNING_PRACH              ,                                   /* 26PACKET������� */
    RCM_GPHY_TASK_PBCCH                     ,                                   /* 27PACKETϵͳ��Ϣ */
    RCM_GPHY_TASK_PPCH                      ,                                   /* 28PACKETѰ�� */
    RCM_GPHY_TASK_TUNING_SINGLE_BLOCK       ,                                   /* 29���͵���Ͷ�� */
    RCM_GPHY_TASK_DCH_CS                    ,                                   /* 30CSר��̬ */
    RCM_GPHY_TASK_DCH_PS                    ,                                   /* 31PSר��̬ */
    RCM_GPHY_TASK_LOST_NET                  ,                                   /* 32������ */
    RCM_GPHY_TASK_INACTIVE                  ,                                   /* 33ȥ���� */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL     ,                                   /* 34��ѡ�����з���С��ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH       ,                                   /* 35��ǿ���չ�����ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_RESEL,                                   /* 36��ѡ������ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_BG   ,                                   /* 37�����ѹ�����ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_END                       ,                                   /* ������������� */
    RCM_WPHY_TASK_LIST                      = RCM_WPHY_TASK_ID_BEGIN_NUM,
    RCM_WPHY_TASK_FREE                      = 101,
    RCM_WPHY_TASK_CPICH_PI                  = 102,
    RCM_WPHY_TASK_CPICH_MEAS                = 103,
    RCM_WPHY_TASK_DPCH                      = 104,
    RCM_WPHY_TASK_END                       ,
    RCM_TPHY_TASK_LIST                      = RCM_TPHY_TASK_ID_BEGIN_NUM,
    RCM_LPHY_TASK_LIST                      = RCM_LPHY_TASK_ID_BEGIN_NUM,
    RCM_PHY_TASK_BUTT
};
typedef VOS_UINT16 RCM_PHY_TASK_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODE_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ģʽ��ʾ ���д����У׼����һ��
*****************************************************************************/
enum RCM_MODE_ID_ENUM
{
    RCM_LTE                             = 0,                                    /* LTE */
    RCM_WCDMA                           = 1,                                    /* WCDMA */
    RCM_1X                              = 2,                                    /* 1X */
    RCM_HRPD                            = 3,                                    /* HRPD */
    RCM_TD                              = 4,                                    /* TD */
    RCM_G0                              = 5,                                    /* G0 */
    RCM_G1                              = 6,                                    /* G1 */
    RCM_G2                              = 7,                                    /* G2 */
    RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODEM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MODEM ID
*****************************************************************************/
enum RCM_MODEM_ID_ENUM
{
    RCM_MODEM_1                         = 0,                                    /* MODEM0 */
    RCM_MODEM_2                         = 1,                                    /* MODEM1 */
    RCM_MODEM_3                         = 2,                                    /* MODEM2 */
    RCM_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RF_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RF ID
*****************************************************************************/
enum RCM_RF_ID_ENUM
{
    RCM_RF_0                            = 0,                                    /* RF0 */
    RCM_RF_1                            = 1,                                    /* RF1 */
    RCM_RF_ID_BUTT
};
typedef VOS_UINT16  RCM_RF_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RTT_STA_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RTT״̬,����ʱ��У׼ѡ��

*****************************************************************************/
enum RCM_RTT_STA_ENUM
{
    RCM_RTT_INITIAL                     = 0,                                    /* ��ʼ̬ ,û��פ�� */
    RCM_RTT_DRX                         = 1,                                    /* ������̬������̬ */
    RCM_RTT_CONTINUE                    = 2,                                    /* ����̬ ����绰����*/
    RCM_RTT_STA_BUTT
};
typedef VOS_UINT16  RCM_RTT_STA_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RSLT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��е���Ч�Ա�ʶ
*****************************************************************************/
enum RCM_RSLT_ENUM
{
    RCM_SUCC                            = 0,                                    /* �ɹ� */
    RCM_FAIL_PARA                       = 1,                                    /* �������� */
    RCM_FAIL_OVERTIME                   = 2,                                    /* ������ǰ������ */
    RCM_FAIL_OTHER                      = 3,                                    /* �����ڵ�Ϊ�� */
    RCM_RSLT_BUTT
};
typedef VOS_UINT16  RCM_RSLT_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_DIRECTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��еĵ��������ʶ
*****************************************************************************/
enum RCM_DIRECTION_ENUM
{
    RCM_DIRECTION_SLOWDOWN              = 0,                                    /* ����1������ */
    RCM_DIRECTION_SPEEDUP               = 1,                                    /* ����1������ */
    RCM_DIRECTION_KEEP                  = 2,                                    /* ������ */
    RCM_DIRECTION_BUTT
};
typedef VOS_UINT16 RCM_DIRECTION_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PERIOD_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ����/�����������ʶ
*****************************************************************************/
enum RCM_TASK_PERIOD_FLAG_ENUM
{
    RCM_TASK_PERIOD_FLAG_INVALID        = 0,                                    /* ���������� */
    RCM_TASK_PERIOD_FLAG_VALID          = 1,                                    /* �������� */
    RCM_TASK_PERIOD_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PERIOD_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_FIXPOS_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �̶�/�ǹ̶�����ʱ�̱�ʶ
*****************************************************************************/
enum RCM_TASK_FIXPOS_FLAG_ENUM
{
    RCM_TASK_FIXPOS_FLAG_INVALID        = 0,                                    /* �޹̶�����ʱ�� */
    RCM_TASK_FIXPOS_FLAG_VALID          = 1,                                    /* �й̶�����ʱ�� */
    RCM_TASK_FIXPOS_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_FIXPOS_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �̶�/�ǹ̶����ȱ�ʶ
*****************************************************************************/
enum RCM_TASK_LIMITLEN_FLAG_ENUM
{
    RCM_TASK_LIMITLEN_FLAG_INVALID      = 0,                                    /* ���޳����� */
    RCM_TASK_LIMITLEN_FLAG_VALID        = 1,                                    /* ���޳����� */
    RCM_TASK_LIMITLEN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ����/���������������ʶ
*****************************************************************************/
enum RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM
{
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_INVALID  = 0,                                /* ����Ҫ������������ */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_VALID    = 1,                                /* ��Ҫ������������ */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ɴ��/���ɴ�������ʶ
*****************************************************************************/
enum RCM_TASK_PREEMPTIND_FLAG_ENUM
{
    RCM_TASK_PREEMPTIND_FLAG_INVALID        = 0,                                /* ���ɴ������ */
    RCM_TASK_PREEMPTIND_FLAG_VALID          = 1,                                /* �ɴ������ */
    RCM_TASK_PREEMPTIND_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_RELEASE_PRINCIPAL_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����/RCM �����ͷű�ʶ
*****************************************************************************/
enum RCM_TASK_RELEASE_PRINCIPAL_ENUM
{
    RCM_TASK_RELEASE_PRINCIPAL_PHY          = 0,                                /* ��������ͷ� */
    RCM_TASK_RELEASE_PRINCIPAL_RCM          = 1,                                /* ��RCM�ͷ� */
    RCM_TASK_RELEASE_PRINCIPAL_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_CMD_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��Ϣ��������Ϣ����
*****************************************************************************/
enum RCM_CMD_ENUM
{
    RCM_CMD_TASK_ASSIGN_SUCC                = 0,                                /* �������ɹ� */
    RCM_CMD_TASK_ASSIGN_FAIL_OTHER          = 1,                                /* �����������ʧ�� */
    RCM_CMD_TASK_RECYCLE                    = 2,                                /* �ѷ�������û�������л��� */
    RCM_CMD_MSG_BUTT
};
typedef VOS_UINT16  RCM_CMD_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_CMODE_TYPE_ENUM_UINT16
 ö��˵��  : Cģ��ϵͳʱ������,00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
*****************************************************************************/
enum RCM_CMODE_TYPE_ENUM
{
    RCM_CMODE_1X                        = 0,
    RCM_CMODE_EVDO                      = 1,
    RCM_CMODE_BASECNT                   = 2,
    RCM_CMODE_BUTT
};
typedef VOS_UINT16 RCM_CMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_WMODE_TYPE_ENUM_UINT16
 ö��˵��  : Wģ��ϵͳʱ������
             00��sys_cnt��ʱ        01��base_cnt��ʱ
             10����Ч               11����Ч
*****************************************************************************/
enum RCM_WMODE_TYPE_ENUM
{
    RCM_WMODE_SYSCNT                    = 0,
    RCM_WMODE_BASECNT                   = 1,
    RCM_WMODE_BUTT
};
typedef VOS_UINT16 RCM_WMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_REQ_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRFID;                         /* RF ID */
    VOS_UINT16                                  usPriority;                     /* �������ȼ� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RTT_STA_ENUM_UINT16                     enRttSta;                       /* RTT״̬ */
    RCM_TASK_FIXPOS_FLAG_ENUM_UINT16            enFixPosFlag;                   /* 0-�޹̶�����ʱ�� 1-�й̶�����ʱ�� */
    RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16          enLimitedLenFlag;               /* 0-���޳� 1-���޳� */
    RCM_TASK_PERIOD_FLAG_ENUM_UINT16            enPeriodFlag;                   /* 0-���������� 1-�������� */
    RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16        enPreemptInd;                   /* 0-�������� 1-������ */
    RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16      enReleasePrincipal;             /* 0-PHY�ͷ�  1-RCM�ͷ� */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16  enImmediateAssignFlag;          /* 0-������������ 1-���������� */
    VOS_UINT16                                  usFailCnt;                      /* ����ʧ�ܴ��� */
    VOS_UINT16                                  usFailThd;                      /* �������ʧ�ܴ�������,�����0��ʾ���Ե�ǰ����������ȼ����� */
    VOS_UINT32                                  ulStartPos;                     /* ��������ʱ�� ������д��Чֵ������޹̶�����ʱ����Ϊ�������ʱ�̣�*/
    VOS_UINT32                                  ulLen;                          /* ���񳤶�.���޳����������д��Чֵ,���ܳ���(RCM_CLOCK_PERIOD/4), */
    VOS_UINT32                                  ulMinLen;                       /* ���񵥴η������С����,���б�����д��Чֵ,���ܳ���(RCM_CLOCK_PERIOD/4),������޳�������Ե���ulLen */
    VOS_UINT32                                  ulPeriod;                       /* ������������ڣ�������������������д��Чֵ */
    VOS_UINT32                                  ulPrmptPeriod;                  /* ���޳��������ռͳ������ ��PS����д��Чֵ 0xffffffff PSҵ�����ʹ�ô˹��ܣ�Ҫ���С��(RCM_CLOCK_PERIOD/4)��ֵ */
    VOS_UINT32                                  ulPrmptTimeThd;                 /* ���޳����񵥴α���ռʱ������ ��PS����д��Чֵ 0xffffffff PSҵ�����ʹ�ô˹��ܣ�Ҫ���С��(RCM_CLOCK_PERIOD/4)��ֵ */
    VOS_UINT32                                  ulTotalPrmptTimeThd;            /* ���޳������������ۼƱ���ռʱ������ ��PS����д��Чֵ 0xffffffff PSҵ�����ʹ�ô˹��ܣ�Ҫ���С��(RCM_CLOCK_PERIOD/4)��ֵ */
}PHY_RCM_TASK_REQ_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_APPLY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    PHY_RCM_TASK_REQ_PARA_STRU                  stTaskReqPara;                  /* ����������� */
}PHY_RCM_TASK_APPLY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_APPLY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_APPLY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ͷ�������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uwRelTaskIdNum;                 /* ��ɾ�������������Ӧ��ausRelTaskId���±� */
    VOS_UINT16                                  ausRelTaskId[RCM_REL_TASK_ID_MAX_NUM]; /* ��ɾ���������� */
}PHY_RCM_TASK_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_REL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������ͷ�������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ��,RCMֻ���MODEM��MODEID����ȷ��  */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_TASK_REL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_RELALL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ȫ���ͷ�������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_TASK_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ�������ͷ�������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
}RCM_PHY_TASK_RELALL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_AWAKE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : wake������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_AWAKE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SLEEP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : sleep������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SLEEP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_PREEMPT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ռָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* ����ռ��RFID */
    VOS_UINT32                                  ulPreemptPos;                   /* ������ռʱ��*/
    VOS_UINT32                                  ul32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_PREEMPT_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_PREEMPT_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ռȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* ����ռ��RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usReserved;                     /* ������ */
}PHY_RCM_TASK_PREEMPT_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_RESUME_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulResumPos;                     /* ����ָ�ʱ��*/
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  ul32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_RESUME_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_RESUME_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
}PHY_RCM_TASK_RESUME_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ�������ݽṹ
*****************************************************************************/

typedef struct
{
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* ��ϢCMD���� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_MSG_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_RPT_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ�������ݽṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usIndex;                        /* ����ID */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* ��ϢCMD���� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_RPT_MSG_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MODE����Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRdIdx;                        /* ��ָ�� */
    VOS_UINT16                                  usWrIdx;                        /* дָ�� */
    RCM_PHY_MSG_STRU                            astMsgList[RCM_PHY_ASSIGN_BUF_SIZE];    /* ��Ϣ���� */
}RCM_PHY_MSG_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_ASSIGN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_ASSIGN_IND_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_ASSIGN_IND_FORTL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ָʾ��Ϣ���ݽṹ����TL
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_PHY_MSG_STRU                            stMsg;
}RCM_PHY_ASSIGN_IND_FORTL_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_ASSIGN_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}PHY_RCM_ASSIGN_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_CLOCK_CAL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ��У׼ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_CLOCK_CAL_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_CLOCK_CAL_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ��У׼�ϱ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    RCM_DIRECTION_ENUM_UINT16                   enDirection;                    /* �������� */
    VOS_UINT32                                  ulAdjustValue;                  /* �������� */
}PHY_RCM_CLOCK_CAL_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_OVERTIME_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʱ�ϱ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_OVERTIME_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_GET_MSGLISTADDR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ȡ��Ϣ���е�ַ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* ԭ������ */
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
}PHY_RCM_GET_MSGLISTADDR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_GET_MSGLISTADDR_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ϣ���е�ַ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* ԭ������ */
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_PHY_MSG_LIST_STRU                      *pstMsgList;                     /* ��Ϣ�����׵�ַ */
}RCM_PHY_GET_MSGLISTADDR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_COMPLETE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����ִ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* �������ڵ�RFID */
    VOS_UINT32                                  ulStartPos;                     /* ��ǰ��ɵ��������������ʱ�� */
}PHY_RCM_TASK_COMPLETE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_COMPLETE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY�յ�����ִ�����ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* �������ڵ�RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ32kʱ�� */
}RCM_PHY_TASK_COMPLETE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_WMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : Wģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfnCnt;                              /* SFN��������Χ0~4095 */
    VOS_UINT16                          uhwSlotCnt;                             /* ʱ϶��������Χ0~14 */
    VOS_UINT16                          uhwChipCnt;                             /* chip��������Χ0~2559 */
    VOS_UINT16                          uhwClkCnt;                              /* chip��ʱ�Ӽ�������Χ0~15 */
    RCM_WMODE_TYPE_ENUM_UINT16          enWMode;                                /* Wģ��ʱ������ */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_WMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_GMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : Gģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFnCnt;                                /* FN���� */
    VOS_UINT16                          uhwQbCnt;                               /* ϵͳ��ʱ֡��Qb��������Χ0~4999 */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_GMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_LTEMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : LTEģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uwSfnCnt;                               /* SFN��������Χ0~1023 */
    VOS_UINT16                          uhwsubfrm_cnt;                          /* ��֡���� */
    VOS_UINT16                          uhwTsCnt;                               /* ��֡�ڼ��� */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_LTEMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_TDMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : TDģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSfnCnt;                               /* tcfsrϵͳ��֡��0~65535ѭ��������TDSʵ����Ч��֡��ΧΪ0~8191 */
    VOS_UINT32                          uwSubFrmcnt;                            /* framc֡���� */
}RCM_TDMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_TIMING_STRU
 Э����  :
 �ṹ˵��  : ��ģϵͳʱ���32K��ʱ
*****************************************************************************/
typedef struct
{
    RCM_WMODE_TIMING_STRU               stWTime;                                /* Wģϵͳʱ�� */
    VOS_UINT32                          uwCTime;                                /* Cģϵͳʱ�� */
    RCM_GMODE_TIMING_STRU               stGmTime;                               /* Gmģϵͳʱ�� */
    RCM_GMODE_TIMING_STRU               stGsTime;                               /* Gsģϵͳʱ�� */
    RCM_LTEMODE_TIMING_STRU             stLTETime;                              /* LTEģϵͳʱ�� */
    RCM_TDMODE_TIMING_STRU              stTDSTime;                              /* TDģϵͳʱ�� */
    VOS_UINT32                          uw32KSysTime;                           /* 32Kϵͳ��ʱ */
}RCM_TIMING_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID RCM_DRV_SetWTimeMode( RCM_WMODE_TYPE_ENUM_UINT16 enWModeType );
extern VOS_UINT32 RCM_DRV_TimingInquire( RCM_WMODE_TYPE_ENUM_UINT16 enCModemType,
                                                 RCM_TIMING_STRU* pstTiming );
extern VOS_INT32 RCM_SCHDL_CalcDistance( VOS_UINT32 uwTimeX,
                                                 VOS_UINT32 uwTimeY );

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

#endif /* end of RcmPhyInterface.h */



