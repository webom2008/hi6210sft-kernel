

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_MEM_REMAP_H__
#define __DRV_MEM_REMAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* DDR�и����ڴ�ε����� */
typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_HUTAF,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_TDS_LH2,
    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;


/* AXI�и����ڴ�ε����� */
typedef enum tagBSP_AXI_SECT_TYPE_E
{
    BSP_AXI_SECT_TYPE_ACORE_DEEPSLEEP = 0x0,
    BSP_AXI_SECT_TYPE_FLASH_SEM,
    BSP_AXI_SECT_TYPE_IFC,
    BSP_AXI_SECT_TYPE_ICC,
    BSP_AXI_SECT_TYPE_MEMMGR_FLAG,
    BSP_AXI_SECT_TYPE_DYNAMIC,
    BSP_AXI_SECT_TYPE_SOFT_FLAG,
    BSP_AXI_SECT_TYPE_IPF,
    BSP_AXI_SECT_TYPE_TEMPERATURE,
    BSP_AXI_SECT_TYPE_ONOFF,
    BSP_AXI_SECT_TYPE_DICC,
    BSP_AXI_SECT_TYPE_HIFI,
    BSP_AXI_SECT_TYPE_DDR_CAPACITY,
    BSP_AXI_SECT_TYPE_PTABLE,
    BSP_AXI_SECT_TYPE_RESERVE,
    BSP_AXI_SECT_TYPE_DLOAD_AUTOINSTALL,
    BSP_AXI_SECT_TYPE_DLOAD,
    BSP_AXI_SECT_TYPE_CCORE_DEEPSLEEP ,
    BSP_AXI_SECT_TYPE_TTF_BBP,
    BSP_AXI_SECT_TYPE_BUTTOM
}BSP_AXI_SECT_TYPE_E;


/* �ڴ������ */
typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;


/* ������ʵ��ַ�Ƿ���ͬ��ö�� */
typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;

/* ����������Ҫ��ѯ��MEM���� */
typedef enum tagBSP_DDR_TYPE_E
{
    BSP_DDR_TYPE_DDR_GU = 0x0,          /*DDR:GUԤ��*/
    BSP_DDR_TYPE_DDR_TLPHY_IMAGE,       /*DDR:TL DSP ����*/
    BSP_DDR_TYPE_DDR_LPHY_SDR,          /*DDR:SDRС������*/
    BSP_DDR_TYPE_DDR_TLPHY_LCS,         /*DDR:TL DSP LCS*/
    BSP_DDR_TYPE_DDR_TLPHY_BANDNV,      /*DDR:TL DSP BAND*/
    BSP_DDR_TYPE_DDR_TPHY_TABLE,        /*DDR:TL TDS TABLE*/
    BSP_DDR_TYPE_DDR_HIFI,              /*DDR:HIFI*/
    BSP_DDR_TYPE_SRAM_TLPHY,            /*SRAM:TL DSP*/
    BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG,   /*SRAM:TL DSP˯�߻��ѱ��*/
    BSP_DDR_TYPE_SHM_TEMPERATURE,       /*�����ڴ�:�±�*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,   /*�����ڴ�:BBE16->HIFI����ͷ*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,   /*�����ڴ�:HIFI->BBE16����ͷ*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,  /*�����ڴ�:BBE16->HIFI�������*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,  /*�����ڴ�:HIFI->BBE16�������*/
    BSP_DDR_TYPE_SHM_TIMESTAMP,         /*DDR:LDSP LP*/
    BSP_DDR_TYPE_SHM_AFC_TEMPCOMP,      /*LPHY�±���Ƶƫ*/
    BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,   /*LPHY���䱣����־*/

    BSP_DDR_TYPE_BUTTOM
}BSP_DDR_TYPE_E;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
/* DDR�ڴ�εĲ�ѯ�ṹ */
typedef struct tagBSP_DDR_SECT_QUERY
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    BSP_U32                 ulSectSize;
}BSP_DDR_SECT_QUERY;


/* DDR�ڴ�ε���ϸ��Ϣ */
typedef struct tagBSP_DDR_SECT_INFO
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    BSP_VOID *             pSectVirtAddr;
    BSP_VOID *             pSectPhysAddr;
    BSP_U32                ulSectSize;
}BSP_DDR_SECT_INFO;


