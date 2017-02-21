/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ext_com.h
*
*  Project Code: VISPV100R007
*   Module Name: BFD EXTERN
*  Date Created: 
*        Author: 
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME         DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-07-24   qinyun       Create
*  2008-11-03   Q62011       Add for BC3D00658, BFD_OSPF_RULE_TYPE_INTF,
*                            BFD_OSPF_RULE_TYPE_PROCת�Ƶ�apiͷ�ļ��й��û�ʹ��
*******************************************************************************/
#ifndef _BFD_EXT_COM_H_
#define _BFD_EXT_COM_H_

#ifdef __cplusplus
extern "C" {
#endif
/*************************************/
/*              �궨��               */
/*************************************/
#define SID_EXT_BFD_OSPF_RULE_S 1
#define SID_EXT_BFD_RTM_NODE_S  2

/*#define BFD_OSPF_MAX_BLOCK_NUM      32   */
/*#define BFD_OSPF_MAX_RULE_NUM       32   */
/*#define BFD_STATIC_MAX_RELATION_NUM 32   */
/*#define BFD_STATIC_ONE_SESS_MAX_NUM 1    */
#define BFD_OSPF_MAX_BLOCK_NUM      64
#define BFD_OSPF_MAX_RULE_NUM       64
#define BFD_STATIC_MAX_RELATION_NUM  5*1024
#define BFD_STATIC_ONE_SESS_MAX_NUM  5*1024

#define BFD_STATIC_DETECT_TIME_DEFAULT  10*1000
#define BFD_STATIC_DETECT_TIME_MAX      50*1000
#define BFD_STATIC_DETECT_MAX_SECS      50
#define BFD_STATIC_DETECT_MIN_SECS      1

/*��BFD_MAX_SESSION_ID����һ�£���BFDģ��ĻỰ�����������޸�����Ҫ��Ӧ�޸ı�ģ��Ĵ���*/
#define BFD_EXT_MIN_SESSION_ID             1          /* BFD��Сsession id*/
#define BFD_EXT_MAX_SESSION_ID          2000          /* BFD���session id*/

#define BFD_EXT_TRUE                       1
#define BFD_EXT_FALSE                      0

/*��־λ*/
#define BFD_EXT_YES     1
#define BFD_EXT_NO      0

typedef struct tagBFD_ADDR6_S
{
    ULONG     u6_uladdr[4];
}BFD_ADDR6_S;

#define HASH_BFD1(ulAddr) \
(((USHORT)((ULONG)(ulAddr)>>16)) ^ ((USHORT)(ulAddr)))

#define HASH_BFD2(pAddr6) \
     (HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[0]) ^ HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[1]) ^ \
      HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[2]) ^ HASH_BFD1(((BFD_ADDR6_S *)(pAddr6))->u6_uladdr[3]))

/*modify by q62011 for ospfv3 */
typedef enum tagBFD_EXT_TABLE_NUM_E
{
    BFD_EXT_TABLE_IPV4 = 0,
    BFD_EXT_TABLE_IPV6,
    BFD_EXT_TABLE_MAX_NUM
}BFD_EXT_TABLE_NUM;

/* End of Added by qinyun62011, 2011/2/9   ���ⵥ��:V2R3C03-ROTUE-MERGE */

typedef struct tagBFD_ENTRY_S
{
    struct tagBFD_ENTRY_S   *pstNextEntry;        
} BFD_ENTRY_S;

