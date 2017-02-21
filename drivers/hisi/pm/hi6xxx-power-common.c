/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pwrctrl_common.c
  �� �� ��   : ����
  ��    ��   : ������ 56193
  ��������   : 2012��7��25��
  ����޸�   :
  ��������   :  �͹��Ĺ���ģ��
  �����б�   :
              pwrctrl_clr_bits
              pwrctrl_get_slice_time
              pwrctrl_is_bit_set
              pwrctrl_is_func_on
              pwrctrl_mem_cpy
              pwrctrl_read_reg32
              pwrctrl_timer_delay
              pwrctrl_write_reg32
              pwrctrl_set_bits

  �޸���ʷ   :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#ifndef WIN32
#include <linux/string.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
/*#include <asm/memory.h>*/
/*#include <mach/system.h>*/
#include <linux/hisi/hi6xxx-platform.h>
#include <linux/delay.h>
/*#include <mach/irqs.h>*/
/*#include <asm/hardware/gic.h>*/
/*#include <asm/hardware/arm_timer.h>*/
#include <linux/slab.h>
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/io.h>
#include <linux/ioport.h>

/*#include <mach/io.h>*/
/*#include <mach/platform.h>*/
/*#include "product_config.h"*/

#endif
#include <linux/hisi/pm/hi6xxx-power-common.h>
#include <linux/hisi/pm/hi6xxx-power-dfs.h>
#include "soc_peri_sctrl_interface.h"
#include "soc_acpu_sctrl_interface.h"

#if 0
#include <soc_baseaddr_interface.h>
#include <soc_sctrl_interface.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>
#endif
#include "drv_timer.h"
#include <linux/hisi/hi6xxx-iomap.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if 0
PWRCTRL_ACPU_EXC_LOG_STRU * g_stAcpuPwcExcLog = NULL;
#endif

static PWC_CCPU_LOG_STRU * g_pPwcCcpuLog = NULL;
static PWC_MCU_LOG_STRU * g_pPwcMcuLog = NULL;

static ST_PWC_SWITCH_STRU * g_stAcpuPwcSwitch = NULL;

s8_t g_pwcAcpuWakeFlagIcc = 0;
s8_t g_pwcAcpuWakeFlagRfile = 0;

#if 0
struct wake_lock g_ulTstwakelock;

u32_t   g_ulPwcDebugTrace = 0;

u32_t g_ulpwrctrl_print_switch = 0;

u32_t g_pwc_init_flag = 0;

extern s32_t pwrctrl_timer_addr_remap(void);
#endif
#if 0
u32_t g_aAcpuHwVoteBaseAddr[] =
{
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_PERI_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_ACPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE1EN0_ADDR(SOC_SC_ON_BASE_ADDR)),
    IO_ADDRESS(SOC_AO_SCTRL_SC_MCU_VOTE2EN0_ADDR(SOC_SC_ON_BASE_ADDR)),

};
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if 0
/*****************************************************************************
 �� �� ��  : pwrctrl_print_switch_set
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ģ�����ô�ӡ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��22��
    ��    ��   : �ż� 00179562
    �޸�����   : �����ɺ���

*****************************************************************************/
void pwrctrl_print_switch_set(unsigned int flag,int mode)
{
    /*bitģʽ*/
    if(0 == mode)
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_print_switch_set,old value:0x%x\n",g_ulpwrctrl_print_switch);
        g_ulpwrctrl_print_switch |= (1<<flag);
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_print_switch_set,new value:0x%x\n",g_ulpwrctrl_print_switch);
    }
    else/*һ������ģʽ*/
    {
        g_ulpwrctrl_print_switch = flag;
    }
}
/*****************************************************************************
 �� �� ��  : print_switch_get
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡ��ӡ����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��22��
    ��    ��   : �ż� 00179562
    �޸�����   : �����ɺ���

*****************************************************************************/
u32_t pwrctrl_print_switch_get(void)
{
    return g_ulpwrctrl_print_switch;
}
#endif

