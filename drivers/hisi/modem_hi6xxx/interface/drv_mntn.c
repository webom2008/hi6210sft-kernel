/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_mntn.c
  �� �� ��   : ����
  ��    ��   : c61362
  ��������   : 2012��3��2��
  ����޸�   :
  ��������   : ������ϲ������װ�Ľӿڲ�
  �޸���ʷ   :
  1.��    ��   : 2012��3��2��
    ��    ��   : c61362
    �޸�����   : �½�Drvinterface.c

  2.��    ��   : 2013��2��19��
    ��    ��   : ��ϲ 220237
    �޸�����   : ��Drvinterface.c�������

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BSP.h"
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "board_diff.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern int exch_notifier_chain_register(exchCBReg cb);
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*******************************************************************************
 �� �� ��: DRV_EXCH_CUST_FUNC_REG
 ��������: ��������ģ���ṩ����ӿڣ����ϲ�ע��ص������ڸ�λʱ�����ϲ�ָ����Ϣ
 �������: cb �ϲ�ָ���ص��ӿ�
 �������: ��
 �� �� ֵ: 0-��ӳɹ�������-���ʧ��
 ˵��    :  pucData :ָ����¼��Ϣ��ַ����ע�ⲻҪָ��ջ����ʱ���������ѿռ����ݣ�
                     ʹ�����Լ�ά���������ռ�ʹ���꣬�Լ��ͷš�����ȫ�ֱ�����
            aucName :����
            ulDataLen: ���ݳ���

���Լ��:
            ��������С:64K������8��ͨ����ÿ��ͨ����ֵ��󲻵ó���8k.
            ע�ắ������ֵΪ:
                ����:    ulDataLen data���ݳ��ȣ�
                �쳣:    0

����ֵ�б�:
    CUST_REG_OK = 0,                        ��ӳɹ�
    CUST_REG_PARM_NULL,                     ���Ϊ��
    CUST_REG_EXCH_NOT_READY,                EXCHģ����δ��ʼ��
    CUST_REG_EXCH_REBOOT_CONTEXT,           �Ѿ����븴λ����
    CUST_REG_EXCH_QUEUE_NOT_INIT,           ע�������δ��ʼ��
    CUST_REG_EXCH_QUEUE_FULL,               ��������
    CUST_REG_EXCH_ALREADY_IN_QUEUE,         �ظ�ע��
    CUST_REG_EXCH_MUTEX_REJECT,             MUTEX REJECT
    CUST_REG_EXCH_QUEUE_IN_ERR              �����ʧ��

��ͨ������ֵ��λ�������

*******************************************************************************/
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb)
{
    return exch_notifier_chain_register(cb);
}
#endif

/*****************************************************************************
 �� �� ��  : DRV_MEM_READ
 ��������  : ��32λ��Ȳ�ѯ�ڴ棬���4�ֽ����ݡ���ά�ɲ⣬V7�ȴ�׮
 �������  : ulAddress����ѯ��ַ�ռ��ַ����ַ�����ڴ淶Χ�ڣ����򷵻�-1��
 �������  : pulData��ָ���ѯ���ݵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int DRV_MEM_READ (unsigned int ulAddress, unsigned int* pulData)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_MEM_READ(ulAddress, pulData);
#endif

#if (defined BSP_CORE_APP)
    return 0;   /* ��׮ */
#endif
}

void drvShutdown(DRV_SHUTDOWN_REASON_ENUM eReason)
{
    return;   /* ��׮ */
}

/*****************************************************************************
 �� �� ��  : DRV_SHUT_DOWN
 ��������  : ����ػ�
 �������  : ��
 �������  : eReason��        �ػ�ԭ��
 �� �� ֵ  : ��
*****************************************************************************/
void DRV_SHUT_DOWN( DRV_SHUTDOWN_REASON_ENUM eReason )
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#if( FEATURE_POWER_ON_OFF == FEATURE_ON )
    drvShutdown(eReason);
#else
    DRV_PRINTF("Function DRV_SHUT_DOWN unsupport!\n");
#endif
#endif

#if (defined BSP_CORE_APP)
    return;   /* ��׮ */
#endif
}

/*****************************************************************************
* �� �� ��  : DRV_MSP_PROC_REG
*
* ��������  : DRV�ṩ��OM��ע�ắ��
*
* �������  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*****************************************************************************/
void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_MspProcReg(eFuncID, pFunc);
#endif
#if (defined BSP_CORE_APP)
    /*BSP_MspProcReg(eFuncID, pFunc);*/
#endif
}


