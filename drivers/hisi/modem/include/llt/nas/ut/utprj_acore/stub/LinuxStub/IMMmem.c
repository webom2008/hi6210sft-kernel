

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
//#include <linux/module.h>
#include "IMMmem.h"
#include "skbuff.h"
//#include <linux/interrupt.h>
#include "TtfMemoryMap.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define    NULL								(0)

/* UT ��׮ begin */
#define panic							printf
#define local_irq_save(flags)	do { ; } while(0)
#define local_irq_restore(flags)	do { ; } while(0)
/* UT ��׮ end */

/* IMM MEM �����ڴ�ص�λ���ƽṹ */
const IMM_MEM_CLUSTER_CFG_INFO_STRU              g_astImmMemSharePoolClusterTableInfo[] =
{
    {864,                               1280},
    {1952,                              1855}
};

#if 0

#define FEATURE_RATE_84                 1

#define FEATURE_RATE_42                 0

#define FEATURE_RATE_28                 0


#if ( FEATURE_RATE_84 )  /* ���� 84 M */
const IMM_MEM_CLUSTER_CFG_INFO_STRU g_astImmMemCtrlPoolClusterTableInfo[] =
    {
        {0,                              835}
    };
#elif ( FEATURE_RATE_42 ) /* ���� 42 M */
const IMM_MEM_CLUSTER_CFG_INFO_STRU g_astImmMemCtrlPoolClusterTableInfo[] =
    {
        {0,                              418}
    };
#elif ( FEATURE_RATE_28 )  /* ���� 28 M */
const IMM_MEM_CLUSTER_CFG_INFO_STRU g_astImmMemCtrlPoolClusterTableInfo[] =
    {
        {0,                              300}
    };
#endif
#endif

const IMM_MEM_CLUSTER_CFG_INFO_STRU g_astImmMemCtrlPoolClusterTableInfo[] =
    {
        {0,                              IMM_MEM_CTRL_MEM_CNT}
    };
EXPORT_SYMBOL(g_astImmMemCtrlPoolClusterTableInfo);


#if 0
/* IMM MEM ����ͷ�ڴ��ʹ�õ��ڴ泤�� Byte */
#if ( FEATURE_RATE_84 )  /* ���� 84 M */
    #define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (200000)
#elif ( FEATURE_RATE_42 ) /* ���� 42 M */
    #define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (200000)
#elif ( FEATURE_RATE_28 )  /* ���� 28 M */
    #define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (200000)
#endif
#endif

/* IMM MEM ����ͷ�ڴ��ʹ�õ��ڴ泤�� Byte */
#define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (200000)


/* IMM MEM ����ͷ�ڴ���ڴ����ʹ�õĳ��� */
unsigned long                           g_ulImmMemCtrlMemSuffix = 0;
const  unsigned long * const            g_pulImmMemCtrlMemSuffix = &g_ulImmMemCtrlMemSuffix;
EXPORT_SYMBOL(g_pulImmMemCtrlMemSuffix);

/* IMM MEM ����ͷ�ڴ���ڴ� */
unsigned long                           g_aulImmMemCtrlMemSpace[IMM_MEM_CTRL_MEM_TOTAL_SIZE/4];
const unsigned long * const             g_paulImmMemCtrlMemSpace = &g_aulImmMemCtrlMemSpace[0];
EXPORT_SYMBOL(g_paulImmMemCtrlMemSpace);


/* IMM MEM �����ڴ�ص�λ���� */
const unsigned char IMM_MEM_SHARE_POOL_CLUSTER_CNT = (sizeof(g_astImmMemSharePoolClusterTableInfo)/sizeof(IMM_MEM_CLUSTER_CFG_INFO_STRU));

/* IMM MEM ����ͷ�ڴ�ص�λ���� */
const unsigned char IMM_MEM_CTRL_POOL_CLUSTER_CNT = 1;

const unsigned char IMM_MAGIC_NUM   =   0xaa;

/* �㿽���ڴ�س�ʼ����־����ֹ�ظ����ó�ʼ������ */
unsigned long                           g_ulImmMemInitFlag  = IMM_FALSE;

/* IMM MEM �����ڴ���ܿ��ƽṹ */
IMM_MEM_POOL_STRU                       g_astImmMemPool[IMM_MEM_POOL_ID_BUTT];
EXPORT_SYMBOL(g_astImmMemPool);

/* IMM MEM ����ͷ�ڴ���ܿ��ƽṹ */
IMM_MEM_POOL_STRU                       g_stImmCtrlMemPool;

/* IMM MEM ����ͷ�ڴ���ܿ��ƽṹָ�� */
IMM_MEM_POOL_STRU   *const g_pstImmCtrlMemPool = &g_stImmCtrlMemPool;
EXPORT_SYMBOL(g_pstImmCtrlMemPool);

/* IMM MEM ����ͷ�ڴ��ID */
const unsigned char IMM_MEM_CTRL_POOL_ID        = IMM_MEM_POOL_ID_BUTT;
EXPORT_SYMBOL(IMM_MEM_CTRL_POOL_ID);

/* IMM MEM MNTN�������ȫ�ֱ��� */
IMM_MEM_REG_MNTN_FUNC_STRU              g_ImmRegMntnFuc;
IMM_MEM_REG_MNTN_FUNC_STRU * const      g_pstImmRegMntnFuc = &g_ImmRegMntnFuc;
EXPORT_SYMBOL(IMM_MEM_CTRL_POOL_ID);

