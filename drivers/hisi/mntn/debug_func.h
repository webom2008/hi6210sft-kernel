/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : debug_func.h
  �� �� ��   : ����
  ��    ��   : ¬��ʤ 00212112
  ��������   : 2014��3��29��
  ����޸�   :
  ��������   : debug_func.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��3��29��
    ��    ��   : ¬��ʤ 00212112
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __DEBUG_FUNC_H__
#define __DEBUG_FUNC_H__
#include <linux/uaccess.h>
#include <linux/types.h>
#include <soc_ao_sctrl_interface.h>
#include <soc_modem_sctrl_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_wdt_interface.h>
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include <linux/io.h>               /* For writel */

/*#include  ###*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
���Լ���������
*****************************************************************************/
/*it's ecall an variable, if the first input parameter is this value
the same as the one defined in ecall.c*/
#define DBG_ECALL_VARIABLE              0xf0
/*The max number of arguments of ecalled function
keep the same as the one defined in ecall.c*/
#define DBG_ECALL_FUNC_ARGS_MAXNUMB     6
/*for mcu wdg*/
#define MCU_WDT_UNLOCK_VALUE              (0x1ACCE551)
#define M3_WDT_GLOBAL_FREQUENCY       (32768)/*ʹ��32.768Kʱ��*/
#define M3_WDT_NOT_GLOBAL_FREQUENCY   (32768)/*ʹ��32.768Kʱ��*/

/*for c core wdg*/
#define CCORE_WDT_REG_VALUE_UNLOCK        0x1ACCE551
#define CCORE_WDT_REG_VALUE_LOCK          0x00000000
#define CCORE_WDT_CLK_CNT_PER_S               32768   /* ���Ź���ʱ��Ƶ�� */

#define DEBUG_FUNC_MARK         "_func"
#define DEBUG_FUNC_MARK_LEN         strlen(DEBUG_FUNC_MARK)

/*type define of watch dogs*/
typedef enum Dbg_wdg_type
{
    DBG_WDG_ACORE,
    DBG_WDG_CCORE,
    DBG_WDG_LOCAL_MCU,
    DBG_WDG_GLOBAL_MCU,
    DBG_CORE_MAX,
} dbg_wdg_type;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
