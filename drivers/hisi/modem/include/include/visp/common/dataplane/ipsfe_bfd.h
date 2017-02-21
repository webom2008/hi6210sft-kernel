/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_bfd.h
*
*  Project Code: V1.1.0
*   Module Name: BFD
*  Date Created: 2009-9-2
*        Author: w60786
*   Description: BFDģ��������Ϳ����湲�õĽṹ,��ȶ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-2     w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_BFD_H_
#define _IPSFE_BFD_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/* BFD�Ự���ò��� */
typedef struct tagSFE_BFD_PARA
{
    UINT32 u32VrfIndex;                  /* �Ự���ڵ�VRF */
    UINT32 u32SessionId;                 /* BFD�ỰID */
    UINT32 u32DetectMode;                /* ʵ�ʵļ��ģʽ */
    UINT32 u32TxInterval;                /* ����ʵ�ʵķ���ʱ����,ms */
    UINT32 u32DetectInterval;            /* ����ʵ�ʵļ����,ms */
    UINT32 u32DetectMult;                /* ����ʵ�ʵļ�ⱶ�� */
    UINT32 u32MyDiscriminator;           /* ���˱�ʶ�� */
    UINT32 u32YourDiscriminator;         /* �Զ˱�ʶ�� */
    UINT32 u32IpVer;                     /* IP�汾��ʶ:0--��ʾ��IPv4 BFD;1--��ʾ��IPv6 BFD */
    SFE_IPADDR_UN unDstIPAddr;           /* �Զ�IP��ַ,������ */
    SFE_IPADDR_UN unSrcIPAddr;           /* ����IP��ַ,������ */
    UINT32 u32TTL;                       /* TTL */
    UINT32 u32DstUdpPort;                /* UDPĿ�Ķ˿ں�,����Ϊ3784,����Ϊ4784,������ */
    UINT32 u32SrcUdpPort;                /* UDPԴ�˿ں�,ֵΪ49151+X(X>0),������ */
    UINT32 u32Tos;                       /* TOSֵ */
    UINT32 u32IsMultiHop;                /* BFD�����Ự��־,Ҫ���ڿ�������ݽӿ�����ת���� */
    SFE_IFID stSendIfID;                 /* �Ự�ĳ��ӿ���Ϣ,����ʱ��Ч,����ʱ��Ч */

    INT8 szCtlPkt[SFE_BFD_LEN_AUTH_NONE];/* �Ự��BFD���Ʊ���,������,ֵΪ�û�����ֵ */
}SFE_BFD_PARA_S;

/* BFD̽��DOWNʱ������֪ͨ���������Ϣ�ṹ */
typedef struct tagSFE_BFD_DETECTDOWN_PARA
{
    UINT32   u32VrfIndex;               /* BFD�Ự����VRF */
    UINT32   u32SessionId;              /* BFD�ỰID */
}SFE_BFD_DETECTDOWN_PARA_S;

/* ����BFD�Ự��Ϣ��ȡ�ؼ��� */
typedef struct tagSFE_BFD_KEY
{
    UINT32   u32VrfIndex;               /* BFD�Ự����VRF */
    UINT32   u32SessionId;              /* BFD�ỰID */
}SFE_BFD_KEY_S;

/* ����BFD�Ự�ĵ��Կ��� */
typedef struct tagSFE_BFD_DEBUGSWITCH
{
    UINT32 u32VrfIndex;                 /* BFD�Ự����VRF */
    UINT32 u32SessionId;                /* BFD�ỰID */
    UINT32 u32IsDebug;                  /* ���Կ���,1Ϊ��,0Ϊ�ر� */
    UINT32 u32Reserved;                 /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
}SFE_BFD_DEBUGSWITCH_S;

#ifdef  __cplusplus
}
#endif

#endif
