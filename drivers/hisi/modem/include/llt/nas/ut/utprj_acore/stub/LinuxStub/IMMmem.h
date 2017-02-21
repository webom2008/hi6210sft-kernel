

#ifndef __IMM_MEM_H__
#define __IMM_MEM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "MemoryMap.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define FEATURE_IMM_MEM_DEBUG             1

/* IMM �ڴ�ؿ��ܵ���󳤶� */
#define IMM_MEM_BLK_MAX_BYTE_LEN        (3800)

/* IMM �����ڴ��Ԥ������ */
#define IMM_MEM_CTRL_MEM_CNT           (418)
/* IMM �ڴ�ؿ��ܵ���൵λ */
#define IMM_MEM_BLK_MAX_CLUSTER_NUM     (8)

/* IMM ����ͷ����ڴ�ָ�� */
#define IMM_ADD_CTL_HEAD_MEM(pstImmHead, pMem)          ((pstImmHead)->p_Imm_Ttf_Mem = (pMem))

#define IMM_GET_4BYTE_ALIGN_VALUE(ulSize)   ( ((ulSize) + 0x03) & (~0x03) )

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    : IMM_BOOL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IMMͳһ��������ö�ٶ���
*****************************************************************************/
enum IMM_BOOL_ENUM
{
    IMM_FALSE                            = 0,
    IMM_TRUE                             = 1,
    IMM_BOOL_BUTT
};
typedef unsigned char   IMM_BOOL_ENUM_UINT8;

/*****************************************************************************
 ö����    : IMM_RSLT_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IMM ͳһ����ֵö�ٶ���
*****************************************************************************/
enum IMM_RSLT_CODE_ENUM
{
    IMM_SUCC                             = 0,
    IMM_FAIL                             = 1,
};
typedef unsigned long   IMM_RSLT_CODE_ENUM_UINT32;


enum IMM_MEM_USED_INFO_TRIG_TYPE_ENUM
{
    IMM_MEM_TRIG_TYPE_ALERT                      = 0x0,     /*�ڴ泬���޸澯*/
    IMM_MEM_TRIG_TYPE_ALLOC_FAIL,                           /*�ڴ�����ʧ��*/
    IMM_MEM_TRIG_TYPE_LEAK,                                 /*��鵽���ڴ�й¶*/
    IMM_MEM_TRIG_TYPE_BUTT
};
typedef unsigned char IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8;

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




enum MEM_BLK_STATE_ENUM
{
    MEM_BLK_STATE_FREE,       /*���ڴ�δ����������ͷ�*/
    MEM_BLK_STATE_ALLOC,      /*���ڴ�������*/
    MEM_BLK_STATE_BUTT
};
typedef unsigned long MEM_BLK_STATE_ENUM_UINT32;



typedef struct
{
    MEM_BLK_STATE_ENUM_UINT32           enMemStateFlag;
    unsigned long                       ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                      usAllocFileID;      /* File ID when alloc or free */
    unsigned short                      usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                      usTraceFileID;      /* File ID when traced */
    unsigned short                      usTraceLineNum;     /* File Line when traced */
    unsigned long                       ulTraceTick;        /* CPU tick when traced */
} IMM_BLK_MEM_DEBUG_STRU;



enum IMM_MEM_POOL_ID_ENUM
{
    IMM_MEM_POOL_ID_SHARE = 0,              /* A�˹����ڴ��ID */
    IMM_MEM_POOL_ID_EXT,                    /* A���ⲿ�ڴ��ID */

    IMM_MEM_POOL_ID_BUTT
};
typedef unsigned char IMM_MEM_POOL_ID_ENUM_UINT8;



enum IMM_MEM_TYPE_ID_ENUM
{
    IMM_MEM_TYPE_ID_SHARE = 0,              /* A�˹����ڴ�� */
    IMM_MEM_TYPE_ID_EXT,                    /* ����C�˵Ŀ���ڴ� */

    IMM_MEM_TYPE_ID_BUTT
};
typedef unsigned char IMM_MEM_TYPE_ID_ENUM_UINT8;



typedef struct
{
    IMM_MEM_TYPE_ID_ENUM_UINT8          enMemType;          /* �ڴ����� */
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId;           /* ���ڴ�����������ĸ��ڴ�� */
    unsigned char                       ucClusterId;        /* ���ڴ���������һ������ */
    unsigned char                       ucMagicNum;         /* �ڴ���ƿ�ħ���� */
    IMM_BLK_MEM_DEBUG_STRU             *pstDbgInfo;         /* ָ���ڴ���ƿ��DEBUG��Ϣ�洢�� */

    unsigned char                      *pstMemBlk;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
}IMM_MEM_STRU;



typedef struct
{
    /*��������IMM_MEM_STRU�ܸ���*/
    unsigned short                      usTotalCnt;

    /*��������IMM_MEM_STRU���и���*/
    unsigned short                      usFreeCnt;

    /*�����ڴ�����ݳ���*/
    unsigned short                      usLen;

    unsigned char                       aucRsv[2];

    /*��¼IMM_MEM_ST�����ڴ��������ջ��Ԫ�أ�������ΪTTF_MEM_STָ�� */
    IMM_MEM_STRU                      **apstFreeStack;
}IMM_MEM_CLUSTER_STRU;