/* IMM MEM ��ȡ�ó������ڵĵ�λ���� */
#define IMM_GET_LEN_INDEX(pstImmMemPoolInfo, usLen) \
            ((pstImmMemPoolInfo)->aucLenIndexTable[(usLen)])



void *IMM_MemCtrlMemAlloc(unsigned long ulSize)
{
    unsigned char                       *pucSpace;
    void                                *pAlloc;


    if ( IMM_MEM_CTRL_MEM_TOTAL_SIZE < (g_ulImmMemCtrlMemSuffix + ulSize) )
    {
        panic(" IMM_MemCtrlMemAlloc Fail, Ctrl MEM Over run! \n");
        return NULL;
    }

    pucSpace = (unsigned char *)g_aulImmMemCtrlMemSpace;

    pAlloc   = pucSpace + g_ulImmMemCtrlMemSuffix;

    g_ulImmMemCtrlMemSuffix += IMM_GET_4BYTE_ALIGN_VALUE(ulSize);

    return pAlloc;

} /* IMM_MemCtrlMemAlloc */

IMM_MEM_STRU **IMM_MemCtrlHeadAssign(unsigned char ucPoolId )
{
    IMM_MEM_CLUSTER_STRU           *pstMemCluster;
    IMM_MEM_STRU                  **pMemAddr;
    unsigned long                   ulSaveFlags = 0;
    IMM_MEM_POOL_STRU *const        pstMemPool  = g_pstImmCtrlMemPool;


    if ( ucPoolId >= IMM_MEM_POOL_ID_BUTT )
    {
        panic("IMM_MemCtrlHeadAssign_Debug PoolId Invalid: PoolId = %d \n", ucPoolId );
        return NULL;
    }


    if ( IMM_TRUE != pstMemPool->ucUsedFlag )
    {
        panic("IMM_MemCtrlHeadAssign_Debug Ctrl mem pool not initialized! \n" );
        return NULL;
    }


    pstMemCluster  = &(pstMemPool->astClusterTable[0]);

    local_irq_save(ulSaveFlags);

    if ( 0 != pstMemCluster->usFreeCnt )
    {
        /* ��ȡһ��û��ʹ�õ�IMM_MEM_STRU��� */
        --pstMemCluster->usFreeCnt;
        pMemAddr   = &pstMemCluster->apstFreeStack[pstMemCluster->usFreeCnt];
        pstMemPool->usImmMemUsedCnt++;

        (*pMemAddr)->enPoolId  = ucPoolId;

        local_irq_restore(ulSaveFlags);


        return pMemAddr;
    }

    local_irq_restore(ulSaveFlags);

    panic("IMM_MemCtrlHeadAssign_Debug, Alloc Fail, PoolId = %d \n", ucPoolId);

    return NULL;
} /* IMM_MemCtrlHeadAssign */



unsigned long IMM_MemPoolInit
(
    unsigned char                            ucPoolId,
    unsigned char                          **ppucDataMemAddr
)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    unsigned long                       ulImmMemCnt;
    unsigned char                       ucClusterId;
    IMM_MEM_STRU                      **ppTempMem = NULL;
    IMM_MEM_STRU                       *pstImmMem = NULL;
    unsigned long                       ulImmMemTotalByteSize = 0;


    if ( IMM_FALSE == g_pstImmCtrlMemPool->ucUsedFlag )
    {
        panic("IMM: ERROR, IMM_MemPoolInit Fail, CTRL POOL is not initialized! \n");
        return IMM_FAIL;
    }

    pstImmMemPool = IMM_MemPoolGet(ucPoolId);

    for ( ucClusterId = 0; ucClusterId < pstImmMemPool->ucClusterCnt; ucClusterId++ )
    {
        pstImmMemCluster    = &(pstImmMemPool->astClusterTable[ucClusterId]);


        for(ulImmMemCnt = 0;
            ulImmMemCnt < pstImmMemCluster->usFreeCnt;
            ulImmMemCnt++)
        {

            ppTempMem = IMM_MemCtrlHeadAssign( ucPoolId );
            if ( NULL == ppTempMem )
            {
                return IMM_FAIL;
            }

            pstImmMem = (*ppTempMem);

            pstImmMem->pstMemBlk    = *ppucDataMemAddr; /* ����IMM_MEM_STRU�Ͷ�Ӧ���ݵĹ�ϵ */
            pstImmMem->enPoolId     = ucPoolId;
            pstImmMem->ucClusterId  = ucClusterId;
            pstImmMem->enMemType    = IMM_MEM_TYPE_ID_SHARE;

            *ppucDataMemAddr       += pstImmMemCluster->usLen;
        }

        /* ��������������Ϳ����ڴ�������Ĺ�ϵ */
        pstImmMemCluster->apstFreeStack = ppTempMem;

        ulImmMemTotalByteSize += pstImmMemCluster->usLen*pstImmMemCluster->usTotalCnt;

    }

    /* ��¼���ڴ������IMM_MEMָ�룬����ڴ�й¶ʹ�� */
    pstImmMemPool->pstImmMemStStartAddr     = pstImmMem;
    pstImmMemPool->ulImmMemTotalByteSize    = ulImmMemTotalByteSize;

    return IMM_SUCC;
} /* IMM_MemPoolInit */



