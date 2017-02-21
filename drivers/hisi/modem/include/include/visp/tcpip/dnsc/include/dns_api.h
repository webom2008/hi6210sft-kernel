/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_api.h
*
*  Project Code: VISPV1R7
*   Module Name: dns
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: dns�û�API�ӿ��ļ�,��ͷ�ļ��漰��IPV6�ĵ�ַ���ݽṹVRP_IN6ADDR_S,��Ҫ�Ȱ���IPV6ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
#ifndef _DNS_API_H_
#define _DNS_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* �����б�����������󳤶�*/
#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20
#endif

/*
����rfc882�ĵ�������������:
To simplify implementations, the total number of octets that
represent label octets and label lengths is limited to 255.  Thus
a printed domain name can be up to 254 characters.

����VISP֧��DNS������󳤶�Ϊ254
*/
#define DNS_DOMAIN_NAME_LENGTH 254

/* �����б���������������*/
#define DNS_DOMAIN_LIST_NUM         10

/* ������������������*/
#define DNS_DOMAIN_SERVER_NUM        6

#define DNS_MAX_INTERFACE_NAME_LEN  47  /*�ӿ�������,��MAX_INTERFACE_NAME_LENֵһ��,���иĶ���Ҫͬ������*/

/*����DNS������������ʹ�õĺ�ֵ*/
#define DNS_ADD_SERVER_IP      0  /*��ʾ����ָ��������������ַ*/
#define DNS_DEL_SERVER_IP      1  /*��ʾɾ��ָ��������������ַ*/
#define DNS_DEL_ALL_SERVER_IP  2  /*��ʾɾ��ȫ��������������ַ.*/

#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef struct tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

typedef struct tagTCPIP_IPV6_DNS_SERVADDRINFO
{   
    VRP_IN6ADDR_S stIpAddr;
    ULONG         ulIfIndex;
    CHAR          szInterfaceName[DNS_MAX_INTERFACE_NAME_LEN + 1];   
}TCPIP_IPV6_DNS_SERVADDRINFO_S;

/*dns������Ϣ�ṹ,��DomainInfo_S�ṹһ�£������޸ģ�Ҫ��ͬ���޸�*/
typedef struct  tagTCPIP_DomainInfo
{
     ULONG  ulDomainServer[DNS_DOMAIN_SERVER_NUM];
     TCPIP_IPV6_DNS_SERVADDRINFO_S stDomainServer6[DNS_DOMAIN_SERVER_NUM];
     CHAR   szDomainList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];
     UCHAR  ucPadding[2]; 
}TCPIP_DomainInfo_S;


/*dnsģ������붨��*/
/*ע��:����޸Ĵ����룬��ͬ���޸�dns_sh_info.c �ļ��е�CHAR *Inf_Dnsc_En[]������Ϣ*/
enum enum_DnsErr_INFO
{
    /* success */
    DNSC_SUCCESS       = 0,                  /* 0 */

    /* error code */
    DNS_INVALID_V4_ADDR,                     /* 1 */
    DNS_INVALID_V6_ADDR,                     /* 2 */
    DNS_UNSPECIFIED_ADDR,                    /* 3 */
    DNS_MULTICAST_ADDR,                      /* 4 */
    DNS_NO_DOMAIN_SERVER,                    /* 5 */
    DNS_ILLEGAL_V6_SERVER_ADDR,              /* 6 */
    DNS_ILLEGAL_INTF_NAME,                   /* 7 */
    DNS_TOO_MANY_SERVERS,                    /* 8 */
    DNS_EXISTING_SERVER,                     /* 9 */
    DNS_SPECIFY_INTF_NAME,                   /* 10 */
    DNS_INVALID_INTF_NAME,                   /* 11 */
    DNS_INVALID_DOMAIN_NAME,                 /* 12��������Ч�����ܹ����򳤶�Ϊ0���зǷ��ַ� */
    DNS_NO_DOMAIN_NAME,                      /* 13 */
    DNS_TOO_MANY_DOMAINS,                    /* 14 */
    DNS_EXISTING_DOMAIN,                     /* 15 */

