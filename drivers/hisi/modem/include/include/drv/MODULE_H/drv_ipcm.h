
#ifndef __DRV_IPCM_H__
#define __DRV_IPCM_H__
#include "drv_global.h"
#include "drv_ipc_enum.h"
#ifdef __OS_RTOSCK__

#if defined(BSP_CORE_MODEM) 
#include <sre_base.h>
#endif

#else 

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(__VXWORKS__)
#include <vxWorks.h>
#endif

#endif


#define INTSRC_NUM                     32


/*****************************************************************************
* �� �� ��  : BSP_DRV_IPCIntInit_Lt
*
* ��������  : IPCģ���ʼ��,Lģר��
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  :
*****************************************************************************/
int BSP_DRV_IPCIntInit_Lt(void);

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntEnable_Lt
*
* ��������  : ʹ��ĳ���ж�,Lģר��
*
* �������  :   IPC_INT_CORE_E enCoreNum Ҫʹ���жϵ�core
                BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :
*****************************************************************************/
int BSP_IPC_IntEnable_Lt (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 * �� �� ��  : BSP_INT_Disable_Lt
 *
 * ��������  : ȥʹ��ĳ���ж�
 *
 * �������  : IPC_INT_CORE_E enCoreNum Ҫʹ���жϵ�core
                BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  :
 *****************************************************************************/
int BSP_IPC_IntDisable_Lt (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 * �� �� ��  : BSP_IPC_IntConnect_Lt
 *
 * ��������  : ע��ĳ���ж�,Lģר��
 *
 * �������  : IPC_INT_CORE_E enCoreNum Ҫʹ���жϵ�core
               BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
               VOIDFUNCPTR routine �жϷ������
 *             BSP_U32 parameter      �жϷ���������
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  :
 *****************************************************************************/
int BSP_IPC_IntConnect_Lt(IPC_INT_LEV_E ulLvl, VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
 * �� �� ��  : BSP_IPC_IntDisonnect_Lt
 *
 * ��������  : ȡ��ע��ĳ���ж�,Lģר��
 *
 * �������  :
 *              BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
 *              VOIDFUNCPTR routine �жϷ������
 *             BSP_U32 parameter      �жϷ���������
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  :
 *****************************************************************************/
 int BSP_IPC_IntDisonnect_Lt (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);

 /*****************************************************************************
 * �� �� ��  : BSP_DRV_IpcIntHandler_Lt
 *
 * ��������  : �жϴ�����,Lģר��
 *
 * �������  : ��
 * �������  : ��
 *
 * �� �� ֵ  : ��
 *
 * �޸ļ�¼  :
 *****************************************************************************/
void BSP_DRV_IpcIntHandler_Lt(void);

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntSend_Lt
*
* ��������  : �����ж�,Lģר��
*
* �������  :
                IPC_INT_CORE_E enDstore Ҫ�����жϵ�core
                BSP_U32 ulLvl Ҫ���͵��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :
*****************************************************************************/
int BSP_IPC_IntSend_Lt(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);



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
int BSP_DRV_IPCIntInit(void);


/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMCREATE
*
* ��������  : �ź�����������
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/
int BSP_IPC_SemCreate(unsigned int u32SignalNum);
extern int DRV_IPC_SEMCREATE(unsigned int u32SignalNum);

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMDELETE
*
* ��������  : ɾ���ź���
*
* �������  :   BSP_U32 u32SignalNum Ҫɾ�����ź������

* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/
int BSP_IPC_SemDelete(unsigned int u32SignalNum);
extern int DRV_IPC_SEMDELETE(unsigned int u32SignalNum);

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
int BSP_IPC_IntEnable (IPC_INT_LEV_E ulLvl);
extern int DRV_IPC_INTENABLE(IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* �� �� ��  : DRV_IPC_INTDISABLE
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
int BSP_IPC_IntDisable (IPC_INT_LEV_E ulLvl);
extern int DRV_IPC_INTDISABLE(IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntConnect
*
* ��������  : ע��ĳ���ж�
*
* �������  :
           BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
           VOIDFUNCPTR routine �жϷ������
*             BSP_U32 parameter      �жϷ���������
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/
int BSP_IPC_IntConnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);
extern int DRV_IPC_INTCONNECT(IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntDisonnect
*
* ��������  : ȡ��ע��ĳ���ж�
*
* �������  :
*              BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
*              VOIDFUNCPTR routine �жϷ������
*             BSP_U32 parameter      �жϷ���������
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2011��4��11�� wangjing creat
*****************************************************************************/
int BSP_IPC_IntDisonnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);
extern int DRV_IPC_INTDISCONNECT  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
* �� �� ��  : DRV_IPC_INTSEND
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
int BSP_IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
extern int DRV_IPC_INTSEND(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMTAKE
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
int BSP_IPC_SemTake(unsigned int u32SignalNum,int s32timeout);
extern int DRV_IPC_SEMTAKE(unsigned int u32SignalNum, int s32timeout);

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMGIVE
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
void BSP_IPC_SemGive(unsigned int u32SignalNum);
extern void DRV_IPC_SEMGIVE(unsigned int u32SignalNum);


void BSP_IPC_SemOwner(unsigned int u32SignalNum, IPC_INT_CORE_E *coreId);

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
void BSP_IPC_SpinLock (unsigned int u32SignalNum);
extern void DRV_SPIN_LOCK (unsigned int u32SignalNum);

/*****************************************************************************
* �� �� ��  : DRV_SPIN_UNLOCK
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
void BSP_IPC_SpinUnLock (unsigned int u32SignalNum);
extern void DRV_SPIN_UNLOCK(unsigned int u32SignalNum);


int BSP_SGI_Connect(unsigned int ulLvl,VOIDFUNCPTR routine, unsigned int parameter);
int BSP_SGI_IntSend(unsigned int ulLvl);

#endif