unsigned long IMM_MemCtrlPoolInit(void)
{
    IMM_MEM_STRU                      **ppst1stImmMem;
    IMM_MEM_STRU                       *pstImmMem;
    IMM_BLK_MEM_DEBUG_STRU             *pstMemDbInfo;
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    unsigned long                       ulImmMemCnt;
    IMM_MEM_STRU                      **ppTempMem;
    IMM_MEM_POOL_STRU * const           pstImmMemPool = g_pstImmCtrlMemPool;


    /* �����Ӧ�ڴ�صĿ����ڴ�������ÿ��POOL����һ�Σ�����ָ��ÿ��clusterʹ�� */
    ppst1stImmMem = (IMM_MEM_STRU **)IMM_MemCtrlMemAlloc(sizeof(IMM_MEM_STRU *) * pstImmMemPool->usImmMemTotalCnt);

    if (NULL == ppst1stImmMem)
    {
        return IMM_FAIL;
    }


    /* �����Ӧ�ڴ�ص�IMM_MEM��ÿ��POOL����һ�Σ�����ָ��ÿ��clusterʹ�� */
    pstImmMem = (IMM_MEM_STRU *)IMM_MemCtrlMemAlloc(sizeof(IMM_MEM_STRU) * pstImmMemPool->usImmMemTotalCnt);

    if (NULL == pstImmMem)
    {
        return IMM_FAIL;
    }

    /* ����IMM_MEM��Ӧ��IMM_BLK_MEM_DEBUG_ST */
    pstMemDbInfo = (IMM_BLK_MEM_DEBUG_STRU *)IMM_MemCtrlMemAlloc(sizeof(IMM_BLK_MEM_DEBUG_STRU) * pstImmMemPool->usImmMemTotalCnt);

    if (NULL == pstMemDbInfo)
    {
        return IMM_FAIL;
    }

    memset(ppst1stImmMem, 0, sizeof(IMM_MEM_STRU *) * pstImmMemPool->usImmMemTotalCnt);
    memset(pstImmMem, 0, sizeof(IMM_MEM_STRU) * pstImmMemPool->usImmMemTotalCnt);
    memset(pstMemDbInfo, 0, sizeof(IMM_BLK_MEM_DEBUG_STRU) * pstImmMemPool->usImmMemTotalCnt);

    ppTempMem = ppst1stImmMem;

     /* ��¼���ڴ������IMM_MEMָ�룬����ڴ�й¶ʹ�� */
    pstImmMemPool->pstImmMemStStartAddr = pstImmMem;


     /* ����IMM_MEM ��Cluster, IMM �����ڴ��ֻ��һ����λ */
    pstImmMemCluster = &(pstImmMemPool->astClusterTable[0]);

    /* ��������������Ϳ����ڴ�������Ĺ�ϵ */
    pstImmMemCluster->apstFreeStack = ppTempMem;

    for(ulImmMemCnt = 0;
        ulImmMemCnt < pstImmMemCluster->usFreeCnt;
        ulImmMemCnt ++)
    {

        pstImmMem->enPoolId     = IMM_MEM_CTRL_POOL_ID;
        pstImmMem->ucClusterId  = 0;
        pstImmMem->pstMemBlk    = NULL;
        pstImmMem->pstDbgInfo   = pstMemDbInfo;
        pstImmMem->ucMagicNum   = IMM_MAGIC_NUM;
        pstImmMem->enMemType    = IMM_MEM_TYPE_ID_EXT;
         /* ���������ڴ��������IMM_MEM_ST�Ĺ�ϵ */

       *ppTempMem               = pstImmMem;

        pstImmMem++;
        ppTempMem++;
        pstMemDbInfo++;
    }


    return IMM_SUCC;
} /* IMM_MemCtrlPoolInit */



