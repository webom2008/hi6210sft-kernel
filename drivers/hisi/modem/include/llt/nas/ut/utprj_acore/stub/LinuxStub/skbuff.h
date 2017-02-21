/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Skbuff.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2011��8��12��
  ����޸�   :
  ��������   : Skbuff.c��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��8��8��
    ��    ��   : caikai
    �޸�����   : �����ļ�


******************************************************************************/

#ifndef __SKBUFF_H__
#define __SKBUFF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#ifdef __CHECK_ENDIAN__
#define __bitwise __bitwise__
#else
#define __bitwise
#endif

#ifdef __CHECKER__
#define __bitwise__ __attribute__((bitwise))
#else
#define __bitwise__
#endif


typedef unsigned __bitwise__ gfp_t;


#define INVALID_RABID_VALUE             (0xFF)
#define NET_SKB_PAD                     (64)
#define WIFI_SKB_PAD                    (256)
typedef void (*IMC_RemoteFreeTtfMemCB)(void *pucAddr);
typedef void (*SkBuffRelUserDataBlkCB)(void *pMem);
typedef void* (*SkBuffGetUserDataBlkCB)(unsigned long lLen);


typedef unsigned char U8;

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef unsigned long long  u64;
typedef signed int              int_t;
typedef unsigned int __u32;
typedef unsigned char __u8;
typedef unsigned short __u16;
typedef __u16 __bitwise __be16;


#ifdef NET_SKBUFF_DATA_USES_OFFSET
typedef unsigned int sk_buff_data_t;
#else
typedef unsigned char *sk_buff_data_t;
#endif


#define printk  vos_printf

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    DEFAULT_DEFINED = 0,        /* ���ݿ���Linuxϵͳ�ṩ*/
    USER_DEFINED,               /*���ݿ����û�������ڴ��ṩ*/
    EXT_DEFINED,                /*���ݿ����ⲿ�ṩ*/
} DATABLOCK_ENUM;

typedef unsigned char DATABLOCK_ENUM_UINT8;


enum MEM_TYPE_ENUM
{
    MEM_TYPE_SYS_DEFINED = 0,            /* ���ݿ���Linuxϵͳ�ṩ*/
    MEM_TYPE_USER_DEFINED,               /* ���ݿ����û�������ڴ��ṩ*/
    MEM_TYPE_BUTT
 } ;
typedef unsigned char MEM_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : SK_BUFF_PRIVATE_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    void                               *pMem;               /*����TTFMEM���׵�ַ����֪ͨc���ͷ�*/
    VOS_UINT16                          usApp;              /*�û�usApp*/
    DATABLOCK_ENUM_UINT8                enType;             /*���ݿ��ṩ��Դ*/
    VOS_UINT8                           ucTailPktInd;
}SK_BUFF_PRIVATE_ST;

#if 0
typedef struct {
    int counter;
} atomic_t;
#endif

/* Linux���ڴ����ṹ */
struct sk_buff_head {
    /* These two members must be first. */
    struct sk_buff  *next;
    struct sk_buff  *prev;
    __u32       qlen;
};

#if ( FEATURE_ON == FEATURE_SKB_EXP )
typedef struct sk_buff_head IMM_ZC_HEAD_STRU;
#endif

union ktime
{
    signed long long 	tv64;

};
typedef union ktime ktime_t;		/* Kill this */
/*****************************************************************************
 �ṹ��    : SK_BUFF
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
struct sk_buff {
    /* These two members must be first. */
    struct sk_buff      *next;
    struct sk_buff      *prev;

    ktime_t			tstamp;

    struct net_device   *dev;
    int         iif;
    /* 4 byte hole on 64 bit*/



    char        cb[48];

    unsigned int    len,
                    data_len,
                    mac_len;

    __u32           priority;
        __u8            local_df:1,
                    cloned:1,
                    ip_summed:2,
                    nohdr:1,
                    nfctinfo:3;
        __u8            pkt_type:3,
                    fclone:2,
                    ipvs_property:1;







    __be16          protocol;
    sk_buff_data_t      transport_header;
    sk_buff_data_t      network_header;
    sk_buff_data_t      mac_header;
    /* These elements must be at the end, see alloc_skb() for details.  */
    sk_buff_data_t      tail;
    sk_buff_data_t      end;
    unsigned char       *head,
                        *data;
    unsigned int        truesize;
    atomic_t        users;
    SK_BUFF_PRIVATE_ST private_mem;             /*������private�� */
};
#if ( FEATURE_ON == FEATURE_SKB_EXP )
typedef struct sk_buff IMM_ZC_STRU;
#endif

