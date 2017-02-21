/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8KuvCXwlu8YyWSXpnqKpNf298MpQO3WS6xwUJOD
26toFzIMHZRToX7CYgU1qGuu06vQx8UaF+raLG8JFTNEr9/txM/+1ZbA5JdiXyiDsx3/y17i
I42Oo2R6lFMvkas798BV2S2Sj3D+65cWSUESa8UCRP5RmBo8l1gV4ZIkkuH44w==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_cache.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������CACHEģ��Ķ���ͷ�ļ��� \n
 */
/** @defgroup sre_cache Cache
   *@ingroup SRE_kernel
*/

#ifndef _SRE_CACHE_H
#define _SRE_CACHE_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
* @ingroup sre_cache
* cache����Ϊָ��cache��
*/
#define OS_ICACHE_TYPE                                      1

/**
* @ingroup sre_cache
* cache����Ϊ����cache��
*/
#define OS_DCACHE_TYPE                                      2
#if(OS_HARDWARE_PLATFORM != OS_HIDSP)
/**
* @ingroup sre_cache
* cache��С�������ò��Ϸ���
*/
#define SRE_CACHE_SIZE_INVALID                              0x00000001
#else
#define SRE_CACHE_SIZE_INVALID                              0xFFFFFFFF
#endif
/**
* @ingroup sre_cache
*cache��ַ�����������ò��Ϸ� ��
*/
#define SRE_CACHE_ADDR_INVALID                              0x00000002

/**
* @ingroup sre_cache
*cache���Ͳ������ò��Ϸ� ��
*/
#define SRE_CACHE_TYPE_INVALID                              0x00000003

/**
* @ingroup sre_cache
* cache�����������㡣
*/
#define SRE_CACHE_NOAREA_LOCK                               0x00000006

/**
* @ingroup sre_cache
* cache TAG��ȡ�ӿ���ε�ַΪ�ա�
*/
#define SRE_CACHE_TAG_PTR_NULL                              0x00000007

/**
* @ingroup sre_cache
*cache������ַ��������
*/
#define SRE_CACHE_ADDR_LOCKED                               0x00000008

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)

typedef enum
{
    CACHE_UNIFY     = 0,                    /**< Unify mode         */
    CACHE_SPLIT     = 1                     /**< Split mode         */
} OS_CACHE_MODE_E;

typedef enum
{
    ONE_LINE_PF     = 0,                    /**< 1 line             */
    TWO_LINES_PF    = 1,                    /**< 2 lines            */
    THREE_LINES_PF  = 3,                    /**< 3 lines            */
    INVALID_DCC_HWPF = 4                    /**< invaild            */
} OS_DCC_HWPF_POLICY_E;

typedef enum
{
    ZERO_LINE_OFFSET    = 0,                /**< 0                  */
    QUATER_LINE_OFFSET  = 1,                /**< 1/4 cache line     */
    HALF_LINE_OFFSET    = 2,                /**< 1/2 cache line     */
    THREE_QUARTERS_LINE_OFFSET = 3,         /**< 3/4 cache line     */
    INVALID_PCC_HWPF = 4                    /**< invaild            */
} OS_PCC_HWPF_POLICY_E;

#endif

/**
* @ingroup sre_cache
* cache������: ʹ��cache�ӿڣ�����cache�����СΪ0�����߼�������Ԥȡ�ӿڲ�����ʵ�ʴ�С�������ɲ�����Χ���򷵻ظ�ֵ��
*
* ֵ: 0x02001101
*
* �������: ���������ռ��С
*/
#define OS_ERRNO_CACHE_SIZE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_SIZE_INVALID)

/**
 * @ingroup sre_cache
 * cache������: ʹ�ü��������Լ���ȡtag�ӿ�ʱ��������ַ������cache�ķ�Χ
 *
 * ֵ: 0x02001102
 *
 * �������: �鿴������ַ�ռ��Ƿ��cache
 */
#define OS_ERRNO_CACHE_ADDR_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_INVALID)

