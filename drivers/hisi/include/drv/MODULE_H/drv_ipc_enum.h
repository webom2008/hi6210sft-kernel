/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_ipc_enum.h
  �� �� ��   : ����
  ��    ��   : ��ҫ��00179452
  ��������   : 2014��4��10��
  ����޸�   :
  ��������   : drv_ipcm.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��10��
    ��    ��   : ��ҫ��00179452
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __DRV_IPC_ENUM_H__
#define __DRV_IPC_ENUM_H__


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


    /* !!!!����Ԫ�������ӵ����  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

/*********************************************************
*  ������IPC��Դ��ö��������ʽ:
*  IPC_<Ŀ�괦����>_INT_SRC_<Դ������>_<����/����>
*  Ŀ�괦����:ACPU��CCPU��MCU��HIFI��BBE16
*  Դ������  :ACPU��CCPU��MCU��HIFI��BBE16
*  ����/���� :
*********************************************************/
typedef enum tagIPC_INT_LEV_E
{
   /* ����CCPU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_INT_DSP_MODEM                   = 0,
    IPC_CCPU_INT_SRC_HIFI_MSG           = 1,    /* bit1, HIFI�����Ϣ֪ͨ */
    IPC_INT_DSP_MSP                     = 2,
    IPC_INT_DSP_PS 						= 3,
    IPC_CCPU_INT_SRC_MCU_MSG            = 5,    /* bit5, MCU�����Ϣ֪ͨ */
    IPC_CCPU_INT_SRC_ACPU_MSG           = 6,    /* bit6, ACPU�����Ϣ֪ͨ */
    IPC_CCPU_INT_SRC_ACPU_IFC           = 7,    /* bit7, ACPU��˺�������֪ͨ */
    IPC_INT_DSP_HALT                    = 8,    /* bit8, DSP֪ͨARM˯��*/
    IPC_INT_DSP_RESUME                  = 9,    /* bit9, DSP֪ͨARM��ɻ��Ѻ�Ļָ�����*/
    IPC_CCPU_INT_SRC_MCU_IFC            = 10,   /* bit10, MCU��˺�������֪ͨ*/
    IPC_INT_WAKE_GU                     = 11,   /* bit11, ��ģ���Ѵ�ģ�ж�*/
    IPC_INT_SLEEP_GU                    = 12,   /* bit12, ��ģ˯���ж�*/
    IPC_INT_DICC_USRDATA_ACPU           = 13,   /* bit13, ռλ,��ֵ������IPC_INT_DICC_USRDATAһ��*/
    IPC_INT_DICC_RELDATA_ACPU           = 14,   /* bit14, ռλ,��ֵ������IPC_INT_DICC_USRDATAһ��*/
    IPC_INT_ARM_SLEEP                   = 15,   /* bit15, ��8�޸�Ϊ15*/
    /* ����TDSʹ�õ�����IPC�ж�,begin */
    IPC_INT_WAKE_GSM                    = 16,   /* bit16, BBE16֪ͨCCPU,����GSM��ģ */
    IPC_INT_WAKE_WCDMA                  = 17,   /* bit17, BBE16֪ͨCCPU,����WCDMA��ģ */
    IPC_INT_DSP_PS_PUB_MBX              = 18,   /* bit18, ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_INT_DSP_PS_MAC_MBX              = 19,   /* bit19, ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_INT_DSP_MBX_RSD                 = 20,   /* bit20, ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_CCPU_INT_SRC_DSP_MNTN           = 21,   /* bit21��BBE16��ά�ɲ��ж�֪ͨmailbox���޾�ǿ */
    IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX    = 22,   /* bit22*/
    /* ����TDSʹ�õ�����IPC�ж�,end */
    IPC_CCPU_INT_SRC_ACPU_ICC           = 30,   /* bit30, ACPU ICC�����Ϣ֪ͨ*/
    IPC_CCPU_INT_SRC_BUTT               = 32,

   /* ����MCU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_MCU_INT_SRC_ACPU_MSG            = 4,    /* bit4, ACPU�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_CCPU_MSG            = 5,    /* bit5, CCPU�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_HIFI_MSG            = 6,    /* bit6, HIFI�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_CCPU_IFC            = 7,    /* bit7, HIFI�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_CCPU_IPF            = 8,    /* bit8, IPF�͹��� */
    IPC_MCU_INT_SRC_ACPU_IFC            = 9,    /* bit9, ACPU��˺�������֪ͨ */
    IPC_MCU_INT_SRC_ACPU0_PD            = 10,   /* bit10, acpu0 power down */
    IPC_MCU_INT_SRC_ACPU1_PD            = 11,   /* bit11, acpu1 power down */
    IPC_MCU_INT_SRC_ACPU2_PD            = 12,   /* bit12, acpu2 power down */
    IPC_MCU_INT_SRC_ACPU3_PD            = 13,   /* bit13, acpu3 power down */
    IPC_MCU_INT_SRC_ACPU_HOTPLUG        = 14,   /* bit14, acpu hotplug--no use */
    IPC_MCU_INT_SRC_ACPU_DFS            = 15,   /* bit15, ACPU DFS*/
    IPC_MCU_INT_SRC_ACPU_PD             = 16,   /* bit16, acpu power down */
    IPC_MCU_INT_SRC_CCPU_PD             = 17,   /* bit17, ccpu power down */
    IPC_MCU_INT_SRC_HIFI_PD             = 18,   /* bit18, hifi power down */
    IPC_MCU_INT_SRC_MCU_AGT             = 19,   /* bit19, mcu agent */
    IPC_MCU_INT_SRC_HIFI_DDR_VOTE       = 20,   /* bit20, HIFI DDR��ˢ��ͶƱ */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    = 21,   /* bit21, ACPU ȫϵͳSLOW̬ǳ˯ͶƱ */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   = 22,   /* bit22, ACPU ȫϵͳTCXO�����費�µ�ǳ˯ͶƱ */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID = 23,   /* bit23, ACPU ȫϵͳǳ˯ȥͶƱ */
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_VOTE = 24,    /* bit24, MP3���͹��Ĳ���ʹ��HARQMEM,HIFI DDR��ˢ��ͶƱ*/
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_EXIT_VOTE = 25, /* bit25, MP3���͹��Ĳ���ʹ��HARQMEM,HIFIͶƱDDR�˳���ˢ��*/
    IPC_MCU_INT_SRC_ACPU4_PD            = 26,   /* bit26, acpu4:cluster1 core0 power down */
    IPC_MCU_INT_SRC_ACPU5_PD            = 27,   /* bit27, acpu5:cluster1 core1 power down */
    IPC_MCU_INT_SRC_ACPU6_PD            = 28,   /* bit28, acpu6:cluster1 core2 power down */
    IPC_MCU_INT_SRC_ACPU7_PD            = 29,   /* bit29, acpu7:cluster1 core3 power down */
    IPC_MCU_INT_SRC_HIFI_IFC            = 31,   /* bit31, HIFI��˺�������֪ͨ*/
    IPC_MCU_INT_SRC_BUTT                = 32,

    /* ����ACPU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_ACPU_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_HIFI_MSG           = 2,    /* bit2, HIFI�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_MCU_MSG            = 3,    /* bit3, ACPU�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_CCPU_NVIM          = 4,    /* bit4, ����NVIMģ��C����A��֮���ͬ��*/
    IPC_ACPU_INT_SRC_CCPU_IFC           = 5,    /* bit5, CCPU��˺�������֪ͨ  */
    IPC_ACPU_INT_SRC_MCU_IFC            = 6,    /* bit6, MCU��˺�������֪ͨ  */
    IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH   = 7,    /* bit7, MCU��طŵ���¹ػ�IPC�ж�֪ͨACPU*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_LOW    = 8,    /* bit8, MCU��طŵ���¹ػ�IPC�ж�֪ͨACPU*/
    IPC_INT_DSP_APP                     = 9,    /* bit9, LDSP���֪ͨ */
    IPC_INT_DICC_USRDATA                = 13,   /* bit13, TTF���CCPU���֪ͨ��������IPC_INT_DICC_USRDATA_ACPUͬʱ�޸�*/
    IPC_INT_DICC_RELDATA                = 14,   /* bit14, TTF���CCPU���֪ͨ��������IPC_INT_DICC_RELDATA_ACPUͬʱ�޸�*/
    IPC_ACPU_INT_SRC_CCPU_LOG = 25,   /* bit25,   CCPU���͸�ACPU��LOG�����ж�*/
    IPC_ACPU_INI_SRC_MCU_TELE_MNTN_NOTIFY    = 26,   /* bit26, TELE_MNTN����ACPU֪ͨ */
    IPC_ACPU_INI_SRC_MCU_EXC_REBOOT     = 27,   /* bit27, MCU�쳣��λ���֪ͨ */
    IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT    = 28,   /* bit28, CCPU�쳣��λ���֪ͨ */
    IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT = 29,   /* bit29, CCPU������λ���֪ͨ */
    IPC_ACPU_INT_SRC_MCU_DDR_EXC        = 30,   /* bit30, MCU DDR�쳣���֪ͨ */
    IPC_ACPU_INT_SRC_CCPU_ICC           = 31,   /* bit31, CCPU ICC�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_BUTT               = 32,


    /* ����HIFI IPC�����Ϣ�ж�Դbitλ�� */
    IPC_HIFI_INT_SRC_ACPU_MSG           = 0,    /* bit0, ACPU�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_BBE_MSG            = 4,    /* bit4, TDDSP�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_MCU_MSG            = 6,    /* bit6, MCU�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_MCU_WAKE_DDR       = 7,    /* bit7, MCU֪ͨHIFI����DDR */
    IPC_HIFI_INT_SRC_MCU_IFC            = 8,    /* bit8, MCU��˺�������֪ͨ */
    IPC_HIFI_INT_SRC_BUTT               = 32,

    /* ����BBE16 IPC�����Ϣ�ж�Դbitλ�� */
    IPC_INT_MSP_DSP_OM_MBX              = 0,   /* bit0, ����ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX              = 1,   /* bit1, ����ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX              = 2,   /* bit2, ����ARM->DSP */
    IPC_INT_HIFI_DSP_MBX                = 3,   /* bit3, HIFI->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG          = 3,   /* bit3, ����Ϊ���v7r2��v9r1�������⣬bit3ͬʱ���������� */
    IPC_BBE16_INT_SRC_BUTT              = 32,
    /* ������������� */
    IPC_INT_BUTTOM                      = 32
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
    IPC_SEM_TELE_MNTN,
    IPC_SEM_MEDPLL_STATE,
    IPC_SEM_BBPMASTER_0 = 10,
    IPC_SEM_BBPMASTER_1 = 11,
    IPC_SEM_BBPMASTER_2 = 12,
    IPC_SEM_BBPMASTER_3 = 13,
    IPC_SEM_BBPMASTER_4 = 14,
    IPC_SEM_BBPMASTER_5 = 15,
    IPC_SEM_BBPMASTER_6 = 16,
    IPC_SEM_BBPMASTER_7 = 17,
    IPC_SEM_BBPMASTER_8 = 18,
    IPC_SEM_SMP_CPU0 = 21,
    IPC_SEM_SMP_CPU1 = 22,
    IPC_SEM_SMP_CPU2 = 23,
    IPC_SEM_SMP_CPU3 = 24,
    IPC_SEM_SYNC = 25,
    IPC_SEM_BBP = 26,           /*��ֵ��BBE16����󶨣��޸���֪ͨBBE16����Ӧ�޸�*/
    IPC_SEM_CPUIDLE = 27,   /*CPUIDLE A/M�˻�����Դ��*/
	IPC_SEM_BBPPS = 28,         /*BBP PS���µ�ͶƱ*/
	IPC_SEM_HKADC = 29,     /*A��M�˶�ȡHKADC�Ļ�����*/
    IPC_SEM_SYSCTRL = 30,
    IPC_SEM_ZSP_HALT = 31,
    IPC_SEM_BUTTOM
}IPC_SEM_ID_E;


#endif