/*****************************************************************************
 �� �� ��  : pwrctrl_get_slice_time
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ����ǰֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��31��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
u32_t  pwrctrl_get_slice_time( void_t )
{
    return BSP_GetSliceValue();
}

/*****************************************************************************
 �� �� ��  : pwrctrl_early_init
 ��������  : ��Ҫ��ǰ��ʼ���Ĳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
static s32_t __init pwrctrl_early_init(void_t)
{
    void __iomem *peri_sc_base, *acpu_sc_base;

    volatile SOC_ACPU_SCTRL_ACPU_SC_CLKEN_UNION *acpusc_clken;
    peri_sc_base = HISI_VA_ADDRESS(SOC_PERI_SCTRL_BASE_ADDR);
    acpu_sc_base = HISI_VA_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR);

    g_stAcpuPwcSwitch = (ST_PWC_SWITCH_STRU *)(SOC_PERI_SCTRL_SC_RESERVED8_ADDR(peri_sc_base));

    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_AGENERAL))
        return RET_ERR;

    /*ACPU auto clk gating*/
    acpusc_clken = (volatile SOC_ACPU_SCTRL_ACPU_SC_CLKEN_UNION *)SOC_ACPU_SCTRL_ACPU_SC_CLKEN_ADDR(acpu_sc_base);
    acpusc_clken->reg.bypass_decbrg_clkgten = 1;
    acpusc_clken->reg.bypass_ace_clkgten = 1;

    pwrctrl_dfs_init();

    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_common_initial
 ��������  : �͹��ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
#if 0
s32_t __init pwrctrl_common_initial ( void_t )
{
/*lint -e553*/
#if 1/*(FEATURE_POWER_DRV == FEATURE_ON)*/
/*lint +e553*/
    local_t u32_t startTm=0;
    u32_t tmpTm = 0;

    g_stAcpuPwcExcLog = (PWRCTRL_ACPU_EXC_LOG_STRU *)(EXCH_ACPU_CORE_PWC_ADDR_V);
    pwrctrl_write_reg32(IO_ADDRESS(EXCH_A_CORE_POWRCTRL_CONV_ADDR), EXCH_ACPU_CORE_PWC_ADDR);

    /*����SLICE TIMER ����ַ*/
#if defined(CHIP_BB_HI6210) /*B020 Modify*/
#else
    pwrctrl_write_reg32(PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR, IO_ADDRESS(SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR(SOC_SC_ON_BASE_ADDR)));
#endif
    wake_lock_init(&g_ulTstwakelock,WAKE_LOCK_SUSPEND,"pwrctrl_tst");
    pwrctrl_sleep_initial();
    pwrctrl_sleep_mgr_sleep_init();

    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_ASLEEP))
    {
        wake_lock(&g_ulTstwakelock);
        PWC_TRACE(PWC_LOG_MAX, "MCU: pwc_common_initial,msleep not support!\r\n",0,0,0,0,0,0);
    }
    else
    {
        /*lint*/
    }

    /* �͹��ĳ�ʼ�����*/
    PWC_TRACE(PWC_LOG_MAX, "ACPU: Enter pwrctrl initial routing! \n",0,0,0,0,0,0);

    register_reboot_notifier(&pm_reboot_nb);
    pwrctrl_write_reg32(IO_ADDRESS(MEMORY_AXI_SEC_CORE_BOOT_TEST_ADDR), 0);
    printk("sec core boot test addr:0x%x\n", MEMORY_AXI_SEC_CORE_BOOT_TEST_ADDR);
#endif
    g_pwc_init_flag = PWRCTRL_INIT_FLAG;

    return RET_OK;
}

int g_acpu_pm_test_flag = 0;

void set_acpu_pm_test_flag(int flag)
{
	printk("%s old:%d new:%d\n", __FUNCTION__, g_acpu_pm_test_flag, flag);
	g_acpu_pm_test_flag = flag;
}