#if 1 //shenwei shenwei she

/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ��ȡ��ǰ��Ʒ����
 �������   : ��
 �������   :
 �� �� ֵ   :
    PROD_STICK  =0,
    PROD_MOD    =1,
    PROD_E5     =2,
    PROD_CPE    =3,
 ���ú���   :
 ��������   :
 �޸���ʷ   :
 ��    ��   : 2011��4��18��
 ��    ��   : C54299
 �޸�����   : �����ɺ���

*************************************************/
BSP_U32 BSP_MNTN_ProductTypeGet(void)
{
   return 0;/*stub*/
}
#endif

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GETSDSTATUS
 ��������  : ����SD����λ״̬
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   1��λ
            0����λ

*****************************************************************************/
int BSP_SDMMC_GetSDStatus(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* �� �� ��  : BSP_OM_GetChipType
*
* ��������  : ��ȡоƬ����,HSO����ʹ��
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSPоƬ����ö��
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_CHIP_TYPE_E BSP_OM_GetChipType(void)
{
    /*������Ҫ�ͱ���hids�˶�*/
    return V8R1_PILOT_CHIP;
}

/*****************************************************************************
* �� �� ��  : BSP_TFUP_CompleteDeal
* ��������  : װ��ʹ��,TLʹ��
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
BSP_VOID BSP_TFUP_CompleteDeal(void)
{
   return ; /* ��׮ */
}

/*****************************************************************************
* �� �� ��  : BSP_TBAT_Read
* ��������  : װ��ʹ��,TLʹ��
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
BSP_S32 BSP_TBAT_Read(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return  0; /* ��׮ */
}

/*****************************************************************************
* �� �� ��  : BSP_TBAT_Write
* ��������  : װ��ʹ��,TLʹ��
* �������  :
* �������  :
* �� �� ֵ  :
*****************************************************************************/
BSP_S32 BSP_TBAT_Write(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return 0; /* ��׮ */
}

/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetSoftwareVer
* ��������  : ��ȡ����汾��
* �������  : BSP_S8 *str   :�ַ���������
*             BSP_S32 len   :�ַ�������
* �������  : BSP_S8 *str   :�ַ���������
* �� �� ֵ  : BSP_ERROR     :��������Ƿ�
*             ����          :�����ַ�������
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetSoftwareVer(BSP_CHAR *str, BSP_U32 len)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_MNTN_MemVersionCtrl((signed char*)str, (unsigned char)len, (unsigned char)VER_SOFTWARE, (unsigned char)VERIONREADMODE);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* �� �� ��  : BSP_BBPDMA_DrxBakReg
* ��������  :
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
BSP_S32 BSP_BBPDMA_DrxBakReg(void)
{
    return  0; /* ��׮ */
}

/*****************************************************************************
* �� �� ��  : BSP_CPU_GetTotalUtilize
* ��������  :
* �������  :
* �������  :
* �� �� ֵ  :
*****************************************************************************/
BSP_U32 BSP_CPU_GetTotalUtilize(void)
{
    return  0; /* ��׮ */
}

/*****************************************************************************
* �� �� ��  : nand_isbad
* ��������  :
* �������  :
* �������  :
* �� �� ֵ  :
*****************************************************************************/
BSP_U32 nand_isbad(BSP_U32 blockID, BSP_U32 *flag)
{
    return 0; /* ��׮,����NAND_OK */
}

/*****************************************************************************
* �� �� ��  : BSP_PM_SetWakeSrc
* ��������  : ��̬���û���Դ
* �������  : eWakeSrc ����Դö��ֵ
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID BSP_PM_SetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src)
{
    /*V9R1��׮����*/
    return;
}

/*****************************************************************************
* �� �� ��  : BSP_PM_UnsetWakeSrc
* ��������  : ��̬���û���Դ
* �������  : eWakeSrc ����Դö��ֵ
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID BSP_PM_UnsetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src)
{
    /*V9R1��׮����*/
    return;
}

/********************************************************************************************************
 �� �� ��  : BSP_FS_GetDskspc
 ��������  : �õ��ļ�ϵͳ�ռ䡣(Modem Core,/yaffs0)
 �������  : path���ļ�ϵͳ·����
 �������  : DskSpc���ܿռ䡣
                           UsdSpc���ù��ռ䡣
                           VldSpc�����пռ䡣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
int BSP_FS_GetDskspc(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}

/* stub for v8r1 link */
#if defined (CHIP_BB_HI6210)
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int uslength)
{
    return BSP_ERROR;
}

int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback)
{
    return BSP_ERROR;
}
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

