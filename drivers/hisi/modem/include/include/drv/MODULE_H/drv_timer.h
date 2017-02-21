/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_timer.h
  �� �� ��   : ����
  ��    ��   : �˳� d00221159
  ��������   : 2013��2��2��
  ����޸�   :
  ��������   : drv_timer.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��2��2��
    ��    ��   : �˳� d00221159
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__
#include "drv_global.h"

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "soc_baseaddr_interface.h"
#if defined(CHIP_BB_HI6210)
#include "soc_rtc_interface.h"
#include "soc_ao_sctrl_interface.h"
#elif defined(BOARD_FPGA)
#include "soc_modem_sctrl_interface.h"
#endif
#endif

typedef enum
{
    PHY_LOAD_MODE_GU,     /* ����GUDSP,ĿǰGUPHY�Ƶ�ARM,�ݲ�ʵ��,��λԤ�� */
    PHY_LOAD_MODE_LTE,    /* ����LTEDSP */
    PHY_LOAD_MODE_TDS,    /* ����TDSDSP */
    PHY_LOAD_MODE_CDMA,   /* ����CDMADSP */
    PHY_LOAD_MODE_BUTTOM
}PHY_LOAD_MODE_E;

/*****************************************************************************
 �� �� ��  : BSP_GetSliceValue
 ��������  : ��ȡSlice��ʱ����ֵ��
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : ��ʱ����ֵ��
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
/*�����Ż���Դ˺���ʵ����MODEM��ʹ�þ�̬��Ƕ*/
static INLINE_ALWAYS unsigned int omTimerGet(void)
{
#if defined(_DRV_LLT_)
	return 0;
#else
#if defined(CHIP_BB_HI6210)
    return (*(volatile unsigned int *)(SOC_AO_SCTRL_SC_SYSTEST_SLICER_CNT0_ADDR(SOC_AO_SCTRL_BASE_ADDR)));
#elif defined(BOARD_FPGA)
	return (*(volatile unsigned int *)(SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_ADDR(SOC_SC_BASE_ADDR)));
#endif
#endif
}
#else
extern unsigned int omTimerGet(void);
#endif
extern unsigned int BSP_GetSliceValue(void);
#define DRV_GET_SLICE() omTimerGet()

/*****************************************************************************
 �� �� ��  : BSP_StartHardTimer
 ��������  : ����һ����ʱ����ֵ��
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : ��ʱ����ֵ��
*****************************************************************************/
extern BSP_VOID BSP_StartHardTimer( BSP_U32 value );
#define DRV_STATR_HARD_TIMER(value)   BSP_StartHardTimer(value)

/*****************************************************************************
 �� �� ��  : BSP_StartHardTimer
 ��������  : ����һ����ʱ����ֵ��
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : ��ʱ����ֵ��
*****************************************************************************/
extern BSP_VOID BSP_StopHardTimer(BSP_VOID);
#define DRV_STOP_HARD_TIMER()   BSP_StopHardTimer()

/*****************************************************************************
 �� �� ��  : BSP_GetHardTimerCurTime
 ��������  : ��ȡһ����ʱ����ʣ��ֵ��
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : ��ʱ����ʣ��ֵ��
*****************************************************************************/
extern BSP_U32 BSP_GetHardTimerCurTime(BSP_VOID);
#define DRV_GET_TIMER_CUR_TIME()   BSP_GetHardTimerCurTime()

/*****************************************************************************
 �� �� ��  : BSP_ClearTimerINT
 ��������  : ���һ����ʱ�����ж�
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : ��ʱ����ʣ��ֵ��
*****************************************************************************/
extern BSP_VOID BSP_ClearTimerINT(BSP_VOID);
#define DRV_CLEAR_TIMER_INT()   BSP_ClearTimerINT()


/*****************************************************************************
* �� �� ��  : BSP_USRCLK_Connect
*
* ��������  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable usr clock interrupts.
*
* �������  : FUNCPTR routine   routine to be called at each clock interrupt
              BSP_S32 arg           argument with which to call routine
              BSP_S32 s32UsrClkid      which user clock the interrup routine belongs to
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat
*****************************************************************************/
extern BSP_S32  BSP_USRCLK_Connect(FUNCPTR routine, BSP_S32 arg, BSP_S32 s32UsrClkid);

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