void acpu_pm_test()
{
	if(0 == g_acpu_pm_test_flag)
	{
		wake_lock(&g_ulTstwakelock);
       }
}

void release_acpu_test_wakelock()
{
	printk("%s wake unlock\n", __FUNCTION__);
	wake_unlock(&g_ulTstwakelock);
}
#endif

/*****************************************************************************
 �� �� ��  : pwrctrl_timer_delay
 ��������  : ��ʱ����
 �������  : s32_t time
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_timer_delay (u32_t time)
{
    u32_t uDecValue = (u32_t)(time * PWRCTRL_SLICE_CLK) / PWRCTRL_SLICE_UNIT_CONV;
    u32_t uCurValue, uTargValue;

    /* ��Timer�ĵ�ǰ����ֵ */
    uCurValue = pwrctrl_get_slice_time();
    PWC_TRACE(PWC_LOG_DEBUG, "Current TIME Value1 = 0x%x\n", uCurValue);

    /* ��Timer�ĵݼ�Ŀ��ֵ */
    if (uDecValue <= uCurValue)
    {
        uTargValue = uCurValue - uDecValue;
    }
    else
    {
        uTargValue = PWRCTRL_SLICETIMER_XLOAD - (uDecValue - uCurValue);
    }

    /* ��ȡ�����Ƚ� */
    for (;;)
    {
        uCurValue = pwrctrl_get_slice_time();
        if (uCurValue <= uTargValue)
        {
            PWC_TRACE(PWC_LOG_DEBUG, "Curent,TIME Value2 = 0x%x\n", uCurValue);
            break;
        }
    }
    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_write_reg32
 ��������  : �Ĵ���д�ӿ�
 �������  : s32_t ulRegAddr
             s32_t ulRegVal
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_write_reg32( u32_t ulRegAddr, u32_t ulRegVal)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_write_reg32 Address: 0x%x not aligned.\r\n", (int)ulRegAddr);
        return RET_ERR;
    }

    *(volatile u32_t *)ulRegAddr = ulRegVal;
    return RET_OK;
}
/*****************************************************************************
 �� �� ��  : pwrctrl_read_reg32
 ��������  : �Ĵ������ӿ�
 �������  : s32_t ulRegAddr
 �������  : ��
 �� �� ֵ  : int            Ŀ��Ĵ�����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
u32_t pwrctrl_read_reg32 ( u32_t ulRegAddr )
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_read_reg32 Address: 0x%x not aligned.\r\n", (int)ulRegAddr);
        return 0;
    }

    return *(volatile u32_t *)ulRegAddr;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_write_reg32_mask
 ��������  : ��mask�ļĴ���д�ӿ�
 �������  : s32_t ulRegAddr
             s32_t ulRegVal
             u32_t ulMask
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
void pwrctrl_write_reg32_mask (u32_t ulRegAddr, u32_t ulRegVal, u32_t ulMask)
{
    u32_t reg_val = pwrctrl_read_reg32(ulRegAddr);

    pwrctrl_clr_bits((u32_t)&reg_val, ulMask);

    pwrctrl_set_bits((u32_t)&reg_val, ulRegVal & ulMask);

    pwrctrl_write_reg32(ulRegAddr, reg_val);
}

/*****************************************************************************
 �� �� ��  : pwrctrl_clear_reg32_mask
 ��������  : ��mask�ļĴ������ӿ�
 �������  : s32_t ulRegAddr
             u32_t ulMask
 �������  : ��
 �� �� ֵ  : int            Ŀ��Ĵ�����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
u32_t pwrctrl_read_reg32_mask(u32_t ulRegAddr, u32_t ulMask)
{
    return pwrctrl_read_reg32(ulRegAddr) & ulMask;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_set_bits
 ��������  : �Ĵ���BIT���ýӿ�
 �������  : s32_t ulRegAddr
             s32_t ulMask
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_set_bits (u32_t ulRegAddr, u32_t ulMask)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_set_bits Address: 0x%x not aligned.\r\n", (int)ulRegAddr);
        return RET_ERR;
    }

    pwrctrl_write_reg32(ulRegAddr, pwrctrl_read_reg32(ulRegAddr)|ulMask);
    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_clr_bits
 ��������  : �Ĵ���BIT����ӿ�
 �������  : s32_t ulRegAddr
             s32_t ulMask
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_clr_bits (u32_t ulRegAddr, u32_t ulMask)
{
    if (0 != (ulRegAddr & 0x03))/* not 4byte aligned */
    {
        PWC_TRACE(PWC_LOG_MAX, "pwrctrl_clr_bits Address: 0x%x not aligned.\r\n", (int)ulRegAddr);
        return RET_ERR;
    }

    pwrctrl_write_reg32(ulRegAddr, pwrctrl_read_reg32(ulRegAddr)&(~ulMask));
    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_is_bits_set
 ��������  : �Ĵ���BITS�жϽӿ�
 �������  : s32_t ulRegAddr
             s32_t ulMask
 �������  : ��
 �� �� ֵ  : TRUE / FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