unsigned long IMM_MemCtrlPoolCreate
(
    const IMM_MEM_POOL_CFG_INFO_STRU   *pstPoolCfg,
    unsigned short                      usExtraCtrlHead
)
{
    const IMM_MEM_CLUSTER_CFG_INFO_STRU    *pstPoolClusterCfgTable;
    const IMM_MEM_CLUSTER_CFG_INFO_STRU    *pstClusterCfgInfo;
    IMM_MEM_CLUSTER_STRU                   *pstMemCluster;
    IMM_MEM_POOL_STRU *const                pstImmMemPool = g_pstImmCtrlMemPool;
    unsigned long                           ulRet = IMM_SUCC;



    /* ����ӦID���ڴ���Ƿ��б��ظ����� */
    if (IMM_TRUE == pstImmMemPool->ucUsedFlag)
    {
        panic("IMM_MemPoolCreate Fail, ulPoolId %d is already used\r\n",
            pstPoolCfg->enPoolId);
        return IMM_FAIL;
    }


    pstPoolClusterCfgTable          = pstPoolCfg->pstClusterCfgInfo;

    /* ��ʼ���ڴ�ص�ͨ�ñ��� */
    pstImmMemPool->ucUsedFlag       = IMM_FALSE;
    pstImmMemPool->ucClusterCnt     = IMM_MEM_CTRL_POOL_CLUSTER_CNT;
    pstImmMemPool->usImmMemTotalCnt = 0;

    /* ÿ��POOL�����һ��size�������ƫ�Ƶ����һ���������ڴ��ֻ��һ�� */
    pstClusterCfgInfo               = pstPoolClusterCfgTable;
    pstImmMemPool->usMaxByteLen     = pstClusterCfgInfo->usSize;


    memset(pstImmMemPool->aucLenIndexTable, 0, IMM_MEM_BLK_MAX_BYTE_LEN);

    memset(pstImmMemPool->astClusterTable, 0,
        sizeof(IMM_MEM_CLUSTER_STRU) * IMM_MEM_BLK_MAX_CLUSTER_NUM);


    pstClusterCfgInfo                   = pstPoolClusterCfgTable;
    pstMemCluster                       = pstImmMemPool->astClusterTable;
    pstMemCluster->usTotalCnt           = pstClusterCfgInfo->usCnt + usExtraCtrlHead;
    pstMemCluster->usFreeCnt            = pstMemCluster->usTotalCnt;
    pstMemCluster->usLen                = pstClusterCfgInfo->usSize;
    pstImmMemPool->aucLenIndexTable[0]  = 0;
    pstImmMemPool->usImmMemTotalCnt     = pstMemCluster->usTotalCnt;


    ulRet = IMM_MemCtrlPoolInit();

    if( IMM_SUCC != ulRet )
    {
        panic(" IMM_MemCtrlPoolCreate Pool Init failed ! \n");
        return IMM_FAIL;
    }


    pstImmMemPool->ucUsedFlag   = IMM_TRUE;

    return IMM_SUCC;
} /* IMM_MemCtrlPoolCreate */



unsigned long IMM_MemPoolCreate
(
    const IMM_MEM_POOL_CFG_INFO_STRU   *pstPoolCfg,
    unsigned char                     **ppucDataMemAddr
)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstPoolClusterCfgTable;
    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;
    IMM_MEM_CLUSTER_STRU               *pstMemCluster;
    unsigned long                       usLastClusterMaxLen;
    unsigned long                       usDataLen;
    unsigned char                       ucPoolId;
    unsigned char                       ucClusterId;
    unsigned char                      *pucDataMemAddr;
    unsigned char                       ucClusterCnt = 0;
    unsigned long                       ulRet = IMM_SUCC;


    if ( NULL == *ppucDataMemAddr )
    {
        panic("IMM_MemPoolCreate Fail, input *ppucDataMemAddr is NULL PRT \r\n");
        return  IMM_FAIL;
    }

    if ( pstPoolCfg->enPoolId >= IMM_MEM_POOL_ID_BUTT )
    {
        panic("IMM_MemPoolCreate Fail, ulPoolId %d exceed the Ranger\r\n",
            pstPoolCfg->enPoolId);
        return  IMM_FAIL;
    }


    pucDataMemAddr  = (unsigned char *)(*ppucDataMemAddr);

    ucPoolId        = pstPoolCfg->enPoolId;

    pstImmMemPool   = IMM_MemPoolGet(ucPoolId);


    if ( NULL == pstImmMemPool )
    {
        panic("IMM_MemPoolCreate Fail, get pool failed\n");
        return IMM_FAIL;
    }

    /* ����ӦID���ڴ���Ƿ��б��ظ����� */
    if (IMM_TRUE == pstImmMemPool->ucUsedFlag)
    {
        panic("IMM_MemPoolCreate Fail, ulPoolId %d is already used\r\n",
            ucPoolId);
        return IMM_FAIL;
    }

    ucClusterCnt                    = pstPoolCfg->ucClusterCnt;
    pstPoolClusterCfgTable          = pstPoolCfg->pstClusterCfgInfo;

    /* ��ʼ���ڴ�ص�ͨ�ñ��� */

    pstImmMemPool->ucUsedFlag       = IMM_FALSE;
    pstImmMemPool->ucClusterCnt     = ucClusterCnt;
    pstImmMemPool->usImmMemTotalCnt = 0;

    /* ÿ��POOL�����һ��size�������ƫ�Ƶ����һ���������POOL�����size */
    pstClusterCfgInfo               = pstPoolClusterCfgTable + (ucClusterCnt - 1);
    pstImmMemPool->usMaxByteLen     = pstClusterCfgInfo->usSize;


    /* ���볤���������Գ���Ϊ�����±꣬������󳤶�Ҫ���������С1 */
    if (pstImmMemPool->usMaxByteLen > (IMM_MEM_BLK_MAX_BYTE_LEN - 1))
    {
        panic("IMM_MemPoolCreate Fail, MaxByteLen:%d too big.\r\n",
            pstImmMemPool->usMaxByteLen);
        return IMM_FAIL;
    }

    if (pstImmMemPool->ucClusterCnt > IMM_MEM_BLK_MAX_CLUSTER_NUM)
    {
        panic("IMM_MemPoolCreate Fail, ClusterCnt:%d exceed.\r\n",
            pstImmMemPool->ucClusterCnt);
        return IMM_FAIL;
    }

    memset(pstImmMemPool->aucLenIndexTable, 0, IMM_MEM_BLK_MAX_BYTE_LEN);

    memset(pstImmMemPool->astClusterTable, 0,
        sizeof(IMM_MEM_CLUSTER_STRU) * IMM_MEM_BLK_MAX_CLUSTER_NUM);

    usLastClusterMaxLen = 1;

    for (ucClusterId = 0; ucClusterId < ucClusterCnt; ucClusterId++)
    {
        pstClusterCfgInfo               = pstPoolClusterCfgTable + ucClusterId;
        pstMemCluster                   = &(pstImmMemPool->astClusterTable[ucClusterId]);

        pstMemCluster->usTotalCnt       = pstClusterCfgInfo->usCnt;
        pstMemCluster->usFreeCnt        = pstClusterCfgInfo->usCnt;
        pstMemCluster->usLen            = pstClusterCfgInfo->usSize;

       *ppucDataMemAddr                += (pstClusterCfgInfo->usSize) * (pstClusterCfgInfo->usCnt);

        for(usDataLen = usLastClusterMaxLen;
            usDataLen <= pstClusterCfgInfo->usSize;
            usDataLen++)
        {
            pstImmMemPool->aucLenIndexTable[usDataLen]      = ucClusterId;
        }

        usLastClusterMaxLen                 = usDataLen;

        pstImmMemPool->usImmMemTotalCnt    += pstClusterCfgInfo->usCnt;
    }


    ulRet = IMM_MemPoolInit(ucPoolId, &pucDataMemAddr);


    if( IMM_SUCC != ulRet )
    {
        panic(" IMM_MemPoolCreate Pool Init failed ! \n");
        return IMM_FAIL;
    }


    pstImmMemPool->ucUsedFlag   = IMM_TRUE;

    return IMM_SUCC;
} /* IMM_MemPoolCreate */

