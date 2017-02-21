/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : skbuff.c
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2011��08��17��
  ����޸�   :
  ��������   :
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��08��17��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <linux/slab.h>
#include <linux/kmemcheck.h>
#include <linux/slab_def.h>
#include <linux/gfp.h>
#include "DrvInterface.h"
#include "PsLog.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
SK_BUFF_CLUSTER_CFG_INFO_STRU              g_astaCpuUserDataBlkClusterTableInfo[] =
{
    {SKB_DATA_ALIGN(1500)+sizeof(struct skb_shared_info), MAXUSERDATABLOCK},     /*�������*/
};
DATA_CLUSTER_STRU  stUserDataCluster;
DATA_CLUSTER_STRU  *g_pstUserDataCluster;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : __alloc_skb
 ��������  : allocate a network buffer
 �������  : unsigned int size,gfp_t gfp_mask,int fclone,int node
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : �޸�Linux�ں�
*****************************************************************************/
struct sk_buff *__alloc_skb(unsigned int size, gfp_t gfp_mask, int fclone, int node)
{
    struct kmem_cache *cache;
    struct skb_shared_info *shinfo;
    struct sk_buff *skb;
    u8 *data;

    /**/
    cache = fclone ? skbuff_fclone_cache : skbuff_head_cache;

    /* Get the HEAD */
    skb = kmem_cache_alloc_node(cache, gfp_mask & ~__GFP_DMA, node);
    if (!skb)
        goto out;
    prefetchw(skb);

    size = SKB_DATA_ALIGN(size);
    data = kmalloc_node_track_caller(size + sizeof(struct skb_shared_info),
            gfp_mask, node);
    if (!data)
        goto nodata;
    prefetchw(data + size);

    /*
     * Only clear those fields we need to clear, not those that we will
     * actually initialise below. Hence, don't put any more fields after
     * the tail pointer in struct sk_buff!
     */

    /*Linux add begin��caikai-191211 */
    skb->private_mem.enType     = DEFAULT_DEFINED;
    skb->private_mem.unRetaddr.pSkBuffAddr   = (VOS_VOID*)skb;
    /*0xFF????*/
    skb->private_mem.ucUserId               = INVALID_RABID_VALUE;
    /*Linux add end��caikai-191211*/

    memset(skb, 0, offsetof(struct sk_buff, tail));
    skb->truesize = size + sizeof(struct sk_buff);
    atomic_set(&skb->users, 1);
    skb->head = data;
    skb->data = data;
    skb_reset_tail_pointer(skb);
  	skb->end = skb->tail + size;
    kmemcheck_annotate_bitfield(skb, flags1);
    kmemcheck_annotate_bitfield(skb, flags2);
#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb->mac_header = ~0U;
#endif

    /* make sure we initialize shinfo sequentially */
    shinfo = skb_shinfo(skb);
    memset(shinfo, 0, offsetof(struct skb_shared_info, dataref));
    atomic_set(&shinfo->dataref, 1);

    if (fclone) {
        struct sk_buff *child = skb + 1;
        atomic_t *fclone_ref = (atomic_t *) (child + 1);

        kmemcheck_annotate_bitfield(child, flags1);
        kmemcheck_annotate_bitfield(child, flags2);
        skb->fclone = SKB_FCLONE_ORIG;
        atomic_set(fclone_ref, 1);

        child->fclone = SKB_FCLONE_UNAVAILABLE;
    }
out:
    return skb;
nodata:
    kmem_cache_free(cache, skb);
    skb = NULL;
    goto out;
}

