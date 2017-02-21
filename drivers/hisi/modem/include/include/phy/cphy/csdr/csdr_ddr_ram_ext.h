

#ifndef __CSDR_DDR_RAM_EXT_H__
#define __CSDR_DDR_RAM_EXT_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "MemoryMap.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ʱ��׮ */
#define CSDR_DDR_RAM_BASE                   ( GLOBAL_MEM_TDS_TABLE_ADDR )       /* ( 0x5C600000 ) */


/****************************************************************************
 *                     ZSPʹ��DDR�е�ַ�Ķ���                               *
 *                                                                          *
*****************************************************************************/
#define CSDR_CTTF_1X_REQUIRE_LEN            ( 0x4 )
#define CSDR_CTTF_1X_F_DATA_BUFFER_LEN      ( 0xA44 )
#define CSDR_DDR_RAM_FCH_PING_LEN           ( 0x300 )
#define CSDR_DDR_RAM_FCH_PANG_LEN           ( 0x300 )
#define CSDR_DDR_RAM_SCH_PING_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCH_PANG_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCCH_PING_LEN          ( 0x180 )
#define CSDR_DDR_RAM_SCCH_PANG_LEN          ( 0x180 )
#define CSDR_DDR_RAM_DCCH_PING_LEN          ( 0x300 )
#define CSDR_DDR_RAM_DCCH_PANG_LEN          ( 0x300 )
#define CSDR_DDR_RAM_BCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_BCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_PCH_PING_LEN           ( 0x180 )
#define CSDR_DDR_RAM_PCH_PANG_LEN           ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PING_LEN         ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PANG_LEN         ( 0x180 )

/* CTTF��SDR ����decode������encodeͷ����ַ��Ϣ,��Ӧ�ṹCTTF_CSDR_1X_ADDR_INFO_STRU */
#define CSDR_CTTF_1X_REQUIRE_ADDR           ( CSDR_DDR_RAM_BASE + 0x0 )

/* CTTF��SDR ����decode,�������ݶ�Ӧ buffer ��Ӧ�ṹCSDR_CTTF_1X_F_DATA_BUFFER_STRU */
#define CSDR_CTTF_1X_F_DATA_BUFFER_ADDR     (  CSDR_CTTF_1X_REQUIRE_ADDR \
                                             + CSDR_CTTF_1X_REQUIRE_LEN )

/* DPP���FCH�ŵ�LLR���ping��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PING_ADDR          (  CSDR_CTTF_1X_F_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_1X_F_DATA_BUFFER_LEN )

/* DPP���FCH�ŵ�LLR���pang��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PANG_ADDR          (  CSDR_DDR_RAM_FCH_PING_ADDR \
                                             + CSDR_DDR_RAM_FCH_PING_LEN )

/* DPP���SCH�ŵ�LLR���ping��ſռ�, �ܴ�С12288��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCH_PING_ADDR          (  CSDR_DDR_RAM_FCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

/* DPP���SCH�ŵ�LLR���pang��ſռ�, �ܴ�С12288��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCH_PANG_ADDR          (  CSDR_DDR_RAM_SCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCH_PING_LEN )

/* DPP���SCCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCCH_PING_ADDR         (  CSDR_DDR_RAM_SCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCH_PANG_LEN )

/* DPP���SCCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCCH_PANG_ADDR         (  CSDR_DDR_RAM_SCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PING_LEN )

/* DPP���DCCH�ŵ�LLR���ping��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_DCCH_PING_ADDR         (  CSDR_DDR_RAM_SCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PANG_LEN )

/* DPP���DCCH�ŵ�LLR���pang��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_DCCH_PANG_ADDR         (  CSDR_DDR_RAM_DCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PING_LEN )

/* DPP���BCCH�ŵ�LLR���ping��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_BCCH_PING_ADDR         (  CSDR_DDR_RAM_DCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PANG_LEN )

/* DPP���BCCH�ŵ�LLR���pang��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_BCCH_PANG_ADDR         (  CSDR_DDR_RAM_BCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PING_LEN )

/* DPP���CCCH�ŵ�LLR���ping��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_CCCH_PING_ADDR         (  CSDR_DDR_RAM_BCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PANG_LEN )

/* DPP���CCCH�ŵ�LLR���pang��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_CCCH_PANG_ADDR         (  CSDR_DDR_RAM_CCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PING_LEN )

/* DPP���PCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_PCH_PING_ADDR          (  CSDR_DDR_RAM_CCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PANG_LEN )

/* DPP���PCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_PCH_PANG_ADDR          (  CSDR_DDR_RAM_PCH_PING_ADDR \
                                             + CSDR_DDR_RAM_PCH_PING_LEN )

/* DPP���SYNCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SYNCH_PING_ADDR        (  CSDR_DDR_RAM_PCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_PCH_PANG_LEN )

/* DPP���SYNCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SYNCH_PANG_ADDR        (  CSDR_DDR_RAM_SYNCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PING_LEN )

/* CTTF��ENC����ǰ���ݴ�ſռ� */
#define CTTF_CSDR_1X_R_DATA_BUFFER_ADDR     ( CSDR_DDR_RAM_SYNCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PANG_LEN )

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/












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

#endif /* end of csdr_ddr_ram_ext.h */