#if 0
/*****************************************************************************
 �ṹ��    : DATA_CLUSTER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /*��������sk_buff�ֽڸ���*/
    VOS_UINT16                          usTotalCnt;
    VOS_UINT16                          usFreeCnt;

    /*�����ڴ�����ݳ���*/
    VOS_UINT16                          usLen;

    VOS_UINT8                           aucRsv[2];

    /*��¼�����ڴ��������ջ��Ԫ�� */
    VOS_UINT8                        **apstFreeStack;
    VOS_UINT8                        *UsrDataAddr[MAXUSERDATABLOCK];
}DATA_CLUSTER_STRU;
#endif

/* sk_buffÿ����������Ϣ*/
typedef struct
{
    VOS_UINT16                          usSize;    /* �������Ĵ�С */
    VOS_UINT16                          usCnt;     /* �������� */
}SK_BUFF_CLUSTER_CFG_INFO_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern struct sk_buff *__alloc_skb(unsigned int size, gfp_t gfp_mask, int fclone, int node);
extern struct sk_buff *dev_alloc_skb(unsigned int length);
extern struct sk_buff *dev_alloc_skb_exp(unsigned int len);
extern void skb_insert_head(struct sk_buff_head *list, struct sk_buff *newsk);
extern void skb_insert_tail(struct sk_buff_head *list, struct sk_buff *newsk);
extern struct sk_buff *skb_remove(struct sk_buff_head *list);
extern struct sk_buff *skb_remove_tail(struct sk_buff_head *list);
extern void SkBuffRegRelUserDataBlkFunc(SkBuffRelUserDataBlkCB RelUserDataBlkFunc);
extern void SkBuffRegGetUserDataBlkFunc(SkBuffGetUserDataBlkCB GetUserDataBlkFunc);
extern void SkBuffRegTtfMemFreeFunc(IMC_RemoteFreeTtfMemCB ImcRemoteFreeFunc);
extern unsigned int DRV_WifiDataReservedTail(unsigned int len);
extern struct sk_buff *dev_alloc_skb_exp_debug(unsigned short usFileID, unsigned short usLineNum,
                        unsigned int ulLen);

extern struct sk_buff *dev_alloc_skb_exp(unsigned int len);

extern struct sk_buff *dev_alloc_skb_ext(unsigned int len, unsigned char* pData, unsigned int HeadReserveLen,unsigned int TailReserveLen);

extern  struct sk_buff *skb_copy_exp(const struct sk_buff *skb);

extern void kfree_skb(struct sk_buff *skb);

extern void kfree_skb_head(struct sk_buff *skb);


extern unsigned char *skb_push(struct sk_buff *skb, unsigned int len);

extern unsigned char *skb_pull(struct sk_buff *skb, unsigned int len);

extern unsigned char *skb_put(struct sk_buff *skb, unsigned int len);

extern void skb_reserve(struct sk_buff *skb, int len);

extern unsigned int skb_headroom(const struct sk_buff *skb);

extern int skb_tailroom(const struct sk_buff *skb);

extern int skb_is_nonlinear(const struct sk_buff *skb);

extern __u32 skb_queue_len(const struct sk_buff_head *list_);

extern void skb_queue_head_init(struct sk_buff_head *list);

extern  void skb_queue_head(struct sk_buff_head *list, struct sk_buff *newsk);
extern void skb_queue_tail(struct sk_buff_head *list, struct sk_buff *newsk);

extern struct sk_buff *skb_dequeue_tail(struct sk_buff_head *list);

extern struct sk_buff *skb_dequeue(struct sk_buff_head *list);
extern char *skb_put_debug(unsigned short usFileID, unsigned short usLineNum,
                           struct sk_buff *skb, unsigned int len);

extern __u32 skb_queue_len_debug(unsigned short usFileID, unsigned short usLineNum, const struct sk_buff_head *list_);

extern void skb_queue_tail_debug(unsigned short usFileID, unsigned short usLineNum,
                                  struct sk_buff_head *list, struct sk_buff *newsk);

extern void skb_queue_head_init_debug(unsigned short usFileID, unsigned short usLineNum, struct sk_buff_head *list);

extern struct sk_buff *skb_dequeue_tail_debug(unsigned short usFileID, unsigned short usLineNum, struct sk_buff_head *list);

extern struct sk_buff *skb_dequeue_debug(unsigned short usFileID, unsigned short usLineNum, struct sk_buff_head *list);


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

#endif /* end of Adapter.h */