/*****************************************************************************
 �� �� ��  :__alloc_skb_exp
 ��������  :allocate a network buffer(Type����ΪUSER_DEFINED)
 �������  :unsigned int size,gfp_t gfp_mask,int fclone,int node
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
struct sk_buff *__alloc_skb_exp(unsigned int size, gfp_t gfp_mask,
                int fclone, int node)
{
    struct kmem_cache *cache;
    struct skb_shared_info *shinfo;
    struct sk_buff *skb;
    u8 *data;

    cache = fclone ? skbuff_fclone_cache : skbuff_head_cache;

    /* Get the HEAD */
    skb = kmem_cache_alloc_node(cache, gfp_mask & ~__GFP_DMA, node);
    if (!skb)
        goto out;
    prefetchw(skb);

    size = SKB_DATA_ALIGN(size);

    /*
     * Only clear those fields we need to clear, not those that we will
     * actually initialise below. Hence, don't put any more fields after
     * the tail pointer in struct sk_buff!
     */

    /* Linux BEGIN */
    data   = SkBuffGetUserDataBlk(size + sizeof(struct skb_shared_info));
    if(!data)
    {
        goto nodata;
    }

    /* �ҽӴ��û���������õ����ݿ� */
    prefetchw(data + size);

    /* ===========��ֵ˽�нṹ============ */
    /* ���ݿ������û��� */
    skb->private_mem.enType =  USER_DEFINED;
    /* ���ص�ַָ�����ݿ� */
    skb->private_mem.unRetaddr.pDataAddr = (VOS_VOID*)data;

    skb->private_mem.ucUserId            = INVALID_RABID_VALUE;

    memset(skb, 0, offsetof(struct sk_buff, tail));
    skb->truesize   = size + sizeof(struct sk_buff);
    atomic_set(&skb->users, 1);
    skb->head       = data;
    skb->data       = data;
    skb_reset_tail_pointer(skb);
    skb->end        = skb->tail + size;
    kmemcheck_annotate_bitfield(skb, flags1);
    kmemcheck_annotate_bitfield(skb, flags2);
#ifdef NET_SKBUFF_DATA_USES_OFFSET
skb->mac_header = ~0U;
#endif

    /* make sure we initialize shinfo sequentially */
    shinfo = skb_shinfo(skb);
    memset(shinfo, 0, offsetof(struct skb_shared_info, dataref));
    atomic_set(&shinfo->dataref, 1);

    if (fclone) {
    struct sk_buff *child = skb + 1;
    atomic_t *fclone_ref = (atomic_t *) (child + 1);

    kmemcheck_annotate_bitfield(child, flags1);
    kmemcheck_annotate_bitfield(child, flags2);
    skb->fclone = SKB_FCLONE_ORIG;
    atomic_set(fclone_ref, 1);

    child->fclone = SKB_FCLONE_UNAVAILABLE;
}

    /* Linux END */
out:
    return skb;
nodata:
    kmem_cache_free(cache, skb);
    skb = NULL;
    goto out;
}

/*****************************************************************************
 �� �� ��  :alloc_skb_exp
 ��������  :allocate a network buffer(Type����ΪUSER_DEFINED)
 �������  :unsigned int size,gfp_t priority
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
static inline struct sk_buff*alloc_skb_exp(unsigned int size,gfp_t priority)
{
    return __alloc_skb_exp(size,priority,0,-1);
}

/*****************************************************************************
 �� �� ��  :__dev_alloc_skb_exp
 ��������  :allocate an skbuff for receiving(Type����ΪUSER_DEFINED)
 �������  :unsigned int length,gfp_t gfp_mask
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
static inline struct sk_buff*__dev_alloc_skb_exp(unsigned int len,gfp_t gfp_mask)
{
#ifdef WIFI_USED
    /*Ԥ��WIFIͷ����β��*/
    struct sk_buff *skb= alloc_skb_exp(len + WIFI_SKB_PAD + NET_SKB_PAD,gfp_mask);
    if (likely(skb))
    {
        skb_reserve(skb,WIFI_SKB_PAD/2 + NET_SKB_PAD);
    }
    return skb;
#else
    struct sk_buff *skb= alloc_skb_exp(len + NET_SKB_PAD,gfp_mask);
    if (likely(skb))
    {
        skb_reserve(skb,NET_SKB_PAD);
    }
    return skb;

#endif
}

