/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  Drvinterface.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"Drvinterface.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/
/*#include <vxWorks.h>
#include "BSP_GLOBAL.h"
#include "BSP_VERSION.h"*/


#ifndef __DRV_INTERFACE_H__
#define __DRV_INTERFACE_H__

#include "TTFMemInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************GLOBAL BEGIN*****************************/
/* �����������Ͷ��� */
#ifndef _WIN32_COMPILE
typedef signed long long    BSP_S64;
#else
typedef double              BSP_S64;
#endif
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;

#ifndef _WIN32_COMPILE
typedef unsigned long long  BSP_U64;
#else
typedef double              BSP_U64;
#endif
typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;

typedef int                 BSP_BOOL;
typedef void                BSP_VOID;
typedef int                 BSP_STATUS;

#ifndef BSP_VOID
#define BSP_VOID void
#endif

#ifndef _WIN32_COMPILE
typedef signed long long*   BSP_PS64;
#else
typedef double*             BSP_PS64;
#endif
typedef signed int*         BSP_PS32;
typedef signed short*       BSP_PS16;
typedef signed char*        BSP_PS8;

#ifndef _WIN32_COMPILE
typedef unsigned long long* BSP_PU64;
#else
typedef double*             BSP_PU64;
#endif
typedef unsigned int*       BSP_PU32;
typedef unsigned short*     BSP_PU16;
typedef unsigned char*      BSP_PU8;

typedef int*                BSP_PBOOL;
typedef void*               BSP_PVOID;
typedef int*                BSP_PSTATUS;

#ifndef BSP_CONST
#define BSP_CONST               const
#endif

#ifndef BSP_FALSE
#define BSP_FALSE                0
#endif

#ifndef BSP_TRUE
#define BSP_TRUE                 1
#endif

#ifndef BSP_NULL
#define BSP_NULL                 (void*)0
#endif

#ifndef BSP_OK
 #define BSP_OK (0)
#endif

#ifndef BSP_ERROR
 #define BSP_ERROR (-1)
#endif


#ifndef INLINE
#define INLINE __inline__
#endif
#define TTFA9_DRAM_SHARE_PHYS           (0x37000000)
#define TTFA9_DRAM_SHARE_VIRT           (0xF3400000)

#ifndef __UT_CENTER__
#ifdef DMT
#define TTF_VIRT_TO_PHY(var)  (var)
#define TTF_PHY_TO_VIRT(var)  (var)
#else
#define TTF_VIRT_TO_PHY(var)  (((unsigned int)(var) - TTFA9_DRAM_SHARE_VIRT) + TTFA9_DRAM_SHARE_PHYS)
#define TTF_PHY_TO_VIRT(var)  (((unsigned int)(var) - TTFA9_DRAM_SHARE_PHYS) + TTFA9_DRAM_SHARE_VIRT)
#endif
#else
#define TTF_VIRT_TO_PHY(var)  (var)
#define TTF_PHY_TO_VIRT(var)  (var)
#endif

#define PWRCTRL_GET_SUCCESS         (0x00)
#define PWRCTRL_GET_PARAINVALID     (0x01)
#define PWRCTRL_ONORLOCK            (0x10)
#define PWRCTRL_OFFORUNLOCK         (0x20)


/* ģ�鶨�� */
typedef enum tagBSP_MODULE_E
{
    BSP_MODU_NANDF = 0x0, /* 0x0 */
    BSP_MODU_TIMER, /* 0x1 */
    BSP_MODU_VIC,   /* 0x2 */
    BSP_MODU_UART,  /* 0x3 */
    BSP_MODU_YAFFS, /* 0x4 */
    BSP_MODU_ETH,   /* 0x5 */
    BSP_MODU_DMAC,  /* 0x6 */
    BSP_MODU_SPI,   /* 0x7 */
    BSP_MODU_GPIO,  /* 0x8 */
    BSP_MODU_WDT,   /* 0x9 */
    BSP_MODU_SCI,   /* 0xA */
    BSP_MODU_USB,   /* 0xB */
    BSP_MODU_DRX,   /* 0xC */
    BSP_MODU_SDIO,  /* 0xD */
    BSP_MODU_FTP,   /* 0xE */
    BSP_MODU_GMAC,	  /* 0xF */
    BSP_MODU_SEEKER,	/* 0x10 */
    BSP_MODU_UPGRADE,	/* 0x11 */
    BSP_MODU_AXI,	/* 0x12 */
    BSP_MODU_NET,	/* 0x13 */
    BSP_MODU_USB_ACM,	/* 0x14 */
    BSP_MODU_USB_NCM,	/* 0x15 */
    BSP_MODU_AXI_MONITOR,
    BSP_MODU_IFC,
    BSP_MODU_ICC,
    BSP_MODU_IPF,
    BSP_MODU_ACC,	/* 0x1A */
    BSP_MODU_BBP,
    BSP_MODU_MEM,
    BSP_MODU_UDI,
    BSP_MODU_DLOAD,
    BSP_MODU_SOCP,
    BSP_MODU_IFCP,  /* 0x20 */
    BSP_MODU_PWRCTRL,
    BSP_MODU_SERIAL_UPGRADE,
    BSP_MODU_SYNC,
    BSP_MODU_IPC,
    BSP_MODU_MNTN,
    BSP_MODU_ALL,   /* �������е�ģ�� */
    BSP_MODU_MAX    /* �߽�ֵ */
} BSP_MODULE_E;

/*
 * ������궨��
 */
#define BSP_ERR_MODULE_OFFSET (0x1000)    /* ��ֹ��ϵͳ�Ĵ������ص� */
#define BSP_DEF_ERR( mod, errid) \
    (((mod + BSP_ERR_MODULE_OFFSET) << 16) | (errid))

/* ͨ�ô����룬��0x1001��ʼ */
#define BSP_ERR_COMMON (0x1000)
#define BSP_ERR_MODULE_NOT_INITED (BSP_ERR_COMMON + 1)
#define BSP_ERR_NULL_PTR (BSP_ERR_COMMON + 2)
#define BSP_ERR_INVALID_PARA (BSP_ERR_COMMON + 3)
#define BSP_ERR_RETRY_TIMEOUT (BSP_ERR_COMMON + 4)
#define BSP_ERR_BUF_ALLOC_FAILED (BSP_ERR_COMMON + 5)
#define BSP_ERR_BUF_FREE_FAILED (BSP_ERR_COMMON + 6)

/* ��ģ��ר�ô����룬��0x1��ʼ  */
#define BSP_ERR_SPECIAL (0x0)

typedef enum{
     BSP_MODEM_CORE         = 0,
     BSP_APP_CORE
}BSP_CORE_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP
}BSP_CHIP_TYPE_E;

/*
 * ���Ժ궨��
 */

/* ��ӡ������ */
typedef enum tagBSP_LOG_LEVEL_E
{
    BSP_LOG_LEVEL_DEBUG = 0,  /* 0x0:debug-level                                  */
    BSP_LOG_LEVEL_INFO,      /* 0x1:informational                                */
    BSP_LOG_LEVEL_NOTICE,     /* 0x2:normal but significant condition             */
    BSP_LOG_LEVEL_WARNING,    /* 0x3:warning conditions                           */
    BSP_LOG_LEVEL_ERROR,      /* 0x4:error conditions                             */
    BSP_LOG_LEVEL_CRIT,       /* 0x5:critical conditions                          */
    BSP_LOG_LEVEL_ALERT,      /* 0x6:action must be taken immediately             */
    BSP_LOG_LEVEL_FATAL,      /* 0x7:just for compatibility with previous version */
    BSP_LOG_LEVEL_MAX         /* �߽�ֵ */
} BSP_LOG_LEVEL_E;

#undef __BSP_DEBUG__


#ifdef __BSP_DEBUG__
#include <logLib.h>

#define BSP_ASSERT(expr) \
{\
    if (!(expr)) { \
        logMsg("ASSERT failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
               (BSP_S32)__FILE__, (BSP_S32)__FUNCTION__, (BSP_S32)__LINE__, (BSP_S32) # expr, (BSP_S32)5, (BSP_S32)6); \
    return BSP_ERROR;\
    } \
}

#define BSP_ASSERT_HALT (expr) \
{\
    if (!(expr)) { \
        logMsg("ASSERT failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
               (BSP_S32)__FILE__, (BSP_S32)__FUNCTION__, (BSP_S32)__LINE__, (BSP_S32) # expr, (BSP_S32)5, (BSP_S32)6); \
        for (;;) ;\
    } \
}


#else
#define BSP_ASSERT(expr)
#define BSP_ASSERT_HALT(expr)
#endif

/*
 * �Ĵ��������궨��
 */
#define BSP_REG(base, reg) (*(volatile BSP_U32 *)((BSP_U32)base + (reg)))
#define BSP_REG8(base, reg) (*(volatile BSP_U8 *)((BSP_U32)base + (reg)))
#define BSP_REG16(base, reg) (*(volatile BSP_U16 *)((BSP_U32)base + (reg)))

/* ��var��[pos, pos + bits-1]��������,  pos��0��ʼ���
   e.g BDOM_CLR_BITS(var, 4, 2) ��ʾ��Bit5~4���� */
#define BSP_REG_CLRBITS(base, reg, pos, bits) (BSP_REG(base, reg) &= ~((((BSP_U32)1 << (bits)) - 1) << (pos)))

/* ��var��[pos, pos + bits-1]��������Ϊval,  pos��0��ʼ���
   e.g BDOM_SET_BITS(var, 4, 2, 2) ��ʾ��Bit5~4����Ϊb'10 */
#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((BSP_U32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((BSP_U32)((val) & (((BSP_U32)1 << (bits)) - 1)) << (pos)))

/* ��ȡvar��[pos, pos + bits-1]����ֵ,  pos��0��ʼ��� */
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((BSP_U32)1 << (bits)) - 1))

#define BSP_REG_READ(base, reg, result) \
    ((result) = BSP_REG(base, reg))

#define BSP_REG_WRITE(base, reg, data) \
    (BSP_REG(base, reg) = (data))

#define BSP_REG_WRITEBITS(base, reg, data) \
            (BSP_REG(base, reg) |= (data))
#define BSP_REG8_READ(base, reg, result) \
    ((result) = BSP_REG8(base, reg))

#define BSP_REG16_READ(base, reg, result) \
    ((result) = BSP_REG16(base, reg))

#define BSP_REG_MODIFY(base, reg, clrmsk, setmsk) \
    (BSP_REG(base, reg) = ((BSP_REG(base, reg) & ~clrmsk) | setmsk))

/* ���������Сֵ */
#ifndef BSP_MIN
 #define BSP_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef BSP_MAX
 #define BSP_MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

//VOID BSP_TRACE(BSP_LOG_LEVEL_E enLogLevel, BSP_U32 enLogModule, const char *fmt, ...);

BSP_VOID BSP_ClearLogModule( BSP_MODULE_E enModule );
BSP_VOID BSP_SetLogModule( BSP_MODULE_E enModule );
BSP_U32  BSP_GetLogModule(BSP_VOID);
BSP_VOID BSP_SetLogLevel(BSP_LOG_LEVEL_E enLogLevel);
BSP_U32  BSP_GetLogLevel(BSP_VOID);
BSP_VOID BSP_SetPrintPos( BSP_BOOL bPrintPos);
BSP_BOOL BSP_GetPrintPos(BSP_VOID);

BSP_S32  BSP_ErrnoGet (BSP_VOID);
BSP_S32  BSP_TaskErrnoGet (BSP_S32 taskId);
BSP_S32  BSP_ErrnoSet (BSP_S32 s32ErrorValue);
BSP_S32  BSP_TaskErrnoSet (BSP_S32 s32TaskId, BSP_S32 s32ErrorValue);
BSP_VOID BSPLogHelp(BSP_VOID);


#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

typedef struct  tagUE_SW_BUILD_VER_INFO_STRU
{
    BSP_U16 ulVVerNo;        // V����
    BSP_U16 ulRVerNo;        // R����
    BSP_U16 ulCVerNo;        // C����
    BSP_U16 ulBVerNo;        // B����
    BSP_U16 ulSpcNo;         // SPC����
    BSP_U16 ulCustomVer;     // �ͻ��趨�Ʋ���, ���Ӳ���ӿڵ�8bit PCB��,��8bitHW��
    BSP_U32 ulProductNo;     // such as porting,CPE, ...
    BSP_S8 acBuildDate[BUILD_DATE_LEN];  // build����,
    BSP_S8 acBuildTime[BUILD_TIME_LEN];  // buildʱ��
} UE_SW_BUILD_VER_INFO_STRU; // �ڲ��汾
/*************************GLOBAL END*****************************/

/*************************TRACE BEGIN*****************************/
void BSP_traceProcessInit();

extern unsigned int g_u32taskTraceBaseAddr;
extern unsigned int g_u32intTraceBaseAddr;

#ifdef BSP_DEBUG
#define PROCESS_TRACE
#endif

#ifdef  PROCESS_TRACE
#define PROCESS_ENTER(pADDRESS) \
    do { \
        *((unsigned int *)pADDRESS) = 1; \
    } while (0)

#define PROCESS_EXIT(pADDRESS) \
    do { \
        *((unsigned int *)pADDRESS) = 0; \
    } while (0)

#else
#define PROCESS_ENTER(pADDRESS)  do { } while (0)
#define PROCESS_EXIT(pADDRESS)   do { } while (0)
#endif

/* �����Ӧ��¼��ַ����*/
#define BSP_IPCOM_SYSL_TRACE   (g_u32taskTraceBaseAddr + 0x0 ) /*ipcom_sysl*/
#define BSP_IPCOM_TICK_TRACE   (g_u32taskTraceBaseAddr + 0x04) /*ipcom_tick*/
#define BSP_IPCOM_TELN_TRACE   (g_u32taskTraceBaseAddr + 0x08) /*ipcom_teln*/
#define BSP_SDIO_MONIT_TRACE   (g_u32taskTraceBaseAddr + 0x0c) /*tSdioMonit*/
#define BSP_SDIO_INT_TRACE     (g_u32taskTraceBaseAddr + 0x10) /*tSdioIntrP*/
#define BSP_PMU_INT_TRACE      (g_u32taskTraceBaseAddr + 0x14) /*tPmuIntTas*/
#define BSP_SCISYSNC_TRACE     (g_u32taskTraceBaseAddr + 0x18) /*tSCISYSNC */
#define PS_VOS_TIMER_TRACE     (g_u32taskTraceBaseAddr + 0x1c) /*VOS_TIMER */
#define PS_RTC_TIMER_TRACE     (g_u32taskTraceBaseAddr + 0x20) /*RTC_TIMER */
#define PS_L2_UL_TRACE         (g_u32taskTraceBaseAddr + 0x24) /*MACRLCUL_F*/
#define PS_HPA_TRACE           (g_u32taskTraceBaseAddr + 0x28) /*HPA_FID   */
#define BSP_NET0_TRACE         (g_u32taskTraceBaseAddr + 0x2c) /*tNet0     */
#define BSP_USB_CONTROL_TRACE  (g_u32taskTraceBaseAddr + 0x30) /*uw_Control*/
#define BSP_USB_CORE_TRACE     (g_u32taskTraceBaseAddr + 0x34) /*uw_Core   */
#define MSP_TID005_TRACE       (g_u32taskTraceBaseAddr + 0x38) /*tid005    */
#define PS_L2_DL_TRACE         (g_u32taskTraceBaseAddr + 0x3c) /*MACRLCDL_F*/
#define BSP_USB_CLASS_TRACE    (g_u32taskTraceBaseAddr + 0x40) /*uw_Class  */
#define MSP_SYM_TRACE          (g_u32taskTraceBaseAddr + 0x44) /*mspSYM    */
#define MSP_MUX_TRACE          (g_u32taskTraceBaseAddr + 0x48) /*mspMUX    */
#define MSP_TID006_TRACE       (g_u32taskTraceBaseAddr + 0x4c) /*tid006    */
#define MSP_DIAG_TRACE         (g_u32taskTraceBaseAddr + 0x50) /*mspDIAG   */
#define MSP_SIMM_TRACE         (g_u32taskTraceBaseAddr + 0x54) /*mspSIMM   */
#define MSP_TID013_TRACE       (g_u32taskTraceBaseAddr + 0x58) /*tid013    */
#define MSP_FTM_TRACE          (g_u32taskTraceBaseAddr + 0x5c) /*mspFTM    */
#define MSP_NVIM_TRACE         (g_u32taskTraceBaseAddr + 0x60) /*mspNVIM   */
#define MSP_RAI_TRACE          (g_u32taskTraceBaseAddr + 0x64) /*mspRAI    */
#define BSP_SCIRX_TRACE        (g_u32taskTraceBaseAddr + 0x68) /*tSCIRxTask*/
#define PS_RRC_TRACE           (g_u32taskTraceBaseAddr + 0x6c) /*RRC_FID   */
#define MSP_MUXOM_TRACE        (g_u32taskTraceBaseAddr + 0x70) /*PS_FID_COM*/
#define PS_NAS_MM_TRACE        (g_u32taskTraceBaseAddr + 0x74) /*MM_FID    */
#define PS_NAS_CM_TRACE        (g_u32taskTraceBaseAddr + 0x78) /*CM_FID    */
#define MSP_L4A_TRACE          (g_u32taskTraceBaseAddr + 0x7c) /*mspL4A    */
#define MSP_AT_TRACE           (g_u32taskTraceBaseAddr + 0x80) /*mspAT     */
#define MSP_DRA_TRACE          (g_u32taskTraceBaseAddr + 0x84) /*mspDRA    */
#define MSP_TID012_TRACE       (g_u32taskTraceBaseAddr + 0x88) /*tid012    */
#define PS_OM_TRACE            (g_u32taskTraceBaseAddr + 0x8c) /*OM_FID    */
#define BSP_WATCHDOG_TRACE     (g_u32taskTraceBaseAddr + 0x90) /*WatchDog  */
#define BSP_IPCOM_EGD_TRACE    (g_u32taskTraceBaseAddr + 0x94) /*ipcom_egd */
#define BSP_ARM_SLEEP0_TRACE   (g_u32taskTraceBaseAddr + 0x98) /*tIdletask*/
#define BSP_SDIO_SVC_TRACE     (g_u32taskTraceBaseAddr + 0x9c) /*taskSdioSvc*/
/*modify by lishangfeng for TaskTrace Begin */
#define PS_ERROR_TASK_TRACE    (g_u32taskTraceBaseAddr + 0xa0) /* ���������쳣����ʱ�ļ�¼ */
/*modify by lishangfeng for TaskTrace End */


/* �ж϶�Ӧ��ַ����*/
#define BSP_WDT_TRACE              (g_u32intTraceBaseAddr + 0x0 ) /*WDT�ж�                      */
#define BSP_SWINT_TRACE            (g_u32intTraceBaseAddr + 0x04) /*SoftWare INT                 */
#define BSP_COMMRX_TRACE           (g_u32intTraceBaseAddr + 0x08) /*COMMRX�ж�                   */
#define BSP_COMMTX_TRACE           (g_u32intTraceBaseAddr + 0x0c) /*COMMTX�ж�                   */
#define BSP_TIMER0_TRACE           (g_u32intTraceBaseAddr + 0x10) /*Timer0�ж�                   */
#define BSP_TIMER123_TRACE         (g_u32intTraceBaseAddr + 0x14) /*Timer123�ж�                 */
#define BSP_SCI_TRACE              (g_u32intTraceBaseAddr + 0x18) /*SCI �ж�                     */
#define BSP_DMAC_TRACE             (g_u32intTraceBaseAddr + 0x1c) /*DMAC                         */
#define BSP_CIPHER_TRACE           (g_u32intTraceBaseAddr + 0x20) /*CIPHER                       */
#define BSP_USBOTG_TRACE           (g_u32intTraceBaseAddr + 0x24) /*USB OTG                      */
#define BSP_SSP012_TRACE           (g_u32intTraceBaseAddr + 0x28) /*SSP0 |SSP1|SSP2              */
#define BSP_UART01_TRACE           (g_u32intTraceBaseAddr + 0x2c) /*UART0| UART1                 */
#define BSP_RTC_TRACE              (g_u32intTraceBaseAddr + 0x30) /*RTC                          */
#define BSP_NANDC_TRACE            (g_u32intTraceBaseAddr + 0x34) /*NANDC                        */
#define BSP_SDMMC_TRACE            (g_u32intTraceBaseAddr + 0x38) /*SD/MMC ���                  */
#define BSP_I2C_TRACE              (g_u32intTraceBaseAddr + 0x3c) /*I2C                          */
#define BSP_FE_TRACE               (g_u32intTraceBaseAddr + 0x40) /*FE                           */
#define BSP_GPIO3_TRACE            (g_u32intTraceBaseAddr + 0x44) /*GPIO3����ж�                */
#define BSP_GPIO012_TRACE          (g_u32intTraceBaseAddr + 0x48) /*GPIO0/1/2����ж�            */
#define BSP_RSA_DES_SHA_TRACE      (g_u32intTraceBaseAddr + 0x4c) /*rsa_int | des_int | sha_int  */
#define BSP_IPCM2ARM_TRACE         (g_u32intTraceBaseAddr + 0x50) /*IPCM2ARM�ж�                 */
#define BSP_PLUSEM0_TRACE          (g_u32intTraceBaseAddr + 0x54) /*PIU_SEM_0                    */
#define BSP_PLUSEM1_TRACE          (g_u32intTraceBaseAddr + 0x58) /*PIU_SEM_1                    */
#define BSP_PLUSEM2_TRACE          (g_u32intTraceBaseAddr + 0x5c) /*PIU_SEM_2                    */
#define BSP_PLUCR_TRACE            (g_u32intTraceBaseAddr + 0x60) /*PIU_CR                       */
#define BSP_PMU01_TRACE            (g_u32intTraceBaseAddr + 0x64) /*pmu0_irq_int_n|pmu1_irq_int_n*/
#define BSP_RESERVED_TRACE         (g_u32intTraceBaseAddr + 0x68) /*����                         */
#define BSP_BBP_TIMESWITCH_TRACE   (g_u32intTraceBaseAddr + 0x6c) /*BBPʱ���л�                  */
#define BSP_BBP_WAKEUP_TRACE       (g_u32intTraceBaseAddr + 0x70) /*BBP ����                     */
#define BSP_BBP_TRACE              (g_u32intTraceBaseAddr + 0x74) /*BBP                          */
#define BSP_BBP_SUBFRAME_TRACE     (g_u32intTraceBaseAddr + 0x78) /*BBP��λ�ж�                  */
#define BSP_BBP_BACKUP_TRACE       (g_u32intTraceBaseAddr + 0x7c) /*BBP ���ݺϲ��ж�             */

#ifndef UINT8
#define UINT8	unsigned char
#endif
/*************************TRACE END*****************************/


/*************************CLK BEGIN*****************************/

#define BSP_ERR_CLK_NO_FREE_CLK         BSP_DEF_ERR(BSP_MODU_TIMER,(BSP_ERR_SPECIAL + 1))
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Alloc
*
* ��������  : �����û�ʱ��ID
*
* �������  : BSP_S32 * ps32UsrClkId
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_U32 BSP_USRCLK_Alloc(BSP_S32 * ps32UsrClkId);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Free
*
* ��������  : �ͷ��û�ʱ��
*
* �������  : BSP_S32 s32UsrClkId
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_U32 BSP_USRCLK_Free(BSP_S32 s32UsrClkId);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Connect
*
* ��������  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable usr clock interrupts.
*
* �������  : FUNCPTR routine   routine to be called at each clock interrupt
              BSP_S32 arg	        argument with which to call routine
              BSP_S32 s32UsrClkid      which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
//extern BSP_S32  BSP_USRCLK_Connect(FUNCPTR routine, BSP_S32 arg, BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Disable
*
* ��������  : This routine disables user clock interrupts.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
extern BSP_S32   BSP_USRCLK_Disable (BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Enable
*
* ��������  : This routine enables user clock interrupts.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
extern BSP_S32    BSP_USRCLK_Enable (BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_RateGet
*
* ��������  : This routine returns the interrupt rate of the system aux clock.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : BSP_S32 * pu32ClkRate  clk rate
* �� �� ֵ  : OK&������
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
extern BSP_S32 BSP_USRCLK_RateGet (BSP_S32 s32UsrClkId, BSP_S32 * pu32ClkRate);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_RateSet
*
* ��������  : This routine sets the interrupt rate of the usr clock.
*
* �������  : BSP_S32 ticksPerSecond   number of clock interrupts per second
              BSP_S32 s32UsrClkid         which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
extern BSP_S32  BSP_USRCLK_RateSet(BSP_S32 ticksPerSecond, BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerStart
*
* ��������  : ��������Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
*             u32Cycles   Timer�Ĵ����ļ���ֵ
* �������  : ��
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
extern BSP_S32    BSP_USRCLK_TimerStart(BSP_S32 s32UsrClkid,BSP_U32 u32Cycles);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerStop
*
* ��������  : �رյ���Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
* �������  : ��
* �� �� ֵ  : ��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
extern BSP_S32    BSP_USRCLK_TimerStop(BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerValue
*
* ��������  : ��������Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
* �������  : Value      ��ǰTimer value�Ĵ����ļ���ֵ
* �� �� ֵ  : OK&������
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
extern BSP_U32  BSP_USRCLK_TimerValue(BSP_S32 s32UsrClkId, BSP_U32 *pu32Value);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerMilliSecStart
*
* ��������  : �Ժ���Ϊ��λ��������Timer��ʱ��.
*
* �������  : s32UsrClkid        Timer Id
*             u32MilliSecond   ���ö�ʱ����ʱ�ĺ���ֵ
* �������  : ��
* �� �� ֵ  : OK&����������
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
extern BSP_S32    BSP_USRCLK_TimerMilliSecStart(BSP_S32 s32UsrClkid ,BSP_U32 u32MilliSecond);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerMilliSecValue
*
* ��������  : ��õ�ǰTimer�ĺ���ֵ.
*
* �������  : s32UsrClkid        Timer Id
* �������  : BSP_U32 * pu32Value ��ǰTimer value�Ĵ����ĺ���ֵ
* �� �� ֵ  : OK&����������
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
extern BSP_U32 BSP_USRCLK_TimerMilliSecValue(BSP_S32 s32UsrClkId ,BSP_U32 * pu32Value);

/*****************************************************************************
* �� �� ��  : sysClkTicksGet
*
* ��������  : ���ϵͳʱ������������tick��.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ϵͳʱ������������tick��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat

*****************************************************************************/
extern BSP_U32 sysClkTicksGet (BSP_VOID);

/*****************************************************************************
* �� �� ��  : sysAuxClkTicksGet
*
* ��������  : ���ϵͳ����ʱ������������tick��.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ϵͳ����ʱ������������tick��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat

*****************************************************************************/
BSP_U32 sysAuxClkTicksGet (BSP_VOID);

/*****************************************************************************
* �� �� ��  : sysTimestampRateSet
*
* ��������  : This routine sets the interrupt rate of the timestamp clock.  It does
*             not enable system clock interrupts unilaterally, but if the timestamp is currently enabled, the clock is disabled and then
*             re-enabled with the new rate.  Normally it is called by usrRoot()
*             in usrConfig.c.
*
* �������  : int ticksPerSecond   number of clock interrupts per second
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
BSP_S32 sysTimestampRateSet(BSP_S32 ticksPerSecond);

/*****************************************************************************
* �� �� ��  : sysTimestampRateGet
*
* ��������  : This routine returns the interrupt rate of the timestamp clock.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : The number of ticks per second of the system clock.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
BSP_S32 sysTimestampRateGet (BSP_VOID);
/*************************CLK END*****************************/


/*************************SCI BEGIN*****************************/
typedef BSP_U32 (*Sci_Event_Func)(BSP_U32 u32Event, BSP_VOID* para);

/*������*/
#define BSP_ERR_SCI_NOTINIT              951
#define BSP_ERR_SCI_INVALIDFREQ          952
#define BSP_ERR_SCI_USEDEFAULT           953
#define BSP_ERR_SCI_INVALIDPARA          954
#define BSP_ERR_SCI_NOCARD               955
#define BSP_ERR_SCI_NODATA               956
#define BSP_ERR_SCI_NOTREADY             957
#define BSP_ERR_SCI_DISABLED             958
#define BSP_ERR_SCI_UNSUPPORTED          959
#define BSP_ERR_SCI_INSERROR             960
#define BSP_ERR_SCI_GETAPDU_ERROR        961
#define BSP_ERR_SCI_VLTG_HIGHEST         962
#define BSP_ERR_SCI_CURRENT_STATE_ERR    963
#define BSP_ERR_SCI_CURRENT_VLTG_ERR     964
#define BSP_ERR_SCI_TIMESTOP_TIMEOUT     965


/*�ص�����ע���¼�����*/
#define SCI_EVENT_CARD_IN                0x1
#define SCI_EVENT_CARD_OUT               0x2
#define SCI_EVENT_CARD_DEACTIVE_SUCCESS  0x4
#define SCI_EVENT_CARD_RESET_SUCCESS     0x8
#define SCI_EVENT_CARD_READ_DATA         0x10
#define SCI_EVENT_CARD_TX_ERR            0x20

#define SCI_DEF_CARD_OK     0x0 /* ������������ʹ��*/
#define SCI_DEF_CARD_ERROR  0x1   /* �޿����߿��쳣*/


typedef enum tagSCI_CLK_STOP_TYPE_E
{
    SCI_CLK_STATE_LOW = 0,        /* Э���ָʾͣ��*/
    SCI_CLK_STATE_HIGH = 1,       /*Э���ָʾͣ��*/
    SCI_CLK_STATE_UNSUPPORTED = 2,/*Э���ָʾ��֧��*/
    SCI_CLK_STATE_BUTT
}SCI_CLK_STOP_TYPE_E;

/*****************************************************************************
* �� �� ��  : BSP_SCI_Reset
*
* ��������  : ���ӿ����ڸ�λSCI��Smart Card Interface��������USIM��Universal
*           Subscriber Identity Module����
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : OK  ��λ�ɹ�
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_Reset();

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetCardStatus
*
* ��������  : ���ӿ����ڻ�ÿ���ǰ��״̬
*
* �������  : ��
* �������  :
*           BSP_U32 *u32CardStatus     ��ǰ����״̬��
*                                       0�������ã�
*                                       1���������ã�
* �� �� ֵ  : OK
*           BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetCardStatus( BSP_U32 *u32CardStatus);

/*****************************************************************************
* �� �� ��  : BSP_SCI_SendData
*
* ��������  : ���ӿ����ڷ���һ�����ݵ�USIM��
*
* �������  : BSP_U32 u32DataLength �������ݵ���Ч���ȡ�ȡֵ��Χ1��256����λΪ�ֽ�
*             BSP_U8 *pu8DataBuffer �������������ڴ���׵�ַ�����Ƕ�̬���䣬���ýӿ�
*                                   ���������ͷţ�������Ӳ����������
* �������  : ��
*
* �� �� ֵ  : OK
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_INVALIDPARA
*           BSP_ERR_SCI_DISABLED
*           BSP_ERR_SCI_NOCARD
*           BSP_ERR_SCI_NODATA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_SendData(BSP_U32 u32DataLength, BSP_U8 *pu8DataBuffer);

/*****************************************************************************
* �� �� ��  : BSP_SCI_ReceiveSync
*
* ��������  : ���ӿ�����USIM Manager��ȡ����SCI Driver�Ŀ���������
*             �ýӿ�Ϊ�����ӿڣ�ֻ��SCI���յ��㹻����������Ż᷵�أ�
*             �ýӿڵĳ�ʱ����Ϊ1s
*
* �������  : BSP_U32 u32DataLength USIM Manager����SCI Driver��ȡ�����ݳ��ȡ�
* �������  : BSP_U8 *pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
*             BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_ReceiveSync(BSP_U32 u32Length,BSP_U8 *pu8Data);

/*****************************************************************************
* �� �� ��  : BSP_SCI_ReceiveAll
*
* ��������  : ���ӿ�����USIM Manager�ڶ�����ʱ��ʱ�򣬵��ñ���������ȡ�������ݻ����е���������
*
* �������  : ��
* �������  : BSP_U32 *u32DataLength Driver��ȡ�����ݳ��ȣ����ظ�USIM Manager��ȡֵ��Χ1��256����λ���ֽ�
*           BSP_U8 * pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_ReceiveAll(BSP_U32 *u32DataLength,BSP_U8 * pu8DataBuffer);

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetATR
*
* ��������  : ���ӿ����ڽ�Driver�㻺���ATR���ݺ����ݸ������ظ�USIM Manager��
*
* �������  : BSP_VOID
* �������  : BSP_U8 *u8DataLength  Driver��ȡ��ATR���ݳ��ȣ����ظ�USIM Manager��
*                                   ȡֵ��Χ0��32����λ���ֽ�
*           BSP_U8 *pu8ATR          USIM Managerָ����Buffer��SCI Driver��ATR
*                                   ���ݿ�������Buffer��һ��Ϊ����ϵͳ������̬����
*                                   ���߾�̬����ĵ�ַ
*
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetATR (unsigned long  *u8DataLength, BSP_U8 *pu8ATR);

/*****************************************************************************
* �� �� ��  : BSP_SCI_ClassSwitch
*
* ��������  : ���ӿ�����֧��PS�Կ��ĵ�ѹ���ͽ����л�����1.8V�л���3V
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  :  OK    ��ǰ��ѹ������ߵģ����е�ѹ�л�����
*           BSP_ERR_SCI_CURRENT_STATE_ERR �л�ʧ�� current SCI driver state is ready/rx/tx
*           BSP_ERR_SCI_VLTG_HIGHEST   ��ǰ��ѹ�Ѿ�����ߵ�ѹ��û�н��е�ѹ�л�
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_CURRENT_VLTG_ERR ��ǰ��ѹֵ�쳣����class B����C��
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_ClassSwitch();

/*****************************************************************************
* �� �� ��  : BSP_SCI_ShowVltgVal
*
* ��������  : ���ӿ�������ʾ��ǰSIM���ӿڵ�ѹ
*
* �������  : ��
* �������  : BSP_U32 * pu32Vltgval ��ǰ��ѹ
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_ShowVltgVal(BSP_U32 * pu32Vltgval);

/*****************************************************************************
* �� �� ��  : BSP_SCI_TimeStop
*
* ��������  : ���ӿ�����֧��PS�ر�SIM��ʱ��
*
* �������  :
*           SCI_CLK_STOP_TYPE_E enTimeStopCfg ʱ��ֹͣģʽ
*
* �������  : ��
*
* �� �� ֵ  : OK - successful completion
*               ERROR - failed
*               BSP_ERR_SCI_NOTINIT
*               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
*               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_S32 BSP_SCI_TimeStop(unsigned long enTimeStopCfg);

/*****************************************************************************
* �� �� ��  : BSP_SCI_Deactive
*
* ��������  : ���ӿ����ڶ�SIM����ȥ�������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_Deactive(BSP_VOID);

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetClkStatus
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��״̬
*
* �������  : BSP_U32 *pu32SciClkStatus   ����ָ�룬���ڷ���SIM��ʱ��״̬��
*                                       0��ʱ���Ѵ򿪣�
*                                       1��ʱ��ֹͣ
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*          BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetClkStatus(BSP_U32 *pu32SciClkStatus);

/*****************************************************************************
* �� �� ��  : BSP_SCI_RegEvent
*
* ��������  : ���ӿ�����ע��ص�����
*
* �������  : BSP_U32 u32Event      �¼����ͣ����������֣�
*                                    0x1���忨��
*                                    0x2���ο���
*                                    0x4�����µ磻
*                                    0x8�����ϵ磻
*                                    0x10�������ݣ�
*                                    0x20���������ݴ���
*              Sci_Event_Func * pFunc   �ص�����
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*          BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_RegEvent(BSP_U32 u32Event, Sci_Event_Func pFunc);

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetClkFreq
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
*
* �������  : ��
*
* �������  : BSP_U32 *pLen   ʱ��Ƶ�����ݵĳ���
*             BSP_U8 *pBuf    ʱ��Ƶ������
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2010��8��24��   zhouluojun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetClkFreq(unsigned long *pLen, unsigned char *pBuf);

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetBaudRate
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
*
* �������  : ��
*
* �������  : BSP_U32 *pLen   ���������ݵĳ���
*             BSP_U8 *pBuf    ����������
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2010��8��24��   zhouluojun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetBaudRate(unsigned long *pLen, BSP_U8 *pBuf);

/*****************************************************************************
* �� �� ��  : BSP_SCI_GetPCSCParameter
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM����PCSC��ز���
*
* �������  : ��
*
* �������  : BSP_U8 *pBuf    PCSC��ز���
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2010��8��24��   zhouluojun  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetPCSCParameter(BSP_U8 *pBuf);

/*****************************************************************************
* �� �� ��  : BSP_SCI_RecordDataSave
*
* ��������  : ���ӿ����ڱ����ά�ɲ���Ϣ��yaffs��
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*             ����   ����ʧ��
*
* �޸ļ�¼  : 2011��5��21��   yangzhi  creat
*
*****************************************************************************/
BSP_U32 BSP_SCI_RecordDataSave();

/*************************SCI END*************************************/

/*************************PMU BEGIN*****************************/

/* ������ */
#define BSP_ERR_PMU_PARA_INVALID      BSP_DEF_ERR(BSP_MODU_SPI, 0x50)
#define BSP_ERR_PMU_ERROR_INIT        BSP_DEF_ERR(BSP_MODU_SPI, 0x51)
#define BSP_ERR_PMU_SPI_NOT_INIT      BSP_DEF_ERR(BSP_MODU_SPI, 0x52)
#define BSP_ERR_PMU_NOT_INIT          BSP_DEF_ERR(BSP_MODU_SPI, 0x53)
/**************************************************************************
  ȫ�ֱ�������
**************************************************************************/


/**************************************************************************
  ö�ٶ���
**************************************************************************/
/*DVFS type*/
typedef enum tagPMU_DVFS_TYPE_E
{
	DVFS_ARMCORE = 0,
	DVFS_CEVACORE,
	DVFS_BUTTOM
}PMU_DVFS_TYPE_E;

/*DVFS Voltage type*/
typedef enum tagPMU_DVFS_VOLTAGE_TYPE_E
{
	DVFS_VOLTAGE_1000 = 0,
	DVFS_VOLTAGE_1100,
	DVFS_VOLTAGE_1150,
	DVFS_VOLTAGE_1200,
	DVFS_VOLTAGE_1250,
	DVFS_VOLTAGE_1350,
	DVFS_VOLTAGE_1500,
	DVFS_VOLTAGE_1800,
    DVFS_VOLTAGE_BUTTOM
}PMU_DVFS_VOLTAGE_TYPE_E;

 /*DEVICE type*/
typedef enum tagPMU_DEVS_TYPE_E
{
	DEVS_RF = 0,
	DEVS_ABB,
	DEVS_SD,
	DEVS_SIM,
    DEVS_BUTTOM
}PMU_DEVS_TYPE_E;


/*DEVICE CTRL type*/
typedef enum tagPMU_DEVS_CTRL_TYPE_E
{
	CTRL_ON = 0,
	CTRL_OFF,
    CTRL_BUTTOM
}PMU_DEVS_CTRL_TYPE_E;

 /*OCP type*/
typedef enum tagPMU_OCP_TYPE_E
{
	OCP_ONLYINT_NOAUTOOFF = 0,
	OCP_INT_AND_AUTOOFF,
	OCP_AUTOOFF,
    OCP_BUTTOM
}PMU_OCP_TYPE_E;

 /* VOLTAGE ADJUST REG */
typedef enum tagPMU_VOL_SCI_E
{
	PMU_VOL_UP = 0, /* ��1.8��������3.0��*/
	PMU_VOL_DOWN,   /* ��3.0������1.8��*/
	PMU_VOL_SCI_BUTTOM
}PMU_VOL_SCI_E;


/* LED MODE */
typedef enum tagPMU_LED_STATE_E
{
	PMU_LED_FLASH_POWER_OFF = 0,    /* ȫ������ */
	PMU_LED_FLASH_BLUE_ON,          /* ���Ƴ��� */
	PMU_LED_FLASH_BLUE_SLOW,        /* �������� */
	PMU_LED_FLASH_BLUE_FAST,        /* ���ƿ��� */
	PMU_LED_FLASH_BLUE_ONCE,        /* ���Ƶ��� */
	PMU_LED_FLASH_BLUE_TWICE,       /* ����˫�� */
	PMU_LED_FLASH_BLUE_FOUR,        /* �������� */
	PMU_LED_FLASH_RED_ON,           /* ��Ƴ��� */
	PMU_LED_FLASH_RED_SLOW,         /* ������� */
	PMU_LED_FLASH_RED_FAST,         /* ��ƿ��� */
	PMU_LED_FLASH_RED_ONCE,         /* ��Ƶ��� */
	PMU_LED_FLASH_RED_TWICE,        /* ���˫�� */
	PMU_LED_FLASH_RED_FOUR,         /* ������� */
	PMU_LED_FLASH_GREEN_ON,         /* �̵Ƴ��� */
	PMU_LED_FLASH_GREEN_SLOW,       /* �̵����� */
	PMU_LED_FLASH_GREEN_FAST,       /* �̵ƿ��� */
	PMU_LED_FLASH_GREEN_ONCE,       /* �̵Ƶ��� */
	PMU_LED_FLASH_GREEN_TWICE,      /* �̵�˫�� */
	PMU_LED_FLASH_GREEN_FOUR,       /* �̵����� */
	PMU_LED_STATE_BUTT
}PMU_LED_STATE_E;


/**************************************************************************
  STRUCT����
**************************************************************************/
/*SPI��ID��ASIC��ʹ��3ƬSPI*/
typedef enum tagSPI_DEV_ID
{
    SPI_ID0,
    SPI_ID1,
    SPI_ID_MAX
}SPI_DEV_ID_E;


/*ÿ��SPI�ϵ�Ƭѡ�ţ���ǰÿ��SPI��4��Ƭѡ*/
typedef enum tagSPI_DEV_CS
{
    SPI_DEV_CS0,
    SPI_DEV_CS1,
    SPI_DEV_CS2,
    SPI_DEV_CS3,
    SPI_DEV_CS_MAX,
    NO_OWNER = -1
}SPI_DEV_CS_E;


/*���ݴ��䷽ʽ������DMA��ʽ����ѭ��ʽ*/
typedef enum tagSPI_SENDMOD
{
    SPI_SENDMOD_POLLING,
    SPI_SENDMOD_DMA,
    SPI_SENDMOD_MAX
}RXTX_MODE_E;


/* ��¼SPI��ID��Ƭѡ�ŵĽṹ��*/
typedef struct tagSPI_DEV_STRUCTION
{
    SPI_DEV_ID_E enSpiId;
    SPI_DEV_CS_E enSpiCs;
}SPI_DEV_S;

/* ���������ֳ��� */
typedef enum tagspi_CommandLen
{
    SPI_COMMANDSIZE_1BITS =  0x0,     /*  1 bit command */
    SPI_COMMANDSIZE_2BITS =  0x1,     /*  2 bit command */
    SPI_COMMANDSIZE_3BITS =  0x2,     /*  3 bit command */
    SPI_COMMANDSIZE_4BITS  = 0x3,     /*  4 bit command */
    SPI_COMMANDSIZE_5BITS  = 0x4,     /*  5 bit command */
    SPI_COMMANDSIZE_6BITS  = 0x5,     /*  6 bit command */
    SPI_COMMANDSIZE_7BITS  = 0x6,     /*  7 bit command */
    SPI_COMMANDSIZE_8BITS  = 0x7,     /*  8 bit command */
    SPI_COMMANDSIZE_9BITS  = 0x8,     /*  9 bit command */
    SPI_COMMANDSIZE_10BITS = 0x9,     /* 10 bit command */
    SPI_COMMANDSIZE_11BITS = 0xA,     /* 11 bit command */
    SPI_COMMANDSIZE_12BITS = 0xB,     /* 12 bit command */
    SPI_COMMANDSIZE_13BITS = 0xC,     /* 13 bit command */
    SPI_COMMANDSIZE_14BITS = 0xD,     /* 14 bit command */
    SPI_COMMANDSIZE_15BITS = 0xE,     /* 15 bit command */
    SPI_COMMANDSIZE_16BITS = 0xF,      /* 16 bit command */
    SPI_COMMANDSIZE_MAX
} SPI_COMMAND_LEN_E;

/*����֡����*/
typedef enum tagspi_DataLen
{
    SPI_DATASIZE_4BITS  = 0x3,     /*  4 bit data */
    SPI_DATASIZE_5BITS  = 0x4,     /*  5 bit data */
    SPI_DATASIZE_6BITS  = 0x5,     /*  6 bit data */
    SPI_DATASIZE_7BITS  = 0x6,     /*  7 bit data */
    SPI_DATASIZE_8BITS  = 0x7,     /*  8 bit data */
    SPI_DATASIZE_9BITS  = 0x8,     /*  9 bit data */
    SPI_DATASIZE_10BITS = 0x9,     /* 10 bit data */
    SPI_DATASIZE_11BITS = 0xA,     /* 11 bit data */
    SPI_DATASIZE_12BITS = 0xB,     /* 12 bit data */
    SPI_DATASIZE_13BITS = 0xC,     /* 13 bit data */
    SPI_DATASIZE_14BITS = 0xD,     /* 14 bit data */
    SPI_DATASIZE_15BITS = 0xE,     /* 15 bit data */
    SPI_DATASIZE_16BITS = 0xF,     /* 16 bit data */
    SPI_DATASIZE_MAX
} SPI_DATA_LEN_E;

/* SPI֧�ֵ�Э��*/
typedef enum tagSPI_PROT
{
    SPI_PROT_SPI,
    SPI_PROT_SSP,
    SPI_PROT_NSM,
    SPI_PROT_MAX
}SPI_PROT_E;

typedef enum tagSPI_SCPOL
{
	SPI_SCPOL_LOW, //�½��ش���
	SPI_SCPOL_HIGH,//�����ش���
	SPI_SCPOL_MAX
}SPI_SCPOL_E;

/*SPI����豸���Խṹ�壬�����豸��Ҫ�������ֳ��ȣ�����֡���ȣ�ʹ��Э��� */
typedef struct tagSPI_DEV_ATTR
{
    SPI_COMMAND_LEN_E enCommandLen;
    SPI_DATA_LEN_E enDataLen;
    SPI_PROT_E enSpiProt;
	SPI_SCPOL_E enSpiScpol;
    BSP_U16 u16SpiBaud;
}SPI_DEV_ATTR_S;

/*��¼��SPI���ݴ��������Ϣ�Ľṹ�壬��Ա����Ҫ��д��SPI�ţ�Ƭѡ�ţ�����ģʽ��
  ���ݵ�ַ�����ݳ��ȵ�*/
typedef struct tagSPI_DATA_HANDLE
{
    SPI_DEV_ID_E enSpiID;
    SPI_DEV_CS_E enCsID;
    RXTX_MODE_E enMode;
    void *pvCmdData;
    BSP_U32 u32length;
}SPI_DATA_HANDLE_S;

/*****************************************************************************
* �� �� ��  : BSP_PMU_ShutDown
*
* ��������  : ���ӿ����ڹر�PMU
*
* �������  :
* �������  : ��
*
* �� �� ֵ  :
* �޸ļ�¼  :
*
*****************************************************************************/
BSP_VOID BSP_PMU_ShutDown();
/*****************************************************************************
* �� �� ��  : BSP_PMU_DVFS_VolAdjust
*
* ��������  : DVFS ��ѹ����
*
* �������  :
* �������  :
*
* �� �� ֵ  :
* �޸ļ�¼  :
*
*****************************************************************************/
BSP_S32 BSP_PMU_DVFS_VolAdjust(PMU_DVFS_TYPE_E enDvfsType,PMU_DVFS_VOLTAGE_TYPE_E enVoltage);
/*****************************************************************************
* �� �� ��  : BSP_PMU_OCPConfig
*
* ��������  : OCPC����
*
* �������  :
* �������  :
*
* �� �� ֵ  :
* �޸ļ�¼  :
*
*****************************************************************************/
BSP_S32 BSP_PMU_OCPConfig(PMU_OCP_TYPE_E enOcpType);
/*****************************************************************************
* �� �� ��  : BSP_PMU_DEVS_Ctrl
*
* ��������  : DEVS������
*
* �������  :
* �������  :
*
* �� �� ֵ  :
* �޸ļ�¼  :
*
*****************************************************************************/
BSP_S32 BSP_PMU_DEVS_Ctrl(PMU_DEVS_TYPE_E enDevsType, PMU_DEVS_CTRL_TYPE_E enCtrlType);
/*****************************************************************************
* �� �� ��  : BSP_PMU_VolAdjust_ForSci
*
* ��������  : SCI��ѹ����
*
* �������  :
* �������  :
*
* �� �� ֵ  :
* �޸ļ�¼  :
*
*****************************************************************************/
BSP_S32 BSP_PMU_VolAdjust_ForSci(PMU_VOL_SCI_E enSCIVolCfg);

/*****************************************************************************
* �� �� ��  : BSP_PMU_CutOff_ForDrx
*
* ��������  : �͹��ĳ���PMU�µ�
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  :
* �޸ļ�¼  : ��ȷ/����
*
*****************************************************************************/
BSP_S32 BSP_PMU_CutOff_ForDrx();

/*****************************************************************************
* �� �� ��  : BSP_PMU_SetLED
*
* ��������  : ����LTD�ƵĿ���
*
* �������  : enLEDType         LED0
*                               LED1
*                               LED2
*             enPower           PMU_LED_POWER_ON
*                               PMU_LED_POWER_OFF
* �������  : ��
*
* �� �� ֵ  : OK�����óɹ�
*             ERROR������ʧ��
*****************************************************************************/
BSP_S32 BSP_PMU_SetLedState(PMU_LED_STATE_E eLedState);

/*************************PMU END*****************************/
/*************************NCM BEGIN*****************************/
/* ������*/
/*ר�ô�����*/
#define BSP_ERR_SPECIAL (0x0)
#define BSP_ERR_NCM_NOTXBUFF         BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 1)) /*0x10120001*/
#define BSP_ERR_NCM_NOIDLEDEV        BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 2)) /*0x10120002*/
#define BSP_ERR_NCM_AT_SEND_TIMEOUT  BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 3))/*0x10121003*/
#define BSP_ERR_NCM_WRONG_STATE      BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 4))/*0x10121004*/
#define BSP_ERR_NCM_AT_SEND_FAIL     BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 5))/*0x10121005*/
#define BSP_ERR_NCM_SEND_EXCEED_MAXPKT  BSP_DEF_ERR(BSP_MODU_USB_NCM,(BSP_ERR_SPECIAL + 6))/*0x10121006*/

typedef struct tagNCM_PKT_S
{
    BSP_U8 *pBuffer;       /* bufferָ��*/
    BSP_U32  u32BufLen;      /* buffer���� */
}NCM_PKT_S;

/* NCM�豸����ö��*/
typedef enum tagNCM_DEV_TYPE_E
{
    NCM_DEV_DATA_TYPE,      /* ����ͨ�����ͣ�PSʹ��*/
    NCM_DEV_CTRL_TYPE       /* ����ͨ����MSP����AT����ʹ��*/
}NCM_DEV_TYPE_E;

/* ������·�հ�����ָ�� */
typedef BSP_VOID (*USBUpLinkRxFunc)(BSP_VOID * pPktNode);

/* ����װ�ͷź���ָ�� */
typedef BSP_VOID (*USBFreePktEncap)(BSP_VOID *PktEncap, BSP_BOOL bNodeOnly);

/* USB IOCTLö�� */
typedef enum tagNCM_IOCTL_CMD_TYPE_E
{
    NCM_IOCTL_NETWORK_CONNECTION_NOTIF,      /* 0x0,NCM�����Ƿ�������*/
    NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, /* 0x1,NCM�豸Э�̵������ٶ�*/
    NCM_IOCTL_SET_PKT_ENCAP_INFO,            /* 0x2,���ð���װ��ʽ*/
    NCM_IOCTL_REG_UPLINK_RX_FUNC,            /* 0x3,ע�������հ��ص�����*/
    NCM_IOCTL_REG_FREE_PKT_FUNC,             /* 0x4,ע���ͷŰ���װ�ص�����*/
    NCM_IOCTL_FREE_BUFF,                     /* 0x5,�ͷŵ���buffer*/
    NCM_IOCTL_GET_USED_MAX_BUFF_NUM,         /* 0x6,��ȡ�ϲ�������ռ�õ�ncm buffer����*/
    NCM_IOCTL_GET_DEFAULT_TX_MIN_NUM,        /* 0x7,��ȡĬ�Ϸ���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_TIMEOUT,        /* 0x8,��ȡĬ�Ϸ�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_MAX_SIZE,       /* 0x9,��ȡĬ�Ϸ����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_MIN_NUM,                /* 0xa,���÷���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_TIMEOUT,                /* 0xb,���÷�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_SET_TX_MAX_SIZE,               /* 0xc,�������ֲ���ʹ�á����÷����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_RX_BUF_SIZE,               /* 0xd,��ȡ�հ�buffer��С*/
    NCM_IOCTL_FLOW_CTRL_NOTIF,               /* 0xe,���ؿ��ƿ���*/
    NCM_IOCTL_REG_AT_PROCESS_FUNC,           /* 0xf,ע��AT�����ص�����*/
    NCM_IOCTL_AT_RESPONSE,                   /* 0x10,AT�����Ӧ*/
    NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC,     /* 0x11,ע������״̬�ı�֪ͨ�ص�����*/
    NCM_IOCTL_SET_PKT_STATICS,               /* 0x12,����ͳ����Ϣ*/

    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 ��ѯNCM����״̬*/
    /* END:   Modified by liumengcun, 2011-4-21 */


    NCM_IOCTL_GET_CUR_TX_MIN_NUM,              /* 0x14 ��ȡ��ǰ����������ֵ*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,               /* 0x15 ��ȡ��ǰ������ʱʱ��*/
    NCM_IOCTL_IPV6_DNS_NOTIF,              /*0x16 IPV6 DNS�����ϱ�*/
    /* END:   Modified by liumengcun, 2011-6-23 */
    /* BEGIN: Modified by liumengcun, 2011-7-20 ֧��IPV6 DNS����*/
    NCM_IOCTL_SET_IPV6_DNS,                     /* 0x16 ����IPV6 DNS*/
    /* END:   Modified by liumengcun, 2011-7-20 */
    /* BEGIN: Modified by liumengcun, 2011-8-10 MSP������*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                     /* 0x17 ���IPV6 DNS�ڰ�˵Ļ���,param�ڴ�������û�����壬�����ָ�뼴��*/
    NCM_IOCTL_GET_NCM_STATUS,                     /* 0x18 ��ȡNCM����״̬ enable:TRUE(1);disable:FALSE(0) */
    /* END:   Modified by liumengcun, 2011-8-10 */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

    /* BEGIN: Modified by baoxianchun, 2012-5-17 GU PS ������*/
	NCM_IOCTL_SET_RX_MIN_NUM,		/*�����հ�������ֵ*/
	NCM_IOCTL_SET_RX_TIMEOUT,			/*�����հ���ʱʱ��*/
    /* END: Modified by baoxianchun, 2012-5-17 GU PS ������*/
    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC   /* NDISͨ��AT����״̬����ص����� */

}NCM_IOCTL_CMD_TYPE_E;

/* NCM����״̬ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECTION_STATUS_E
{
    NCM_IOCTL_CONNECTION_LINKDOWN,      /* NCM����Ͽ�����*/
    NCM_IOCTL_CONNECTION_LINKUP         /* NCM��������*/
}NCM_IOCTL_CONNECTION_STATUS_E;

/* NCM�����ٶȽṹ,NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_IOCTL_CONNECTION_SPEED_S
{
    BSP_U32 u32DownBitRate;
    BSP_U32 u32UpBitRate;
}NCM_IOCTL_CONNECTION_SPEED_S;

/* ����װ�ṹ��,NCM_IOCTL_SET_PKT_ENCAP_INFO�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_PKT_ENCAP_INFO_S
{
    BSP_S32 s32BufOft;      /* bufƫ���� */
    BSP_S32 s32LenOft;      /* lenƫ���� */
    BSP_S32 s32NextOft;     /* nextƫ���� */
}NCM_PKT_ENCAP_INFO_S;

/* AT����ظ�����ָ�뼰���� NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    BSP_U8* pu8AtAnswer;
    BSP_U32 u32Length;
} NCM_AT_RSP_S;

/* AT������պ���ָ�룬�ú���Ϊͬ���ӿڣ���ӦNCM_IOCTL_REG_AT_PROCESS_FUNC������*/
typedef BSP_VOID (*USBNdisAtRecvFunc)(BSP_U8 * pu8Buf, BSP_U32 u32Len);

/* NCM���ؿ���ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_FLOW_CTRL_E
{
    NCM_IOCTL_FLOW_CTRL_ENABLE,      /* ������*/
    NCM_IOCTL_FLOW_CTRL_DISABLE      /* �ر�����*/
}NCM_IOCTL_FLOW_CTRL_E;

/* NCM����״̬�ı�֪ͨö��,NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECT_STUS_E
{
    NCM_IOCTL_STUS_CONNECT,      /* ����*/
    NCM_IOCTL_STUS_BREAK         /* �����Ͽ�,����*/
}NCM_IOCTL_CONNECT_STUS_E;

typedef enum tagHKADC_TEMP_PROTECT_E
{
    HKADC_TEMP_BATTERY,
    HKADC_TEMP_PA0,
    HKADC_TEMP_PA1,
    HKADC_TEMP_DCXO0,
    HKADC_TEMP_DCXO1,
    HKADC_TEMP_LCD,
    HKADC_TEMP_SIM_CARD,
    HKADC_TEMP_BUTT
}HKADC_TEMP_PROTECT_E;

/* ����״̬�л�֪ͨ��������ӦNCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC������*/
typedef BSP_VOID (*USBNdisStusChgFunc)(NCM_IOCTL_CONNECT_STUS_E enStatus, BSP_VOID * pBuffer);

/*  �´��ϴ������ذ��ĸ���ͳ����Ϣ��
    �����͸�PC�������ȴ�PC�Ķ�ȡ,NCM_IOCTL_SET_PKT_STATICS�����ֶ�Ӧ�����ṹ*/
typedef struct tagNCM_IOCTL_PKT_STATISTICS_S
{
    BSP_U32     u32TxOKCount;         /*���Ͱ���*/
    BSP_U32     u32RxOKCount;         /*���հ���*/
    BSP_U32     u32TxErrCount;        /*���ʹ���*/
    BSP_U32     u32RxErrCount;        /*���մ���*/
    BSP_U32     u32TxOverFlowCount;   /*�����������*/
    BSP_U32     u32RxOverFlowCount;   /*�����������*/
    BSP_U32     u32CurrentTx;         /*��������*/
    BSP_U32     u32CurrentRx;         /*��������*/
} NCM_IOCTL_PKT_STATISTICS_S;

/* BEGIN: Modified by liumengcun, 2011-7-20 IPV6 DNS���ýṹ,NCM_IOCTL_SET_IPV6_DNS��Ӧ�����ṹ*/
#define BSP_NCM_IPV6_DNS_LEN     32
 typedef struct tagNCM_IPV6DNS_S  /* 0x16 ����IPV6 DNS*/
 {
     BSP_U8 * pu8Ipv6DnsInfo;/* 32�ֽڣ���16�ֽڱ�ʾprimaryDNS����16�ֽڱ�ʾSecondaryDNS��*/
     BSP_U32 u32Length;
 } NCM_IPV6DNS_S;
/* END:   Modified by liumengcun, 2011-7-20 */
typedef struct tagNCM_PKT_INFO_S
{
    BSP_U32 u32PsRcvPktNum;              /* �հ��͵�PS�İ�����*/
    BSP_U32 u32RcvUnusedNum;             /* �հ�������PSҪ����������*/
    BSP_U32 u32NcmSendPktNum;            /* ��������*/
}NCM_PKT_INFO_S;


/*****************************************************************************
* �� �� ��  : BSP_NCM_Open
*
* ��������  : ������ȡ����ʹ��NCM�豸ID,����ͨ�����ͣ�PSʹ��;����ͨ�����ͣ�
*              MSP����AT����ʹ��
*
* �������  : NCM_DEV_TYPE_E enDevType  �豸����
* �������  : pu32NcmDevId              NCM �豸ID
*
* �� �� ֵ  : BSP_ERR_NET_NOIDLEDEV
*             OK
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 BSP_NCM_Open(NCM_DEV_TYPE_E enDevType, BSP_U32 * pu32NcmDevId);

/*****************************************************************************
* �� �� ��  : BSP_NCM_Write
*
* ��������  : ��������
*
* �������  : BSP_U32 u32NcmDevId  NCM�豸ID
* �������  : BSP_VOID *pPktEncap       ����װ�׵�ַ
*
* �� �� ֵ  : BSP_OK
*             BSP_ERR_NET_INVALID_PARA
*             BSP_ERR_NET_BUF_ALLOC_FAILED
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 BSP_NCM_Write(BSP_U32 u32NcmDevId, BSP_VOID *pPktEncap);

/*****************************************************************************
* �� �� ��  : BSP_NCM_Ioctl
*
* ��������  : ����NCM�豸����
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  :
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 BSP_NCM_Ioctl(BSP_U32 u32NcmDevId, NCM_IOCTL_CMD_TYPE_E enNcmCmd, BSP_VOID *param);

/*****************************************************************************
* �� �� ��  : BSP_NCM_Close
*
* ��������  : �ر�NCM�豸
*
* �������  : NCM_DEV_TYPE_E enDevType   �豸ID����
*             BSP_U32 u32NcmDevId        NCM�豸ID
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 BSP_NCM_Close(NCM_DEV_TYPE_E enDevType, BSP_U32 u32NcmDevId);
/*************************NCM END*****************************/

/*************************ACM BEG*****************************/
/* IOCTL CMD ���� */
#define ACM_IOCTL_SET_WRITE_CB      0x7F001000
#define ACM_IOCTL_SET_READ_CB       0x7F001001
#define ACM_IOCTL_SET_EVT_CB        0x7F001002
#define ACM_IOCTL_SET_FREE_CB       0x7F001003


#define ACM_IOCTL_WRITE_ASYNC       0x7F001010
#define ACM_IOCTL_GET_RD_BUFF       0x7F001011
#define ACM_IOCTL_RETURN_BUFF       0x7F001012
#define ACM_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define ACM_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014

#define ACM_IOCTL_IS_IMPORT_DONE    0x7F001020
#define ACM_IOCTL_WRITE_DO_COPY     0x7F001021

/* Modem ���������� */
#define ACM_MODEM_IOCTL_SET_MSC_READ_CB 0x7F001030
#define ACM_MODEM_IOCTL_MSC_WRITE_CMD   0x7F001031
#define ACM_MODEM_IOCTL_SET_REL_IND_CB  0x7F001032

//qijiwen IOCTL code for HSIC
#define ACM_IOCTL_FLOW_CONTROL  0x7F001035


/* UDI IOCTL ����ID */
#define UDI_ACM_IOCTL_SET_READ_CB           ACM_IOCTL_SET_READ_CB
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    ACM_IOCTL_GET_RD_BUFF
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       ACM_IOCTL_RETURN_BUFF

#define UART_IOCTL_SET_WRITE_CB      0x7F001000
#define UART_IOCTL_SET_READ_CB       0x7F001001
#define UART_IOCTL_SET_EVT_CB        0x7F001002
#define UART_IOCTL_SET_FREE_CB       0x7F001003
#define UART_IOCTL_WRITE_ASYNC       0x7F001010
#define UART_IOCTL_GET_RD_BUFF       0x7F001011
#define UART_IOCTL_RETURN_BUFF       0x7F001012
#define UART_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define UART_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014
#define UART_IOCTL_SET_WRITE_TIMEOUT 0x7F001015
#define UART_IOCTL_SET_BAUD           0X7F001016
#define UART_IOCTL_SET_WLEN           0X7F001017
#define UART_IOCTL_SET_STP2           0X7F001018
#define UART_IOCTL_SET_EPS            0X7F001019
#define UART_IOCTL_IS_IMPORT_DONE    0x7F001020
#define UDI_UART_IOCTL_SET_READ_CB           UART_IOCTL_SET_READ_CB
#define UDI_UART_IOCTL_GET_READ_BUFFER_CB    UART_IOCTL_GET_RD_BUFF
#define UDI_UART_IOCTL_RETUR_BUFFER_CB       UART_IOCTL_RETURN_BUFF
#define UART_IOCTL_SET_MSC_READ_CB 0x7F001021
#define UART_IOCTL_MSC_WRITE_CMD 0x7F001022
#define UART_IOCTL_SWITCH_MODE_CB 0x7F001023
#define UART_IOCTL_SET_FLOW_CONTROL 0x7F001024
#define UART_IOCTL_SET_AC_SHELL 0x7F001025

/* UART UDI ������*/
#define UART_UDI_ERROR_BASE               0x80000000

#define UART_ERR_MODULE_NOT_INITED      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_MODULE_NOT_INITED) | UART_UDI_ERROR_BASE))
#define UART_ERR_NULL_PTR      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_NULL_PTR) | UART_UDI_ERROR_BASE))
#define UART_ERR_INVALID_PARA      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_INVALID_PARA) | UART_UDI_ERROR_BASE))
#define UART_ERR_RETRY_TIMEOUT      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_RETRY_TIMEOUT) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_ALLOC_FAILED      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_BUF_ALLOC_FAILED) | UART_UDI_ERROR_BASE))
#define UART_ERR_BUF_FREE_FAILED      ((BSP_S32)(BSP_DEF_ERR(BSP_MODU_UART, (BSP_S32) BSP_ERR_BUF_FREE_FAILED) | UART_UDI_ERROR_BASE))

/* UART����λ��*/
typedef enum
{
    WLEN_5_BITS,
    WLEN_6_BITS,
    WLEN_7_BITS,
    WLEN_8_BITS,
    WLEN_MAX,
}UART_WLEN_ENUM;

/* UARTֹͣλ��*/
typedef enum
{
    STP2_OFF,
    STP2_ON,
    STP2_MAX,
}uart_stp2_enum;

/* UARTУ�鷽ʽ*/
typedef enum
{
    PARITY_NO_CHECK,
    PARITY_CHECK_ODD,
    PARITY_CHECK_EVEN,
    PARITY_CHECK_MARK,        /*У��λʼ��Ϊ1*/
    PARITY_CHECK_SPACE,       /*У��λʼ��Ϊ0*/
    PARITY_CHECK_MAX,
}uart_parity_enum;

/* �첽�����շ��ṹ */
typedef struct tagUART_WR_ASYNC_INFO
{
    char* pBuffer;
    unsigned int u32Size;
    void* pDrvPriv;
}uart_wr_async_info;
/* ��buffer������Ϣ */
typedef struct tagUART_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}uart_read_buff_info;

	extern unsigned long free_mem_size_get(void);
#define FREE_MEM_SIZE_GET() free_mem_size_get()


/* ACM�豸�¼����� */
typedef enum tagACM_EVT_E
{
    ACM_EVT_DEV_SUSPEND = 0,        /* �豸�����Խ��ж�д(��Ҫ�����¼��ص�������״̬) */
    ACM_EVT_DEV_READY = 1,          /* �豸���Խ��ж�д(��Ҫ�����¼��ص�������״̬) */
    ACM_EVT_DEV_BOTTOM
}ACM_EVT_E;

/* parameters for HSIC ACM flow control command */
typedef enum tagACM_IOCTL_FLOW_CONTROL_E
{
    ACM_IOCTL_FLOW_CONTROL_DISABLE = 0,      /* resume receiving data from ACM port */
    ACM_IOCTL_FLOW_CONTROL_ENABLE      /* stop receiving data from ACM port */
}ACM_IOCTL_FLOW_CONTROL_E;


/* �첽�����շ��ṹ */
typedef struct tagACM_WR_ASYNC_INFO
{
    char* pVirAddr;
    char* pPhyAddr;
    unsigned int u32Size;
    void* pDrvPriv;
}ACM_WR_ASYNC_INFO;


/* ��buffer��Ϣ */
typedef struct tagACM_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}ACM_READ_BUFF_INFO;

/* MODEM �ܽ��ź�ֵ���� */
#define SIGNALNOCH 0
#define SIGNALCH 1
#define RECV_ENABLE 1
#define RECV_DISABLE 0
#define SEND_ENABLE 1
#define SEND_DISABLE 0
#define HIGHLEVEL 1
#define LOWLEVEL 0


/* MODEM �ܽ��źŽṹ�嶨��*/
typedef struct tagMODEM_MSC_STRU
{
    BSP_U32 OP_Dtr     :    1;          /*DTR CHANGE FLAG*/
    BSP_U32 OP_Dsr     :    1;          /*DSR CHANGE FLAG*/
    BSP_U32 OP_Cts     :    1;          /*CTSCHANGE FLAG*/
    BSP_U32 OP_Rts     :    1;          /*RTS CHANGE FLAG*/
    BSP_U32 OP_Ri      :    1;          /*RI CHANGE FLAG*/
    BSP_U32 OP_Dcd     :    1;          /*DCD CHANGE FLAG*/
    BSP_U32 OP_Fc      :    1;          /*FC CHANGE FLAG*/
    BSP_U32 OP_Brk     :    1;          /*BRK CHANGE FLAG*/
    BSP_U32 OP_Spare   :    24;         /*reserve*/
    BSP_U8   ucDtr;                     /*DTR  VALUE*/
    BSP_U8   ucDsr;                     /*DSR  VALUE*/
    BSP_U8   ucCts;                     /*DTS VALUE*/
    BSP_U8   ucRts;                     /*RTS  VALUE*/
    BSP_U8   ucRi;                      /*RI VALUE*/
    BSP_U8   ucDcd;                     /*DCD  VALUE*/
    BSP_U8   ucFc;                      /*FC  VALUE*/
    BSP_U8   ucBrk;                     /*BRK  VALUE*/
    BSP_U8   ucBrkLen;                  /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;


typedef BSP_VOID (*ACM_WRITE_DONE_CB_T)(char* pDoneBuff, int s32DoneSize);
typedef BSP_VOID (*ACM_READ_DONE_CB_T)(BSP_VOID);
typedef BSP_VOID (*ACM_EVENT_CB_T)(ACM_EVT_E enEvt);
typedef BSP_VOID (*ACM_FREE_CB_T)(char* pBuff);
typedef BSP_VOID (*ACM_MODEM_MSC_READ_CB_T)(MODEM_MSC_STRU* pModemMsc);
typedef BSP_VOID (*ACM_MODEM_REL_IND_CB_T)(BSP_BOOL bEnable);
/*************************ACM END*****************************/

typedef void (*uart_free_cb_t)(char* pBuff);
typedef void (*uart_read_cb_t)(void);
typedef void (*uart_msc_read_cb_t)(MODEM_MSC_STRU* pModemMsc);
typedef void (*uart_switch_mode_cb_t)(void);


/*************************INT BEGIN*****************************/
/*****************************************************************************
* �� �� ��  : BSP_INT_Enable
*
* ��������  : ʹ��ĳ���ж�
*
* �������  : INT32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��40
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
*****************************************************************************/
BSP_S32 BSP_INT_Enable ( BSP_S32 s32Lvl);

#define DRV_VICINT_ENABLE(ulLvl)    BSP_INT_Enable(ulLvl)

/*****************************************************************************
 * �� �� ��  : BSP_INT_Disable
 *
 * ��������  : ȥʹ��ĳ���ж�
 *
 * �������  : INT32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��40
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
 *****************************************************************************/
BSP_S32 BSP_INT_Disable ( BSP_S32 s32Lvl);

#define  DRV_VICINT_DISABLE(ulLvl)    BSP_INT_Disable(ulLvl)

/*****************************************************************************
 * �� �� ��  : BSP_INT_Lock
 *
 * ��������  : ���������ж�
 *
 * �������  : ��
 *
 * �������  : ��
 *
 * �� �� ֵ  : �ж�����
 *
 * �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
 *****************************************************************************/
BSP_S32 BSP_INT_Lock (BSP_VOID);

/*****************************************************************************
 * �� �� ��  : BSP_INT_UnLock
 *
 * ��������  : ���ж�
 *
 * �������  : INT32 ulLocKKey  �ж����ţ�ǰһ��BSP_INT_Lock�ķ���ֵ
 *
 * �������  : ��
 *
 * �� �� ֵ  : �ж�����
 *
 * �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
 *****************************************************************************/
BSP_VOID BSP_INT_UnLock ( BSP_S32 s32LocKKey);

/*************************INT END*****************************/

/*************************WDT BEGIN*****************************/
#define BSP_HW_WATCHDOG       0
#define BSP_SW_WATCHDOG       1


typedef enum tagWDT_TIMEOUT_E
{
    WDT_TIMEOUT_1   = 0,        /*0xFFFF000/WDT_CLK_FREQ,  about 3657ms*/      /*WDT_CLK_FREQ = ARM_FREQ/6 = 70M*/
    WDT_TIMEOUT_2,              /*0x1FFFE000/WDT_CLK_FREQ, about 7314ms*/
    WDT_TIMEOUT_3,              /*0x3FFFC000/WDT_CLK_FREQ, about 14628ms*/
    WDT_TIMEOUT_4,              /*0x7FFF8000/WDT_CLK_FREQ, about 29257ms*/
    WDT_TIMEOUT_BUTT
}WDT_TIMEOUT_E;


/*���Ź�Ӳ����Ϣ���ݽṹ*/
typedef struct tagWDT_ID_INFO_S
{
    BSP_U32 u32PartNum;
    BSP_U32 u32DesignerID;
    BSP_U32 u32Version;
    BSP_U32 u32Config;
    BSP_U32 u32PrimeCellID;
}WDT_ID_INFO_S;

typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1
} SCI_DETECT_STATE;
typedef BSP_VOID(*wdt_timeout_cb)();


typedef void (*OMSCIFUNCPTR)(unsigned int ulVal);
#if defined (VERSION_V3R2)
void BSP_SCIFuncRegister(OMSCIFUNCPTR omSciFuncPtr);
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    BSP_SCIFuncRegister(omSciFuncPtr)
#else
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    DRV_OK
#endif

/*****************************************************************************
* �� �� ��  : BSP_WDT_Init
*
* ��������  : ��ʼ�����ƿ��Ź������ó�ʱʱ�䣬�ҽ��жϷ�����
*
* �������  : wdtId         ���Ź�ID,оƬ�ṩ1�����Ź���ID����Ϊ0
*             wdtTimeOuts   ���Ź���ʱʱ�䣬��λ��,ʱ������ܳ���51��
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_Init(BSP_U8 wdtId , BSP_U32 wdtTimeOuts);

/*****************************************************************************
* �� �� ��  : BSP_WDT_EnableWdt
*
* ��������  : �������Ź�
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_Enable(BSP_U8 wdtId);

/*****************************************************************************
* �� �� ��  : BSP_WDT_Disable
*
* ��������  : �رտ��Ź�
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_Disable(BSP_U8 wdtId);

/*****************************************************************************
* �� �� ��  : BSP_WDT_SetTime
*
* ��������  : ���ÿ��Ź��ĳ�ʱʱ��
*
* �������  : BSP_U8 u8WdtId:���Ź�ID��оƬ�ṩ�������Ź�����ֻʹ��һ����IDΪ0
*             WDT_TIMEOUT_E enTimeOut:���Ź���ʱ���
* �������  : ��
*
* �� �� ֵ  : OK:    �����ɹ�
*             ERROR: ����ʧ��
* ����˵��  :
*
*****************************************************************************/
BSP_S32 BSP_WDT_SetTimeOut(BSP_U8 u8WdtId, WDT_TIMEOUT_E enTimeOut);

/*****************************************************************************
* �� �� ��  : BSP_WDT_HardwareFeed
*
* ��������  : ���ÿ��Ź������Ĵ�����ι����
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_HardwareFeed(BSP_U8 wdtId);

/*****************************************************************************
* �� �� ��  : BSP_WDT_HardwareFeed_Force
*
* ��������  : ���ÿ��Ź������Ĵ�����ι����
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_HardwareFeed_Force(BSP_U8 u8WdtId);

/*****************************************************************************
* �� �� ��  : BSP_WDT_Switch
*
* ��������  : �л�ι����ʽ
*
* �������  : wdtId    ���Ź�ID
*           feedMode ι����ʽ(0������ι����1�����ι��)
*
* �������  : ��
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_Switch(BSP_U8 wdtId, BSP_U8 feedMode);

/*****************************************************************************
* �� �� ��  : BSP_WDT_IntInstall
*
* ��������  : �ڿ��Ź��жϷ��������ע�ᳬʱ������
*
* �������  : wdtId  ���Ź�ID
*		    p      ע��ĺ���ָ��
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_IntInstall(BSP_U8 wdtId, BSP_VOID * p);

/*****************************************************************************
* �� �� ��  : BSP_WDT_IntInstall
*
* ��������  : �ڿ��Ź��жϷ��������ж�س�ʱ������
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_IntUnInstall(BSP_U8 wdtId);

/*****************************************************************************
* �� �� ��  : BSP_WDT_TimeoutGet
*
* ��������  : ��ÿ��Ź�ʣ�೬ʱʱ��
*
* �������  : wdtId  ���Ź�ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2009��3��5��  v1.00  wangxuesong  ����
*****************************************************************************/
BSP_S32 BSP_WDT_TimeoutGet(BSP_U8 u8WdtId, BSP_U32 *u32TimeOut);

/*****************************************************************************
* �� �� ��  : BSP_WDT_reboot
*
* ��������  : ���Ź���λϵͳ
*
* �������  : BSP_VOID
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ʹ�ÿ��Ź�����ϵͳ��λ
*
*****************************************************************************/
BSP_VOID BSP_WDT_reboot(BSP_VOID);

/*************************WDT END*****************************/
/*************************SD BEGIN************************************/
#define WRFlAG     1
#define RDFlAG     0

typedef enum
{
    TFUP_FAIL = 0,  /*���*/
    TFUP_OK         /*��*/
}TFUP_DISPLAY_TYPE;

enum SD_MMC_OPRT_ENUM
{
    SD_MMC_OPRT_FORMAT = 0,
    SD_MMC_OPRT_ERASE_ALL,
    SD_MMC_OPRT_ERASE_SPEC_ADDR,
    SD_MMC_OPRT_WRITE,
    SD_MMC_OPRT_READ,
    SD_MMC_OPRT_BUTT
};

typedef unsigned int SD_MMC_OPRT_ENUM_UINT32;


/*SD���豸����*/
typedef struct _sd_dev_type_str
{
    unsigned long   devNameLen;
    char            devName[16];
}SD_DEV_TYPE_STR;

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_ATProcess
 ��������  : at^sd,SD��������д����������ʽ������
 �������  : �������� ulOp:
            0  ��ʽ��SD��
            1  ��������SD�����ݣ�
            2  ����ָ����ַ���ݵĲ���������ָ�����������ݳ���Ϊ512�ֽڡ�������ĵ�ַ��дȫ1
            3  д���ݵ�SD����ָ����ַ�У���Ҫ���ڶ����͵���������
            4  ��ȡulAddrָ���ĵ�ַ(ulAddr*512)��512���ֽڵ����ݵ�pucBuffer��

            ulAddr < address >  ��ַ����512BYTEΪһ����λ��������n��ʾ

            ulData
             < data >            �������ݣ���ʾ512BYTE�����ݣ�ÿ���ֽڵ����ݾ���ͬ��
             0       �ֽ�����Ϊ0x00
             1       �ֽ�����Ϊ0x55
             2       �ֽ�����Ϊ0xAA
             3       �ֽ�����Ϊ0xFF

 �������  : pulErr
 �� �� ֵ  : 0 ��OK  �� 0 ��Error

            ����Ĵ���ֵ�����*pulErr��
            0 ��ʾSD������λ
            1 ��ʾSD����ʼ��ʧ��
            2 ��ʾ<opr>�����Ƿ�����Ӧ������֧��(�ô�����ATʹ��,����Ҫ����ʹ��)
            3 ��ʾ<address>��ַ�Ƿ�������SD����������
            4 ����δ֪����
*****************************************************************************/
extern  unsigned long  BSP_SDMMC_ATProcess(SD_MMC_OPRT_ENUM_UINT32 ulOp,
                unsigned long ulAddr,  unsigned long ulData,unsigned char *pucBuffer,unsigned long *pulErr);
#define DRV_SDMMC_AT_PROCESS(ulOp,ulAddr,ulData,pucBuffer,pulErr)   \
                     BSP_SDMMC_ATProcess (ulOp,ulAddr,ulData,pucBuffer,pulErr)

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
/*****************************************************************************
* �� �� ��  : sd_mmc_blk_w
*
* ��������  :д���ӿ�
*
* �������  : u32StartBlk ��ʼ��
				  pu8DataBuf  д���ݻ���
				  u32Len д���ݴ�С������Ϊ512�ֽڵ�������
* �������  : NA
*
* �� �� ֵ  :  �ɹ�����0
*
* ����˵��  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_w(BSP_U32 u32StartBlk,BSP_U8 *pu8DataBuf,BSP_U32 u32Len);
/*****************************************************************************
* �� �� ��  : sd_mmc_blk_r
*
* ��������  : �����ӿ�
*
* �������  : u32StartBlk ��ʼ��
				  pu8DataBuf  �����ݻ���
				  u32Len  �����ݴ�С������Ϊ512�ֽڵ�������
* �������  : NA
*
* �� �� ֵ  :  �ɹ�����0
*
* ����˵��  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_r(BSP_U32 u32StartBlk,BSP_U8 *pu8DataBuf,BSP_U32 u32Len);
/*****************************************************************************
* �� �� ��  : sd_mmc_blk_erase
*
* ��������  : ��������ӿ�
*
* �������  : u32StartBlk ��ʼ��
				  u32EndBlk  ��ֹ��
* �������  : NA
*
* �� �� ֵ  :  �ɹ�����0
*
* ����˵��  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_erase(BSP_U32 u32StartBlk,BSP_U32 u32EndBlk);
/*****************************************************************************
* �� �� ��  : sd_mmc_get_status
*
* ��������  : ����λ��ѯ
*
* �������  : void
* �������  : NA
*
* �� �� ֵ  : 0 : ��λ��-1: ����λ
*
* ����˵��  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_get_status(BSP_VOID);
#endif

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_GetOprtStatus
 ��������  : at^sd,SD����ǰ����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
            0: δ����������Ѿ����;
            1: ������
            2: �ϴβ���ʧ��
*****************************************************************************/
extern unsigned long BSP_SDMMC_GetOprtStatus(void);
#define DRV_SDMMC_GET_OPRT_STATUS()    BSP_SDMMC_GetOprtStatus()

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_AddHook
 ��������  : TFģ�鹳�Ӻ���ע�ᡣ
 �������  : hookType���ص��������ͣ�
                       0����������ļ���Ϣ����õĻص�������
                       1��TF������֪ͨOM�Ļص�������
                       2��TF���γ�֪ͨOM�Ļص�������
                       3�� TF����ʼ����֪ͨU�̵Ļص�������
             p���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ������ͬһ���ͻص��������ظ�ע��Ḳ����ǰ���á�
*****************************************************************************/
//#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern int sdmmcAddHook (int hookType , void * p);/*y00186965 for sd_update*/
#define DRV_SDMMC_ADD_HOOK(hookType,p)    sdmmcAddHook(hookType,p)
//#else
//extern int BSP_SDMMC_AddHook(int hookType, void * p);
//#define DRV_SDMMC_ADD_HOOK(hookType,p)    BSP_SDMMC_AddHook(hookType,p)
//#endif

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_UsbGetStatus
 ��������  : ����SD��״̬
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   0  Ϊ����
           ��0 ������

*****************************************************************************/
extern unsigned int BSP_SDMMC_UsbGetStatus(void);
#define DRV_SDMMC_USB_STATUS()    BSP_SDMMC_UsbGetStatus();

/*****************************************************************************
* �� �� ��  : sdmmc_ClearWholeScreen
* ��������  : SD������NV�ָ������ʾ������
* �������  : ��
* �������  : ��
* �� �� ֵ  :��
* ����˵��  : ��
*****************************************************************************/
extern void sdmmc_ClearWholeScreen(void);
#define DRV_SDMMC_CLEAR_WHOLE_SCREEN()    sdmmc_ClearWholeScreen()

/*****************************************************************************
* �� �� ��  : sdmmc_UpdateDisplay
* ��������  : SD������NV�ָ������ʾ����ʾ
* �������  : BOOL UpdateStatus
* �������  : ��
* �� �� ֵ  :��
* ����˵��  : �����ɹ���NV������ɺ���øú�����
              ����ʧ�ܺ���øú������
*****************************************************************************/
extern void sdmmc_UpdateDisplay(int UpdateStatus);
#define DRV_SDMMC_UPDATE_DISPLAY(state)    sdmmc_UpdateDisplay(state)

/*****************************************************************************
* �� �� ��  : DRV_SD_GET_STATUS
*
* ��������  : ����λ��ѯ
*
* �������  : void
* �������  : NA
*
* �� �� ֵ  : 0 : ��λ��-1: ����λ
*
* ����˵��  : NA
*
*****************************************************************************/
extern int DRV_SD_GET_STATUS(void);

/*****************************************************************************
* �� �� ��  : DRV_SD_GET_CAPACITY
*
* ��������  : ��������ѯ
*
* �������  : void
* �������  : NA
*
* �� �� ֵ  : 0 : ʧ�ܣ�>0: ������
*
* ����˵��  : NA
*
*****************************************************************************/
extern int DRV_SD_GET_CAPACITY(void);

/*****************************************************************************
* �� �� ��  : DRV_SD_TRANSFER
*
* ��������  : ���ݴ���
*
* �������  : struct scatterlist *sg    ���������ݽṹ��ָ��
                            unsigned dev_addr   ��д���SD block ��ַ
                            unsigned blocks    ��д���block����
                            unsigned blksz      ÿ��block�Ĵ�С����λ�ֽ�
                            int wrflags    ��д��־λ��д:WRFlAG ; ��:RDFlAG
* �������  : NA
*
* �� �� ֵ  : 0 : �ɹ�������: ʧ��
*
* ����˵��  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_TRANSFER(struct scatterlist *sg, unsigned dev_addr,unsigned blocks, unsigned blksz, int wrflags);
#endif
/*****************************************************************************
* �� �� ��  : DRV_SD_SG_INIT_TABLE
*
* ��������  : SD������ݴ���sg list��ʼ��
*
* �������  : const void *buf		��������buffer��ַ
				  unsigned int buflen	��������buffer��С��С��32K, ��СΪ512B��������
				  					����32K, ��СΪ32KB�������������bufferΪ128K
* �������  : NA
*
* �� �� ֵ  :  0 : �ɹ�;  ����:ʧ��
* ����˵��  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_SG_INIT_TABLE(const void *buf,unsigned int buflen);
#endif
/*****************************************************************************
* �� �� ��  : DRV_SD_MULTI_TRANSFER
*
* ��������  : SD������ݴ���
*
* �������  : unsigned dev_addr	��д���SD block��ַ
				  unsigned blocks		��д���block ����
				  unsigned blksz		ÿ��block �Ĵ�С����λ�ֽ�
				  int write			��д��־λ��д:1;	��:0
* �������  : NA
*
* �� �� ֵ  :  0 : �ɹ�;  ����:ʧ��
* ����˵��  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_MULTI_TRANSFER(unsigned dev_addr,unsigned blocks,unsigned blksz,int write);
#endif
/*************************SD END**************************************/

/*************************SD BEGIN*****************************/

/*****************************************************************************
* �� �� ��  : SDIO_check_card
*
* ��������  :
*
* �������  : BSP_S32 s32CardNo
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 SDIO_check_card(BSP_S32 s32CardNo);

/*****************************************************************************
* �� �� ��  : read_write_blkdata
*
* ��������  :

* �������  :

* �������  :
* �� �� ֵ  :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_S32  read_write_blkdata(BSP_S32 s32CardNo, BSP_U32 u32Addr,
                            BSP_U32 u32DataSize,
                            BSP_U8  *pu8DataBuff,
                            BSP_U8  *pu8CmdRespBuff,
                            BSP_U8  *pu8ErrRespBuff,
                            BSP_VOID (*callback)(BSP_U32 u32ErrData),
                            BSP_S32 s32NoOfRetries,
                            BSP_S32 s32Flags);
/*************************SD END*****************************/

/*************************DLOAD BEGIN*****************************/
/*--------------------------------------------------------------*
 * �궨��                                                       *
 *--------------------------------------------------------------*/
/* ������ */
#define DLOAD_OK                    BSP_OK
#define DLOAD_ERROR                 BSP_ERROR
#define DLOAD_ERR_NOT_INITED        BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_MODULE_NOT_INITED)
#define DLOAD_ERR_NULL_PTR          BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_NULL_PTR)
#define DLOAD_ERR_INVALID_PARA      BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_INVALID_PARA)
#define DLOAD_ERR_ALLOC_FAILED      BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_BUF_ALLOC_FAILED)
#define DLOAD_ERR_FREE_FAILED       BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_BUF_FREE_FAILED)
#define DLOAD_ERR_RETRY_TIMEOUT     BSP_DEF_ERR(BSP_MODU_DLOAD,BSP_ERR_RETRY_TIMEOUT)

#define DLOAD_ERR_NO_BACKUP         BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 1)  /* �ޱ��ݰ汾 */
#define DLOAD_ERR_OPEN_FAILED       BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 2)  /* ���⴮�ڴ�ʧ�� */
#define DLOAD_ERR_SEM_CREAT         BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 3)  /* �ź�������ʧ�� */
#define DLOAD_ERR_ABORT             BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 4)  /* ������ֹ */
#define DLOAD_ERR_MODE_MISMATCH     BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 5)  /* ����ģʽ��ƥ�� */
#define DLOAD_ERR_INVALID_ATSTRING  BSP_DEF_ERR(BSP_MODU_DLOAD, BSP_ERR_SPECIAL + 6)  /* AT�ַ����Ƿ� */



/*--------------------------------------------------------------*
 * ö�ٶ���                                                     *
 *--------------------------------------------------------------*/

/* ����ģʽö�� */
typedef enum tagDLOAD_MODE_E
{
    DLOAD_MODE_DOWNLOAD = 0,
    DLOAD_MODE_NORMAL,
    DLOAD_MODE_DATA,
    DLOAD_MODE_MAX
}DLOAD_MODE_E;
typedef enum
{
    NORMAL_DLOAD = 0,   /*��������ģʽ*/
    FORCE_DLOAD = 1    /*ǿ������ģʽ*/
}DLOAD_TYPE;

extern BSP_S32 BSP_DLOAD_GetDloadInfo(unsigned char atCmdBuf[], unsigned int dloadType);
#define DRV_GET_DLOAD_INFO(atCmdBuf, dloadType)    BSP_DLOAD_GetDloadInfo(atCmdBuf, dloadType)
/*****************************************************************************
 �� �� ��  : BSP_DLOAD_GetAuthorityId
 ��������  : ��ȡ���ؼ�ȨЭ��Id
 �������  : unsigned char *buf
                          int len
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
                      -1������ʧ�ܡ�
*****************************************************************************/
extern BSP_S32 BSP_DLOAD_GetAuthorityId(unsigned char *buf, BSP_S32 len);
#define DRV_GET_AUTHORITY_ID(buf,len) BSP_DLOAD_GetAuthorityId(buf,len)

/*****************************************************************************
 �� �� ��  : drvShutdown
 ��������  : ����ػ�
 �������  : ��
 �������  : eReason��        �ػ�ԭ��
 �� �� ֵ  : ��
*****************************************************************************/
typedef enum DRV_SHUTDOWN_REASON_tag_s
{
    E5_DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����                 */
    E5_DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣                   */
    E5_DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�          */
    E5_DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�               */
    E5_DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ                 */
    E5_DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
    E5_DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ         */
    E5_DRV_SHUTDOWN_BUTT
}E5_DRV_SHUTDOWN_REASON_ENUM;

typedef enum DRV_SHUTDOWN_REASON_tag
{
    DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����           */
    DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣            */
    DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�    */
    DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�         */
    DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ           */
    DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
    DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ */
    DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_ENUM;

void drvShutdown( DRV_SHUTDOWN_REASON_ENUM eReason );
#define DRV_SHUT_DOWN(eReason) drvShutdown(eReason)

/*****************************************************************************
 �� �� ��  : BSP_DFS_GetCurCpuLoad
 ��������  : ��ѯ��ǰCPU
 �������  : pu32AcpuLoad ACPUloadָ��
             pu32CcpuLoad CCPUloadָ��
 �������  : pu32AcpuLoad ACPUloadָ��
             pu32CcpuLoad CCPUloadָ��
 �� �� ֵ  : 0:  �����ɹ���
            -1������ʧ�ܡ�
*****************************************************************************/
extern BSP_U32 BSP_DFS_GetCurCpuLoad(BSP_U32 *pu32AcpuLoad,BSP_U32 *pu32CcpuLoad);
#define DRV_GET_CUR_CPU_LOAD(pu32AcpuLoad,pu32CcpuLoad) BSP_DFS_GetCurCpuLoad(pu32AcpuLoad,pu32CcpuLoad)
/*************************************************
 �� �� ��   : BSP_HKADC_BatVoltGet
 ��������   : ���ص�ǰ��ص�ѹֵ
 �������   : pslData : ��ص�ѹֵ
 �������   : pslData : ��ص�ѹֵ
 �� �� ֵ   :0:��ȡ�ɹ�
            -1:��ȡʧ��
*************************************************/
extern BSP_S32 BSP_HKADC_BatVoltGet(BSP_S32 *ps32Data);
#define DRV_HKADC_BAT_VOLT_GET(ps32Data)   BSP_HKADC_BatVoltGet(ps32Data)

/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ���ص�ǰ��Ʒ����
 �������   : ��
 �������   : ��
 �� �� ֵ   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern BSP_U32 BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

/*****************************************************************************
 �� �� ��  : BSP_DLOAD_GetAuthorityVer
 ��������  : Get Authority version
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern BSP_S32 BSP_DLOAD_GetAuthorityVer(BSP_U8 *str, BSP_S32 len);
#define DRV_GET_AUTHORITY_VERSION(str, len )   BSP_DLOAD_GetAuthorityVer(str, len )



/*--------------------------------------------------------------*
 * ����ָ�����Ͷ���                                             *
 *--------------------------------------------------------------*/
typedef BSP_U32 (*BSP_DLOAD_AtCallBack)( BSP_VOID* pDataIn, BSP_U32 ulLen);
typedef BSP_U32 (*BSP_DLOAD_NVGetInfoCb)( BSP_VOID* pDataOut, BSP_U32 ulLen);
typedef BSP_U32 (*BSP_DLOAD_NVSetInfoCb)( BSP_VOID* pDataIn, BSP_U32 ulLen);

/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetDloadVer
*
* ��������  : ��ѯ����Э��汾�š�����ϢBSP�̶�дΪ2.0��
*
* �������  : BSP_S8 *str   :�ַ���������
*             BSP_S32 len   :�ַ�������
* �������  : BSP_S8 *str   :�ַ���������
*
* �� �� ֵ  : DLOAD_ERROR   :��������Ƿ�
*             ����          :�����ַ�������
*
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetDloadVer(BSP_CHAR *str, BSP_U32 len);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetISOVer
*
* ��������  : ��ȡ��̨�汾���ַ���
*
* �������  : BSP_S8 *str   :�ַ���������
*             BSP_S32 len   :�ַ�������
* �������  : BSP_S8 *str   :�ַ���������
*
* �� �� ֵ  : DLOAD_ERROR   :��������Ƿ�
*             ����          :�����ַ�������
*
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetISOVer(BSP_CHAR *str, BSP_U32 len);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetProductId
*
* ��������  : ��ȡ��Ʒ�����ַ���
*
* �������  : BSP_S8 *str   :�ַ���������
*             BSP_S32 len   :�ַ�������
* �������  : BSP_S8 *str   :�ַ���������
*
* �� �� ֵ  : DLOAD_ERR_INVALID_PARA    :��������Ƿ�
*             DLOAD_ERROR               :ʧ��
*             ����                      :�����ַ�������
*
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetProductId(BSP_CHAR *str, BSP_U32 len);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetDloadType
*
* ��������  : ��ȡ��������
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : 0 :����ģʽ
*             1 :ǿ��ģʽ
*
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetDloadType(BSP_VOID);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetCurMode
*
* ��������  : ���õ�ǰ����ģʽ
*
* �������  : BSP_VOID
* �������  : DLOAD_MODE_NORMAL     :����ģʽ
*             DLOAD_MODE_DATA       :����ģʽ
*             DLOAD_MODE_DOWNLOAD   :����ģʽ
*
* �� �� ֵ  : ��
*
* ����˵��  : ATģ�����
*             ����ģʽ֧�ֵ���:
*                 BSP_DLOAD_GetCurMode(DLOAD_MODE_DOWNLOAD)
*             ����ģʽ֧�ֵ���:
*                 BSP_DLOAD_GetCurMode(DLOAD_MODE_DATA)
*
*****************************************************************************/
BSP_VOID BSP_DLOAD_SetCurMode(DLOAD_MODE_E eDloadMode);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetCurMode
*
* ��������  : ��ȡ��ǰ����ģʽ
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : DLOAD_MODE_NORMAL     :����ģʽ
*             DLOAD_MODE_DATA       :����ģʽ
*             DLOAD_MODE_DOWNLOAD   :����ģʽ
*
* ����˵��  : ��
*
*****************************************************************************/
DLOAD_MODE_E BSP_DLOAD_GetCurMode(BSP_VOID);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_SetSoftLoad
*
* ��������  : ����������־
*
* �������  : BSP_BOOL bSoftLoad  :
*             BSP_FALSE :��vxWorks����
*             BSP_TRUE  :��bootrom����
* �������  : ��
*
* �� �� ֵ  : ��
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_VOID BSP_DLOAD_SetSoftLoad (BSP_BOOL bSoftLoad);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetSoftLoad
*
* ��������  : ��ȡ������־
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : BSP_TRUE  :��bootrom����
*             BSP_FALSE :��vxWorks����
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_BOOL BSP_DLOAD_GetSoftLoad (BSP_VOID);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_SetCdromMarker
*
* ��������  : �����豸��̬��־
*
* �������  : BSP_BOOL bCdromMarker  :
*             BSP_TRUE  :���������豸��̬
*             BSP_FALSE :����bootrom�豸��̬
* �������  : ��
*
* �� �� ֵ  : ��
*
* ����˵��  : ��������̨�ļ�ʱ������Ϊ�ϱ������豸��̬�����ָ�NV��
*             ������ǰ̨�ļ�ʱ������Ϊ�ϱ�bootrom�豸��̬���ָ�NV��
*
*****************************************************************************/
BSP_VOID BSP_DLOAD_SetCdromMarker(BSP_BOOL bCdromMarker);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetCdromMarker
*
* ��������  : ��ȡ�豸��̬��־
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : BSP_TRUE  :�ϱ������豸��̬
*             BSP_FALSE :�ϱ�bootrom�豸��̬
*
* ����˵��  : ��������̨�ļ�ʱ������Ϊ�ϱ������豸��̬�����ָ�NV��
*             ������ǰ̨�ļ�ʱ������Ϊ�ϱ�bootrom�豸��̬���ָ�NV��
*
*****************************************************************************/
BSP_BOOL BSP_DLOAD_GetCdromMarker (BSP_VOID);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_SendData
*
* ��������  : ͨ�����⴮����PC�˷�������
*
* �������  : pBuf      :���ݻ�����
*             u32Len    :���ݻ���������
* �������  : pBuf      :���ݻ�����
*
* �� �� ֵ  : ��
*
* ����˵��  : pBuf���뱣֤cache line(32�ֽ�)����
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_SendData(BSP_CHAR *pBuf, BSP_U32 u32Len);
/*****************************************************************************
* �� �� ��  : BSP_DLOAD_AtProcReg
*
* ��������  : ע��AT������
*
* �������  : pFun
* �������  : ��
*
* �� �� ֵ  : DLOAD_OK:�ɹ�
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_AtProcReg (BSP_DLOAD_AtCallBack pFun);

/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetSoftwareVer
*
* ��������  : ��ȡ����汾��
*
* �������  : BSP_S8 *str   :�ַ���������
*             BSP_S32 len   :�ַ�������
* �������  : BSP_S8 *str   :�ַ���������
*
* �� �� ֵ  : DLOAD_ERROR   :��������Ƿ�
*             ����          :�����ַ�������
*
* ����˵��  : ATģ�����
*             ����ģʽ֧��
*             ����ģʽ֧��
*
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetSoftwareVer(BSP_CHAR *str, BSP_U32 len);

/*************************DLOAD END*****************************/


/*************************GPIO START*****************************/

/* �жϴ�������ö��*/
typedef enum tagGPIO_INT_TRIG_E
{
    GPIO_HIGH_LEVEL          	=  1,/* �ߵ�ƽ����*/
    GPIO_LOW_LEVEL           	=  2,/* �͵�ƽ����*/
    GPIO_BOTH_EDGE           	=  3,/* ˫�ش���*/
    GPIO_RISING_EDGE        	=  4,/* �����ش���*/
    GPIO_DECENDING_EDGE    	    =  5 /* �½��ش���*/
} GPIO_INT_TRIG_E;

#ifdef BSP_CPE
typedef enum tagCPE_SIGNAL_INTENSITY_E
{
	SIGNALNULL,
    SIGNALLOW,
    SIGNALMIDDLE,
    SIGNALHIGH,
    SIGNALMAX
}CPE_SIGNAL_INTENSITY_E;

typedef enum tagCPE_SIGNAL_STATUS_E
{
     SIGNAL_STATUS_ABNORMAL,    //�ź��쳣
     SIGNAL_STATUS_NORMAL,      //�ź�����
     SIGNAL_STATUS_MAX
}CPE_SIGNAL_STATUS_E;

typedef enum tagGPIO_CTRL_E
{
    GPIO_ON,
    GPIO_OFF,
    GPIO_MAX
}GPIO_CTRL_E;

#endif


/* PV500����2��GPIO */
typedef enum tagGPIO_GPIO_NUM_E
{
    GPIO_DEF_GPIO0          	=  0,
    GPIO_DEF_GPIO1           	=  1,
    GPIO_DEF_MAX
} GPIO_GPIO_NUM_E;

/* ��ѯģʽ */
typedef enum tagGPIO_GPIO_GETMODE_NUM_E
{
    LINE_STATE          	=  0,
    FORCE_LOAD_CTRL       =  1
} GPIO_GETMODE_NUM_E;


/*****************************************************************************
 �� �� ��  : USB_NDIS_GetMaxTxNum
 ��������  : �ṩ��Э��ջ��ȡ����һ�η������IP������
 �������  :
 �������  : unsigned long
 �� �� ֵ  : IP������
*****************************************************************************/
extern unsigned long USB_NDIS_GetMaxTxNum(void);
#define DRV_USB_NDIS_GETMAXTXNUM()     USB_NDIS_GetMaxTxNum()
/*****************************************************************************
* �� �� ��  : BSP_GPIO_Init
*
* ��������  : GPIO��ʼ���ӿڣ��ҽ��жϷ������
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_VOID  BSP_GPIO_Init (BSP_VOID);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_DrcSet
*
* ��������  : ����GPIO���ŵķ���
*
* �������  : BSP_U32 u32Mask        ָ�������õ�GPIOλ
*             BSP_U32 u32Directions  �����õķ���ֵ,0�����룻1�����
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32  BSP_GPIO_DrcSet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask, BSP_U32 u32Directions);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_DrcGet
*
* ��������  : ��ѯGPIO ���ŵķ���
*
* �������  : ��
* �������  : BSP_U32 * pu32Directions  ���淵�صķ���ֵ
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_DrcGet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 * pu32Directions);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_ValSet
*
* ��������  : ����GPIO ���ŵĵ�ƽֵ
*
* �������  : BSP_U32 u32Mask  ָ�������õ�GPIOλ
*             BSP_U32 u32Data  �����õĵ�ƽֵ
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_ValSet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask, BSP_U32 u32Data);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_ValGet
*
* ��������  : ��ѯGPIO���ŵĵ�ƽֵ
*
* �������  : ��
* �������  : BSP_U32 * pu32Data  ���淵�صĵ�ƽֵ
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_ValGet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 * pu32Data);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntMaskSet
*
* ��������  : �����ж�λ
*
* �������  : BSP_U32 u32Mask  ָ�������жϵ�GPIOλ
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntMaskSet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntUnMaskSet
*
* ��������  : ʹ���ж�λ
*
* �������  : BSP_U32 u32Mask  ָ��ʹ���жϵ�GPIOλ
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntUnMaskSet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntStateGet
*
* ��������  : ��ѯ�ж�״̬λ
*
* �������  : BSP_U32 *pu32Stat
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntStateGet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 *pu32Stat);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_RawIntStateGet
*
* ��������  : ��ѯԭʼ�ж�״̬λ
*
* �������  : ��
* �������  : BSP_U32 *pu32RawStat  ���淵�ص�ԭʼ�ж�״̬
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_RawIntStateGet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 *pu32RawStat);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntStateClear
*
* ��������  : ����ж�״̬λ����1��ʾ��Ӧ�ж�λ����ж�
*
* �������  : BSP_U32 u32Mask  ָ���������GPIOλ
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntStateClear(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntTriggerSet
*
* ��������  : �����жϴ�����ʽ�������ء��½��ء�˫���ء��ߵ�ƽ���͵�ƽ
*
* �������  : BSP_U32 u32Mask             ָ�������õ�GPIOλ
*             GPIO_INT_TRIG enTrigMode  �жϴ���ģʽ
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntTriggerSet(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask, GPIO_INT_TRIG_E enTrigMode);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntInstall
*
* ��������  : ��������ģ��ע��GPIO�жϴ������Ľӿ�
*
* �������  : BSP_U32 u32Mask  ָ��GPIOλID
*             BSP_VOID* routine  ��ע��Ļص�����ָ��
*             BSP_S32 para       �ص���������
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntInstall(GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask, BSP_VOID* routine,BSP_S32 para);

/*****************************************************************************
* �� �� ��  : BSP_GPIO_IntUnInstall
*
* ��������  : ��������ģ��ж��GPIO�жϴ������Ľӿ�
*
* �������  : BSP_U32 u32Mask  ָ��GPIOλID
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   liumengcun  creat
*****************************************************************************/
extern  BSP_S32 BSP_GPIO_IntUnInstall (GPIO_GPIO_NUM_E enGPIONum, BSP_U32 u32Mask);
/*************************GPIO END *****************************/



/*************************TIMER BEGIN*****************************/
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Connect
*
* ��������  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable usr clock interrupts.
*
* �������  : FUNCPTR routine   routine to be called at each clock interrupt
              BSP_S32 arg	        argument with which to call routine
              BSP_S32 s32UsrClkid      which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
//BSP_S32  BSP_USRCLK_Connect(FUNCPTR routine, BSP_S32 arg, BSP_S32 s32UsrClkid);
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerStart
*
* ��������  : ��������Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
*             u32Cycles   Timer�Ĵ����ļ���ֵ
* �������  : ��
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
BSP_S32    BSP_USRCLK_TimerStart(BSP_S32 s32UsrClkid,BSP_U32 u32Cycles);
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerStop
*
* ��������  : �رյ���Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
* �������  : ��
* �� �� ֵ  : ��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
BSP_S32    BSP_USRCLK_TimerStop(BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerValue
*
* ��������  : ��������Timer��ʱ��.
*
* �������  : s32UsrClkid   Timer Id
* �������  : Value      ��ǰTimer value�Ĵ����ļ���ֵ
* �� �� ֵ  : OK&������
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
BSP_U32  BSP_USRCLK_TimerValue(BSP_S32 s32UsrClkid, BSP_U32 *pu32Value);
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Disable
*
* ��������  : This routine disables user clock interrupts.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
BSP_S32   BSP_USRCLK_Disable (BSP_S32 s32UsrClkid);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Enable
*
* ��������  : This routine enables user clock interrupts.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
BSP_S32    BSP_USRCLK_Enable (BSP_S32 s32UsrClkid);
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_RateGet
*
* ��������  : This routine returns the interrupt rate of the system aux clock.
*
* �������  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* �������  : BSP_S32 * pu32ClkRate  clk rate
* �� �� ֵ  : OK&������
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
BSP_S32     BSP_USRCLK_RateGet(BSP_S32 s32UsrClkId, BSP_S32 * pu32ClkRate);

/*****************************************************************************
* �� �� ��  : BSP_USRCLK_RateSet
*
* ��������  : This routine sets the interrupt rate of the usr clock.
*
* �������  : BSP_S32 ticksPerSecond   number of clock interrupts per second
              BSP_S32 s32UsrClkid         which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
BSP_S32  BSP_USRCLK_RateSet(BSP_S32 ticksPerSecond, BSP_S32 s32UsrClkid);
/*****************************************************************************
* �� �� ��  : BSP_USRCLK_TimerMilliSecValue
*
* ��������  : ��õ�ǰTimer�ĺ���ֵ.
*
* �������  : s32UsrClkid        Timer Id
* �������  : BSP_U32 * pu32Value ��ǰTimer value�Ĵ����ĺ���ֵ
* �� �� ֵ  : OK&����������
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat
*****************************************************************************/
BSP_U32  BSP_USRCLK_TimerMilliSecValue(BSP_S32 s32UsrClkId ,BSP_U32 * pu32Value);
/*****************************************************************************
* �� �� ��  : sysClkTicksGet
*
* ��������  : ���ϵͳʱ������������tick��.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ϵͳʱ������������tick��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat

*****************************************************************************/
BSP_U32 sysClkTicksGet (BSP_VOID);

/*****************************************************************************
* �� �� ��  : sysAuxClkTicksGet
*
* ��������  : ���ϵͳ����ʱ������������tick��.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ϵͳ����ʱ������������tick��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat

*****************************************************************************/
BSP_U32 sysAuxClkTicksGet (BSP_VOID);
/*****************************************************************************
* �� �� ��  : sysTimestampRateSet
*
* ��������  : This routine sets the interrupt rate of the timestamp clock.  It does
*             not enable system clock interrupts unilaterally, but if the timestamp is currently enabled, the clock is disabled and then
*             re-enabled with the new rate.  Normally it is called by usrRoot()
*             in usrConfig.c.
*
* �������  : int ticksPerSecond   number of clock interrupts per second
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
BSP_S32 sysTimestampRateSet(BSP_S32 ticksPerSecond);

/*****************************************************************************
* �� �� ��  : sysTimestampRateGet
*
* ��������  : This routine returns the interrupt rate of the timestamp clock.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : The number of ticks per second of the system clock.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
BSP_S32 sysTimestampRateGet (BSP_VOID);
/*************************TIMER END*****************************/

/*************************DRX BEGIN*****************************/
/*PSע�ắ������*/
typedef BSP_U8   (*BSPRegDRXFunc)(BSP_VOID);

typedef enum tagDRX_SLEEP_MODE_E
{
    DRX_WEEK_SLEEP_MODE_E = 0x0,
    DRX_DEEP_SLEEP_MODE_E = 0x1,
    DRX_WEEK2_SLEEP_MODE_E = 0x2,
	DRX_NO_SLEEP_MODE_E = 0x3
}DRX_SLEEP_MODE_E;


typedef enum tagDRX_TIMER_ID_E
{
    DRX_LTESYS_TIMER = 0x0,
    DRX_LTET3412_TIMER,
    DRX_LTEVPLMN_TIMER,
    DRX_LTETSRHC_TIMER,
    DRX_LTETA_TIMER,
    DRX_DEEP_SLEEP_TIMER,
    DRX_LTE_PS32K_TIMER,
    DRX_LTE_PS32K_BASETIMER,
    DRX_LTE_NO_TIMER
}DRX_TIMER_ID_E;

typedef enum tagDRX_TIMER_MODE_E
{
    DRX_TIMER_FREE_MODE = 0x0,
    DRX_TIMER_USER_MODE
}DRX_TIMER_MODE_E;

typedef enum tagDRX_REG_CB_E
{
    DRX_PS_GET_SLEEP_INFO = 0x0,
    DRX_RTC_TIME_START = 0x1,
	DRX_RTC_TIME_END = 0x2
}DRX_REG_CB_E;

/*****************************************************************************
* �� �� ��  : set32KHwTimerMode
*
* ��������  : ��ѯ32KӲ��ʱ�Ӽ�����ֵ
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_S32 set32KHwTimerMode(DRX_TIMER_MODE_E eMode);
/*****************************************************************************
* �� �� ��  : get32KHwTimerMode
*
* ��������  : ��ѯ32KӲ��ʱ�Ӽ������Ĺ���ģʽ
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
DRX_TIMER_MODE_E get32KHwTimerMode();
/*****************************************************************************
* �� �� ��  : BSP_DRX_RegCb
*
* ��������  : PSע�ắ��
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_VOID BSP_DRX_RegCb (DRX_REG_CB_E enType, BSPRegDRXFunc pFunc);
/*****************************************************************************
* �� �� ��  : usrTimer4Start
*
* ��������  : ����32KӲ��ʱ�Ӷ�ʱ��
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_S32 usrTimer4Start(DRX_TIMER_ID_E eTimerId, BSP_U32 u32Count);
/*****************************************************************************
* �� �� ��  : usrTimer4Stop
*
* ��������  : ֹͣ32KӲ��ʱ�Ӷ�ʱ��
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_S32 usrTimer4Stop(DRX_TIMER_ID_E eTimerId);
/*****************************************************************************
* �� �� ��  : usrTimer4Value
*
* ��������  : ��ѯ32K BBP ʱ�Ӷ�ʱ��ʣ��ֵ
*
* �������  :
* �������  :
* �� �� ֵ   :
*
* �޸ļ�¼  :

*****************************************************************************/
BSP_S32 usrTimer4Value(DRX_TIMER_ID_E eTimerId);
/*************************DRX END*****************************/

/*************************IPCONFIG BEGIN************************/

typedef enum tagBSP_NET_IPVER_E
{
  IPV4 = 0,
  IPV6
}BSP_NET_IPVER_E;

typedef struct tagBSP_NET_NETMASK_S
{
  BSP_U8 au8Mask[4];   //��������
}BSP_NET_NETMASK_S;

typedef struct tagBSP_NET_MAC_S
{
  BSP_U8 au8MAC[6];   // MAC��ַ
}BSP_NET_MAC_S;

typedef union tagBSP_NET_IP_U
{
  BSP_U8 au8IPV4[4];    // ��������ĵ�ַΪIPV4�ĵ�ַ
  BSP_U8 au8IPV6[16];   //��������ĵ�ַΪIPV6�ĵ�ַ
}BSP_NET_IP_U;

BSP_U8* BSP_GetMacAddr();
//typedef VOID (*PFN_DEVICE_NOTIFY_HOOK)(ENUM_DEVICE_NOTIFY_EVENT ulEvent, ENUM_DEVICE_STATSU ulStatus);


/* ���ؿ��ؽṹ */
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved1 : 14;/* bit[0-13] : reversed */
        unsigned int  rtsen         : 1;/* bit[14] : rts enable, up stream flow ctrl  */
        unsigned int  ctsen         : 1;/* bit[15] : cts enable, down stream flow ctrl */
        unsigned int  reserved2 : 16;/* bit[16-31] : reversed */
    } reg;
} uart_flow_ctrl_union;




/*****************************************************************************
* �� �� ��  : BSP_SetPsMacAddr
*
* ��������  : �޸�PS mac��ַ
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2009��9��2��   liumengcun  creat
*****************************************************************************/
BSP_S32 BSP_SetPsMacAddr(BSP_U8 u8MacAddr0,BSP_U8 u8MacAddr1,BSP_U8 u8MacAddr2,
		BSP_U8 u8MacAddr3,BSP_U8 u8MacAddr4,BSP_U8 u8MacAddr5);

/*****************************************************************************
* �� �� ��  : BSP_SetOsMacAddr
*
* ��������  : �޸�vxWorks mac��ַ
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2009��9��2��   liumengcun  creat
*****************************************************************************/
BSP_S32 BSP_SetOsMacAddr(BSP_U8 u8MacAddr0,BSP_U8 u8MacAddr1,BSP_U8 u8MacAddr2,
		BSP_U8 u8MacAddr3,BSP_U8 u8MacAddr4,BSP_U8 u8MacAddr5);

/*****************************************************************************
* �� �� ��  : BSP_NET_OMIpMacSet
*
* ��������  : ����vxWorks�� IP/NetMask/Mac��ַ,�����浽Flash�ļ�ϵͳ��
*
* �������  : u32IPVer: IP�汾: V4/V6
*             pOMIP:    IP��ַ
*             pstNetMask:NetMask
*             pOMMac:   Mac��ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_NET_OMIpMacSet(BSP_NET_IPVER_E u32IPVer, BSP_NET_IP_U* pOMIP, BSP_NET_NETMASK_S* stNetMask, BSP_NET_MAC_S* pOMMac);

/*****************************************************************************
* �� �� ��  : BSP_NET_OMIpMacGet
*
* ��������  : ��ȡvxWorks�� IP/NetMask/Mac��ַ
*
* �������  : u32IPVer: IP�汾: V4/V6
*             pOMIP:    IP��ַ
*             pstNetMask:NetMask
*             pOMMac:   Mac��ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_NET_OMIpMacGet(BSP_NET_IPVER_E u32IPVer, BSP_NET_IP_U* pOMIP, BSP_NET_NETMASK_S* pstNetMask, BSP_NET_MAC_S* pOMMac);

/*****************************************************************************
* �� �� ��  : BSP_NET_PsMacSet
*
* ��������  : ����Э��ջMac��ַ,�����浽Flash�ļ�ϵͳ��
*
* �������  : u32IPVer: IP�汾: V4/V6
*             pOMIP:    IP��ַ
*             pstNetMask:NetMask
*             pOMMac:   Mac��ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_NET_PsMacSet(BSP_NET_MAC_S* pLteMac);

/*****************************************************************************
* �� �� ��  : BSP_NET_PsMacGet
*
* ��������  : ��ȡЭ��ջMac��ַ
*
* �������  : pLteMac:   ��ȡ��Mac��ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_NET_PsMacGet(BSP_NET_MAC_S* pLteMac);
/*************************IPCONFIG END************************/

/*************************SPI BEGIN************************/
/*�����붨��*/
#define BSP_ERR_SPI_MODULE_NOT_INITED BSP_DEF_ERR(BSP_MODU_SPI, BSP_ERR_MODULE_NOT_INITED)
#define BSP_ERR_SPI_INVALID_PARA      BSP_DEF_ERR(BSP_MODU_SPI, BSP_ERR_INVALID_PARA)
#define BSP_ERR_SPI_RETRY_TIMEOUT     BSP_DEF_ERR(BSP_MODU_SPI, BSP_ERR_RETRY_TIMEOUT)

#define BSP_ERR_SPI_SEM_CREATE        BSP_DEF_ERR(BSP_MODU_SPI, 1)
#define BSP_ERR_SPI_SEM_LOCK          BSP_DEF_ERR(BSP_MODU_SPI, 2)
#define BSP_ERR_SPI_SEM_UNLOCK        BSP_DEF_ERR(BSP_MODU_SPI, 3)
#define BSP_ERR_SPI_DATASIZE_INVALID  BSP_DEF_ERR(BSP_MODU_SPI, 4)
#define BSP_ERR_SPI_ATTR_NOTSET       BSP_DEF_ERR(BSP_MODU_SPI, 5)
#define BSP_ERR_SPI_PROT_INVALID      BSP_DEF_ERR(BSP_MODU_SPI, 6)
#define BSP_ERR_SPI_TMOD_INVALID      BSP_DEF_ERR(BSP_MODU_SPI, 7)
#define BSP_ERR_SPI_RECEIVE_POLL      BSP_DEF_ERR(BSP_MODU_SPI, 8)



/*****************************************************************************
* �� �� ��  : BSP_SPI_SetAttr
*
* ��������  : ����SPI�ļĴ��������ÿ��������ֳ��ȡ�����֡���ȵȡ�
*
* �������  : enSpiID        ��Ҫ���õ�SPI�ţ��Լ�������ƬƬѡ�������õ�Ƭѡ�š�
*             pstSpiDevAttr  ��¼SPI����豸���ԵĽṹ��ָ�룬�ṹ���Ա�����豸
                             ��Ҫ�������ֳ��ȣ�����֡���ȣ�ʹ��Э�飬�����ʵȡ�
*
* �������  : ��
*
* �� �� ֵ  : OK    ���ճɹ�
*             ERROR ����ʧ��
*****************************************************************************/
BSP_S32 BSP_SPI_SetAttr(SPI_DEV_S *enSpiID,SPI_DEV_ATTR_S *pstSpiDevAttr);

/*****************************************************************************
* �� �� ��  : BSP_SPI_Write
*
* ��������  : ͨ��SPI���豸д������
*
* �������  : pstWriteData ��¼��SPI���ݴ����й���Ϣ�Ľṹ��ָ�룬��Ա����
                           Ҫ��д��SPI�ţ�Ƭѡ�ţ�����ģʽ��
*             pSendData    �洢���յ����ݻ�����ָ��
*             u32Length    �����յ����ݳ���
*
* �������  : ��
*
* �� �� ֵ  : OK    ���ճɹ�
*             ERROR ����ʧ��
*****************************************************************************/
BSP_S32 BSP_SPI_Write(SPI_DATA_HANDLE_S *pstWriteData,BSP_VOID *pSendData, BSP_U32 u32Length);

/*****************************************************************************
* �� �� ��  : BSP_SPI_Read
*
* ��������  : ͨ��SPI��ȡ�豸����
*
* �������  : pstReadData  ��¼��SPI���ݴ����й���Ϣ�Ľṹ��ָ�룬��Ա����
                           Ҫ��д��SPI�ţ�Ƭѡ�ţ�����ģʽ�ȡ�
*             u32Length    �����յ����ݳ���
*
* �������  : pRecData     �洢���յ����ݻ�����ָ�롣
*
* �� �� ֵ  : OK    ���ճɹ�
*             ERROR ����ʧ��
*****************************************************************************/
BSP_S32 BSP_SPI_Read(SPI_DATA_HANDLE_S *pstReadData,BSP_VOID *pRecData, BSP_U32 u32Length);

/*****************************************************************************
* �� �� ��  : BSP_SPI_GetAttr
*
* ��������  : ��ȡ��ǰSPI���õ�����
*
* �������  : enSpiId    Ҫ��ѯ��SPI�š�
*
* �������  : pstDevAttr ���SPI���ԵĽṹ��ָ�롣
*
* �� �� ֵ  : OK    ���ճɹ�
*             ERROR ����ʧ��
*****************************************************************************/
BSP_S32 BSP_SPI_GetAttr(SPI_DEV_ID_E enSpiId, SPI_DEV_ATTR_S *pstDevAttr);
/*************************SPI END************************/

/*************************IPCM BEGIN************************/
#ifdef BSP_ASIC_V7R1
/* ����������*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_COMARM = 0x1,
    IPC_CORE_APPARM = 0x2,
    IPC_CORE_DSP    = 0x3,
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;
#else

/* ����������*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_ARM11 = 0x0,   /* P500�ϵ�IPC */
    IPC_CORE_A9,
    IPC_CORE_CEVA,
    IPC_CORE_TENS0,
    IPC_CORE_TENS1,
    IPC_CORE_DSP,
    IPC_CORE_APPARM = 0x0,  /* V7R1/V3R2�ϵ�IPC */
    IPC_CORE_COMARM,
    IPC_CORE_LTEDSP,
    IPC_CORE_VDSP,
    IPC_CORE_ZSP,
    IPC_CORE_DSP_GU,
    IPC_CORE_ACPU = 0x0,/* V9R1 SFT�ϵ�IPC */
    IPC_CORE_CCPU,
    IPC_CORE_MCU,
    IPC_CORE_HIFI,
    IPC_CORE_BBE16,


    /* !!!!����Ԫ������ӵ����  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

#endif
typedef enum tagIPC_INT_LEV_E
{
    IPC_INT_DSP_MODEM,
    IPC_INT_DSP_APP,
    IPC_INT_MODEM_APP,
    IPC_ACPU_INT_SRC_CCPU_NVIM,
    IPC_INT_DICC_USRDATA = 6,
    IPC_INT_DICC_RELDATA = 7,
    IPC_INT_BUTTOM
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_ICC,
    IPC_SEM_NAND,
    IPC_SEM_MEM,
    IPC_SEM_DICC,
    IPC_SEM_RFILE_LOG,          /*����flashless��ά�ɲ�*/
    IPC_SEM_EMMC,
    IPC_SEM_NVIM,
    IPC_SEM_SMP_CPU0 = 21,
    IPC_SEM_SMP_CPU1 = 22,
    IPC_SEM_SMP_CPU2 = 23,
    IPC_SEM_SMP_CPU3 = 24,
    IPC_SEM_SYNC = 25,
    IPC_SEM_SYSCTRL = 30,
    IPC_SEM_ZSP_HALT = 31,
    IPC_SEM_BUTTOM
}IPC_SEM_ID_E;

/*****************************************************************************
* �� �� ��  : BSP_DRV_IPCIntInit
*
* ��������  : IPCģ���ʼ��
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��3��5��   wangjing  creat
*****************************************************************************/
BSP_S32 BSP_DRV_IPCIntInit();

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntEnable
*
* ��������  : ʹ��ĳ���ж�
*
* �������  :
                BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/
BSP_S32 BSP_IPC_IntEnable (IPC_INT_LEV_E ulLvl);
#define DRV_IPC_INTENABLE(var)		BSP_IPC_IntEnable(var)

/*****************************************************************************
 * �� �� ��  : BSP_INT_Disable
 *
 * ��������  : ȥʹ��ĳ���ж�
 *
 * �������  :
                BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  : 2011��4��11�� wangjing creat
 *****************************************************************************/
BSP_S32 BSP_IPC_IntDisable (IPC_INT_LEV_E ulLvl);
#define DRV_IPC_INTDISABLE(var)     BSP_IPC_IntDisable(var)


 /*****************************************************************************
* �� �� ��  : BSP_IPC_IntSend
*
* ��������  : �����ж�
*
* �������  :
                IPC_INT_CORE_E enDstore Ҫ�����жϵ�core
                BSP_U32 ulLvl Ҫ���͵��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/

BSP_S32 BSP_IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
#define DRV_IPC_INTSEND(a,b)		BSP_IPC_IntSend(a,b)

 /*****************************************************************************
 * �� �� ��  : BSP_IPC_SemTake
 *
 * ��������  : ��ȡ�ź���
 *
 * �������  : ��
 * �������  : ��
 *
 * �� �� ֵ  : ��
 *
 * �޸ļ�¼  : 2011��4��11�� wangjing creat
 *****************************************************************************/
 BSP_S32 BSP_IPC_SemTake(BSP_U32 u32SignalNum);
 /*****************************************************************************
 * �� �� ��  : BSP_IPC_SemGive
 *
 * ��������  : �ͷ��ź���
 *
 * �������  : ��
 * �������  : ��
 *
 * �� �� ֵ  : ��
 *
 * �޸ļ�¼  : 2011��4��11�� wangjing creat
 *****************************************************************************/
 BSP_VOID BSP_IPC_SemGive(BSP_U32 u32SignalNum);

 /*****************************************************************************
  * �� �� ��  : BSP_IPC_SpinLock
  *
  * ��������  : ��ȡ�ź���
  *
  * �������  : ��
  * �������  : ��
  *
  * �� �� ֵ  : ��
  *
  * �޸ļ�¼  : 2011��4��11�� wangjing creat
  *****************************************************************************/

 BSP_VOID BSP_IPC_SpinLock (BSP_U32 u32SignalNum);
#define DRV_SPIN_LOCK()		BSP_IPC_SpinLock(IPC_SEM_ICC)

 /*****************************************************************************
   * �� �� ��  : BSP_IPC_SpinUnLock
   *
   * ��������  : �ͷ��ź���
   *
   * �������  : ��
   * �������  : ��
   *
   * �� �� ֵ  : ��
   *
   * �޸ļ�¼  : 2011��4��11�� wangjing creat
   *****************************************************************************/
  BSP_VOID BSP_IPC_SpinUnLock (BSP_U32 u32SignalNum);

#define DRV_SPIN_UNLOCK()		BSP_IPC_SpinUnLock(IPC_SEM_ICC)
 /*****************************************************************************
  * �� �� ��  : BSP_IPC_DebugShow
  *
  * ��������  : ��ά�ɲ�ӿ�
  *
  * �������  : ��
  * �������  : ��
  *
  * �� �� ֵ  : ��
  *
  * �޸ļ�¼  : 2011��4��11�� wangjing creat
  *****************************************************************************/
 BSP_VOID BSP_IPC_DebugShow();


/*************************IPCM END************************/

/*************************BBP INT BEGIN************************/

/* BBP��֡�жϴ�����,���ж�ֻ��ӦModem��*/
typedef BSP_VOID (*BSPBBPIntTimerFunc)(BSP_VOID);
/* ����ҵ������DMA��������ж�,���ж�ֻ��ӦModem��*/
typedef BSP_VOID (*BSPBBPIntDlTbFunc)(BSP_VOID);




/*****************************************************************************
* �� �� ��  : BSP_BBPGetCurTime
*
* ��������  : ��PS���ã�������ȡϵͳ��ȷʱ��
*
* �������  : ��
* �������  : BSP_U32 u32CurTime:��ǰʱ��
*
* �� �� ֵ  : BSP_OK : ��ȡ�ɹ�
*                        BSP_ERR_INVALID_PARA  :��ȡʧ��
*
* �޸ļ�¼  : 2011��3��7��  wangjing  creat
*****************************************************************************/
BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime);


/*****************************************************************************
* �� �� ��  : BSP_BBPIntTimerRegCb
*
* ��������  : ��PS���ã����������ע��1ms��ʱ�жϵĻص�
*
* �������  :
* �������  :��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2011��3��7��  wangjing  creat
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerRegCb(BSPBBPIntTimerFunc pFunc);

/*****************************************************************************
* �� �� ��  : BSP_BBPIntDlTbRegCb
*
* ��������  : ��PS���ã����������ע����������DMA��������жϵĻص�
*
* �������  :
* �������  :��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2011��3��7��  wangjing  creat
*****************************************************************************/
BSP_VOID BSP_BBPIntDlTbRegCb(BSPBBPIntDlTbFunc pFunc);

/*****************************************************************************
* �� �� ��  : BSP_BBPIntTimerClear
*
* ��������  : ��PS���ã��������1ms��ʱ�ж�
*
* �������  : ��
* �������  :��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2011��5��31��  wangjing  creat
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerClear();

/*****************************************************************************
* �� �� ��  : BSP_BBPIntTimerEnable
*
* ��������  : ��PS���ã�������1ms��ʱ�ж�
*
* �������  : ��
* �������  :��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2011��3��7��  wangjing  creat
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerEnable();


/*****************************************************************************
* �� �� ��  : BSP_BBPIntTimerDisable
*
* ��������  : ��PS���ã������ر�1ms��ʱ�ж�
*
* �������  : ��
* �������  :��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2011��3��7��  wangjing  creat
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerDisable();


/*************************BBP INT END************************/

/*************************CIPHER BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/

/* ��ӡ���� */
#define CIPHER_PRNT_NOT           BSP_LOG_LEVEL_MAX       /* ����ӡ�κ���Ϣ */
#define CIPHER_PRNT_ERR           BSP_LOG_LEVEL_ERROR     /* ֻ��ӡ������Ϣ */
#define CIPHER_PRNT_WAR           BSP_LOG_LEVEL_WARNING   /* ֻ��ӡ����, �澯��Ϣ*/
#define CIPHER_PRNT_LOG           BSP_LOG_LEVEL_DEBUG     /* ��ӡ����, �澯, ������Ϣ */

/* ������ */
#define CIPHER_SUCCESS                  0

#define CHN_BUSY                    0
#define CHN_FREE                    1
/* ע��CIPHER������ҪΪ��ֵ */
#define CIPHER_ERROR_BASE               0x80000800

typedef enum tagCIPHER_ERR_CODE_E
{
    CIPHER_ERR_CODE_NULL_PTR = 1,
    CIPHER_ERR_CODE_NO_MEM ,
    CIPHER_ERR_CODE_NOT_INIT ,
    CIPHER_ERR_CODE_FIFO_FULL ,
    CIPHER_ERR_CODE_INVALID_CHN ,
    CIPHER_ERR_CODE_INVALID_OPT ,
    CIPHER_ERR_CODE_ALIGN_ERROR ,
    CIPHER_ERR_CODE_PURGING ,
    CIPHER_ERR_CODE_TIME_OUT,
    CIPHER_ERR_CODE_INVALID_ENUM,
    CIPHER_ERR_CODE_INVALID_RD,
    CIPHER_ERR_CODE_RD_NULL,
    CIPHER_ERR_CODE_INVALID_KEY,
    CIPHER_ERR_CODE_CHECK_ERROR,
    CIPHER_ERR_CODE_BDLEN_ERROR,
    CIPHER_ERR_CODE_INVALID_NUM
}CIPHER_ERR_CODE_E;

#define CIPHER_NULL_PTR      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NULL_PTR))
#define CIPHER_NO_MEM        ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_MEM))
#define CIPHER_NOT_INIT      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NOT_INIT))
#define CIPHER_FIFO_FULL     ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_FIFO_FULL))
#define CIPHER_INVALID_CHN   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_CHN))
#define CIPHER_INVALID_OPT   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_OPT))
#define CIPHER_ALIGN_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_ALIGN_ERROR))
#define CIPHER_PURGING       ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_PURGING))
#define CIPHER_TIME_OUT      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_TIME_OUT))
#define CIPHER_INVALID_ENUM  ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_ENUM))
#define CIPHER_INVALID_RD    ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_RD))
#define CIPHER_RDQ_NULL      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_RD_NULL))
#define CIPHER_INVALID_KEY   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_KEY))
#define CIPHER_CHECK_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_CHECK_ERROR))
#define CIPHER_BDLEN_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_BDLEN_ERROR))
#define CIPHER_INVALID_NUM   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_NUM))

#define CIPHER_UNKNOWN_ERROR ((BSP_S32)(CIPHER_ERROR_BASE|0xff))

/**************************************************************************
  ö�ٶ���
**************************************************************************/
enum CIPHER_SECURITY_CHANNEL_ENUM
{
    CIPHER_SECURITY_CHANNEL_0            = 0,                /*ͨ��0*/
    CIPHER_SECURITY_CHANNEL_1            = 1,                /*ͨ��1*/
    CIPHER_SECURITY_CHANNEL_2            = 2,                /*ͨ��2*/
    CIPHER_SECURITY_CHANNEL_3            = 3,                /*ͨ��3*/

    CIPHER_SECURITY_CHANNEL_BUTT
};

/* ͨ����*/
#define LTE_SECURITY_CHANNEL_NAS    CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_RRC    CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_UL_SRB CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_SRB CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_UL_DRB CIPHER_SECURITY_CHANNEL_0
#define LTE_SECURITY_CHANNEL_DL_DRB CIPHER_SECURITY_CHANNEL_3

/* CIPHER������������ */
typedef enum tagCIPHER_SINGLE_OPT_E
{
    /* ������������,����ö��ֵ��Ĵ�������ֵһ�� */
    CIPHER_OPT_ENCRYPT = 0x0,   /* ���� */
    CIPHER_OPT_DECRYPT = 0x1,   /* ���� */
    CIPHER_OPT_PROTECT_SMAC = 0x2,   /* �������������MAC����Ϊ2Byte */
    CIPHER_OPT_PROTECT_LMAC = 0x3,   /* �������������MAC����Ϊ4Byte */
    CIPHER_OPT_CHECK_PRE_SMAC  = 0x4,   /* ��������MAC����Ϊ2Byte��λ��������ǰ�� */
    CIPHER_OPT_CHECK_POST_SMAC = 0x5,   /* ��������MAC����Ϊ2Byte��λ�������ݺ��� */
    CIPHER_OPT_CHECK_PRE_LMAC  = 0x6,   /* ��������MAC����Ϊ4Byte��λ��������ǰ�� */
    CIPHER_OPT_CHECK_POST_LMAC = 0x7,   /* ��������MAC����Ϊ4Byte��λ�������ݺ��� */
    CIPHER_SINGLE_OPT_BUTTOM
}CIPHER_SINGLE_OPT_E;


/* CIPHER������������ */     //PDCP ���������������
typedef enum tagCHPHER_RELA_OPT_E
{
    /*  ������������ */
    CIPHER_PDCP_PRTCT_ENCY,     /*PDCP��������(����)*/
    CIPHER_PDCP_DECY_CHCK,      /*PDCP���ܼ��(����)*/

    CIPHER_NAS_ENCY_PRTCT,      /* NAS����ܱ���(����) */
    CIPHER_NAS_CHCK_DECY,       /* NAS�������(����) */

	CIPHER_RELA_OPT_BUTTOM
}CIPHER_RELA_OPT_E;

/* CIPHER֧�ֵ��㷨����,ע��ö��ֵ��Ĵ�������ֵһ�� */
typedef enum tagCIPHER_ALGORITHM_E
{
    CIPHER_ALG_NULL = 0,        /* ���㷨 */
    CIPHER_ALG_SNOW3G  = 1,     /* SNOW3G�㷨 */
    CIPHER_ALG_AES_128 = 2,     /* AES128�㷨 */
    CIPHER_ALG_AES_192 = 3,     /* AES192�㷨 */
    CIPHER_ALG_AES_256 = 4,     /* AES256�㷨 */
    CIPHER_ALG_BUTTOM
}CIPHER_ALGORITHM_E;

/* CIPHER��Կ����, ע��ö��ֵ��Ĵ�������ֵһ�� */
typedef enum tagCIPHER_KEY_LEN_E
{
    CIPHER_KEY_L128 = 0,        /* ��Կ����128 bit */
    CIPHER_KEY_L192 = 1,        /* ��Կ����192 bit */
    CIPHER_KEY_L256 = 2,        /* ��Կ����256 bit */
    CIPHER_KEY_LEN_BUTTOM
}CIPHER_KEY_LEN_E;

/* CIPHER�����ύ���� */
typedef enum tagCIPHER_SUBMIT_TYPE_E
{
    CIPHER_SUBM_NONE = 0,           /* �����κ�֪ͨ */
    CIPHER_SUBM_BLK_HOLD = 1,       /* ѭ����ѯ�ȴ���� */
    CIPHER_SUBM_CALLBACK = 2,       /* �ص�����֪ͨ */
    CIPHER_SUBM_BUTTOM
}CIPHER_SUBMIT_TYPE_E;

/* CIPHER֪ͨ���� */
typedef enum tagCIPHER_NOTIFY_STAT_E
{
    CIPHER_STAT_OK = 0,           /* �ɹ���� */
    CIPHER_STAT_CHECK_ERR = 1,    /* �����Լ����� */
    CIPHER_STAT_BUTTOM
}CIPHER_NOTIFY_STAT_E;

typedef enum CIPHER_HDR_BIT_ENUM
{
    CIPHER_HDR_BIT_TYPE_0              = 0,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ0�����������˹���*/
    CIPHER_HDR_BIT_TYPE_5              = 1,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_7              = 2,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_12             = 3,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�����뱣��*/

    CIPHER_APPEND_HDR_BIT_TYPE_5       = 4,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_7       = 5,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_12      = 6,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�������뱣����ֻ����*/

    CIPHER_HDR_BIT_TYPE_BUTT
}CIPHER_HDR_E;

/* ��ɻص��������Ͷ��� */
/*
u32ChNum   :  ͨ����;
u32SourAddr:  Դ��ַ
u32DestAddr:  Ŀ�ĵ�ַ
enStatus   :  ֪ͨ��״̬,����: ��� / ���ݴ������ / ��������Լ�����
u32Private   :  �û�˽������;
*/
typedef BSP_VOID (*CIPHER_NOTIFY_CB_T)(BSP_U32 u32ChNum, BSP_U32 u32SourAddr,
              BSP_U32 u32DestAddr, CIPHER_NOTIFY_STAT_E enStatus, BSP_U32 u32Private);

typedef BSP_VOID (*CIPHER_FREEMEM_CB_T)(BSP_VOID* pMemAddr);

/**************************************************************************
  STRUCT����
**************************************************************************/

/* �㷨������Ϣ */
typedef struct tagCIHPER_ALG_INFO_S
{
    BSP_U32 u32KeyIndexSec;
    BSP_U32 u32KeyIndexInt;
    CIPHER_ALGORITHM_E enAlgSecurity;          /* ��ȫ�����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
    CIPHER_ALGORITHM_E enAlgIntegrity;         /* �����Բ����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
}CIHPER_ALGKEY_INFO_S;

/* CIPHER������Ϣ���� */
typedef struct tagCIHPER_SINGLE_CFG_S
{
    CIPHER_SINGLE_OPT_E enOpt;          /* ������������(��DMA��������������㷨����) */
    BSP_U8 u8BearId;
    BSP_U8 u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
	BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
} CIHPER_SINGLE_CFG_S;

typedef struct tagCIHPER_RELA_CFG_S
{
    CIPHER_RELA_OPT_E enOpt;             /* ������������(��DMA��������������㷨����) */
    BSP_U8 u8BearId;
    BSP_U8 u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
	BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* ����������һ�����㷨��Կ������Ϣ */

} CIHPER_RELA_CFG_S;


/*�������������Ϣ*/
typedef struct tagACC_SINGLE_CFG_S
{
    BSP_U32 u32BearId;
    BSP_U32 u32AppdHeaderLen;
    BSP_U32 u32HeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
    BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    BSP_U32 u32Offset;                  /* ʹ�����ݾ������ݰ���ʼ��ַƫ��*/
    BSP_U32 u32OutLen;                  /* ʹ�õ������ݳ���*/
    BSP_U32 u32Aph;                      /*���Ӱ�ͷ��*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
} ACC_SINGLE_CFG_S;

/**************************************************************************
  ��������
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_RegistNotifyCB
*
* ��������  : ע��֪ͨ�ص�����
*
* �������  : pFunNotifyCb: ֪ͨ�ص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*****************************************************************************/
BSP_S32 BSP_CIPHER_RegistNotifyCB(CIPHER_NOTIFY_CB_T pFunNotifyCb);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_FreeMemCB
*
* ��������  : ע��Memory�ͷŻص�����
*
* �������  : u32Chn: ͨ����
*             bSrc:   0:����Buffer / 1:���Bufffer
*             pFunFreeMemCb: Memory�ͷŻص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
BSP_S32 BSP_CIPHER_RegistFreeMemCB(BSP_U32 u32Chn, BSP_BOOL bSrc, CIPHER_FREEMEM_CB_T pFunFreeMemCb);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_Purge
*
* ��������  : ������е�ǰָ��ͨ����CIPHER����(�����ӿ�,���purge�󷵻�)
*
* �������  : u32Chn: Ҫ�����ͨ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_Purge(BSP_U32 u32Chn);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_SingleSubmitTask
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڵ���������
*
* �������  : u32Chn: ͨ����
*             pInMemMgr: ����buffer�ڴ����ṹָ��
*             pOutMemMgr:���buffer�ڴ����ṹָ��
*             pstCfg: Cipher������������
*             pstSubmAttr:�ύ������
*             u32Private:˽������
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*             ʧ��:CIPHER_NOT_INIT
*             CIPHER_INVALID_CHN
*             CIPHER_NULL_PTR
*             CIPHER_ALIGN_ERROR
*             CIPHER_INVALID_ENUM
*             CIPHER_PURGING
*             CIPHER_FIFO_FULL
*             CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_SingleSubmitTask(BSP_U32 u32Chn, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
                    CIHPER_SINGLE_CFG_S *pstCfg, CIPHER_SUBMIT_TYPE_E enSubmAttr, BSP_U32 u32Private);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_RelaSubmitTask
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڹ���������
*
* �������  : u32Chn: ͨ����
*             pInMemMgr: ����buffer�ڴ����ṹָ��
*             pOutMemMgr:���buffer�ڴ����ṹָ��
*             pstCfg: Cipher������������
*             enSubmAttr:�ύ������
*             u32Private:˽������
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*             ʧ��:CIPHER_NOT_INIT
*             CIPHER_INVALID_CHN
*             CIPHER_NULL_PTR
*             CIPHER_ALIGN_ERROR
*             CIPHER_INVALID_ENUM
*             CIPHER_PURGING
*             CIPHER_FIFO_FULL
*             CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_RelaSubmitTask(BSP_U32 u32Chn, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
                    CIHPER_RELA_CFG_S *pstCfg, CIPHER_SUBMIT_TYPE_E enSubmAttr, BSP_U32 u32Private);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_SetKeyIndex
*
* ��������  : ������Կֵ
*
* �������  : pKeyAddr   : ��Կ��ַ
*             enKeyLen   : ��Կ����
*             u32KeyIndex: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_ENUM
*           :      CIPHER_INVALID_KEY
*****************************************************************************/
BSP_S32 BSP_CIPHER_SetKey(const BSP_VOID* pKeyAddr,CIPHER_KEY_LEN_E enKeyLen,BSP_U32 u32KeyIndex);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_GetKey
*
* ��������  : ����KeyIndex��ȡKey�ĵ�ַ
*
* �������  : u32KeyIndex: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:����KeyIndex�õ���Key�ĵ�ַ
*           : ʧ��:��ȡKeyֵ���ڵ�ַʧ��,����0
*****************************************************************************/
BSP_U32 BSP_CIPHER_GetKey(BSP_U32 u32KeyIndex);

/*****************************************************************************
* �� �� ��  : CIPHER_DataBuffPara
*
* ��������  : ��ȡ�ϲ�������Ϣ��������Ϣ
*
* �������  : u32Chn        : ͨ����
*             bSrc          : TRUE:Դ��ַ���������� / FALSE:Ŀ�ĵ�ַ��������
*             u32BufOft     : ����bufferָ��ƫ��
*             u32LenOft     : Buffer����ƫ��
*             NextOft       : ��һ�ڵ�ƫ��
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
BSP_S32 BSP_CIPHER_SetDataBufPara(BSP_U32 u32Chn, BSP_BOOL bSrc, BSP_U32 u32BufOft,
                                  BSP_U32 u32LenOft, BSP_U32 u32NextOft);

/*****************************************************************************
* �� �� ��  : CIPHER_GetCmplSrcBuff
*
* ��������  : ��ȡ�Ѿ�������ɵ�Դ���ݵ�ַ
*
* �������  : u32ChNum     : ͨ����
* �������  : pu32SourAddr : ������ɵ�Դ��ַ;
*             pu32DestAddr : ������ɵ�Ŀ�ĵ�ַ
*             penStatus    : ������ɵ�״̬
*             pu32Private  : ���ص�˽������
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_RD
*****************************************************************************/
BSP_S32 BSP_CIPHER_GetCmplSrcBuff(BSP_U32 u32Chn, BSP_U32 *pu32SourAddr,
              BSP_U32 *pu32DestAddr, CIPHER_NOTIFY_STAT_E *penStatus, BSP_U32 *pu32Private);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_GetBdFifoAddr
*
* ��������  : ���ڻ�ȡ��ǰ���õ�BDFIFO�׵�ַ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : BDFIFO�׵�ַ
*****************************************************************************/
BSP_U32 BSP_Accelerator_GetBdFifoAddr();

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_DMA
*
* ��������  : Ϊָ��ͨ�����������������ڵ�����DMA����
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*             pInMemMgr    : ����buffer�׵�ַ
*             pOutMemMgr   : ���buffer�׵�ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_DMA(BSP_U32 u32BdFifoAddr, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_Cipher
*
* ��������  : Ϊָ��ͨ��������������������ҪCipher���м��ܵĲ���
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*             pInMemMgr    : ����buffer�׵�ַ
*             pOutMemMgr   : ���buffer�׵�ַ
*             pstCfg       : Cipher������Ϣ
* �������   : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_Cipher(BSP_U32 u32BdFifoAddr, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
               ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_GetStatus
*
* ��������  : ��ȡ��ǰͨ��״̬
*
* �������  :  ��
* �������   : ��
* �� �� ֵ  : ͨ��æ/����
*****************************************************************************/
BSP_S32 BSP_Accelerator_GetStatus();

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_Enable
*
* ��������  : ʹ���������
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_Enable(BSP_U32 u32BdFifoAddr);
/*************************CIPHER END************************/

/*************************DMA BEGIN************************/
/**************************************************************************
  ȫ�ֱ�������
**************************************************************************/

/**************************************************************************
  ö�ٶ���
**************************************************************************/
/*DMA transport type*/
typedef enum tagDMA_TRANS_TYPE_E
{
    MEM2MEM_DMA = 0,    /* �ڴ浽�ڴ棬DMA����*/
    MEM2PRF_DMA,        /* �ڴ浽���裬DMA����*/
    PRF2MEM_DMA,        /* ���赽�ڴ棬DMA����*/
    PRF2PRF_DMA,        /* ���赽���裬DMA����*/
    PRF2MEM_PRF,        /* ���赽�ڴ棬��������*/
    PRF2PRF_SRCPRF = 5, /* ���赽���裬Դ��������*/
    MEM2PRF_PRF,        /* �ڴ浽���裬��������*/
    PRF2PRF_DSTPRF,     /* ���赽���裬Ŀ����������*/
    CTL_TT_FC_BUTTOM    /* ���ֵ���ж���*/
} DMA_TRANS_TYPE_E;

/**************************************************************************
  �궨��
**************************************************************************/

/*�����붨��*/
#define DMA_SUCCESS                    BSP_OK

#define BSP_ERR_DMA_MODULE_NOT_INITED   BSP_DEF_ERR(BSP_MODU_DMAC, BSP_ERR_MODULE_NOT_INITED)
#define BSP_ERR_DMA_NULL_PTR            BSP_DEF_ERR(BSP_MODU_DMAC, BSP_ERR_NULL_PTR)
#define BSP_ERR_DMA_INVALID_PARA        BSP_DEF_ERR(BSP_MODU_DMAC, BSP_ERR_INVALID_PARA)

#define BSP_ERR_DMA_CHANNEL_BUSY        BSP_DEF_ERR(BSP_MODU_DMAC, 1)
#define BSP_ERR_DMA_ALL_CHANNEL_BUSY    BSP_DEF_ERR(BSP_MODU_DMAC, 2)
#define BSP_ERR_DMA_STOP_FAIL           BSP_DEF_ERR(BSP_MODU_DMAC, 3)

/**************************************************************************
  ö�ٶ���
**************************************************************************/

/* ͨ���߼�״̬*/
typedef enum tagDMA_CHN_USR_STATUS_E
{
    DMA_CHN_IDLE = 0, /* ͨ������*/
    DMA_CHN_ALLOCED = 1 /* ͨ���Ѿ�������*/
}DMA_CHN_USR_STATUS_E;

/* ͨ������*/
typedef enum tagDMA_CHN_TYPE_E
{
    DMA_FIXED_MODE = 0,   /* �̶�ͨ����ʹ�����֮�󲻻��Զ��ͷţ����ǿ���ͨ���ͷ�ͨ���ӿ��ͷ�*/
    DMA_COMMON_MODE = 1,   /* ��ͨͨ����ʹ�����֮����Զ��ͷţ�Ҳ����ͨ���ͷ�ͨ���ӿ��ͷ�*/
    DMA_SPECIAL_MODE = 2   /*
����ͨ����ʹ�����֮�󲻻��Զ��ͷţ�ͨ���ͷŽӿ�Ҳ�޷��ͷţ��Ҹ�ͨ����ҪĳЩ���⴦��Ŀǰֻ��Э��ջʹ��*/
}DMA_CHN_TYPE_E;

/* ͨ��״̬ */
typedef enum tagDMA_CHN_STATUS_E
{
    DMA_CHN_FREE = 0,   /* ͨ������ */
    DMA_CHN_BUSY = 1   /* ͨ��æ */
}DMA_CHN_STATUS_E;



/* DESCRIPTION
 * This data type is used for selecting the transfer width for the
 *  source and/or destination on a DMA channel when using the specified
 *  driver API functions. This data type maps directly to the AMBA AHB
 *  HSIZE parameter.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CTLx.SRC_TR_WIDTH, CTLx.DST_TR_WIDTH
 */

typedef enum tagDMA_TRANS_WIDTH_E {
    DMA_TRANS_WIDTH_8   = 0x0,/* 8bitλ��*/
    DMA_TRANS_WIDTH_16  = 0x1,/* 16bitλ��*/
    DMA_TRANS_WIDTH_32  = 0x2,/* 32bitλ��*/
    DMA_TRANS_WIDTH_64  = 0x3,/* 64bitλ��*/
    DMA_TRANS_WIDTH_128 = 0x4,/* 128bitλ��*/
    DMA_TRANS_WIDTH_256 = 0x5 /* 256bitλ��*/
}DMA_TRANS_WIDTH_E;

/* DESCRIPTION
 *  This data type is used for selecting the burst transfer length
 *  on the source and/or destination of a DMA channel when using the
 *  specified driver API functions. These transfer length values do
 *  not relate to the AMBA HBURST parameter.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CTLx.SRC_MSIZE, CTLx.DEST_MSIZE
 */
typedef enum tagDMA_BURST_TRANS_LENGTH_E
{
    DMA_MSIZE_1   = 0x0,/* burst���ȣ���һ�δ���ĸ���Ϊ1��*/
    DMA_MSIZE_4   = 0x1,/* burst���ȣ���һ�δ���ĸ���Ϊ4��*/
    DMA_MSIZE_8   = 0x2,/* burst���ȣ���һ�δ���ĸ���Ϊ8��*/
    DMA_MSIZE_16  = 0x3,/* burst���ȣ���һ�δ���ĸ���Ϊ16��*/
    DMA_MSIZE_32  = 0x4,/* burst���ȣ���һ�δ���ĸ���Ϊ32��*/
    DMA_MSIZE_64  = 0x5,/* burst���ȣ���һ�δ���ĸ���Ϊ64��*/
    DMA_MSIZE_128 = 0x6,/* burst���ȣ���һ�δ���ĸ���Ϊ128��*/
    DMA_MSIZE_256 = 0x7 /* burst���ȣ���һ�δ���ĸ���Ϊ256��*/
}DMA_BURST_TRANS_LENGTH_E;

/* DMA Ӳ�����ֽӿ�*/
typedef enum tagDMA_HS_HK_INTERFACE_E
{
    DMA_UART0_RX = 0x0,
    DMA_UART0_TX = 0x1,
    DMA_SSI2_RX = 0x2,
    DMA_SSI2_TX = 0x3,
    DMA_SSI1_RX = 0x4,
    DMA_SSI1_TX = 0x5,
    DMA_SSI0_RX = 0x6,
    DMA_SSI0_TX = 0x7,
    DMA_MMC     = 0x8,
    DMA_UART1_RX = 0x9,
    DMA_UART1_TX = 0xa,
    DMA_SCI_RX = 0xb,
    DMA_SCI_TX = 0xc
}DMA_HS_HK_INTERFACE_E;


/**************************************************************************
  STRUCT����
**************************************************************************/
/*����������ṹ��*/
typedef struct tagDMA_LLI_S
{
    BSP_U32 u32Reserved[2]; /* reserved 8 bytes  PSҪ���ʽ��ʹ��ʱ��������*/
    struct  tagDMA_LLI_S *pNextLLI; /* next node */
    BSP_U32 TransLength;  /* transfer length */
    BSP_U32 SrcAddr; /*source address*/
    BSP_U32 DstAddr; /*destination address��PS���Բ���ע�������*/
} DMA_LLI_S;

/*������Ҫ�����ķ���dmaӲ��Ҫ������ݽṹ*/
typedef struct tagDMA_LLI_PHY_S
{
    BSP_U32 SrcAddr; /*source address*/
    BSP_U32 DstAddr; /*destination address*/
    BSP_U32 NextLLI; /*pointer to next LLI  the pSrcAddr of next node*/
    BSP_U32 ulTransferCtrl_l; /*control word low 32 bits */
    BSP_U32 ulTransferCtrl_h; /*control word high 32 bits */
    BSP_U32 s_stat; /*source state*/
    BSP_U32 d_stat; /*dest state*/
} DMA_LLI_PHY_S;

/*����ͨ�������ṹ*/
typedef struct tagDMA_CHN_PARA_S
{
    BSP_U32 u32Chan; /*ͨ����*/
    BSP_VOID * pfuncDmaTcIsr;/* ����жϻص�����*/
    BSP_S32 s32DmaTcPara; /* ����жϻص���������*/
    BSP_VOID * pfuncDmaErrIsr;/* �����жϻص�����*/
    BSP_S32 s32DmaErrPara; /* �����жϻص���������*/
} DMA_CHN_PARA_S;

/*sturcture for single block*/
typedef struct tagDMA_SINGLE_BLOCK_S
{
    DMA_CHN_PARA_S stChnPara;/*����ͨ�������ṹ*/
    DMA_TRANS_TYPE_E enTransType; /*������������*/
    DMA_HS_HK_INTERFACE_E enSrcHSHKInterface;/* Ӳ�����ֽӿ�*/
    DMA_HS_HK_INTERFACE_E enDstHSHKInterface;/* Ӳ�����ֽӿ�*/
    DMA_TRANS_WIDTH_E enSrcWidth; /*Դλ��*/
    DMA_TRANS_WIDTH_E enDstWidth; /*Ŀ��λ�� */
    DMA_BURST_TRANS_LENGTH_E enSrcBurstLength; /*Դburst���� */
    DMA_BURST_TRANS_LENGTH_E enDstBurstLength; /*Ŀ��burst����*/
    BSP_U32 u32SrcAddr;/* Դ��ַ*/
    BSP_U32 u32DstAddr;/* Ŀ�ĵ�ַ*/
    BSP_U32 u32TransLength;/* �����ܳ���*/
} DMA_SINGLE_BLOCK_S;

/**************************************************************************
  UNION����
**************************************************************************/

/**************************************************************************
  OTHERS����
**************************************************************************/

/**************************************************************************
  ��������
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_DMA_Init
*
* ��������  : DMA��ʼ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2009��1��20��   ����  ����

*****************************************************************************/
BSP_S32 BSP_DMA_Init(BSP_VOID);
/*****************************************************************************
* �� �� ��  : BSP_DMA_GetIdleChannel
*
* ��������  : ��ȡһ����ǰ���ڿ���״̬��DMAͨ������ǰ����������������ݺ��
*             �Զ��ͷţ��´���ʹ��ʱ���ٻ�ȡ��ǰ����ͨ��,ĿǰDMA_SPECIAL_MODE
*             ����Э��ջʹ�ã������û����벻������ͨ��
*
* �������  : DMA_CHN_TYPE_E enChnType ͨ������
*
* �������  : BSP_U32 *pulChan      ������뵽��ͨ����
* �� �� ֵ  :  DMA_SUCCESS       ��װ�ɹ�
*             BSP_ERR_DMA_MODULE_NOT_INITED      DMAδ��ʼ��
*             BSP_ERR_DMA_INVALID_PARA  ��������
*             BSP_ERR_DMA_ALL_CHANNEL_BUSY ����ͨ��æ
*
* �޸ļ�¼  :2009��10��15��   liumengcun  ����

*****************************************************************************/
BSP_S32  BSP_DMA_GetIdleChannel(DMA_CHN_TYPE_E enChnType, BSP_U32 *pulChan);

/*****************************************************************************
* �� �� ��  : BSP_DMA_ChannelRelease
*
* ��������  : DMA����ͨ���ͷ�,��������²���Ҫ���ô˽ӿ��ͷ�ͨ����������ɺ�
*             ������Զ��ͷ�ͨ�������ӿ�Ϊ�˴���ĳЩ�쳣����£�ȡ����ͨ����
*             ��ȴû�п�ʼ���ݴ��䣬�޷��Զ��ͷ�ͨ����ʱ����ô˽ӿ��ֶ��ͷ�ͨ��
*             ͨ�����ڴ���ʱ�޷��ͷ�ͨ����ͨ��0��Э��ջ�̶�ʹ���޷��ͷš�
*
* �������  : BSP_U32 ulChan  ͨ����
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS       �ͷųɹ�
*             DMA_NOT_INIT      DMAδ��ʼ��
*             DMA_PARA_INVALID  ��������
*             DMA_CHANNEL_BUSY  ͨ��æ
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
BSP_U32  BSP_DMA_ChannelRelease(BSP_U32 u32Chan);

/*****************************************************************************
* �� �� ��  : BSP_DMA_AllChannelCheck
*
* ��������  : DMAȫ��ͨ���Ƿ���м�⺯��
*
* �������  : ��
* �������  : pChannelInfo   ����ͨ��ʹ��״̬����bit�����ʾ�����ڴ������ݵ�ͨ��bitλ��1��
*               bit0��Ӧ0ͨ����bit1��Ӧ1ͨ�����Դ�����
* �� �� ֵ  : DMA_ERROR
*             DMA_SUCCESS
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
BSP_S32  BSP_DMA_AllChannelCheck(BSP_U32 *pChannelInfo);

/*TCP/IPЭ��ջ��ά�ɲⲶ�����Ϣ��ʶ*/
enum IPS_MNTN_TRACE_IP_MSG_TYPE_ENUM
{
    /* IP ���ݰ���ά�ɲ��ϱ� */
    ID_IPS_TRACE_IP_ADS_UL                  = 0xD030,
    ID_IPS_TRACE_IP_ADS_DL                  = 0xD031,
    ID_IPS_TRACE_IP_USB_UL                  = 0xD032,
    ID_IPS_TRACE_IP_USB_DL                  = 0xD033,

    ID_IPS_TRACE_IP_MSG_TYPE_BUTT
};
/********************************************************
����˵����Э��ջע��USB��SKB�ؼ���Ϣ�ϱ���SDT�ص�����
��������:
���������pFunc: SKB�ؼ���Ϣ�ϱ���SDT�ص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
extern unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc);
#define DRV_USB_REG_IPS_TRACECB(x) BSP_USB_RegIpsTraceCB(x)

/********************************************************
����˵����Э��ջע��USBʹ��֪ͨ�ص�����
��������:
���������pFunc: USBʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*USB_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc);
#define DRV_USB_REGUDI_ENABLECB(x) BSP_USB_RegUdiEnableCB(x)

/********************************************************
����˵����Э��ջע��USBȥʹ��֪ͨ�ص�����
��������:
���������pFunc: USBʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*USB_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc);
#define DRV_USB_REGUDI_DISABLECB(x) BSP_USB_RegUdiDisableCB(x)

/********************************************************
����˵����Э��ջע��HSICʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

/********************************************************
����˵����Э��ջע��HSICȥʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)
/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
extern unsigned int BSP_GetHsicEnumStatus(void);
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()

/*****************************************************************************
* �� �� ��  : BSP_DMA_OneChannelCheck
*
* ��������  : DMA����ͨ������״̬���
*
* �������  : BSP_U32 ulChan   ������ͨ����
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS    ��ͨ���������
*          DMA_TRXFER_ERROR   ��ͨ���������
*          DMA_NOT_FINISHED   ��ͨ������δ���
*          DMA_ERROR    δ֪״̬
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
BSP_S32 BSP_DMA_OneChannelCheck(BSP_U32 ulChan, BSP_U32 *pChannelStatus);

/*****************************************************************************
* �� �� ��  : BSP_DMA_SingleBlockStart
*
* ��������  : �������ݴ�������
*
* �������  : DMA_SINGLE_BLOCK_S stDMASingleBlock   ���鴫��ʹ�õĲ����ṹ��
*
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS    �����������
*          DMA_CHANNEL_INVALID   ����ͨ���Ŵ���
*          DMA_TRXFERSIZE_INVALID   ���봫�䳤�ȷǷ�
*          DMA_CHANNEL_BUSY         ͨ��æ
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
BSP_S32 BSP_DMA_SingleBlockStart(DMA_SINGLE_BLOCK_S * stDMASingleBlock);

/*****************************************************************************
* �� �� ��  : BSP_DMA_SetDstAddr
*
* ��������  : �ײ��ṩ��Э��ջ������Ŀ�ĵ�ַ������Э��ջĿ�ĵ�ַ�̶�����仯
*
* �������  : BSP_U32 u32Addr  �������Ŀ�ĵ�ַ
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS  ���óɹ�
*
* �޸ļ�¼  :2009��7��24��   ����  ����

*****************************************************************************/
BSP_U32 BSP_DMA_SetDstAddr(BSP_U32 u32Addr);

/*****************************************************************************
* �� �� ��  : BSP_DMA_LliBuild
*
* ��������  : ����������
*
* �������  : BSP_U32 ulChan        ͨ����
*             DMA_LLI_S *pFirstLLI  ��Դ����ĵ�һ���ڵ�ָ��
* �������  : ��
* �� �� ֵ  : BSP_VOID *  ָ��ײ㽨���õĴ��������ͷ�ڵ��ָ��
*
* �޸ļ�¼  :2009��7��24��   ����  ����

*****************************************************************************/
BSP_VOID * BSP_DMA_LliBuild(BSP_U32 ulChan, DMA_LLI_S *pFirstLLI);

/*****************************************************************************
* �� �� ��  : BSP_DMA_LliStart
*
* ��������  : �������ݴ�������ר�ú���
*
* �������  : BSP_U32 ulChan        ͨ����
*             BSP_VOID *pu32Head��   ����BSP_DMA_LliBuild��õĴ���������ͷָ��
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS    �����������
*          DMA_LLIHEAD_ERROR   ���������ͷ����
*          DMA_CHANNEL_INVALID   ����ͨ���Ŵ���
*          DMA_ERROR    ͨ�������л���DMAδ��ȷ��ʼ��
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
BSP_U32 BSP_DMA_LliStart(DMA_CHN_PARA_S * stChnPara, BSP_VOID *pu32Head);

/*****************************************************************************
* �� �� ��  : BSP_DMA_GetDar
*
* ��������  : ����ʹ�øú�����ȡDMA��DAR�Ĵ�����ֵ
*
* �������  : BSP_U32 u32Chan   ͨ����
*
* �������  : BSP_U32 *u32Dar  ��ͨ����Ӧ��Ŀ�ĵ�ַ�Ĵ�����ֵ
* �� �� ֵ  : DMA_SUCCESS       ��ȡ�ɹ�
*             BSP_ERR_DMA_MODULE_NOT_INITED      DMAδ��ʼ��
*             BSP_ERR_DMA_INVALID_PARA  ��������
*
* �޸ļ�¼  :2010��12��1��   ³��  ����

*****************************************************************************/
BSP_S32 BSP_DMA_GetDar(BSP_U32 u32Chan, BSP_U32 *u32Dar);

/*****************************************************************************
* �� �� ��  : BSP_DMA_DisableChannel
*
* ��������  : ����ʹ�øú���ȥʹ��DMACͨ��
*
* �������  : BSP_U32 u32Chan   ͨ����
*
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS       ��ȡ�ɹ�
*             BSP_ERR_DMA_MODULE_NOT_INITED      DMAδ��ʼ��
*             BSP_ERR_DMA_INVALID_PARA  ��������
*
* �޸ļ�¼  :2010��12��1��   ³��  ����

*****************************************************************************/
BSP_S32 BSP_DMA_DisableChannel(BSP_U32 u32Chan);

/*************************DMA END************************/

/*************************NANDF BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/
/*������*/
#define NANDF_OK              BSP_OK
#define NANDF_ERROR_INIT      BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_MODULE_NOT_INITED)  /*û�г�ʼ��*/
#define NANDF_ERROR_ARGS      BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_INVALID_PARA)  /*��������*/
#define NANDF_ERROR_MALLOC    BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_BUF_ALLOC_FAILED)  /*�ڴ�ռ����ʧ��*/
#define NANDF_ERROR_TIMEOUT   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_RETRY_TIMEOUT)  /*ѭ�������ﵽ���*/
#define NANDF_BAD_BLOCK       BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 1)  /*����*/
#define NANDF_GOOD_BLOCK      BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 2)  /*�ÿ�*/
#define NANDF_ERROR_READ      BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 3)  /*������ʧ��*/
#define NANDF_ERROR_WRITE     BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 4)  /*д����ʧ��*/
#define NANDF_ERROR_ERASE     BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 5)  /*��������ʧ��*/
#define NANDF_ERROR_MARKBAD   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 6)  /*��־����ʧ��*/
#define NANDF_ERROR_ERASE_MARKBAD   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 7)  /*����ʧ�ܲ��ұ�־����ʧ��*/
#define NANDF_ERROR_WRITE_MARKBAD   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 8)  /*д��ʧ�ܲ��ұ�־����ʧ��*/
#define NANDF_ERROR_STATUS_CHECK   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 9)  /*��ȡ״̬�Ĵ�����״̬����ȷ*/
#define NANDF_ERROR_SEMTAKE   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 10)  /*�����ź���ʧ��*/
#define NANDF_ERROR_SEMGIVE   BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 11)  /*�ͷ��ź���ʧ��*/
#define NANDF_ERROR_ADDR_OVERFLOW BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 12)  /* ��ַԽ�� */
#define NANDF_ERROR_MODULE_LOCKED  BSP_DEF_ERR(BSP_MODU_NANDF, BSP_ERR_SPECIAL + 13)

/******************************************************************************
* Function     :   BSP_NANDF_Read
*
* Description  :   ��ȡNand Flash��ָ����ַ�ͳ������ݵ�ָ���ռ���
*
* Input        :   u32FlashAddr  ��ȡ���ݵ�Դ��ַ
*              :   u32NumByte    ��ȡ���ݳ��ȣ���λΪ�ֽ�
*
* Output       :   pRamAddr      ��ȡ�����ݴ�ŵĵ�ַ
*
* return       :   �������ɹ����
******************************************************************************/
BSP_S32 BSP_NANDF_Read(BSP_VOID* pRamAddr, BSP_U32 u32FlashAddr, BSP_U32 u32NumByte);
/******************************************************************************
* Function     :   BSP_NANDF_Write
*
* Description  :   ��ָ����ַ�ͳ������ݵ�д��ָ��FLASH��ַ��
*
* Input        :   pRamAddr     д����Դ��ַ
*              :   u32NumByte   ���ݳ��ȣ���λΪ�ֽ�
*
* Output       :   u32FlashAddr д����Ŀ�ĵ�ַ
*
* return       :   д�����ɹ����
******************************************************************************/
BSP_S32 BSP_NANDF_Write(BSP_U32 u32FlashAddr, BSP_VOID *pRamAddr,  BSP_U32 u32NumByte);
/******************************************************************************
* Function     :   BSP_NANDF_Erase
*
* Description  :   ����ָ��Flash��ַ���ڿ�
*
* Input        :   u32address   Ҫ�������ID
*
* Output       :   ��
*
* return       :   ���������ɹ����
******************************************************************************/
BSP_S32 BSP_NANDF_Erase(BSP_U32 u32BlockID);
/*************************NANDF END************************/

/*************************OM BEGIN************************/
typedef struct tagBSP_OM_NET_S
{
    BSP_U32 u32NetRxStatOverFlow;       /* ����FIFO���ͳ�Ƽ��� */
    BSP_U32 u32NetRxStatPktErr;         /* �����ܴ������ */
    BSP_U32 u32NetRxStatCrcErr;         /* ����CRC������� */
    BSP_U32 u32NetRxStatLenErr;         /* ������Ч���Ȱ����� */
    BSP_U32 u32NetRxNoBufInt;           /* ����û��BUFFER�жϼ��� */
    BSP_U32 u32NetRxStopInt;            /* ����ֹͣ�жϼ��� */
    BSP_U32 u32NetRxDescErr;            /* �������������� */

    BSP_U32 u32NetTxStatUnderFlow;      /* ����FIFO����ͳ�Ƽ��� */
    BSP_U32 u32NetTxUnderFlowInt;       /* ����FIFO�����жϼ��� */
    BSP_U32 u32NetTxStopInt;            /* ����ֹͣ�жϼ��� */
    BSP_U32 u32NetTxDescErrPs;          /* ��������������(Ps) */
    BSP_U32 u32NetTxDescErrOs;          /* ��������������(Os) */
    BSP_U32 u32NetTxDescErrMsp;         /* ��������������(Msp) */

    BSP_U32 u32NetFatalBusErrInt;      /* ���ߴ���*/
}BSP_OM_NET_S;

typedef enum{
     ADDRTYPE8BIT,
     ADDRTYPE16BIT,
     ADDRTYPE32BIT
}ENADDRTYPE;

typedef enum{
     MEMCHKTYPE16BIT,
     MEMCHKTYPE32BIT
}ENMEMCHKTYPE;


typedef enum{
     BOARD_TYPE_LTE_ONLY,
     BOARD_TYPE_GUL
}BOARD_TYPE_E;

/*****************************************************************************
* �� �� ��  : BSP_OM_GetFlashSpec
*
* ��������  : ��ȡFLASH���
*
* �������  : ��
*
* �������  : BSP_U32 *pu32FlashTotalSize  : FLASH�ܴ�С
*             BSP_U32 *pu32FlashBlkSize     : FLASH���С
*             BSP_U32 *pu32FlashPageSize    : FLASHҳ��С
*
* �� �� ֵ  : BSP_ERROR:��ȡʧ��
*             BSP_OK:��ȡ�ɹ�
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_S32 BSP_OM_GetFlashSpec(BSP_U32 *pu32FlashTotalSize, BSP_U32 *pu32FlashBlkSize, BSP_U32 *pu32FlashPageSize);
/*****************************************************************************
* �� �� ��  : BSP_OM_GetVerTime
*
* ��������  : ���verʱ��
*
* �������  : ��
*
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_VOID BSP_OM_GetVerTime(BSP_S8* strVerTime);

/******************************************************************************
* Function     :   BSP_OM_RegRead
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegRead(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 *pu32Value);
/******************************************************************************
* Function     :   BSP_OM_RegWrite
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegWrite(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 u32Value);
/******************************************************************************
* Function     :   BSP_OM_MemRead
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_MemRead(BSP_U32 u32MemAddr, ENADDRTYPE enAddrType, BSP_U32 *pu32Value);
/******************************************************************************
* Function     :   BSP_OM_MemWrite
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_MemWrite(BSP_U32 u32MemAddr, ENADDRTYPE enAddrType, BSP_U32 u32Value);
/******************************************************************************
* Function     :   BSP_OM_MemNWrite
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_MemNWrite(BSP_U32 u32MemAddr, BSP_U32 u32Value, BSP_U32 u32Count);
/******************************************************************************
* Function     :   BSP_OM_MemPrint
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_MemPrint(BSP_U32 u32MemAddr,ENADDRTYPE enAddrType);
/******************************************************************************
* Function     :   BSP_OM_MemChk
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_MemChk(BSP_U32 u32StartAddr, BSP_U32 u32EndAddr, ENMEMCHKTYPE enChkType);
/******************************************************************************
* Function     :   BSP_OM_GetVersion
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_GetVersion();
/******************************************************************************
* Function     :   BSP_OM_SoftReboot
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_SoftReboot();
/******************************************************************************
* Function     :   BSP_OM_GetFPGAVer
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_GetFPGAVer();
/******************************************************************************
* Function     :   BSP_OM_NET
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_NET(BSP_OM_NET_S *pstNetOm);
/******************************************************************************
* Function     :   BSP_OM_ShellLock
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_ShellLock(BSP_BOOL bRequest);

/*****************************************************************************
* �� �� ��  : BSP_OM_GetBoardType
*
* ��������  : ��ȡ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP��������ö��
*
* ����˵��  : ��
*
*****************************************************************************/
BOARD_TYPE_E BSP_OM_GetBoardType(void);

/*************************OM END************************/

/*************************GMAC BEGIN************************/
/* ������·�հ�����ָ�� */
typedef BSP_VOID (*UpLinkRxFunc)(BSP_U8 *buf, BSP_U32 len);

/* ����װ�ͷź���ָ�� */
typedef BSP_VOID (*FreePktEncap)(BSP_VOID *PktEncap);

/* GMAC������ö�� */
typedef enum tagGMAC_OWNER_E
{
    GMAC_OWNER_VXWORKS = 0, /* Vxworks����Э��ջ */
    GMAC_OWNER_PS,          /* LTE����Э��ջ */
    GMAC_OWNER_MSP,         /* MSP */
    GMAC_OWNER_MAX          /* �߽�ֵ */
}GMAC_OWNER_E;

/******************************************************************************
* Function     :   BSP_GMAC_PowerDown
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_PowerDown(BSP_VOID);
/******************************************************************************
* Function     :   BSP_GMAC_PowerUp
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_PowerUp(BSP_VOID);
/******************************************************************************
* Function     :   BSP_GMAC_RegisterUpLinkRxCb
*
* Description  :   ע��������·���ջص�����
*
* Input        :  GMAC_OWNER_E eOwner,     ������
                  UpLinkRxFunc pfunc       ������·���ջص�����
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_RegisterUpLinkRxCb(GMAC_OWNER_E eOwner,   UpLinkRxFunc pfunc );
/******************************************************************************
* Function     :   BSP_GMAC_RegisterFreePktEncapCb
*
* Description  :    ע�����װ�ͷŻص�����
*
* Input        :  GMAC_OWNER_E eOwner,     ������
                  FreePktEncap pfunc      ����װ�ͷŻص�����
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_RegisterFreePktEncapCb( GMAC_OWNER_E eOwner, FreePktEncap pfunc );
/******************************************************************************
* Function     :   BSP_GMAC_SetPktEncapInfo
*
* Description  :    ���ð���װ�ṹ��Ϣ
*
* Input        :  GMAC_OWNER_E eOwner,    ������
                  BSP_S32 s32BufOft,      bufƫ����
                  BSP_S32 s32LenOft,      lenƫ����
                  BSP_S32 s32NextOft      nextƫ����
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_SetPktEncapInfo(GMAC_OWNER_E eOwner, BSP_S32 s32BufOft, BSP_S32 s32LenOft,BSP_S32 s32NextOft);
/******************************************************************************
* Function     :   BSP_GMAC_DownLinkTx
*
* Description  :    �������ݷ��ͺ���
*
* Input        :  GMAC_OWNER_E eOwner,    ����ģ��
                  BSP_VOID *pPktEncap     ����װ�׵�ַ
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_GMAC_DownLinkTx(GMAC_OWNER_E eOwner, BSP_VOID *pPktEncap );
/*************************GMAC END************************/

/*************************CCID BEGIN************************/
#define _DEBUG_JUNGO_CCID

typedef BSP_U32     ICC_HANDLE;
#define ICC_INVALID_HANDLE              (-1)

#define ICC_EVENT_INSERT                0x0
#define ICC_EVENT_REMOVE                0x1

#define ICC_HW_ERROR_OVERCURRENT        0x1

#define ICC_TRANS_PROTOCOL_T0           0x0
#define ICC_TRANS_PROTOCOL_T1           0x1

#define ICC_TRANS_LEVEL_CHAR_FRAME      0x0
#define ICC_TRANS_LEVEL_TPDU            0x1
#define ICC_TRANS_LEVEL_SHORT_APDU      0x2
#define ICC_TRANS_LEVEL_EXTENDED_APDU   0x4

#define ICC_VOL_CLASS_A                 0x0
#define ICC_VOL_CLASS_B                 0x1
#define ICC_VOL_CLASS_C                 0x2

#define ICC_AUTO_PARAM_CFG              0x2
#define ICC_AUTO_ACTIVATION             0x4
#define ICC_AUTO_SELECT_VOL             0x8
#define ICC_AUTO_CHANGE_FREQ            0x10
#define ICC_AUTO_CHANGE_BAUD_RATE       0x20
#define ICC_AUTO_PARAM_NEGOTIATION      0x40
#define ICC_AUTO_PARAM_PPS              0x80
#define ICC_AUTO_STOP_CLOCK             0x100

#define ICC_ACTIVE                      0x0
#define ICC_PRESENT                     0x1
#define ICC_ABSENT                      0x2

#define ICC_CLOCK_STATE_RUNNING         0x0
#define ICC_CLOCK_STATE_STOP_L          0x1
#define ICC_CLOCK_STATE_STOP_H          0x2
#define ICC_CLOCK_STATE_STOP_UNKNOW     0x3


#define ICC_HANDLE_NONE                 0x0
#define ICC_HANDLE_DATA_EXCHANGE        0x1
#define ICC_HANDLE_ABORT                0x2
#define ICC_HANDLE_ACTIVE               0x3
#define ICC_HANDLE_DEACTIVE             0x4


/*������*/
#define BSP_ERR_CCID_NOTINIT             951

typedef struct
{
    BSP_U32         u32VoltageLevel;
    BSP_U32         u32TransProtocol;
    BSP_U32         u32TransLevel;
    BSP_U32         u32Automation;
    BSP_U32         u32ClkFrq;
    BSP_U32         u32BaudRate;
    BSP_BOOL        bReactive;
}BSP_CCID_capability_t;


typedef struct
{

    /* reset icc */
    BSP_U32 (*bsp_ccid_active_cb)(BSP_U8 u8Seq);

    /* deactive icc */
    BSP_U32 (*bsp_ccid_deactive_cb)();

    /* change voltage class */
    BSP_U32 (*bsp_ccid_change_vol_cb)();

    /* get FI DI*/
    BSP_U32 (*bsp_ccid_get_fi_di_cb)(BSP_U8 *pu8FI, BSP_U8 *pu8DII);

    /* get icc state */
    BSP_U32 (*bsp_ccid_get_state_cb)(BSP_U32 *pu32IccState, BSP_U32 *pu32ClockState);

    /* send apdu */
    BSP_U32 (*bsp_ccid_send_apdu_cb)(BSP_U8 u8Seq, BSP_U32 u32DateLen, BSP_U8 *pu8Data);

    /* send tpdu */
    BSP_U32 (*bsp_ccid_send_tpdu_cb)(BSP_U8 u8Seq, BSP_U32 u32DateLen, BSP_U8 *pu8Data);

    /* send character bytes */
    BSP_U32 (*bsp_ccid_send_char_cb)(BSP_U8 u8Seq, BSP_U32 u32DateLen, BSP_U8 *pu8Data);

    /* abort command */
    BSP_U32 (*bsp_ccid_abort_cb)();

} BSP_CCID_callbacks_t;

/*****************************************************************************
* �� �� ��  : BSP_CCID_StatusChange
*
* ��������  : ICC����ģ��ʹ�ô˽ӿ�ע�ᵽCCID��CCID�����ڻص�����ȡ��ICC�ķ���Ȩ
*
* �������  : handle     �豸���
*             u32Event   ICC��״̬�仯
*                ICC_EVENT_INSERT    ������
*                ICC_EVENT_REMOVE    ���Ƴ�
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2010.04.19   z67193  create
*
*****************************************************************************/
BSP_VOID BSP_CCID_StatusChange(ICC_HANDLE handle);


/*****************************************************************************
* �� �� ��  : BSP_CCID_HardwareError
*
* ��������  : ICC����ģ��ʹ�ô˽ӿ�ע�ᵽCCID��CCID�����ڻص�����ȡ��ICC�ķ���Ȩ
*
* �������  : handle     �豸���
*             u32Error   ICC��Ӳ������
*                ICC_HW_ERROR_OVERCURRENT    ��������
*
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2010.04.19   z67193  create
*
*****************************************************************************/
BSP_VOID BSP_CCID_HardwareError(ICC_HANDLE handle, BSP_U32 u32Error);


/*****************************************************************************
* �� �� ��  : BSP_CCID_HandleFinished
*
* ��������  : ICC����ģ��ʹ�ô˽ӿ�ע�ᵽCCID��CCID�����ڻص�����ȡ��ICC�ķ���Ȩ
*
* �������  : handle     �豸���
*             u8Type     ��������
*             u8Seq      �������к�
*             u32Result  ������
*             u32Len     �������ݳ���
*             pu8Data    ��������
*
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2010.04.19   z67193  create
*
*****************************************************************************/
BSP_U32 BSP_CCID_Complete(ICC_HANDLE handle, BSP_U8 u8Type, BSP_U8 u8Seq,
                          BSP_U32 u32Result, BSP_U32 u32Len, BSP_U8 *pu8Data);


/*****************************************************************************
* �� �� ��  : BSP_CCID_HandleDelay
*
* ��������  : ICC����ģ��ʹ�ô˽ӿ�ע�ᵽCCID��CCID�����ڻص�����ȡ��ICC�ķ���Ȩ
*
* �������  : handle     �豸���
*             u8Type     ��������
*
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2010.04.19   z67193  create
*
*****************************************************************************/
BSP_U32 BSP_CCID_HandleDelay(ICC_HANDLE handle, BSP_U8 u8Type);
/*************************CCID END************************/

/*************************FTP BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/

/**************************************************************************
  �����붨��
**************************************************************************/
#define BSP_ERR_FTP_NOT_INIT            BSP_DEF_ERR(BSP_MODU_FTP, BSP_ERR_MODULE_NOT_INITED)    /*û�г�ʼ��*/
#define BSP_ERR_FTP_NULL_PTR            BSP_DEF_ERR(BSP_MODU_FTP, BSP_ERR_NULL_PTR)             /*��������*/
#define BSP_ERR_FTP_INVALID_PARAM       BSP_DEF_ERR(BSP_MODU_FTP, BSP_ERR_INVALID_PARA)         /*�ڴ�ռ����ʧ��*/
#define BSP_ERR_FTP_NO_MEM              BSP_DEF_ERR(BSP_MODU_FTP, BSP_ERR_BUF_ALLOC_FAILED)     /*ѭ�������ﵽ���*/

#define BSP_ERR_FTP_NET                 BSP_DEF_ERR(BSP_MODU_FTP, 0x10)                         /*�������*/
#define BSP_ERR_FTP_XFER                BSP_DEF_ERR(BSP_MODU_FTP, 0x11)                         /*FTP���鴫��ʧ��*/
#define BSP_ERR_FTP_DATA_TRANSFER       BSP_DEF_ERR(BSP_MODU_FTP, 0x12)                         /*���ݴ���ʧ��*/
#define BSP_ERR_FTP_CMD                 BSP_DEF_ERR(BSP_MODU_FTP, 0x13)                         /*�����ʧ��*/
#define BSP_ERR_FTP_READ                BSP_DEF_ERR(BSP_MODU_FTP, 0x14)                         /*��ʧ��*/
#define BSP_ERR_FTP_WRITE               BSP_DEF_ERR(BSP_MODU_FTP, 0x15)                         /*дʧ��*/

/**************************************************************************
  ö�ٶ���
**************************************************************************/

/*FTP transport type*/
typedef enum tagFTP_LOAD_TYPE_E
{
    FTP_LOADTYPE_VXWORKS_IMAGE = 0,
	FTP_LOADTYPE_TENCILICA_TEXT,
	FTP_LOADTYPE_TENCILICA_BOOTCODE,
    FTP_LOADTYPE_BOOTSECT,
    FTP_LOADTYPE_COMMONFILE,
    FTP_LOADTYPE_IMPORT,
    FTP_LOADTYPE_IPCFG,
    FTP_LOADTYPE_WITHSPARE,
    FTP_LOADTYPE_BUTTOM
} FTP_LOAD_TYPE_E;


/*****************************************************************************
* �� �� ��  : LOADF
*
* ��������  :
*
* �������  : BSP_U8 * pu8FileName, BSP_U32 u32DestAddr, FTP_LOAD_TYPE_E enLoadType
*
* �������  : ��
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 LOADF(BSP_U8 * pu8FileName, BSP_U32 u32DestAddr, FTP_LOAD_TYPE_E enLoadType);

/*****************************************************************************
* �� �� ��  : LOADB
*
* ��������  :
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 LOADB();

/*****************************************************************************
* �� �� ��  : BSP_LoadDsp
*
* ��������  :
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 BSP_LoadDsp();

/*****************************************************************************
* �� �� ��  : BSP_RunDsp
*
* ��������  :
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_VOID BSP_RunDsp();

/*****************************************************************************
* �� �� ��  : BSP_BootDsp
*
* ��������  :
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
BSP_S32 BSP_BootDsp();

/*************************FTP END************************/

/*************************ICC BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/
#define ICC_CHAN_NUM_MAX            (32)

#define ICC_CHAN_PRIORITY_HIGH      (0)
#define ICC_CHAN_PRIORITY_LOW       (255)
#define ICC_CHAN_PRIORITY_DEFAULT   ICC_CHAN_PRIORITY_LOW

#define ICC_CHAN_FIFO_MIN           (32)
#define ICC_CHAN_FIFO_MAX           (65536)
#define ICC_CHAN_FIFO_SIZE1         (1024)
#define ICC_CHAN_FIFO_SIZE2         (2048)
#define ICC_CHAN_FIFO_SIZE3         (4096)

/**************************************************************************
  �ṹ����
**************************************************************************/
typedef enum tagICC_CHAN_STATE_E
{
    ICC_CHAN_STATE_CLOSED   = 0,
    ICC_CHAN_STATE_OPENED,
    ICC_CHAN_STATE_CLOSEING,
    ICC_CHAN_STATE_BUTT
}ICC_CHAN_STATE_E;

typedef enum tagICC_CHAN_MODE_E{
    ICC_CHAN_MODE_STREAM    = 0,
    ICC_CHAN_MODE_PACKET,
    ICC_CHAN_MODE_BUTT
}ICC_CHAN_MODE_E;

typedef enum tagICC_IOCTL_CMD_E{
    ICC_IOCTL_SET_WRITE_CB  = 0,
    ICC_IOCTL_SET_READ_CB,
    ICC_IOCTL_SET_EVENT_CB,
    ICC_IOCTL_GET_STATE,
    ICC_IOCTL_SET_BUTT
}ICC_IOCTL_CMD_E;


typedef enum tagICC_EVENT_E{
    ICC_EVENT_CLOSE         = 0,
    ICC_EVENT_RESET,
    ICC_EVENT_BUTT
}ICC_EVENT_E;


typedef BSP_U32 (*icc_event_cb)(BSP_U32 u32ChanID, BSP_U32 u32Event, BSP_VOID* Param);
typedef BSP_U32 (*icc_write_cb)(BSP_U32 u32ChanID);
typedef BSP_U32 (*icc_read_cb)(BSP_U32 u32ChanID, BSP_S32 u32Size);

typedef struct tagICC_CHAN_ATTR_S{
    BSP_U32             u32FIFOInSize;
    BSP_U32             u32FIFOOutSize;
    BSP_U32             u32Priority;
    ICC_CHAN_MODE_E     enChanMode;
    BSP_U32             u32TimeOut;
    icc_event_cb        event_cb;
    icc_write_cb        write_cb;
    icc_read_cb         read_cb;
}ICC_CHAN_ATTR_S;

/**************************************************************************
  ��������
**************************************************************************/
BSP_S32 BSP_ICC_Open(BSP_U32 u32ChanId, ICC_CHAN_ATTR_S *pChanAttr);
BSP_S32 BSP_ICC_Close(BSP_U32 u32ChanId);
BSP_S32 BSP_ICC_Write(BSP_U32 u32ChanId, BSP_U8* pData, BSP_S32 s32Size);
BSP_S32 BSP_ICC_Read(BSP_U32 u32ChanId, BSP_U8* pData, BSP_S32 s32Size);
BSP_S32 BSP_ICC_Ioctl(BSP_U32 u32ChanId, BSP_U32 cmd, BSP_VOID *param);


/**************************************************************************
  �����붨��
**************************************************************************/
#define BSP_ERR_ICC_BASE                (BSP_S32)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_ICC, 0)))
#define BSP_ERR_ICC_NOT_INIT            (BSP_ERR_ICC_BASE + 0x1)
#define BSP_ERR_ICC_NOT_CONNECT         (BSP_ERR_ICC_BASE + 0x2)
#define BSP_ERR_ICC_NULL                (BSP_ERR_ICC_BASE + 0x3)
#define BSP_ERR_ICC_NO_MEM              (BSP_ERR_ICC_BASE + 0x4)
#define BSP_ERR_ICC_INVALID_CHAN        (BSP_ERR_ICC_BASE + 0x5)
#define BSP_ERR_ICC_INVALID_PARAM       (BSP_ERR_ICC_BASE + 0x6)
#define BSP_ERR_ICC_EXIST               (BSP_ERR_ICC_BASE + 0x7)
#define BSP_ERR_ICC_NOT_EXIST           (BSP_ERR_ICC_BASE + 0x8)
#define BSP_ERR_ICC_OPENED              (BSP_ERR_ICC_BASE + 0x9)
#define BSP_ERR_ICC_NOT_OPEN            (BSP_ERR_ICC_BASE + 0xa)
#define BSP_ERR_ICC_NO_SEM              (BSP_ERR_ICC_BASE + 0xb)
#define BSP_ERR_ICC_NEGOTIATE_FAIL      (BSP_ERR_ICC_BASE + 0xc)
#define BSP_ERR_ICC_BUFFER_FULL         (BSP_ERR_ICC_BASE + 0xd)
#define BSP_ERR_ICC_BUFFER_EMPTY        (BSP_ERR_ICC_BASE + 0xe)
#define BSP_ERR_ICC_INVALID_PACKET      (BSP_ERR_ICC_BASE + 0xf)
#define BSP_ERR_ICC_PACKET_SIZE         (BSP_ERR_ICC_BASE + 0x10)
#define BSP_ERR_ICC_USER_BUFFER_SIZE    (BSP_ERR_ICC_BASE + 0x11)
/*************************ICC END************************/

/*************************IPM START************************/
/**************************************************************************
  �궨��
**************************************************************************/

#define MAC_HEADER_LEN      14
#define IPM_SUCCESS                       BSP_OK
#define IPM_ERROR                         BSP_ERROR

/**************************************************************************
  STRUCT����
**************************************************************************/

/* �˼�����Ŀ��ṹ�� */
typedef struct tagIPM_DESC_ITEM_S
{
	BSP_U32 Addr;
	BSP_U16 Len;
	BSP_U16 Invalid;  /* 0��ʾ����BD,1��ʾ����BD */
} IPM_DESC_ITEM_S;

/* �˼��������ṹ�� */
typedef struct tagIPM_DESC_NODE_S
{
    BSP_U32 StartAddr;
    BSP_U16 ItemNum;  /* �ܵ�Item��Ŀ */
    BSP_U16 TailIdx;  /* ���һ����Ч��Item ID, ��0��ʼ */
    BSP_U16 ValidNum; /* ��Ч��Item��Ŀ */
    IPM_DESC_ITEM_S *pstDescItem;
}IPM_DESC_NODE_S;



/**************************************************************************
  UNION����
**************************************************************************/

/**************************************************************************
  OTHERS����
**************************************************************************/


/**************************************************************************
  ��������
**************************************************************************/

unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOutTimeout);
unsigned long USB_ETH_DrvSetDeviceAssembleParam(unsigned long ulEthTxMinNum,
										  unsigned long ulEthTxTimeout,
										  unsigned long ulEthRxMinNum,
										  unsigned long ulEthRxTimeout);


/******************************IP���ݹ���ģ��Ľӿ�***************************/
/*****************************************************************************
* �� �� ��  : BSP_IPM_GetDescNode
*
* ��������  : ��ȡ��Ϣ���ָ��ӿ�
*
* �������  : BSP_U32 u32ItemNum    IP��������
*
* �������  : ��
* �� �� ֵ  : �� --- ��ȡʧ��
*             �ǿ� ---  ��ȡ����Ϣ���ָ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
IPM_DESC_NODE_S *BSP_IPM_GetDescNode(BSP_U32 u32ItemNum);

/*****************************************************************************
* �� �� ��  : BSP_IPM_FreeDescNode
*
* ��������  : �ͷ���Ϣ���ָ��ӿ�
*
* �������  : IPM_DESC_NODE_S *pstDescNode
*             BSP_BOOL bNodeOnly
*             trueֻ�ͷŽ��      false �ͷŽ�����֯�ڴ�
*
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
BSP_S32 BSP_IPM_FreeDescNode(IPM_DESC_NODE_S *pstDescNode, BSP_BOOL bNodeOnly);

/*****************************************************************************
* �� �� ��  : BSP_IPM_GetBspBuf
*
* ��������  : �����ڴ�ӿ�
*
* �������  : BSP_U32 u32len    ��Ҫ�����buf����
*
* �������  : ��
* �� �� ֵ  : ��ȡ��bufָ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
BSP_U8 *BSP_IPM_GetBspBuf(BSP_U32 u32len);

/*****************************************************************************
* �� �� ��  : BSP_IPM_FreeBspBuf
*
* ��������  : �ͷ��ڴ�ӿ�
*
* �������  : BSP_U8 *pBuf ��Ҫ�ͷŵ�ָ��
*
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
BSP_VOID BSP_IPM_FreeBspBuf(BSP_U8 *pBuf);

/*************************IPM END************************/


/*************************IPF BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/



/**************************************************************************
  ö�ٶ���
**************************************************************************/


/**************************************************************************
  STRUCT����
**************************************************************************/


#if 0
/* TTF�ṹ�� */
/* below for debug structure */
enum TTF_BLK_MEM_STATE_ENUM
{
    TTF_BLK_MEM_STATE_FREE,       /*���ڴ�δ����������ͷ�*/
    TTF_BLK_MEM_STATE_ALLOC,      /*���ڴ�������*/
    TTF_BLK_MEM_STATE_BUTT
};
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned int                    ulAllocFileID;      /* File ID when alloc or free */
    unsigned int                    ulAllocLineNum;     /* File Line when alloc or free */
    unsigned int                    ulTraceFileID;      /* File ID when traced */
    unsigned int                    ulTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct
{
    unsigned int    aulGroupCnt[4];    /* �� TTF_BLK_MEM_CNT Ƭ TTF_MEM �ڴ����Ϊ 4 ��,
                                        �ֱ��¼��ǰ�������� [0, TTF_BLK_MEM_CNT/4-1],
                                        [TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT/2-1],
                                        [TTF_BLK_MEM_CNT/2, 3*TTF_BLK_MEM_CNT/4-1],
                                        [3*TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT] ��Χ�Ĵ��� */
    unsigned int    ulMaxCnt;    /* ��¼ʹ�õ� TTF_MEM ��ֵ */
} TTF_BLK_MEM_CNT_ST;

typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned long                   ulPoolId;    /*���ڴ�������һ���ڴ�� */
    unsigned long                   ulClusterId;  /*���ڴ���������һ������*/
    struct _TTF_MEM_ST              *pNext;       /* �����ݵ���һ�� */
    unsigned short                  usType;      /* �ڴ����ͣ�DYN��BLK��EXT���� */
    unsigned short                  usLen;       /* �������ݵ��ܳ��ȣ�����һ��ȫ����ʹ�� */
    unsigned short                  usUsed;      /* �Ѿ�ʹ�õ����ݳ���   */
    unsigned short                  usApp;       /* ʹ���߿���ʹ�õ����� */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;          /* ��¼���ݵ�ԭʼָ�� */
    unsigned char                  *pData;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
    void                           *pExtBuffAddr;    /* ����extern���͵��ڴ��ַ�����ͷ� */
    unsigned long                   ulForLte[6];     /*Ԥ����LTEʹ�ã�GUģ���ó�ʼ��*/
} TTF_MEM_ST;
#endif

/*����Flash��Ϣ*/
typedef struct
{
    unsigned int ulblockCount;    /*Block����*/
    unsigned int ulpageSize;    /*pageҳ��С*/
    unsigned int ulpgCntPerBlk;    /*һ��Block�е�page����*/
}DLOAD_FLASH_STRU;


/**************************************************************************
  UNION����
**************************************************************************/

/**************************************************************************
  OTHERS����
**************************************************************************/



/**************************************************************************
  ��������
**************************************************************************/



/*************************IPF END************************/



/*************************IFC BEGIN************************/
/* ������*/
/*ר�ô�����*/
#define BSP_ERR_IFC_SEND_FAIL         BSP_DEF_ERR(BSP_MODU_IFC,(BSP_ERR_SPECIAL + 1)) /*0x10120001*/
#define BSP_ERR_IFC_SEND_TIMEOUT      BSP_DEF_ERR(BSP_MODU_IFC,(BSP_ERR_SPECIAL + 2)) /*0x10120002*/
#define BSP_ERR_IFC_RCV_FAIL          BSP_DEF_ERR(BSP_MODU_IFC,(BSP_ERR_SPECIAL + 3)) /*0x10120003*/

#define IFC_ICC_CHAN_IN_FIFOSIZE  1024
#define IFC_ICC_CHAN_OUT_FIFOSIZE 1024
/*IFC������󳤶�*/
#define BSP_IFC_SEND_MAX_LEN  IFC_ICC_CHAN_IN_FIFOSIZE
/* ģ��IDö��*/
typedef enum tagIFC_MODULE_E
{
    IFC_MODULE_BSP=  0,
    IFC_MODULE_LPS=  1,
    IFC_MODULE_GUPS= 2,
    IFC_MODULE_LMSP = 3,
    IFC_MODULE_GUOM = 4,
    IFC_MODULE_BUTT
} IFC_MODULE_E;

/* IFC�ص������ṹ*/
/* pMsgBody:�ú���ID��Ӧ�����Ĳ���,ǰ���ֽ��豣֤ΪmoduleId*/
/* u32Len:pMsgBody����*/
typedef BSP_S32 (*BSP_IFC_REG_FUNC)(BSP_VOID *pMsgBody,BSP_U32 u32Len);

/*****************************************************************************
* �� �� ��  : BSP_IFC_RegFunc
*
* ��������  : ע��IFC�ص������ӿ�
*
* �������  : IFC_MODULE_E enModuleId    ģ��ID
*             BSP_IFC_REG_FUNC pFunc     �ص�����ָ��
* �������  : ��
*
* �� �� ֵ  : BSP_SUCCESS
*             BSP_ERR_MODULE_NOT_INITED
*             BSP_ERR_INVALID_PARA
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_U32 BSP_IFC_RegFunc(IFC_MODULE_E enModuleId, BSP_IFC_REG_FUNC pFunc);


/*****************************************************************************
* �� �� ��  : BSP_IFC_Send
*
* ��������  : IFC������Ϣ�ӿ�
*
* �������  : BSP_VOID * pMspBody           ������Ϣ����
*             BSP_U32 u32Len               pMspBody�ĳ���
* �������  : ��
*
* �� �� ֵ  : BSP_SUCCESS
*             BSP_ERR_MODULE_NOT_INITED
*             BSP_ERR_INVALID_PARA
*             BSP_ERR_IFC_SEND_FAIL
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_U32 BSP_IFC_Send(BSP_VOID * pMspBody, BSP_U32 u32Len);

/*************************IFC END************************/

/*************************UDI BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/
#define UDI_INVALID_HANDLE     (-1)

#define UDI_CAPA_BLOCK_READ    ((BSP_U32)(1<<0)) /* ���豸��read�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_BLOCK_WRITE   ((BSP_U32)(1<<1)) /* ���豸��write�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_READ_CB       ((BSP_U32)(1<<2)) /* ���豸֧��read �ص����� */
#define UDI_CAPA_WRITE_CB      ((BSP_U32)(1<<3)) /* ���豸֧��write �ص����� */
#define UDI_CAPA_BUFFER_LIST   ((BSP_U32)(1<<4)) /* ���豸�Ķ�дbufferΪ�ڴ�����ṹ(Ĭ��Ϊ��ͨ�ڴ��) */
#define UDI_CAPA_CTRL_OPT      ((BSP_U32)(1<<5)) /* ���豸֧�ֿ��Ʋ��� */


/**************************************************************************
  �ṹ����
**************************************************************************/
#define UDI_BUILD_DEV_ID(dev, type) (((BSP_U32)(dev) << 8) | ((BSP_U32)(type) & 0x00ff))
#define UDI_BUILD_CMD_ID(dev, cmd) (((BSP_U32)(dev) << 8) | ((BSP_U32)(cmd) & 0xffff))


typedef BSP_S32 UDI_HANDLE;

/* ���豸���� */
typedef enum tagUDI_DEVICE_MAIN_ID
{
    UDI_DEV_USB_ACM = 0,
    UDI_DEV_USB_NCM,
    UDI_DEV_ICC,
    UDI_DEV_UART,
    UDI_DEV_HSUART,

    UDI_DEV_MAX                 /* ���������, ���ڱ߽�ֵ */
}UDI_DEVICE_MAIN_ID;

/* ���豸���Ͷ���(Ҫ�� usb ���豸��̬ͳһ����) */
/* ACM */
typedef enum tagUDI_ACM_DEV_TYPE
{
    UDI_USB_ACM_CTRL,
    UDI_USB_ACM_AT,
    UDI_USB_ACM_SHELL,
    UDI_USB_ACM_LTE_DIAG,
    UDI_USB_ACM_OM,
    UDI_USB_ACM_MODEM,
    UDI_USB_ACM_HSIC_MODEM,
    UDI_USB_ACM_GPS,      /*HISO*/
    UDI_USB_ACM_3G_GPS,   /*ashell*/
    UDI_USB_ACM_3G_PCVOICE, /*Ԥ��*/
    UDI_USB_ACM_PCVOICE,    /*Ԥ��*/
    /*UDI_USB_ACM_3G_AT,    //3G AT*/
    /*UDI_USB_ACM_3G_MODEM, //3G PPP*/
    UDI_USB_HSIC_ACM0,
    UDI_USB_HSIC_ACM1,
    UDI_USB_HSIC_ACM2,
    UDI_USB_HSIC_ACM3,
    UDI_USB_HSIC_ACM4,
    UDI_USB_HSIC_ACM5,
    UDI_USB_HSIC_ACM6,
    UDI_USB_HSIC_ACM7,
    UDI_USB_HSIC_ACM8,
    UDI_USB_HSIC_ACM9,
    UDI_USB_HSIC_ACM10,
    UDI_USB_HSIC_ACM11,
    UDI_USB_HSIC_ACM12,
    UDI_USB_HSIC_ACM13,
	UDI_USB_HSIC_ACM14,
    UDI_USB_ACM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ACM_DEV_TYPE;

/* NCM */
typedef enum tagUDI_NCM_DEV_TYPE
{
    UDI_USB_NCM_NDIS,
    UDI_USB_NCM_CTRL,
    UDI_USB_HSIC_NCM0,
    UDI_USB_HSIC_NCM1,
    UDI_USB_HSIC_NCM2,

    UDI_USB_NCM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_NCM_DEV_TYPE;

/* ICC */
typedef enum tagUDI_ICC_DEV_TYPE
{
    UDI_ICC_GUOM0 = 16,
    UDI_ICC_GUOM1,
    UDI_ICC_GUOM2,
    UDI_ICC_GUOM3,
    UDI_ICC_GUOM4,

    UDI_ICC_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ICC_DEV_TYPE;

/* �豸ID�Ŷ��� */
typedef enum tagUDI_DEVICE_ID
{
    /* USB ACM */
    UDI_ACM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
    UDI_ACM_AT_ID =    UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
    UDI_ACM_SHELL_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
    UDI_ACM_LTE_DIAG_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
    UDI_ACM_OM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_OM),
    UDI_ACM_MODEM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
    UDI_ACM_HSIC_MODEM0_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_HSIC_MODEM),
    UDI_ACM_GPS_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),     /*HISO*/
    UDI_ACM_3G_GPS_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_GPS),  /*ashell*/
    UDI_ACM_3G_PCVOICE_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_PCVOICE), /*Ԥ��*/
    UDI_ACM_PCVOICE_ID    = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_PCVOICE),    /*Ԥ��*/
    /*UDI_ACM_3G_AT_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_AT),    //3G AT*/
    /*UDI_ACM_3G_MODEM_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_MODEM), //3G PPP*/
    UDI_ACM_HSIC_ACM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM0),
    UDI_ACM_HSIC_ACM1_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM1),
    UDI_ACM_HSIC_ACM2_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM2),
    UDI_ACM_HSIC_ACM3_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM3),
    UDI_ACM_HSIC_ACM4_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM4),
    UDI_ACM_HSIC_ACM5_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM5),
    UDI_ACM_HSIC_ACM6_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM6),
    UDI_ACM_HSIC_ACM7_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM7),
    UDI_ACM_HSIC_ACM8_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM8),
    UDI_ACM_HSIC_ACM9_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM9),
    UDI_ACM_HSIC_ACM10_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM10),
    UDI_ACM_HSIC_ACM11_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM11),
    UDI_ACM_HSIC_ACM12_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM12),
    UDI_ACM_HSIC_ACM13_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM13),
	UDI_ACM_HSIC_ACM14_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM14),

    /* USB NCM */
    UDI_NCM_NDIS_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS),
    UDI_NCM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL),
    UDI_NCM_HSIC_NCM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM0),
    UDI_NCM_HSIC_NCM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM1),
    UDI_NCM_HSIC_NCM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM2),

    /* UART */
    UDI_UART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 0),
    UDI_UART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 1),

    /* HSUART */
    UDI_HSUART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 0),
    UDI_HSUART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 1),

    /* ICC */
    UDI_ICC_IFC_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 0),
    UDI_ICC_IPM_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 1),
    UDI_ICC_LMSP_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 2),

    UDI_ICC_GUOM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM0),
    UDI_ICC_GUOM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM1),
    UDI_ICC_GUOM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM2),
    UDI_ICC_GUOM3_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM3),
    UDI_ICC_GUOM4_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM4),

    /* MUST BE LAST */
    UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID;


/* �豸�Ĵ򿪲��� */
typedef struct tagUDI_OPEN_PARAM
{
    UDI_DEVICE_ID devid;                        /* �豸ID */
    void   *pPrivate;                            /* ģ�����е����� */
} UDI_OPEN_PARAM;

/* IOCTL ������,��Ҫ���������ڴ���� */
typedef enum tagUDI_IOCTL_CMD_TYPE
{
    UDI_IOCTL_SET_WRITE_CB = 0xF001,            /* ����һ����ʼ��ֵ��ֹ��ϵͳ�����ͻ */
    UDI_IOCTL_SET_READ_CB,

    UDI_IOCTL_INVAL_CMD = 0xFFFFFFFF
} UDI_IOCTL_CMD_TYPE;

/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �� �� ��  : udi_get_capability
*
* ��������  : �����豸ID��ȡ��ǰ�豸֧�ֵ�����
*
* �������  : devId: �豸ID
* �������  : ��
* �� �� ֵ  : ֧�ֵ�����ֵ
*****************************************************************************/
BSP_S32 udi_get_capability(UDI_DEVICE_ID devId);

/*****************************************************************************
* �� �� ��  : udi_open
*
* ��������  : ���豸(����ͨ��)
*
* �������  : pParam: �豸�Ĵ����ò���
* �������  : ��
* �� �� ֵ  : -1:ʧ�� / ����:�ɹ�
*****************************************************************************/
UDI_HANDLE udi_open(UDI_OPEN_PARAM *pParam);

/*****************************************************************************
* �� �� ��  : udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_close(UDI_HANDLE handle);

/*****************************************************************************
* �� �� ��  : udi_write
*
* ��������  : ����д
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ����д�ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

/*****************************************************************************
* �� �� ��  : udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ���ݶ��ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

/*****************************************************************************
* �� �� ��  : udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, BSP_VOID* pParam);

/*************************UDI END************************/

/*************************MEMORY BEGIN************************/
/**************************************************************************
  �궨��
**************************************************************************/
/* �ڴ������, Flags����� */
typedef enum tagMEM_POOL_TYPE
{
    MEM_NORM_DDR_POOL = 0,
    MEM_ICC_DDR_POOL,
    MEM_ICC_AXI_POOL,
    MEM_POOL_MAX
}MEM_POOL_TYPE;

/**************************************************************************
  �ӿ�����
**************************************************************************/
BSP_VOID* BSP_Malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
BSP_VOID* BSP_MallocDbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line);
BSP_VOID  BSP_Free(BSP_VOID* pMem);
BSP_VOID  BSP_FreeDbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line);

/*****************************************************************************
* �� �� ��  : BSP_MALLOC
*
* ��������  : BSP ��̬�ڴ����
*
* �������  : sz: ����Ĵ�С(byte)
*             flags: �ڴ�����(�ݲ�ʹ��,Ԥ��)
* �������  : ��
* �� �� ֵ  : ����������ڴ�ָ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_MALLOC(sz, flags) BSP_MallocDbg(sz, flags, __FILE__, __LINE__)
#else
#define BSP_MALLOC(sz, flags) BSP_Malloc(sz, flags)
#endif

/*****************************************************************************
* �� �� ��  : BSP_FREE
*
* ��������  : BSP ��̬�ڴ��ͷ�
*
* �������  : ptr: ��̬�ڴ�ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_FREE(ptr) BSP_FreeDbg(ptr, __FILE__, __LINE__)
#else
#define BSP_FREE(ptr) BSP_Free(ptr)
#endif


/*************************MEMORY END************************/


/*****************************************************************************
  1 GU����������ӿڣ�GUPorting��Ŀ���.
*****************************************************************************/

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DRV_OK                          (0)
#define DRV_ERROR                       (-1)
#define DRV_INTERFACE_RSLT_OK           (0)

/***************************************************AUDIOģ��*********************************************************/
/*AUDIO IOCTL�ӿ�������*/
#define AUDIO_IOCTL_BASE                   0x30000000
#define IOCTL_AUDIO_SAMPLE_RATE_SET                (AUDIO_IOCTL_BASE+1)
#define IOCTL_AUDIO_PCM_MODE_SET                   (AUDIO_IOCTL_BASE+7)
#define IOCTL_AUDIO_IN_DEV_SELECT                  (AUDIO_IOCTL_BASE+11)
#define IOCTL_AUDIO_OUT_DEV_SELECT                 (AUDIO_IOCTL_BASE+12)
#define IOCTL_AUDIO_OUT_DEV_UNSELECT               (AUDIO_IOCTL_BASE+13)
#define IOCTL_AUDIO_IN_DEV_UNSELECT               (AUDIO_IOCTL_BASE+14)
#define IOCTL_AUDIO_VOICE_OPEN                     (AUDIO_IOCTL_BASE+23)
#define IOCTL_AUDIO_VOICE_CLOSE                    (AUDIO_IOCTL_BASE+24)

/***************************************************MNTNģ��*********************************************************/
/*VERSIONINFO_I���ݽṹ�а汾�ַ��������Ч�ַ�����*/
#define VER_MAX_LENGTH                  30

/*memVersionCtrl�ӿڲ�������*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

#define OM_SAVE_EXCHFILE_ING            0
#define OM_SAVE_EXCHFILE_END            1

/***************************************************USBģ��*********************************************************/
/* �豸ö�����˿ڸ��� */
#define DYNAMIC_PID_MAX_PORT_NUM        17

/* ��ACM �����ظ�*/
#if 0
/* UDI IOCTL ����ID */
#define UDI_ACM_IOCTL_SET_READ_CB           0x7F001001
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    0x7F001011
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       0x7F001012
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/***************************************************AUDIOģ��*********************************************************/
typedef enum
{
    NODEV=0x00,
    HEADSET=0x01,
    HANDSET=0x02,
    HANDFREE=0x04
}AUDIO_DEV_TYPE_I;

typedef enum
{
    SAMPLE_RATE_8K=0,
    SAMPLE_RATE_11K025=1,
    SAMPLE_RATE_12K=2,
    SAMPLE_RATE_16K=3,
    SAMPLE_RATE_22K05=4,
    SAMPLE_RATE_24K=5,
    SAMPLE_RATE_32K=6,
    SAMPLE_RATE_44K1=7,
    SAMPLE_RATE_48K=8,
    SAMPLE_RATE_INVALID=0xFFFF
}AUDIO_SAMPLE_RATE_I;

/***************************************************DLOADģ��*********************************************************/
enum UPDATE_STATUS_I
{
    DL_UPDATE = 0,
    DL_NOT_UPDATE = 1
};

/***************************************************GPIOģ��*********************************************************/
enum GPIO_OPRT_ENUM
{
    GPIO_OPRT_SET = 0,
    GPIO_OPRT_GET,
    GPIO_OPRT_BUTT
};
typedef unsigned int GPIO_OPRT_ENUM_UINT32;

/***************************************************MNTNģ��*********************************************************/
/*�������*/
typedef enum
{
    VER_BOOTLOAD = 0,
    VER_BOOTROM =1,
    VER_NV =2 ,
    VER_VXWORKS =3,
    VER_DSP =4 ,
    VER_PRODUCT_ID =5 ,
    VER_WBBP =6 ,
    VER_PS =7,
    VER_OAM =8,
    VER_GBBP =9 ,
    VER_SOC =10,
    VER_HARDWARE =11,
    VER_SOFTWARE =12,
    VER_MEDIA =13,
    VER_APP =14,
    VER_ASIC =15,
    VER_RF =16,
    VER_PMU =17,
    VER_PDM = 18,
    VER_PRODUCT_INNER_ID =19,
    VER_INFO_NUM =20,
}COMP_TYPE_I;

/* ��ɫ��״̬���*/
enum
{
    LED_LIGHT_SYSTEM_STARTUP,
    LED_LIGHT_POWER_ON,
    LED_LIGHT_G_REGISTERED,
    LED_LIGHT_W_REGISTERED,
    LED_LIGHT_G_CONNECTED,
    LED_LIGHT_W_CONNNECTED,
    LED_LIGHT_H_CONNNECTED,
    LED_LIGHT_OFFLINE,
    LED_LIGHT_FORCE_UPDATING,
    LED_LIGHT_NORMAL_UPDATING,
    LED_LIGHT_UPDATE_FAIL,
    LED_LIGHT_UPDATE_SUCCESS,
    LED_LIGHT_UPDATE_FILEFAIL,
    LED_LIGHT_UPDATE_NVFAIL,
    LED_LIGHT_SIM_ABSENT,
    LED_LIGHT_SHUTDOWN,
    LED_LIGHT_G_PLMN_SEARCH,
    LED_LIGHT_W_PLMN_SEARCH,
	LED_LIGHT_L_REGISTERED,
    LED_LIGHT_STATE_MAX = 32,
};/*the state of LED */

enum SECURE_SUPPORT_STATUS_I
{
    SECURE_NOT_SUPPORT = 0,
    SECURE_SUPPORT = 1
};

enum SECURE_ENABLE_STATUS_I
{
    SECURE_DISABLE = 0,
    SECURE_ENABLE = 1
};

typedef enum                /* CACHE_TYPE */
{
    PS_OSAL_INSTRUCTION_CACHE ,
    PS_OSAL_DATA_CACHE
} PS_OSAL_CACHE_TYPE_I;

/***************************************************USBģ��*********************************************************/
typedef  enum
{
    FLOW_CON,     /* ����        */
    PDP_STATUS,   /* PDP������ */
    SIGNAL_LEVEL, /* �ź�ǿ��    */
    PKT_STATICS,  /* ����ͳ��    */
    AT_CMD,       /* AT����      */
    PS_NOTIFY,    /* Notify����  */
    RESERVE       /* ����        */
}NDIS_NOTICE;


typedef enum
{
    WWAN_WCDMA    = 1,/*WCDMAģʽ*/
    WWAN_CDMA	 = 2  /*CDMAģʽ*/
}NDIS_WWAN_MODE;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* �����������Ͷ��� */
typedef void (*PVOIDFUNC)();

typedef int  (*pFUNCPTR)();

typedef unsigned long (*pFUNCPTR2)( unsigned long ulPara1, unsigned long ulPara2);

typedef unsigned int tagUDI_DEVICE_ID_UINT32;

/***************************************************DPMģ��*********************************************************/
typedef unsigned long (*pULULFUNCPTR)( unsigned long ulPara );

/***************************************************MNTNģ��*********************************************************/
typedef int  (*OM_SAVE_FUNC)(int funcType, unsigned char *data, unsigned int* ulLength);

typedef struct
{
    unsigned char CompId;              /* ����ţ��μ�COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* ���汾���� 30 �ַ�+ \0 */
}VERSIONINFO_I;

typedef struct
{
    pULULFUNCPTR pRestoreFunction;
    pULULFUNCPTR pEnableFunction;
    pULULFUNCPTR pDisableFunction;
    pFUNCPTR2    pDfsSetFunc;
    pULULFUNCPTR pDfsReleaseFunc;
}DPM_SLEEP_CALLBACK_STRU;

typedef struct
{
    unsigned char enHSDSCHSupport;          /*Ӳ���Ƿ�֧��HSDPA*/
    unsigned char ucHSDSCHPhyCategory;      /*Ӳ��֧�ֵ����HSDPA�����ȼ�*/
    unsigned char enEDCHSupport;            /*Ӳ���Ƿ�֧��HSUPA*/
    unsigned char ucEDCHPhyCategory;        /*Ӳ��֧�ֵ����HSUPA�����ȼ�*/
    unsigned int  reserved;                 /*Ԥ��*/
}SUPPORT_MAX_HSPA_CAPA_STRU;

typedef unsigned long (*pPCSCFUNC)(unsigned long CmdType, unsigned char *pApdu, unsigned long ApduLen);

/* NV��50091�ṹ�������豸��Ҫö�ٵĶ˿���̬ */
typedef struct
{
    unsigned long ulStatus;
    unsigned char aucFirstPortStyle[DYNAMIC_PID_MAX_PORT_NUM];  /* �豸�л�ǰ�˿���̬ */
    unsigned char aucRewindPortStyle[DYNAMIC_PID_MAX_PORT_NUM]; /* �豸�л���˿���̬ */
    unsigned char reserved[22];
}DRV_DYNAMIC_PID_TYPE_STRU;

/***************************************************SCIģ��*********************************************************/
typedef void (*USIMMSCIInfo)(void);


/***************************************************USBģ��*********************************************************/
/*�ܽ��źŵĶ���*/
#define IO_CTRL_FC                      (0x02)
#define IO_CTRL_DSR                     (0x20)
#define IO_CTRL_DTR                     (0x01)
#define IO_CTRL_RFR                     (0x04)
#define IO_CTRL_CTS                     (0x10)
#define IO_CTRL_RI                      (0x40)
#define IO_CTRL_DCD                     (0x80)

typedef int  (*pComRecv)(unsigned char  uPortNo, unsigned char* pData, unsigned short uslength);

typedef int  (*pUartRecv)(unsigned char uPortNo, unsigned char* pData, unsigned short uslength);

typedef long (*pUsbStatus)(unsigned char ucStatus);

typedef long  (*pUsbState)(unsigned char ucStatus);

typedef int  (*pComStatusNotify)(unsigned char uStatus);

/* ��ACM �����ظ�*/
#if 0
/* MODEM �ܽ��źŽṹ�嶨��*/
typedef struct _AT_DCE_MSC_STRU
{
    unsigned long    OP_Dtr     : 1;    /*DTR CHANGE FLAG*/
    unsigned long    OP_Dsr     :  1;  /*DSR CHANGE FLAG*/
    unsigned long    OP_Cts     :  1;  /*CTSCHANGE FLAG*/
    unsigned long    OP_Rts     : 1;   /*RTS CHANGE FLAG*/
    unsigned long    OP_Ri      :  1;   /*RI CHANGE FLAG*/
    unsigned long    OP_Dcd     :  1;  /*DCD CHANGE FLAG*/
    unsigned long    OP_Fc      :  1;  /*FC CHANGE FLAG*/
    unsigned long    OP_Brk     :  1;  /*BRK CHANGE FLAG*/
    unsigned long    OP_Spare   :  24; /*reserve*/
    unsigned char     ucDtr;                 /*DTR  VALUE*/
    unsigned char     ucDsr;                 /*DSR  VALUE*/
    unsigned char     ucCts;                 /*DTS VALUE*/
    unsigned char     ucRts;                  /*RTS  VALUE*/
    unsigned char     ucRi;                   /*RI VALUE*/
    unsigned char     ucDcd;                 /*DCD  VALUE*/
    unsigned char     ucFc;                   /*FC  VALUE*/
    unsigned char     ucBrk;                 /*BRK  VALUE*/
    unsigned char     ucBrkLen;         /*BRKLEN VALUE*/
}MODEM_MSC_STRU,*pMODEM_MSC_STRU,AT_DCE_MSC_STRU;
#endif

/*Э��ջBULK���ݽ��ջص��������Ͷ���*/
typedef int (*USB_MODEM_RECV_CALL)
(
    unsigned char ucPortType,          /*�˿ں�*/
    unsigned char ucDlci,                 /*��·��*/
    unsigned char *pData,               /*����ָ��*/
    unsigned short usLen                /*���ݳ���*/
);


/*Э��ջ��Ϣͨ��״̬�仯���ݽ��ջص���������*/
typedef int (*USB_MODEM_AT_Sig)
(
    unsigned char ucPortType,          /*�˿ں�*/
    unsigned char ucDlci,                   /*��·��*/
    MODEM_MSC_STRU* data  /*ָ��MODEM �ܽ��źŽṹ���ָ��*/
);


/*Э��ջ�����������ص�����*/
typedef int (*USB_MODEM_IN_OUT)
(
    unsigned char ucPortType,           /*�˿ں�*/
    unsigned char ucDlci                   /*��·��*/
);

/*Э��ջ�����ܸ��ƺ�������*/
typedef void (*USB_MODEM_COPY)
(
    unsigned char   *pDest,
    unsigned char   *pSrc,
    unsigned long   ulLen
);


typedef struct
{
    unsigned int    GateWayIpAddr;  /* PDP�����ȡ����Զ������IP��ַ      */
    unsigned int    LocalIpAddr;    /* PDP�����ȡ���ķ��䵽MODEM��IP��ַ */
    unsigned int    MaskAddr;       /* �������� */
    unsigned int    speed;          /* �����ٶȣ���λbps */
    unsigned char   ActiveSatus;    /* ��������0Ϊ�ɹ�������Ϊʧ�� */
}NDIS_PDP_STRU,*pNDIS_PDP_STRU;


typedef struct
{
    unsigned int    currentTx;    /* CURRENT_TX */
    unsigned int    currentRx;    /* CURRENT_RX */
    unsigned int    maxTx;        /* MAX_TX */
    unsigned int    maxRx;        /* MAX_RX */
}NDIS_RATE_STRU,*pNDIS_RATE_STRU;


typedef struct
{
    unsigned int     TxOKCount;         /*���Ͱ���*/
    unsigned int     RxOKCount;         /*���հ���*/
    unsigned int     TxErrCount;        /*���ʹ���*/
    unsigned int     RxErrCount;        /*���մ���*/
    unsigned int     TxOverFlowCount;   /*�����������*/
    unsigned int     RxOverFlowCount;   /*�����������*/
    unsigned int     MaxTx;         /*��������*/
    unsigned int     MaxRx;         /*��������*/
} NDIS_PKT_STATISTICS, *pNDIS_PKT_STATISTICS;

typedef struct
{
    unsigned char   *pucAtCmd;          /*ָ��AT�����ָ��*/
    unsigned short   usLen;             /*AT����ĳ���*/
}NDIS_AT_CMD_STRU, *pNDIS_AT_CMD_STRU;

/* �ź��ϱ�����ʹ�õĽṹ��*/
typedef struct
{
    NDIS_NOTICE                 type;
    union
    {
        NDIS_PDP_STRU           pdp;
        NDIS_PKT_STATISTICS     pktStatics;
        unsigned char           flowFlag;   /*  1:���أ�0�������� */
        int                     dbm;
        NDIS_AT_CMD_STRU        atCmd;
    }NDIS_STATUS_DATA;

} NDIS_PRO_STRU, *pNDIS_PRO_STRU;

typedef int (*USB_NDIS_RECV_CALL)
(
    unsigned char *pData, /* ���ջ�����ָ��,����ΪIP���� */
    unsigned short usLen  /* ���ݳ��� */
);

typedef int (*USB_NDIS_BRK)
(
    void
);

typedef int (*USB_NDIS_EST)
(
    unsigned char *pData /* ���ջ�����ָ�룬����Ϊ�������ù������ */
);

typedef int (*USB_NDIS_PKT_STATISTICS_PERIOD)
(
    unsigned int period /*��λS */
);

typedef int (*USB_NDIS_GET_RATE)
(
    NDIS_RATE_STRU  *pRate
);

typedef int (*USB_NDIS_AT_CMD_RECV)
(
    unsigned char *pBuff,   /*ָ��AT����ָ��*/
    unsigned short usLen    /*AT�����*/
);

typedef unsigned int (*USB_NDIS_GET_WWAN_MODE)	/*��ȡ��ǰ����ģʽcdma/wcdma*/
(
    void
);

typedef unsigned long (*USB_NET_DEV_SET_MAX_TX_PACKET_NUMBER)
(
    unsigned long ulNumber
);

typedef void (*IPC_RECV_HANDLER)(unsigned char ucCidNo, unsigned char *pstData, unsigned int ulLength );

typedef int (*IPC_COM_RECV_HANDLER)(unsigned char uPortNo, unsigned char* pData, unsigned short uslength);



/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������(��ģ�����)
*****************************************************************************/

/**************************************************ABBģ��*********************************************************************/
/*****************************************************************************
 �� �� ��  : BSP_ABB_RegGet
 ��������  : ��ȡABB�Ĵ���ֵ
 �������  : usInstruction: �����Ĵ�����ַ
             uspData: ��żĴ���ֵ
 �������  :
 �� �� ֵ  :
*****************************************************************************/
extern int BSP_ABB_RegGet(unsigned char usInstruction, unsigned char *uspData);
#define DRV_ABB_REG_VALUE_GET(usInstruction,uspData)    BSP_ABB_RegGet (usInstruction,uspData)


/***************************************************AUDIOģ��*********************************************************/
/********************************************************************************************************
 �� �� ��  : BSP_AUDIO_CodecOpen
 ��������  : ��һ��audio�豸������codec���г�ʼ����
 �������  : devname���ò����̶�Ϊ"/dev/codec0"��
                           flags���ò�����ʾ��д��ʽ���̶�Ϊ0��
                           mode���ò�����ʾ�½��ļ���ʽ���̶�Ϊ0����
  �������  : �ޡ�
 �� �� ֵ  : �Ǹ�ֵ:  �豸�����
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_AUDIO_CodecOpen(const char *devname, int flags, int mode);
#define DRV_CODEC_OPEN(devname, flags, mode)    BSP_AUDIO_CodecOpen(devname, flags, mode)

/********************************************************************************************************
 �� �� ��  : BSP_AUDIO_Codec_ioctl
 ��������  : codec�豸�����ֿ��ơ�
 �������  : devid���豸�����
                           cmd�������֡�
                           arg�����������
  �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_AUDIO_Codec_ioctl(int devid, int cmd, int arg);
#define DRV_CODEC_IOCTL(devid, cmd, arg)   BSP_AUDIO_Codec_ioctl(devid, cmd, arg)


/***************************************************DLOADģ��*********************************************************/
/*****************************************************************************
 �� �� ��  : BSP_DLOAD_SetSoftLoad
 ��������  : �����������ر�־��
 �������  : flag���������ر�־��
                   0�����������bootrom�������������ء�
                   1�������󲻽���bootrom������������
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int BSP_DLOAD_SetSoftLoad(int flag);*/
#define DRV_SET_UPDATA_FLAG(flag)   BSP_DLOAD_SetSoftLoad(flag)

/*****************************************************************************
 �� �� ��  : BSP_DLOAD_SetCdromMarker
 ��������  : ����ISO�ļ����ر�־��
 �������  : flag��ISO�ļ����ر�־��
                   0�������󲻼���ISO�ļ���
                   1�����������ISO�ļ�������������
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int BSP_DLOAD_SetCdromMarker(int flag);*/
#define DRV_SET_CDROM_FLAG(flag)    BSP_DLOAD_SetCdromMarker(flag)

/*****************************************************************************
 �� �� ��  : BSP_DLOAD_GetCdromMarker
 ��������  : ���ISO�ļ����ر�־��
 �������  : ��
 �������  : �ޡ�
 �� �� ֵ  :
             0�������󲻼���ISO�ļ���
             1�����������ISO�ļ�������������
*****************************************************************************/
/*extern int BSP_DLOAD_GetCdromMarker(void);*/
#define DRV_GET_CDROM_FLAG()    BSP_DLOAD_GetCdromMarker()

/*****************************************************************************
 �� �� ��  : getCdromVersion
 ��������  : ���ISO�ļ��汾��Ϣ
 �������  : pVersionInfo: ��ŷ��صİ汾��Ϣ���ڴ��ַ
                           ulLength: ��ŷ��صİ汾��Ϣ���ڴ泤�ȣ�Ŀǰ�̶�
                           128
 �������  : pVersionInfo: ���صİ汾��Ϣ���ڴ��ַ
 �� �� ֵ  :  0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int BSP_DLOAD_GetISOVer(char *pVersionInfo, unsigned long ulLength);*/
#define DRV_GET_CDROM_VERSION(pVersionInfo,ulLength)    BSP_DLOAD_GetISOVer(pVersionInfo, ulLength)

/********************************************************************************************************
 �� �� ��  : BSP_DLOAD_NVBackupRead
 ��������  : ��Flash�е�NV�������ȡ���ݣ�ʵ��NV��Ļָ����ܡ�
 �������  : len����NV�������ʼ����ʼ����Ҫ��ȡ��NV��ȣ��ֽ�������������1Block��
 �������  : pRamAddr��Ŀ��RAM��ַ�����ڴ�Ŷ�����NV�����ݡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_DLOAD_NVBackupRead(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_READ(pRamAddr,len)    BSP_DLOAD_NVBackupRead(pRamAddr, len)

/********************************************************************************************************
 �� �� ��  : BSP_DLOAD_NVBackupWrite
 ��������  : ���ض�����д��Flash�е�NV�������ʵ��NV��ı��ݹ��ܡ�
 �������  : pRamAddr��ԴRAM��ַ�����ڴ����Ҫд���NV�����ݡ�
             len����NV�������ʼ����ʼ����Ҫд���NV��ȣ��ֽ�������������1Block��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_DLOAD_NVBackupWrite(unsigned char *pRamAddr, unsigned int len);
#define DRV_NVBACKUP_WRITE(pRamAddr, len)   BSP_DLOAD_NVBackupWrite(pRamAddr, len)

/*****************************************************************************
 �� �� ��  : BSP_DLOAD_GetTFUpdateFlag
 ��������  : �ж��Ƿ���TF������
 �������  : None
 �������  : None
 �� �� ֵ  : ����1��TF������NV�ָ��ɹ�����Ҫ������
             ����0����TF������NV�ָ��ɹ�������Ҫ������

*****************************************************************************/
extern int BSP_DLOAD_GetTFUpdateFlag(void);
#define DRV_GET_TFUPDATE_FLAG()    BSP_DLOAD_GetTFUpdateFlag()


/****************************************** FSģ��*******************************************/
/********************************************************************************************************
 �� �� ��  : BSP_FS_GetDskspc
 ��������  : �õ��ļ�ϵͳ�ռ䡣
 �������  : path���ļ�ϵͳ·����
 �������  : DskSpc���ܿռ䡣
                           UsdSpc���ù��ռ䡣
                           VldSpc�����пռ䡣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_FS_GetDskspc(const char *path,unsigned int *DskSpc,unsigned int  *UsdSpc,  unsigned int *VldSpc);
#define DRV_FILE_GET_DISKSPACE(path,DskSpc,UsdSpc,VldSpc)    BSP_FS_GetDskspc(path,DskSpc,UsdSpc,VldSpc)


/****************************************** GPIOģ��*******************************************/
/*****************************************************************************
 �� �� ��  : BSP_GPIO_Oprt
 ��������  : at^GPIOPL,���úͲ�ѯGPIO�ĵ�ƽ
 �������  : �������� ulOp:
             0  ���ø�GPIO��PLֵ
             1  ��ѯ��ǰ��GPIO��PLֵ

             pucPL ��Ӧ20Byte������,ÿ��BYTE����һ��8���ܽŵ�ֵ

             ���ò���ʱ,pucPLΪ���õ�20��Byte
             ��ѯ����ʱ,pucPLΪ��ǰ��ȡ����PL��ʵ��ֵ��ɵ�16��������
             �����û�����at^GPIOPL = ABCDEF,���ӦpucPL������ֵΪ{A,B,C,D,E,F,0,0,...}

 �������  : ��
 �� �� ֵ  :  0 ��OK  �� 0 ��Error

*****************************************************************************/
extern unsigned long BSP_GPIO_Oprt(unsigned long ulOp, unsigned char *pucPL);
#define DRV_GPIO_OPRT(ulOp,pucPL)    BSP_GPIO_Oprt(ulOp,pucPL)


/******************************************MNTNģ��*******************************************/
/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetFlashSpec
 ��������  : Get flash infomation
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_MNTN_GetFlashSpec(unsigned char * pFlashInfo, unsigned int ulLength);
#define DRV_GET_FLASH_INFO(pFlashInfo, usLength)    BSP_MNTN_GetFlashSpec (pFlashInfo, usLength )

/*****************************************************************************
 �� �� ��  : BSP_GU_GetVerTime
 ��������  : ��ȡ�汾����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
extern char *BSP_GU_GetVerTime(void);
#define DRV_GET_VERSION_TIME()    BSP_GU_GetVerTime()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_MemVersionCtrl
 ��������  : ����汾��д�ӿڡ�
 �������  : pcData����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��ַ��
                     ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ�ĵ�ַ��
             ucLength����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��С��
                       ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ���ַ�����������'\0'����
             ucType���汾��ϢID��
                     0�� BOOTLOAD��
                     1�� BOOTROM��
                     2�� NV��
                     3�� VXWORKS��
                     4�� DSP��
                     5�� CDROMISO��
                     6�� PHY��
                     7�� PS��
                     8�� COM��
                     9�� RF��
                     10��SOC��
                     11��HARDWARE��
                     12��SOFTWARE��
                     13��MEDIA��
                     14��APP��
                     15��INFO_NUM��
             ucMode��0����ȡָ��ID������汾��Ϣ��1��д��ָ��ID������汾��Ϣ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_MemVersionCtrl(signed char *pcData, unsigned char ucLength, unsigned char ucType, unsigned char ucMode);
#define DRV_MEM_VERCTRL(pcData,ucLength,ucType,ucMode)  \
                          BSP_MNTN_MemVersionCtrl(pcData,ucLength,ucType,ucMode)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetFullHwVersion
 ��������  : Ӳ�������汾���ӿڡ�
 �������  : pFullHwVersion��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��׵�ַ��
             ulLength      ��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetFullHwVersion(char * pFullHwVersion,unsigned int ulLength);
#define  DRV_GET_FULL_HW_VER(pFullHwVersion,ulLength)  \
               BSP_MNTN_GetFullHwVersion(pFullHwVersion,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetProductIdInter
 ��������  : ��Ʒ���������汾���ӿڡ�
 �������  : pProductIdInter��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��׵�ַ��
             ulLength       ��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetProductIdInter(char * pProductIdInter, unsigned int ulLength);
#define  DRV_GET_PRODUCTID_INTER_VER(pProductIdInter,ulLength)  \
              BSP_MNTN_GetProductIdInter(pProductIdInter,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_VersionQueryApi
 ��������  : ��ѯ��������İ汾�š�
 �������  : ppVersionInfo��������İ汾��Ϣ��ַ��
 �������  : ucLength�������ص����ݵ��ֽ�����
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_VersionQueryApi(void ** ppVersionInfo, unsigned int * ulLength);
#define  DRV_VER_QUERY(ppVersionInfo,ulLength)  \
              BSP_MNTN_VersionQueryApi (ppVersionInfo,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetGsmPATemperature
 ��������  : ��ȡGSM PA�¶�
 �������  : Temprature
             hkAdcTalble
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetGsmPATemperature(int *temperature, unsigned short *hkAdcTable);
#define DRV_GET_PA_GTEMP(temperature, hkAdcTable)   \
                BSP_MNTN_GetGsmPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 �� �� ��  : getWcdmaPATemperature
 ��������  : ��ȡWCDMA PA�¶�
 �������  : Temprature
             hkAdcTalble
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetWcdmaPATemperature (int *temperature, unsigned short *hkAdcTable);
#define  DRV_GET_PA_WTEMP(temperature, hkAdcTable)  \
              BSP_MNTN_GetWcdmaPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSIMTemperature
 ��������  : ��ȡSIM���¶�
 �������  : pusHkAdcTable����ŵ�ѹ��
 �������  : pTemp��        ָ��SIM���¶ȵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetSIMTemperature(int *plTemp, unsigned short *pusHkAdcTable);
#define DRV_GET_SIM_TEMP(plTemp, pusHkAdcTable)   \
               BSP_MNTN_GetSIMTemperature(plTemp, pusHkAdcTable)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ABBSelfCheck
 ��������  : ����abb�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_ABBSelfCheck(void);
#define DRV_ABB_SELFCHECK()    BSP_MNTN_ABBSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_PmuSelfCheck
 ��������  : PMU�Լ졣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_PmuSelfCheck(void);
#define DRV_PMU_SELFCHECK()    BSP_MNTN_PmuSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_I2cSelfCheck
 ��������  : ����I2c�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern int BSP_MNTN_I2cSelfCheck(void);
#define DRV_I2C_SELFCHECK()    BSP_MNTN_I2cSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_SpiSelfCheck
 ��������  : ����spi�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern int BSP_MNTN_SpiSelfCheck(void);
#define DRV_SPI_SELFCHECK()    BSP_MNTN_SpiSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetCodecFuncStatus
 ��������  : ��ȡCODEC����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1:  CODEC����
             0��CODEC ������
*****************************************************************************/
extern  int BSP_MNTN_GetCodecFuncStatus(void);
#define DRV_GET_CODEC_FUNC_STATUS()    BSP_MNTN_GetCodecFuncStatus()

/*****************************************************************************
 �� �� ��  : MNTN_RFGLockStateGet
 ��������  : ��ȡGSM RF����״̬��
 �������  : �ޡ�
 �������  : Status���������״̬�����ֵ��
                        0��TX����RX��������
                        1��TX��RX��û�б�������

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_RFGLockStateGet(unsigned int *Status);
#define DRV_GET_RF_GLOCKSTATE(Status)    BSP_MNTN_RFGLockStateGet(Status)

/****************************************************************************
 �� �� ��  : BSP_MNTN_LedStateFuncReg
 ��������  : ���ӿ�Ϊ�ṩ��Э��ջ�Ĺ��Ӻ��������ڻ�ȡЭ��ջ�ĵ��״̬��
 �������  : Э��ջ��ȡ���״̬������ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע������  : �ޡ�

******************************************************************************/
extern void BSP_MNTN_LedStateFuncReg (pFUNCPTR p);
#define DRV_LED_STATE_FUNREG(p)    BSP_MNTN_LedStateFuncReg(p)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_LedFlush
 ��������  : ��ɫ�����á�
 �������  : status����ɫ�Ƶ�״̬����LED_STATUS_I
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_LedFlush(unsigned long state);
#define DRV_LED_FLUSH(state)    BSP_MNTN_LedFlush(state)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_LedControlAddressGet
 ��������  : �õ����Ƶĵ������
 �������  : ��
 �������  : �ޡ�
 �� �� ֵ  : ��ƿ������ݵ�ȫ�ֱ�����ַ
*****************************************************************************/
extern unsigned int BSP_MNTN_LedControlAddressGet(void);
#define DRV_LED_GET_ADDRESS()   BSP_MNTN_LedControlAddressGet()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_BootForceloadModeCheck
 ��������  : ǿ�Ƽ���ģʽ��ѯ��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��ǿ�Ƽ��أ�
             1����ǿ�Ƽ��ء�
*****************************************************************************/
extern unsigned int BSP_MNTN_BootForceloadModeCheck(void);
#define DRV_BOOT_FORCELOAD_MODE_CHECK()    BSP_MNTN_BootForceloadModeCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_BootFlagConfig
 ��������  : ����Bootline�����е�������־Ϊ����������������ʱ7�����������ֶ�������
 �������  : ulBootFlag����δ���塣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern  int BSP_MNTN_BootFlagConfig(unsigned int ulBootFlag);
#define DRV_BOOTFLAG_CFG(ulBootFlag)    BSP_MNTN_BootFlagConfig(ulBootFlag)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_CheckArmTCM
 ��������  : TCM���
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   0xffff0000�����ɹ���TCM����
            ��ַ��������ĵ�ַ��0��0x5fff��
            0xffffffff:���ʧ��

*****************************************************************************/
extern unsigned int BSP_MNTN_CheckArmTCM(void);
#define DRV_CHECK_ARM_TCM()    BSP_MNTN_CheckArmTCM()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExchOMSaveRegister
 ��������  : ע��������trace���溯���������ڵ��帴λʱ��
             ���浱ǰ���������־��Ϣ��
 �������  : funcType: ����ID
             pFunc:ע��Ļص�����
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע���������ͬ��funcTypeֻ��ע��һ���ص��������ظ�ע��Ḳ��ԭ������
*****************************************************************************/
extern int BSP_MNTN_ExchOMSaveRegister(int funcType, OM_SAVE_FUNC *pFunc);
#define DRV_SAVE_REGISTER(funcType, pFunc)    BSP_MNTN_ExchOMSaveRegister(funcType, pFunc)

#if defined(VERSION_V7R1_C010)
/*****************************************************************************
 �� �� ��  : BSP_MNTN_SystemError
 ��������  : ϵͳ��������
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
#define DRV_SYSTEM_ERROR(modId, arg1, arg2, arg3, arg3Length)\
                   BSP_MNTN_SystemError(modId, arg1, arg2, arg3, arg3Length)
#else
/*****************************************************************************
 �� �� ��  : systemError
 ��������  : ϵͳ��������
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void systemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
#define DRV_SYSTEM_ERROR(modId, arg1, arg2, arg3, arg3Length)\
                    systemError(modId, arg1, arg2, arg3, arg3Length)
#endif

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExchMemMalloc
 ��������  : ��systemOsaError�ӿ�һ��������¼���ĸ�λ��Ϣ��
             Ŀǰ���֧��128k.
 �������  : ulSize - �ڴ��С
 �������  : �ޡ�
 �� �� ֵ  : �ڴ��ַ
*****************************************************************************/
extern unsigned int BSP_MNTN_ExchMemMalloc(unsigned int ulSize);
#define DRV_EXCH_MEM_MALLOC(ulSize)    BSP_MNTN_ExchMemMalloc(ulSize)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_OmExchFileSave
 ��������  : ������¼ARM��DSP�������쳣�ļ�
 �������  :    address��buffer��ַ
                length���洢����
                IsFileEnd��1��ʾ�ļ������һ�飬0��ʾ�����һ��
 �������  : �ޡ�
 �� �� ֵ  : 0 ΪOK��
*****************************************************************************/
extern int BSP_MNTN_OmExchFileSave(void * address, unsigned long length, unsigned char IsFileEnd,unsigned char FileType);
#define DRV_EXCH_FILE_SAVE(address, length, IsFileEnd, FileType) BSP_MNTN_OmExchFileSave(address, length, IsFileEnd, FileType)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetHwGpioInfo
 ��������  : Get flash infomation
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_MNTN_GetHwGpioInfo(unsigned char *pGpioInfo, unsigned long usLength );
#define DRV_GET_GPIO_INFO(pGpioInfo, usLength)    BSP_MNTN_GetHwGpioInfo(pGpioInfo, usLength )

/*****************************************************************************
 �� �� ��  : BSP_MNTN_Int4ToString
 ��������  : ���Ĵ�����ֵת��ΪASCII�ַ�
 �������  : �Ĵ�����ֵ����ת���ַ��Ĵ洢�ռ�,���ռ䲻����30byte
 �������  : ת���ַ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_Int4ToString(unsigned int value, char * string);
#define DRV_MEM_VERCONVERT(value,string)    BSP_MNTN_Int4ToString(value, string)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_HeapInfoGet
 ��������  : ��ȡ�������ڴ���Ϣ��
 �������  : allocSize: �Ѿ�����Ķ��ڴ��С����λbyte��
             totalSize: ���ڴ��ܳߴ磬��λbyte��
 �������  : None
 �� �� ֵ  : 0: �����ɹ���
             -1��  ����ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_HeapInfoGet(unsigned int *allocSize, unsigned int *totalSize);
#define DRV_GET_HEAPINFO(allocSize, totalSize)    BSP_MNTN_HeapInfoGet(allocSize, totalSize)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSupportBands
 ��������  : �ӵ����õ�ǰ֧�ֵ�Bands.
 �������  : pusWBands - WCDMA��Ƶ��ֵ
             pusGBands - GSM��Ƶ��ֵ

 �������  : pusWBands - WCDMA��Ƶ��ֵ
             pusGBands - GSM��Ƶ��ֵ

 �� �� ֵ  : 0����ȷ����0: ʧ��
             ͨ��Bitλ����ʾ��ЩƵ��֧�֡�
*****************************************************************************/
extern int BSP_MNTN_GetSupportBands(unsigned short *pusWBands, unsigned short *pusGBands);
#define DRV_GET_SUPPORT_BANDS(pusWBands, pusGBands)    BSP_MNTN_GetSupportBands(pusWBands, pusGBands)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSupportDivBands
 ��������  : �ӵ����õ�ǰ֧�ֵķּ�Ƶ��
 �������  : N/A

 �������  : pDivBands - ���ص�ǰ������֧�ֵķּ�Ƶ�Σ�Ƶ�ΰ�bit
 			      ����ʽ����(ͬW ��G��Ƶ�β�ѯ)

 �� �� ֵ  : 0����ȷ����0: ʧ��
*****************************************************************************/
extern int BSP_MNTN_GetSupportDivBands(unsigned short* pDivBands);

#define DRV_GET_SUPPORT_DIVBANDS(pDivBands)    BSP_MNTN_GetSupportDivBands(pDivBands)

/********************************************************************************************************
 �� �� ��  : BSP_MNTN_WriteSysBackupFile
 ��������  : ��FLASH����ZSP��NV����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int BSP_MNTN_WriteSysBackupFile(void);
#define DRV_BACKUP_SYS_FILE()    BSP_MNTN_WriteSysBackupFile()

/*****************************************************************************
 �� �� ��  : DRV_MNTN_GetExtAntenLockState
 ��������  : ��ȡ���������ߵ�����״̬
 �������  : None
 �������  : 0 - ��������
             1 - ��������
 �� �� ֵ  : 0 - �ɹ�
             ����Ϊʧ��

*****************************************************************************/
extern int BSP_MNTN_GetExtAntenLockState(unsigned int *pulStatus);
#define DRV_GET_ANTEN_LOCKSTATE(enModemId, pulStatus)    BSP_MNTN_GetExtAntenLockState(pulStatus)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExtAntenIntInstall
 ��������  : �ж�ע�ắ����������õ�ǰ������״̬
 �������  : routine   - �жϴ�����
             para      - �����ֶ�
 �������  : None
 �� �� ֵ  : void

*****************************************************************************/
extern void BSP_MNTN_ExtAntenIntInstall(void* routine, int para);
#define DRV_ANTEN_INT_INSTALL(routine, para)    BSP_MNTN_ExtAntenIntInstall(routine, para)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExchHookFuncAdd
 ��������  : �����л����жϹ���ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
extern void BSP_MNTN_ExchHookFuncAdd(void);
#define DRV_EXCH_HOOK_FUNC_ADD()    BSP_MNTN_ExchHookFuncAdd()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExchHookFuncDelete
 ��������  : �����л����жϹ���ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
extern void BSP_MNTN_ExchHookFuncDelete(void);
#define DRV_EXCH_HOOK_FUNC_DELETE()    BSP_MNTN_ExchHookFuncDelete()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExcStackPeakRecord
 ��������  : ��¼����ջ�����������Ϣ.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_ExcStackPeakRecord(void);
#define DRV_STACK_HIGH_RECORD()    BSP_MNTN_ExcStackPeakRecord()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_SubIntHook
 ��������  : �����жϷ����Ӻ���ע�ᡣ��ά�ɲ����
 �������  : p_Func�����Ӻ���ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_SubIntHook(pFUNCPTR p_Func);
#define DRV_VICINT_HOOK_ADD(p_Func)    BSP_MNTN_SubIntHook(p_Func)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_SubIntHookDel
 ��������  : �����жϷ����Ӻ���ע������ά�ɲ����
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_SubIntHookDel(void);
#define DRV_VICINT_HOOK_DEL()    BSP_MNTN_SubIntHookDel()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_IntBreakInHook
 ��������  : һ���ж���ڹ��Ӻ���ע�ᡣ��ά�ɲ����
 �������  : p_Func :���Ӻ�����
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntBreakInHook(pFUNCPTR p_Func);
#define DRV_VICINT_IN_HOOK_ADD(p_Func)   BSP_MNTN_IntBreakInHook(p_Func)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_IntBreakInHookDel
 ��������  : һ���ж���ڹ��Ӻ���ע������ά�ɲ����
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntBreakInHookDel(void);
#define DRV_VICINT_IN_HOOK_DEL()    BSP_MNTN_IntBreakInHookDel()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_IntBreakOutHook
 ��������  : һ���жϳ��ڹ��Ӻ���ע�ᡣ��ά�ɲ���أ�V7�ȴ�׮
 �������  : p_Func: ���Ӻ�����
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntBreakOutHook(pFUNCPTR p_Func);
#define DRV_VICINT_OUT_HOOK_ADD(p_Func)    BSP_MNTN_IntBreakOutHook(p_Func)

/*****************************************************************************
 �� �� ��  : vicIntBreakOutHookDel
 ��������  : һ���жϳ��ڹ��Ӻ���ע������ά�ɲ����
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntBreakOutHookDel(void);
#define DRV_VICINT_OUT_HOOK_DEL()    BSP_MNTN_IntBreakOutHookDel()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_IntLvlChgHook
 ��������  : һ���ж�level change���Ӻ���ע�ᡣ��ά�ɲ����
 �������  : p_Func: ���Ӻ�����
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntLvlChgHook(pFUNCPTR p_Func);
#define DRV_VICINT_LVLCHG_HOOK_ADD(p_Func)    BSP_MNTN_IntLvlChgHook(p_Func)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_IntLvlChgHookDel
 ��������  : һ���ж�level change���Ӻ���ע������ά�ɲ����
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_MNTN_IntLvlChgHookDel(void);
#define DRV_VICINT_LVLCHG_HOOK_DEL()    BSP_MNTN_IntLvlChgHookDel()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_TFUPIfNeedNvBackup
 ��������  : ʹ��TF������ǰͨ���ýӿ��ж��Ƿ���Ҫ����NV��.
 �������  : None
 �������  : None
 �� �� ֵ  : 1:��Ҫ����
             0:���豸��
*****************************************************************************/
extern int BSP_MNTN_TFUPIfNeedNvBackup(void);
#define DRV_TF_NVBACKUP_FLAG()    BSP_MNTN_TFUPIfNeedNvBackup()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSDDevName
 ��������  : ��ȡ�豸�б��е�SD�豸��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : SD_DEV_TYPE_STR�ṹָ�롣
*****************************************************************************/
extern SD_DEV_TYPE_STR * BSP_MNTN_GetSDDevName(void);
#define DRV_GET_SD_PATH()     BSP_MNTN_GetSDDevName()

/****************************************** PMUģ�� *******************************************/
/*****************************************************************************
 �� �� ��  : BSP_PMU_GetPMUState
 ��������  : ��ȡPMUģ�鿪����ʽ�����״̬����ص����������λ״̬��
 �������  : �ޡ�
 �������  : Pmu_State :������ʽ�����״̬����ص����������λ״̬��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern unsigned int BSP_PMU_GetPMUState(void*  Pmu_State);
#define DRV_GET_PMU_STATE(Pmu_State)     BSP_PMU_GetPMUState(Pmu_State)

/*****************************************************************************
 �� �� ��  : BSP_PMU_UsbEndRegActionFunc
 ��������  : ���ӿ���USB����/�γ��ص�ע�ắ����
 �������  : srcFunc��ע���USB�����γ���������ʱ�Ļص�����ָ�롣
             actionIndex������ָʾ��
                          0������srcFunc��ע���USB���붯���Ļص�������
                          1������srcFunc��ע���USB�γ������Ļص�������

 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  �����ô˽ӿڣ�����Ҫִ�еĺ���ָ�봫�룬����USB�����γ�ʱ������Ҫִ�еĺ�����
*****************************************************************************/
extern int BSP_PMU_UsbEndRegActionFunc(pFUNCPTR srcFunc, unsigned char actionIndex);
#define DRV_USB_ENDREGACTION_FUNC(srcFunc,actionIndex) \
                BSP_PMU_UsbEndRegActionFunc(srcFunc,actionIndex)


/******************************************PRODUCT_INFOģ��***************************/
/*****************************************************************************
 �� �� ��  : BSP_PROD_GetRecoverNvInfo
 ��������  : �ӵ����õ�ǰ��Ҫ���ǵ�NV��Ϣ
 �������  : N/A

 �������  : ppNvInfo  - ָ��NV��Ϣ�ṹ�������
             pulNvNum  - �������

 �� �� ֵ  : 0����ȷ����0: ʧ��
*****************************************************************************/
extern  int BSP_PROD_GetRecoverNvInfo(void **ppNvInfo, unsigned long *pulNvNum);
#define  DRV_GET_RECOVER_NV_INFO(ppNvInfo, pulNvNum)  \
                BSP_PROD_GetRecoverNvInfo(ppNvInfo, pulNvNum)


/******************************************SDģ��*******************************************/
/*****************************************************************************
 �� �� ��  : BSP_MNTN_GETSDSTATUS
 ��������  : ����SD����λ״̬
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   1��λ
            0����λ

*****************************************************************************/
extern int BSP_MNTN_GETSDSTATUS(void);
#define DRV_SDMMC_GET_STATUS()    BSP_MNTN_GETSDSTATUS()

/*****************************************************************************
 �� �� ��  : SDIO_read_write_blkdata
 ��������  : SD����д�ӿ�
 �������  :    nCardNo     SD����
                dwBlkNo     ����
                nBlkCount   ��д��С
                pbDataBuff  ��д������
                nFlags      ��/д
 �������  : �ޡ�
 ����ֵ��   0:  ��д�ɹ�
            ��0:������
*****************************************************************************/
extern int BSP_MNTN_SDRWBlkData(int nCardNo,unsigned int dwBlkNo,
                   unsigned int nBlkCount, unsigned char *pbDataBuff,int nFlags);
#define DRV_SDMMC_BLK_DATA_RW(nCardNo,dwBlkNo,nBlkCount,pbDataBuff,nFlags)   \
             BSP_MNTN_SDRWBlkData(nCardNo,dwBlkNo,nBlkCount,pbDataBuff, nFlags)

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_ATProcess
 ��������  : at^sd,SD��������д����������ʽ������
 �������  : �������� ulOp:
            0  ��ʽ��SD��
            1  ��������SD�����ݣ�
            2  ����ָ����ַ���ݵĲ���������ָ�����������ݳ���Ϊ512�ֽڡ�������ĵ�ַ��дȫ1
            3  д���ݵ�SD����ָ����ַ�У���Ҫ���ڶ����͵���������
            4  ��ȡulAddrָ���ĵ�ַ(ulAddr*512)��512���ֽڵ����ݵ�pucBuffer��

            ulAddr < address >  ��ַ����512BYTEΪһ����λ��������n��ʾ

            ulData
             < data >            �������ݣ���ʾ512BYTE�����ݣ�ÿ���ֽڵ����ݾ���ͬ��
             0       �ֽ�����Ϊ0x00
             1       �ֽ�����Ϊ0x55
             2       �ֽ�����Ϊ0xAA
             3       �ֽ�����Ϊ0xFF

 �������  : pulErr
 �� �� ֵ  : 0 ��OK  �� 0 ��Error

            ����Ĵ���ֵ�����*pulErr��
            0 ��ʾSD������λ
            1 ��ʾSD����ʼ��ʧ��
            2 ��ʾ<opr>�����Ƿ�����Ӧ������֧��(�ô�����ATʹ��,����Ҫ����ʹ��)
            3 ��ʾ<address>��ַ�Ƿ�������SD����������
            4 ����δ֪����
*****************************************************************************/
extern  unsigned long  BSP_SDMMC_ATProcess(SD_MMC_OPRT_ENUM_UINT32 ulOp,
                unsigned long ulAddr,  unsigned long ulData,unsigned char *pucBuffer,unsigned long *pulErr);
#define DRV_SDMMC_AT_PROCESS(ulOp,ulAddr,ulData,pucBuffer,pulErr)   \
                     BSP_SDMMC_ATProcess (ulOp,ulAddr,ulData,pucBuffer,pulErr)

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_GetOprtStatus
 ��������  : at^sd,SD����ǰ����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
            0: δ����������Ѿ����;
            1: ������
            2: �ϴβ���ʧ��
*****************************************************************************/
extern unsigned long BSP_SDMMC_GetOprtStatus(void);
#define DRV_SDMMC_GET_OPRT_STATUS()    BSP_SDMMC_GetOprtStatus()


typedef enum USB_CHARGE_TYPE_ENUM_tag
{
    USB_CHARGE_TYPE_NON_CHECK = -1,          /* ��δ�жϳ������������� */
    USB_CHARGE_TYPE_HW = 0,                      /* ��Ϊ�����             */
    USB_CHARGE_TYPE_NON_HW =1,                  /* �ǻ�Ϊ�����           */

}USB_CHARGE_TYPE_ENUM;

/*Battery query API*/
typedef enum CHARGING_STATE_ENUM_tag
{
    CHARGING_INIT = -1,
    NO_CHARGING_UP= 0,         /* ����δ���*/
    CHARGING_UP,               /*�������ڳ�� */
    NO_CHARGING_DOWN,          /* �ػ�δ��� */
    CHARGING_DOWN,             /* �ػ����  */
}CHARGING_STATE_ENUM;

/* ��ص������͵�����ѯ**/
typedef enum BATT_LEVEL_ENUM_tag
{
    BATT_INIT = -2,
    BATT_LOW_POWER = -1 ,  /*��ص͵磬*/
    BATT_LEVEL_0,                 /*0���ص���**/
    BATT_LEVEL_1 ,                /*1���ص���*/
    BATT_LEVEL_2 ,                 /*2���ص���*/
    BATT_LEVEL_3 ,               /*3���ص���*/
    BATT_LEVEL_4  ,              /*4���ص���*/
    BATT_LEVEL_MAX
}BATT_LEVEL_ENUM;



typedef struct BATT_STATE_tag
{
   CHARGING_STATE_ENUM  charging_state;
   BATT_LEVEL_ENUM           battery_level;
}BATT_STATE_T;

/*****************************************************************************
 �� �� ��  : BSP_CHG_StateSet
 ��������  :ʹ�ܻ��߽�ֹ���
 �������  :ulState      0:��ֹ���
 						1:ʹ�ܳ��
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
extern void BSP_CHG_StateSet(unsigned long ulState);
#define DRV_CHG_STATE_SET(ulState)    BSP_CHG_StateSet(ulState)

/*****************************************************************************
 �� �� ��  : BSP_CHG_GetBatteryState
 ��������  :��ȡ�ײ���״̬��Ϣ
 �������  :battery_state ������Ϣ
 �������  :battery_state ������Ϣ
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
extern int BSP_CHG_GetBatteryState(BATT_STATE_T *battery_state);
#define DRV_CHG_GET_BATTERY_STATE(battery_state)    BSP_CHG_GetBatteryState(battery_state)

/*****************************************************************************
 �� �� ��  : BSP_CHG_ChargingStatus
 ��������  :��ѯĿǰ�Ƿ����ڳ����
 �������  :��
 �������  :��
 ����ֵ��   0 δ���
                          1 �����
*****************************************************************************/
extern int BSP_CHG_ChargingStatus(void);
#define DRV_CHG_GET_CHARGING_STATUS()    BSP_CHG_ChargingStatus()

/*****************************************************************************
 �� �� ��  : BSP_CHG_GetCbcState
 ��������  : ���ص��״̬�͵���
 �������  :pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 �������  : pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
extern int BSP_CHG_GetCbcState(unsigned char *pusBcs,unsigned char *pucBcl);
#define DRV_CHG_GET_CBC_STATE(pusBcs,pucBcl)    BSP_CHG_GetCbcState(pusBcs,pucBcl)

/*************************INT BEGIN*****************************/
typedef void(* USB_NET_DEV_SWITCH_GATEWAY)
(
    void
);
extern void DRV_AT_SETAPPDAILMODE(unsigned int ulStatus);


/*****************************************************************************
 �� �� ��  : BSP_USB_NASSwitchGatewayRegExtFunc
 ��������  : ���ӿ�����NASע���л�����֪ͨ�ص�����
 �������  :�ص��ӿڡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ɹ�
                       ����:ʧ��
*****************************************************************************/
extern int BSP_USB_NASSwitchGatewayRegFunc(USB_NET_DEV_SWITCH_GATEWAY switchGwMode) ;
#define DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC(switchGwMode)    BSP_USB_NASSwitchGatewayRegFunc(switchGwMode)

/*************************CLK BEGIN*****************************/
/*****************************************************************************
 �� �� ��  : BSP_ONOFF_DrvPowerOff
 ��������  : ����ֱ���µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
extern void BSP_ONOFF_DrvPowerOff(void);
#define DRV_POWER_OFF() BSP_ONOFF_DrvPowerOff()

/************************************************************************
 * FUNCTION
 *       max_freeblock_size_get
 * DESCRIPTION
 *       get memory max free block size
 * INPUTS
 *       ��
 * OUTPUTS
 *       max free block size
 *************************************************************************/
extern int DRV_GET_FREE_BLOCK_SIZE(void);

/*****************************************************************************
 �� �� ��  : BSP_SDMMC_UsbGetStatus
 ��������  : ����SD��״̬
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   0  Ϊ����
           ��0 ������

*****************************************************************************/
extern unsigned int BSP_SDMMC_UsbGetStatus(void);
#define DRV_SDMMC_USB_STATUS()    BSP_SDMMC_UsbGetStatus();


/****************************************** SYSCTRLģ��*******************************************/
/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspReset
 ��������  : ���ӿ�ʵ��ZSPģ��ĸ�λ����������zsp core�����ߺ����衣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_DspReset(void);
#define DRV_DSP_ZONE_RESET()    BSP_GUSYS_DspReset()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspResetCancel
 ��������  : ���ӿ�ʵ��ZSPģ��Ľ⸴λ����������zsp core�����ߺ����衣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_DspResetCancel(void);
#define DRV_DSP_ZONE_RESET_CANCEL()    BSP_GUSYS_DspResetCancel()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ABBGSMRxCtrl
 ��������  : ���ӿ�ʵ��ABB GSM���տ��ơ�
 �������  : ucStatus��0���رգ�1���򿪡�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern unsigned int BSP_GUSYS_ABBGSMRxCtrl(unsigned char ucStatus);
#define DRV_ABB_GRX_CTRL(ucStatus)    BSP_GUSYS_ABBGSMRxCtrl(ucStatus)

/*****************************************************************************
 �� �� ��  : ABBWCDMARxCtrl
 ��������  : ���ӿ�ʵ��ABB WCDMA���տ��ơ�
 �������  : ucStatus��0���رգ�1���򿪡�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern unsigned int BSP_GUSYS_ABBWCDMARxCtrl(unsigned char ucStatus);
#define DRV_ABB_WRX_CTRL(ucStatus)    BSP_GUSYS_ABBWCDMARxCtrl(ucStatus)

/*****************************************************************************
 �� �� ��  : ABBTxCtrl
 ��������  : ���ӿ�ʵ��ABB ���Ϳ��ơ�
 �������  : ucStatus��0���رգ�1���򿪡�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ��ABB���Ϳ��Ʋ�����W/Gģʽ��
*****************************************************************************/
extern int BSP_GUSYS_ABBTxCtrl(unsigned char ucStatus);
#define DRV_ABB_TX_CTRL(ucStatus)    BSP_GUSYS_ABBTxCtrl(ucStatus)

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_WcdmaBbpPllEnable
 ��������  : ���ӿ�ʵ��ʹ��WCDMA BBP PLL��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_WcdmaBbpPllEnable(void);
#define DRV_WBBP_PLL_ENABLE()    BSP_GUSYS_WcdmaBbpPllEnable()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_WcdmaBbpPllDisable
 ��������  : ���ӿ�ʵ�ֹر�WCDMA BBP PLL��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_WcdmaBbpPllDisable(void);
#define DRV_WBBP_PLL_DSABLE()    BSP_GUSYS_WcdmaBbpPllDisable()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_GsmBbpPllEnable
 ��������  : ���ӿ�ʵ��ʹ��GSM BBP PLL��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_GsmBbpPllEnable(void);
#define DRV_GBBP_PLL_ENABLE()    BSP_GUSYS_GsmBbpPllEnable()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_GsmBbpPllDisable
 ��������  : ���ӿ�ʵ�ֹر�GSM BBP PLL��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_GsmBbpPllDisable(void);
#define DRV_GBBP_PLL_DISABLE()    BSP_GUSYS_GsmBbpPllDisable()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_RFLdoOn
 ��������  : ���ӿ�ʵ��WCDMA��GSM RF LDO�ϵ硣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_RFLdoOn(void);
#define DRV_RF_LDOUP()    BSP_GUSYS_RFLdoOn()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_RFLdoDown
 ��������  : ���ӿ�ʵ��WCDMA��GSM RF LDO�µ硣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_RFLdoDown(void);
#define DRV_RF_LDODOWN()    BSP_GUSYS_RFLdoDown()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_WcdmaPllStatusGet
 ��������  : ��ȡWCDMA BBP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
extern unsigned long BSP_GUSYS_WcdmaPllStatusGet(void);
#define DRV_GET_WCDMA_PLL_STATUS()    BSP_GUSYS_WcdmaPllStatusGet()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_GsmPllStatusGet
 ��������  : ��ȡGSM BBP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
extern unsigned long BSP_GUSYS_GsmPllStatusGet(void);
#define DRV_GET_GSM_PLL_STATUS()    BSP_GUSYS_GsmPllStatusGet()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspPllStatusGet
 ��������  : ��ȡDSP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
extern unsigned long BSP_GUSYS_DspPllStatusGet(void);
#define DRV_GET_DSP_PLL_STATUS()    BSP_GUSYS_DspPllStatusGet()




/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ArmPllStatusGet
 ��������  : ��ȡARM PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
extern unsigned int BSP_GUSYS_ArmPllStatusGet(void);
#define DRV_GET_ARM_PLL_STATUS()    BSP_GUSYS_ArmPllStatusGet()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_BBPAutoAdjust
 ��������  : ��ʼ��ABB����У׼ʹ��
 �������  : uiSysMode��0��WCDMAģʽ��1��GSMģʽ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_GUSYS_BBPAutoAdjust(unsigned char ucAdjustMode);
#define DRV_BBP_AUTO_ADJUST(ucAdjustMode)    BSP_GUSYS_BBPAutoAdjust(ucAdjustMode)

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspPllEnable
 ��������  : ��DSP PLL
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_DspPllEnable(void);
#define DRV_DSP_PLL_ENABLE()    BSP_GUSYS_DspPllEnable()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspPllDisable
 ��������  : �ر�DSP PLL
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUSYS_DspPllDisable(void);
#define DRV_DSP_PLL_DISABLE()    BSP_GUSYS_DspPllDisable()


/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ModeSwitchs
 ��������  : ���ӿ�ʵ��WCDMA/GSMϵͳģʽ�л���
 �������  : uiSysMode��0���л���WCDMAģʽ��1���л���GSMģʽ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_GUSYS_ModeSwitch(unsigned int uiSysMode);
#define DRV_SYSMODE_SWITCH(uiSysMode)    BSP_GUSYS_ModeSwitch(uiSysMode)


/******************************************UDI�ӿ�ģ��*******************************************/
/*****************************************************************************
 �� �� ��  : udi_open
 ��������  : ���ӿڿɴ�ָ����UDI�豸��
 �������  : pParam����Ҫ�򿪵��豸�ṹ��
 �������  : �ޡ�
 �� �� ֵ  : -1������ʧ�ܡ�
             ����ֵ:  �����ɹ���
 ע������  ����
*****************************************************************************/
/*extern UDI_HANDLE udi_open(UDI_OPEN_PARAM *pParam);*/
#define DRV_UDI_OPEN(pParam)    udi_open(pParam)

/*****************************************************************************
 �� �� ��  : udi_write
 ��������  : ���ӿڿ����򿪵�UDI�豸�������ݡ�
 �������  : handle:  �豸��handle
*            pMemObj: buffer�ڴ� �� �ڴ��������
*            u32Size: ����д�ߴ� �� �ڴ��������ɲ�����
 �������  : �ޡ�
 �� �� ֵ  : -1������ʧ�ܡ�
             ����ֵ:  �����ɹ���
 ע������  ������ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
/*extern BSP_S32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);*/
#define  DRV_UDI_WRITE(handle,pMemObj,u32Size)     udi_write (handle,pMemObj,u32Size)

/*****************************************************************************
* �� �� ��  : udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ���ݶ��ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
/*extern BSP_S32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);*/
#define DRV_UDI_READ(handle,pMemObj,u32Size)  udi_read(handle,pMemObj,u32Size)


/*****************************************************************************
* �� �� ��  : udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
/*extern BSP_S32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, VOID* pParam);*/
#define DRV_UDI_IOCTL(handle,u32Cmd,pParam)    udi_ioctl(handle,u32Cmd,pParam)

/*****************************************************************************
* �� �� ��  : udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
/*BSP_S32 udi_close(UDI_HANDLE handle);*/
#define DRV_UDI_CLOSE(handle)    udi_close(handle)


/****************************************** USBģ��(��Ʒ����������ʱ��׮) *******************************************/
/*****************************************************************************
 �� �� ��  : BSP_USB_SetPid
 ��������  :
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_USB_SetPid(unsigned char u2diagValue);
#define DRV_SET_PID(u2diagValue)    BSP_USB_SetPid(u2diagValue)

#if defined(VERSION_V7R1_C010)
/*****************************************************************************
��������   BSP_USB_PortTypeQuery
��������:  ��ѯ��ǰ���豸ö�ٵĶ˿���ֵ̬
��������� stDynamicPidType  �˿���̬
��������� stDynamicPidType  �˿���̬
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
unsigned int BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType);
#define DRV_SET_PORT_QUIRY(a)   BSP_USB_PortTypeQuery(a)
#else
/*****************************************************************************
��������   set_port_quiry
��������:  ��ѯ��ǰ���豸ö�ٵĶ˿���ֵ̬
��������� stDynamicPidType  �˿���̬
��������� stDynamicPidType  �˿���̬
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
unsigned int set_port_quiry(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType);
#define DRV_SET_PORT_QUIRY(a)   set_port_quiry(a)
#endif

/*****************************************************************************
 �� �� ��  : BSP_USB_ATProcessRewind2Cmd
 ��������  : rewind2 CMD ����
 �������  : pData�����ݡ�
 �������  : ��
 �� �� ֵ  : false(0):����ʧ��
             tool(1):����ɹ�
*****************************************************************************/
extern int BSP_USB_ATProcessRewind2Cmd(unsigned char *pData);
#define DRV_PROCESS_REWIND2_CMD(pData)    BSP_USB_ATProcessRewind2Cmd(pData)


/*****************************************************************************
 �� �� ��  : BSP_USB_GetDiagModeValue
 ��������  : ����豸���͡�
 �������  : �ޡ�
 �������  : ucDialmode:  0 - ʹ��Modem����; 1 - ʹ��NDIS����; 2 - Modem��NDIS����
              ucCdcSpec:   0 - Modem/NDIS������CDC�淶; 1 - Modem����CDC�淶;
                           2 - NDIS����CDC�淶;         3 - Modem/NDIS������CDC�淶
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
extern BSP_S32 BSP_USB_GetDiagModeValue(unsigned char *pucDialmode,
                             unsigned char *pucCdcSpec);
#define DRV_GET_DIAG_MODE_VALUE(pucDialmode, pucCdcSpec)    \
                             BSP_USB_GetDiagModeValue(pucDialmode, pucCdcSpec)


/*****************************************************************************
 �� �� ��  : BSP_USB_GetPortMode
 ��������  : ��ȡ�˿���̬ģʽ�����ضԽ����󣬴�׮��
 �������  : ��
 �������  :
 �� �� ֵ  :
*****************************************************************************/
extern unsigned char BSP_USB_GetPortMode(char*PsBuffer, unsigned long*Length );
#define DRV_GET_PORT_MODE(PsBuffer, Length)    BSP_USB_GetPortMode(PsBuffer,Length)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetU2diagDefaultValue
 ��������  : ��ö˿�Ĭ��u2diagֵ
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   u2diagֵ

*****************************************************************************/
extern BSP_U32 BSP_USB_GetU2diagDefaultValue(void);
#define DRV_GET_U2DIAG_DEFVALUE()    BSP_USB_GetU2diagDefaultValue()

/*****************************************************************************
 �� �� ��  : ErrlogRegFunc
 ��������  : USB MNTNע���쳣��־�ӿڣ�Porting��Ŀ�д�׮
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   ��

*****************************************************************************/
/*extern void ErrlogRegFunc(MNTN_ERRLOGREGFUN pRegFunc);*/
#define MNTN_ERRLOG_REG_FUNC(pRegFunc)

/*****************************************************************************
 �� �� ��  : BSP_USB_UdiagValueCheck
 ��������  : ���ӿ����ڼ��NV����USB��ֵ̬�ĺϷ���.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��OK��
            -1��ERROR
*****************************************************************************/
extern int BSP_USB_UdiagValueCheck(unsigned long DiagValue);
#define DRV_UDIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)
#define DRV_U2DIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetLinuxSysType
 ��������  : ���ӿ����ڼ��PC���Ƿ�ΪLinux���Թ��Linux��̨���β���ʧ�ܵ�����.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��Linux��
            -1����Linux��
*****************************************************************************/
extern int BSP_USB_GetLinuxSysType(void) ;
#define DRV_GET_LINUXSYSTYPE()    BSP_USB_GetLinuxSysType()



/***************************************************************SCIģ��*********************************************************************/
/*************************************************************************************************************************************
 �� �� ��  : BSP_SCI_Reset
 ��������  : ���ӿ����ڸ�λSCI��Smart Card Interface��������USIM��Universal Subscriber Identity Module������
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
 ע������  ���ڿ�δ����ʱ���ܵ��ã��ں�������ǰ����ȷ��USIM���Ѳ��룬�������ʾ����������Ч����Ҫ���뿨�����µ��á�
*************************************************************************************************************************************/
/*extern void BSP_SCI_Reset(void);*/
#define DRV_USIMMSCI_RST()    BSP_SCI_Reset()

/********************************************************************************************************************
 �� �� ��  : BSP_SCI_GetCardStatus
 ��������  : ���ӿ����ڻ�ÿ���ǰ��״̬��ĿǰLTE�ṩ�ӿڲ������Ͳ�һ��
 �������  : �ޡ�
 �������  :
 �� �� ֵ  : 0:  ������Ready��
             -1����δ����Ready��
 ע������  ����Ч����BSP_SCI_Reset()�������ٵ��ô˺�����
********************************************************************************************************************/
extern int BSP_GUSCI_GetCardStatus();
#define DRV_USIMMSCI_GET_CARD_STAU()    BSP_GUSCI_GetCardStatus()


/********************************************************************************************************************
 �� �� ��  : BSP_SCI_SendData
 ��������  : ���ӿ����ڷ���һ�����ݵ�USIM����
 �������  : ulDataLength���������ݵ���Ч���ȡ�ȡֵ��Χ1��511����λΪ�ֽڡ�
             pucDataBuffer���������������ڴ���׵�ַ�����Ƕ�̬���䣬���ýӿں��������ͷţ�������Ӳ���������ݡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ��USIMMSCIReset()������Ч���ú��ٵ��ô˺�������ȷ�������������Ч�ԡ�
********************************************************************************************************************/
/*extern int BSP_SCI_SendData(unsigned long ulDataLength, unsigned char *pucDataBuffer);*/
#define DRV_USIMMSCI_SND_DATA(ulDataLength,pucDataBuffer)\
                BSP_SCI_SendData(ulDataLength,pucDataBuffer)

/********************************************************************************************************************
 �� �� ��  : USIMMSCIReceived
 ��������  : ���ӿ�����USIM Manager��ȡ����SCI Driver��USIMMSCIPreRead()����ָ������������
 �������  : ulDataLength��USIM Manager����SCI Driver��ȡ�������ֽ�����
                           ȡֵ��ΧӦ��USIMMSCIPreRead()����ָ�������ݳ�����ͬ��
 �������  : pucDataBuffer��USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
                            ȡֵ��Χ�ǲ���ϵͳ������̬������߾�̬����ĵ�ַ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ���յ��ײ㷢�����ݳ���������Ϣ���ٵ��ô˺��������յĳ���Ӧ�ú�Ԥ���ĳ���һ�¡�
********************************************************************************************************************/
/*extern int BSP_SCI_ReceiveSync(unsigned long ulDataLength,unsigned char *pucDataBuffer);*/
#define DRV_USIMMSCI_RCV(ulDataLength,pucDataBuffer)    BSP_SCI_ReceiveSync(ulDataLength,pucDataBuffer)

/********************************************************************************************************************
 �� �� ��  : USIMMSCIGetATR
 ��������  : ���ӿ����ڽ�Driver�㻺���ATR���ݺ����ݸ������ظ�USIM Manager�㡣
 �������  : �ޡ�
 �������  : ulDataLength��Driver��ȡ��ATR���ݳ��ȣ����ظ�USIM Manager��ȡֵ��Χ0��32����λ���ֽڡ�
             pucATR��USIM Managerָ����Buffer��SCI Driver��ATR���ݿ�������Buffer��
                     һ��Ϊ����ϵͳ������̬������߾�̬����ĵ�ַ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ����Ч����USIMMSCIReset()�������ٵ��ô˺�����
********************************************************************************************************************/
/*extern int BSP_SCI_GetATR(unsigned long *pulDataLength,unsigned char  *pucATR);*/
#define DRV_USIMMSCI_GET_ATR(pulDataLength,pucATR)    BSP_SCI_GetATR(pulDataLength,pucATR)

/*****************************************************************************
 �� �� ��  : USIMMSCIClassSwitch
 ��������  : ���ӿ�����֧��PS�Կ��ĵ�ѹ���ͽ����л�����1.8V�л���3V��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0�� �����ɹ�����ǰ��ѹ������ߵģ����е�ѹ�л���������
             -1������ʧ�ܣ���ǰ��ѹ�Ѿ�����ߵ�ѹ��û�н��е�ѹ�л�����
 ע������  ����Ч����USIMMSCIReset()�������ٵ��ô˺�����
*****************************************************************************/
/*extern int BSP_SCI_ClassSwitch(void);*/
#define DRV_USIMMSCI_CLASS_SWITCH()    BSP_SCI_ClassSwitch()

/*****************************************************************************
 �� �� ��  : USIMMSCITimeStop
 ��������  : ���ӿ�����֧��PS�ر�SIM��ʱ�ӡ���Ч����USIMMSCIReset()�������ٵ��ô˺�����
 �������  : ulCardType��������ʶ�������USIM or SIM��
             ulTimeStopCfg�������֧��ʱ��ֹͣģʽ����������������SIM������ʼ��ֹͣģʽʱ��ʱ�ӵ�ѹ�ߵ�״̬��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ����Ч����USIMMSCIReset()�������ٵ��ô˺�����
*****************************************************************************/
/*extern int BSP_SCI_TimeStop(unsigned long ulStopType);*/
#define DRV_USIMMSCI_TM_STOP(ulStopType)    BSP_SCI_TimeStop(ulStopType)

/*****************************************************************************
 �� �� ��  : USIMMSCIDeactive
 ��������  : ���ӿ����ڶ�SIM����ȥ���������
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ����Ч����USIMMSCIReset()�������ٵ��ô˺�����
*****************************************************************************/
/*extern int BSP_SCI_Deactive(void);*/
#define DRV_USIMMSCI_DEACT()    BSP_SCI_Deactive()

/*****************************************************************************
 �� �� ��  : USIMMSCIGetClkStatus
 ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��״̬��
 �������  : �ޡ�
 �������  : pulSciClkStatus������ָ�룬���ڷ���SIM��ʱ��״̬��
                              0��ʱ���Ѵ򿪣�1��ʱ��ֹͣ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܣ�ָ�����Ϊ�ա�
 ע������  ����Ч����USIMMSCIReset()�������ٵ��ô˺�����
*****************************************************************************/
/*extern int BSP_SCI_GetClkStatus(unsigned long *pulSciClkStatus);*/
#define DRV_USIMMSCI_GET_CLK_STAU(pulSciClkStatus)    BSP_SCI_GetClkStatus(pulSciClkStatus)

/*****************************************************************************
 �� �� ��  : sciRecordDataSave
 ��������  : ���ӿ����ڻ�ȡ��ǰSIM���������ݡ������쳣����ģ�飬V7�ȴ�׮
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܣ�ָ�����Ϊ�ա�
 ע������  ��
*****************************************************************************/
/*extern int sciRecordDataSave(void);*/
#define DRV_USIMMSCI_RECORD_DATA_SAVE()        DRV_OK

/*****************************************************************************
 �� �� ��  : USIMMSCIGetPCSCParameter
 ��������  : PCSC�����ȡ��������
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
/*extern unsigned long BSP_SCI_GetPCSCParameter(unsigned char *pbuf);*/
#define DRV_PCSC_GET_SCI_PARA(Para)    BSP_SCI_GetPCSCParameter(Para)


/*****************************************************************************
 �� �� ��  : USIMMGetCLKFREQ
 ��������  : PCSC�����ȡʱ��Ƶ�ʲ�������
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
/*extern unsigned long BSP_SCI_GetClkFreq(unsigned long *pDatalen, unsigned char *pbuf);*/
#define DRV_PCSC_GET_CLK_FREQ(pDataLen, Buffer)    BSP_SCI_GetClkFreq(pDataLen, Buffer)


/*****************************************************************************
 �� �� ��  : BSP_SCI_GetBaudRate
 ��������  : PCSC�����ȡʱ�����ʲ�������
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
/*extern unsigned long BSP_SCI_GetBaudRate(unsigned long *pDatalen, unsigned char *pbuf);*/
#define DRV_PCSC_GET_BAUD_RATE(pDataLen, Buffer)    BSP_SCI_GetBaudRate(pDataLen, Buffer)


/***********************************Watch Dogģ��*****************************************/
/*****************************************************************************
 �� �� ��  : BSP_WDT_Init
 ��������  : ��ʼ�����ƿ��Ź������ó�ʱʱ�䣬�ҽ��жϷ�������
 �������  : wdtId�����Ź�ID��
                    ȡֵ��Χ����Ӳ���ṩ1�����Ź�����ֻ��ȡֵΪ0��
                    ��Ӳ���ṩ2�����Ź�����ȡֵΪ0/1��
             wdtTimeOutms�����Ź���ʱʱ�䣬��λ���롣ʱ������ܳ���1���ʱ�䡣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ���ú���ֻ�ܱ�һ��������ã�������������Ź���������ģ��������ڵ��ԣ����򲻵õ��øÿ��Ź���Ϊ��ʱ���ߡ�
*****************************************************************************/
/*extern int BSP_WDT_Init(unsigned char wdtId, unsigned long wdtTimeOutms);*/
#define DRV_WDT_INIT(wdtId,wdtTimeOutms)      BSP_WDT_Init(wdtId,wdtTimeOutms)

/*****************************************************************************
 �� �� ��  : wdtEnable
 ��������  : �������Ź���
 �������  : wdtId�����Ź�ID��
                    ȡֵ��Χ����Ӳ���ṩ1�����Ź�����ֻ��ȡֵΪ0��
                    ��Ӳ���ṩ2�����Ź�����ȡֵΪ0/1��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ���ú���ֻ�ܱ�һ��������ã�������������Ź���������ģ��������ڵ��ԣ����򲻵õ��øÿ��Ź���Ϊ��ʱ���ߡ�
*****************************************************************************/
/*extern int BSP_WDT_Enable(unsigned char wdtId);*/
#define DRV_WDT_ENABLE(wdtId)    BSP_WDT_Enable(wdtId)

/*****************************************************************************
 �� �� ��  : BSP_WDT_HardwareFeed
 ��������  : ������Ź��жϣ�ι������
 �������  : wdtId�����Ź�ID��
                    ȡֵ��Χ����Ӳ���ṩ1�����Ź�����ֻ��ȡֵΪ0��
                    ��Ӳ���ṩ2�����Ź�����ȡֵΪ0/1��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ���ú���ֻ�ܱ�һ��������ã�������������Ź���������ģ��������ڵ��ԣ����򲻵õ��øÿ��Ź���Ϊ��ʱ���ߡ�
*****************************************************************************/
/*extern int BSP_WDT_HardwareFeed(unsigned char wdtId);*/
#define DRV_WDT_FEED(wdtId)    BSP_WDT_HardwareFeed(wdtId)

/*****************************************************************************
 �� �� ��  : BSP_WDT_Disable
 ��������  : �رտ��Ź���
 �������  : wdtId�����Ź�ID��
                    ȡֵ��Χ����Ӳ���ṩ1�����Ź�����ֻ��ȡֵΪ0��
                    ��Ӳ���ṩ2�����Ź�����ȡֵΪ0/1��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  ���ú���ֻ�ܱ�һ��������ã�������������Ź���������ģ��������ڵ��ԣ����򲻵õ��øÿ��Ź���Ϊ��ʱ���ߡ�
*****************************************************************************/
/*extern int BSP_WDT_Disable(unsigned char wdtId);*/
#define DRV_WDT_DISABLE(wdtId)    BSP_WDT_Disable(wdtId)


/***********************************�ڴ濽���Ż�*****************************************/
/*****************************************************************************
 �� �� ��  : __rt_memcpy
 ��������  : ���汾��memcpy����
 �������  : Dest :Ŀ�ĵ�ַ
             Src :Դ��ַ
             Count:�������ݵĴ�С
 �������  : �ޡ�
 �� �� ֵ  : Ŀ�ĵ�ַ��
*****************************************************************************/
extern void * __rt_memcpy(void * Dest, const void * Src, unsigned long Count);
#define DRV_RT_MEMCPY(Dest,Src,Count)       __rt_memcpy(Dest,Src,Count)


/***********************************GU DSP����*****************************************/
/*****************************************************************************
 �� �� ��  : BSP_GUDSP_LayerInfoGet
 ��������  : ��ȡ����������Ϣ��
 �������  : �ޡ�
 �������  : pulAddr���������������Ϣ�Ļ��档
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern void BSP_GUDSP_LayerInfoGet(unsigned long* pulAddr, unsigned long* pulLength);
#define DRV_PHY_SLOAD_INFO_GET(pulAddr,pulLength)    BSP_GUDSP_LayerInfoGet(pulAddr,pulLength)

/*****************************************************************************
 �� �� ��  : BSP_GUDSP_CommonInfoGet
 ��������  : ��ȡ�����BSS COMMON����Ϣ��
 �������  : �ޡ�
 �������  : pulAddr���������������Ϣ�Ļ��档
 �� �� ֵ  : 0:�ɹ���-1:ʧ�ܡ�
*****************************************************************************/
extern int BSP_GUDSP_CommonInfoGet(unsigned long* pulAddr, unsigned long* pulLength);
#define DRV_DSP_COMMON_INFO_GET(pulAddr,pulLength)    BSP_GUDSP_CommonInfoGet(pulAddr,pulLength)

/*****************************************************************************
 �� �� ��  : BSP_GUDSP_Load
 ��������  : ���GU ZSP���ع��ܣ���ZSP��̬�δ�DDR���ص�ZSP TCM��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:�ɹ���-1:ʧ�ܡ�
*****************************************************************************/
extern int BSP_GUDSP_Load(void);
#define DRV_GUDSP_LOAD()    BSP_GUDSP_Load()


/***********************************MD5���*****************************************/
/*****************************************************************************
 �� �� ��  : cardlock_md5_verify
 ��������  : �жϵ�ǰ�������Ƿ���ȷ .
 �������  : imei       - ����IMEI��
             unlockcode - ������
 �������  : �ޡ�
 �� �� ֵ  : 1��   �����ɹ�
             0:    ����ʧ��
*****************************************************************************/
extern int cardlock_md5_verify(char *imei, char *unlockcode);
#define DRV_CARDLOCK_MD5_VERIFY(imei, unlockcode)    cardlock_md5_verify(imei, unlockcode)


/************************************����궨��Ϊ�յĺ���******************************************/
/*****************************************************************************
 �� �� ��  : UsbStatusCallbackRegister
 ��������  : ��¼pCallBack��ȫ�ֱ����С�SD��������ؽӿڣ�V7�ȴ�׮
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
 /*extern int  UsbStatusCallbackRegister(pUsbState pCallBack);*/
#define DRV_USB_STATUS_CALLBACK_REGI(pCallBack)              DRV_OK

/*****************************************************************************
 �� �� ��  : CicomClkEnable
 ��������  : This routine enable CICOM IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void CicomClkEnable(void);*/
#define DRV_CICOM_CLK_ENABLE()

/*****************************************************************************
 �� �� ��  : CicomClkDisable
 ��������  : This routine disable CICOM IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void CicomClkDisable(void);*/
#define DRV_CICOM_CLK_DISABLE()

/*****************************************************************************
 �� �� ��  : HdlcClkEnable
 ��������  : This routine enable HDLC IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void HdlcClkEnable(void);*/
#define DRV_HDLC_CLK_ENABLE()

/*****************************************************************************
 �� �� ��  : HdlcClkDisable
 ��������  : This routine disable HDLC IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void HdlcClkDisable(void);*/
#define DRV_HDLC_CLK_DISABLE()

/*****************************************************************************
 �� �� ��  : memReadApi
 ��������  : ��32λ��Ȳ�ѯ�ڴ棬���4�ֽ����ݡ���ά�ɲ⣬V7�ȴ�׮
 �������  : ulAddress����ѯ��ַ�ռ��ַ����ַ�����ڴ淶Χ�ڣ����򷵻�-1��
 �������  : pulData��ָ���ѯ���ݵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int  memReadApi (unsigned int ulAddress, unsigned int* pulData);*/
#define DRV_MEM_READ(ulAddress,pulData)     DRV_OK

/*****************************************************************************
 �� �� ��  : DrvLogInstall
 ��������  : ��ӡ����ע�ᡣ��ά�ɲ⣬V7�ȴ�׮
 �������  : fptr ע��ĺ���ָ��
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int DrvLogInstall(PVOIDFUNC fptr, PVOIDFUNC fptr1, PVOIDFUNC fptr2, PVOIDFUNC fptr3, PVOIDFUNC fptr4);*/
#define DRV_LOG_INSTALL(fptr, fptr1, fptr2, fptr3, fptr4)     DRV_OK

/*****************************************************************************
 �� �� ��  : ErrlogRegFunc
 ��������  : �����ģ��ע��Errlogע�ắ����V7����Ϊ��
 �������  : ��

 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ��
*****************************************************************************/
/*extern void ErrlogRegFunc(MNTN_ERRLOGREGFUN pRegFunc);*/
#define MNTN_ERRLOG_REG_FUNC(pRegFunc)


/***************************************************DPMģ�� V7�ȶ���Ϊ��*********************************************************/

//wangwei dfs
typedef  enum
{
    PWRCTRL_DFS_USB = 0,
    PWRCTRL_DFS_SD  = 1,
    PWRCTRL_DFS_PS1 = 2,
    PWRCTRL_DFS_BUTT
} PWC_DFS_ID_E;

typedef enum
{
    DFS_PROFILE_0 = 0,            /*Ƶ�ʼ���1*/
    DFS_PROFILE_1 = 1,            /*Ƶ�ʼ���2*/
    DFS_PROFILE_2 = 2,            /*Ƶ�ʼ���3*/
    DFS_PROFILE_3 = 3,            /*Ƶ�ʼ���4*/
    DFS_PROFILE_4 = 4,            /*Ƶ�ʼ���5*/
    DFS_PROFILE_BUTT
} PWC_DFS_PROFILE_E;//PWC_DFS_PROFILE_E;

/*
 *  DFS Device QoS
 */
typedef enum tagDFS_QOS_ID_E
{
    DFS_QOS_ID_ACPU_MINFREQ_E = 0,  /*(0)*/
    DFS_QOS_ID_ACPU_MAXFREQ_E,      /*(1)*/
    DFS_QOS_ID_CCPU_MINFREQ_E,      /*(2)*/
    DFS_QOS_ID_CCPU_MAXFREQ_E,      /*(3)*/
    DFS_QOS_ID_DDR_MINFREQ_E,       /*(4)*/
    DFS_QOS_ID_DDR_MAXFREQ_E,       /*(5)*/
    DFS_QOS_ID_GPU_MINFREQ_E,       /*(6)*/
    DFS_QOS_ID_GPU_MAXFREQ_E,       /*(7)*/
    DFS_QOS_ID_BUS_MINFREQ_E,       /*(8)*/
    DFS_QOS_ID_BUS_MAXFREQ_E        /*(9)*/
}DFS_QOS_ID_E;


typedef enum tagPWC_COMM_MODE_E
{
    PWC_COMM_MODE_WCDMA,
    PWC_COMM_MODE_GSM,
    PWC_COMM_MODE_LTE,
    PWC_COMM_MODE_TDS,
    PWC_COMM_MODE_BUTT
}PWC_COMM_MODE_E;

typedef enum tagPWC_COMM_MODULE_E
{
    PWC_COMM_MODULE_PA,
    PWC_COMM_MODULE_RF,
    PWC_COMM_MODULE_BBP_SOC,
    PWC_COMM_MODULE_BBP_PWR,
    PWC_COMM_MODULE_DSP,
    PWC_COMM_MODULE_ABB,
    PWC_COMM_MODULE_HIFI,
    PWC_COMM_MODULE_BUTT
}PWC_COMM_MODULE_E;

/* ˯��ͶƱID */
typedef enum tagPWC_CLIENT_ID_E
{
    PWRCTRL_SLEEP_SCI       = 0x100,
    PWRCTRL_SLEEP_PS        = 0x101,
    PWRCTRL_SLEEP_BBPMASTER = 0x102,
    PWRCTRL_SLEEP_CICOM     = 0x103,
    PWRCTRL_SLEEP_NV        = 0x104,

    PWRCTRL_SLEEP_DMA       = 0x108,
    PWRCTRL_SLEEP_FLASH     = 0x109,
    PWRCTRL_SLEEP_SD        = 0x10A,
    PWRCTRL_SLEEP_FTM       = 0x10B,

    PWRCTRL_SLEEP_BOOT      = 0x110,
    PWRCTRL_SLEEP_ACPU      = 0x111,

    PWRCTRL_SLEEP_WIFI      = 0x114,
    PWRCTRL_SLEEP_USB       = 0x115,
    PWRCTRL_SLEEP_LCD       = 0x116,
    PWRCTRL_SLEEP_NCM     	= 0x117,
    PWRCTRL_SLEEP_ACM     	= 0x118,
    PWRCTRL_SLEEP_ICC     	= 0x119,
    PWRCTRL_SLEEP_NAS     	= 0x11a,
    PWRCTRL_SLEEP_LTEPS     = 0x11b,

    /* Test */
    PWRCTRL_TEST_LIGHTSLEEP = 0x11E,
    PWRCTRL_TEST_DEEPSLEEP  = 0x11F,
    PWRCTRL_SLEEP_RNIC      = 0x120,
    PWRCTRL_SLEEP_DSFLOW    = 0x121,
    PWRCTRL_CLIENT_BUTT     = 0x122
} PWC_CLIENT_ID_E;

typedef enum tagPWC_TEMP_PROTECT_E
{
	PWC_TEMP_OLED,
	PWC_TEMP_BATTERY,
	PWC_TEMP_L_PA,
	PWC_TEMP_G_PA,
	PWC_TEMP_W_PA,
	PWC_TEMP_SIM_CARD,
	PWC_TEMP_DCXO,
	PWC_TEMP_BUTT
}PWC_TEMP_PROTECT_E;

typedef struct
{
    PVOIDFUNC drx_slow;
} PWC_SLEEP_CALLBACK_STRU;

/*****************************************************************************
 �� �� ��  : dpm_armsleep
 ��������  : ARM���� normal WFI
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_ARM_SLEEP()

/*****************************************************************************
 �� �� ��  : dpm_lightsleep
 ��������  : ARM���� normal WFI ����ʱ��ֹͣ
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_LIGHT_SLEEP()

/*****************************************************************************
 �� �� ��  : dpm_deepsleep
 ��������  : ARM���� sleep
 �������  : 0 û��USB���� 1 ��USB����
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_DEEP_SLEEP(sleepmode)

/*****************************************************************************
 �� �� ��  : dpm_sleep_callback_register
 ��������  : ע��DPM����������ʹ��
 �������  : ��ע��ĺ���
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_DPM_SLEEP_CALLBACK_REG(Callback)
/*****************************************************************************
 �� �� ��  : dpm_sleep_ahb_bak_addr_alloc
 ��������  : arm���µ繦�ܣ���Ҫ����ahb���ݣ��ýӿ��������ݱ����ַ�ͳ���
 �������  : length     ��������ռ��С��ָ��
 �������  : ��
 �� �� ֵ  : ����ռ�ĵ�ַ ��
*****************************************************************************/
#if defined (VERSION_V3R2)
extern void * dpm_sleep_ahb_bak_addr_alloc(unsigned long * length);
#define DRV_DPM_SLEEP_AHB_BAK_ADDR_ALLOC(length)  dpm_sleep_ahb_bak_addr_alloc(length)
#else
#define DRV_DPM_SLEEP_AHB_BAK_ADDR_ALLOC(length)
#endif
/*****************************************************************************
 �� �� ��  : dpm_bbp_powerdown
 ��������  : BBP�µ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_BBP_POWERDOWN()

/*****************************************************************************
 �� �� ��  : pwrctrl_bbp_powerdown_adjust
 ��������  : BBP�µ�,��SOC
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
#define DRV_BBP_POWERDOWN_ADJUST()
/*****************************************************************************
 �� �� ��  : dpm_bbp_powerup
 ��������  : BBP�ϵ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_BBP_POWERUP()
/*****************************************************************************
 �� �� ��  : pwrctrl_bbp_powerup_adjust
 ��������  : BBP�ϵ�,��SOC
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
#define DRV_BBP_POWERUP_ADJUST()

/*****************************************************************************
 �� �� ��  : dpm_dfs_exec
 ��������  : ����ARMƵ��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_DFS_EXEC(en_curr_profile,en_new_profile)      0

/*****************************************************************************
 �� �� ��  : pwrctrl_rf_pwr_down
 ��������  : RF�µ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_RF_POWERDOWN()

/*****************************************************************************
 �� �� ��  : pwrctrl_rf_pwr_up
 ��������  : RF�ϵ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_RF_POWERUP()

/*****************************************************************************
 �� �� ��  : pwrctrl_rf_pd_io_set
 ��������  : RF�µ磬BB����������
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_RF_DOWN_BB_SET()

/*****************************************************************************
 �� �� ��  : pwrctrl_rf_pu_io_set
 ��������  : RF�ϵ磬BB����������
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/* A13 ��Ƭ�������е͹��Ĺ������� */
#define DRV_RF_UP_BB_SET()

/*****************************************************************************
 �� �� ��  : pwrctrl_usb_lowpower_enter
 ��������  : USB����͹���
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
#define USB_POWER_OFF()

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_SleepVoteLock
 ��������  : �����ֹ˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#define DRV_PWRCTRL_SLEEPVOTE_LOCK(enClientId) DRV_OK
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_SleepVoteUnLock
 ��������  : ��������˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#define DRV_PWRCTRL_SLEEPVOTE_UNLOCK(enClientId) DRV_OK
/*************************************************
 �� �� ��       : secureSupport
 ��������   : ��ǰ�汾�Ƿ�֧�ְ�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ      : OK/ERROR
*************************************************/
#define DRV_SECURE_SUPPORT(pData)    DRV_OK


/*************************************************
 �� �� ��       : secureAlreadyUse
 ��������   : ��ѯ��ǰ�汾�Ƿ��Ѿ����ð�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ      : OK/ERROR
*************************************************/
#define DRV_SECURE_ALREADY_USE(pData)    DRV_OK

/*************************************************
 �� �� ��       : startSecure
 ��������   : ���ð�ȫ����
 �������   :
 �������   :
 �� �� ֵ      : OK/ERROR
*************************************************/
#define DRV_START_SECURE()    DRV_OK


/********************************************************
����˵���� ���ص�ǰ�豸�б���֧��(sel=1)���߲�֧��(sel=0)PCSC���豸��ֵ̬
��������:
���������sel
          0: ͨ������dev_type���ص�ǰ����PCSC���豸��ֵ̬
          1��ͨ������dev_type���ص�ǰ��PCSC���豸��ֵ̬
���������dev_type д����Ҫ���豸��ֵ̬�����û����д��ֵ��
          NV�д洢���豸��ֵ̬
���������pulDevType ��ulCurDevType��Ӧ���豸��ֵ̬�����û�з���ֵ1��
����ֵ��
          0����ѯ����Ӧ���豸��ֵ̬��
          1��û�в�ѯ����Ӧ���豸��ֵ̬��
********************************************************/
int BSP_USB_PcscInfoSet(unsigned int  ulSel, unsigned int  ulCurDevType, unsigned int *pulDevType);
#define DRV_USB_PCSC_INFO_SET(ulSel, ulCurDevType, pulDevType)    BSP_USB_PcscInfoSet(ulSel, ulCurDevType, pulDevType)



/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
extern unsigned int BSP_GetHsicEnumStatus(void);
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()


/********************************************************
��������   BSP_UDI_FindVcom
���������� ��ѯ��ǰ�豸��̬��ָ����UDI���⴮�ڶ˿��Ƿ����
��������� UDI_DEVICE_IDö��ֵ��������ѯ�����⴮�ڶ˿�ID
��������� ��
����ֵ��
           0����ǰ�豸��̬��֧�ֲ�ѯ�����⴮�ڶ˿ڣ�
           1����ǰ�豸��̬֧�ֲ�ѯ�����⴮�ڶ˿ڡ�
ע����� ��
********************************************************/
extern int BSP_UDI_FindVcom(UDI_DEVICE_ID enVCOM);

/********************************************************
����˵���� ���ص�ǰNV���е��豸��ֵ̬���Ƿ�֧��PCSC
��������:
��������� dev_type���豸��ֵ̬��OAM��NV�ж�����

��������� �ޡ�
����ֵ��
          0: dev_type��֧��PCSC�豸��
          1��dev_type֧��PCSC�豸
********************************************************/
/*unsigned int pcsc_info_quiry(unsigned int ulDevType);*/
#define DRV_USB_PCSC_INFO_QUIRY(a)            DRV_OK


/*****************************************************************************
 �� �� ��  : pcsc_usim_int
 ��������  : ע��PCSC������պ���
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
/*extern void pcsc_usim_int(pPCSCFUNC pFunc);*/
#define DRV_PCSC_REG_CALLBACK(pFunc)


/*****************************************************************************
 �� �� ��  : pcsc_usim_ctrl_cmd
 ��������  : PCSC����ظ�����
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
/*extern unsigned long pcsc_usim_ctrl_cmd(unsigned long CmdTpye, unsigned long Result,
                                        unsigned char *Buf, unsigned long Length);*/
#define DRV_PCSC_SEND_DATA(CmdType, Result, Buffer, Length)

#if 0
/* Porting���࣬��ʱ����Ϊ�� */
#define DRV_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)    DRV_OK
#endif
extern signed int Sock_RecvCallbackRegister(unsigned char  uPortNo, pComRecv pCallback);
#define DRV_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)\
                Sock_RecvCallbackRegister(uPortNo,pCallback)

/*****************************************************************************
 �� �� ��  : pcsc_usim_ctrl_cmd
 ��������  : PCSC����ظ�����
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/

extern BSP_VOID* cacheDmaMalloc(BSP_U32  bytes);
#define DRV_CACHEDMAM_ALLOC(bytes) cacheDmaMalloc(bytes)

/*****************************************************************************
 �� �� ��  : pcsc_usim_ctrl_cmd
 ��������  : PCSC����ظ�����
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
extern BSP_S32 cacheDmaFree(BSP_VOID*  pBuf);
#define DRV_CACHEDMAM_FREE(pBuf) cacheDmaFree(pBuf)

/*****************************************************************************
 �� �� ��  : usbModemRegFastCpyFunc
 ��������  : Э��ջע���Ч���ƺ���������
 �������  : FUNCPTR srcFunc , ��Ч���ƺ���ָ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int usbModemRegFastCpyFunc
(
  USB_MODEM_COPY pCopyFunc
);
#define DRV_MODEM_REG_FAST_COPY_FUNC(pFunc) \
    usbModemRegFastCpyFunc(pFunc)

/*****************************************************************************
 �� �� ��  : Sock_Send
 ��������  : ʵ��USB����ͨ�������ݷ��͹��ܣ����ϲ�������ݵĴ���������ֱ�Ӵ�����USB�˵�����������HOST�ࡣ
 �������  : uPortNo������ʵ���š�
             pData��������ָ�롣
             uslength�������ֽ�����
 �������  : �ޡ�
 �� �� ֵ  : 0�������ɹ���
             ����ֵ������ʧ��
 ע������  ��
 1������USB R�ӿ�ģ�鴮�ڵķ��ͻ������Ĵ�С�̶�ΪUSBCOMS_MAX_BUFSIZE��8192����������ĳ��ȣ�
    �����ڵ��øú����������ݷ���ʱ�����������ݻ������ĳ���Ӧ������USBCOMS_MAX_BUFSIZE��ָ���ĳ��ȡ�
 2�����ݻ�����ָ��Ҫ��4�ֽڶ��롣
 3�����ںŶ���OMΪ1,ATΪ2,DLOADΪ2��AT��DLOAD��ͬʱ��������
 4���ýӿ���������ʽ�ӿ�,�����ݷ��ͳɹ���ŷ��ء�
*****************************************************************************/
extern VOS_INT32 Sock_Send(VOS_UINT8 ucPortNo, VOS_UINT8* pucData, VOS_UINT16 uslength);
#define DRV_COM_SEND(uPortNo,pData,uslength) Sock_Send(uPortNo,pData,uslength)

/*****************************************************************************
 �� �� ��  : UartRecvCallbackRegister
 ��������  : �ṩ�ϲ�Ӧ�ó���ע�����ݽ��ջص�����ָ���API�ӿں�����
 �������  : uPortNo������ʵ���š�
             pCallback���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int  UartRecvCallbackRegister(unsigned char  uPortNo, pUartRecv pCallback);
#define DRV_UART_RCV_CALLBACK_REGI(uPortNo,pCallback)\
                UartRecvCallbackRegister(uPortNo,pCallback)

/*****************************************************************************
 �� �� ��  : pwrctrl_wpa_pwr_up
 ��������  : RF�µ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_wpa_pwr_up(void);
#define DRV_WPA_POWERUP()

/*****************************************************************************
 �� �� ��  : pwrctrl_wpa_pwr_up
 ��������  : RF�µ磬BB����������
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_wpa_pwr_down(void);
#define DRV_WPA_POWERDOWN()

/************************************************************************
 * FUNCTION
 *       vmEnable
 * DESCRIPTION
 *       �ڴ��д��������ʹ�ܺ���
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int vmEnable(int enable);
#define DRV_VM_ENABLE(flag)   vmEnable(flag)


extern unsigned int drvSecCheck(void);
#define DRV_SEC_CHECK() drvSecCheck()

/*****************************************************************************
 �� �� ��  : vmStateSet
 ��������  : ���õ�ַ�ռ�״̬
 �������  : ��

 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ��
*****************************************************************************/
#define DRV_VM_STATESET(context, virtAdrs, len, stateMask, state)

/*****************************************************************************
 �� �� ��  : pwrctrl_gpa_pwr_down
 ��������  : RF�ϵ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_gpa_pwr_down(void);
#define DRV_GPA_POWERDOWN()


extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()

/*****************************************************************************
 �� �� ��  : hkadcBatADCRead
 ��������  : ��ȡ��ص�ѹ����ֵ
 �������  : ��
 �������  : pTemp��        ָ�����¶ȵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int hkadcBatADCRead(int* pslData);
#define DRV_GET_BATTERY_ADC(pslData) hkadcBatADCRead(pslData)

/*************************************************
*  Function:  wifi_end_athr_tcmd_init
*  Description: ����WIFI����״̬
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          x:     ����WIFI��PA״̬
*  Output:
*         N/A
*  Return:
*         ����ִ�е�״̬���ֵ��
*************************************************/
int wifi_end_athr_tcmd_init(int x);
#define WIFI_TEST_CMD_INIT(x) wifi_end_athr_tcmd_init(x)

/*****************************************************************************
 �� �� ��  : ComPnpCallbackRegister
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��USB����/�γ��ص�����ָ���API�ӿں�����
 �������  : pInsert��USB����ص�����ָ�롣
             pPullout��USB�γ��ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0�������ɹ���
             ����ֵ������ʧ�ܡ�
 ע������  ���ýӿ�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern int  ComPnpCallbackRegister(void* pInsert, void* pPullout);
#define DRV_COM_PNP_CALLBACK_REGI(pInsert, pPullout)\
                ComPnpCallbackRegister(pInsert, pPullout)

/*****************************************************************************
 �� �� ��  : drvOnLineUpdateResult
 ��������  : WebUIģ�麯��ע�ᡣ
 �������  : ��
 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ��
*****************************************************************************/
extern void drvOnLineUpdateResult(void);
#define DRV_ONLINE_UPDATE_RESULT()    drvOnLineUpdateResult()

/*****************************************************************************
 �� �� ��  : pwrctrl_gpa_pwr_up
 ��������  : RF�ϵ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_gpa_pwr_up(void);
#define DRV_GPA_POWERUP()

/*****************************************************************************
 �� �� ��  : MNTN_RecordVersionInfo
 ��������  : ����汾��Ϣ��Errlog
 �������  : ��

 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ������ָ�벻��ΪNULL
*****************************************************************************/
extern void  MNTN_RecordVersionInfo(void);

/*****************************************************************************
 �� �� ��  : usbModemRegExtFunc
 ��������  : AT�������ݻ�ܽ��źź���ע��
 �������  : FUNCPTR srcFunc , Э��ջBULK���ݽ��ջص�����
FUNCPTR statusSet, Э��ջ��Ϣͨ��״̬�仯���ݽ��ջص�����
FUNCPTR connectBrk, Э��ջ�����ص�����
FUNCPTR connectEst ��Э��ջ�����ص�����
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int usbModemRegExtFunc
(
 USB_MODEM_RECV_CALL srcFunc ,
 USB_MODEM_AT_Sig statusSet,
 USB_MODEM_IN_OUT connectBrk,
 USB_MODEM_IN_OUT connectEst
 );
#define DRV_MODEM_REG_EXT_FUNC(srcFunc,statusSet,connectBrk,connectEst)\
    usbModemRegExtFunc(srcFunc,statusSet,connectBrk,connectEst)

/*****************************************************************************
 �� �� ��  : USB_AT_SendForProtocal
 ��������  : USB �ṩ��Э��ջ���ݷ��ͽӿں���
 �������  : buffer-Ҫ������ַ���
                           Lenth---�ַ����ĳ���
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int USB_AT_SendForProtocal(unsigned char* buffer,  unsigned long length);
#define DRV_AT_SEND_FOR_PROTOCAL(buffer,length)   USB_AT_SendForProtocal(buffer,length)

/*****************************************************************************
 �� �� ��  : USB_AT_SetMode
 ��������  : �ṩ��Э��ջ�ж�ͨ���ϱ�
                           UE�������״̬��PC����
 �������  : pMscStru -pointer to MODEM_MSC_STRU
 �������  : �ޡ�
 �� �� ֵ  : ��
*****************************************************************************/
extern void USB_AT_SetMode(MODEM_MSC_STRU *pMscStru);
#define DRV_AT_SET_MODE(pMscStru)   USB_AT_SetMode(pMscStru)

/*****************************************************************************
 �� �� ��  : usb_modem_for_ps_flowctrl
 ��������  : �ṩ��Э��ջ�������ؽ����ؽӿ�
 �������  : MODEM_MSC_STRU *pMscStru
 �������  : �ޡ�
 �� �� ֵ  : ��
*****************************************************************************/
extern void usb_modem_for_ps_flowctrl(MODEM_MSC_STRU *pMscStru);
#define DRV_MODEM_FOR_PS_FLOWCTRL(pMscStru)     usb_modem_for_ps_flowctrl(pMscStru)

/*****************************************************************************
 �� �� ��  : ComRecvCallbackRegister
 ��������  : �ṩ�ϲ�Ӧ�ó���ע�ᴮ��״̬֪ͨ�ص�����ָ���API�ӿں�����
 �������  : uPortNo������ʵ���š�
             pCallback���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int ComStatusCallbackRegister(unsigned char uPortNo, pComStatusNotify pCallback);
#define DRV_COM_STATUS_CALLBACK_REGI(uPortNo,pCallback)\
                ComStatusCallbackRegister(uPortNo,pCallback)

/*****************************************************************************
 �� �� ��  : GetComStatus
 ��������  : �����ṩ�Ľӿڣ������ж�USB�豸�Ƿ��Ѿ�׼���ã����Խ������ݡ�
 �������  : no������ʵ���š�
 �������  : ��
 �� �� ֵ  : OK(0):�豸ready
             ERROR(-1):�豸û��ready
*****************************************************************************/
extern int  GetComStatus(unsigned char no);
#define DRV_GetComStatus(no) GetComStatus(no)

/*****************************************************************************
 �� �� ��  : UartSend
 ��������  : ʵ��UART����ͨ�������ݷ��͹��ܣ����ϲ�������ݵĴ���������ֱ�Ӵ�����UART�˵�����������HOST�ࡣ
 �������  : uPortNo��  ����ʵ���š�
             pData��    ������ָ�롣
             uslength�� �����ֽ�����
 �������  : �ޡ�
 �� �� ֵ  : 0�������ɹ���
             ����ֵ������ʧ�ܡ�
 ע������  ���ýӿ�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern int  UartSend (unsigned char  uPortNo, unsigned char  *pData, unsigned short  uslength);
#define DRV_UART_SEND(uPortNo,pData,uslength)    UartSend(uPortNo,pData,uslength)

/*****************************************************************************
 �� �� ��  : usb_modem_for_ps_notify
 ��������  : �ͷ��ź�����notify����
 �������  : ��
 �������  : �ޡ�
 �� �� ֵ  : ��
*****************************************************************************/
extern void usb_modem_for_ps_notify(void);
#define DRV_MODEM_FOR_PS_NOTIFY()       usb_modem_for_ps_notify()

/************************************************************************
 * FUNCTION
 *       max_freeblock_size_get
 * DESCRIPTION
 *       get memory max free block size
 * INPUTS
 *       ��
 * OUTPUTS
 *       max free block size
 *************************************************************************/
extern int max_freeblock_size_get(void);
#define DRV_GET_FREE_LOCK_SIZE() max_freeblock_size_get()

/*****************************************************************************
 �� �� ��  : getDloadVersion
 ��������  : ��ѯ��ǰ����Э��汾
 �������  : unsigned char *buf
                          int len
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
                      -1������ʧ�ܡ�
*****************************************************************************/
extern int getDloadVersion(unsigned char *buf, int len);
#define DRV_GET_DLOAD_VERSION(buf,len) getDloadVersion(buf,len)


/*****************************************************************************
 �� �� ��  : getDloadNetMode
 ��������  : ��ѯ����ģʽ
 �������  : unsigned long*netMode
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
                      -1������ʧ�ܡ�
*****************************************************************************/
extern int getDloadNetMode(unsigned long *netMode);
#define DRV_GET_DLOAD_NETMODE(netMode) getDloadNetMode (netMode)


extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()

/*****************************************************************************
 �� �� ��  : getDloadFlashInfo
 ��������  : ��ȡ����Flash��Ϣ
 �������  : DLOAD_FLASH_STRU *flashInfo
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
                      -1������ʧ�ܡ�
*****************************************************************************/
extern int getDloadFlashInfo(DLOAD_FLASH_STRU *flashInfo);
#define DRV_GET_DLOAD_FLASHINFO(flashinfo) getDloadFlashInfo (flashinfo)

/*****************************************************************************
 �� �� ��  : pmLDOOFF
 ��������  : ���ӿ����ڹر�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ1��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע�������LDO6��Ӳ�����ƣ������֧�ֶ�LDO6�Ĳ����������LDO1�رգ���ϵͳ��ػ���
*****************************************************************************/
extern void pmLDOOFF(unsigned char ucLDO);
#define DRV_PM_LDO_OFF(ucLDO)                 pmLDOOFF(ucLDO)

/*****************************************************************************
 �� �� ��  : pmLDOON
 ��������  : ���ӿ��������ô�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ2��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע���������֧�ֶ�LDO1��LDO6�Ĳ�����LDO1����ϵͳ����ʱ�Զ��򿪣�һ���ر�������ϵͳ���µ磻LDO6����Ӳ���ܽſ��ơ�
*****************************************************************************/
extern void pmLDOON(unsigned char ucLDO);
#define DRV_PM_LDO_ON(ucLDO)                  pmLDOON(ucLDO)

/************************* DMA BEGIN ****************************************/

/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �� �� ��  : BSP_EDMA_CheckChannelBusy
*
* ��������  : �ж�ͨ���Ƿ����
*
* �������  : u32Channel�����жϵ�ͨ����
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS       ͨ������
*             BSP_ERR_DMA_CHANNEL_BUSY  ͨ��æ
*             BSP_ERR_DMA_INVALID_PARA  ��������
*
* �޸ļ�¼  :2009��06��20��   ����  ����

*****************************************************************************/
extern BSP_S32 BSP_EDMA_CheckChannelBusy(BSP_U32 u32Channel);
#define DRV_EDMA_CHECK_CHANNEL_BUSY(u32Channel) BSP_EDMA_CheckChannelBusy(u32Channel)

/*****************************************************************************
* �� �� ��  : BSP_EDMA_SingleBlockStart
*
* ��������  : �������ݴ�������
*
* �������  : DMA_SINGLE_BLOCK_S stDMASingleBlock   ���鴫��ʹ�õĲ����ṹ��
*
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS    �����������
*          DMA_CHANNEL_INVALID   ����ͨ���Ŵ���
*          DMA_TRXFERSIZE_INVALID   ���봫�䳤�ȷǷ�
*          DMA_CHANNEL_BUSY         ͨ��æ
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
extern BSP_S32 BSP_EDMA_SingleBlockStart(DMA_SINGLE_BLOCK_S * stDMASingleBlock);
#define DRV_EDMA_SINGLE_BLOCK_START(stDMASingleBlock) BSP_EDMA_SingleBlockStart(stDMASingleBlock)

/*****************************************************************************
* �� �� ��  : BSP_EDMA_LliBuild
*
* ��������  : ����������
*
* �������  : BSP_U32 ulChan        ͨ����
*             DMA_LLI_S *pFirstLLI  ��Դ����ĵ�һ���ڵ�ָ��
* �������  : ��
* �� �� ֵ  : BSP_VOID *  ָ��ײ㽨���õĴ��������ͷ�ڵ��ָ��
*
* �޸ļ�¼  :2009��7��24��   ����  ����

*****************************************************************************/
extern BSP_VOID * BSP_EDMA_LliBuild(BSP_U32 ulChan, DMA_LLI_S *pFirstLLI);
#define DRV_EDMA_LLI_BUILD(ulChan,pFirstLLI) BSP_EDMA_LliBuild(ulChan,pFirstLLI)

/*****************************************************************************
* �� �� ��  : BSP_EDMA_LliStart
*
* ��������  : �������ݴ�������ר�ú���
*
* �������  : BSP_U32 ulChan        ͨ����
*             BSP_VOID *pu32Head��   ����BSP_DMA_LliBuild��õĴ���������ͷָ��
* �������  : ��
* �� �� ֵ  : DMA_SUCCESS    �����������
*          DMA_LLIHEAD_ERROR   ���������ͷ����
*          DMA_CHANNEL_INVALID   ����ͨ���Ŵ���
*          DMA_ERROR    ͨ�������л���DMAδ��ȷ��ʼ��
*
* �޸ļ�¼  :2008��12��26��   ����  ����

*****************************************************************************/
extern BSP_U32 BSP_EDMA_LliStart(DMA_CHN_PARA_S * stChnPara, BSP_VOID *pu32Head);
#define DRV_EDMA_LLI_START(stChnPara,pu32Head) BSP_EDMA_LliStart(stChnPara,pu32Head)

/*****************************************************************************
* �� �� ��  : BSP_EDMA_GetRegistValue
*
* ��������  : ��ȡ�쳣ʱ���EDMACģ��Ĵ�����ֵ
*
* �������  : BSP_VOID
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*
*****************************************************************************/
extern BSP_VOID BSP_EDMA_GetRegistValue(BSP_VOID);
#define DRV_EDMA_GET_REGIST_VALUE(BSP_VOID) BSP_EDMA_GetRegistValue(BSP_VOID)

/*************************DMA END************************/

/*****************************************************************************
 �� �� ��  : pwrctrl_abb_powerdown
 ��������  : ABB�µ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_abb_powerdown(void);
#define DRV_ABB_POWERDOWN()                       pwrctrl_abb_powerdown()

/*****************************************************************************
 �� �� ��  : pwrctrl_abb_powerup
 ��������  : ABB�ϵ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_abb_powerup(void);
#define DRV_ABB_POWERUP()                       pwrctrl_abb_powerup()

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_GetTemp
 ��������  : ��ȡOLED����ء�GPA��WPA��SIM����DCXO���¶ȡ�
 �������  : enModule:PWC_TEMP_PROTECT_E
             hkAdcTable:��ѹ�¶Ȼ����
 �������  : pslData:�洢�ĵ�ѹת��Ϊ���¶�ֵ
 �� �� ֵ  : HKADC_OK/HKADC_ERROR ��
*****************************************************************************/
#if defined (VERSION_V3R2)
extern BSP_S32 BSP_PWRCTRL_GetTemp(PWC_TEMP_PROTECT_E enModule, BSP_U16 *hkAdcTable,BSP_S32 *pslData);
#define DRV_PWRCTRL_GET_TEMP(enModule,hkAdcTable,pslData) BSP_PWRCTRL_GetTemp(enModule,hkAdcTable,pslData)
#else
#define DRV_PWRCTRL_GET_TEMP(enModule,hkAdcTable,pslData) DRV_OK
#endif

/********************************************************************************************************
 �� �� ��  : getHwVersionIndex
 ��������  : ��ȡ��HKADC��ȡ��Ӳ��ID����ƴװ���Ӳ������ֵ
 �������  : ��
 �������  : Ӳ��ID������ֵ

 �� �� ֵ  : ��-1:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int getHwVersionIndex(void);
#define DRV_GET_HW_VERSION_INDEX()       getHwVersionIndex()

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PwrUp
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB���ϵ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#if defined (VERSION_V3R2)
extern BSP_U32 BSP_PWRCTRL_PwrUp (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
#define DRV_PWRCTRL_PWRUP(enCommMode,enCommModule) BSP_PWRCTRL_PwrUp(enCommMode,enCommModule)
#else
#define DRV_PWRCTRL_PWRUP(enCommMode,enCommModule) DRV_OK
#endif
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PwrDown
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB���µ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#if defined (VERSION_V3R2)
extern BSP_U32 BSP_PWRCTRL_PwrDown (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
#define DRV_PWRCTRL_PWRDOWN(enCommMode,enCommModule) BSP_PWRCTRL_PwrDown(enCommMode,enCommModule)
#else
#define DRV_PWRCTRL_PWRDOWN(enCommMode,enCommModule) DRV_OK
#endif
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PllEnable
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#if defined (VERSION_V3R2)
extern BSP_U32 BSP_PWRCTRL_PllEnable (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
#define  DRV_PWRCTRL_PLL_ENABLE(enCommMode,enCommModule) BSP_PWRCTRL_PllEnable(enCommMode,enCommModule)
#else
#define  DRV_PWRCTRL_PLL_ENABLE(enCommMode,enCommModule) DRV_OK
#endif
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PllDisable
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLȥʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
#if defined (VERSION_V3R2)
extern BSP_U32 BSP_PWRCTRL_PllDisable (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
#define  DRV_PWRCTRL_PLL_DISABLE(enCommMode,enCommModule) BSP_PWRCTRL_PllDisable(enCommMode,enCommModule)
#else
#define  DRV_PWRCTRL_PLL_DISABLE(enCommMode,enCommModule) DRV_OK
#endif

typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
/*****************************************************************************
* �� �� ��  : BSP_MspProcReg
*
* ��������  : DRV�ṩ��OM��ע�ắ��
*
* �������  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*
*****************************************************************************/
#if defined (VERSION_V3R2)
extern void BSP_MspProcReg(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);
#define DRV_MSP_PROC_REG(eFuncID, pFunc)  BSP_MspProcReg(eFuncID, pFunc)
#else
extern void BSP_MspProcReg(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);
#define DRV_MSP_PROC_REG(eFuncID, pFunc)
#endif

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_SleepCallbackRegister
 ��������  : ע��PWC����������ʹ��
 �������  : ��ע��ĺ���
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
#if defined (VERSION_V3R2)
extern int BSP_PWRCTRL_SleepCallbackRegister(PWC_SLEEP_CALLBACK_STRU pCallback);
#define DRV_PWRCTRL_SLEEP_CALLBACK_REG(Callback)  BSP_PWRCTRL_SleepCallbackRegister(Callback)
#else
#define DRV_PWRCTRL_SLEEP_CALLBACK_REG(Callback)  DRV_OK
#endif

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_AhbBakAddrAlloc
 ��������  : arm���µ繦�ܣ���Ҫ����ahb���ݣ��ýӿ��������ݱ����ַ�ͳ���
 �������  : length     ��������ռ��С��ָ��
 �������  : ��
 �� �� ֵ  : ����ռ�ĵ�ַ ��
*****************************************************************************/
#if defined (VERSION_V3R2)
extern void * BSP_PWRCTRL_AhbBakAddrAlloc(unsigned int * length);
#define DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC(length) BSP_PWRCTRL_AhbBakAddrAlloc(length)
#else
#define DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC(length) DRV_OK
#endif



extern BSP_S32 BSP_MNTN_GetBattState(void);
#define DRV_MNTN_GET_BATT_STATE() BSP_MNTN_GetBattState()

/* Modified by z40661 for PC����, 2012-02-25 begin */

typedef  unsigned long OSM_WDOG_ID;
typedef enum tagSYNC_MODULE_EX_E
{
    SYNC_MODULE_MEM     = 0,
    SYNC_MODULE_NANDC,
    SYNC_MODULE_PMU,
    SYNC_MODULE_SOCP,
    SYNC_MODULE_DMA,
    SYNC_MODULE_NV,
    SYNC_MODULE_YAFFS,
    SYNC_MODULE_MSP,
    SYNC_MODULE_BUTT
}SYNC_MODULE_E;
/* Modified by z40661 for PC����, 2012-02-25 end */

/*****************************************************************************
*  Function:  drv_get_local_usr_connect_status
*  Description: ���ص�ǰ�Ƿ���USB���ӻ���WIFI�û�����
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*  Output:
*  Return:
*         1 : ��
*         0 : ��
*************************************************/
extern unsigned long  drv_get_local_usr_connect_status(void);
#define DRV_AT_GET_USER_EXIST_FLAG() drv_get_local_usr_connect_status()

/* Added by l60609 for B060 Project, 2012-2-20, Begin   */

void pwrctrl_wifi_lowpower_enter(void);
#define WIFI_POWER_OFF()  pwrctrl_wifi_lowpower_enter()
extern BSP_VOID oledPwrOff(BSP_VOID);

extern void BSP_PWRCTRL_UsbLowPowerEnter(void);

#define DRV_PWRCTRL_USB_LOWPOWER_ENTER() BSP_PWRCTRL_UsbLowPowerEnter()

/* Added by l60609 for B060 Project, 2012-2-20, End   */

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_DeepSleepForever
 ��������  : AARM CARM �µ�ӿ�
 �������  : None
 �������  : None
 �� �� ֵ  : None

*****************************************************************************/
extern void BSP_PWRCTRL_DeepSleepForever(void );
#define DRV_PWRCTRL_DEEPSLEEP_FOREVER()  BSP_PWRCTRL_DeepSleepForever()

/*****************************************************************
Function: wifi_get_status
Description:
    get wifi current mode
Input:
    N/A
Output:
    N/A
Return:
    0: wifi is off
    1: wifi is in normal mode
    2: wifi is in tcmd mode
*******************************************************************/

extern int wifi_get_status(void);
#define WIFI_GET_STATUS() wifi_get_status()

/*****************************************************************
Function: wifi_get_rx_packet_report
Description:
    get result of rx ucast&mcast packets
Input:
    N/A
Output:
     ucast,mcast
Return:
    N/A
*******************************************************************/
extern void  wifi_get_rx_packet_report(unsigned int *ucastPkts, unsigned int *mcastPkts);
#define WIFI_GET_RX_PACKET_REPORT(ucastPkts,mcastPkts)  wifi_get_rx_packet_report(ucastPkts,mcastPkts)

/*****************************************************************
Function: wifi_power_off
Description:
    shutdown wifi
Input:
    N/A
Output:
    N/A
Return:
    0: execute ok
    1: execute failed
*******************************************************************/
int wifi_power_off(void);
#define WIFI_POWER_SHUTDOWN()  wifi_power_off()

/*************************************************
*  Function:  wifi_athtestcmd
*  Description: WIFI Control API
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          cmdStr:     ����WIFI����������
*  Output:
*         N/A
*  Return:
*         ����ִ�е�״̬���ֵ��
*************************************************/
void wifi_athtestcmd(char * cmdStr);
#define WIFI_TEST_CMD(cmdStr) wifi_athtestcmd(cmdStr)

/***********************************************************************************
 Function:          wifi_get_pa_curMode
 Description:      get the currrent PA mode of the wifi chip
 Calls:
 Input:              NA
 Output:            NA
 Return:            0  (WIFI_ONLY_PA_MODE) WIFI chip is in PA mode
                        1 (WIFI_ONLY_NOPA_MODE) WIFI chip is in no PA mode
                      -1: wifi chip is in abnormal mode
 ************************************************************************************/

extern int wifi_get_pa_curMode(void);
#define WIFI_GET_PA_CUR_MODE()  wifi_get_pa_curMode()

/***********************************************************************************
 Function:          wifi_get_pa_mode
 Description:      returen the support PA mode of wifi chip
 Calls:
 Input:              NA
 Output:            NA
 Return:            0  (WIFI_ONLY_PA_MODE) WIFI suppport only PA mode
                        1 (WIFI_ONLY_NOPA_MODE) WIFI suppport only no PA mode
                        2 (WIFI_PA_NOPA_MODE) WIFI suppport both PA &  no PA mode
                      -1: failed
 ************************************************************************************/

extern int wifi_get_pa_mode(void);
#define WIFI_GET_PA_MODE()  wifi_get_pa_mode()


/***********************************************************************************
 Function:          wifi_set_pa_mode
 Description:      set the PA mode of wifi chip
 Calls:
 Input:              0  (WIFI_ONLY_PA_MODE) WIFI suppport only PA mode
                        1 (WIFI_ONLY_NOPA_MODE) WIFI suppport only no PA mode
                        2 (WIFI_PA_NOPA_MODE) WIFI suppport both PA &  no PA mode
 Output:            NA
 Return:
              0: success
             -1: failed
 ************************************************************************************/

extern int wifi_set_pa_mode(int wifiPaMode);
#define WIFI_SET_PA_MODE(wifiPaMode)  wifi_set_pa_mode(wifiPaMode)

/*****************************************************************
Function: wifi_power_on
Description:
    start wifi
Input:
    N/A
Output:
    N/A
Return:
    0: execute ok
    1: execute failed
*******************************************************************/
int wifi_power_on();
#define WIFI_POWER_START(type)  wifi_power_on()


extern BSP_S32  BSP_StartModeGet(void);
#define DRV_START_MODEGET() BSP_StartModeGet()

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_GetCpuLoad
 ��������  : arm cpuռ���ʲ�ѯ����
 �������  : ��
 �������  : ulAcpuLoad:Acpuռ���ʵ�ַ.
             ulCcpuLoad:Ccpuռ���ʵ�ַ.
 �� �� ֵ  : 0/1 ��
*****************************************************************************/
extern unsigned int BSP_PWRCTRL_GetCpuLoad(unsigned int *ulAcpuLoad,unsigned int *ulCcpuLoad);
#define DRV_PWRCTRL_GetCpuLoad(ulAcpuLoad,ulCcpuLoad) BSP_PWRCTRL_GetCpuLoad(ulAcpuLoad,ulCcpuLoad)

/* Modified by z40661 for PC����, 2012-02-25 end */

/*****************************************************************************
*  Function:  drv_get_local_usr_connect_status
*  Description: ���ص�ǰ�Ƿ���USB���ӻ���WIFI�û�����
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*  Output:
*  Return:
*         1 : ��
*         0 : ��
*************************************************/
extern unsigned long  drv_get_local_usr_connect_status(void);
#define DRV_AT_GET_USER_EXIST_FLAG() drv_get_local_usr_connect_status()



/******************************************************************************
  ������:       BSP_S32 nand_get_bad_block (BSP_U32 *len, BSP_U32 **ppBadBlock)
  ��������:     ��ѯ����NAND������FLASH ����
  �������:     ��
  �������:     pNum       : ���ػ������
                ppBadBlock ������ָ�룬�������л����index����
  ����ֵ:       0    : ��ѯ�ɹ�
                ���� : ��ѯʧ��
*******************************************************************************/
extern BSP_S32 nand_get_bad_block (BSP_U32 *pNum, BSP_U32 **ppBadBlock);
#define NAND_GET_BAD_BLOCK(pNum, ppBadBlock) nand_get_bad_block(pNum, ppBadBlock)

/******************************************************************************
*
  ������:       BSP_VOID  nand_free_bad_block_mem(BSP_U32* pBadBlock)
  ��������:     ͨ��nand_get_bad_block�ӿ�����Ļ����ڴ��ɵ������룬��Э��ջ����
                �ýӿ��ͷš�
  �������:     pBadBlock
  �������:     ��
  ����ֵ:       BSP_VOID
*******************************************************************************/
extern BSP_VOID  nand_free_bad_block_mem(BSP_U32* pBadBlock);
#define NAND_FREE_BAD_BLOCK_MEM(pBadBlock)  nand_free_bad_block_mem(pBadBlock)


#define NAND_MFU_NAME_MAX_LEN    16
#define NAND_DEV_SPEC_MAX_LEN    32

typedef struct
{
    BSP_U32           MufId;                                         /* ����ID */
    BSP_U8            aucMufName[NAND_MFU_NAME_MAX_LEN];             /* ���������ַ��� */
    BSP_U32           DevId;                                         /* �豸ID */
    BSP_U8            aucDevSpec[NAND_DEV_SPEC_MAX_LEN];             /* �豸����ַ��� */
}NAND_DEV_INFO_S;

/******************************************************************************
  ������:       BSP_S32 nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo)
  ��������:     ��ѯNAND�豸�����Ϣ����������ID���������ơ��豸ID���豸���
  �������:     ��
  �������:     pNandDevInfo    �洢NAND�豸�����Ϣ�Ľṹ��
  ����ֵ:       0    : ��ѯ�ɹ�
                ���� : ��ѯʧ��
*******************************************************************************/
extern BSP_S32 nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo);
#define NAND_GET_DEV_INFO(pNandDevInfo) nand_get_dev_info(pNandDevInfo)

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_signal_set
 ��������  : ����BALONG��K3�Խ�ʱUSBͨ���л�GPIO���ſ���
 �������  : ��š����źź�ֵ
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_signal_set(UINT8 ucGroup, UINT8 ucPin, UINT8 ucValue);
#define DRV_GPIO_SET(group, pin, value) USB_otg_switch_signal_set(group, pin, value)

#define DRV_GPIO_USB_SWITCH     200
#define DRV_GPIO_HIGH           1
#define DRV_GPIO_LOW            0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_set
 ��������  : ����BALONG��K3�Խ�ʱMODEM�࿪����ر�USB PHY
 �������  : ������ر�
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_set(UINT8 ucValue);
#define DRV_USB_PHY_SWITCH_SET(value) USB_otg_switch_set(value)

#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2

#define USB_SWITCH_ON       1
#define USB_SWITCH_OFF      0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_get
 ��������  : ����BALONG��K3�Խ�ʱMODEM��USB PHY״̬��ѯ
 �������  : ��
 �������  : ����USB PHY����״̬

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_get(UINT8 *pucValue);
#define DRV_USB_PHY_SWITCH_GET(value) USB_otg_switch_get(value)

/*************************��ѯģ���Ƿ�֧�� START**********************/
/*����DrvInterface.c��ʱ����ɾ����ѯģ�飬DrvInterface.c������֧��*/
/* ��ǰ�汾�Ƿ�֧��ĳ��ģ�� */
typedef enum tagBSP_MODULE_SUPPORT_E
{
    BSP_MODULE_SUPPORT     = 0,
    BSP_MODULE_UNSUPPORT   = 1,
    BSP_MODULE_SUPPORT_BUTTOM
}BSP_MODULE_SUPPORT_E;

/* ��ѯ��ģ������ */

/* ��ѯ��ģ������ */
typedef enum tagBSP_MODULE_TYPE_E
{
    BSP_MODULE_TYPE_SD = 0x0,
    BSP_MODULE_TYPE_CHARGE,
    BSP_MODULE_TYPE_WIFI,
    BSP_MODULE_TYPE_OLED,
    BSP_MODULE_TYPE_HIFI,
    BSP_MODULE_TYPE_POWER_ON_OFF,
    BSP_MODULE_TYPE_HSIC,
    BSP_MODULE_TYPE_HSIC_NCM,
    BSP_MODULE_TYPE_LOCALFLASH,
    BSP_MODULE_TYPE_BUTTOM
}BSP_MODULE_TYPE_E;

/*****************************************************************************
 �� �� ��  : BSP_CheckModuleSupport
 ��������  : ��ѯģ���Ƿ�֧��
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 �������  : ��
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
extern BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType);

#define DRV_USB_HSIC_SUPPORT_NCM()    BSP_CheckModuleSupport(BSP_MODULE_TYPE_HSIC_NCM)

#define DRV_GET_LOCAL_FLASH_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_LOCALFLASH)

#define DRV_GET_BATTERY_SUPPORT()   BSP_CheckModuleSupport(BSP_MODULE_TYPE_CHARGE)

#define DRV_GET_WIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_WIFI)

#define DRV_GET_SD_SUPPORT()        BSP_CheckModuleSupport(BSP_MODULE_TYPE_SD)

#define DRV_GET_OLED_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_OLED)

#define DRV_GET_HIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HIFI)

#define DRV_GET_HSIC_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HSIC)

/*************************��ѯģ���Ƿ�֧�� END************************/




/********************************�ڴ���� start*******************************/
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
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
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
    BSP_AXI_SECT_TYPE_TEMP_PROTECT,
    BSP_AXI_SECT_TYPE_ONOFF,
    BSP_AXI_SECT_TYPE_DICC,
    BSP_AXI_SECT_TYPE_HIFI,
    BSP_AXI_SECT_TYPE_PTABLE,
    BSP_AXI_SECT_TYPE_RESERVE,
    BSP_AXI_SECT_TYPE_DLOAD_AUTOINSTALL,
    BSP_AXI_SECT_TYPE_DLOAD,
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
    BSP_U32                ulSectVirtAddr;
    BSP_U32                ulSectPhysAddr;
    BSP_U32                ulSectSize;
}BSP_DDR_SECT_INFO;


/* AXI�ڴ�ε���ϸ��Ϣ */
typedef struct tagBSP_AXI_SECT_INFO
{
    BSP_AXI_SECT_TYPE_E    enSectType;
    BSP_U32                ulSectVirtAddr;
    BSP_U32                ulSectPhysAddr;
    BSP_U32                ulSectSize;
}BSP_AXI_SECT_INFO;

/*************************IP����ַ���жϺŲ�ѯ START******************/

/* ����������Ҫ��ѯ��IP���� */
typedef enum tagBSP_IP_TYPE_E
{
    BSP_IP_TYPE_SOCP = 0x0,
    BSP_IP_TYPE_CICOM0,
    BSP_IP_TYPE_CICOM1,
    BSP_IP_TYPE_HDLC,
    BSP_IP_TYPE_BBPMASTER,
    BSP_IP_TYPE_ZSP_ITCM,
    BSP_IP_TYPE_ZSP_DTCM,
    BSP_IP_TYPE_AHB,
    BSP_IP_TYPE_WBBP,
    BSP_IP_TYPE_WBBP_DRX,
    BSP_IP_TYPE_GBBP,
    BSP_IP_TYPE_GBBP_DRX,
    BSP_IP_TYPE_GBBP1,
    BSP_IP_TYPE_GBBP1_DRX,
    BSP_IP_TYPE_ZSPDMA,
    BSP_IP_TYPE_SYSCTRL,
    BSP_IP_TYPE_CTU,

    BSP_IP_TYPE_BUTTOM
}BSP_IP_TYPE_E;

/*****************************************************************************
 �� �� ��  : BSP_GetIPBaseAddr
 ��������  : IP����ַ��ѯ
 �������  : enIPType: ��Ҫ��ѯ��IP����
 �������  : ��
 ����ֵ    ����ѯ����IP����ַ
*****************************************************************************/
BSP_U32 BSP_GetIPBaseAddr(BSP_IP_TYPE_E enIPType);
#define DRV_GET_IP_BASE_ADDR(enIPType)  BSP_GetIPBaseAddr(enIPType)

/* ��Ҫ��ѯ���ж����� */
typedef enum tagBSP_INT_TYPE_E
{
    BSP_INT_TYPE_RTC = 0,
    BSP_INT_TYPE_WDT,
    BSP_INT_TYPE_USBOTG,
    BSP_INT_TYPE_UICC,
    BSP_INT_TYPE_IPF_C,
    BSP_INT_TYPE_IPF_A,
    BSP_INT_TYPE_SOCP_A,
    BSP_INT_TYPE_SOCP_C,
    BSP_INT_TYPE_CICOM_UL,
    BSP_INT_TYPE_CICOM_DL,
    BSP_INT_TYPE_HDLC_DEF,
    BSP_INT_TYPE_HDLC_FRM,
    #if 1 //monan:not used yet
    BSP_INT_TYPE_BBPMASTER,
    BSP_INT_TYPE_GBBP,          /*G_BBP_INT_LEVEL*/
    BSP_INT_TYPE_GBBP_AWAKE,    /*G_BBP_AWAKE_INT_LEVEL*/
    BSP_INT_TYPE_WBBP_0MS,      /*W_BBP_0MS_INT_LEVEL*/
    BSP_INT_TYPE_WBBP_AWAKE,    /*W_BBP_AWAKE_INT_LEVEL*/
    BSP_INT_TYPE_WBBP_SWITCH,   /*W_BBP_CLOCK_SWITCH_INT_LEVEL*/
    BSP_INT_TYPE_INT_OSRTC,     /*RTC_DUAL_TIMER_INT_LEVEL*/
    BSP_INT_TYPE_INT_SIMI,      /*SOC_SMIM_INT_LEVEL*/
    BSP_INT_TYPE_INT_ZSP_DOG,   /*ZSP_WDG_INT_LEVEL*/
    BSP_INT_TYPE_INT_HIFI_DOG,  /*HIFI_WDG_INT_LEVEL*/
    #endif

    BSP_INT_TYPE_ODTOA_INT12,     	/*Ŀ�궨λ�ж�*/
    BSP_INT_TYPE_CTU_INT_W,       	/*CTU������Wģ��ص��ж�(W����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
    BSP_INT_TYPE_CTU_INT_G,       	/*CTU������Gģ��ص��ж�(G����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
    BSP_INT_TYPE_CTU_INT_LTE,     	/*CTU������LTEģ��ص��ж�(LTE����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
    BSP_INT_TYPE_CTU_INT_TDS,     	/*CTU������TDSģ��ص��ж�(TDS����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
    BSP_INT_TYPE_WBBP_BBPMST_INTR,  /*����BBP Master�ϱ��ж�*/
    BSP_INT_TYPE_WBBP_MULTI_SEARCH_INTR, /*�ྶ���������ж�*/
    BSP_INT_TYPE_WBBP_CARD2_TIME_INTR,   /*card2��ʱ�ж�*/
    BSP_INT_TYPE_WBBP_CARD1_TIME_INTR,   /*card1��ʱ�ж�*/
    BSP_INT_TYPE_WBBP_DECODE_INTR,       /*���������ϱ��ж�*/
    BSP_INT_TYPE_WBBP_RAKE_INTR,         /*Rake����ϱ��ж�*/
    BSP_INT_TYPE_WBBP_SEARCH_INTR,       /*С�������ж�*/
    BSP_INT_TYPE_WBBP_CARD2_0MS_INTR,    /*Card2 0ms �ж�*/
    BSP_INT_TYPE_WBBP_CLK_SW_INTR,       /*ʱ���л��ж�*/
    BSP_INT_TYPE_WDRX_SLP_AWK_SW_INTR,   /*˯�ߡ������ж�*/
    BSP_INT_TYPE_WBBP_CARDL_0MS_INTR,    /*card1 0ms�ж�*/
    BSP_INT_TYPE_GBBP_GSML_DRX_INTRL,    /*ARM_32Kʱ�����жϣ������ǵ�������*/
    BSP_INT_TYPE_GBBP_GSML_NODRX_INTRL,  /*ARM_104Mʱ�����жϣ�����������ǵ�������*/
    BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR,/*PHY_32Kʱ�����ж�(�����ǵ�����)*/
    BSP_INT_TYPE_GBBP_GSML_NODRX_INTR,   /*PHY_104Mʱ�����ж�(����������ǵ�����)*/
    BSP_INT_TYPE_BUTTOM
}BSP_INT_TYPE_E;

#if defined (VERSION_V3R2)
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    BSP_SCIFuncRegister(omSciFuncPtr)
#else
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    DRV_OK
#endif
/* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
extern unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
extern unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
#define DRV_PWRCTRL_STANDBYSTATEACPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateAcpu(ulStandbyTime, ulSwitchTime)
#define DRV_PWRCTRL_STANDBYSTATECCPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateCcpu(ulStandbyTime, ulSwitchTime)
/*****************************************************************************
* �� �� ��  : BSP_GetProductDloadName
*
* ��������  : ��ȡ��Ʒ���ذ汾���ƣ�һ�������ݴ��ж��Ƿ���������
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��Ʒ���ذ汾�����ַ���ָ��
*
* �޸ļ�¼  : 2011-3-30 wuzechun creat
*
*****************************************************************************/
extern BSP_S32 BSP_GetProductDloadName(char * pProductDloadName, unsigned int ulLength);

/*****************************************************************************
* �� �� ��  : BSP_GetProductInnerName
*
* ��������  : ��ȡ�ڲ���Ʒ����
*
* �������  : char* pProductIdInter,�ַ���ָ��
*                             BSP_U32 ulLength,����������
* �������  : ��
*
 �� �� ֵ  : 0����ȷ����0: ʧ��
*
* �޸ļ�¼  : 2011-3-29 wuzechun creat
*
*****************************************************************************/
extern BSP_S32 BSP_GetProductInnerName (char * pProductIdInter, unsigned int ulLength);

/*****************************************************************************
* �� �� ��  : BSP_GetProductName
*
* ��������  : ��ȡ��Ʒ����
*
* �������  : char* pProductName,�ַ���ָ�룬��֤��С��32�ֽ�
*                             BSP_U32 ulLength,����������
* �������  : ��
*
 �� �� ֵ  : 0����ȷ����0: ʧ��
*
* �޸ļ�¼  : 2011-3-30 wuzechun creat
*
*****************************************************************************/
extern BSP_S32 BSP_GetProductName (char * pProductName, unsigned int ulLength);

/*****************************************************************************
* �� �� ��  : BSP_GetSupportBands
*
* ��������  : ��ȡ֧�ֵ�Ƶ��
*
* �������  :
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
extern BSP_U32 BSP_GetSupportBands( BSP_VOID );

/*****************************************************************************
* �� �� ��  : BSP_HwGetHwVersion
*
* ��������  : ��ȡӲ���汾����
*
* �������  : BSP_CHAR* pHwVersion,�ַ���ָ�룬��֤��С��32�ֽ�
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011-3-29 wuzechun creat
*
*****************************************************************************/
extern BSP_S32 BSP_HwGetHwVersion (char* pFullHwVersion, BSP_U32 ulLength);

/*****************************************************************************
��������   BSP_USB_PortTypeValidCheck
��������:  �ṩ���ϲ��ѯ�豸�˿���̬���úϷ��Խӿ�
           1���˿�Ϊ��֧�����ͣ�2������PCUI�ڣ�3�����ظ��˿ڣ�4���˵���������16��
           5����һ���豸��ΪMASS��
��������� pucPortType  �˿���̬����
           ulPortNum    �˿���̬����
����ֵ��   0:    �˿���̬�Ϸ�
           �������˿���̬�Ƿ�
*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum);
#define DRV_USB_PORT_TYPE_VALID_CHECK(pucPortType, ulPortNum)  \
                    BSP_USB_PortTypeValidCheck(pucPortType, ulPortNum)

/*****************************************************************************
��������   BSP_USB_GetAvailabePortType
��������:  �ṩ���ϲ��ѯ��ǰ�豸֧�ֶ˿���̬�б�ӿ�
��������� ulPortMax    Э��ջ֧�����˿���̬����
�������:  pucPortType  ֧�ֵĶ˿���̬�б�
           pulPortNum   ֧�ֵĶ˿���̬����
����ֵ��   0:    ��ȡ�˿���̬�б�ɹ�
           ��������ȡ�˿���̬�б�ʧ��
*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType,
                            unsigned long *pulPortNum, unsigned long ulPortMax);
#define DRV_USB_GET_AVAILABLE_PORT_TYPE(pucPortType, pulPortNum, ulPortMax)  \
                BSP_USB_GetAvailabePortType(pucPortType, pulPortNum, ulPortMax)
/*****************************************************************************
 �� �� ��  : DRV_CHG_STATE_GET
 ��������  :��ȡ�����־
 �� �� ֵ      : 1:��Ҫ����
			      0:����Ҫ��
 �������  : ��
 ����ֵ��    ��
*****************************************************************************/
extern unsigned int  DRV_CHG_STATE_GET(void);

/*****************************************************************************
 �� �� ��  : DRV_CHG_BATT_SPLY
 ��������  :��ʼ����״̬
 �������  :
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
extern int DRV_CHG_BATT_SPLY(void);
/* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

/*****************************************************************************
 �� �� ��  : BSP_AXI_GetSectInfo
 ��������  : AXI�ڴ�β�ѯ�ӿ�
 �������  : enSectType: ��Ҫ��ѯ���ڴ������
 �������  : pstSectInfo:  ��ѯ�����ڴ����Ϣ
 ����ֵ    ��BSP_OK/BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_AXI_GetSectInfo(BSP_AXI_SECT_TYPE_E enSectType, BSP_AXI_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_AXI_ADDR(enSectType, pstSectInfo) BSP_AXI_GetSectInfo(enSectType, pstSectInfo)

/*for create_crypto_key,hash algorithm enum*/
typedef enum
{
    CREATE_CRYPTO_KEY_ALGORITHM_MD5 = 0x0,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA1,
    CREATE_CRYPTO_KEY_ALGORITHM_MAX,
}CREATE_CRYPTO_KEY_ALGORITHM;

/*for crypto_hash,hash algorithm enum*/
typedef enum
{
	CRYPTO_ALGORITHM_MD5 = 0x0,
	CRYPTO_ALGORITHM_SHA1,
	CRYPTO_ALGORITHM_SHA256,
	CRYPTO_ALGORITHM_MAX
}CRYPTO_HASH_ALGORITHM;

/*for crypto_encrypt,aes algorithm enum*/
typedef enum
{
    CRYPTO_ENCRYPT_ALGORITHM_AES_ECB = 0x0,
    CRYPTO_ENCRYPT_ALGORITHM_MAX,
}CRYPTO_ENCRYPT_ALGORITHM;

typedef enum tagPWC_COMM_MODEM_E
{
	PWC_COMM_MODEM_0 = 0,
	PWC_COMM_MODEM_1 = 1,
	PWC_COMM_MODEM_BUTT
}PWC_COMM_MODEM_E;

/*****************************************************************************
* �� �� ��  : create_crypto_key
*
* ��������  : ʹ����������ݺ�HUK��������Կ��
*��ǰ֧��MD5����SHA-1�㷨��������Կ�ķ�������HUK������
*����������������ΪMD5��SHA-1�㷨�����룬������HASHֵ
*
* �������  : data������������������������Կ�����ݡ�
*                           len���������������������ݳ���(�ֽ�)
*                           algorithm��������������ڲ�����Կ���㷨��
*                           key�����������������ɵ���Կ��
*            ע�⣺�䳤�ȱ��벻С��16�ֽڡ���Ϊ��ԿΪ16�ֽڡ�
*                           klen�����������������Ϊ������������key��
*            �������ĳ��ȡ���Ϊ���������������ɵ���Կ�ĳ��ȡ�(�ֽ�)
* �������  :
*
* �� �� ֵ  :  BSP_OK--���ܳɹ�;BSP_ERROR--����ʧ��
*
* ����˵��  :�ڴ��ɵ���������
*
*****************************************************************************/
int create_crypto_key(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM algorithm, char *key, int *klen);
#define CREATE_CRYPTO_KEY(data,len,algorithm,key,klen)  create_crypto_key(data,len,algorithm,key,klen)

/*****************************************************************************
* �� �� ��  : crypto_hash
*
* ��������  : ������������ݵ�HASHֵ��
*                           ��ǰ֧��MD5����SHA-1�㷨�����HASHֵ������16�ֽ�
*
* �������  : data��������������������Ҫ����HASHֵ�����ݡ�
*                           len���������������������ݳ���(�ֽ�)
*                           algorithm�����������HASH�㷨��
*                           hash�����������������ɵ�HASHֵ��
*                           hlen�����������������Ϊ������������HASHֵ�Ļ������ĳ��ȡ�(�ֽ�)
*                           ��Ϊ���������������ɵ�HASHֵ�ĳ��ȡ�
* �������  :
*
* �� �� ֵ  : BSP_OK--���ܳɹ�;BSP_ERROR--����ʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_hash(char *data, int len, CRYPTO_HASH_ALGORITHM algorithm, char *hash, int *hlen);
#define CRYPTO_HASH(data,len,algorithm,hash,hlen)  crypto_hash(data,len,algorithm,hash,hlen)

/*****************************************************************************
* �� �� ��  : crypto_encrypt
*
* ��������  : ʹ��ָ������Կ��ָ�����㷨����������ݼ��ܣ�������ܺ�����ݡ�
                             ��ǰ֧��AES-ECB�㷨��
*
* �������  : data����������������Ҫ���ܵ����ݡ�
*                           len���������������������ݳ���(�ֽ�)
*                           algorithm�����������HASH�㷨��
*                           key�������������ż�����Կ��
*                           klen�����������key�ĳ��ȡ�(�ֽ�)
*                           cipher_data�������������ż��ܺ�����ݡ�
*                           cipher_len�����������������Ϊ���������������ĵĻ������ĳ��ȡ�(�ֽ�)
*               ��Ϊ���������������ɵ����ĵĳ��ȡ�
* �������  :
*
* �� �� ֵ  :  BSP_OK--���ܳɹ�;BSP_ERROR--����ʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_encrypt (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM algorithm, char *key, int klen, char *cipher_data, int *cipher_len);
#define CRYPTO_ENCRYPT(data,len,algorithm,key,klen,cipher_data,cipher_len)  \
crypto_encrypt(data,len,algorithm,key,klen,cipher_data,cipher_len)

/*****************************************************************************
* �� �� ��  : crypto_rsa_encrypt
*
* ��������  : ʹ�ñ�����NV�еĸ�����RSA��Կ����ȡʱ��Ҫͬ������ǩ����֤��
*           ����������ݼ��ܣ�������ܺ�����ݡ�
* �������  : data����������������Ҫ���ܵ����ݡ�
*                           len���������������������ݳ���(�ֽ�)
*                           rsa_key:RSA��Կ
*                           rsa_len:RSA��Կ����(�ֽ�)
*                           cipher_data�������������ż��ܺ�����ݡ�
*                           cipher_len�����������������Ϊ���������������ĵĻ������ĳ��ȡ�(�ֽ�)
*               ��Ϊ���������������ɵ����ĵĳ��ȡ�
* �������  :
*
* �� �� ֵ  :  BSP_OK--���ܳɹ�;BSP_ERROR--����ʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_rsa_encrypt (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len);
#define CRYPTO_RSA_ENCRYT(data,len,rsa_key,rsa_klen,cipher_data,cihper_len) \
crypto_rsa_encrypt(data,len,rsa_key,rsa_klen,cipher_data,cihper_len)

/*****************************************************************************
* �� �� ��  : crypto_rsa_decrypt
*
* ��������  : ʹ�ñ�����NV�еĸ�����RSA��Կ������������ݽ���
*               ������ܺ�����ݡ�
* �������  : cipher_data�������������ż������ݡ�
*                           cipher_len�����������������ĵĻ������ĳ��ȡ�(�ֽ�)
*                           rsa_key:RSA��Կ
*                           rsa_len:RSA��Կ����(�ֽ�)
*                           data������������������ܺ�����ݡ�
*                           len�����������������Ϊ�����������Ž��ܺ�Ļ������ĳ���(�ֽ�)
*               ��Ϊ���������������ɵ����ĵĳ���
* �������  :
*
* �� �� ֵ  :  BSP_OK--���ܳɹ�;BSP_ERROR--����ʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_rsa_decrypt (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len);
#define CRYPTO_RSA_DECRYPT(cipher_data,cihper_len,rsa_key,rsa_klen,data,len) \
crypto_rsa_decrypt(cipher_data,cihper_len,rsa_key,rsa_klen,data,len)

/*****************************************************************************
* �� �� ��  : crypto_rand
*
* ��������  : ��������ɽӿ�
* �������  : rand_data:��������buffer
*                           len:�����õ���������ֽ���
*
* �������  :
*
* �� �� ֵ  :  BSP_OK--��ȡ������ɹ�;BSP_ERROR--��ȡʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_rand (char *rand_data, int len);
#define CRYPTO_RAND(rand_data,len)  crypto_rand(rand_data,len)


int efuseWriteHUK(char *pBuf,unsigned int len);
#define EFUSE_WRITE_HUK(pBuf,len) efuseWriteHUK(pBuf,len)


int CheckHukIsValid(void);
#define DRV_CHECK_HUK_IS_VALID() CheckHukIsValid()

extern void BSP_PWC_SetTimer4WakeSrc(void);
extern void BSP_PWC_DelTimer4WakeSrc(void);

#define EXCH_TASK_NAME_PART_LEN     12
#define EXCH_CB_NAME_SIZE           32

typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char * pucData;
    unsigned int ulDataLen;
}cb_buf_t;

typedef void (*exchCBReg)(void *);

extern int  DRV_EXCH_TASK_INFO_ADD(int taskPid);
extern int  DRV_EXCH_CUST_FUNC_REG(exchCBReg cb);

/*  SIM  state*/
typedef enum tagSCI_CARD_STATE_E
{
    SCI_CARD_STATE_READY = 0,           	/* Ready */
    SCI_CARD_STATE_NOCARD,                	/* No card */
    SCI_CARD_STATE_BUSY,               		/* In initialization*/
	SCI_CARD_STATE_BUTT,               		/* Butt*/
} SCI_CARD_STATE_E;
extern int BSP_Modem_OS_Status_Switch(int enable);
#define DRV_OS_STATUS_SWITCH(enable) BSP_Modem_OS_Status_Switch(enable)

/*****************************************************************************
* �� �� ��  : BSP_DLOAD_GetNVBackupFlag
*
* ��������  : ��ȡ����ǰ�Ƿ����NV���ݱ�־
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP_TRUE  :����NV
*            BSP_FALSE :������NV
*
* ����˵��  : �˽ӿ�ֻ�Է�һ��ʽ������ʽ��SD����/������������Ч��һ��ʽ�����ᷢAT��������
*
*****************************************************************************/
BSP_BOOL BSP_DLOAD_GetNVBackupFlag(BSP_VOID);
#define DRV_DLOAD_GETNVBACKUPFLAG() BSP_DLOAD_GetNVBackupFlag()

extern BSP_VOID BSP_RunDsp(BSP_VOID);
extern BSP_S32 BSP_LoadDsp(BSP_VOID);

typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);     /* ptr to function returning int */

#define DRV_NOT_START_UMTS (0x55aa5a5a)
extern unsigned long DRV_BBP_GPIO_GET(void);

BSP_S32 BSP_DDR_GetSectInfo(BSP_DDR_SECT_QUERY *pstSectQuery, BSP_DDR_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_DDR_ADDR(pstSectQuery, pstSectInfo) BSP_DDR_GetSectInfo(pstSectQuery, pstSectInfo)

extern BSP_S32 BSP_PMU_AptEnable(BSP_VOID);
#define DRV_PMU_APT_ENABLE()    BSP_PMU_AptEnable()

extern BSP_S32 BSP_PMU_AptDisable(BSP_VOID);
#define DRV_PMU_APT_DISABLE()    BSP_PMU_AptDisable()

BSP_S32 BSP_GetIntNO(BSP_INT_TYPE_E enIntType);
#define DRV_GET_INT_NO(enIntType)    BSP_GetIntNO(enIntType)

/*����������Modem/HIFI��λǰ���Ǹ�λ����ûص�����*/
typedef enum
{
    DRV_RESET_CALLCBFUN_RESET_BEFORE,   /*Modem/HIFI ��λǰ*/
    DRV_RESET_CALLCBFUN_RESET_AFTER,    /*Modem/HIFI ��λ��*/
    DRV_RESET_CALLCBFUN_MOEMENT_INVALID
} DRV_RESET_CALLCBFUN_MOMENT;

/*****************************************************************************
 �� �� ��  : pdrv_reset_cbfun
 ��������  : �����Ҫע��Ļص���������.
 �������  : DRV_RESET_CALLCBFUN_MOMENT eparam,��ʾ��λǰ���Ǹ�λ��,
                int userdata,�û�����
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             ��0������ʧ�ܡ�
*****************************************************************************/
typedef int (*pdrv_reset_cbfun)(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);

/*****************************************************************************
 �� �� ��  : ccorereset_regcbfunc
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��Modem������λǰ/��Ļص��ӿں�����
 �������  : pname���ϲ����ע������֣�ע�ⲻ�����������9���ַ���������洢��
             pcbfun���ص�����ָ�롣
             userdata:�ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ����û���
             priolevel: �ص������������ȼ���0-49
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_CCORERESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                ccorereset_regcbfunc(pname,pcbfun, userdata, priolevel)

/*****************************************************************************
 �� �� ��  : hifireset_regcbfunc
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��HIFI������λ�Ļص��ӿں�����
 �������  : pname���ϲ����ע������֣�ע�ⲻ�����������9���ַ���������洢��
             pcbfun���ص�����ָ�롣
             puserdata:�ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ����û���
             priolevel: �ص������������ȼ���0-49
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_HIFIRESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                hifireset_regcbfunc(pname,pcbfun, userdata, priolevel)

typedef enum tagHKADC_CONV_MODE_E
{
    HKADC_CONV_DELAY = 0,
	HKADC_CONV_NO_DELAY,
	HKADC_CONV_BUTT

}HKADC_CONV_MODE_E;

/*****************************************************************************
 �� �� ��  : DRV_HKADC_GET_TEMP
 ��������  : ��ȡ�豸���¶�ֵ�͵�ѹֵ
 �������  : enMode, *pusVolt, *psTemp
 �������  : *pusVolt, *psTemp
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int DRV_HKADC_GET_TEMP(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E enConvMode);

extern unsigned int BSP_GetSliceValue(BSP_VOID);
#define DRV_GET_SLICE()   BSP_GetSliceValue()

extern BSP_VOID DRV_IPC_SEMGIVE(BSP_U32 u32SignalNum);
extern BSP_S32 DRV_IPC_SEMTAKE(BSP_U32 u32SignalNum, BSP_S32 s32timeout);

#define NV_NAME_LENGTH          8       /*NV name maximum length*/
#define NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define NV_READ                 1       /*NV read  operation*/
#define NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	BSP_U32 nv_operation;              /*0-write,1-read*/
	BSP_U32 nv_number;                 /*NV number you want to visit*/
	BSP_S8 nv_name[NV_NAME_LENGTH];
	BSP_U32 valid_size;
	BSP_U8 nv_data[NVE_NV_DATA_SIZE];
}NVE_INFO_S;

/*****************************************************************************
* �� �� ��  : BSP_NVE_DirectAccess
*
* ��������  : ����LINUX NVE��ι����
*
* �������  : nve  ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2013��6��27��  v1.00  yuanqinshun  ����
*****************************************************************************/
BSP_S32 BSP_NVE_DirectAccess(NVE_INFO_S *nve);
#define DRV_NVE_ACCESS(nve)    BSP_NVE_DirectAccess(nve)

/*****************************************************************************
 �� �� ��  : DRV_PASTAR_EXC_CHECK
 ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : BSP_OK          û���쳣
             BSP_ERROR       �����쳣
*****************************************************************************/
extern BSP_S32 DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id);


extern BSP_S32 PWRCTRL_DfsQosUpdate(BSP_S32 qos_id, BSP_S32 req_id, BSP_U32 req_value);


extern BSP_S32 PWRCTRL_DfsQosRequest(BSP_S32 qos_id, BSP_U32 req_value, BSP_S32* req_id);


/* UART �˿��л� */
#define UART_A_SHELL  (0x5A5A5A5A)
#define UART_C_SHELL  (0xA5A5A5A5)

/*****************************************************************************
 �� �� ��  : DRV_OUTER_RFSWITCH_SET
 ��������  : NASר�ýӿ�
             ���Modem������ѡ����ƽӿ�
             ��ǰ���岻֧�ִ˹��ܣ���ӦNV��Ϊȫ0�������������쳣 ����-1
 �������  : status 1:���Modem���߹��ܣ�0�������Modem���߹���
 �������  : ��
 �� �� ֵ  : 0���ɹ���-1��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��30��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int outer_rfswitch_set(BSP_U32 status);
#define  DRV_OUTER_RFSWITCH_SET(status) outer_rfswitch_set(status)

/*****************************************************************************
 �� �� ��  : DRV_OUTER_RFSWITCH_GET
 ��������  : NASר�ýӿ�
             ���Modem������ѡ���ѯ�ӿ�
             ��ǰ���岻֧�ִ˹��ܣ���ӦNV��Ϊȫ0�������������쳣 ����-1
 �������  : ��
 �������  : status 1:���Modem���߹��ܣ�0�������Modem���߹���
 �� �� ֵ  : 0���ɹ���-1��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��30��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int outer_rfswitch_get(BSP_U32 *status);
#define  DRV_OUTER_RFSWITCH_GET(status) outer_rfswitch_get(status)


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

#endif /* end of __DRV_INTERFACE_H__ */


