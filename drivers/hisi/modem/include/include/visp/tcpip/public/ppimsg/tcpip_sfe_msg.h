/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_msg.h
*
*  Project Code: VISPV100R008C02
*   Module Name: MSG 
*  Date Created: 2009-8-20
*        Author: zhangchunyu(62474)
*   Description: �����浽��������Ϣͨ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-20  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _TCPIP_SFE_MSG_H_
#define _TCPIP_SFE_MSG_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

/* ���������������ظ���Ϣ��������󳤶� */
#define MAX_RECV_FROM_SFE_LEN  1024

/* �ͷ�ͨ���ڴ� */
#define SFE_MSG_Free(pSendMsgBuf, pRcvMsgBuf)\
{\
    if (pSendMsgBuf)\
    {\
        (VOID)g_pfFreeMsgFun(pSendMsgBuf);\
    }\
    \
    if (pRcvMsgBuf)\
    {\
        (VOID)g_pfFreeMsgFun(pRcvMsgBuf);\
    }\
}

extern g_pfSendMsgToSFE g_pfSendMsgToSfeFun;
extern g_pfRecvMsgFromSFE g_pfRecvMsgFromSfeFun;
extern g_pfAllocMsg g_pfAllocMsgFun;
extern g_pfFreeMsg  g_pfFreeMsgFun;

/* �����淢��������ĸ�ģ���������Ϣ����� */
extern UINT32 g_u32PpiMsgSeq[MOUDLE_TYPE_MAX][MSG_TYPE_NP_MAX];
/* ����������к� */
extern UINT32 g_u32SfeTableSeq;

/* �������������յ���������Ϣ����� */
extern UINT32 g_u32SfeEventExpSeq[SFE_MAX_EVENT];

/* ͨ����Ϣ���¼����Կ��� */
extern UINT32 g_u32CtrlMsgOrEvtDebugSwitch;

extern UINT32 TCPIP_RcvSfeEventMsgDispatch(VOID *pMsg);
extern UINT32 SFE_MSG_Proc(UINT32 u32MoudleID, UINT32 u32MsgType, UINT32 u32OperType,
                            UINT32 u32SendDataLen, INT8 *pSendDataBuf, UINT32 u32RcvDataLen, INT8 *pRcvDataBuf);
extern UINT32 SFE_MSG_Malloc(INT8 **ppSendMsgBuf, UINT32 u32SendMsgLen, 
                            INT8 **ppRcvMsgBuf, UINT32 u32SRcvMsgLen);
extern UINT32 SFE_MSG_Encapsule(UINT32 u32MoudleID, UINT32 u32MsgType, UINT32 u32OperType, UINT32 u32DataLen, 
                            INT8 *pData, INT8 *pMsg);
extern UINT32 SFE_MSG_SendRcv(INT8 *pSendMsgBuf, UINT32 u32SendMsgLen, INT8 *pRcvMsgBuf, UINT32 u32RcvBufLen, 
                            UINT32 u32ExpectRcvLen, UINT32 u32RcvDataLen, INT8 *pRcvDataBuf);
extern USHORT TCPIP_MSG_CalcCksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern USHORT TCPIP_MSG_GetCksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern VOID TCPIP_MsgOrEvent_InOutDebug(UINT32 u32Type, UINT32 u32InOrOut, 
                                 VOID *pData, UINT32 u32Len);
#ifdef  __cplusplus
}
#endif
   
#endif