bool_t pwrctrl_is_bits_set(u32_t ulRegAddr, u32_t ulMask)
{
    if(0 != (ulRegAddr & 0x03))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_is_bits_set para error.\r\n");
    }

    return (pwrctrl_read_reg32(ulRegAddr) & ulMask) == ulMask;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_is_bits_clr
 ��������  : �Ĵ���BITS�жϽӿ�
 �������  : s32_t ulRegAddr
             s32_t ulMask
 �������  : ��
 �� �� ֵ  : TRUE / FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
bool_t pwrctrl_is_bits_clr(u32_t ulRegAddr, u32_t ulMask)
{
    if(0 != (ulRegAddr & 0x03))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_is_bits_clr para error.\r\n");
    }

    return (pwrctrl_read_reg32(ulRegAddr) & ulMask) == 0x0;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_is_bit_set
 ��������  : ���Ĵ���BIT״̬
 �������  : u32_t addr    �Ĵ�����ַ
             u32_t offset  bit ƫ��
 �������  : ��
 �� �� ֵ  : PWC_TRUE         1
             PWC_FALSE        0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
u32_t pwrctrl_is_bit_set ( u32_t addr,  u32_t offset)
{
    if ((pwrctrl_read_reg32(addr) & (1<<offset)) == (1<<offset))
    {
        return PWRCTRL_TRUE ;
    }
    else
    {
        return PWRCTRL_FALSE;
    }
}


