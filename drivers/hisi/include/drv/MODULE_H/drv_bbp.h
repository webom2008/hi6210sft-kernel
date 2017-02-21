
#ifndef __DRV_BBP_H__
#define __DRV_BBP_H__

#include "drv_global.h"
#include "drv_dpm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*����bbp����ʱ�� ��ѯ��֡�ŵȽӿڵķ���ֵ*/
#define BBP_POWER_DOWN_BACK 0xffff
#define BBP_TDS_STU_SFN_MASK 0x1fff

#define BSP_BBP_POWER_DOWN BBP_POWER_DOWN_BACK

/* ����ҵ������DMA��������ж�,���ж�ֻ��ӦModem��*/
typedef BSP_VOID (*BSPBBPIntDlTbFunc)(BSP_VOID);
/* BBP��֡�жϴ�����,���ж�ֻ��ӦModem��*/
typedef BSP_VOID (*BSPBBPIntTimerFunc)(BSP_VOID);
/* BBP TDS�жϴ�����,���ж�ֻ��ӦModem�� */
typedef BSP_VOID (*BSPBBPIntTdsFunc)(BSP_VOID);


extern BSP_VOID bsp_bbp_timerintregcb(BSPBBPIntTimerFunc pFunc);
#define DRV_BBP_INT_TIMER_REG_CB(pFunc) bsp_bbp_timerintregcb(pFunc)
/*���ݾɽӿ�*/
#define BSP_BBPIntTimerRegCb(pFunc) bsp_bbp_timerintregcb(pFunc)
extern BSP_VOID bsp_bbp_dltbintregcb(BSPBBPIntDlTbFunc pFunc);
#define DRV_BBP_INT_DL_TB_REG_CB(pFunc) bsp_bbp_dltbintregcb(pFunc)
/*���ݾɽӿ�*/
#define BSP_BBPIntDlTbRegCb(pFunc) bsp_bbp_dltbintregcb(pFunc)
extern BSP_VOID bsp_bbp_timerintclear(BSP_VOID);
#define DRV_BBP_INT_TIMER_CLEAR() bsp_bbp_timerintclear()
/*���ݾɽӿ�*/
#define BSP_BBPIntTimerClear() bsp_bbp_timerintclear()
extern BSP_S32 bsp_bbp_timerintenable(BSP_VOID);
#define DRV_BBP_INT_TIMER_ENABLE() bsp_bbp_timerintenable()
/*���ݾɽӿ�*/
#define BSP_BBPIntTimerEnable() bsp_bbp_timerintenable()
extern BSP_VOID bsp_bbp_timerintdisable(BSP_VOID);
#define DRV_BBP_INT_TIMER_DISABLE() bsp_bbp_timerintdisable()
/*���ݾɽӿ�*/
#define BSP_BBPIntTimerDisable() bsp_bbp_timerintdisable()
extern BSP_U32 bsp_bbp_getcurtime(BSP_U64 *pCurTime);
extern BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime);
#define DRV_BBP_GET_CUR_TIME(pCurTime) BSP_BBPGetCurTime(pCurTime)


extern BSP_S32 bsp_bbp_get_time_value(BSP_U32  *pulHigh32bitValue,  BSP_U32  *pulLow32bitValue);
#define DRV_GET_BBP_TIMER_VALUE(pulHigh32bitValue, pulLow32bitValue) bsp_bbp_get_time_value(pulHigh32bitValue, pulLow32bitValue)