    /* info code */
    DNS_V4_SERVERS,                          /* 16 */
    DNS_DOMAIN_SERVER,                       /* 17 */
    DNS_IP_ADDR,                             /* 18 */
    DNS_NO_SERVERS,                          /* 19 */
    DNS_V6_SERVERS,                          /* 20 */
    DNS_IPv6_ADDR,                           /* 21 */
    DNS_INTF_NAME,                           /* 22 */
    DNS_NO,                                  /* 23 */
    DNS_DOMAIN_NAME,                         /* 24 */
    DNS_TTL,                                 /* 25 */
    DNS_ALIAS,                               /* 26 */
    DNS_STOP_SEARCH,                         /* 27 */
    DNS_TRY_SERVER,                          /* 28 */
    DNS_NO_FIRST,                            /* 29 */

    /* error code */
    DNS_NULL_POINTER,                        /* 30, ��ָ�����. */
    DNS_ERR_WAITLIST,                        /* 31, ��waitlist register/unregister����ʧ��*/
    DNS_ERR_SETWAITLIST,                     /* 32, ��waitlist SET����ʧ��*/
    DNS_ERR_GETWAITLIST,                     /* 33, ��waitlist GET����ʧ��*/
    DNS_LEN_DOMAIN_NAME,                     /* 34��������Ч,��������*/
    DNS_LEN_INTF_NAME,                       /* 35��IFNET���ֹ���*/
    DNS_ADD_IPV6_INTF_NAME,                  /* 36������ ipv6 Domain Setver��ַ���Ϸ�*/
    DNS_DEL_IPV6_INTF_NAME,                  /* 37��ɾ�� ipv6 Domain Setver��ַ���Ϸ�*/
    DNS_V6_TOO_MANY_SERVERS,                 /* 38��IPV6 ����������*/
    DNS_V4_TOO_MANY_SERVERS,                 /* 39��IPV4 ����������*/
    DNS_TOO_MANY_SERVERS_FORLINT,            /* 40��IPV4 ���������� for pclint*/
    DNS_DEL_V6_NO_DOMAIN_SERVER,             /* 41,  ɾ��V6 DOMAIN SEVER������*/
    DNS_V6_EXISTING_SERVER,                  /* 42,  ���V6����������.add by z62474 for A82D20453*/

    DNS_API_COM_NULL,                        /* 43, DNS���Ϊ��*/
    DNS_API_PARA_WRONG,                      /* 44, �����������*/
    DNS_API_POINTER_NULL,                    /* 45, ָ�����Ϊ��*/
    
    DNS_LEN_DOMAIN_LABEL,                    /* 46, ����Label���� */
    DNS_API_IPV6ADDR_WRONG = 47,             /* 47, ����IPv6��ַ����*/
    DNS_API_IPV4ADDR_WRONG,                  /* 48, ����IPv4��ַ����*/
};
/*ע��:����޸Ĵ����룬��ͬ���޸�dns_sh_info.c �ļ��е�CHAR *Inf_Dnsc_En[]������Ϣ*/

/* ����DNS server IP��ַ��ȡ��Ҫ�󶨵�ԴIP��ַ, server IP��ַ��ԴIP��ַ��Ϊ������ */
typedef ULONG (*DNSCGetSrcIPHOOK)(ULONG ulDnsServerIP);