unsigned long IMM_MemBlkInit(void)
{
    unsigned long                       ulRet1;
    unsigned long                       ulRet2;
    unsigned long                       ulLoop;

    unsigned char                      *pucBaseAddr;
    IMM_MEM_POOL_CFG_INFO_STRU          stSharePoolCfgInfo;
    IMM_MEM_POOL_CFG_INFO_STRU          stCtrlPoolCfgInfo;
    unsigned short                      usBlkNum = 0;


    /*��ʼ������ֻ�ᱻskbuf_init ���� */
    if ( IMM_TRUE == g_ulImmMemInitFlag )
    {
        printk( "IMM_MemBlkInit, Warning, Memory pools were already initialized!\n");

        return IMM_SUCC;
    }

    /* �����ڴ����Ϣ */
    memset(g_astImmMemPool, 0, sizeof(IMM_MEM_POOL_STRU)* IMM_MEM_POOL_ID_BUTT);
    memset(&g_ImmRegMntnFuc, 0, sizeof(IMM_MEM_REG_MNTN_FUNC_STRU));
    memset(g_pstImmCtrlMemPool, 0, sizeof(IMM_MEM_POOL_STRU));

    memset(&stSharePoolCfgInfo, 0, sizeof(IMM_MEM_POOL_CFG_INFO_STRU));
    memset(&stCtrlPoolCfgInfo, 0, sizeof(IMM_MEM_POOL_CFG_INFO_STRU));

    /* ���湲���ڴ�����ò��� */
    stSharePoolCfgInfo.pstClusterCfgInfo       = (IMM_MEM_CLUSTER_CFG_INFO_STRU *)g_astImmMemSharePoolClusterTableInfo;
    stSharePoolCfgInfo.ucClusterCnt            = IMM_MEM_SHARE_POOL_CLUSTER_CNT;
    stSharePoolCfgInfo.enPoolId                = IMM_MEM_POOL_ID_SHARE;

    /* �������ͷ�ڴ�����ò��� */
    stCtrlPoolCfgInfo.pstClusterCfgInfo        = (IMM_MEM_CLUSTER_CFG_INFO_STRU *)g_astImmMemCtrlPoolClusterTableInfo;
    stCtrlPoolCfgInfo.ucClusterCnt             = IMM_MEM_CTRL_POOL_CLUSTER_CNT;
    stCtrlPoolCfgInfo.enPoolId                 = IMM_MEM_CTRL_POOL_ID;

    /* ���������ڴ������Ҫ�Ŀ��ƽڵ���Ŀ */
    for ( ulLoop = 0;  ulLoop < IMM_MEM_SHARE_POOL_CLUSTER_CNT; ++ulLoop )
    {
        usBlkNum += stSharePoolCfgInfo.pstClusterCfgInfo[ulLoop].usCnt;
    }

    /* ��������ͷ�ڴ�� */
    ulRet1 = IMM_MemCtrlPoolCreate(&stCtrlPoolCfgInfo, usBlkNum );

    /* �ڴ�����ַ������ʵ��ַת���ַ */
    pucBaseAddr = (unsigned char *)TTF_PHY_TO_VIRT(IMM_SHARE_MEM_POOL_ADDR);

    /* ���������ڴ�� */
    ulRet2 = IMM_MemPoolCreate(&stSharePoolCfgInfo, &pucBaseAddr);

    /* �����ѱ���ʼ���ı�־ */
    g_ulImmMemInitFlag = IMM_TRUE;

    if ( ( IMM_FAIL == ulRet1 ) || ( IMM_FAIL == ulRet2 ) )
    {
        panic("Create IMM failed ! \n");

        return IMM_FAIL;
    }

    return IMM_SUCC;

} /* IMM_MemBlkInit */