/**
 * @ingroup sre_cache
 * cache������: ����cache�ӽ����ӿ��Լ���ȡtag�ӿ�ʱ�������cache���Ͳ���ȷ��Ŀǰֻ֧��ICACHE���мӽ�������������ֵ�������룬��ȡcache tag�ӿ�֧��ָ��cache������cache���ͣ�ֻ����PCC����DCC��
 *
 * ֵ: 0x02001103
 *
 * �������: �鿴�����cache�����Ƿ�֧��
 */
#define OS_ERRNO_CACHE_TYPE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TYPE_INVALID)

/**
 * @ingroup sre_cache
 * cache������: cache���������У�����ĳһ�������������
 *
 * ֵ: 0x02001106
 *
 * �������: ���������ӿ���Ҫ���ʹ�ã������ռ䷶Χ���ޣ���鿴�Ƿ���ж�μ�����
 */
#define OS_ERRNO_CACHE_NOAREA_LOCK                      SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_NOAREA_LOCK)

/**
 * @ingroup sre_cache
 * cache������: cache tag��ȡ�ӿڣ������tag�ṹ��ָ��Ϊ��
 *
 * ֵ: 0x02001107
 *
 * �������: ��������Ľṹ��ָ���Ƿ�Ϊ��
 */
#define OS_ERRNO_CACHE_TAG_PTR_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TAG_PTR_NULL)

/**
 * @ingroup sre_cache
 * cache������: ����ָ��cache��Ч�ӿ�ʱ�����ڸ���Ч�ռ���ڼ����������Ч���ɹ�
 *
 * ֵ: 0x02001108
 *
 * �������: ��Чǰ����õ�ַ�Ƿ����
 */
#define OS_ERRNO_CACHE_ADDR_LOCKED                      SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_LOCKED)

/**
 * @ingroup sre_cache
 * cache������: CACHEģʽ����ֻ����Unify����Split
 *
 * ֵ: 0x0200110a
 *
 * �������: �޸�cacheģʽ
 */
#define OS_ERRNO_CACHE_MODE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0a)

/**
 * @ingroup sre_cache
 * cache������: Thread ID����ֻ����0����1
 *
 * ֵ: 0x0200110b
 *
 * �������: �޸�Thread ID
 */
#define OS_ERRNO_CACHE_THD_ID_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0b)

/**
 * @ingroup sre_cache
 * cache������: PCC Ӳ��Ԥȡ���Դ���
 *
 * ֵ: 0x0200110c
 *
 * �������: �޸�PCC Ӳ��Ԥȡ����
 */
#define OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0c)

/**
 * @ingroup sre_cache
 * cache������: PCC BACKDOOR�������ʹ���
 *
 * ֵ: 0x0200110d
 *
 * �������: �޸�PCC BACKDOOR��������,MEM/TAG��Ч
 */
#define OS_ERRNO_CACHE_PCC_BACKDOOR_ACESS_INVALID         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0d)

/**
 * @ingroup sre_cache
 * cache������: PCC BACKDOOR����way number����
 *
 * ֵ: 0x0200110e
 *
 * �������: �޸�PCC BACKDOOR����way number,ȡֵ��Χ0~7
 */
#define OS_ERRNO_CACHE_PCC_BACKDOOR_WAY_NUM_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0e)

/**
 * @ingroup sre_cache
 * cache������: DCC Ӳ��Ԥȡ���Դ���
 *
 * ֵ: 0x0200110f
 *
 * �������: �޸�DCC Ӳ��Ԥȡ����
 */
#define OS_ERRNO_CACHE_DCC_HWPF_POLICY_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0f)

/**
 * @ingroup SRE_cache
 * CACHE������: PCC ����������
 *
 * ֵ: 0x02001110
 *
 * ������� :4��ɼ�����ַ�����Ѿ�ʹ���꣬��������ܼ�������
 */
#define OS_ERRNO_CACHE_PCC_LOCK_BLOCK_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_CACHE,0x10)

/**
 * @ingroup SRE_cache
 * CACHE������: ��ȡTAG����MEM��Ϣʧ��
 *
 * ֵ: 0x02001111
 *
 * ������� : �û�����ĵ�ַ��Ӧ��TAG����MEM������Ч��cache��
 */
#define OS_ERRNO_CACHE_BACKDOOR_INFO_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_CACHE,0x11)

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 * @ingroup sre_cache
 * CACHE Tag �ṹ����Ϣ��
 */