/*****************************************************************************
 �� �� ��  : pwrctrl_is_func_on
 ��������  : ���͹����������Ƿ�ʹ��
 �������  : EM_PWC_SWITCH funId    �ӹ���ģ��id
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_is_func_on ( EM_PWC_SWITCH funId )
{
    if (pwrctrl_is_bit_set((u32_t)(g_stAcpuPwcSwitch),funId))
    {
        return RET_OK;
    }
    else
    {
        return RET_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : pwrctrl_mem_cpy
 ��������  : �͹����ڴ濽��
 �������  : dest   Ŀ���ڴ�
             src    Դ�ڴ�
             size   ���ȣ���λ 32bit
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_mem_cpy ( void_t * dest, void_t * src, u32_t size )
{
    u32_t length = 0;
    u32_t * tDest = (u32_t *)(dest);
    u32_t * tSrc = (u32_t *)(src);

    for(; length<size; length++)
    {
        pwrctrl_write_reg32((u32_t)tDest,pwrctrl_read_reg32((u32_t)tSrc));
        tDest ++;
        tSrc ++;
    }

    return RET_OK;
}
/*****************************************************************************
 �� �� ��  : pwrctrl_debug_info_show
 ��������  : �͹��ĵ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��30��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
#if 0
s32_t pwrctrl_acpu_debug_info_show( void_t )
{
    PWC_TRACE(PWC_LOG_MAX, "\n################ A�� core0, Current slice: 0x%x ##############\n", pwrctrl_get_slice_time());
    PWC_TRACE(PWC_LOG_MAX, "˯�ߴ���: 0x%x, ���Ѵ���: 0x%x      \n", \
         g_stAcpuPwcExcLog->core0.SlpCnt, g_stAcpuPwcExcLog->core0.WkCnt);
    PWC_TRACE(PWC_LOG_MAX, "˯�߿�ʼʱ��:0x%x, ˯��ʱ��:0x%x, ����ʱ��:0x%x , ���ѽ���ʱ��:0x%x \n", \
         g_stAcpuPwcExcLog->core0.SlpMgrSTm, g_stAcpuPwcExcLog->core0.SlpSTm, \
         g_stAcpuPwcExcLog->core0.WkSTm, g_stAcpuPwcExcLog->core0.WkMgrSTm);
#ifndef WIN32
    PWC_TRACE(PWC_LOG_MAX, "Ӳ��ͶƱ״̬:0x%x, \n", \
         (((volatile ST_VOTE_HW_INFO *)g_aAcpuHwVoteBaseAddr[PWRCTRL_TELE_ACPU])->voteWakeStat));
#endif
#if 0
    PWC_TRACE(PWC_LOG_MAX, "################################ A�� core1 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�ߴ���: 0x%x, ���Ѵ���: 0x%x      \n", \
         g_stAcpuPwcExcLog->core1.SlpCnt, g_stAcpuPwcExcLog->core1.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�߿�ʼʱ��:0x%x, ˯��ʱ��:0x%x, ����ʱ��:0x%x , ���ѽ���ʱ��:0x%x \n", \
         g_stAcpuPwcExcLog->core1.SlpMgrSTm, g_stAcpuPwcExcLog->core1.SlpSTm, \
         g_stAcpuPwcExcLog->core1.WkSTm, g_stAcpuPwcExcLog->core1.WkMgrSTm, 0, 0);

    PWC_TRACE(PWC_LOG_MAX, "################################ A�� core2 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�ߴ���: 0x%x, ���Ѵ���: 0x%x      \n", \
         g_stAcpuPwcExcLog->core2.SlpCnt, g_stAcpuPwcExcLog->core2.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�߿�ʼʱ��:0x%x, ˯��ʱ��:0x%x, ����ʱ��:0x%x , ���ѽ���ʱ��:0x%x \n", \
         g_stAcpuPwcExcLog->core2.SlpMgrSTm, g_stAcpuPwcExcLog->core2.SlpSTm, \
         g_stAcpuPwcExcLog->core2.WkSTm, g_stAcpuPwcExcLog->core2.WkMgrSTm, 0, 0);

    PWC_TRACE(PWC_LOG_MAX, "################################ A�� core3 ############################\n", 0, 0, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�ߴ���: 0x%x, ���Ѵ���: 0x%x      \n", \
         g_stAcpuPwcExcLog->core3.SlpCnt, g_stAcpuPwcExcLog->core3.WkCnt, 0, 0, 0, 0);
    PWC_TRACE(PWC_LOG_MAX, "˯�߿�ʼʱ��:0x%x, ˯��ʱ��:0x%x, ����ʱ��:0x%x , ���ѽ���ʱ��:0x%x \n", \
         g_stAcpuPwcExcLog->core3.SlpMgrSTm, g_stAcpuPwcExcLog->core3.SlpSTm, \
         g_stAcpuPwcExcLog->core3.WkSTm, g_stAcpuPwcExcLog->core3.WkMgrSTm, 0, 0);
#endif

    return RET_OK;
}
#endif

extern unsigned char* g_exch_c_core_base_addr;
extern unsigned char* g_exch_m_core_base_addr;

s32_t pwrctrl_mcu_debug_info_show( void_t )
{
    int i;
    u32_t  tmp = 0;
    if(NULL == g_pPwcMcuLog)
    {
        tmp = pwrctrl_read_reg32(HISI_VA_ADDRESS(MEMORY_AXI_MCU_LOG_ADDR));
        if(tmp < MCU_DUMP_LOG_ADDR || tmp > (MCU_DUMP_LOG_ADDR + MCU_DUMP_LOG_SIZE))
        {
            return 0;
        }
        if(NULL == g_exch_m_core_base_addr)
        {
            return 0;
        }
        /*g_pPwcMcuLog = (PWC_MCU_LOG_STRU *)ioremap(tmp, sizeof(PWC_MCU_LOG_STRU));*/
        g_pPwcMcuLog = (PWC_MCU_LOG_STRU *)(tmp - MCU_DUMP_LOG_ADDR + g_exch_m_core_base_addr);

    }
    PWC_TRACE(PWC_LOG_ERROR, "######## MCU Debug Info, Current slice: 0x%x ########\r\n", pwrctrl_get_slice_time());

    PWC_TRACE(PWC_LOG_ERROR, "###### SYSTEM[%d] ###### \r\n", g_pPwcMcuLog->mcu.sX);

    for(i = 0; i < PERI_SLEEP_CUR_STATE_NUM; i++)
    {
    	PWC_TRACE(PWC_LOG_ERROR, "###### PERI[%d][%d] ###### \r\n", i,g_pPwcMcuLog->mcu.info[i].stat.sX);
    	PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         	g_pPwcMcuLog->mcu.info[i].stat.sleepCount, g_pPwcMcuLog->mcu.info[i].stat.wakeCount);
    	PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         	g_pPwcMcuLog->mcu.info[i].stat.sleepSliceTime, g_pPwcMcuLog->mcu.info[i].stat.wakeSliceTime);
    	PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, \r\n", \
         	g_pPwcMcuLog->mcu.info[i].stat.wakeSrc0, g_pPwcMcuLog->mcu.info[i].stat.wakeSrc1);
        PWC_TRACE(PWC_LOG_ERROR, "can deep sleep ret: 0x%x, hard vote:0x%x, soft vote:0x%x,\r\n", \
            g_pPwcMcuLog->mcu.info[i].notSleepReason.canSleepRet, \
            g_pPwcMcuLog->mcu.info[i].notSleepReason.HWVoteMap, \
            g_pPwcMcuLog->mcu.info[i].notSleepReason.voteMap);
        PWC_TRACE(PWC_LOG_ERROR, "vote stat:0x%x, map:0x%x, cli:0x%x, task:0x%x, slice:0x%x, \r\n", \
            g_pPwcMcuLog->vote[i].voteStat.stat, g_pPwcMcuLog->vote[i].voteStat.voteMap, \
            g_pPwcMcuLog->vote[i].voteStat.clientId, g_pPwcMcuLog->vote[i].voteStat.taskId, \
            g_pPwcMcuLog->vote[i].sliceTime);
     }

    PWC_TRACE(PWC_LOG_ERROR, "###### C core ###### \r\n");
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_pPwcMcuLog->ccpu.pdStat.sleepCount, g_pPwcMcuLog->ccpu.puStat.wakeCount);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_pPwcMcuLog->ccpu.pdSliceTime, g_pPwcMcuLog->ccpu.puSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, WFI wait fail slice:0x%x, \r\n", \
         g_pPwcMcuLog->ccpu.WFIFailStat.WFIFailCount, g_pPwcMcuLog->ccpu.WFIFailSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, IPC sta: 0x%x,\r\n", \
         g_pPwcMcuLog->ccpu.puStat.wakeSrc0, g_pPwcMcuLog->ccpu.puStat.wakeSrc1, \
         g_pPwcMcuLog->ccpu.puStat.wakeSrcIPC);
    PWC_TRACE(PWC_LOG_ERROR, "GPIO sta: (GPIO7-4)0x%08x, (GPIO3-0)0x%08x,\r\n", \
         *((u32_t*)&(g_pPwcMcuLog->ccpu.puStat.wakeSrcGPIO[4])), \
         *((u32_t*)&(g_pPwcMcuLog->ccpu.puStat.wakeSrcGPIO[0])));


    PWC_TRACE(PWC_LOG_ERROR, "###### A core ###### \r\n");
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_pPwcMcuLog->acpu.pdStat.sleepCount, g_pPwcMcuLog->acpu.puStat.wakeCount);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_pPwcMcuLog->acpu.pdSliceTime, g_pPwcMcuLog->acpu.puSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, WFI wait fail slice:0x%x, \r\n", \
         g_pPwcMcuLog->acpu.WFIFailStat.WFIFailCount, g_pPwcMcuLog->acpu.WFIFailSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, IPC sta: 0x%x, 2ndInt: 0x%x, \r\n", \
         g_pPwcMcuLog->acpu.puStat.wakeSrc0, g_pPwcMcuLog->acpu.puStat.wakeSrc1, \
         g_pPwcMcuLog->acpu.puStat.wakeSrcIPC, g_pPwcMcuLog->acpu.puStat.wake2ndInt);
    PWC_TRACE(PWC_LOG_ERROR, "GPIO sta: (GPIO7-4)0x%08x, (GPIO3-0)0x%08x,\r\n", \
         *((u32_t*)&(g_pPwcMcuLog->acpu.puStat.wakeSrcGPIO[4])), \
         *((u32_t*)&(g_pPwcMcuLog->acpu.puStat.wakeSrcGPIO[0])));


    PWC_TRACE(PWC_LOG_ERROR, "###### HIFI ###### \r\n");
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
         g_pPwcMcuLog->hifi.pdStat.sleepCount, g_pPwcMcuLog->hifi.puStat.wakeCount);
    PWC_TRACE(PWC_LOG_ERROR, "sleep slice: 0x%x, wake slice: 0x%x, \r\n", \
         g_pPwcMcuLog->hifi.pdSliceTime, g_pPwcMcuLog->hifi.puSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "WFI wait fail cnt: 0x%x, WFI wait fail slice:0x%x, \r\n", \
         g_pPwcMcuLog->hifi.WFIFailStat.WFIFailCount, g_pPwcMcuLog->hifi.WFIFailSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "wake src: 0x%x, 0x%x, IPC sta: 0x%x,\r\n", \
         g_pPwcMcuLog->hifi.puStat.wakeSrc0, g_pPwcMcuLog->hifi.puStat.wakeSrc1, \
         g_pPwcMcuLog->hifi.puStat.wakeSrcIPC);


    return RET_OK;
}

