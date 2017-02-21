/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                                 ippp.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2004-07-01
 *        Author: YiAn
 *   Description: Defines Component Interfaces for PPP Component.
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-07-01      YiAn            Create
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2008-08-25      f54882          Modify for BC3D00263
 *
 *************************************************************************/

#ifndef _IPPP_H
#define _IPPP_H

#ifdef __cplusplus
extern "C"{
#endif

DECLARE_INTERFACE( IIF_COMP_PPP_ComIntFUN ) 
{
    IUNKNOWN_METHODS
  
    /*this  methods has to be used by upper or lower layer for sending or receiving packets by ppp module  */
    /*delete by y36299 for SWFD03944  2004/12/7
    METHOD_(ULONG, pfPPP_Shell_ReceiveAsyPacket)(MBUF_S *pMbuf);
    METHOD_(ULONG, pfPPP_Shell_ReceiveNegoPacket)(MBUF_S *pMbuf);
    METHOD_(ULONG, pfPPP_Shell_ReceiveStacPacket)(MBUF_S *pMbuf);*/
    METHOD_(ENQUEUE_PF, pfPPP_Shell_ISLInput)(IFNET_S*  pstIfnet, MBUF_S *pMbuf);
    METHOD_(ULONG, pfPPP_Shell_NiOutput)(MBUF_S *pMbuf);
    METHOD_(ULONG, pfPPP_Shell_DropPacket)(MBUF_S *pMbuf, ULONG ulCmd, CHAR *pData);
    
    /* This two methods have to be used by IFNET for sending control message to ppp module  */
    METHOD_(ULONG, pfPPP_Shell_ISLIoCtl)(IFNET_S* pstIfnet, ULONG ulCmd, CHAR *pPara);
    METHOD_(ULONG, pfPPP_Shell_NiIoCtl)(IFNET_S* pstIfnet, ULONG ulCmd, CHAR *pPara);

    /*this method has to be used for getting Mtu of the ppp link*/
    METHOD_(ULONG, pfPPP_Shell_GetMtu)(IFNET_S* pstIfnet);

    /*add by y36299 for SWFD03944  2004/12/7*/
    METHOD_(ULONG, pfGetUserName)(IFNET_S* pstIfnet, CHAR *szName);
    METHOD_(ULONG, pfGetPeerIPAddr)(IFNET_S* pstIfnet, ULONG *ulIpAddr);
    METHOD_(VOID, pfGetInterfaceID)(IFNET_S* pstIfnet, UCHAR * pInterfaceID);

    /* This  method have to be used to collect statistic infomation*/
    METHOD_(ULONG, pfPPP_Shell_GetDataStat)(ULONG ulIfnetIndex, PPPSTATISTIC_S *pstPppDataFlow);

    /*the two methods are the interface used by ppp and auth module*/
    METHOD_( ULONG, pfPPP_Shell_ReceiveAuthResult)(PPPAUTHRESULT_S *pstAuthResult);/*y36299 modify for warning 04/11/03*/

    METHOD_( ULONG, pfPPP_GetPppFsmState)(ULONG ulIfIndex, ULONG* pulPppPhase, 
                                          ULONG* pulPppNegoType, ULONG* pulPppFsmState);
    /* Added by z43740 for PPP�ӿ�����, 2006/06/07 */
    METHOD_( ULONG, pfPPP_GetFsmState)(ULONG ulIfIndex, USHORT usProtocol, ULONG* pulFsmState);
    METHOD_( ULONG, pfPPP_GetPppPhase)(ULONG ulIfIndex, ULONG *pulPhase);
    /* End of modification */
    
    METHOD_( ULONG, pfPPP_ResetLinkByPeerIp)(ULONG ulIfIndex, ULONG ulPeerIpaddr);

    METHOD_( ULONG, pfPPP_CopyCBInfo)(ULONG ulIfIndex, VOID *pstPppCBInfo, ULONG ulFlag);
    METHOD_( ULONG, pfPPP_GetDebugInfo)(ULONG ulIfIndex, PPPDEBUGINFO_S *pstPppDebugInfo);

    METHOD_( VOID, pfPPP_Timer_Out)( VOID *pArg );

    /*x44006 �������úͲ�ѯPPP�ӿ��Ƿ����LCP/NCPЭ�̽ӿ�*/
    METHOD_( ULONG, pfPPP_SetInterfaceNego)(ULONG ulIfIndex,ULONG ulNegoLCP,ULONG ulNegoNCP);
    METHOD_( ULONG, pfPPP_GetInterfaceNego)(ULONG ulIfIndex, ULONG* pulNegoLCP,ULONG* pulNegoNCP);

    METHOD_( ULONG, pfPPP_SetInterfaceNegoOsicp)(ULONG ulIfIndex, ULONG ulNegoOSICP);
    METHOD_( ULONG, pfPPP_GetInterfaceNegoOsicp)(ULONG ulIfIndex, ULONG *pulNegoOSICP);

    /*Added by x36317 for SWID00036, 2005-11-03*/
    METHOD_( ULONG, pfPPP_OpenPPPEntry)(ULONG *pulWaitListHandle);
    METHOD_( ULONG, pfPPP_GetPPPEntry)(ULONG ulEntryWaitList, PPPINFO_S *pstPppInfo);
    METHOD_(ULONG, pfPPP_ClosePPPEntry)( ULONG ulWaitListHandle );
    METHOD_(ULONG, pfPPP_HA_BatchBackup)();
    METHOD_(ULONG, pfPPP_HA_Input)(UCHAR *pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfPPP_HA_Smooth)();
    METHOD_(ULONG, pfPPP_HA_Clean)();
    METHOD_(ULONG, pfPPP_HA_VirtualCfgInput)(UCHAR *pBuf, ULONG ulMsgLen);

    METHOD_(ULONG, pfPPP_PpiRepeateCallback)(ULONG aulArgs[]);
    METHOD_(VOID, pfPPP_Health_BatchCheckup)(VOID);
    METHOD_(ULONG, pfPPP_LastWord_BatchCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);
    METHOD_(ULONG, pfPPP_LastWord_StatisticCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);

    METHOD_(ULONG, pfPPP_SetNegoMagicNum)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfPPP_GetNegoMagicNum)(ULONG ulIfIndex, ULONG *pulSetYes);
    METHOD_(ULONG, pfPPP_SetPppSelfLoop)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfPPP_GetPppSelfLoop)(ULONG ulIfIndex, ULONG *pulSetYes);
    METHOD_(ULONG, pfPPP_SetNcpResendTime)(ULONG ulIfIndex, ULONG ulTime);
    METHOD_(ULONG, pfPPP_GetNcpResendTime)(ULONG ulIfIndex, ULONG *pulTime);
    METHOD_(ULONG, pfPPP_GetLcpEchoInfo)(ULONG ulIfIndex, ULONG ulCmd, VOID  *pData);
    METHOD_(VOID,  pfPPP_GR_DealMsg)(ULONG aulMsg[4]);
    METHOD_(ULONG, pfPPP_SetMaxLoopbackDetectTime)(ULONG ulTime);
    METHOD_(ULONG, pfPPP_GetMaxLoopbackDetectTime)(ULONG *pulTime);
    METHOD_(ULONG, pfPPP_GetPapUserName)(ULONG ulIfIndex, UCHAR *pucUserName);
    METHOD_(ULONG, pfPPP_GetChapUserName)(ULONG ulIfIndex, UCHAR *pucUserName);
    METHOD_(ULONG, pfPPP_GR_RestoreByCase)(IFNET_S *pstIf, PPPINFO_S *pstPppInfo, ULONG ulCaseType);
    METHOD_(ULONG, pfPPP_GR_SmoothByCase)(IFNET_S *pstIf, ULONG ulCaseType);
    METHOD_(ULONG, pfPPP_GetPppByIndex)(ULONG ulIfIndex, PPPINFO_S **ppstPppInfo);
    METHOD_(ULONG, pfPPP_GetPppDownInfo)(ULONG ulIfIndex, ULONG ulProtocolType, PPPDOWNINFO_S *pstPppDownInfo);
};