typedef struct tagCacheCb
{
    UINT32  uwCacheTag; /**< cache tag��������Ϣ                         */
    BOOL    bDirty;     /**< dcache�е������Ƿ��޸ģ�����Dache��Ч     */
    BOOL    bLock;      /**< cache�е������Ƿ񱻼���������SD6182��SD6157ƽ̨��Ч */
    BOOL    bValid;     /**< cache�е������Ƿ���Ч                       */
} CACHE_LINE_INFO_S;

#endif

#if (OS_HAVE_DCACHE == NO)

/**
 * @ingroup sre_cache
 * ������Cache�����ݻ�д���ڴ档
 */
#define  SRE_DCacheFlush(pAddr, uwSize, bWait)          SRE_OK

/**
 * @ingroup sre_cache
 * ������Cache�е�������Ч��
 */
#define  SRE_DCacheInv(pAddr, uwSize, bWait)            SRE_OK

/**
 * @ingroup sre_cache
 * ������Cache������ݻ�д���ڴ沢��Ч������cache��
 */
#define  SRE_DCacheFlushInv(pAddr, uwSize, bWait)       SRE_OK

/**
 * @ingroup sre_cache
 * �ȴ�DCache������ɡ�
 */
#define  SRE_DCacheWait(VOID)

#else

/**
 * @ingroup  sre_cache
 * @brief ��д����DCACHE
 *
 * @par ����:
 * ˢ������DCACHE, �������������ݻ�д���ڴ�
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��CORTEX_AXƽ̨��SD6181/SD6108 CPU�ˡ�SD6183֧��ˢ������DCACHE����</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief Ԥȡ����CACHE
 *
 * @par ����:
 * ����ַΪpVirtAddr����СΪuwSize���ڴ�����Ԥȡ������cache�У��ɸ��ݲ���bWaitѡ���Ƿ�ȴ���
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧��ԤȡDCACHE����</li>
 * <li>�û�����ĵ�ַ�ռ���cache line������ܳ���dcache��С</li>
 * </ul>
 *
 * @param  pVirtAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize     [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait      [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_DCachePrefetch(VOID * pVirtAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����ָ��cache
 *
 * @par ����:
 * ��������ΪuwCacheType����ַΪpVirtAddr����СΪuwSize��ָ��cache���м���������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧�ּ���ָ��CACHE����</li>
 * <li>��֧������cache����</li>
 * <li>����SD6182ƽ̨��cache�����׵�ַ�ʹ�Сcache line����ʱ��ÿ��4-WAY�����ܼ���3-WAY�������������СΪcache��С���ķ�֮��</li>
 * <li>����SD6182ƽ̨��cache��С������λΪһ��cache line�����ǵ���β��ַ������������ܻ��˷ѵ�����cache line�������ɼ�����С����Ϊ�ķ�֮����cache��С��ȥ����cache line</li>
 * <li>����SD6183ƽ̨��������4���ַ�飬ÿ��8-WAY����ȫ�����ϣ����Ϻ󣬺�����Ӧ���������ݲ�����cache</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] ����#UINT32��cache���ͣ�OS_ICACHE_TYPE��ʾָ��cache,Ŀǰֻ֧��ָ��cache��
 * @param  pVirtAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize       [IN] ����#UINT32���ڴ��Ĵ�С��
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������cache�ռ䷶Χ������
 * @retval #OS_ERRNO_CACHE_NOAREA_LOCK    0x02001106�������������㡣
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103���������Ͳ���ȷ��Ŀǰֻ֧��ICACHE��
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheUnLock
 */
extern UINT32 SRE_CacheLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);

/**
 * @ingroup  sre_cache
 * @brief ����ָ��cache
 *
 * @par ����:
 * ��������ΪuwCacheType����ַΪpVirtAddr����СΪuwSize��ָ��cache���н���������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧�ֽ���ָ��CACHE����</li>
 * <li>��֧������cache����</li>
 * <li>������ӿڱ���һ�£���������СΪ�ķ�֮����cache��С��ȥ��β��ַcache line������������</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] ����#UINT32��cache���ͣ�OS_ICACHE_TYPE��ʾָ��cache,Ŀǰֻ֧��ָ��cache��
 * @param  pVirtAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize       [IN] ����#UINT32���ڴ��Ĵ�С��
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������cache�ռ䷶Χ������
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103���������Ͳ���ȷ��Ŀǰֻ֧��ICACHE��
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheLock
 */