typedef enum
{
    TIMER_CCPU_OSA_ID           = 0,         /*v3r3 ,v9r1 c���ṩ��osa��timer ID*/
    TIMER_CCPU_MSP_ID           = 1,
    TIMER_CCPU_APP_ID           = 2,
    TIMER_CCPU_SOFTTIMER_ID     = 3,         /* v3r3 ,v9r1 c�˷������timer��ID */
    TIMER_DSP_TIMER1_ID         = 4,         /* v3r3 ,v9r1�����DSP��timerID1 */
    TIMER_DSP_TIMER2_ID         = 5,         /*v3r3 , v9r1�����DSP��timerID2 ,v3r3 Ϊ32kʱ�ӣ����͹���ʹ��*/
    TIMER_HIFI_TIMER1_ID        = 6,         /*v9r1 �����HIFI��timerID1,v3r3�����A��codec�ĵ�timer ID */
    TIMER_CCPU_DFS_ID           = 7,
    TIMER_CCPU_SYS_ID           = 8,         /* v3r3 ,v9r1�����ϵͳʱ�ӵ�ID */
    TIMER_CCPU_AUX_ID           = 9,         /* v3r3 ,v9r1�����ϵͳ����ʱ�ӵ�ID */
    TIMER_CCPU_DSP_DRX_PROT_ID  = 10,        /* ֻ��v9r1 sft��v9r1 bbit���ã������DSP */
    TIMER_CCPU_DRX_STAMP_ID     = 12,
    TIMER_HIFI_TIMER2_ID        = 13,
    TIMER_ALL_SLICE_ID          = 14,        /* A��C�˹��õ�slicetimerID */
    TIMER_MCU_TIMER1_ID         = 15,        /* Ԥ��������MCUʹ�� */
    TIMER_MCU_TIMER2_ID         = 16,        /* Ԥ��������MCUʹ�� */
    TIMER_CCPU_CPUVIEW_ID       = 17,        /*�ṩ��TTFʹ��*/
    TIMER_CCPU_DRX1_STABLE_ID   = 18,        /* v9r1�����DRX1 TCXO�ȶ���ʱ�ӵ�ID */
    TIMER_CCPU_DRX2_STABLE_ID   = 19,        /* v9r1�����DRX2 TCXO�ȶ���ʱ�ӵ�ID */
    TIMER_ACPU_SYSTEM_ID        = 20,        /* v3r3 ,v9r1�����ϵͳʱ�ӵ�ID */
    TIMER_ACPU_FREE_RUN         = 21,        /* v3r3 ,v9r1�����linux ����ʱ�ӵ�ID */
    TIMER_ACPU_OSA_ID           = 22,        /*v3r3 ,v9r1 A���ṩ��osa��timer ID*/
    TIMER_ACPU_SOFTTIMER_ID     = 23,        /* v3r3 ,v9r1 A�˷������timer��ID */
    TIMER_OM_TCXO_ID            = 24,        /* (�ѷ���)�ṩ��OM �ĸ߾��ȶ�ʱ��,A��C�˾��ṩ */
    TIMER_ACPU_APP_ID           = 25,        /* v9r1 v3r3 bbitʹ�� */
    TIMER_CCPU_DRX_TIMER_ID     = 26,        /* V3R3 v9r1 �͹���drx��������ʹ�� */
    TIMER_ACPU_IDLE_ID          = 27,        /* a�˵͹�����,cpu idle */
    TIMER_ACPU_OM_TCXO_ID       = 28,        /* Ϊ���VOS_TIMERƵ�����ȵ����⣬�����timer��OAM */
    TIMER_CCPU_G1PHY_DRX_ID     = 29,        /* ֻ��v9r1�ã������DSP ����drx��ܷ��� */
    TIMER_MCU_SYSTEM_ID         = 38,
    TIMER_MCU_SOFTTIMER_ID      = 39,
    TIMER_ID_MAX                = 40
} DRV_TIMER_ID;

typedef enum
{
    TIMER_ONCE_COUNT = 0,        /* ���ζ�ʱ��ģʽ */
    TIMER_PERIOD_COUNT,          /* ���ڶ�ʱ��ģʽ */
    TIMER_COUNT_BUTT
}DRV_TIMER_MODE;

typedef enum
{
    TIMER_UNIT_MS = 0,           /* 0��ʾ��λmsģʽ */
    TIMER_UNIT_US,               /* 1��ʾ��λusģʽ */
    TIMER_UNIT_NONE,             /* 2��ʾ��λ1����ֱ�Ӳ���load�Ĵ���ģʽ  */
    TIMER_UNIT_BUTT
}DRV_TIMER_UNIT;