extern BSP_U16 bsp_bbp_getsysframe(BSP_VOID);
#define DRV_GET_SYS_FRAME() bsp_bbp_getsysframe()
/*���ݾɽӿ�*/
#define BSP_GetSysFrame() bsp_bbp_getsysframe()
extern BSP_U16 bsp_bbp_getsyssubframe(BSP_VOID);
#define DRV_GET_SYS_SUB_FRAME() bsp_bbp_getsyssubframe()
/*���ݾɽӿ�*/
#define BSP_GetSysSubFrame() bsp_bbp_getsyssubframe()
extern BSP_U16 bsp_bbp_get_tds_subframe(BSP_VOID);
#define DRV_GET_TDS_SUB_FRAME()   bsp_bbp_get_tds_subframe()
/*���ݾɽӿ�*/
#define BSP_GetTdsSubFrame()   bsp_bbp_get_tds_subframe()
extern BSP_U16 bsp_bbp_set_tds_subframoffset(BSP_U16 usOffset);
#define DRV_SET_TDS_SUB_FRAME_OFFSET(usOffset)   bsp_bbp_set_tds_subframoffset(usOffset)
/*���ݾɽӿ�*/
#define BSP_SetTdsSubFrameOffset(usOffset)   bsp_bbp_set_tds_subframoffset(usOffset)
extern BSP_U32 bsp_bbp_get_tds_sleep_time(BSP_VOID);
#define DRV_GET_TDS_SLEEP_TIME()   bsp_bbp_get_tds_sleep_time()
/*���ݾɽӿ�*/
#define BSP_GetTdsSleepTime()   bsp_bbp_get_tds_sleep_time()
extern BSP_VOID bsp_bbp_tdstf_regcb(BSPBBPIntTdsFunc pFunc);
#define DRV_BBP_INT_TDS_TF_REG_CB(pFunc) bsp_bbp_tdstf_regcb(pFunc)
/*���ݾɽӿ�*/
#define BSP_BBPIntTdsTFRegCb(pFunc) bsp_bbp_tdstf_regcb(pFunc)
extern BSP_S32 bsp_bbp_tdstf_enable(BSP_VOID);
#define DRV_BBP_INT_TDS_TF_ENABLE() bsp_bbp_tdstf_enable()
/*���ݾɽӿ�*/
#define BSP_BBPIntTdsTFEnable() bsp_bbp_tdstf_enable()
extern BSP_VOID bsp_bbp_tdstf_disable(BSP_VOID);
#define DRV_BBP_INT_TDS_TF_DISABLE() bsp_bbp_tdstf_disable()
/*���ݾɽӿ�*/
#define BSP_BBPIntTdsTFDisable() bsp_bbp_tdstf_disable()
extern void bbp_wakeup_int_enable(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_ENABLE(mode) bbp_wakeup_int_enable(mode)
/*���ݾɽӿ�*/
#define BSP_BBPIntWakeEnable(mode) bbp_wakeup_int_enable(mode)
extern void bbp_wakeup_int_disable(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_DISABLE(mode) bbp_wakeup_int_disable(mode)
/*���ݾɽӿ�*/
#define BSP_BBPIntWakeDisable(mode) bbp_wakeup_int_disable(mode)
extern void bbp_wakeup_int_clear(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_CLEAR(mode) bbp_wakeup_int_clear(mode)
/*���ݾɽӿ�*/
#define BSP_BBPIntWakeClear(mode) bbp_wakeup_int_clear(mode)
extern BSP_S32 bsp_bbp_get_tdsclk_switch(BSP_VOID);
#define DRV_GET_TDS_CLK_STATUS()   bsp_bbp_get_tdsclk_switch()
/*���ݾɽӿ�*/
#define BSP_GetTdsClkSwitchStatus()   bsp_bbp_get_tdsclk_switch()
extern BSP_S32 bsp_bbp_get_means_flag(PWC_COMM_MODE_E enCommMode);
#define DRV_PWC_GET_MEANSFLAG(enCommMode) bsp_bbp_get_means_flag(enCommMode)
/*���ݾɽӿ�*/
#define BSP_PWC_GetMeansFlag(enCommMode) bsp_bbp_get_means_flag(enCommMode)
extern int bsp_bbp_timer_int_init(PWC_COMM_MODE_E mode);
#define DRV_BBP_TIMER_INT_INIT(mode) bsp_bbp_timer_int_init(mode)


int bsp_bbp_dma_int_init(void);
#define DRV_BBP_DMA_INT_INIT() bsp_bbp_dma_int_init()


int bsp_bbp_dma_int_enable(void);
#define DRV_BBP_DMA_INT_ENABLE() bsp_bbp_dma_int_enable()

/*****************************************************************************
* �� �� ��  : bsp_bbp_lps_get_ta
* ��������  : ��LPS���ã��鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_U16
* �޸ļ�¼  : 2013��11��15��  porting from v7r2,just for lte
*****************************************************************************/
extern BSP_U16 bsp_bbp_lps_get_ta(void);
#define DRV_LPS_GET_TA() bsp_bbp_lps_get_ta()
/*���ݾɽӿ�*/
#define BSP_LPS_GetTa() bsp_bbp_lps_get_ta()

/*****************************************************************************
* �� �� ��  : bsp_bbp_timerintswitch
* ��������  : ���ڻ�ȡlte 1ms��ʱ���ж�ʹ��/����״̬
* �������  : ��
* �������  : BSP_BOOL  ��ʱ���жϿ���״̬(1:�ж�ʹ�ܡ�0:�ж�ȥʱ��,BBP��ֹ����ʱĬ���ж�ȥʹ��)
* �� �� ֵ  : BSP_OK    LTE-BBP�����������״̬
*             BSP_ERROR LTE-BBP���ڽ�ֹ����״̬
* �޸ļ�¼  : 2014��1��9��  zhoushan  creat
*****************************************************************************/
BSP_S32 bsp_bbp_timerintswitch(BSP_BOOL *pbStat);
#define DRV_BBP_INT_TIMER_SWITCH_STATUS(pbStat) bsp_bbp_timerintswitch(pbStat)
/*���ݾɽӿ�*/
#define BSP_BBPIntTimerSwitchStatus(pbStat) bsp_bbp_timerintswitch(pbStat)
BSP_U32 bsp_bbp_get_ms(BSP_VOID);
#define DRV_GET_32K_MS()    bsp_bbp_get_ms()
/*���ݾɽӿ�*/
#define BSP_BBP_Get32kMs()    bsp_bbp_get_ms()

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