extern UINT32 SRE_CacheUnLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);

/**
 * @ingroup  sre_cache
 * @brief �ȴ�����Cache������ɡ�
 *
 * @par ����:
 * �ȴ�DCache������ɡ�
 *
 * @attention
 * <ul>
 * <li>����Բ��ȴ��ķ�ʽʹ������cache�Ľӿڣ�����ʹ������ӿڱ�֤��ȫ�ԡ�</li>
 * </ul>
 *
 *@param ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))

OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    OS_EMBED_ASM("memw");
}

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    OS_EMBED_ASM("sync");
}

#endif

/**
 * @ingroup  sre_cache
 * @brief ������Cache������ݻ�д���ڴ档
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ��С�
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183��Cortex-AX֧�ָù��ܡ�</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #SRE_CACHE_SIZE_INVALID        0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlush(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����Cache��Ч��
 *
 * @par ����:
 * ��ָ����ַ���������Cache������Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183֧�ָù��ܡ�</li>
 * <li>Cortex-AXоƬ��֧�ָýӿڡ�</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv | SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����Cache��д����Ч��
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ沢��Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183��Cortex-AX֧�ָù��ܡ�</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv
 */
extern UINT32 SRE_DCacheFlushInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#endif /* (OS_HAVE_DCACHE == NO) */

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 * @ingroup  sre_cache
 * @brief ��ȡָ����ַ��cache tag��Ϣ
 *
 * @par ����:
 * ������ΪuwCacheType����ַΪpVirtAddr��cache Tag��Ϣ��ȡ���洢��pstCacheInfo�ṹ���С�
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182/SD6157/SD6181/SD6108ƽ̨֧�ֻ�ȡcache tag��Ϣ����</li>
 * <li>SD6181/SD6108ƽ̨DSP�˲�֧�ֻ�ȡdcache tag��Ϣ����</li>
 * <li>�����ȡ��ָ����ַ��Cache Tag��ϢΪ0��˵���õ�ַ����Cache��</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] ����#UINT32��OS_ICACHE_TYPE��ʾָ��cache��OS_DCACHE_TYPE��ʾ����cache��
 * @param  pVirtAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ������SD6182/SD6157ƽ̨����Cache��ַ��ΧΪ[0x08000000, 0x60000000)������SD6181/SD08ƽ̨����Cache��ַ��ΧΪ[0x10000000, 0x60000000)
 * @param  pstCacheInfo [OUT] ����#CACHE_LINE_INFO_S *����ȡ��tag��Ϣ�ṹ�塣
 *
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103��cache�������벻����
 * @retval #OS_ERRNO_CACHE_TAG_PTR_NULL   0x02001107������Ĵ��Tag��Ϣ��ָ��ΪNULL��
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������ĵ�ַ���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_CacheLineInfoGet(UINT32 uwCacheType, VOID *pVirtAddr, CACHE_LINE_INFO_S *pstCacheInfo);

#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 * @ingroup  sre_cache
 * @brief ����PCCģʽ
 *
 * @par ����:
 * PCC ģʽ����: UNIFY/SPLIT
 *
 * @attention
 * <ul>
 * <li>/li>
 * </ul>
 *
 * @param  enMode        [IN] ����#OS_CACHE_MODE��SPLIT/UNIFYģʽ��
 *
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since
 * @see
 */
extern UINT32 SRE_ICacheModeSet(OS_CACHE_MODE_E enMode);

/**
 * @ingroup  sre_cache
 * @brief ����PCCӲ��Ԥȡ
 *
 * @par ����:
 * PCC ��Ӳ��Ԥȡ��ʹ��ȥʹ�ܣ��Լ�Ԥȡ�Ĳ�������
 *
 * @attention
 * <ul>
 * <li>/li>
 * </ul>
 *
 * @param  uwHwTrdID     [IN] ����#UINT32��0����1��
 * @param  bEnable       [IN] ����#BOOL��1:ʹ�ܣ�0:ȥʹ�ܡ�
 * @param  enHwPfPolicy  [IN] ����#OS_PCC_HWPF_POLICY��4�ֲ��ԡ�
 *
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since
 * @see
 */