/*******************************************************************************
*    Func Name: TCPIP_ClrDnsDynamicHost
*  Description: ���DNS������Ϣ
*        Input: ULONG ulProtocolFlag:AF_INET �� AF_INET6
*       Output: ��
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrDnsDynamicHost(ULONG ulProtocolFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetDnsDomainList
*  Description: ��ȡDNS�����б���Ϣ
*        Input: TCPIP_DomainInfo_S *pstTcpipDomainInfo:DNS�����б���Ϣָ��
*       Output: ��
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDnsDomainList(TCPIP_DomainInfo_S *pstDomainInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetDnsHost
*  Description: ��ȡDNS�����������IP��ַ��Ϣ
*        Input: CHAR *pcDNSName:DNS����
*               ULONG ulIPV6Flag:IPV6���,0��ʾIPV4,��0��ʾIPV6
*       Output: VOID *pulIPAddr:�������IP��ַ,IPV4ʱ����ULONG *����,IPV6ʱΪCHAR ulIPAddr[46]����
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDnsHost(CHAR *pcDNSName, VOID *pulIPAddr, ULONG ulIPV6Flag);
/*******************************************************************************
*    Func Name: TCPIP_GetDnsServer
*  Description: ��ȡDNS�����������б�
*        Input: TCPIP_DomainInfo_S * pstTcpipDomainInfo:DNS������������Ϣָ��
*       Output: ��
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDnsServer(TCPIP_DomainInfo_S * pstDomainInfo);
/*******************************************************************************
*    Func Name: TCPIP_SetDnsDomainSuffix
*  Description: ����DNS����ǰ׺��Ϣ
*        Input: ULONG ulNoFlag:0Ϊ����������׺����0Ϊɾ��������׺
*               CHAR  *pstDomainName:Ԥ��ӻ�ɾ����������׺
*               ULONG ulDomainNameFlag:���ulNoFlag��0��ulDomainNameFlagΪ0����ɾ������������׺
*       Output: ��
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDnsDomainSuffix(ULONG ulNoFlag, 
                                      CHAR  *pstDomainName, 
                                      ULONG ulDomainNameFlag);
/*******************************************************************************
*    Func Name: TCPIP_SetDnsServer
*  Description: ����DNS����������
*        Input: ULONG ulOpMode:
*               ����ģʽ:0��ʾ����ָ��������������ַ;
*                        1��ʾɾ��ָ��������������ַ;
*                        2��ʾɾ��ȫ��������������ַ.
*               CHAR *pstServerIP:��������ַ
*               ULONG ulIPV6Flag:IPV6���,0��ʾIPV4,��0��ʾIPV6
*       Output: ��
*       Return: �ɹ����� DNSC_SUCCESS,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDnsServer(ULONG ulOpMode, CHAR *pstServerIP, ULONG ulIPV6Flag);
/*******************************************************************************
*    Func Name: TCPIP_ShowDnsInfo
*  Description: ��ʾDNSģ��������������Ϣ
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDnsInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetDNSDebugSwitch
*  Description: ���õ��Կ���
*        Input: ulswitch: 0 ��  1 �ر�
*       Output: NA
*       Return: VOS_OK �ɹ�  ���� ʧ��
*      Caution: NA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME              DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-04-10  wuhailan           Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDNSDebugSwitch(ULONG ulswitch);
/*******************************************************************************
*    Func Name: TCPIP_GetDNSDebugSwitch
*  Description: ���õ��Կ���
*        Input: NA
*       Output: pulswitch: ���Կ���
*       Return: VOS_OK �ɹ�  ���� ʧ��
*      Caution: NA
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME              DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-04-10  wuhailan           Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDNSDebugSwitch(ULONG *pulswitch);

/*******************************************************************************
*    Func Name: TCPIP_SetDnsTos
*  Description: ����dnsģ���tosֵ
*        Input: UCHAR ucTos: Ҫ���õ�tosֵ��ֵ����Ч
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDnsTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetDnsTos
*  Description: ��ȡdnsģ���tosֵ
*        Input: UCHAR *pucTos: �������tosֵ
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDnsTos(UCHAR *pucTos);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDNSCGetSrcIPHook
* Date Created: 2008-10-04
*       Author: z43740
*  Description: ע�����DNS server��IP��ַ��ȡDNS�������������ĵ�Դ��ַ�Ļص�����
*        Input: DNSCGetSrcIPHOOK pfHook: �ص�����
*       Output: 
*       Return: VOS_OK                  ע��ɹ�
*               DNS_NULL_POINTER        �ص�����ָ��Ϊ��
*      Caution: �������Ҫ�ֶ�ָ��DNS�������������ĵ�Դ��ַ������0
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-04   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDNSCGetSrcIPHook(DNSCGetSrcIPHOOK pfHook);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _DNS_API_H_ */