/*****************************************************************************
 �� �� ��  : DRV_TIMER_START
 ��������  : ��װ��Э��ջ���û�ʱ�Ӷ�ʱ����������
 �������  : usrClkId:ʹ��DRV_TIMER_ID �ṩ��timerID
             routine:�ص�����
             arg:�ص�����
             timerValue:����ֵ
             mode:��ʱ������ģʽ������ģʽ������ģʽ���μ�DRV_TIMER_MODE
             unitType: 0��ʾ��λms�� 1��ʾ��λus�� 2��ʾ��λ1����ֱ�Ӳ���load�Ĵ���ģʽ
                unitType=0ʱ, Ƶ��Ϊ19.2MHz��timer  timerValueȡֵ��Χ[1,223696]
                              Ƶ��Ϊ32KHz  ��timer  timerValueȡֵ��Χ[1,131071]
                unitType=1ʱ, Ƶ��Ϊ19.2MHz��timer  timerValueȡֵ��Χ[1,223696]
                              Ƶ��Ϊ32KHz  ��timer��������������������Ӳ�����ƣ�֧�ֵ���С�̶�ԼΪ31us;
                                                    timerValue��Χ[1,31]�����ӳ�1us;
                                                              ��Χ[32,131071]ʱ����ʵ��������(timerValue*32768)/1000000���䶨ʱ����countֵ�����޷�����31us��60us����������
                unitType=2ʱ, timerValueȡֵ��Χ[1,0xFFFFFFFF]

 �������  : ��
 �� �� ֵ  : int  0 �����ɹ��� -1 ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : ��ҫ�� 00179452
   �޸�����    : �����ɺ���

 2.��    ��   : 2013��5��21��
   ��    ��   : ��ϲ 00220237
   �޸�����   : ���Ӷ�32Kʱ�ӵ���΢��ӿڵ�֧�֣�ֻ������ʱ��С�̶�ԼΪ31us

*****************************************************************************/
extern int DRV_TIMER_START
(
    unsigned int     usrClkId,
    FUNCPTR_1        routine,
    int              arg,
    unsigned int     timerValue,
    unsigned int     mode,
    unsigned int     unitType
);

/*****************************************************************************
 �� �� ��  : DRV_TIMER_STOP
 ��������  : ��װ��Э��ջ���û�ʱ�Ӷ�ʱ��ֹͣ����
 �������  : usrClkId:ʱ��ID,ȡֵ0~19
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : ��ҫ�� 00179452
   �޸�����   : �����ɺ���

*****************************************************************************/
extern int DRV_TIMER_STOP(unsigned int usrClkId);

/*****************************************************************************
 �� �� ��  : DRV_TIMER_GET_REST_TIME
 ��������  : ��ȡ��ʱ����ʣ��ʱ��
 �������  : usrClkId:ʱ��ID,ȡֵ0~19
            unitType
            pRestTime
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  :

 �޸���ʷ  :
 1.��    ��   : 2012��7��19��
   ��    ��   : ��ҫ�� 00179452
   �޸�����   : �����ɺ���

*****************************************************************************/
extern int DRV_TIMER_GET_REST_TIME(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime);

/*****************************************************************************
* �� �� ��  : BSP_PWC_SetDrxTimerWakeSrc
* ��������  : ����DRX timer ��Ϊ����Դ
* �������  :
* �������  :
* �� �� ֵ   :
* �޸ļ�¼  : ��v7r1��ֲ�������ڲ��̶�ʹ��TIMER_CCPU_DRX_TIMER_ID
                v9r1 sft c��ʵ�� a�˴�׮
                v9r1 bbit Ӳ����֧�֣���׮
                v3r3 sft c��ʵ�� a�˴�׮
*****************************************************************************/
extern void BSP_PWC_SetDrxTimerWakeSrc(void);
#define DRV_SET_DRX_TIMER_WAKE_SRC() BSP_PWC_SetDrxTimerWakeSrc()

/*****************************************************************************
* �� �� ��  : BSP_PWC_DelDrxTimerWakeSrc
* ��������  : ����DRX timer ����Ϊ����Դ
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  : ��v7r1��ֲ�������ڲ��̶�ʹ��TIMER_CCPU_DRX_TIMER_ID
                v9r1 sft c��ʵ�� a�˴�׮
                v9r1 bbit Ӳ����֧�֣���׮
                v3r3 sft c��ʵ�� a�˴�׮
*****************************************************************************/
extern void BSP_PWC_DelDrxTimerWakeSrc(void);
#define DRV_DEL_DRX_TIMER_WAKE_SRC() BSP_PWC_DelDrxTimerWakeSrc()

/*****************************************************************************
 �� �� ��  : DRV_GET_RTC_VALUE
 ��������  : ����rtc�Ĵ�������õ�ǰRTC��ֵ
 �������  : ��
 �������  : ��
 ����ֵ    ��RTCֵ����λs
 �޸�˵��  :
             V9sft A��C�˹��ʵ��(A����mach_info.c�ļ���)
             V3sft A��C�˴�׮
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
static INLINE_ALWAYS BSP_U32 BSP_GET_RTC_VALUE(void)
{
#if defined(BOARD_FPGA) || defined(_DRV_LLT_)
    return 0;
#else
	BSP_U32 result;
	BSP_REG_READ(0, SOC_RTC_RTCDR_ADDR(SOC_RTC0_BASE_ADDR), result);
	return result;
#endif
}
#define DRV_GET_RTC_VALUE() BSP_GET_RTC_VALUE()
#else
unsigned int DRV_GET_RTC_VALUE(void);
#endif

/*****************************************************************************
 �� �� ��  : DRV_GET_SLICE_VALUE
 ��������  : ��õ�ǰSLICEֵ
 �������  : ��
 �������  : ��
 ����ֵ    ��SLICE
*****************************************************************************/
unsigned int DRV_GET_SLICE_VALUE(void);

#endif