/*****************************************************************************
 �� �� ��  :dev_alloc_skb_exp
 ��������  :allocate an skbuff for receiving(Type����ΪUSER_DEFINED)
 �������  :unsigned int length
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
inline struct sk_buff *dev_alloc_skb_exp(unsigned int len)
{
    return __dev_alloc_skb_exp(len,GFP_ATOMIC);
}

/*****************************************************************************
 �� �� ��  :__alloc_skb_exp
 ��������  :allocate a network buffer(Type����ΪEXT_DEFINED)
 �������  :unsigned char *pData,unsigned int size,gfp_t gfp_mask,int fclone,int node
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
  1.��    ��   : 2011��8��20��
    ��    ��   : yinweidong
    �޸�����   : Modified


*****************************************************************************/
struct sk_buff *__alloc_skb_ext( IMC_DATA_STRU *pImcData,int len,gfp_t gfp_mask,
                int fclone, int node)
{
    unsigned int size;
    struct kmem_cache *cache;
    struct skb_shared_info *shinfo;
    struct sk_buff *skb;
    u8 *data;

    cache = fclone ? skbuff_fclone_cache : skbuff_head_cache;

    /* Get the HEAD */
    skb = kmem_cache_alloc_node(cache, gfp_mask & ~__GFP_DMA, node);
    if (!skb)
        goto out;
    prefetchw(skb);
    size = SKB_DATA_ALIGN(pImcData->usDataLen + len);
    /* Linux BEGIN */

    /*
     * Only clear those fields we need to clear, not those that we will
     * actually initialise below. Hence, don't put any more fields after
     * the tail pointer in struct sk_buff!
     */


    /* ===============�ҽ��ⲿ���ݿ�========================*/
    data                                = pImcData->pDataAddr;
    if (!data)
        goto nodata;
//  data                                = DRV_PHY_TO_VIRT(data);

    prefetchw(data + size);
    skb->private_mem.enType             = EXT_DEFINED;

    memset(skb, 0, offsetof(struct sk_buff, tail));
    skb->truesize                       = size + sizeof(struct sk_buff);
    atomic_set(&skb->users, 1);

    /* head��data��ָ��CCPU�ṩ�������׵�ַ */
    skb->head                           = data;
    skb->data                           = data;
    skb_reset_tail_pointer(skb);
    skb->end                            = skb->tail + size;
    kmemcheck_annotate_bitfield(skb, flags1);
    kmemcheck_annotate_bitfield(skb, flags2);
#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb->mac_header                     = ~0U;
#endif

    /* make sure we initialize shinfo sequentially */
    shinfo                              = skb_shinfo(skb);
    memset(shinfo, 0, offsetof(struct skb_shared_info, dataref));
    atomic_set(&shinfo->dataref, 1);

    if (fclone) {
        struct sk_buff *child = skb + 1;
        atomic_t *fclone_ref = (atomic_t *) (child + 1);

        kmemcheck_annotate_bitfield(child, flags1);
        kmemcheck_annotate_bitfield(child, flags2);
        skb->fclone = SKB_FCLONE_ORIG;
        atomic_set(fclone_ref, 1);

        child->fclone = SKB_FCLONE_UNAVAILABLE;
    }
out:
    return skb;
nodata:
    kmem_cache_free(cache, skb);
    skb = NULL;
    goto out;
}