/* AXI�ڴ�ε���ϸ��Ϣ */
typedef struct tagBSP_AXI_SECT_INFO
{
    BSP_VOID *             pSectVirtAddr;
    BSP_VOID *             pSectPhysAddr;
    BSP_AXI_SECT_TYPE_E    enSectType;
    BSP_U32                ulSectSize;
}BSP_AXI_SECT_INFO;

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
/* MEMORY ADDR INFO */
typedef struct BSP_MEMADDR_INFO_S
{
    BSP_DDR_TYPE_E         mem_type;
    BSP_U32                mem_base;
    BSP_U32                mem_size;
}BSP_MEMADDR_INFO;
#endif

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
/*****************************************************************************
 �� �� ��  : BSP_DDR_GetSectInfo
 ��������  : DDR�ڴ�β�ѯ�ӿ�
 �������  : pstSectQuery: ��Ҫ��ѯ���ڴ�����͡�����
 �������  : pstSectInfo:  ��ѯ�����ڴ����Ϣ
 ����ֵ    ��BSP_OK/BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_DDR_GetSectInfo(BSP_DDR_SECT_QUERY *pstSectQuery, BSP_DDR_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_DDR_ADDR(pstSectQuery, pstSectInfo) BSP_DDR_GetSectInfo(pstSectQuery, pstSectInfo)

/*****************************************************************************
 �� �� ��  : BSP_AXI_GetSectInfo
 ��������  : AXI�ڴ�β�ѯ�ӿ�
 �������  : enSectType: ��Ҫ��ѯ���ڴ������
 �������  : pstSectInfo:  ��ѯ�����ڴ����Ϣ
 ����ֵ    ��BSP_OK/BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_AXI_GetSectInfo(BSP_AXI_SECT_TYPE_E enSectType, BSP_AXI_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_AXI_ADDR(enSectType, pstSectInfo) BSP_AXI_GetSectInfo(enSectType, pstSectInfo)

/*****************************************************************************
 �� �� ��  : BSP_GetMemAddrSize
 ��������  : ��ȡmem��ַ�ʹ�С��Ϣ
 �������  : enMemType: ��Ҫ��ѯ��mem����
 �������  : addr ��ַ
             size ��С
 ����ֵ    ��BSP_OK    ��ѯ�ɹ�
             BSP_ERROR ��ѯʧ��
*****************************************************************************/
BSP_S32 BSP_GetMemAddrSize(BSP_DDR_TYPE_E enDdrType, BSP_U32 *addr, BSP_U32 *size);
#define DRV_GET_MEM_ADDR_SIZE(enDdrType, pAddr, pSize)  BSP_GetMemAddrSize(enDdrType, pAddr, pSize)

/*****************************************************************************
 �� �� ��  : DRV_DDR_VIRT_TO_PHY
 ��������  : DDR�ڴ����ַ��ʵ��ַת��
 �������  : pVirtAddr�����ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
BSP_VOID * DRV_DDR_VIRT_TO_PHY(BSP_VOID * pVirtAddr);

/*****************************************************************************
 �� �� ��  : DRV_DDR_PHY_TO_VIRT
 ��������  : DDR�ڴ����ַ��ʵ��ַת��
 �������  : pPhyAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
BSP_VOID * DRV_DDR_PHY_TO_VIRT(BSP_VOID * pPhyAddr);


/*****************************************************************************
 �� �� ��  : TTF_VIRT_TO_PHY
 ��������  : TTF�ڴ����ַ��ʵ��ַת��
 �������  : pVirtAddr���ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
extern BSP_VOID * TTF_VIRT_TO_PHY(BSP_VOID * pVirtAddr);

/*****************************************************************************
 �� �� ��  : TTF_PHY_TO_VIRT
 ��������  : TTF�ڴ����ַ��ʵ��ַת��
 �������  : pPhyAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern BSP_VOID * TTF_PHY_TO_VIRT(BSP_VOID * pPhyAddr);

/*****************************************************************************
 �� �� ��  : IPF_VIRT_TO_PHY
 ��������  : IPF�Ĵ������ַ��ʵ��ַת��
 �������  : pVirtAddr�����ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
extern BSP_VOID *IPF_VIRT_TO_PHY(BSP_VOID * pVirtAddr);

/*****************************************************************************
 �� �� ��  : IPF_PHY_TO_VIRT
 ��������  : IPF�Ĵ������ַ��ʵ��ַת��
 �������  : pPhyAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern BSP_VOID * IPF_PHY_TO_VIRT(BSP_VOID * pPhyAddr);

/*****************************************************************************
 �� �� ��  : DRV_AXI_VIRT_TO_PHY
 ��������  : AXI�����ַ��ʵ��ַת��
 �������  : pVirtAddr�����ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern BSP_VOID * DRV_AXI_VIRT_TO_PHY(BSP_VOID * pVirtAddr);

/*****************************************************************************
 �� �� ��  : DRV_AXI_PHY_TO_VIRT
 ��������  : AXI��ʵ��ַ�����ַת��
 �������  : pPhyAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern BSP_VOID * DRV_AXI_PHY_TO_VIRT(BSP_VOID * pPhyAddr);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_mem_remap.h */

