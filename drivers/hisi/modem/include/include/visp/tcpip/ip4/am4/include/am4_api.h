
#ifndef __AM4_API_H__
#define __AM4_API_H__

#ifdef __cplusplus
extern "C"{
#endif

/*Ų��am4_core.h*/
/*f47854 modify begin*/
#define MAXADDR_ON_ONEIF    48
#define IPADDR_ADD 1
#define IPADDR_DEL 0
#define CFG_SECONDARY_IPADDR 0
#define CFG_PRIMARY_IPADDR 1
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define MAXADDR_DESCRIPTION_LEN 47
#define IP4_MAX_VRFNAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
/*f47854 modify end*/

#define RTM_NEWADDRESS      0x20    /* IP��㱨���ؽӿڵĵ�ַ*/
#define RTM_DELADDRESS      0x40    /* IP��ɾ�����ؽӿڵĵ�ַ*/
#define RM_IM_MSG_ADDIP     RTM_NEWADDRESS  /* New IP address configured */
#define RM_IM_MSG_DELIP     RTM_DELADDRESS  /* IP address deleted */

#define RM_IM_STATE_PRIMARY     0x0008  /* It's the IP address configured on an physical interface without 
                                           "secondary" keyword. */
#define RM_IM_STATE_BORROW      0x0010  /* Contrary to the above */

#define INVALID_VRF             0xffffffff
typedef struct tagINADDR
{
    ULONG s_ulAddr;
}INADDR_S;

typedef struct tagTCPIP_IPIFADDR
{    
    struct tagINADDR ia_stAddr;
    /* net info */
    struct tagINADDR ia_stNet;
    struct tagINADDR ia_stNetMask;
    struct tagINADDR ia_stNetBroadcast;
    /* subnet info */
    struct tagINADDR ia_stSubnet;
    struct tagINADDR ia_stSubnetMask;
    struct tagINADDR ia_stSubnetBroadcast;
    /* dst info */
    struct tagINADDR ia_stDstAddr;
    /*Modify for BC3D00792,DR.137֧��ȫ�ֵ�ַ������*/
    ULONG  ulIpIfIndex;
    ULONG  ulIsMainIp;
    /* add  for api TCPIP_GetAddrTable*/
    ULONG  ulIfIndex;
} TCPIP_IPIFADDR_S;

/*VR7�û�API���ģ����ݽṹIP_AM4_IF_ADDR_SŲ��am4_core.h��edited by z00104207*/
typedef struct tagIpAm4IfAddr
{
    ULONG ulAddrNum;
    ULONG ipif_address[MAXADDR_ON_ONEIF];
    ULONG ipif_mask[MAXADDR_ON_ONEIF];
}IP_AM4_IF_ADDR_S;

/* AM4���÷��ش���ţ�ͬʱ��Ϊģ����Ӣ����Ϣ���±� 
��ע��ͬ���޸� am4_sh_info.c�ļ���CHAR * ErrInf_AM4_En[]������Ϣ*/
enum enum_IP_AM4_ERR
{
    ERR_AM4_OK = 0,                          /* 0 success */
    ERR_AM4_NOPRIADDR,                       /* 1 ����ַ������ */
    ERR_AM4_DELSECBFPRI,                     /* 2 ɾ������ַ֮ǰ������ɾ���ӵ�ַ */
    ERR_AM4_INVALIDADDR,                     /* 3 ��ЧIP��ַ */
    ERR_AM4_NOSECADDR,                       /* 4 �ôӵ�ַ������ */
    ERR_AM4_SECPRIISSAME,                    /* 5 �ӵ�ַ����������ַ��ͬ */
    ERR_AM4_ADDREXIST,                       /* 6 �õ�ַ�Ѿ����� */
    ERR_AM4_SECFAIL,                         /* 7 ֻ������������ַ,�������ôӵ�ַ */
    ERR_AM4_MAX,                             /* 8 ��������ַ�� */
    ERR_AM4_INVALIDLENDIN,                   /* 9 ��Ч�Ľ���ӿ� */
    ERR_AM4_ADDRCONFLICT,                    /* 10 ��ַ��ͻ */
    ERR_AM4_INVALIDIN,                       /* 11 ����������Ϸ� */
    ERR_AM4_CANTNONEGO,                      /* 12 δ����Э�̵�ַ������ȡ�� */
    ERR_AM4_INVALIDBRIN,                     /* 13 ��Ч�Ľ���ӿ� */
    ERR_AM4_CANTUSEUNIN,                     /* 14 ���õ��ĵ�ַ����ת�� */
    ERR_AM4_CANTNOUNNUMBER,                  /* 15 δ���õ�ַ���ã�����ȡ�� */
    ERR_AM4_INVALIDMAC,                      /* 16 ��Ч��MAC��ַ */
    ERR_AM4_NOARPENTRY,                      /* 17 û�����ARP�� */
    ERR_AM4_ARPMAX,                          /* 18 ARP��Ŀ���Ѿ��ﵽ���ֵ */
    ERR_AM4_MALLOCFAIL,                      /* 19 �ڴ����ʧ�� */
    ERR_AM4_WRONGCOMMAND,                    /* 20 �����ֲ��Ϸ� */
    ERR_AM4_NOT_IN_ONEVPN,                   /* 21 ���ýӿ�VRF�ͱ����ýӿ�VRF����ͬһ��*/
    ERR_AM4_NOVRF,                           /* 22 ָ����VPNʵ�������ڻ�VPNʵ��û������Route-Distinguisher */
                                             
    ERR_AM4_VRRP,                            /* 23 ĳЩ���Ϸ�������IP��ַ�ѱ�ɾ�� */
    ERR_AM4_VRRP_EQUAL_VRITUAL_IP,           /* 24 ĳЩ����·���������ȼ���Ϊ��255 */
    ERR_AM4_DISPARP_INVALIDMASK,             /* 25 ��Ч���� */
    ERR_AM4_DISPARP_RPCFAIL,                 /* 26 RPCʧ�� */
    ERR_AM4_DISPARP_WAITLIST_REGISTER_FAIL,  /* 27 Waitlistע��ʧ�� */
    ERR_AM4_DISPARP_WAITLIST_GET_FAIL,       /* 28 Waitlistȡ����ʧ�� */
    ERR_AM4_DISPARP_SPECIFY_SUBIF_AND_VLAN,  /* 29 ��ָ���ӽӿں�VID */
           
    ERR_AM4_IPCRPCERR,                       /* 30 IPC/RPC ���� */
    ERR_AM4_CANTNODHCP,                      /* 31 û������DHCP�����ַ������ȡ�� */
    ERR_AM4_GENERR,                          /* 32 �����ַ���� */
    ERR_AM4_ISBINDING,                       /* 33 �ӿ�����ִ��ip binding��undo ip bindingʱ���������õ�ַ */
    ERR_AM4_NOFREE_ITEM,                     /* 34 RIBû�п��ÿռ� */

    ERR_AM4_HA_IS_SMOOTHING,                 /* 35 HA����ƽ��������ֶ���������*/

    ERR_AM4_INTERFACE,                       /* 36 ָ���Ľӿڲ��������� */
    ERR_AM4_IPCTL,                           /* 37 ��Ч��IP���ƿ� */
    ERR_AM4_GENERR_DELPRIADDR,               /* 38 ɾ������ַ����(��֪ͨ��·��) */
    ERR_AM4_GENERR_DELSECONDARY,             /* 39 ɾ���ӵ�ַ����(��֪ͨ��·��)*/
    ERR_AM4_GENERR_DELALL,                   /* 40 ɾ�����е�ַʱ(��֪ͨ��·��) */
    ERR_AM4_GENERR_ADDSECONDARY,             /* 41 ���Ӵӵ�ַʱ����(��֪ͨ��·��) */
    ERR_AM4_GENERR_ADDPRI,                   /* 42 ��������ַʱ����(��֪ͨ��·��) */
    ERR_AM4_DELPRI,                          /* 43 ɾ������ַ���� */
    ERR_AM4_ADDRESS,                         /* 44 ��ַ��Ч */
    ERR_AM4_DELSECONDARY,                    /* 45 ɾ���ӵ�ַ���� */
    ERR_AM4_ADDSECONDARY,                    /* 46 ���Ӵӵ�ַ���� */
    ERR_AM4_ADDPRI,                          /* 47 ��������ַ���� */
    ERR_AM4_INVALIDIN_2,                     /* 48 ����������Ϸ� */
    ERR_AM4_INVALIDIN_3,                     /* 49 ����������Ϸ� */
    ERR_AM4_INVALIDIN_4,                     /* 50 ����������Ϸ� */
    ERR_AM4_NOFREE_ITEM_2,                   /* 51 RIBû�п��ÿռ� */
    ERR_AM4_NOFREE_ITEM_3,                   /* 52 RIBû�п��ÿռ� */
    ERR_AM4_NOFREE_ITEM_4,                   /* 53 RIBû�п��ÿռ� */
    ERR_AM4_LOOPBACKORNULL,                  /* 54 ���ýӿ�Ϊloopback��null�ӿ� */
    ERR_AM4_INVALIDBRIN_2,                   /* 55 ��Ч�Ľ���ӿ� */
    ERR_AM4_INVALIDBRIN_3,                   /* 56 ��Ч�Ľ���ӿ� */
    ERR_AM4_INVALIDBRIN_4,                   /* 57 ��Ч�Ľ���ӿ� */
    ERR_AM4_INVALIDBRIN_5,                   /* 58 ��Ч�Ľ���ӿ� */
    
    ERR_AM4_INVALIDLENDIN_2,                 /* 59 ��Ч�Ľ���ӿ� */
    ERR_AM4_INVALIDLENDIN_3,                 /* 60 ��Ч�Ľ���ӿ� */
    ERR_AM4_CFG_DHCP4R,                      /* 61 �ӿ�������DHCP4 RELAY */
    ERR_AM4_IFISVT,                          /* 62 �ӿ���VT���ͣ��������ý��õ�ַ */

    ERR_AM4_PARAM,                           /* 63 �������� */
    ERR_AM4_NO_NEGO,                         /* 64 ȡ��Э��ʱ���� */
    ERR_AM4_ADDRINEXISTENCE,                 /* 65 ���õĵ�ַ�Ѿ����� */
    ERR_AM4_LENDINLOOKBACK,                  /* 66 INLOOKBACK�ӿڵ�ַ���ܱ����� */

    ERR_AM4_IF_NULL,                         /* 67 �ӿ�IFNETָ��Ϊ�� */
    ERR_AM4_NOADDR,                          /* 68 �ӿ��޵�ַ */
    ERR_AM4_PPP_COMP_NULL,                   /* 69 PPP������Ϊ�� */    
    ERR_AM4_NOT_SAME_BOARD,                  /* 70 �������ӿڲ���ͬһ�鵥���� */
    ERR_AM4_VIRTUAL_IFNET,                   /* 71 ��ӿ�*/
    ERR_AM4_IF_NOT_EXIST,                    /* 72 �ӿڲ�����*/
    
    ERR_AM4_END,                             /* 73 �ӿ�û�е�ַ��ȫ�ֵ�ַ��Ϊ��*/

    /*BEGIN Add by h55555 for V1R7C02*/
    ERR_AM4_IFTYPE,                          /* 74 �ӿ����ʹ��� */
    ERR_AM4_IPIFNET_NULL,                    /* 75 �ӿ�IP���ƿ�ָ��Ϊ�� */
    /*END Add*/

    ERR_AM4_IS_L2PORT,                       /* 76 �����Ŀ��ӿ��Ƕ���˿� */
    
    ERR_AM4_GETWAITLIST_FAIL,                /* 77 ��ȡwaitlistʧ�� */
    ERR_AM4_SETWAITLIST_FAIL,                /* 78 ����waitlistʧ��*/ 
    ERR_AM4_CLOSEWAITLIST_FAIL,              /* 79 �ر�waitlistʧ�� */
    ERR_AM4_OPENWAITLIST_FAIL,               /* 80 ��waitlistʧ�� */

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ERR_AM4_GET_VRFINDEX,                    /* 81 ��ȡVRF ����ʧ�� */
    ERR_AM4_INVALID_VRFINDEX,                /* 82 VRF ������ƥ�� */
    ERR_AM4_NULL_POINT,                      /* 83 ����ָ�����Ϊ�� */
    ERR_AM4_VRF_NOT_INIT,                    /* 84 VRF���δע�� */
    ERR_AM4_NOT_FINDIF,                      /* 85 ����IP���ҽӿ�ʧ�� */
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    
    ERR_AM4_MAX_INVALID_END                 /* 255 ���ֵ */
}; 
/* AM4���÷��ش���ţ�ͬʱ��Ϊģ����Ӣ����Ϣ���±� 
��ע��ͬ���޸� am4_sh_info.c�ļ���CHAR * ErrInf_AM4_En[]������Ϣ*/

typedef struct tagIpAddrNotifyMsg
{
    ULONG  ulIfnetIndex;     /* IFNET index of bound physical interface */
    ULONG  ulIpFlag;         /* IP address flag, such as primary or borrow */
    ULONG  ulLogAddr;        /* IP address */
    ULONG  ulSubMask;        /* Address mask */
    UCHAR  ucMsgType;        /* IP address added or deleted */
    UCHAR  ucPadding[3]; 
}IP_ADDR_NOTIFY_MSG_S;  

typedef struct tagIfAddrmsg
{
    ULONG   ulIntfIndex;        /* �ӿ����� */
    USHORT  usMsgType;          /* ��Ϣ���� */
    UCHAR   ucPadding[2]; 
    ULONG   ulIpFlag;           /* ����IP�ȱ�־ */
    SOCKADDR_S  sLocalAddr;     
    SOCKADDR_S  sNetMask;       /* �������� */
    SOCKADDR_S  sPrimaryAddr;   /* �µ�����ַ */
}IFADDRMSG_S;

/*f47854 add begin*/
typedef struct tagIpAddrOper
{
    ULONG ulOper;
    ULONG ulIpAddr;
    ULONG ulMask;
    ULONG ulPrimary;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szIfName[IF_MAX_INTERFACE_NAME_LEN + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}IPADDR_OPER_S;
/*f47854 add end*/

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagIpAddrFilter
{
    ULONG ulIfIndex;
    CHAR szVrfName[IP4_MAX_VRFNAME_LENGTH + 1];
    ULONG ulIsAll;
}IPADDR_FILTER_S;
typedef struct tagIpAddrDecOper
{
    ULONG ulIpAddr;
    CHAR szDesc[MAXADDR_DESCRIPTION_LEN + 1];
    CHAR szVrfName[IP4_MAX_VRFNAME_LENGTH + 1];
}IPADDR_DEC_OPER_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef ULONG(*AM4_SHELL_RM_CALLBACK_FUNC_PTR)(USHORT usInstanceID, struct tagIpAddrNotifyMsg *pstIpMsg, struct tagIfAddrmsg * pstIPMsg);/*add by x36530*/

extern ULONG TCPIP_AddIpAddr (ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_AddPrimaryAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_AddSecondAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_CloseAddrTable(UINTPTR ulWaitlist);

extern ULONG TCPIP_ConflictIpAddressSpecial(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);

extern ULONG TCPIP_DelIpAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_DelPrimaryAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_DelSecondAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_GetAddrNumOnIf(ULONG ulIfIndex);

extern ULONG TCPIP_GetAddrTable(UINTPTR ulWaitlist,TCPIP_IPIFADDR_S *pIfa,ULONG ulIfIndex);

extern ULONG TCPIP_GetIpHADbg(ULONG *pulDbg);

extern ULONG TCPIP_GetLocalIpAddr(ULONG ulIfIndex, IP_AM4_IF_ADDR_S *pstIPIfAddr);

extern ULONG TCPIP_GetMainIpAddr(ULONG ulIfIndex,ULONG *pulMainAddr, ULONG *pulMainMask);

extern ULONG TCPIP_GetPeerIpAddr(ULONG ulIfIndex, ULONG *pulIpAddr);

extern ULONG TCPIP_OpenAddrTable(UINTPTR *pulWaitlist,ULONG ulIfIndex);

extern ULONG TCPIP_ProIpNegoSet(ULONG ulIfIndex, ULONG ulSetYes);

extern ULONG TCPIP_RegFuncUpdateIntfAddrHook(AM4_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc);

extern ULONG TCPIP_SetIpHADbg(ULONG ulDbg);

extern ULONG TCPIP_UnnumberIpAddr(ULONG ulIfIndex, ULONG ulIfIndexLendIn, ULONG ulSetYes);

extern ULONG TCPIP_IsLocalIfAddr(ULONG ulIpAddr);
extern ULONG TCPIP_Proc_IPAddr( IPADDR_OPER_S* pIpAddrOper );
extern ULONG TCPIP_SetIPAddrDescription( ULONG ulIpAddr, CHAR* pucDesc );
/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByIP
*  Description: ͨ��IP��ȡ��Ӧ�Ľӿ�����
*        Input: ULONG ulIPAddr:IP��ַ(������)
*       Output: ULONG *pulIfIndex:���صĽӿ�����ֵ
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: ���õĵ�ַ�޷����ض�Ӧ�Ľӿ�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-31   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByIP(ULONG ulIPAddr, ULONG *pulIfIndex);


extern ULONG TCPIP_SetHostRouteReserved(ULONG ulIfIndex, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetHostRouteReserved
*  Description: ��ȡ�ӿ�DWONʱ�Ƿ�������·�ɵı��
*        Input: ULONG ulIfIndex:�ӿ�������ֻ����ETH��Trunk�Ķ�Ӧ�Ľӿڣ�
*       Output: ULONG *pulFlag:��ʶ
*       Return: �ɹ�: VOS_OK
*               ʧ��: FIB_HA_IS_SMOOTHING
*                     FIB_ERR_NULL_POINTER
*                     FIB_ERR_INVALID_INTERFACE
*                     FIB_ERR_INVALID_IFTYPE
*                     FIB_ERR_INVALID_IPCTL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetHostRouteReserved(ULONG ulIfIndex, ULONG *pulFlag);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_OpenAddrTableByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: ע��waitlist
*        Input: IPADDR_FILTER_S szFilter:    ��������
*       Output: ULONG *pulWaitlist: waitlist���
*       Return: �ɹ�:VOS_OK
*               ʧ��:
*               ERR_AM4_INVALIDIN:              ����������Ϸ�
*               ERR_AM4_GENERR:                 �����ַ����
*               ERR_AM4_END:                    δ֪����
*               ERR_WAITLIST_INVALID_HANDLE:    waitlist�����Ч
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenAddrTableByVrf(UINTPTR *pulWaitlist,IPADDR_FILTER_S szFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetAddrTableByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: ��ȡ��ַ������һ���ڵ�
*        Input: ULONG   ulWaitlist:waitlist���
*               IPADDR_FILTER_S szFilter:    ��������
*       Output: TCPIP_IPIFADDR_S *pIfa:��ַ�ڵ����������������û�ָ��
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR, ERR_AM4_INVALIDIN,
*                    ERR_AM4_END,ERR_WAITLIST_INVALID_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetAddrTableByVrf(UINTPTR ulWaitlist, TCPIP_IPIFADDR_S *pIfa, IPADDR_FILTER_S szFilter);
/*******************************************************************************
*    Func Name: TCPIP_SetIPAddrDescriptionByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: ����IP��ַ������Ϣ
*        Input: pIpDesInfo
*        Output: ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPAddrDescriptionByVrf(IPADDR_DEC_OPER_S *pIpDesInfo);
/*******************************************************************************
*    Func Name: TCPIP_IsLocalIfAddrByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: ����ָ����IP��ַ����ȫ��IP��ַ��,�жϸ�IP��ַ�Ƿ��Ǳ���ĳ���ӿڵ�IP��ַ
*        Input: ULONG ulIpAddr:IP��ַ(������)
*       Output: 
*       Return: �ɹ�:0, ʧ��:1
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_IsLocalIfAddrByVrf(ULONG ulIpAddr,CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByIpByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: ͨ��IP��ȡ��Ӧ�Ľӿ�����
*        Input: ULONG ulIPAddr:IP��ַ(������)
*       Output: ULONG *pulIfIndex:���صĽӿ�����ֵ
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: ���õĵ�ַ�޷����ض�Ӧ�Ľӿ�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByIpByVrf(ULONG ulIPAddr, CHAR *pszVrfName, ULONG *pulIfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*****************************************************************************
 �� �� ��  : TCPIP_CheckIpIsOnIf
 ��������  : �ж�IP��ַ�Ƿ��Ǹ����ӿ��ϵ�IP��ַ
 �������  : ULONG ulIfIndex  
             ULONG ulIpAddr   
 �������  : ULONG *pulFlag : 
            VOS_TRUE:IP��ַ��ָ���Ľӿ���
            VOS_FALSE:IP��ַ���ڽӿ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��4��24��
    ��    ��   : w62223
    �޸�����   : �����ɺ���

*****************************************************************************/
extern ULONG TCPIP_CheckIpIsOnIf( ULONG ulIfIndex, ULONG ulIpAddr,ULONG *pulFlag );

/*******************************************************************************
*    Func Name: TCPIP_GetIPAddrFlag
* Date Created: 2009-12-15
*       Author: Gexianjun/h00121208
*  Description: ��ȡ�ӿ�IP��ַ�����ԣ���ַЭ�̡�����IP��ַ�����Լ���IP��ַ
*        Input: ULONG ulIfIndex:    �ӿ�����
*       Output: ULONG *pulAddrFlag: �ӿ�IP��ַ����
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIPAddrFlag(ULONG ulIfIndex, ULONG *pulAddrFlag);

#ifdef __cplusplus
}
#endif

#endif /* __AM4_API_H__ */

