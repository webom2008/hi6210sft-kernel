#ifndef __BSP_AO_SCTRL_H_
#define  __BSP_AO_SCTRL_H_


#if defined(BOARD_FPGA)

#include "soc_fpga_baseaddr_interface.h"
#include "soc_modem_sctrl_interface.h"



#define AOSCTRL_SC_TIMER_EN2		SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_ADDR(SOC_SC_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN3		SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_ADDR(SOC_SC_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN4		SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_ADDR(SOC_SC_BASE_ADDR)

#else
#include "soc_baseaddr_interface.h"
#if !defined(CHIP_BB_HI6758)
#include "soc_ao_sctrl_interface.h"
#endif

#if defined(CHIP_BB_HI6210)
#else
#define AOSCTRL_SC_SYS_CTRL0		SOC_AO_SCTRL_SC_SYS_CTRL0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SYS_CTRL1		SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SYS_CTRL2		SOC_AO_SCTRL_SC_SYS_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SYS_STAT0		SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SYS_STAT1		SOC_AO_SCTRL_SC_SYS_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_IMCTRL		SOC_AO_SCTRL_SC_MCU_IMCTRL_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_IMSTAT		SOC_AO_SCTRL_SC_MCU_IMSTAT_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECONDRY_INT_EN0		SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECONDRY_INT_STATR0		SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECONDRY_INT_STATM0		SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN6		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR6		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM6		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN5		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR5		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM5		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN2		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR2		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM2		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN3		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR3		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM3		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN4		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR4		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM4		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN0		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR0		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM0		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_EN1		SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATR1		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_WKUP_INT_STATM1		SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_EN_STAT		SOC_AO_SCTRL_SC_INT_EN_STAT_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_STATR		SOC_AO_SCTRL_SC_INT_STATR_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_STATM		SOC_AO_SCTRL_SC_INT_STATM_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_CLEAR		SOC_AO_SCTRL_SC_INT_CLEAR_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_EN0		SOC_AO_SCTRL_SC_INT_EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_INT_DIS0		SOC_AO_SCTRL_SC_INT_DIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_BRG_ERR_CLEAR		SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN0		SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN1		SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN2		SOC_AO_SCTRL_SC_TIMER_EN2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN3		SOC_AO_SCTRL_SC_TIMER_EN3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN4		SOC_AO_SCTRL_SC_TIMER_EN4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_TIMER_EN5		SOC_AO_SCTRL_SC_TIMER_EN5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME12		SOC_AO_SCTRL_SC_PWUP_TIME12_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME13		SOC_AO_SCTRL_SC_PWUP_TIME13_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME14		SOC_AO_SCTRL_SC_PWUP_TIME14_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME15		SOC_AO_SCTRL_SC_PWUP_TIME15_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME16		SOC_AO_SCTRL_SC_PWUP_TIME16_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME17		SOC_AO_SCTRL_SC_PWUP_TIME17_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED31		SOC_AO_SCTRL_SC_RESERVED31_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED32		SOC_AO_SCTRL_SC_RESERVED32_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED33		SOC_AO_SCTRL_SC_RESERVED33_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED34		SOC_AO_SCTRL_SC_RESERVED34_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED35		SOC_AO_SCTRL_SC_RESERVED35_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED36		SOC_AO_SCTRL_SC_RESERVED36_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED37		SOC_AO_SCTRL_SC_RESERVED37_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_RESERVED38		SOC_AO_SCTRL_SC_RESERVED38_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL0		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL1		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL2		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL3		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL4		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL5		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL6		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_CTRL7		SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT0		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT1		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT2		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT3		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT4		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT5		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT6		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_SUBSYS_STAT7		SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL0		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL1		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL2		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL3		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL4		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL5		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL6		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL7		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL8		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL9		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL10		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_CTRL11		SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT0		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT1		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT2		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT3		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT4		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT5		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT6		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ALWAYSON_SYS_STAT7		SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKEN4		SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKDIS4		SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKSTAT4		SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKEN5		SOC_AO_SCTRL_SC_PERIPH_CLKEN5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKDIS5		SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKSTAT5		SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKEN6		SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKDIS6		SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKSTAT6		SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKEN7		SOC_AO_SCTRL_SC_PERIPH_CLKEN7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKDIS7		SOC_AO_SCTRL_SC_PERIPH_CLKDIS7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_CLKSTAT7		SOC_AO_SCTRL_SC_PERIPH_CLKSTAT7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTEN4		SOC_AO_SCTRL_SC_PERIPH_RSTEN4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTDIS4		SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTSTAT4		SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTEN5		SOC_AO_SCTRL_SC_PERIPH_RSTEN5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTDIS5		SOC_AO_SCTRL_SC_PERIPH_RSTDIS5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERIPH_RSTSTAT5		SOC_AO_SCTRL_SC_PERIPH_RSTSTAT5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLKEN0		SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLKDIS0		SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLKEN1		SOC_AO_SCTRL_SC_PW_CLKEN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLKDIS1		SOC_AO_SCTRL_SC_PW_CLKDIS1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RSTEN0		SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RSTDIS0		SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RSTEN1		SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RSTDIS1		SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISOEN0		SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISODIS0		SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISOEN1		SOC_AO_SCTRL_SC_PW_ISOEN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISODIS1		SOC_AO_SCTRL_SC_PW_ISODIS1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_EN0		SOC_AO_SCTRL_SC_PW_EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_DIS0		SOC_AO_SCTRL_SC_PW_DIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_EN1		SOC_AO_SCTRL_SC_PW_EN1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_DIS1		SOC_AO_SCTRL_SC_PW_DIS1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MTCMOS_ACK_ISOEN0		SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MTCMOS_ACK_ISODIS0		SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MTCMOS_ACK_ISOSTAT0		SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_STAT0		SOC_AO_SCTRL_SC_PW_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MTCMOS_STAT0		SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MTCMOS_STAT1		SOC_AO_SCTRL_SC_MTCMOS_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLK_STAT0		SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CLK_STAT1		SOC_AO_SCTRL_SC_PW_CLK_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISO_STAT0		SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_ISO_STAT1		SOC_AO_SCTRL_SC_PW_ISO_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RST_STAT0		SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_RST_STAT1		SOC_AO_SCTRL_SC_PW_RST_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0		SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1		SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME0		SOC_AO_SCTRL_SC_PWUP_TIME0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME1		SOC_AO_SCTRL_SC_PWUP_TIME1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME2		SOC_AO_SCTRL_SC_PWUP_TIME2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME3		SOC_AO_SCTRL_SC_PWUP_TIME3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME4		SOC_AO_SCTRL_SC_PWUP_TIME4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME5		SOC_AO_SCTRL_SC_PWUP_TIME5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME6		SOC_AO_SCTRL_SC_PWUP_TIME6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME7		SOC_AO_SCTRL_SC_PWUP_TIME7_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME8		SOC_AO_SCTRL_SC_PWUP_TIME8_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME9		SOC_AO_SCTRL_SC_PWUP_TIME9_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME10		SOC_AO_SCTRL_SC_PWUP_TIME10_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PWUP_TIME11		SOC_AO_SCTRL_SC_PWUP_TIME11_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ARM_PWDN_HARDEN0		SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ARM_PWDN_HARDDIS0		SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ARM_PWDN_HARDSTAT0		SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PW_CTRL		SOC_AO_SCTRL_SC_PW_CTRL_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTEEN0		SOC_AO_SCTRL_SC_MCPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTEDIS0		SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTESTAT0		SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTE_MSK0		SOC_AO_SCTRL_SC_MCPU_VOTE_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTE_MSK1		SOC_AO_SCTRL_SC_MCPU_VOTE_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTESTAT0_MSK		SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCPU_VOTESTAT1_MSK		SOC_AO_SCTRL_SC_MCPU_VOTESTAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTEEN0		SOC_AO_SCTRL_SC_PERI_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTEDIS0		SOC_AO_SCTRL_SC_PERI_VOTEDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTESTAT0		SOC_AO_SCTRL_SC_PERI_VOTESTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTE_MSK0		SOC_AO_SCTRL_SC_PERI_VOTE_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTE_MSK1		SOC_AO_SCTRL_SC_PERI_VOTE_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTESTAT0_MSK		SOC_AO_SCTRL_SC_PERI_VOTESTAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_PERI_VOTESTAT1_MSK		SOC_AO_SCTRL_SC_PERI_VOTESTAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTEEN0		SOC_AO_SCTRL_SC_ACPU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTEDIS0		SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTESTAT0		SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTE_MSK0		SOC_AO_SCTRL_SC_ACPU_VOTE_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTE_MSK1		SOC_AO_SCTRL_SC_ACPU_VOTE_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTESTAT0_MSK		SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ACPU_VOTESTAT1_MSK		SOC_AO_SCTRL_SC_ACPU_VOTESTAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTEEN0		SOC_AO_SCTRL_SC_MCU_VOTEEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTEDIS0		SOC_AO_SCTRL_SC_MCU_VOTEDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTESTAT0		SOC_AO_SCTRL_SC_MCU_VOTESTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE_MSK0		SOC_AO_SCTRL_SC_MCU_VOTE_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE_MSK1		SOC_AO_SCTRL_SC_MCU_VOTE_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTESTAT0_MSK		SOC_AO_SCTRL_SC_MCU_VOTESTAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTESTAT1_MSK		SOC_AO_SCTRL_SC_MCU_VOTESTAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1EN0		SOC_AO_SCTRL_SC_MCU_VOTE1EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1DIS0		SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1STAT0		SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1_MSK0		SOC_AO_SCTRL_SC_MCU_VOTE1_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1_MSK1		SOC_AO_SCTRL_SC_MCU_VOTE1_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1STAT0_MSK		SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE1STAT1_MSK		SOC_AO_SCTRL_SC_MCU_VOTE1STAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2EN0		SOC_AO_SCTRL_SC_MCU_VOTE2EN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2DIS0		SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2STAT0		SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2_MSK0		SOC_AO_SCTRL_SC_MCU_VOTE2_MSK0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2_MSK1		SOC_AO_SCTRL_SC_MCU_VOTE2_MSK1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2STAT0_MSK		SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_MCU_VOTE2STAT1_MSK		SOC_AO_SCTRL_SC_MCU_VOTE2STAT1_MSK_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ECONUM		SOC_AO_SCTRL_SC_ECONUM_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCSYSID0		SOC_AO_SCTRL_SCSYSID0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCSYSID1		SOC_AO_SCTRL_SCSYSID1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCSYSID2		SOC_AO_SCTRL_SCSYSID2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCSYSID3		SOC_AO_SCTRL_SCSYSID3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCCHIPID		SOC_AO_SCTRL_SCCHIPID_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCWBBPID		SOC_AO_SCTRL_SCWBBPID_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCGBBPID		SOC_AO_SCTRL_SCGBBPID_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCSOCID		SOC_AO_SCTRL_SCSOCID_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SOC_FPGA_RTL_DEF		SOC_AO_SCTRL_SC_SOC_FPGA_RTL_DEF_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SOC_FPGA_PR_DEF		SOC_AO_SCTRL_SC_SOC_FPGA_PR_DEF_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SOC_FPGA_RES_DEF0		SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SOC_FPGA_RES_DEF1		SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCPCELLID0		SOC_AO_SCTRL_SCPCELLID0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCPCELLID1		SOC_AO_SCTRL_SCPCELLID1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCPCELLID2		SOC_AO_SCTRL_SCPCELLID2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SCPCELLID3		SOC_AO_SCTRL_SCPCELLID3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL0		SOC_AO_SCTRL_SC_XTAL_CTRL0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL1		SOC_AO_SCTRL_SC_XTAL_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL2		SOC_AO_SCTRL_SC_XTAL_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL3		SOC_AO_SCTRL_SC_XTAL_CTRL3_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL4		SOC_AO_SCTRL_SC_XTAL_CTRL4_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL5		SOC_AO_SCTRL_SC_XTAL_CTRL5_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_CTRL6		SOC_AO_SCTRL_SC_XTAL_CTRL6_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_XTAL_STAT0		SOC_AO_SCTRL_SC_XTAL_STAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_EFUSE_CHIPID0		SOC_AO_SCTRL_SC_EFUSE_CHIPID0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_EFUSE_CHIPID1		SOC_AO_SCTRL_SC_EFUSE_CHIPID1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_DEBUG_CTRL1		SOC_AO_SCTRL_SC_DEBUG_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ARM_DBG_KEY0		SOC_AO_SCTRL_SC_ARM_DBG_KEY0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_ARM_DBG_KEY1		SOC_AO_SCTRL_SC_ARM_DBG_KEY1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURE_CTRLEN0		SOC_AO_SCTRL_SC_SECURE_CTRLEN0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURE_CTRLDIS0		SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURE_CTRLSTAT0		SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURITY_CTRL0		SOC_AO_SCTRL_SC_SECURITY_CTRL0_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURITY_CTRL1		SOC_AO_SCTRL_SC_SECURITY_CTRL1_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURITY_CTRL2		SOC_AO_SCTRL_SC_SECURITY_CTRL2_ADDR(SOC_SC_ON_BASE_ADDR)
#define AOSCTRL_SC_SECURITY_CTRL3		SOC_AO_SCTRL_SC_SECURITY_CTRL3_ADDR(SOC_SC_ON_BASE_ADDR)

#endif
#endif
#endif