typedef void (*IMM_MEM_EVENT_CALLBACK)(unsigned long ulMaxClusterFreeCnt);
typedef void (*IMM_MEM_EXT_FREE_CALLBACK)(const void *pAddr);
typedef void (*IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK)( unsigned char  ucPoolId, IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8 enTrigType );
typedef unsigned char (*IMM_SAVE_MEM_FREE_INFO_CALLBACK)(IMM_MEM_STRU *pstImmMem);
typedef void (*IMM_SAVE_MEM_ALLOC_INFO_CALLBACK)(IMM_MEM_STRU *pstImmMem,unsigned short usFileId,unsigned short usLineNum);

typedef unsigned long (*IMM_OM_GET_SLICE_CALLBACK)(void);


typedef struct
{
    /* ��ʶ���ڴ���Ƿ�ʹ�� */
    unsigned char                       ucUsedFlag;

    /* ���ڴ��һ���ж��ټ�*/
    unsigned char                       ucClusterCnt;

    /* ���ڴ����ʹ�õ�����û��ֽ� */
    unsigned short                      usMaxByteLen;

    /* ָ�򳤶��������ָ�� */
    unsigned char                       aucLenIndexTable[IMM_MEM_BLK_MAX_BYTE_LEN];

    /* ָ�����������ָ�� */
    IMM_MEM_CLUSTER_STRU                astClusterTable[IMM_MEM_BLK_MAX_CLUSTER_NUM];


    unsigned short                      usImmMemTotalCnt;       /* ���ڴ��һ���ж���IMM_MEM_ST */
    unsigned short                      usImmMemUsedCnt;        /* ʹ���˶���IMM_MEM_ST */
    unsigned long                       ulImmMemTotalByteSize;  /* һ���ж����ֽ� */
    unsigned long                       ulImmMemUsedByteSize;   /* ��ʹ���ڴ��ܴ�С�����ֽ�Ϊ��λ */

    unsigned long                       ulImmMemMaxBlkCcpuUsedCnt; /* ��ߵ�A�˴���C�˵Ŀ���� */

    IMM_MEM_STRU                       *pstImmMemStStartAddr;   /* ָ��ImmMemST�׵�ַ��ָ�� */
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent;
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent;
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc;        /* ָ���ⲿע����ͷź���*/
} IMM_MEM_POOL_STRU;



typedef struct
{
    unsigned short                          usSize;    /* �������Ĵ�С */
    unsigned short                          usCnt;     /* �������� */
}IMM_MEM_CLUSTER_CFG_INFO_STRU;



typedef struct
{
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId;           /* ���� ID */
    unsigned char                       ucClusterCnt;       /* ���ڴ���ж��ټ� */
    unsigned char                       aucResv[2];

    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;  /* ÿ���ľ�����Ϣ */
} IMM_MEM_POOL_CFG_INFO_STRU;
typedef struct
{
    IMM_SAVE_MEM_ALLOC_INFO_CALLBACK             pImmSaveMemAllocDebugInfoFunc;
    IMM_SAVE_MEM_FREE_INFO_CALLBACK              pImmSaveMemFreeDebugInfoFunc;
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK         pImmMemEventRptFunc;
}IMM_MEM_REG_MNTN_FUNC_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern IMM_MEM_POOL_STRU                    g_astImmMemPool[IMM_MEM_POOL_ID_BUTT];
extern const unsigned char                  IMM_MEM_CTRL_POOL_ID;
extern IMM_MEM_POOL_STRU * const            g_pstImmCtrlMemPool;
extern const IMM_MEM_CLUSTER_CFG_INFO_STRU  g_astImmMemCtrlPoolClusterTableInfo[];
extern const unsigned long * const          g_pulImmMemCtrlMemSuffix;
extern const unsigned long * const          g_paulImmMemCtrlMemSpace;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern IMM_MEM_STRU *IMM_MemCtrlHeadAlloc_Debug(unsigned short usFileID, unsigned short usLineNum);

extern IMM_MEM_STRU *IMM_MemBlkAlloc_Debug(unsigned short usFileID, unsigned short usLineNum,
                    unsigned char ucPoolId, unsigned short usLen);

extern void IMM_MemFree_Debug(IMM_MEM_STRU **pstMem);

extern void IMM_MemRegMntnFuncCallBack
(
    IMM_SAVE_MEM_ALLOC_INFO_CALLBACK             pImmSaveMemAllocDebugInfoFunc,
    IMM_SAVE_MEM_FREE_INFO_CALLBACK              pImmSaveMemFreeDebugInfoFunc,
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK         pImmMemEventRptFunc
);

extern  unsigned long IMM_MemRegExtFreeCallBack
(
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
);

extern  unsigned long IMM_MemBlkInit(void);
extern  IMM_MEM_POOL_STRU *IMM_MemPoolGet(unsigned char ucPoolId);
extern  IMM_MEM_POOL_STRU *IMM_MemEventRptPoolGet(unsigned char ucPoolId);

#define IMM_MemFree(pstMem)             IMM_MemFree_Debug(&pstMem)

/* IMM MEM ��ȡ�ڴ��ָ�� */
#define IMM_MEM_GET_POOL(ucPoolId)      (&g_astImmMemPool[(ucPoolId)])

#pragma pack(0)




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of IMM.h */