unsigned long IMM_MemFreeMemCheck( const IMM_MEM_STRU **ppstImm )
{
    if ( NULL == ppstImm )
    {
        printk( "Error: IMM_MemFreeMemCheck Input pstMem is NULL! \n");
        return IMM_FALSE;
    }

    if ( NULL == *ppstImm )
    {
        printk("Error: IMM_MemFreeMemCheck Input *pstMem is NULL! \n");
        return IMM_FALSE;
    }

    if ( IMM_MEM_TYPE_ID_BUTT <= (*ppstImm)->enMemType)
    {
        printk("Error: IMM_MemFreeMemCheck Input *pstMem type = %d is invalid! \n", (int)(*ppstImm)->enMemType);

        return IMM_FALSE;
    }


    if ( IMM_MAGIC_NUM != (*ppstImm)->ucMagicNum)
    {
        printk("IMM_MemFreeMemCheck, Magic Num %d is invalid! \n", (int)(*ppstImm)->ucMagicNum);

        return IMM_FALSE;
    }

    return IMM_TRUE;
}



IMM_MEM_POOL_STRU *IMM_MemPoolGet(unsigned char ucPoolId)
{
    if ( IMM_MEM_POOL_ID_BUTT > ucPoolId )
    {
        return &g_astImmMemPool[ucPoolId];
    }
    else
    {
        return NULL;
    }

} /* IMM_MemPoolGet */
EXPORT_SYMBOL(IMM_MemPoolGet);
IMM_MEM_POOL_STRU *IMM_MemEventRptPoolGet(unsigned char ucPoolId)
{
    if ( IMM_MEM_POOL_ID_BUTT > ucPoolId )
    {
        return &g_astImmMemPool[ucPoolId];
    }
    else if( IMM_MEM_CTRL_POOL_ID == ucPoolId )
    {
        return g_pstImmCtrlMemPool;
    }
    else
    {
        return NULL;
    }

} /* IMM_MemEventRptPoolGet */
EXPORT_SYMBOL(IMM_MemEventRptPoolGet);
IMM_MEM_STRU *IMM_MemBlkAlloc_Debug(unsigned short usFileID, unsigned short usLineNum,
                        unsigned char ucPoolId, unsigned short usLen)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;
    IMM_MEM_CLUSTER_STRU           *pstImmMemCluster;
    IMM_MEM_STRU                   *pMem;
    unsigned long                   ulMaxClusterFreeCnt;
    unsigned char                   ucClusterId;
    unsigned char                   ucMostFitLev;
    unsigned long                   ulSaveFlags  = 0;


    if ( ucPoolId >= IMM_MEM_POOL_ID_BUTT )
    {
        printk("IMM_MemBlkAlloc_Debug,Poolid %d is invalid!\n", ucPoolId);
        return NULL;
    }

     /* ��ȡ�ڴ�� */
    pstImmMemPool = IMM_MEM_GET_POOL(ucPoolId);

    if ( IMM_TRUE != pstImmMemPool->ucUsedFlag )
    {
        printk("IMM_MemBlkAlloc_Debug,Pool %d is not used!\n", ucPoolId);
        return NULL;
    }

     /* ���볤���Ƿ��ڸ��ڴ��� */
    if ((0 == usLen ) || (usLen > pstImmMemPool->usMaxByteLen))
    {
        printk("IMM_MemBlkAlloc_Debug,usLen %d exceed the ranger!\n", usLen);
        return NULL;
    }

     /* ���ڴ�صĶ������Ѱ�Һ��ʵ�IMM_MEM */
    ucMostFitLev = IMM_GET_LEN_INDEX(pstImmMemPool, usLen);

    for(ucClusterId = ucMostFitLev;
        ucClusterId < pstImmMemPool->ucClusterCnt;
        ucClusterId ++)
    {
        pstImmMemCluster  = &(pstImmMemPool->astClusterTable[ucClusterId]);

        local_irq_save(ulSaveFlags);

        if (0 != pstImmMemCluster->usFreeCnt)
        {
            /* ��ȡһ��û��ʹ�õ�IMM_MEM_ST��� */
            pMem    = pstImmMemCluster->apstFreeStack[--pstImmMemCluster->usFreeCnt];
            pstImmMemPool->usImmMemUsedCnt++;
            pstImmMemPool->ulImmMemUsedByteSize += pstImmMemCluster->usLen;
            ulMaxClusterFreeCnt = pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usFreeCnt;

            local_irq_restore(ulSaveFlags);

            if (NULL != pstImmMemPool->pMemAllocEvent)
            {
                pstImmMemPool->pMemAllocEvent( ulMaxClusterFreeCnt );
            }

            if ( NULL != g_pstImmRegMntnFuc->pImmSaveMemAllocDebugInfoFunc )
            {
                g_pstImmRegMntnFuc->pImmSaveMemAllocDebugInfoFunc( pMem, usFileID, usLineNum );
            }

            return pMem;
        }


        local_irq_restore(ulSaveFlags);
    }

    printk("IMM_MemBlkAlloc_Debug, Alloc Fail, PoolId %d, FileID %d, LineNum %d",
        (int)ucPoolId, (int)usFileID, (int)usLineNum);

    if ( NULL != g_ImmRegMntnFuc.pImmMemEventRptFunc)
    {
        g_ImmRegMntnFuc.pImmMemEventRptFunc(ucPoolId, IMM_MEM_TRIG_TYPE_ALLOC_FAIL);
    }


    return NULL;
} /* IMM_MemBlkAlloc_Debug */
EXPORT_SYMBOL(IMM_MemBlkAlloc_Debug);
void IMM_MemFreeCtrlHead_Debug(IMM_MEM_STRU **ppstMem)
{
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    IMM_MEM_STRU                       *pstImmMem;
    unsigned char                       ucRlst;
    IMM_MEM_POOL_STRU * const           pstImmMemPool = g_pstImmCtrlMemPool;
    unsigned long                       ulSaveFlags  = 0;


    pstImmMem = *ppstMem;

    if ( NULL != g_pstImmRegMntnFuc->pImmSaveMemFreeDebugInfoFunc )
    {
        ucRlst = g_pstImmRegMntnFuc->pImmSaveMemFreeDebugInfoFunc( pstImmMem );
        if (IMM_SUCC != ucRlst  )
        {
            printk("IMM_MemFreeCtrlHead_Debug, free IMM MEM fail ! \n");
            return;
        }
    }

    if (IMM_TRUE != pstImmMemPool->ucUsedFlag)
    {
        printk("IMM_MemFreeCtrlHead_Debug, CTRL Pool is not used! \n");
        return ;
    }

    pstImmMemCluster = &(pstImmMemPool->astClusterTable[pstImmMem->ucClusterId]);

    if ( NULL != pstImmMemPool->pMemExtFreeFunc )
    {
        pstImmMemPool->pMemExtFreeFunc(pstImmMem->pstMemBlk);/*�ͷ��ⲿ�ڴ�*/
    }
    else if ( NULL != pstImmMem->pstMemBlk )
    {
        printk("IMM_MemFreeCtrlHead_Debug, warning, pstImmMem->pstMemBlk not freed! \n");
    }

    pstImmMem->pstMemBlk = NULL;

    local_irq_save(ulSaveFlags);


    if (pstImmMemCluster->usFreeCnt >= pstImmMemCluster->usTotalCnt)
    {
        local_irq_restore(ulSaveFlags);
        printk("IMM_MemFreeCtrlHead_Debug, free cnt error:FreeCnt %d, TotalCnt %d ! \n",
                pstImmMemCluster->usFreeCnt, pstImmMemCluster->usTotalCnt);
        return ;
    }

    pstImmMemCluster->apstFreeStack[pstImmMemCluster->usFreeCnt] = pstImmMem;
    pstImmMemCluster->usFreeCnt++;

    pstImmMemPool->usImmMemUsedCnt--;

    local_irq_restore(ulSaveFlags);

    *ppstMem = NULL;

    return ;
} /* IMM_MemFreeCtrlHead_Debug */
EXPORT_SYMBOL(IMM_MemFreeCtrlHead_Debug);



