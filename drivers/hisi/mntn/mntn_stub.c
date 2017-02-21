/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  mntn.c    hisi mntn driver, maintain function s when panic/freeze happens
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/notifier.h>
#include <linux/hisi/reset.h>
#include "soc_peri_sctrl_interface.h"
#include <soc_modem_sctrl_interface.h>
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include <soc_ao_sctrl_interface.h>
#include <soc_wdt_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_mddrc_axi_interface.h>
#include <linux/io.h>
#include "MemoryMap.h"
#include "rfilesystem_process.h"
#include "rfilesystem_interface.h"
#include "BSP_IPF.h"
#include "../modem_hi6xxx/icc/bsp_icc_drv.h"
#include "../ipc_hi6xxx/bsp_drv_ipc.h"
#include "bsp_mailbox.h"
#include "../usb/usb_shell.h"
#include <linux/hisi/etb.h>
#include "excDrv.h"
#include "drv_timer.h"


#if defined(FEATURE_KERNEL_LINUX_3_10)
#if 0
/*****************************************************************************
 �� �� ��  : DRV_NVE_ACCESS
 ��������  : ����NVE
 �������  : NVE
 �������  : ��
 �� �� ֵ  : BSP_OK / BSP_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : Ԭ��˳ 00167654
    �޸�����   : �����ɺ���

*****************************************************************************/
signed int DRV_NVE_ACCESS(NVE_INFO_S *nve)
{
    return 0;
}
#endif


#endif