/*****************************************************************************
 �� �� ��  :alloc_skb_exp
 ��������  :allocate a network buffer(Type����ΪEXT_DEFINED)
 �������  :unsigned char *pData,unsigned int size,gfp_t priority
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
static inline struct sk_buff*alloc_skb_ext(IMC_DATA_STRU *pImcData,int len,gfp_t priority)
{
    return __alloc_skb_ext(pImcData,len,priority,0,-1);
}

/*****************************************************************************
 �� �� ��  :__dev_alloc_skb_exp
 ��������  :allocate an skbuff for receiving(Type����ΪEXT_DEFINED)
 �������  :unsigned char *pData,unsigned int length,gfp_t gfp_mask
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
static inline struct sk_buff*__dev_alloc_skb_ext(IMC_DATA_STRU *pImcData,gfp_t gfp_mask)
{
#ifdef WIFI_USED
    struct sk_buff *skb= alloc_skb_ext(pImcData,WIFI_SKB_PAD+NET_SKB_PAD, gfp_mask);
    if (likely(skb))
    {
        skb_reserve(skb,WIFI_SKB_PAD/2 + NET_SKB_PAD);
    }
#else
    struct sk_buff *skb= alloc_skb_ext(pImcData,NET_SKB_PAD,gfp_mask);
    if (likely(skb))
    {
        skb_reserve(skb,NET_SKB_PAD);
    }
#endif
    return skb;
}

/*****************************************************************************
 �� �� ��  :dev_alloc_skb_ext
 ��������  :allocate an skbuff for receiving(Type����ΪEXT_DEFINED)
 �������  :unsigned char *pData,unsigned int length
 �������  : ��
 �� �� ֵ  : sk_buff*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
inline struct sk_buff *dev_alloc_skb_ext(IMC_DATA_STRU *pImcData)
{
    return __dev_alloc_skb_ext(pImcData,GFP_ATOMIC);
}

/*****************************************************************************
 �� �� ��  : SkBuffUserDataBlkInit
 ��������  : SkBuffUserDataBlk�ܳ�ʼ������
 �������  : VOS_UINT8 **ppucDataMemAddr
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��12��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/

/*����4M�ڴ���λ���????*/
VOS_UINT32 SkBuffUserDataBlkInit(VOS_UINT8 **ppucDataMemAddr)
{
    VOS_UINT32                          ulSkbuffCnt;

    g_pstUserDataCluster              = &stUserDataCluster;
    stUserDataCluster.apstFreeStack   = ppucDataMemAddr;
    stUserDataCluster.usFreeCnt       = g_astaCpuUserDataBlkClusterTableInfo[0].usCnt;
    stUserDataCluster.usTotalCnt      = g_astaCpuUserDataBlkClusterTableInfo[0].usCnt;
    stUserDataCluster.usLen           = g_astaCpuUserDataBlkClusterTableInfo[0].usSize ;

    for ( ulSkbuffCnt = 0; ulSkbuffCnt < g_astaCpuUserDataBlkClusterTableInfo[0].usCnt; ulSkbuffCnt++ )
    {
       stUserDataCluster.UsrDataAddr[ulSkbuffCnt] = (VOS_UINT8*)SKB_DATA_ALIGN((VOS_UINT32)*ppucDataMemAddr);
       *ppucDataMemAddr                           = g_astaCpuUserDataBlkClusterTableInfo[0].usSize + stUserDataCluster.UsrDataAddr[ulSkbuffCnt] ;
    }
    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : SkBuffGetUserDataBlk
 ��������  : ���û�������������ݿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��12��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID *SkBuffGetUserDataBlk(VOS_INT32 lLen)
{
    VOS_VOID                           *pMem;
    DATA_CLUSTER_STRU                  *pstUserDataCluster;
    VOS_INT32                           lLockKey;

    pstUserDataCluster          = g_pstUserDataCluster;

    if ( pstUserDataCluster->usLen  < lLen )
    {
        return VOS_NULL_PTR;
    }

    lLockKey = VOS_SplIMP();
    if ( 0 != pstUserDataCluster->usFreeCnt )
    {
        pMem    = (VOS_VOID*)pstUserDataCluster->apstFreeStack[--pstUserDataCluster->usFreeCnt];
    }
    else
    {
        pMem = VOS_NULL_PTR;
    }
    VOS_Splx(lLockKey);
    return pMem;
}

/*****************************************************************************
 �� �� ��  : SkBuffRelUserDataBlk
 ��������  : ���ݿ�Ż��û�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��12��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID SkBuffRelUserDataBlk(VOS_VOID *pMem)
{
    VOS_INT32       lLockKey;
    DATA_CLUSTER_STRU                  *pstUserDataCluster;
    if( !pMem )
    {
        PS_LOG(UEPS_PID_RNIC, 0, PS_PRINT_WARNING,
                "sk_buff, SkBuffRelUserDataBlk : ERROR : pMem is NULL!" );
        return;
    }
    pstUserDataCluster          = g_pstUserDataCluster;
    lLockKey = VOS_SplIMP();

    pstUserDataCluster->apstFreeStack[pstUserDataCluster->usFreeCnt]  = (VOS_UINT8*)pMem;
    pstUserDataCluster->usFreeCnt++;
    VOS_Splx(lLockKey);
    return;
}

/*****************************************************************************
 �� �� ��  : skb_release_data
 ��������  : Free an sk_buff. Release anything attached to the buffer.
 �������  : struct sk_buff *skb
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��9��
    ��    ��   : ������
    �޸�����   : �޸�
*****************************************************************************/
static void skb_release_data(struct sk_buff *skb)
{
    if (!skb->cloned ||
        !atomic_sub_return(skb->nohdr ? (1 << SKB_DATAREF_SHIFT) + 1 : 1,
                   &skb_shinfo(skb)->dataref)) {
        if (skb_shinfo(skb)->nr_frags) {
            int i;
            for (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
                put_page(skb_shinfo(skb)->frags[i].page);
        }

        if (skb_has_frags(skb))
            skb_drop_fraglist(skb);

        /*Linux modified begin��yinweidong-171741*/
        if (skb->private_mem.enType == USER_DEFINED)
        {
            /* �ͷ��û����ݿ� */
            SkBuffRelUserDataBlk(skb->private_mem.unRetaddr.pDataAddr);
        }
        else if (skb->private_mem.enType == DEFAULT_DEFINED)
        {
            kfree(skb->head);
        }
        else
        {
            IMC_RemoteFreeTtfMem(skb->private_mem.unRetaddr.pTtfMemAddr);
        }
        /*Linux modified end��yinweidong-171741*/
    }
}

/*****************************************************************************
 �� �� ��  :skb_insert_head
 ��������  :queue a buffer at the list head
 �������  :struct sk_buff_head *list, struct sk_buff *newsk
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
void skb_insert_head(struct sk_buff_head *list, struct sk_buff *newsk)
{
    VOS_INT32                           lLockKey;
    lLockKey        = VOS_SplIMP();
    __skb_queue_head(list, newsk);
    VOS_Splx(lLockKey);
}

/*****************************************************************************
 �� �� ��  :skb_insert_tail
 ��������  :queue a buffer at the list tail
 �������  :struct sk_buff_head *list, struct sk_buff *newsk
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
void skb_insert_tail(struct sk_buff_head *list, struct sk_buff *newsk)
{
    VOS_INT32                           lLockKey;
    lLockKey    = VOS_SplIMP();
    __skb_queue_tail(list, newsk);
    VOS_Splx(lLockKey);
}

/*****************************************************************************
 �� �� ��  :skb_remove
 ��������  :Remove the head of the list.
 �������  :struct sk_buff_head *list
 �������  : ��
 �� �� ֵ  : sk_buff *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
struct sk_buff *skb_remove(struct sk_buff_head *list)
{
    struct sk_buff                     *result;
    VOS_INT32                           lLockKey;
    lLockKey    = VOS_SplIMP();
    result      = __skb_dequeue(list);
    VOS_Splx(lLockKey);
    return result;
}

/*****************************************************************************
 �� �� ��  :skb_remove_tail
 ��������  :Remove the tail of the list.
 �������  :struct sk_buff_head *list
 �������  : ��
 �� �� ֵ  : sk_buff *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
struct sk_buff *skb_remove_tail(struct sk_buff_head *list)
{
    struct sk_buff                     *result;
    VOS_INT32                           lLockKey;
    lLockKey    = VOS_SplIMP();
    result      = __skb_dequeue_tail(list);
    VOS_Splx(lLockKey);
    return result;
}

/*****************************************************************************
 �� �� ��  :skb_copy_exp
 ��������  :create private copy of an sk_buff
 �������  :const struct sk_buff *skb, gfp_t gfp_mask
 �������  : ��
 �� �� ֵ  : sk_buff *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��16��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
struct sk_buff *skb_copy_exp(const struct sk_buff *skb, gfp_t gfp_mask)
{
    int headerlen = skb->data - skb->head;
    /*
    Allocate the copy buffer
    */
    struct sk_buff *n;
#ifdef NET_SKBUFF_DATA_USES_OFFSET
    n = alloc_skb_exp(skb->end + skb->data_len, gfp_mask);
#else
    n = alloc_skb_exp(skb->end - skb->head + skb->data_len, gfp_mask);
#endif
    if (!n)
        return NULL;

    /* Set the data pointer */
    skb_reserve(n, headerlen);
    /* Set the tail pointer and length */
    skb_put(n, skb->len);

    if (skb_copy_bits(skb, -headerlen, n->head, headerlen + skb->len))
        BUG();

    copy_skb_header(n, skb);
    return n;
}


char *skb_put(struct sk_buff *skb, unsigned int len)
{
    unsigned char *tmp = skb_tail_pointer(skb);

    skb->tail += len;
    skb->len  += len;

    return tmp;
}

unsigned char *skb_tail_pointer(const struct sk_buff *skb)
{
    return skb->tail;
}

char *skb_put_debug(unsigned long ulFileID, unsigned long ulLineNum,
                           struct sk_buff *skb, unsigned int len)
{
    unsigned char *tmp = skb_tail_pointer(skb);

    skb->tail += len;
    skb->len  += len;

    return tmp;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