void IMM_MemFree_Debug(IMM_MEM_STRU **ppstMem)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    IMM_MEM_STRU                       *pstImmMem;
    unsigned long                       ulMaxClusterFreeCnt;
    unsigned char                       ucRlst;
    unsigned long                       ulSaveFlags  = 0;


    if ( IMM_FALSE== IMM_MemFreeMemCheck(ppstMem) )
    {
        printk( "Error: IMM_MemBlkSingleFree_Debug Input pstMem is invalid! \n");
        return;
    }

    pstImmMem = *ppstMem;


    if (( IMM_MEM_TYPE_ID_EXT == pstImmMem->enMemType)&&( IMM_MEM_CTRL_POOL_ID == pstImmMem->enPoolId ))
    {
        IMM_MemFreeCtrlHead_Debug(ppstMem);

        return;
    }

    if ( NULL != g_pstImmRegMntnFuc->pImmSaveMemFreeDebugInfoFunc )
    {
        ucRlst = g_pstImmRegMntnFuc->pImmSaveMemFreeDebugInfoFunc( pstImmMem );
        if (IMM_SUCC != ucRlst  )
        {
            printk("IMM_MemFreeCtrlHead_Debug, free IMM MEM fail ! \n");
            return;
        }
    }

    if( pstImmMem->enPoolId > IMM_MEM_POOL_ID_BUTT )
    {
        printk("IMM_MemFree_Debug, Poolid %d is invalid! \n",
             pstImmMem->enPoolId);
        return ;
    }

    pstImmMemPool   = IMM_MEM_GET_POOL(pstImmMem->enPoolId);

    if (IMM_TRUE != pstImmMemPool->ucUsedFlag)
    {
        printk("IMM_MemFree_Debug, Pool %d is not used! \n",
            pstImmMem->enPoolId);
        return ;
    }

    pstImmMemCluster = &(pstImmMemPool->astClusterTable[pstImmMem->ucClusterId]);

    local_irq_save(ulSaveFlags);


    if (pstImmMemCluster->usFreeCnt >= pstImmMemCluster->usTotalCnt)
    {
        local_irq_restore(ulSaveFlags);
        printk("IMM_MemFreeCtrlHead_Debug, free cnt error:FreeCnt %d, TotalCnt %d ! \n",
                pstImmMemCluster->usFreeCnt, pstImmMemCluster->usTotalCnt);

        return ;
    }


    pstImmMemCluster->apstFreeStack[pstImmMemCluster->usFreeCnt] = pstImmMem;
    pstImmMemCluster->usFreeCnt++;
    pstImmMemPool->usImmMemUsedCnt--;
    pstImmMemPool->ulImmMemUsedByteSize -= pstImmMemCluster->usLen;
    ulMaxClusterFreeCnt = pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usTotalCnt
                            - pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usFreeCnt;

    local_irq_restore(ulSaveFlags);

    if ( NULL != pstImmMemPool->pMemFreeEvent)
    {
        pstImmMemPool->pMemFreeEvent(ulMaxClusterFreeCnt );
    }

    *ppstMem = NULL;

    return ;
} /* IMM_MemFree_Debug */
EXPORT_SYMBOL(IMM_MemFree_Debug);
unsigned long IMM_MemRegExtFreeCallBack
(
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
)
{
    IMM_MEM_POOL_STRU * const           pstIMMMemPool = g_pstImmCtrlMemPool;


    if ( NULL == pMemExtFreeFunc )
    {
        return IMM_FAIL;
    }

    if ( NULL != pstIMMMemPool->pMemExtFreeFunc )
    {
        return IMM_SUCC;
    }

    pstIMMMemPool->pMemExtFreeFunc = pMemExtFreeFunc;

    return IMM_SUCC;
} /* IMM_MemRegExtFreeCallBack */
EXPORT_SYMBOL(IMM_MemRegExtFreeCallBack);
void IMM_MemRegMntnFuncCallBack
(
    IMM_SAVE_MEM_ALLOC_INFO_CALLBACK             pImmSaveMemAllocDebugInfoFunc,
    IMM_SAVE_MEM_FREE_INFO_CALLBACK              pImmSaveMemFreeDebugInfoFunc,
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK         pImmMemEventRptFunc
)
{
    if (( NULL == pImmSaveMemAllocDebugInfoFunc )
        ||( NULL == pImmSaveMemFreeDebugInfoFunc )
        ||( NULL == pImmMemEventRptFunc ))
    {
        printk("IMM_MemRegPsFuncCallBack fail: invalid input paras! \n");
        return;
    }

    g_pstImmRegMntnFuc->pImmSaveMemAllocDebugInfoFunc   = pImmSaveMemAllocDebugInfoFunc;
    g_pstImmRegMntnFuc->pImmSaveMemFreeDebugInfoFunc    = pImmSaveMemFreeDebugInfoFunc;
    g_pstImmRegMntnFuc->pImmMemEventRptFunc             = pImmMemEventRptFunc;

    return;
}
EXPORT_SYMBOL(IMM_MemRegMntnFuncCallBack);