DECLARE_INTERFACE( IIF_COMP_PPP_ComIntCFG )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_( ULONG , pfPPP_Init_Com ) (COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_( ULONG , pfPPP_Activate_Com) (VOID);
    METHOD_( ULONG , pfPPP_SetModuleInfo ) ( PPP_MOD_INFO_S *pstMInfo );

    /*methods provided to shell for command processing*/
    /*process to select packet compress protocol type or not, right now just support stac compress */
    METHOD_( ULONG, pfPPP_ProcessCompress) (ULONG ulIfIndex, ULONG ulCompress,ULONG ulSetYes);  
    /*process to set ppp negotiate timeout time or use default */
    METHOD_( ULONG, pfPPP_ProcessNegotiateTimeout ) (ULONG ulIfIndex, ULONG ulSetYes, ULONG ulTimeoutTime);
    /*process to set ppp authentication type :pap, chap or not use authentication */
    METHOD_( ULONG, pfPPP_ProcessAuthenticationType) (ULONG ulIfIndex, ULONG ulSetYes, ULONG usPap, ULONG usChap, ULONG usCallin);
    /*set the debug switch of the debug info type*/
    METHOD_( ULONG, pfPPP_ProcessDebug)(ULONG ulIfIndex, 
                                        ULONG ulDebugAll, 
                                        ULONG ulSetYes, 
                                        ULONG ulType,
                                        USHORT usProtocol, 
                                        ULONG ulPacketNum, 
                                        ULONG ulPacketOctets);
    /*the two blow are used to set the hostname, P***W*** of chap authentication*/
    METHOD_( ULONG, pfPPP_ProcessChapHostname)(ULONG ulIfIndex, ULONG ulSetYes, CHAR *pcHostname);
    METHOD_( ULONG, pfPPP_ProcessChapPassword)(ULONG ulIfIndex,ULONG ulSetYes, ULONG usEncrypt, UCHAR *pcPassword);
    /*set user name and P***W*** of pap authentication*/
    METHOD_( ULONG, pfPPP_ProcessPapNamePwd)(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
    METHOD_( ULONG, pfPPP_ProcessCallbackAcceptMsg)(ULONG ulIfIndex, ULONG ulNo);
    METHOD_( ULONG, pfPPP_ProcessCallbackRequest )(ULONG ulIfIndex, ULONG ulNo);
    METHOD_( ULONG, pfPPP_ProcessIPCPDNSAddr)(ULONG ulIfIndex, ULONG ulPriIpAddress, ULONG ulSecIpAddress, ULONG ulFlag);
    METHOD_( ULONG, pfPPP_ProcessIPCPDNSAccept)(ULONG ulIfIndex , ULONG ulNo);
    METHOD_( ULONG, pfPPP_SetDebugSwitch)(ULONG ulPppDebugFlag);  
    METHOD_( ULONG, pfSetVjCompEnable)(ULONG ulIfIndex, ULONG ulSetYes);

    /* Added by z43740 for IPHC,2005/09/20*/
    METHOD_( ULONG, pfPPP_ProcessIPHCEnable) (ULONG ulIfIndex, ULONG ulEnable, ULONG ulCCompany);
    METHOD_( ULONG, pfPPP_ProcessTcpSpace) (ULONG ulIfIndex, ULONG ulTcpSpace, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessNonTcpSpace) (ULONG ulIfIndex, ULONG ulNonTcpSpace, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessFMaxPeriod) (ULONG ulIfIndex, ULONG ulFMaxPeriod, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessFMaxTime) (ULONG ulIfIndex, ULONG ulFMaxTime, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessMaxHeader) (ULONG ulIfIndex, ULONG ulMaxHeader, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessNegoSubOptions) (ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG, pfPPP_ProcessRtpCompression) (ULONG ulIfIndex, ULONG ulRtpCompression, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessCompressType) (ULONG ulIfIndex, ULONG ulCompressType, ULONG ulReset);
    METHOD_( ULONG, pfPPP_ProcessClearIfIPHCContext) (ULONG ulIfIndex);
    
    /* Added by z43740 for IPHC debug enhance, 2006/05/12*/
    METHOD_( ULONG, pfPPP_ProcessClearIfIPHCStat)(ULONG ulIfIndex);
    /* Added by Sunmo(44939) for A82D02217, 2006-06-15; and Modified by Sunmo for A82D03499, 2006-07-12 */
    METHOD_( ULONG, pfPPP_ProcessDeleteUdpChkSum) (ULONG ulIfIndex, ULONG ulDeleteUdpChkSum);
    /* End of addition for IPHC,2005/09/20*/
    
    /* Added by z43740 for PPP header compression 2006/05/08 */
    METHOD_( ULONG, pfPPP_ProcessPFCEnable)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG, pfPPP_ProcessACFCEnable)(ULONG ulIfIndex, ULONG ulSetYes);

    METHOD_( ULONG , pfPPP_HA_GetPppDbg )  (ULONG *pulDbg);
    METHOD_( ULONG , pfTCPIP_HA_SetPppDbg ) (ULONG ulDbg);
    METHOD_( ULONG , pfPPP_HA_SetVerboseDbg) (ULONG ulDbg);
    METHOD_( ULONG , pfPPP_HA_GetVerboseDbg) (ULONG *pulDbg);
    METHOD_( VOID , pfPPP_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);

    /*(ͬ�����ⵥA82D11804)Added by f54882, 2007-2-2, HDLC�Զ������Ǳ������ܿ���*/
    METHOD_(ULONG, pfPPP_SetDiscrSpecial) (ULONG ulSet);     
    /*(ͬ�����ⵥA82D17438)add by wuhailan, 2007-7-5.����PPP��λ��ʱ��*/
    METHOD_(ULONG, pfPPP_SetPPPResetTime) (ULONG ulTime); 
    /* ����LQM ģ��ӿ� */
    METHOD_( ULONG , pfPPP_ProcessLQMNeg)( ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG , pfPPP_ProcessLQMPeriod)( ULONG ulIfIndex, USHORT usLqrPeriod);
    METHOD_( ULONG , pfPPP_ProcessLQMLimit)( ULONG ulIfIndex, ULONG ulCloseValue,ULONG ulResumeValue);
     /* Added by y62007 for V1R5C02,2007/05/16 */    
    METHOD_(ULONG, pfPPP_SetIpcpNegoDns)(ULONG ulIfIndex, ULONG ulSetYes);
    /*add by wuhailan for A82D18512, 2007-8-2.����MP�ն�������һ���Լ�⿪��*/
    METHOD_(ULONG, pfPPP_SetMpEDConsistent) (ULONG ulSetYes);
    METHOD_(ULONG, pfPPP_GetMpEDConsistent) (VOID);

    METHOD_(ULONG, pfPPP_ResetIPCP)(ULONG ulIfIndex);
    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
    METHOD_(ULONG, pfPPP_ResetIP6CP)(ULONG ulIfIndex);
    /*End of Added by hanna55555, 2009/3/20 */
    METHOD_(ULONG, pfPPP_ResetOSICP)(ULONG ulIfIndex);

    METHOD_(ULONG, pfPPP_ProcessIPHCUniDirection)(ULONG ulIfIndex, ULONG ulEnable);

    METHOD_(ULONG, pfPPP_PPI_SetVerifySwitch)(ULONG ulSwitch, ULONG ulPeriod, ULONG ulIfNum);
    METHOD_(ULONG, pfPPP_PPI_GetVerifySwitch)(PPPVERIFYSWITCH_S *pstPppVerifySwitch);
    METHOD_(ULONG, pfPPP_Set_NegTimeoutWaring)(ULONG ulTime);    
    METHOD_(ULONG, pfPPP_Get_NegTime)(ULONG *pulTime);    
    
    METHOD_(ULONG, pfGR_SetDebug)(ULONG ulDebugSwitch);
    METHOD_(ULONG, pfGR_GetDebug)(ULONG *pulDebugSwitch);
    METHOD_(ULONG, pfPPP_SetDealAcfcPfcFlag)(ULONG ulIfIndex, ULONG ulFlag);
    METHOD_(ULONG, pfPPP_GetDealAcfcPfcFlag)(ULONG ulIfIndex, ULONG *pulFlag);
    METHOD_(ULONG, pfPPP_GetAuthenticationType)(ULONG ulIfIndex, ULONG *pulType, ULONG *pulCallInAuth);
    
};    

DECLARE_INTERFACE( IIF_COMP_PPP_ComIntSSA )
{
    IUNKNOWN_METHODS

    /* Methods provided to shell for functionality purpose */ 
    METHOD_( ULONG , pfPPP_RegShellApi ) ( PPP_SHELL_CALLBACK_SET_S *pstCallBkSet);

    /* Methods provided to shell for ppp timer */ 
    /* METHOD_( VOID , pfPPP_TimerOut) (); */

};

/* For implement of QuerfyInstance() */
typedef struct tagPPPINT_OBJ_S
{
    IIF_COMP_PPP_ComIntFUN  *pComIntFUN;
    IIF_COMP_PPP_ComIntCFG  *pComIntCFG;
    IIF_COMP_PPP_ComIntSSA  *pComIntSSA;
    IIF_IFS_IntFun  *pComIntIFG;
}PPP_INT_OBJ_S;


#ifdef __cplusplus
}
#endif

#endif