s32_t pwrctrl_ccpu_debug_info_show( void_t )
{
    u32_t  tmp = 0;
    if(NULL == g_pPwcCcpuLog)
    {
        tmp = pwrctrl_read_reg32(HISI_VA_ADDRESS(MEMORY_AXI_CCPU_LOG_ADDR));
        if(tmp < MODEM_DUMP_LOG_ADDR || tmp > (MODEM_DUMP_LOG_ADDR + MODEM_DUMP_LOG_SIZE))
        {
            return 0;
        }
        if(NULL == g_exch_c_core_base_addr)
        {
            return 0;
        }
        /*g_pPwcCcpuLog = (PWC_CCPU_LOG_STRU *)ioremap(tmp, sizeof(PWC_CCPU_LOG_STRU));*/
        g_pPwcCcpuLog = (PWC_CCPU_LOG_STRU *)(tmp - MODEM_DUMP_LOG_ADDR + g_exch_c_core_base_addr);

    }

    PWC_TRACE(PWC_LOG_ERROR, "######## CCPU Debug Info, Current slice: 0x%x ########\r\n", pwrctrl_get_slice_time());
    PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: 0x%x, wake cnt: 0x%x      \r\n", \
        g_pPwcCcpuLog->ccpu.stat.cSleepCount, g_pPwcCcpuLog->ccpu.stat.cWakeCount);
    PWC_TRACE(PWC_LOG_ERROR, "sleep start slice: 0x%x, sleep slice: 0x%x, wake slice: 0x%x, wake end slice: 0x%x, \r\n", \
        g_pPwcCcpuLog->ccpu.stat.cSleepMgrSliceTime, g_pPwcCcpuLog->ccpu.stat.cSleepSliceTime, \
        g_pPwcCcpuLog->ccpu.stat.cWakeSliceTime, g_pPwcCcpuLog->ccpu.stat.cWakeMgrSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "IPC sleep cnt: 0x%x, IPC sleep slice: 0x%x, WFI return cnt: 0x%x, WFI return slice:0x%x, \r\n", \
        g_pPwcCcpuLog->ccpu.stat.cSleepIpcCount, g_pPwcCcpuLog->ccpu.stat.cSleepIpcSliceTime, \
        g_pPwcCcpuLog->ccpu.stat.cWFIRetCount, g_pPwcCcpuLog->ccpu.stat.cWFIRetSliceTime);
    PWC_TRACE(PWC_LOG_ERROR, "can deep sleep ret: 0x%x, hard vote:0x%x, soft vote:0x%x, sch time id:0x%x, sch time val:0x%x,\r\n", \
        g_pPwcCcpuLog->ccpu.notSleepReason.canSleepRet, g_pPwcCcpuLog->ccpu.notSleepReason.HWVoteMap, \
        g_pPwcCcpuLog->ccpu.notSleepReason.voteMap, g_pPwcCcpuLog->ccpu.notSleepReason.nextSchTimeId, \
        g_pPwcCcpuLog->ccpu.notSleepReason.nextSchTimeValue);
    PWC_TRACE(PWC_LOG_ERROR, "vote stat:0x%x, map:0x%x, cli:0x%x, task:0x%x, slice:0x%x, \r\n", \
        g_pPwcCcpuLog->vote.voteStat.stat, g_pPwcCcpuLog->vote.voteStat.voteMap, \
        g_pPwcCcpuLog->vote.voteStat.clientId, g_pPwcCcpuLog->vote.voteStat.taskId, \
        g_pPwcCcpuLog->vote.sliceTime);
    return RET_OK;
}
#if 0
s32_t pwrctrl_mem_show( u32_t addr )
{
    u32_t *addrV=0;

    addrV = (u32_t *)ioremap(addr, 0x1000);

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         addr, *(addrV++), *(addrV++), *(addrV++), *(addrV++));

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x10), *(addrV++), *(addrV++), *(addrV++), *(addrV++));

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x20), *(addrV++), *(addrV++), *(addrV++), *(addrV++));

    PWC_TRACE(PWC_LOG_ERROR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x \r\n", \
         (addr+0x30), *(addrV++), *(addrV++), *(addrV++), *(addrV++));

    iounmap(addrV);

    return RET_OK;
}




void_t pwrctrl_log_mem(u8_t* info, void_t* addr, u32_t size)
{
    u32_t idx;

    if(!info || !addr)
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_log_mem: null parameters.");

        return ;
    }

    PWC_TRACE(PWC_LOG_INFO, "%s, 0x%ux, %u", info, (u32_t)addr, size);

    for(idx = 0; idx < size; idx = idx + 16)
    {
        PWC_TRACE(PWC_LOG_INFO, " 0x%.8X:  0x%.8X  0x%.8X  0x%.8X  0x%.8X ", (int)addr + idx,
            *(int*)((int)addr + idx), *(int*)((int)addr + idx + 0x4), *(int*)((int)addr + idx + 0x8), *(int*)((int)addr + idx + 0xC));
    }

}




late_initcall(pwrctrl_common_initial);
#endif
arch_initcall(pwrctrl_early_init);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