unsigned long IMM_MemRegEventCallBack
(
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId,
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent,
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent
)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;


    pstImmMemPool   = IMM_MemPoolGet(enPoolId);

    if ( NULL == pstImmMemPool )
    {
        return IMM_FAIL;
    }

    pstImmMemPool->pMemAllocEvent   = pMemAllocEvent;
    pstImmMemPool->pMemFreeEvent    = pMemFreeEvent;

    return IMM_SUCC;
} /* IMM_MemRegEventCallBack */
EXPORT_SYMBOL(IMM_MemRegEventCallBack);
IMM_MEM_STRU *IMM_MemCtrlHeadAlloc_Debug(unsigned short usFileID, unsigned short usLineNum )
{
    IMM_MEM_CLUSTER_STRU           *pstImmMemCluster;
    IMM_MEM_STRU                   *pMem;
    unsigned long                   ulSaveFlags     = 0;
    IMM_MEM_POOL_STRU * const       pstImmMemPool   = g_pstImmCtrlMemPool;



    if ( IMM_TRUE != pstImmMemPool->ucUsedFlag )
    {
        printk("IMM_MemCtrlHeadAlloc_Debug IMM Ctrl Pool is not used!");
        return NULL;
    }


    pstImmMemCluster  = &(pstImmMemPool->astClusterTable[0]);

    local_irq_save(ulSaveFlags);

    if (0 != pstImmMemCluster->usFreeCnt)
    {
        /* ��ȡһ��û��ʹ�õ�IMM_MEM_ST��� */
        pMem    = pstImmMemCluster->apstFreeStack[--pstImmMemCluster->usFreeCnt];
        pstImmMemPool->usImmMemUsedCnt++;

        local_irq_restore(ulSaveFlags);

        pMem->enMemType = IMM_MEM_TYPE_ID_EXT;

        if ( NULL != g_pstImmRegMntnFuc->pImmSaveMemAllocDebugInfoFunc )
        {
            g_pstImmRegMntnFuc->pImmSaveMemAllocDebugInfoFunc( pMem, usFileID, usLineNum );
        }

        return pMem;
    }


    local_irq_restore(ulSaveFlags);

    printk("IMM_MemCtrlHeadAlloc_Debug, Alloc Fail, FileID %d, LineNum %d",
            (int)usFileID, (int)usLineNum);


    if ( NULL != g_ImmRegMntnFuc.pImmMemEventRptFunc)
    {
        g_ImmRegMntnFuc.pImmMemEventRptFunc( IMM_MEM_CTRL_POOL_ID, IMM_MEM_TRIG_TYPE_ALLOC_FAIL);
    }

    return NULL;
} /* IMM_MemCtrlHeadAlloc_Debug */
EXPORT_SYMBOL(IMM_MemCtrlHeadAlloc_Debug);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

