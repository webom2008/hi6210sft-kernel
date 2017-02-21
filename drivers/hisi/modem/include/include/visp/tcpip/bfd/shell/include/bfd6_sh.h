typedef struct tagBFD_NEGOFAIL_S
{
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4]; 
    ULONG ulPeerAddr[4]; 
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1]; 
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulProtocol;      /* IPv6/IPv4标识:0-IPv4,1-IPv6 */
}BFD_NEGOFAIL_S;

/* Bfd6 全局socket结构 */
typedef struct tagBFD6_SOCK_INFO_S
{
    LONG lMutiRcv;    /* 多跳接收 */
    LONG lOneRcv;     /* 单跳接收 */
    LONG lSnd;        /* 报文发送 */
}BFD6_SOCK_INFO_S;

/* 关闭socket */
#define BFD6_CLOSE_SOCKET(lSocktId)\
{\
    if (-1 != lSocktId)\
    {\
        (VOID)close(lSocktId);\
        lSocktId = -1;\
    }\
}


ULONG BFD6_GetVrfIndexByName(CHAR *pszVrfName,ULONG *pulVrfIndex);

ULONG BFD6_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);

CHAR * BFD6_Inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);

ULONG BFD6_Shell_Init();

ULONG BFD6_Shell_Send (UCHAR* pIpPacket, BFD_PKTINFO_S * pstSndPktInfo);
ULONG BFD6_Shell_Init_Socket();
VOID BFD6_Shell_Close_GlobalSocket();

extern ULONG g_ulBfd6EnableFlag;
/* wangjiaqi modify for ipv6 bfd 20131125 begin */
/*******************************************************************************
*    Func Name: BFD6_GetRtmInstByIndex
* Date Created: 2013-11-25
*       Author: Wangchengyang
*  Description: 通过VRF ID获取路由管理实例号
*        Input: ulVrfIndex :VRF ID
*       Output: pulInst:实例号
*       Return: NA
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetRtmInstByIndex(ULONG ulVrfIndex,ULONG *pulInst);

/*******************************************************************************
*    Func Name: BFD6_GetVrfIndexByIfIndex
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: 通过接口索引获取其VRF6 索引
*        Input: ulIfIndex  :接口索引
*       Output: pulVrfIndex:VRF 索引
*       Return: NA
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetVrfIndexByIfIndex(ULONG ulIfIndex,ULONG *pulVrfIndex);
/* wangjiaqi modify for ipv6 bfd end */

