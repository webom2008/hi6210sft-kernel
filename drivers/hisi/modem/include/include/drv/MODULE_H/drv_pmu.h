

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_PMU_H__
#define __DRV_PMU_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*ͨ��ģ�鹩��� CONSUMER��idö��*/
typedef enum EM_MODEM_CONSUMER_ID_E
{
    CH0_PA_VCC,/* PA��VCC*/
    CH0_PA_VBIAS,/* PA��ƫ�õ�Դ*/
    CH0_SWITCH_VCC,/* ����2.8V��Դ*/
    CH0_RFIC_TX_ANA,/* RFIC TXģ���Դ*/
    CH0_RFIC_RX_ANA,/* RFIC RXģ��1.8V��Դ*/
    CH0_FEM_VIO,/*FEM��VIO��Դ1.8V*/
    CH0_TUNNER_VCC,/*ǰ��Tunner VCC��Դ*/


    CH1_PA_VCC,/*PA��VCC*/
    CH1_PA_VBIAS,/* PA��ƫ�õ�Դ*/
    CH1_SWITCH_VCC,/* ����2.8V��Դ*/
    CH1_RFIC_TX_ANA,/* RFIC TXģ���Դ*/
    CH1_RFIC_RX_ANA,/* RFIC RXģ��1.8V��Դ*/
    CH1_FEM_VIO,/*FEM��VIO��Դ1.8V*/
    CH1_TUNNER_VCC,/*ǰ��Tunner VCC��Դ*/
    CH0_RFIC_XO_2P85,
    CH1_RFIC_XO_2P85,
    /*����RF ��Դ���޸� MODEM_RF_COMSUMER_ID_BUTT*/
    MODEM_SIM0,
    MODEM_SIM1,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;

/*old consumer id,there will be rm in the future;advice to use the new consumer id*/
#define MODEM_PA0               CH0_PA_VCC
#define MODEM_PA_VBIAS0         CH0_PA_VBIAS
#define MODEM_FEM0              CH0_SWITCH_VCC
#define MODEM_RFIC0_ANALOG0     CH0_RFIC_TX_ANA
#define MODEM_RFIC0_ANALOG1     CH0_RFIC_RX_ANA

#define MODEM_PA1               CH1_PA_VCC
#define MODEM_PA_VBIAS1         CH1_PA_VBIAS
#define MODEM_FEM1              CH1_SWITCH_VCC
#define MODEM_RFIC1_ANALOG0     CH1_RFIC_TX_ANA
#define MODEM_RFIC1_ANALOG1     CH1_RFIC_RX_ANA

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : DRV_GET_PMU_STATE
 ��������  : ��ȡPMUģ�鿪����ʽ�����״̬����ص����������λ״̬��
 �������  : �ޡ�
 �������  : Pmu_State :������ʽ�����״̬����ص����������λ״̬��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
extern unsigned int DRV_GET_PMU_STATE(void*  Pmu_State);

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
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned int ulPortNum);
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
                            unsigned int *pulPortNum, unsigned int ulPortMax);
#define DRV_USB_GET_AVAILABLE_PORT_TYPE(pucPortType, pulPortNum, ulPortMax)  \
                BSP_USB_GetAvailabePortType(pucPortType, pulPortNum, ulPortMax)

/*****************************************************************************
 �� �� ��  : BSP_PMU_LDOOFF
 ��������  : ���ӿ����ڹر�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ1��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע�������LDO6��Ӳ�����ƣ������֧�ֶ�LDO6�Ĳ����������LDO1�رգ���ϵͳ��ػ���
*****************************************************************************/
extern void BSP_PMU_LDOOFF(BSP_U8 u8LDO);
#define DRV_PM_LDO_OFF(u8LDO)                 BSP_PMU_LDOOFF(u8LDO)

/*****************************************************************************
 �� �� ��  : BSP_PMU_LDOON
 ��������  : ���ӿ��������ô�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ2��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע���������֧�ֶ�LDO1��LDO6�Ĳ�����LDO1����ϵͳ����ʱ�Զ��򿪣�һ���ر�������ϵͳ���µ磻LDO6����Ӳ���ܽſ��ơ�
*****************************************************************************/
extern void BSP_PMU_LDOON(BSP_U8 u8LDO);
#define DRV_PM_LDO_ON(u8LDO)                  BSP_PMU_LDOON(u8LDO)

/************************************
�� �� ��  : BSP_PMU_AptEnable
��������  : ʹ��PMU��APT����
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_OK�����óɹ�
		����ֵ������ʧ��
**************************************/
extern BSP_S32 BSP_PMU_AptEnable(BSP_VOID);
#define DRV_PMU_APT_ENABLE()    BSP_PMU_AptEnable()

/************************************
�� �� ��  : BSP_PMU_AptDisable
��������  : ȥʹ��PMU��APT����
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_OK�����óɹ�
		����ֵ������ʧ��
**************************************/
extern BSP_S32 BSP_PMU_AptDisable(BSP_VOID);
#define DRV_PMU_APT_DISABLE()    BSP_PMU_AptDisable()

/************************************
�� �� ��  : BSP_PMU_AptIsEnable
��������  : ��ѯPMU��APT�����Ƿ�ʹ��
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_TURE��ʹ��APT
		    BSP_FALSE,δʹ��APT
**************************************/
extern BSP_BOOL  BSP_PMU_AptIsEnable(BSP_VOID);
#define DRV_PMU_APT_ISENABLE()    BSP_PMU_AptIsEnable()


/**********************************NEW PMU INTERFACE BEGIN*******************************************/

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_SET
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����(����PA��ѹ���ã�����ʹ��ö��EM_MODEM_PA_DYNAMIC_VOLTAGE_ID���)
 �������  : ��
 �� �� ֵ  : BSP_OK          ���óɹ�
             BSP_ERROR       ����ʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 voltage_mv );
/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_GET
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : BSP_OK          ��ȡ�ɹ�
             BSP_ERROR       ��ȡʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 *voltage_mv );

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_LIST
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : BSP_OK          ��ȡ�ɹ�
             BSP_ERROR       ��ȡʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,BSP_U16 **list, BSP_U32 *size);


/**********************************NEW PMU INTERFACE END*******************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_pmu.h */