typedef struct tagBFD_STATIC_NODE_S
{
    struct tagBFD_STATIC_NODE_S   *pstNextNode;  
    struct tagBFD_STATIC_NODE_S   *pstPreNode;
    struct tagBFD_STATIC_NODE_S   *pstLeft; /* ������ */
    struct tagBFD_STATIC_NODE_S   *pstRight; /* ������ */    
    VOID   *pTable;        
    /* wangjiaqi modify for ipv6 bfd 20131125 begin */
    ULONG   ulDstIp[4]; 
    ULONG   ulPreLen; 
    ULONG   ulNextHop[4]; 
    /* wangjiaqi modify for ipv6 bfd end */
    ULONG   ulIfIndex; 
    ULONG   ulTimeId;  
    ULONG   ulVrfIndex; /* Vrf Index V4,V6���� */
    ULONG   ulIpVersion;/* ������V4����V6��HASH�ڵ� */
} BFD_STATIC_NODE_S ;

/*modify by q62011 for ospfv3 */
typedef struct tagBFD_OSPF_NODE_S
{
    struct tagBFD_OSPF_NODE_S   *pstNextNode;        
    VOID   *pTable;        
    ULONG   ulInstanceId;     /*OSPFV3��Ч*/      
    ULONG   ulRouterId;        /*�ھӵ�Route ID(������)*/      
    ULONG   ulIfIndex;            
    ULONG   ulProcId;           /*OSPF/OSPFV3ʵ����*/
} BFD_OSPF_NODE_S ;
/* End of Added by qinyun62011, 2011/2/9   ���ⵥ��:V2R3C03-ROTUE-MERGE */

typedef union unBFD_RELATION_PARA_U
{
    struct tagOSPFTbl
    {
        ULONG   ulNumber;       
        BFD_OSPF_NODE_S stNodeHd;
    }Bfd_For_Ospf;
    struct tagStaticTbl
    {
        ULONG   ulNumber;       
        ULONG   ulProcId;           /*RTMʵ����*/
        BFD_STATIC_NODE_S stNodeHd;
    }Bfd_For_Static;
}BFD_RELATION_PARA_U;

typedef struct tagBFD_RELATION_TABLE_S
{
    ULONG   ulProcType;         /*·��Э�����ͣ�֧��OSPF��RTM */
    ULONG   ulBfdSessId;        /*��Ӧ��BFD�Ự��������ʼ�����κ��������Ӧ������*/
    ULONG   ulNetworkType;       /*���ͣ�0-IPv4����,1-IPv6���� */
    BFD_RELATION_PARA_U  unRelationPara;
} BFD_RELATION_TABLE_S;


typedef struct tagBFD_RELATION_HASHTABLE_S
{
    struct tagBFD_STATIC_NODE_S   *pstLeft; /* ������ */
    struct tagBFD_STATIC_NODE_S   *pstRight; /* ������ */
}BFD_RELATION_HASHTABLE_S;

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
typedef struct tagBFD_VRFRELATION_TABLE_S
{
    ULONG ulVrfIndex;                              /* ��ӦVRF���� */
    /* �������BFD�ỰIDͨ��Ԥ��������,�����ֵ�ǿɱ��,Ϊ�˼��ٶ�ʹ�ûỰID����Ԥ�������ֵ��SGSN��Ʒ���ڴ�Ӱ��
       ���Բ��ö�̬�ڴ����뷽ʽ,������ʹ��ָ����������� */
    BFD_RELATION_TABLE_S **ppstBfdRelationTable;   /* �Ự������ */
}BFD_VRFRELATION_TABLE_S;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-12 */