extern UINT32 SRE_ICacheHwPfCfg(UINT32 uwHwTrdID, BOOL bEnable, OS_PCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief ����DCCӲ��Ԥȡ
 *
 * @par ����:
 * DCC ��Ӳ��Ԥȡ��ʹ��ȥʹ�ܣ��Լ�Ԥȡ�Ĳ�������
 *
 * @attention
 * <ul>
 * <li>/li>
 * </ul>
 *
 * @param  uwHwTrdID     [IN] ����#UINT32��0����1��
 * @param  bEnable       [IN] ����#BOOL��1:ʹ�ܣ�0:ȥʹ�ܡ�
 * @param  enHwPfPolicy  [IN] ����#OS_DCC_HWPF_POLICY��3�ֲ��ԡ�
 *
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since
 * @see
 */
extern UINT32 SRE_DCacheHwPfCfg(UINT32 uwHwTrdID, BOOL bEnable,  OS_DCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief �첽��ʽ������Cache������ݻ�д���ڴ档
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ��У����������ʱ��Ŀ���ַ������Ϣ֪ͨ��
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱�ڻ�дȫ��������cache</li>
 * <li>ͨ��MSGM�Ľӿ�SRE_QportAddrGet�����Եõ�Ŀ���ָ�����еĵ�ַ</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr  [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData    [IN] ����#UINT32�������͵���Ϣ���ݡ�
 *
 * @retval #SRE_CACHE_SIZE_INVALID        0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup sre_cache
 * @brief �첽��ʽ����Cache��Ч��
 *
 * @par ����:
 * �첽��ʽ��ָ����ַ���������Cache������Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱����Чȫ��������cache</li>
 * <li>ͨ��MSGM�Ľӿ�SRE_QportAddrGet�����Եõ�Ŀ���ָ�����еĵ�ַ</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr  [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData    [IN] ����#UINT32�������͵���Ϣ���ݡ�

 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ICacheInv | SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup  sre_cache
 * @brief �첽��ʽ������Cache��д����Ч��
 *
 * @par ����:
 * �첽��ʽ��ָ����ַ���������Cache���ݻ�д���ڴ沢��Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱�ڻ�д��Чȫ��������cache��</li>
 * <li>ͨ��MSGM�Ľӿ�SRE_QportAddrGet�����Եõ�Ŀ���ָ�����еĵ�ַ��</li>
 * </ul>
 *
 * @param  pAddr      [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize     [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait      [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr  [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData    [IN] ����#UINT32 *�������͵���Ϣ���ݡ�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ICacheInv
 */
extern UINT32 SRE_DCacheFlushInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

#endif

/**
 * @ingroup  sre_cache
 * @brief ��Ч����ָ��Cache
 *
 * @par ����:
 * ������ָ��Cache��Ч��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,SD6183ƽ̨֧����Ч����ָ��Cache���ܡ�</li>
 * <li>SD6182��SD6157ƽָ̨��Cache�����������ýӿ��н������ܡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_ICacheInv
 */
extern VOID SRE_ICacheInvAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief ��Чָ��Cache
 *
 * @par ����:
 * ��ָ����ַ�����ָ��Cache��Ϊ��Ч��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183ƽ̨֧����Чָ��ܡ�</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>Ϊ��ָ֤��cache�����İ�ȫ�ԣ�Icache���������Եȴ���ʽ������bWait������Ч��</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_ADDR_LOCKED    0x02001108����SD6182��SD6157ƽ̨��������Ч��ַ�Ƿ��Ѿ�������
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_ICacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����ָ�����Cache
 *
 * @par ����:
 * ��ָ����ַ�����д����Ч����Cache��Ȼ������Чָ��cache��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183ƽ̨֧�ָ���ָ�����Cache���ܡ�</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��DCACHE����£��˽ӿڵ�ͬSRE_ICacheInv��</li>
 * </ul>
 *
 * @param  pAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait  [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv | SRE_ICacheInv
 */
extern UINT32 SRE_CacheUpdate(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_CACHE_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