typedef struct tagOspfMsg
{
    /*modify by q62011 for ospfv3 */
    /*ULONG ulRouterId;           OSPF·�ɱ�����ID
    ULONG ulIfIndex;            OSPF·�ɳ��ӿ�
    ULONG ulLocalIp;            ���˵�ַ
    ULONG ulPeerIp;             �Զ˵�ַ*/
    ULONG ulNbrKey;                /*OSPF�ھӲ��ҹؼ��֣�V2��Route ID��V3��Instace ID*/
    ULONG ulIfIndex;               /*OSPF·�ɳ��ӿ�*/
    ULONG ulLocalIp[LEN_4];        /*���˵�ַ*/
    ULONG ulPeerIp[LEN_4];         /*�Զ˵�ַ*/
    ULONG ulIpType;                /*��ַ���ͣ�BFD_OVER_IPV4(0)-IPv4��ַ,BFD_OVER_IPV6(1)-IPv6��ַ*/
    /* End of Added by qinyun62011, 2011/2/9   ���ⵥ��:V2R3C03-ROTUE-MERGE */
}BFD_TO_OSPF_MSG_S;/*��BFD_NTY_OSPF����һ��*/
typedef struct tagRtmMsg
{
    ULONG ulDstIp[LEN_4];       /*��̬·��Ŀ�ĵ�ַ*/
    ULONG ulPreLen;             /*��̬·�����볤��*/
    ULONG ulNextHop[LEN_4];     /*��̬·����һ��IP��ַ*/
    ULONG ulOutIndex;           /*��̬·�ɳ��ӿ�����*/
    ULONG ulIpType;             /*��ַ���ͣ�BFD_OVER_IPV4(0)-IPv4��ַ,BFD_OVER_IPV6(1)-IPv6��ַ*/
}BFD_TO_RTM_MSG_S;/*��BFD_TO_RTM_DATA����һ��*/

typedef ULONG(*BFD_IFNET_GET_INDEX_BY_NAME)( CHAR *pszIfName, ULONG *pulIfIndex);
typedef ULONG(*BFD_IFNET_GET_NAME_BY_INDEX)( ULONG ulIfIndex, CHAR *pszIfName);

extern ULONG Extern_BFD_Init(VOID);
extern ULONG Extern_BFD_RegStatNotifyHook( BFD_RM_NOTIFY_HOOK_FUNC pfStatNotifyFunc );
extern ULONG Extern_BFD_RegOspfAndRtmType( ULONG ulOspf, ULONG ulRtm );
extern ULONG Extern_BFD_NotifyHook(ULONG ulSessionID, ULONG ulState,ULONG ulDstIP, ULONG ulSrcIP, 
                                         ULONG ulInIfIndex, ULONG ulAppGroup);
extern ULONG Extern_BFD_NotifyVrfHook(BFD_NOTIFY_BYVRF_S *pstBfdNotifyByVrf);
extern ULONG Extern_BFD6_NotifyHook(BFD6_NOTIFY_S *pstBfdNotify);

extern ULONG Extern_BFD_SetDbgSwitch(ULONG ulNetworkType, ULONG ulSwitch);
extern ULONG Extern_BFD_CheckDbgSwitch(ULONG ulNetworkType, ULONG ulRelaType);
extern VOID Extern_BFD_RemoveEntry(BFD_ENTRY_S *pstPrevEntry,BFD_ENTRY_S *pstCurEntry);
extern VOID Extern_BFD_InsertEntry(BFD_ENTRY_S *pstCurEntry,BFD_ENTRY_S *pstNewEntry);
extern VOID Extern_BFD_StateNotify(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                                                        ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulNewSessionID);
extern CHAR* VOS_IpAddrToStr(ULONG ulAddr, CHAR * szStr);
extern LONG VOS_strcmp(const CHAR *,const CHAR *);
extern VOID* TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);
extern VOID BFD_Begin_PT();
extern VOID BFD_End_PT();

extern ULONG Extern_BFD6_HashFunc(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop, ULONG ulVrfIndex);
extern ULONG Extern_BFD_HashFunc(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop, ULONG ulVrfIndex);
extern VOID Extern_BFD_AddToHashRelation(BFD_RELATION_HASHTABLE_S * pstHashNode, BFD_STATIC_NODE_S *pstBfdStNode);
extern VOID Extern_BFD_DelFromHashRelation(BFD_RELATION_HASHTABLE_S * pstHashNode, BFD_STATIC_NODE_S *pstBfdStNode);
extern VOID Extern_BFD_DelFromRelationTable(BFD_STATIC_NODE_S *pstBfdStNode);
#ifdef __cplusplus
}
#endif

#endif


