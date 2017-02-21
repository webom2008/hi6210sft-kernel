

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "AtDataProc.h"
#include "ATCmdProc.h"
#include "AtCsdInterface.h"
#include "AtTafAgentInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_DATAPROC_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/* HiLinkģʽ: ����ģʽ������ģʽ */
AT_HILINK_MODE_ENUM_U8                  g_enHiLinkMode       = AT_HILINK_NORMAL_MODE;

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/* Э��ջ����PDP��������� */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtNdisActPdpType;

/* Э��ջ����PDP��������� */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtFirstNdisActPdpType;

/* ����NDIS���������õĲ��� */
AT_DIAL_PARAM_STRU                      gstAtNdisAddParam   = {0};

/* NDIS PDPʵ�� */
AT_PDP_ENTITY_STRU                      g_stAtNdisDhcpPara;

/* ����NDISCONN �����ʱ�Ĳ���, ����NDISCONN ��ѯ���� */
AT_NDISCONN_PARA_STRU                   g_stAtNdisConnPara;



/* Э��ջ����PDP��������� */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppActPdpType;

/* Э��ջ����PDP��������� */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppFirstActPdpType;

/* ���沦�������õĲ��� */
AT_DIAL_PARAM_STRU                      g_stAtAppDialPara       = {0};

/* APP PDPʵ�� */
AT_PDP_ENTITY_STRU                      g_stAtAppPdpEntity;

/* RA��Ϣ����ز��� */
AT_IPV6_RA_INFO_STRU                    g_stAtAppRaInfo         = {0};

/* IP*/
VOS_UINT32                              g_ulIpAddr = 0;


/*****************************************************************************
 ȫ�ֱ�����   : g_stFcIdMaptoFcPri
 ȫ�ֱ������� : ���ڱ���ָ����FC ID��Ӧ��FC Pri

1. ��    ��   : 2012��2��24��
   ��    ��   : L47619
   �޸�����   : �����ṹ��
*****************************************************************************/
AT_FCID_MAP_STRU                        g_stFcIdMaptoFcPri[FC_ID_BUTT];

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
AT_PS_RMNET_ID_TAB                      g_astPsRmNetIdTab[] = {{MODEM_ID_0, FC_ID_NIC_1, AT_PS_USER_CID_1},
                                                               {MODEM_ID_0, FC_ID_NIC_2, AT_PS_USER_CID_2},
                                                               {MODEM_ID_0, FC_ID_NIC_3, AT_PS_USER_CID_3},
                                                               {MODEM_ID_1, FC_ID_NIC_4, AT_PS_USER_CID_1},
                                                               {MODEM_ID_1, FC_ID_NIC_5, AT_PS_USER_CID_2}
                                                               };
#else
AT_PS_RMNET_ID_TAB                      g_astPsRmNetIdTab[] = {{MODEM_ID_0, FC_ID_NIC_1, AT_PS_USER_CID_1},
                                                               {MODEM_ID_0, FC_ID_NIC_2, AT_PS_USER_CID_2},
                                                               {MODEM_ID_0, FC_ID_NIC_3, AT_PS_USER_CID_3}
                                                               };

#endif

/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
/* ^DCONN�ϱ������� */
AT_PS_REPORT_CONN_RESULT_STRU           g_astAtRptConnectedResultTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC2_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC3_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC4_USER,                     AT_PS_ReportDCONN},
    {AT_APP_USER,                       AT_PS_ReportDCONN}
};

/* ^DEND�ϱ������� */
AT_PS_REPORT_END_RESULT_STRU            g_astAtRptEndedResultTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_ReportDEND},
    {AT_HSIC2_USER,                     AT_PS_ReportDEND},
    {AT_HSIC3_USER,                     AT_PS_ReportDEND},
    {AT_HSIC4_USER,                     AT_PS_ReportDEND},
    {AT_APP_USER,                       AT_PS_ReportDEND}
};


/* ���ص�ע�ᴦ�������� */
AT_PS_REG_FC_POINT_STRU                 g_astAtRegFCPointTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_RegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_RegAppFCPoint}
};


/* ���ص�ȥע�ᴦ�������� */
AT_PS_DEREG_FC_POINT_STRU               g_astAtDeRegFCPointTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_DeRegAppFCPoint}
};

AT_PS_SND_PDP_ACT_IND_STRU              g_astAtSndPdpActIndTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpActInd}
};

AT_PS_SND_PDP_DEACT_IND_STRU            g_astAtSndPdpDeActIndTab[] =
{
    /* ��ϢID */                        /* ��Ϣ�������� */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpDeactInd}
};

AT_CHDATA_RNIC_RMNET_ID_STRU            g_astAtChdataRnicRmNetIdTab[] =
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    {AT_CH_DATA_CHANNEL_ID_1, RNIC_RM_NET_ID_0, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_2, RNIC_RM_NET_ID_1, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_3, RNIC_RM_NET_ID_2, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_4, RNIC_RM_NET_ID_3, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_5, RNIC_RM_NET_ID_4, {0, 0, 0}}
#else
    {AT_CH_DATA_CHANNEL_ID_1, RNIC_RM_NET_ID_0, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_2, RNIC_RM_NET_ID_1, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_3, RNIC_RM_NET_ID_2, {0, 0, 0}}
#endif
};

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */
/*****************************************************************************
   3 ��������������
*****************************************************************************/

extern const TAF_CHAR                       *g_PppDialRateDisplay[];

#if (FEATURE_ON == FEATURE_LTE)
extern const TAF_CHAR                       *g_ucLTEDlRateDisplay[];
#endif

extern const VOS_CHAR                       *g_ucDialRateDisplayNv[];

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : AT_PS_SetPsCallErrCause
 ��������  : ����PS�򲦺Ŵ�����
 �������  : VOS_UINT16                          usClientId
             TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->enPsErrCause = enPsErrCause;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetPsCallErrCause
 ��������  : ��ѯPS�򲦺Ŵ�����
 �������  : VOS_UINT16                          usClientId
 �������  : ��
 �� �� ֵ  : TAF_PS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->enPsErrCause;
}

VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    ulAddr = *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr;

    return ulAddr;
}


/******************************************************************************
 Function:       AT_DHCPGetIPMask
 Description:    ����IP��ַ������������
 Calls:
 Data Accessed:
 Data Updated:
 Input:         TAF_UINT32 ulIpAddrHL   IP��ַ   ������
 Output:
 Return:        TAF_UINT32 ulNetMask    �������� ������
 Others:
                ��סIP��ַ��bit[0]
                ����ѭ����ȡIP��ַ��ÿ��bit��ֱ��ĳbit[x]������bit[0]
                ����������λΪ 0--xλ
  1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
)
{
    /* 11111111.11111111.11111111.11111110*/
    TAF_UINT32 ulMask    = 0xfffffffeU;
    TAF_UINT32 ulIpTemp  = ulIpAddrHL;
    TAF_UINT32 ul1stBit;

    ul1stBit = ulIpTemp & 0x00000001;

    while(0x0 != ulMask)
    {
        ulMask   = ulMask << 1;
        ulIpTemp = ulIpTemp >> 1;

        if (ul1stBit != (ulIpTemp & 0x00000001))
        {
            break;
        }
    }

    return ulMask;
}
/******************************************************************************
 Function:       AT_DHCPGetGateWay
 Description:    ����IP��ַ�����������������
 Calls:
 Data Accessed:
 Data Updated:
 Input:         VOS_UINT32 ulIpAddrHL   IP��ַ   ������
                VOS_UINT32 ulMaskHL     �������� ������
 Output:
 Return:        VOS_UINT32 ulGateWay    ���� ������
 Others:
                ����IP+���룬�������أ���IP��ͬһ���μ�?
   1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
)
{
    VOS_UINT32 ulGateWay;

    ulGateWay = 0;

    ulGateWay = (ulIpAddrHL & ulMaskHL) + 1;

    while (ulGateWay == ulIpAddrHL)
    {
        ulGateWay ++;
    };

    return ulGateWay;
}


VOS_UINT32 AT_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[4] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255") )
    {
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* ͳ��'.'�ĸ��� */
            ulDotNum++;

            continue;
        }
        else
        {
            /* ����ֱֵ�ӷ���ʧ�� */
            return VOS_ERR;
        }
    }

    /* �������3��'.'�򷵻�ʧ�� */
    if ( 3 != ulDotNum )
    {
        return VOS_ERR;
    }

    /* �������ַ���ȡֵ */
    if (ulValTmp > 255)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    PS_MEM_CPY(pucNumber, aucAddr, 4);

    return VOS_OK;
}

/******************************************************************************
 ��������: At_IPaddritoa
 ��������: ��IPV4��ַ�����ָ�ʽת�����ַ�����ʽ

 ����˵��:
   pcString [out] �ַ�����ʽ��IP��ַ,char * pcString="192.168.0.1"
   pucNumber [in] ���ָ�ʽ��IP��ַ,char pucNumber[4]={192,168,0,1};

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          ret = VOS_OK;
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        ret = VOS_ERR;
    }
    else
    {
        PS_MEM_SET(pcString, 0, TAF_MAX_IPV4_ADDR_STR_LEN);
        sprintf(astringTmp, "%d", pucNumber[0]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[1]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[2]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[3]);
        strcat(pcString, astringTmp);
    }

    return ret;
}


VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pcString, 0, TAF_MAX_IPV4_ADDR_STR_LEN);

    /* ��������ַΪ�գ��򷵻ؿ��ַ��� */
    if ((0 == pucNumber[0])
      &&(0 == pucNumber[1])
      &&(0 == pucNumber[2])
      &&(0 == pucNumber[3]))
    {
        return VOS_OK;
    }

    sprintf(astringTmp, "%d", pucNumber[0]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[1]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[2]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[3]);
    strcat(pcString, astringTmp);

    return VOS_OK;
}
VOS_UINT32 AT_Ipv6AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[TAF_IPV6_ADDR_LEN] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255.255.255.255.255.255.255.255.255.255.255.255.255") )
    {
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* ͳ��'.'�ĸ��� */
            ulDotNum++;

            continue;
        }
        else
        {
            /* ����ֱֵ�ӷ���ʧ�� */
            return VOS_ERR;
        }
    }

    /* �������3��'.'�򷵻�ʧ�� */
    if ((TAF_IPV6_ADDR_LEN - 1) != ulDotNum )
    {
        return VOS_ERR;
    }

    /* �������ַ���ȡֵ */
    if (ulValTmp > 255)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    PS_MEM_CPY(pucNumber, aucAddr, TAF_IPV6_ADDR_LEN);

    return VOS_OK;
}

/******************************************************************************
 �� �� ��  : AT_LenStr2IpAddr
 ��������  : ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ.��ȫ�̳�V100R001
 �������  : pucStr - �ַ�����ʽ��IP��ַ
 �������  : pucIpAddr - SMЭ�鶨���IP��ַ
 �� �� ֵ  : TAF_SUCCESS - ת���ɹ�
             TAF_FAILURE - ת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��23��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
)
{
    VOS_UINT8 i;
    VOS_UINT8 j;
    VOS_UINT8 ucValue;

    i                = 0;
    j                = 0;
    ucValue          = 0;

    if (0 == pucStr[0])
    {
       /*ADDR����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return AT_SUCCESS;
    }

    if (pucStr[0] == '.')
    {
        /*�����1����Ч�ַ���'.'��IP��ַ�ǷǷ���*/
        return AT_FAILURE;
    }

    for (i = 0; (i <= AT_AP_MAX_IPV4_ADDR_LEN) && (0 != pucStr[i]) ; i++)
    {
        /*�ӵ�1����Ч�ַ���ʼ���*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {
            /*����'0'-'9'���ַ��Ƿ�*/
            return AT_FAILURE;
        }
        if (pucStr[i] != '.')
        {
            /*�������Ч�ַ���ת��Ϊ����*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {
                /*�ַ���ת��Ϊ��ЧIP��λֵ*/
                ucValue = (TAF_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /*����255����*/
                return AT_FAILURE;
            }
        }
        else
        {   /*����ַ���'.'��ǰһλ��ֵ�Ѿ��������*/
            /*����ַ���'.'��ǰһλ��ֵ�Ѿ��������*/
            if (j <= 3)
            {
               /*���汾ֻ֧��IPV4��ַ*/
                pucIpAddr[j] = ucValue;
                ucValue      = 0;

                /*��ʼ��һ����Ч�ַ��εĳ����ۼ�*/
                j++;
            }
            else
            {
                /*����4��IPλ�Σ��Ƿ�*/
                return AT_FAILURE;
            }
        }
    }

    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT16                          usValue;            /*Ipv6ʮ������ת����*/
    VOS_UINT8                           ucValue;            /*Ipv4ʮ������ת����*/

    usValue                             = 0;
    ucValue                             = 0;
    j                                   = 0;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ((':' != pucStr[i]) && ('.' != pucStr[i]))
        {
            usValue <<= 4;

            if ((pucStr[i] >= '0') &&(pucStr[i] <= '9'))
            {
                /* ʮ���Ƹ�ʽת�� */
                usValue += (pucStr[i] - '0');
                ucValue  = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /* ʮ�����Ƹ�ʽת�� */
                 usValue += (pucStr[i] - 'A' + 10);
            }
        }
        else if (':' == pucStr[i])
        {
            /* IPV6ʮ������ȡ�߰�λ���� */
            pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
            j++;
            /* IPV6ʮ������ȡ�Ͱ�λ���� */
            pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
            j++;
            usValue      = 0;
        }
        else
        {
            /* IPV4ʮ����ת�� */
            pucIpAddr[j] = ucValue;
            j++;
            ucValue      = 0;
        }
    }

    /* ƥ�����һ��ת�� */
    if (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
    {
        pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
        j++;
        pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
        j++;
    }

    if (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount)
    {
        pucIpAddr[j] = ucValue;
        j++;
    }

    return;
}


VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
)
{
    VOS_UINT8                           i;

    /* ���ַ�����ѹ��λ�ÿ�ʼ˳������ƶ� */
    for (i = ucStrlen; i >= ucIdxPos; i--)
    {
        if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
        {
            pucStr[i + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
        else
        {
            pucStr[i + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
    }

    /* ����ѹ����ð�� */
    if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }
    else
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }

    return;
}


VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
)
{
    VOS_UINT32                          i;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ( (pucStr[i] < '0' || pucStr[i] > '9')
          && (pucStr[i] < 'A' || pucStr[i] > 'F')
          && ('.' != pucStr[i])
          && (':' != pucStr[i]) )
        {
            return VOS_ERR;
        }
        /* ȡ�ò���ð������λ�� */
        if ((pucStr[i -1] == ':') && (pucStr[i] == ':'))
        {
            *pucIdxPos = (VOS_UINT8)i;
        }

        /* ͳ��ð�Ÿ��� */
        if (':' == pucStr[i])
        {
            (*pucColonCount)++;
        }

        /*ͳ�Ƶ�Ÿ���*/
        if ('.' == pucStr[i])
        {
            (*pucDotCount)++;
        }
    }

    *pucStrlen = (VOS_UINT8)i;

    return VOS_OK;
}
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_UINT8                           ucColonCount;       /* �ַ�����ð�Ÿ��� */
    VOS_UINT8                           ucDotCount;         /* �ַ����е�Ÿ��� */
    VOS_UINT8                           ucStrlen;           /* �ַ������� */
    VOS_UINT8                           ucIdxPos;           /* ��Ҫ����ð�ŵ�λ�� */
    VOS_UINT8                           pucStrTmp[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    PS_MEM_CPY(pucStrTmp, pucStr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);
    ucColonCount                        = 0;
    ucDotCount                          = 0;
    ucStrlen                            = 0;
    ucIdxPos                            = 0;

    /* ����IPV6��ַ�ַ��� */
    if (VOS_OK != AT_Ipv6LenStrToAddrAccess(pucStrTmp, &ucColonCount,
                                           &ucDotCount, &ucStrlen, &ucIdxPos))
    {
        return VOS_ERR;
    }

    /* �ַ���Ϊ�շ���ʧ�� */
    if (ucStrlen == 0)
    {
        return VOS_ERR;
    }

    /* ð�Ÿ�������7���ߵ�Ÿ���������3����ʧ�� */
    if ( (ucColonCount > AT_MAX_IPV6_STR_COLON_NUM)
      || ((AT_MAX_IPV6_STR_DOT_NUM != ucDotCount) && (0 != ucDotCount)) )
    {
        return VOS_ERR;
    }

    if ( (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
      || ( (AT_MAX_IPV4V6_STR_COLON_NUM == ucColonCount)
        && (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount) ) )
    {
        /* ��ѹ����ʽ���� */
        AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, ucColonCount, ucDotCount);
    }
    else
    {
        /* ѹ����ʽ���� */
        AT_Ipv6LenStrToAddrProcCompressed(pucStrTmp, ucColonCount, ucDotCount, ucStrlen, ucIdxPos);
        if (ucDotCount != AT_MAX_IPV6_STR_DOT_NUM)
        {
            /* ��IPV4ӳ��IPV6��ַ��ʽ */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV6_STR_COLON_NUM, ucDotCount);
        }
        else
        {
            /* IPV4ӳ��IPV6��ַ��ʽ */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV4V6_STR_COLON_NUM, ucDotCount);
        }
    }

    return VOS_OK;
}
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[AT_IPV6_STR_MAX_TOKENS];
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucTokensNum;
    VOS_UINT8                           ucRadix;
    VOS_UINT32                          i;

    pucBuffer                           = aucAddrStr;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    /* ����IP�ַ�����ʽ��������, ���ö�Ӧ��ת������ */
    switch (enIpStrType)
    {
        case AT_IPV6_STR_TYPE_HEX:
            ucDelimiter = AT_IPV6_STR_DELIMITER;
            ucTokensNum = 8;
            ucRadix     = 16;
            break;

        case AT_IPV6_STR_TYPE_DEC:
            ucDelimiter = AT_IPV4_STR_DELIMITER;
            ucTokensNum = 16;
            ucRadix     = 10;
            break;

        default:
            return VOS_ERR;
    }

    /* ����IP�ַ�����ʽ��������, ��ȡ�ֶε�IP��ַ��ֵ */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        if (AT_IPV6_STR_TYPE_HEX == enIpStrType)
        {
            usAddrNum <<= 8;
            usAddrNum  |= *aucIpAddr++;
        }

        ausAddrValue[i] = usAddrNum;
    }

    /* ����IP��ַ�ֶ�, �����зָ�����ǵ�IP��ַ�ַ��� */
    for (i=0; i < ucTokensNum; i++)
    {
        pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        *pucBuffer++ = ucDelimiter;
    }

    /* ȡ�����һ���ָ���, �����ַ��������� */
    if (aucAddrStr != pucBuffer)
    {
        *(--pucBuffer) = '\0';
    }

    return VOS_OK;
}


VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
)
{
    if (usRadix == 16)
    {
        pcStr += sprintf(pcStr, "%x", usValue);
    }
    else if(usRadix == 10)
    {
        pcStr += sprintf(pcStr, "%d", usValue);
    }
    else
    {
    }

    return pcStr;
}


VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                           ucStart;
    VOS_UINT8                           ucCount;
    VOS_UINT8                           i;

    ucStart                             = 0xFF;
    ucCount                             = 0;

    for (i = 0; i < ucTokensNum - 1; i++)
    {
        if ( (0x0000 == ausAddrValue[i])
          && (0x0000 == ausAddrValue[i + 1]) )
        {
            /* ��¼��ֵ����Ϊ0��IP��ַ����ʼλ�� */
            if (0xFF == ucStart)
            {
                ucStart = i;
            }

            /* ������ֵ����Ϊ0��IP��ַ�θ��� */
            ucCount++;
        }
        else
        {
            /* ���´�ѹ����IP��ַ��λ��, �Լ�IP��ַ�θ��� */
            if (0xFF != ucStart)
            {
                if (ucCount > *pucZeroFieldCount)
                {
                    *pucZeroFieldStart = ucStart;
                    *pucZeroFieldCount = ucCount;
                }

                ucStart = 0xFF;
                ucCount = 0;
            }
        }
    }

    /* ��ֵ����Ϊ0��IP��ַ���ڽ�βʱ, ��Ҫ����һ�δ�ѹ����IP��ַ��λ��,
       �Լ�IP��ַ�θ��� */
    if (0xFF != ucStart)
    {
        if (ucCount > *pucZeroFieldCount)
        {
            *pucZeroFieldStart = ucStart;
            *pucZeroFieldCount = ucCount;
        }
    }

    return VOS_OK;
}


VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[8]; /*TAF_IPV6_STR_RFC2373_TOKENS]; */
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucRadix;
    VOS_UINT8                           ucZeroFieldStart;
    VOS_UINT8                           ucZeroFieldCount;
    VOS_UINT8                           i;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    pucBuffer                           = aucAddrStr;
    ucDelimiter                         = TAF_IPV6_STR_DELIMITER;
    ucRadix                             = 16;
    ucZeroFieldStart                    = 0xFF;
    ucZeroFieldCount                    = 0;

    /* ����IP�ַ�����ʽ��������, ��ȡ�ֶε�IP��ַ��ֵ */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        usAddrNum <<= 8;
        usAddrNum  |= *aucIpAddr++;

        ausAddrValue[i] = usAddrNum;
    }

    /* �ҳ���Ҫʹ��"::"��ʾ��IP��ַ�ε���ʼλ��  */
    AT_FindIpv6AddrZeroFieldsToBeCompressed(&ucZeroFieldStart,
                                            &ucZeroFieldCount,
                                            ausAddrValue,
                                            ucTokensNum);

    /* ����IP��ַ�ֶ�, �����зָ�����ǵ�IP��ַ�ַ��� */
    for (i=0; i < ucTokensNum; i++)
    {
        if (ucZeroFieldStart == i)
        {
            *pucBuffer++ = ucDelimiter;

            i += ucZeroFieldCount;

            /* ����ѵ�IP��ַ�ֶε����һ��, ��Ҫ����ָ��� */
            if ((ucTokensNum - 1) == i)
            {
                *pucBuffer++ = ucDelimiter;
            }
        }
        else
        {
            /* �����IP��ַ�ֶεĵ�һ��, ����Ҫ����ָ��� */
            if (0 != i)
            {
                *pucBuffer++ = ucDelimiter;
            }

            pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        }
    }

    /* �����ַ��������� */
    if (aucAddrStr != pucBuffer)
    {
        *pucBuffer = '\0';
    }

    return VOS_OK;
}
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
)
{
    VOS_UINT16                         *pusBuffer;
    VOS_UINT32                          ulCheckSum;

    pusBuffer    = (VOS_UINT16 *)pucData;
    ulCheckSum = 0;

    while (usSize > 1)
    {
        ulCheckSum += *pusBuffer++;
        usSize     -= sizeof(VOS_UINT16);
    }

    if (usSize)
    {
#if (VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER)
        ulCheckSum += *(VOS_UINT8 *)pusBuffer;
#else
        ulCheckSum += 0 | ((*(VOS_UINT8 *)pusBuffer) << 8);
#endif
    }

    ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    ulCheckSum += (ulCheckSum >> 16);

    return (VOS_UINT16)(~ulCheckSum);
}


VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
)
{
    static VOS_UINT16                   usIdentification = 0;

    /* ���ָ��Ϸ��� */
    if (VOS_NULL_PTR == pstUdpPkt)
    {
        return VOS_ERR;
    }

    /* ��дIPͷ */
    pstUdpPkt->stIpHdr.ucIpVer          = AT_IP_VERSION;
    pstUdpPkt->stIpHdr.ucIpHdrLen       = 5;
    pstUdpPkt->stIpHdr.ucServiceType    = 0x00;
    pstUdpPkt->stIpHdr.usTotalLen       = VOS_HTONS(usLen + AT_IP_HDR_LEN + AT_UDP_HDR_LEN);
    pstUdpPkt->stIpHdr.usIdentification = VOS_HTONS(usIdentification);
    pstUdpPkt->stIpHdr.usOffset         = 0;
    pstUdpPkt->stIpHdr.ucTTL            = AT_IP_DEF_TTL;
    pstUdpPkt->stIpHdr.ucProtocol       = AT_IPPROTO_UDP;
    pstUdpPkt->stIpHdr.ulSrcAddr        = VOS_HTONL(ulSrcAddr);
    pstUdpPkt->stIpHdr.ulDstAddr        = VOS_HTONL(ulDstAddr);
    pstUdpPkt->stIpHdr.usCheckSum       = AT_CalcIpHdrCRC16((VOS_UINT8 *)&pstUdpPkt->stIpHdr, AT_IP_HDR_LEN);

    /* ��дUDPͷ */
    pstUdpPkt->stUdpHdr.usSrcPort       = VOS_HTONS(usSrcPort);
    pstUdpPkt->stUdpHdr.usDstPort       = VOS_HTONS(usDstPort);
    pstUdpPkt->stUdpHdr.usLen           = VOS_HTONS(usLen + AT_UDP_HDR_LEN);
    pstUdpPkt->stUdpHdr.usChecksum      = 0;

    usIdentification++;

    return VOS_OK;
}

/******************************************************************************
 Function:       AT_DHCPCheckCfg
 Description:    ���DHCP���ò����Ƿ�Ϸ���IP��ַ��Ϊȫ0��ȫ1����
 Calls:
 Data Accessed:
 Data Updated:
 Input:         AT_AP_DHCP_SETUP_PARAM_ST *ptrDHCPCfg DHCP���ò���
 Output:
 Return:        VOS_OK      ��ȷ
                VOS_ERR     ����
 Others:        IP��ַΪ��ȫ0����ȫ1
     1.Date        : 2009-08-03-
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPCheckCfg(
    AT_DHCP_SETUP_PARAM_ST             *ptrDHCPCfg
)
{
    if ( (0 == ptrDHCPCfg->ulIPAddr)
      || (0 == (0xffffffffU - ptrDHCPCfg->ulIPAddr)) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/******************************************************************************
 �� �� ��  : AT_DHCPServerSetUp
 ��������  : ����ptrDHCPParam��������DHCP Server��״̬����ͨ��ptrDHCPConfig
                ����DHCP Server���յ�����(�����������ء������)
                ���ر�DHCP Serverʱ����������������Ϊ��
 �������  : pstEventָ��PDPȥ�����ָ��
 �������  : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP���ò���
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    ����DHCP��������
 �� �� ֵ  : VOS_OK      ��ȷ
             VOS_ERR     ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��23��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
)
{
    if (VOS_ERR == AT_DHCPCheckCfg(ptrDHCPParam))
    {
        AT_ERR_LOG("AT_DHCPServerSetUp, ERROR, DHCP Config IP Address is Error!" );
        return VOS_ERR;
    }

      /*�������롢����*/
    ptrDHCPConfig->ulIPAddr     = ptrDHCPParam->ulIPAddr;
    ptrDHCPConfig->ulSubNetMask =
      AT_DHCPGetIPMask(ptrDHCPParam->ulIPAddr);
    ptrDHCPConfig->ulGateWay    =
      AT_DHCPGetGateWay(ptrDHCPParam->ulIPAddr,ptrDHCPConfig->ulSubNetMask);
    ptrDHCPConfig->ulPrimDNS    = ptrDHCPParam->ulPrimDNS;
    ptrDHCPConfig->ulSndDNS     = ptrDHCPParam->ulSndDNS;

    return VOS_OK;
}
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
)
{
    /* ��DHCP����ת��Ϊ������ */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(pstIpv4Dhcp->ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(pstIpv4Dhcp->ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(pstIpv4Dhcp->ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(pstIpv4Dhcp->ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(pstIpv4Dhcp->ulIpv4SecDNS);

    return;
}

/******************************************************************************
 �� �� ��  : AT_AtoI
 ��������  : �ַ���ת����
 �������  : pString �ַ���
 �������  : ��
 �� �� ֵ  : ���� IP��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��23��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_UINT32  AT_AtoI(
    VOS_UINT8                         *pString
)
{
    VOS_UINT8   *pucTmp;
    VOS_UINT32   ulRet;

    pucTmp  = pString;
    ulRet   = 0;

    for (pucTmp = pString ; *pucTmp != '\0' ; pucTmp++)
    {
        /* ������,�򲻴���*/
        if ((*pucTmp < '0') || (*pucTmp > '9'))
        {
            continue;
        }

        ulRet = (ulRet * 10) + (*pucTmp - '0');
    }

    return ulRet;
}
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT32                         *ulSpeed
)
{
      VOS_UINT8 aucSpeed[AT_AP_SPEED_STRLEN + 1];

      PS_MEM_SET(aucSpeed, 0, (VOS_SIZE_T)(AT_AP_SPEED_STRLEN + 1));
      if (VOS_ERR == Taf_GetDisplayRate(usClientId, aucSpeed))
      {
          AT_ERR_LOG("AT_GetDisplayRate : ERROR : at get rate Error!");
          return VOS_ERR;
      }
      aucSpeed[AT_AP_SPEED_STRLEN] = '\0';

      *ulSpeed = AT_AtoI(aucSpeed);

      return VOS_OK;
}


VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    PS_MEM_SET(&stParam, 0, sizeof(AT_DHCP_SETUP_PARAM_ST));
    PS_MEM_SET(&stConfig, 0, sizeof(AT_DHCP_CONFIG_STRU));

    /* ���PS�¼���DNS��ַ�����¼DNS��ַ*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* ��¼IP��ַ*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_CtrlConnIndProc : ERROR AT_DHCPServerSetUp Error!" );

        return;
    }
    else
    {
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if (AT_NDIS_USER == ucUserType)
        {
            AT_NdisAddrProc(&stConfig, pstEvent);
        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        if (AT_APP_USER == ucUserType)
        {
            AT_AppPdpAddrProc(&g_stAtAppPdpEntity, &stConfig, pstEvent);
        }

        /* ɾ��AT_USBCOM_USER������֧ */
    }

    return;
}
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *ucSpeed
)
{
    VOS_UINT32                          ulTmp = 0;
    PPP_RATE_DISPLAY_ENUM_UINT32        enRateDisplay;
    VOS_UINT32                          ulNvDialRateIndex;
    VOS_UINT8                           ucSubSysMode;
    VOS_UINT8                           aucDialRateTmp[AT_AP_RATE_STRLEN];
    TAF_AGENT_SYS_MODE_STRU             stSysMode;
    VOS_UINT32                          ulRet;

    /* ������ʼ�� */
    PS_MEM_SET(&stSysMode, 0, sizeof(stSysMode));

    /* ��C�˻�ȡucRatType��ucSysSubMode */
    ulRet = TAF_AGENT_GetSysMode(usClientId, &stSysMode);

    if (VOS_OK != ulRet)
    {
        stSysMode.enRatType     = TAF_PH_RAT_GSM;
        stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_BUTT;
    }

    ucSubSysMode = stSysMode.enSysSubMode;
    switch(ucSubSysMode)
    {
        case TAF_SYS_SUBMODE_GSM:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;

            break;

        case TAF_SYS_SUBMODE_EDGE:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucEdgeConnectRate;
            break;

        case TAF_SYS_SUBMODE_WCDMA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucWcdmaConnectRate;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucDpaConnectRate;
            break;

        default:
            ulNvDialRateIndex = 0;
            break;
    }

    if ((0 == ulNvDialRateIndex) || (ulNvDialRateIndex > 6))
    {
        if (TAF_PH_RAT_WCDMA == stSysMode.enRatType)
        {
            enRateDisplay = AT_GetRateDisplayIndexForWcdma(&g_stAtDlRateCategory);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);

        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (TAF_PH_RAT_LTE == stSysMode.enRatType)
        {
            enRateDisplay = AT_GetRateDisplayIndexForLTE(&g_stAtDlRateCategory);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_ucLTEDlRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_ucLTEDlRateDisplay[enRateDisplay], ulTmp);
        }
#endif
        else
        {
            enRateDisplay = AT_GetRateDisplayIndexForGsm(&stSysMode);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);
        }
    }
    else
    {
        ulTmp = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
        VOS_MemCpy(aucDialRateTmp, g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulTmp);
    }

    /*��CONNECT����������Ϣ*/
    PS_MEM_CPY(ucSpeed, aucDialRateTmp, (VOS_UINT16)ulTmp);
    ucSpeed[ulTmp] = '\0';

    return VOS_OK;
}


VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    VOS_UINT32                          ulRet;

    PS_MEM_SET((VOS_VOID *)pstPdpPrimContextExt, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstPdpPrimContextExt->bitOpPdpType      = VOS_TRUE;
    pstPdpPrimContextExt->bitOpPdpDcomp     = VOS_FALSE;
    pstPdpPrimContextExt->bitOpPdpHcomp     = VOS_FALSE;
    pstPdpPrimContextExt->enPdpType         = pstDialParam->enPdpType;
    pstPdpPrimContextExt->ucCid             = pstDialParam->ucCid;

    /* ��ȡAPN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPdpPrimContextExt->bitOpApn      = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)pstPdpPrimContextExt->aucApn,
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /* ��ȡ��̬IP��ַ��AT������PDP���ͣ�APS��Ҫ���ǣ���IPV6������̬IP��ַ */
    if (VOS_TRUE == pstDialParam->ulIPv4ValidFlag )
    {
        ulRet = AT_LenStr2IpAddr(pstDialParam->aucIPv4Addr,pstPdpPrimContextExt->stPdpAddr.aucIpv4Addr);
        if (AT_SUCCESS == ulRet )
        {
            pstPdpPrimContextExt->bitOpPdpAddr        = VOS_TRUE;
            pstPdpPrimContextExt->stPdpAddr.enPdpType = TAF_PDP_IPV4;
        }
    }
}


VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    PS_MEM_SET((VOS_VOID *)pstPsDialParam, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstPsDialParam->enPdpType       = pstDialParam->enPdpType;
    pstPsDialParam->ucCid           = pstDialParam->ucCid;

    /* ��ȡAPN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPsDialParam->bitOpApn        = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)pstPsDialParam->aucApn,
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /* ������֤��Ϣ */
    pstPsDialParam->bitOpAuthType   = VOS_TRUE;
    pstPsDialParam->enAuthType      = (PPP_AUTH_TYPE_ENUM_UINT8)pstDialParam->usAuthType;

    if (0 != pstDialParam->usPasswordLen)
    {
        pstPsDialParam->bitOpPassWord = VOS_TRUE;
        PS_MEM_CPY((VOS_VOID *)pstPsDialParam->aucPassWord,
                   (VOS_VOID *)pstDialParam->aucPassword,
                   pstDialParam->usPasswordLen);
    }
    else
    {
        pstPsDialParam->bitOpPassWord = VOS_FALSE;
    }

    if (0 != pstDialParam->usUsernameLen)
    {
        pstPsDialParam->bitOpUserName = VOS_TRUE;
        PS_MEM_CPY((VOS_VOID *)pstPsDialParam->aucUserName,
                   (VOS_VOID *)pstDialParam->aucUsername,
                   pstDialParam->usUsernameLen);
    }
    else
    {
        pstPsDialParam->bitOpUserName = VOS_FALSE;
    }

}


/*****************************************************************************
 �� �� ��  : AT_GetFcPriFromMap
 ��������  : ��ȡָ��FC ID��FC PRI
 �������  : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��18��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
)
{
    if (enFcId >= FC_ID_BUTT)
    {
        return VOS_ERR;
    }

    if ((FC_ID_MODEM == enFcId)
     || (FC_ID_NIC_1 == enFcId)
     || (FC_ID_NIC_2 == enFcId)
     || (FC_ID_NIC_3 == enFcId)
     || (FC_ID_NIC_4 == enFcId)
     || (FC_ID_NIC_5 == enFcId)
     || (FC_ID_DIPC_1 == enFcId)
     || (FC_ID_DIPC_2 == enFcId)
     || (FC_ID_DIPC_3 == enFcId))
    {
        pstFcIdMap->ulUsed  = g_stFcIdMaptoFcPri[enFcId].ulUsed;
        pstFcIdMap->enFcPri = g_stFcIdMaptoFcPri[enFcId].enFcPri;

        return VOS_OK;
    }

    return VOS_ERR;
}





VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    AT_FCID_MAP_STRU                    stFCPriOrg;

    if (VOS_OK == AT_GetFcPriFromMap(enFcId, &stFCPriOrg))
    {
        if (TAF_USED == pstEvent->bitOpUmtsQos)
        {
            enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
        }
        else
        {
            enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
        }

        if ( (VOS_TRUE == stFCPriOrg.ulUsed)
           && (enFCPriCurrent > stFCPriOrg.enFcPri))
        {
            /* ���ݷ���QOS���ı����ص�����ȼ�*/
            AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent,enFcId);
        }
    }

    return;
}



/***************************************************************************
               ���´���ʵ��NDIS��ع���
*****************************************************************************/
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

VOS_UINT8* AT_PutNetworkAddr32(
  VOS_UINT8                            *pucAddr,
  VOS_UINT32                            ulAddr
)
{
    *pucAddr = (ulAddr >> 24);
    pucAddr++;

    *pucAddr = ((ulAddr >> 16) & 0xFF);
    pucAddr++;

    *pucAddr = ((ulAddr >> 8) & 0xFF);
    pucAddr++;

    *pucAddr = (ulAddr & 0xFF);
    pucAddr++;

    return pucAddr;
}


VOS_UINT32 AT_CovertArrayToU32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    pucAddr += 4;

    pucAddr--;
    ulAddr = *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    return ulAddr;
}


VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT32                          ul3gppSmCause;

    if ( (enCause >= TAF_PS_CAUSE_SM_NW_SECTION_BEGIN)
      && (enCause <= TAF_PS_CAUSE_SM_NW_SECTION_END) )
    {
        ul3gppSmCause = enCause - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    /* E5�����翨��PDP DEACTIVEʱ�ϱ������36��ԭ��ֵ */
    else if (TAF_PS_CAUSE_SUCCESS == enCause)
    {
        ul3gppSmCause = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    else
    {
        ul3gppSmCause = AT_NDISSTAT_ERR_UNKNOWN;
    }

    return ul3gppSmCause;
}
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
)
{
    AT_NDISCONN_PARA_STRU               *pstNdisDailPara;
    VOS_UINT16                          usStrLen;

    pstNdisDailPara = AT_GetNdisConnParaAddr();

    PS_MEM_SET(pstNdisDailPara, 0x00, sizeof(AT_NDISCONN_PARA_STRU));

    pstNdisDailPara->ulConnectState = pstParaList[AT_NDIS_CONN_IDX].ulParaValue;
    pstNdisDailPara->ucCID = (VOS_UINT8)pstParaList[AT_NDIS_CID_IDX].ulParaValue;

    usStrLen = pstParaList[AT_NDIS_APN_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_APN_LEN )
    {
        usStrLen = TAF_MAX_APN_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucAPN,
               (VOS_CHAR*)pstParaList[AT_NDIS_APN_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_NAME_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_USERNAME_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_USERNAME_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucUsername,
               (VOS_CHAR*)pstParaList[AT_NDIS_NAME_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_PWD_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_PASSWORD_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_PASSWORD_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucPassword,
               (VOS_CHAR*)pstParaList[AT_NDIS_PWD_IDX].aucPara, usStrLen);

    pstNdisDailPara->usAuthType = AT_CtrlGetPDPAuthType(pstParaList[AT_NDIS_AUTH_IDX].ulParaValue,
                                                        pstParaList[AT_NDIS_AUTH_IDX].usParaLen);
}
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
)
{
    /* Modified by l60609 for PS Project, 2011-12-21, Begin */
    AT_NDIS_PDNINFO_REL_REQ_STRU        stNdisRelReq;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SendNdisRelReq:Get Modem Id fail");
        return VOS_ERR;
    }

    /* ������Ϣ */
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, Begin */
    stNdisRelReq.enModemId = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, End */
    stNdisRelReq.ucRabId   = pstEvent->ucRabId;

    /* Modified by l60609 for PS Project, 2011-12-21, End */


    /* ������Ϣ */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_REL_REQ,
                                            sizeof(AT_NDIS_PDNINFO_REL_REQ_STRU),
                                            (VOS_UINT8*)&stNdisRelReq))
    {
        AT_ERR_LOG("GUAT_SendNdisRelReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_ActiveUsbNet(VOS_VOID)
{
    VOS_UINT32                      ulLinkstus;
    VOS_INT32                       lRtn;
    NCM_IOCTL_CONNECTION_SPEED_S    stNcmConnectSpeed;
    VOS_UINT32                      ulSpeed;
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    {
        AT_ERR_LOG("AT_ActiveUsbNet : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }
    stNcmConnectSpeed.u32DownBitRate   = ulSpeed;
    stNcmConnectSpeed.u32UpBitRate     = ulSpeed;

    lRtn        = udi_ioctl(g_ulAtUdiNdisHdl, NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, (VOS_VOID *)(&stNcmConnectSpeed));
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Ctrl Speed Fail!" );
        return VOS_ERR;
    }

    ulLinkstus  = NCM_IOCTL_CONNECTION_LINKUP;
    lRtn        = udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, &ulLinkstus);
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Active usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID)
{
    VOS_UINT32  ulLinkstus;
    VOS_INT32   lRtn;

    /*ȥ����Ѻ�BSPȷ�ϣ����������ȥ�����ȥ���û��Ӱ��*/
    ulLinkstus = NCM_IOCTL_CONNECTION_LINKDOWN;

    lRtn  = udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, (VOS_VOID*)(&ulLinkstus));
    if(0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Deactive usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_SendNdisIPv4PdnInfoCfgReq(
    MN_CLIENT_ID_T                      usClientId,
    AT_IPV4_DHCP_PARAM_STRU            *pstIPv4DhcpParam
)
{
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    VOS_UINT32                          ulSpeed;
    VOS_UINT32                          ulRelt;

    /* ��ʼ�� */
    PS_MEM_SET(&stNdisCfgReq, 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));
    stNdisCfgReq.enModemId              = MODEM_ID_0;

    ulRelt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)usClientId, &stNdisCfgReq.enModemId);

    if (VOS_OK != ulRelt)
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq:Get Modem Id fail");
        return VOS_ERR;
    }

    stNdisCfgReq.bitOpIpv4PdnInfo       = VOS_TRUE;
    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;

    /* ������Ϣ */
    if (0 != pstIPv4DhcpParam->ucRabId )
    {
        stNdisCfgReq.ucRabId = pstIPv4DhcpParam->ucRabId;
    }

    /* ��дIPv4��ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4Addr)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPdnAddr     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPDNAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4Addr);
    }

    /* ��д�����ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4NetMask)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stSubnetMask.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4NetMask);
    }

    /* ��д���ص�ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4GateWay)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stGateWayAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4GateWay);
    }

    /* ��д��DNS��ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsPrim     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimDNS);

    }

    /* ��д��DNS��ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4SecDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsSec      = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsSecAddrInfo.aucIpV4Addr,
                          pstIPv4DhcpParam->ulIpv4SecDNS);

    }

    /* ��д��WINS��ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsPrim    = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimWINNS);
    }

    /* ��д��WINS��ַ */
    if (0 != pstIPv4DhcpParam->ulIpv4SecWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsSec     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4SecWINNS);
    }

    /* ��д��PCSCF��ַ */
    if (VOS_TRUE == pstIPv4DhcpParam->bitOpIpv4PriPCSCF)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfPrim   = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimPCSCF);
    }

    /* ��д��PCSCF��ַ */
    if (VOS_TRUE == pstIPv4DhcpParam->bitOpIpv4Secpcscf)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfSec    = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4SecPCSCF);
    }

    /* ��ȡ�������۴���*/
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }

    stNdisCfgReq.ulMaxRxbps                 = ulSpeed;
    stNdisCfgReq.ulMaxTxbps                 = ulSpeed;

    /* ������Ϣ */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
)
{
    if (AT_NDIS_PDNCFG_CNF_FAIL == pstNdisPdnInfoCfgCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
)
{
    if (AT_NDIS_SUCC != pstNdisPdnInfoRelCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}



#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_NdisConfigIpv6Dns(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    NCM_IPV6DNS_S                       stIPv6Dns;
    VOS_INT32                           lRslt;

    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();

    stIPv6Dns.pu8Ipv6DnsInfo = (BSP_U8*)PS_MEM_ALLOC(
                                    WUEPS_PID_AT,
                                    BSP_NCM_IPV6_DNS_LEN);

    if (VOS_NULL_PTR == stIPv6Dns.pu8Ipv6DnsInfo)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns:Invalid stIPv6Dns.pu8Ipv6DnsInfo");
        return;
    }

    PS_MEM_SET(stIPv6Dns.pu8Ipv6DnsInfo, 0x00, BSP_NCM_IPV6_DNS_LEN);

    /* �ϱ���������DNS���ȹ̶�Ϊ32(Primary DNS LEN + Secondary DNS LEN) */
    stIPv6Dns.u32Length = BSP_NCM_IPV6_DNS_LEN;

    /*�����DNS����Ҫ����DRV�Ľӿ��ϱ�DNS��PC*/
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        PS_MEM_CPY(stIPv6Dns.pu8Ipv6DnsInfo,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        PS_MEM_CPY(stIPv6Dns.pu8Ipv6DnsInfo + AT_MAX_IPV6_DNS_LEN,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    /* ���õ�������DNS��Ϣ */
    lRslt = DRV_UDI_IOCTL(g_ulAtUdiNdisHdl, NCM_IOCTL_SET_IPV6_DNS, &stIPv6Dns);
    if (0 != lRslt)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns, DRV_UDI_IOCTL Fail!" );
    }

    /* �ͷ�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, stIPv6Dns.pu8Ipv6DnsInfo);

}
VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    /* ����ԭ��ֵ��ԭ��ֵΪ52����Ҫ������һ��PDP���� */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
            {
                /* ����һ��δ�����CID���м��� */
                ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV4))
            {
                /* ����һ��δ�����CID���м��� */
                ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                }
            }
        }
        else
        {
            ;
        }

        return;
    }
    /* ����ԭ��ֵ, ֪ͨAPP���Ž�� */
    switch (pstEvent->enCause)
    {
        /* ԭ��ֵ#50 (IPv4 ONLY), ֪ͨAPPģ��IPv6����ʧ�� */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
            AT_NdisStateChangeProc(TAF_PDP_IPV6, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* ԭ��ֵ#51 (IPv6 ONLY), ֪ͨAPPģ��IPv4����ʧ�� */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
            AT_NdisStateChangeProc(TAF_PDP_IPV4, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* ����ԭ��ֵ, ������ */
        default:
            AT_NORM_LOG1("AT_NdisActCnfBackProc: Other <Cause>", pstEvent->enCause);
            break;
    }

    return;
}
VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    /* ��ʼ�� */
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv6Cid   = pstEvent->ucCid;

    /* ����IPV6��ַ */
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDIS�û����͵�PDP�����,�������ص�ע����� */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDIS�û����͵�PDP�����, ��������SharePdp״̬*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV6);

    /* ͨ�������ϱ�IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    /* �����IPV4V6����Ҫ������һ��PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            case TAF_PDP_IPV6:
                /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
                   IPV6��PDP����, IPV6������ٷ���IPV4��PDP���� */
                break;

            /* ������PDP������˹���ʵ�� */
            case TAF_PDP_IPV4V6:
                /* ����PDP�л���IDLE̬ */
               AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

               AT_NdisActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_NdisIpv6ActCnfProc:g_enAtNdisActPdpType is error!");
               break;
        }
    }

    return;
}


VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           aucIpv6Dns[AT_MAX_IPV6_DNS_LEN * 2];

    /* ��ʼ�� */
    PS_MEM_SET(aucIpv6Dns, 0x00, sizeof(aucIpv6Dns));

    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv4v6Cid   = pstEvent->ucCid;

    /* ����IPV4���͵�DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* ����IPV6��ַ*/
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDIS�û����͵�PDP״̬�ı��,�������ص�ע����� */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* ��IPV4��PDN��Ϣ���͸�NDISģ�� */
    AT_SendNdisIPv4PdnInfoCfgReq(pstEvent->stCtrl.usClientId,
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));


    /* NDIS�û����͵�PDP�����, ��������SharePdp״̬*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4V6);

    /* ֪ͨNDIS PDP����ɹ�,ipv6��PDN��Ϣ���յ�RA����ʱ���� */

    /* ͨ�������ϱ�IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    return;
}


VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
    MODEM_ID_ENUM_UINT16                 enModemId,
    TAF_PS_IPV6_INFO_IND_STRU           *pIPv6RaNotify
)
{
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    VOS_UINT32                          ulSpeed;
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;

    /* ��ʼ�� */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    PS_MEM_SET(&stNdisCfgReq, 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));

    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;
    stNdisCfgReq.bitOpIpv6PdnInfo       = VOS_TRUE;
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, Begin */
    stNdisCfgReq.enModemId              = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, End */
    stNdisCfgReq.ucRabId                = pIPv6RaNotify->ucRabId;

    /* �������DNS */
    stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum    = 0;
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucPriServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucSecServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    /* ���MTU */
    if (VOS_TRUE == pIPv6RaNotify->stIpv6RaInfo.bitOpMtu)
    {
        stNdisCfgReq.stIpv6PdnInfo.ulBitOpMtu   = VOS_TRUE;
        stNdisCfgReq.stIpv6PdnInfo.ulMtu        = pIPv6RaNotify->stIpv6RaInfo.ulMtu;
    }

    stNdisCfgReq.stIpv6PdnInfo.ulBitCurHopLimit = pIPv6RaNotify->stIpv6RaInfo.ulBitCurHopLimit;
    stNdisCfgReq.stIpv6PdnInfo.ulBitM           = pIPv6RaNotify->stIpv6RaInfo.ulBitM;
    stNdisCfgReq.stIpv6PdnInfo.ulBitO           = pIPv6RaNotify->stIpv6RaInfo.ulBitO;
    stNdisCfgReq.stIpv6PdnInfo.ulPrefixNum      = pIPv6RaNotify->stIpv6RaInfo.ulPrefixNum;
    PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.astPrefixList,
                (VOS_VOID *)pIPv6RaNotify->stIpv6RaInfo.astPrefixList,
                sizeof(TAF_PDP_IPV6_PREFIX_STRU)*TAF_MAX_PREFIX_NUM_IN_RA);

    /* ��дINTERFACE��ȡIPV6��ַ�ĺ�8�ֽ�����дINTERFACE */
    PS_MEM_CPY((VOS_VOID*)stNdisCfgReq.stIpv6PdnInfo.aucInterfaceId,
               (VOS_VOID*)pstNdisPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                sizeof(VOS_UINT8)*AT_NDIS_IPV6_IFID_LENGTH);

    /* �������PCSCF��ַ  */
    stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum      = 0;
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum += 1;
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucPriServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                    sizeof(pstNdisPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr));
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum += 1;
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucSecServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                    sizeof(pstNdisPdpEntity->stIpv6Dhcp.aucSecPcscfAddr));
    }

    /* ��ȡ�������۴���*/
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }

    stNdisCfgReq.ulMaxRxbps                 = ulSpeed;
    stNdisCfgReq.ulMaxTxbps                 = ulSpeed;

    /* ������Ϣ */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    g_stAtNdisDhcpPara.stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* ����IPV6��IP��ַ����ʽΪ������ */
    PS_MEM_CPY(g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* ����IPV6������DNS��ַ����ʽΪ������ */
    AT_SaveIPv6Dns(pstEvent, &g_stAtNdisDhcpPara);

    /* ����IPV6������PCSCF��ַ����ʽΪ������ */
    AT_SaveIPv6Pcscf(pstEvent, &g_stAtNdisDhcpPara);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_NdisIpv6DhcpRest
 ��������  : ���IPV6��ַ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��9��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID)
{
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    return;
}


VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 AT_NdisCheckPdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_NdisCheckPdpIdleState
 ��������  : �����Ƿ���idel��deacting��PDP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��18��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID)
{
    /*������е�PDP������IDLE;�����һ������DEACTINGҲ����OK*/
    if ( (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv6State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID  AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
)
{
    VOS_UINT32                          ulIpAddr;

    g_stAtNdisDhcpPara.stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr              = pstConfig->ulIPAddr;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay           = pstConfig->ulGateWay;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask           = pstConfig->ulSubNetMask;


    /* ����û���������DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulPrimDNS )
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS   = pstConfig->ulPrimDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* ����û������˸�DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulSndDNS)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = pstConfig->ulSndDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    /* ����û���������WINS����ʹ���û����õ�WINS�����緵�ص�WINS��ʹ�� */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_FALSE;
    }

    /* ����û������˸�WINS����ʹ���û����õ�WINS�����緵�ص�WINS��ʹ�� */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_FALSE;
    }

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriPCSCF = VOS_TRUE;
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimPCSCF   = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4Secpcscf = VOS_TRUE;
    }

    return;
}


VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATUS_ENUM_UINT32           enStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
#if(FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";
#endif

    VOS_UINT32                          ul3gppSmCause;

    usLength = 0;

    if (AT_PDP_STATUS_DEACT == enStat)
    {
        ul3gppSmCause = AT_Get3gppSmCauseByPsCause(enCause);

        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

#if(FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:

                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;
#endif

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }
    else
    {
        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

#if(FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:
                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;
#endif

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }

    At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_NdisGetState
 ��������  : ��ȡNDIS״̬������̬/�Ǽ���̬
 �������  : ucPdpType --- PDP����
 �������  : ��
 �� �� ֵ  : AT_PDP_STATE_ENUM_U8 ��ǰ״̬ ����̬/�Ǽ���̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��3��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucPdpType
)
{
    if (TAF_PDP_IPV4 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv4State;
    }
    else if (TAF_PDP_IPV6 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv6State;
    }
    else
    {
        return g_stAtNdisDhcpPara.enIpv4v6State;
    }
}


VOS_VOID AT_NdisSetState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enState
)
{
    if (TAF_PDP_IPV4 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4State   = enState;
    }
/* Modified by s62952 for AT Project��2011-10-17,  Begin*/
#if(FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv6State   = enState;
    }
    else if (TAF_PDP_IPV4V6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4v6State = enState;
    }
    else
    {}


#endif
/* Modified by s62952 for AT Project��2011-10-17,  Begin*/

    return;
}

/*****************************************************************************
 �� �� ��  : AT_NdisDhcpRest
 ��������  : ���DHCP����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��9��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_NdisDhcpRest(VOS_VOID)
{
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv4Dhcp,
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_E5GetDhcpPara
 ��������  : ��ȡDHCP����(DHCP����Ϊ������)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��10��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
)
{
    /* ��DHCP����ת��Ϊ������ */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS);
    return;
}
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8               enPdpType
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisDeRegFCPoint:Get Modem Id fail");
        return;
    }

    /* ȥע��NDIS�˿ڵ����ص� */
    AT_DeRegNdisFCPoint(pstEvent->ucRabId, enModemId);

}
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulRet;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisRegFCPoint:Get Modem Id fail");
        return;
    }

    ulRet = AT_GetFcPriFromMap(FC_ID_NIC_1 ,&stFCPriOrg);
    if (VOS_OK == ulRet)
    {
        /* ���FC IDδע�ᣬ��ôע������ص㡣Ŀǰֻ֧��һ������.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* ע��NDIS�˿ڵ����ص� */
            AT_RegNdisFCPoint(pstEvent, FC_ID_NIC_1, enModemId);
        }
        else
        {
            if (TAF_USED == pstEvent->bitOpUmtsQos)
            {
                enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
            }
            else
            {
                enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
            }

            /* �����ǰFC���ȼ���֮ǰ���ص�FC���ȼ��ߣ���ô�������ȼ���*/
            if(enFCPriCurrent > stFCPriOrg.enFcPri)
            {
                AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent, FC_ID_NIC_1);
            }
        }
    }

}
VOS_VOID  AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;
#endif

    g_stAtNdisDhcpPara.ucIpv4Cid = pstEvent->ucCid;

    /* ����IPV4���͵�DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* NDIS�û����͵�PDP״̬�ı��,�������ص�ע����� */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* ��IPV4��PDN��Ϣ���͸�NDISģ�� */
    AT_SendNdisIPv4PdnInfoCfgReq(pstEvent->stCtrl.usClientId,
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));

    /* NDIS�û����͵�PDP�����, ��������SharePdp״̬ */
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����IPV4V6����Ҫ������һ��PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
               IPV6��PDP������У�TAF_PDP_IPV6���쳣������û�����IPV6��PDP
               ���������ظ�IPV4�ļ����ʱҲ��Ҫ���·���IPV6��PDP���� */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
                {
                    /* ����һ��δ�����CID���м��� */
                    ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* ������PDP������˹���ʵ�� */
            case TAF_PDP_IPV4V6:
                /* ����PDP�л���IDLE̬ */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_NdisIpv4ActCnfProc:g_enAtNdisActPdpType is error!");
                break;
        }
    }
#endif

    return;
}
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /*��������*/
    AT_ActiveUsbNet();

    /* ֪ͨPC���� */
    AT_NdisStateChangeProc(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED, TAF_PS_CAUSE_SUCCESS);

    /* ����PDP ����״̬�л���act̬ */
    AT_NdisSetState(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED);

    /* ����PDP���ͷֱ���*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            AT_NdisIpv4ActCnfProc(pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_NdisIpv6ActCnfProc(pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_NdisIpv4v6ActCnfProc(pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_NdisPsRspPdpActEvtCnfProc:pdp type invaild!");
            break;
    }

    return;
}


VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;

    PS_MEM_SET(&stDialParaInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* ����QOS���� */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_NDIS_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,&gstAtNdisAddParam);
    stDialParaInfo.ucCid        = ucCid;
    stDialParaInfo.enPdpType    = ucPdpType;

    /* ����PDP���� */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stDialParaInfo))
    {
        if (TAF_PDP_IPV4 == stDialParaInfo.enPdpType)
        {
            g_stAtNdisDhcpPara.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtNdisDhcpPara.ucIpv6Cid = ucCid;
        }

        g_enAtNdisActPdpType = ucPdpType;

        AT_NdisSetState(ucPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}



VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    /* ��ʼ�� */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    enPreIpv4State = pstNdisPdpEntity->enIpv4State;

    /* �����IPV4 ONLY��IPV6 ONLYֱ���ϱ�����ʧ�ܡ�IPV4V6
       ����Ҫ�Ӿ���ʵ�ֱַ���IPv4��IPv6���͵�PDP���� */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        if (TAF_PDP_IPV4V6 == g_enAtNdisActPdpType)
        {
            /* �����������Ҫ�ֱ���IPv4��IPv6��PDP���� */
            if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
            {
                /* �����𲦺ŵ�PDPtype״̬�л���IDLE */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
            }
            else
            {
                /* ����PDP�л���IDLE̬ */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                /* ֪ͨPDP����ʧ�� */
                AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

                /* ���NDIS���Ų��� */
                PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else if ( TAF_PDP_IPV4 == g_enAtNdisActPdpType )
        {
            /* �û�����IPv4v6���͵�PDP����, ���ұ�����ܾ�, ԭ��Ϊ28, Э��ջ��Ҫ
               �ֱ���IPv4/IPv6���͵�PDP����, Э��ջ���ȷ���IPv4, �ٷ���IPv6,
               ���IPV4���͵�PDP�����ٴα�����ܾ�, Э��ջ����Ҫ����IPV6���͵�
               PDP����Ϊ�˷�ֹPDP����Ƕ��, ���IPv6���͵�PDP����ʧ��, �����ٳ���
               IPv4���͵�PDP���� */
            AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

            /* ֪ͨPDP����ʧ�� */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            if ( (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
              && (AT_PDP_STATE_ACTING == enPreIpv4State) )
            {
                /* ���IPv6�����Ƿ��Ѿ�����, ���������, ����IPv6���͵�PDP���� */
                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);
            }
            else
            {
                /* ���NDIS���Ų��� */
                PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else
        {
            /* ���IPv6����, �Ͳ���Ҫ�ٳ���IPv4, ��Ϊǰ���Ѿ������IPv4���͵�PDP
               ����, ����ٷ���IPv4���͵�PDP����Ļ�, ���ܻᵼ��PDP����Ƕ�� */
             AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

             /* ֪ͨPDP����ʧ�� */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

             /* ���NDIS���Ų��� */
             PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
        }
    }
    else
    {
        /* ����PDP�л���IDLE̬ */
        AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

        /* ֪ͨPDP����ʧ�� */
        AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

        /* ���NDIS���Ų��� */
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enState;
#endif

    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);
    AT_NdisDhcpRest();

    /* NDIS�û����͵�PDP״̬�ı��Ĵ������� */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* NDIS�û����͵�PDPȥ�����, ����ȥ����SharePdp״̬*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* �������һ��PDP�����ڼ���״̬����Ҫ����ȥ���� */
    enState = AT_NdisGetState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         pstEvent->stCtrl.usClientId,
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv6Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID AT_NdisIPv6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enState;

    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    AT_NdisIpv6DhcpRest();

    /* NDIS�û����͵�PDP״̬�ı��Ĵ������� */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDIS�û����͵�PDPȥ�����, ����ȥ����SharePdp״̬*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV6);

    /*�������һ��PDP�����ڼ���״̬����Ҫ����ȥ����*/
    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         pstEvent->stCtrl.usClientId,
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv4Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV4,AT_PDP_STATE_DEACTING);
        }
    }
}
VOS_VOID AT_NdisIPv4v6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_NdisDhcpRest();

    AT_NdisIpv6DhcpRest();

    /* NDIS�û����͵�PDP״̬�ı��Ĵ������� */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* NDIS�û����͵�PDPȥ�����, ����ȥ����SharePdp״̬*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4V6);
}
#endif


VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* ֪ͨPCȥ���� */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* ֪ͨTTFȥ������Ӧ��RAB */
    AT_SendNdisRelReq(pstEvent);

    /* �л�NDIS״̬��IDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
#endif
    else
    {
        ;
    }

    /* ���NDIS���Ų��� */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /* ֪ͨ����ȥ���� */
    AT_DeActiveUsbNet();

    return;
}
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{

    /* �ϱ�^NDISSTATָʾNDIS״̬ */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* ֪ͨTTFȥ������Ӧ��RAB */
    AT_SendNdisRelReq(pstEvent);

    /* �л�NDIS״̬��IDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
#endif
    else
    {
        ;
    }

    /* ���NDIS���Ų��� */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /* ֪ͨ����ȥ���� */
    AT_DeActiveUsbNet();

    return;
}
VOS_UINT32 AT_EnableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* ͨ��udi_ioctl����ʹ������ */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_ENABLE;

    if (0 != udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_DisableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* ͨ��udi_ioctl����ȥʹ������ */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_DISABLE;

    if (0 != udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-17, Begin */
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    /* ����ͨ����RABIDӳ���ϵ */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* ����������������ȼ�RAB QoS���ȼ�������,���ȼ��ı�ʱ����Ҫ�ı����ȼ� */
    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */

    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.pClrFunc           = AT_DisableNdisFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableNdisFlowCtl;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.ulParam1           = (VOS_UINT32)pstEvent->stCtrl.usClientId;

    /* ע�����ص�,��Ҫ�ֱ�ע��MEM,CPU,CDS��GPRS�� */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-12-17, End */

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = enFCPri;
    /* ��һ�������϶��RABID�������������Ҫ�����RABID��¼���� */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = enModemId;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}
VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;

    /* �ڵ���FC_DeRegPointǰ,�ȵ���FC_ChannelMapDelete */
    FC_ChannelMapDelete(ucRabId, enModemId);

    /* ĿǰNDISֻ֧��һ������ */
    enFcId = FC_ID_NIC_1;

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegNdisFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = FC_PRI_BUTT;
    /* ��һ�������϶��RABID�������������Ҫ����Ӧ��RABID��������� */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = MODEM_ID_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint(AT_CLIENT_TAB_NDIS_INDEX, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulHostOutTimeout;

    /* ��ȡ�ϲ�Խ�Ӧ������: MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulHostOutTimeout   = pstFcDrvAssemPara->ucHostOutTimeout;


    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        /* ����HOST�����ʱ�� */
        if (VOS_OK != DRV_UDI_IOCTL(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_ACCUMULATION_TIME,
                                    (VOS_VOID*)&ulHostOutTimeout))
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set host out timeout failed.");

            return VOS_ERR;
        }

    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        if (VOS_OK != USB_ETH_DrvSetHostAssembleParam(ulHostOutTimeout) )
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthHostAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulEthTxMinNum;
    VOS_UINT32                          ulEthTxTimeout;
    VOS_UINT32                          ulEthRxMinNum;
    VOS_UINT32                          ulEthRxTimeout;

    /* ��ȡ�ϲ�Խ�Ӧ������: MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulEthTxMinNum      = pstFcDrvAssemPara->ucEthTxMinNum;
    ulEthTxTimeout     = pstFcDrvAssemPara->ucEthTxTimeout;
    ulEthRxMinNum      = pstFcDrvAssemPara->ucEthRxMinNum;
    ulEthRxTimeout     = pstFcDrvAssemPara->ucEthRxTimeout;

    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        if (VOS_OK != DRV_UDI_IOCTL(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_MIN_NUM,
                                    (VOS_VOID*)&ulEthTxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != DRV_UDI_IOCTL(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_TIMEOUT,
                                    (VOS_VOID*)&ulEthTxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx timeout failed.");

            return VOS_ERR;
        }

        if (VOS_OK != DRV_UDI_IOCTL(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_MIN_NUM,
                                    (VOS_VOID*)&ulEthRxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != DRV_UDI_IOCTL(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_TIMEOUT,
                                    (VOS_VOID*)&ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx timeout failed.");

            return VOS_ERR;
        }
    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        if (VOS_OK != USB_ETH_DrvSetDeviceAssembleParam(ulEthTxMinNum,
                                                        ulEthTxTimeout,
                                                        ulEthRxMinNum,
                                                        ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthDeviceAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUsrIndex;

    if (VOS_TRUE == AT_CheckNdisUser(ucIndex))
    {
        enUsrIndex = ucIndex;
    }
    else
    {
        enUsrIndex = AT_CLIENT_TAB_NDIS_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUsrIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUsrIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}



/***************************************************************************
               ���´���ʵ��APP��ع���
*****************************************************************************/

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
)
{
    VOS_UINT16                         *pausAddr;
    VOS_UINT8                           aucLanAddr[AT_MAC_LEN] = { 0x58, 0x2C, 0x80, 0x13, 0x92, 0x08 };

    if ( (ulIpv6LanAddrLen < TAF_IPV6_ADDR_LEN )
      || (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN) )
    {
        return VOS_ERR;
    }

    pausAddr = (VOS_UINT16 *)pucIpv6LanAddr;

    /* ����IPv6��ַǰ׺ */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    /*--------------------------------------------------------------
       MAC��ַ���ɽӿ�ID����16λ��0xFFFE����MAC��ַ�м�
       MAC��ַǰ24λ + 0xFFFE + MAC��ַ��24λ
       �ٽ�U/Lλ(ȫ��/���ص�ַ,MAC��ַ����ֽڵĵ�һλ)ȡ��
    --------------------------------------------------------------*/
    pausAddr[4] = ((VOS_UINT16 *)aucLanAddr)[0] ^ VOS_HTONS(0x0200);
    pausAddr[5] = VOS_HTONS(0x00ff) | ((VOS_UINT16 *)aucLanAddr)[1];
    pausAddr[6] = VOS_HTONS(0xfe00) | (((VOS_UINT16 *)aucLanAddr)[1] & VOS_HTONS(0x00ff));
    pausAddr[7] = ((VOS_UINT16 *)aucLanAddr)[2];

    return VOS_OK;
}


VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    /* ��ȫ�ֵ�ַת��Ϊѹ����ʽ */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucLanAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    /* �ϱ�LANȫ�ֵ�ַ */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APLANADDR: \"%s\",%d%s",
                                      gaucAtCrLf,
                                      aucIpv6AddrStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}


VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT8                           aucPrefixStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucTokensNum;

    /* ��ǰ׺ת����ѹ����ʽ */
    ucTokensNum = TAF_IPV6_STR_RFC2373_TOKENS;
    AT_ConvertIpv6AddrToCompressedStr(aucPrefixStr, aucPrefix, ucTokensNum);

    /* �ϱ�^APPREFIX: <PrefixAddr> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFIX: \"%s/%d\"%s",
                                      gaucAtCrLf,
                                      aucPrefixStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}


VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
)
{
    VOS_UINT16                          usLength;

    /* �ϱ�^APPREFERREDLIFETIME: <PreferredLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFERREDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulPrefixPreferredLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
)
{
    VOS_UINT16                          usLength;

    /* �ϱ�^APVALIDLIFETIME: <ValidLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APVALIDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulValidLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
)
{
    VOS_UINT16                          usLength;

    /* �ϱ�^IPV6MTU: <MTU> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6MTU: %d%s",
                                      gaucAtCrLf,
                                      ulMtu,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucStatus;

    ucStatus                            = 1;

    /* �ϱ�^APIPV6ENABLE: <status> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6ENABLE: %d%s",
                                      gaucAtCrLf,
                                      ucStatus,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}


VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_AppProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* ��ȡ��IPv6��ַǰ׺��, �ϱ������ӽ��^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* ֪ͨAPPģ��IPv6���ųɹ� */
        AT_AppSndCallConnectedResult(pstRaInfoNotifyInd->ucCid, TAF_PDP_IPV6);
    }

    /* ��¼IPv6ǰ׺ */
    pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
    pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
    PS_MEM_CPY(pstAppRaInfoAddr->aucPrefixAddr,
               pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
               TAF_IPV6_ADDR_LEN);

    /* ��¼Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* ��¼Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* ��¼IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* ����IPv6ȫ�ֵ�ַ */
    AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                     pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                     aucIpv6LanAddr,
                                     TAF_IPV6_ADDR_LEN);

    /* ��¼IPv6ȫ�ֵ�ַ */
    pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
    PS_MEM_CPY(pstAppRaInfoAddr->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* ����DHCPV6��Ϣ�е�IPv6ȫ�ֵ�ַ */
    PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* �����ϱ�IPV6��ַǰ׺ */
    AT_AppRcvIpv6Prefix(pstAppRaInfoAddr->aucPrefixAddr, pstAppRaInfoAddr->ulPrefixBitLen);

    /* �����ϱ�ǰ׺����ʹ�������� */
    AT_AppRcvPrefixIpv6PreferredLifetime(pstAppRaInfoAddr->ulPreferredLifetime);

    /* �����ϱ�ǰ׺��Ч������ */
    AT_AppRcvPrefixIpv6ValidLifetime(pstAppRaInfoAddr->ulValidLifetime);

    /* �����ϱ�IPV6ȫ�ֵ�ַ */
    AT_AppRcvIpv6LanAddr(pstAppRaInfoAddr->aucLanAddr, TAF_IPV6_ADDR_LEN, pstAppRaInfoAddr->ulPrefixBitLen);

    /* ֪ͨAPP�����µ�IPV6ǰ׺ */
    AT_AppRcvEnableIpv6Prefix();

    return;
}


VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    pstAppPdpEntity->stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* ����IPv6��IP��ַ����ʽΪ������ */
    if (TAF_PDP_IPV6 == (pstEvent->stPdpAddr.enPdpType & TAF_PDP_IPV6))
    {
        PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   pstEvent->stPdpAddr.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* ����IPV6������DNS��ַ����ʽΪ������ */
    AT_SaveIPv6Dns(pstEvent, pstAppPdpEntity);

    /* ����IPV6������PCSCF��ַ����ʽΪ������ */
    AT_SaveIPv6Pcscf(pstEvent, pstAppPdpEntity);

    return;
}
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pucAppRaInfoAddr;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pucAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    PS_MEM_SET(&pstAppPdpEntity->stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    PS_MEM_SET(pucAppRaInfoAddr,
               0x00,
               sizeof(AT_IPV6_RA_INFO_STRU));

    return;
}
#endif


VOS_VOID AT_AppDhcpReset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    PS_MEM_SET(&pstAppPdpEntity->stIpv4Dhcp,
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}


VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;
    VOS_UINT32                          ulIpAddr;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();
    ulIpAddr                            = 0;

    pstAppPdpEntity->stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* ����û���������DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucPrimIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* ����û������˸�DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == pstAppDialPara->ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucSndIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriPCSCF = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimPCSCF   = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4Secpcscf = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
    }

    return;
}

/* �������ܻ�ʹ�� */
#if 0
VOS_VOID AT_AppPsRecoverState(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV4))
    {
         /* ֪ͨ������ADS PDP ȥ���� */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL,VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL,VOS_NULL_PTR);

         /* ֪ͨRNIC PDPȥ����ɹ� */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv4Cid, RNIC_RM_NET_ID_0);
    }

    /* ���IPV4/V6��DHCP��Ϣ */
    AT_AppDhcpReset();

    /* �����е�PDP_TYPE״̬����ΪIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV6))
    {
         /* ֪ͨ������ADS PDP ȥ���� */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL, VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL, VOS_NULL_PTR);

         /* ֪ͨRNIC PDPȥ����ɹ� */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv6Cid, RNIC_RM_NET_ID_0);
    }

    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV4V6))
    {
        /* ֪ͨ������ADS PDP ȥ���� */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4v6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL, VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4v6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL, VOS_NULL_PTR);

         /* ֪ͨRNIC PDPȥ����ɹ� */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv4v6Cid, RNIC_RM_NET_ID_0);
    }

    AT_AppDhcpv6Reset();
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);
#endif

    return;
}
#endif


VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* ������е�PDP������IDLE, �����һ������DEACTIVATINGҲ����TRUE */
    if ( (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv6State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv4State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv6State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


AT_PDP_STATE_ENUM_U8 AT_AppGetPdpStateByCid(
    VOS_UINT8                           ucCid
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if (ucCid == pstAppPdpEntity->ucIpv4Cid)
    {
        return pstAppPdpEntity->enIpv4State;
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (ucCid == pstAppPdpEntity->ucIpv6Cid)
    {
        return pstAppPdpEntity->enIpv6State;
    }
    else if (ucCid == pstAppPdpEntity->ucIpv4v6Cid)
    {
        return pstAppPdpEntity->enIpv4v6State;
    }
#endif
    else
    {
        return AT_PDP_STATE_IDLE;
    }
}


AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstAppPdpEntity->enIpv4State;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            enPdpState = pstAppPdpEntity->enIpv6State;
            break;

        case TAF_PDP_IPV4V6:
            enPdpState = pstAppPdpEntity->enIpv4v6State;
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppGetPdpState:ERROR: PDP type is invalid!");
            enPdpState = AT_PDP_STATE_IDLE;
            break;
    }

    return enPdpState;
}


VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            pstAppPdpEntity->enIpv4State    = enPdpState;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstAppPdpEntity->enIpv6State    = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstAppPdpEntity->enIpv4v6State  = enPdpState;
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSetPdpState:ERROR: PDP type is invalid!");
            break;
    }

    return;
}


VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSndConnectResult: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}


VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSndCallEndedResult: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}


VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* ����AT_RNIC_IPV4_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* ��д��Ϣ�� */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    /* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
    pstMsg->ucRmNetId       = ucRmNetId;
    /* Added by l60609 for DSDA Phase II, 2012-12-18, End */
    pstMsg->ulIpv4Addr      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulNetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulGateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulPrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulSecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulPrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulSecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    /* ����AT_NDIS_IPV6_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /* ��д��Ϣ�� */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv6Dhcp.ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    PS_MEM_CPY(pstMsg->aucIpv6Addr,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    PS_MEM_CPY(pstMsg->aucPrimDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    PS_MEM_CPY(pstMsg->aucSecDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU      *pstMsg;

    /* ����AT_NDIS_IPV6_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV4V6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;

    /* ��д��Ϣ�� */
    pstMsg->ucRabId             = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    pstMsg->ucRmNetId           = ucRmNetId;
    pstMsg->ulIpv4Addr          = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulIPv4NetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulIPv4GateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_IPv4PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_IPv4SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_IPv4PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_IPv4SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulIPv4PrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulIPv4SecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulIPv4PrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulIPv4SecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    pstMsg->OP_IPv6PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_IPv6SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    PS_MEM_CPY(pstMsg->aucIpv6Addr,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    PS_MEM_CPY(pstMsg->aucIpv6PrimDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    PS_MEM_CPY(pstMsg->aucIpv6SecDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif


VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulResult;

    /* ֪ͨRNIC PDP����ɹ� */
    if ( TAF_PDP_IPV4== enPdpType )
    {
        AT_SendRnicIpv4ActInd(RNIC_RM_NET_ID_0);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    if ( TAF_PDP_IPV6== enPdpType )
    {
        AT_SendRnicIpv6ActInd(RNIC_RM_NET_ID_0);
    }

    if ( TAF_PDP_IPV4V6== enPdpType )
    {
        ulResult = AT_SendRnicIpv4v6ActInd(RNIC_RM_NET_ID_0);
        if (VOS_OK != ulResult)
        {
            AT_ERR_LOG("AT_AppSndRnicPdpActInd: ERROR: Send Rnic Ipv4 Act Ind To Rnic Failed.");
        }
    }
#endif
    return;
}

/*****************************************************************************
�� �� ��  : AT_SendRnicPdpDeactInd
��������  : APP�˿ڲ���ʱ֪ͨ��������
�������  : VOS_UINT8                           ucRabId
            VOS_UINT8                           ucRmNetId
�������  : ��
�� �� ֵ  : �ɹ�
            ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��18��
   ��    ��   : S62952
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;

    /* ����AT_NDIS_PDP_DEACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /* ��д��Ϣ�� */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;

    AT_GetPdpContextFromAtDialParam(&stPdpPrimContextExt,AT_APP_GetDailParaAddr());
    stPdpPrimContextExt.enPdpType   = enPdpType;
    stPdpPrimContextExt.ucCid       = ucCid;

    /* ����QOS���� */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_APP_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,AT_APP_GetDailParaAddr());
    stDialParaInfo.enPdpType    = enPdpType;
    stDialParaInfo.ucCid        = ucCid;

    /* ����PDP���� */
    if ( VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stDialParaInfo) )
    {
        if (TAF_PDP_IPV4 == enPdpType)
        {
            g_stAtAppPdpEntity.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtAppPdpEntity.ucIpv6Cid = ucCid;
        }

        AT_APP_SetActPdpType(enPdpType);

        AT_AppSetPdpState(enPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}


VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    /* APP����Ĭ��ʹ��NDIS����1�����ص� */
    enDefaultFcId = FC_ID_NIC_1;

    ulResult = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulResult)
    {
        /* ���FC IDδע�ᣬ��ôע������ص㡣Ŀǰֻ֧��һ������.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* ע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, RNIC_RM_NET_ID_0);
        }
        else
        {
            /* APP����ֻʹ����͵�����QOS���ȼ�FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppRegFCPoint: No need to change the default QOS priority.");
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF = VOS_FALSE;

    /* ����IPV6����PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* ����IPV6�ĸ�PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
}

VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns    = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns    = VOS_FALSE;

    /* ��������DNS���յ�RA����ʱ��Ҫ����������ʱ��Ҫ֪ͨDRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns = VOS_TRUE;
    }

}
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    /* ����ԭ��ֵ��ԭ��ֵΪ52����Ҫ������һ��PDP���� */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
            {
                /* ����һ��δ�����CID���м��� */
                ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV4))
            {
                /* ����һ��δ�����CID���м��� */
                ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                }
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        /* ����ԭ��ֵ, ֪ͨAPP���Ž�� */
        switch (pstEvent->enCause)
        {
            /* ԭ��ֵ#50 (IPv4 ONLY), ֪ͨAPPģ��IPv6����ʧ�� */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:

                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV6);

                break;

            /* ԭ��ֵ#51 (IPv6 ONLY), ֪ͨAPPģ��IPv4����ʧ�� */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:

                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV4);

                break;

            /* ����ԭ��ֵ, ������ */
            default:
                AT_NORM_LOG1("AT_AppActCnfBackProc: Other <Cause>", pstEvent->enCause);
                break;
        }
    }

    return;
}
#endif
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
 #if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;
#endif

    /* ���DHCP��Ϣ */
    AT_AppDhcpReset();

    /* ��¼IPv4����PDP��Ӧ��CID */
    pstAppPdpEntity->ucIpv4Cid          = pstEvent->ucCid;

    /* ����IPv4����PDP״̬�л�������״̬ */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* ����IPv4���͵�DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* ֪ͨAPPģ��IPv4���� */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /* ע�����ص� */
    AT_ProcAppRegFCPoint(pstEvent);

    /* �ϱ�RNIC������Ϣ */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����IPV4V6����Ҫ������һ��PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
               IPV6��PDP������У�TAF_PDP_IPV6���쳣������û�����IPV6��PDP
               ���������ظ�IPV4�ļ����ʱҲ��Ҫ���·���IPV6��PDP���� */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
                {
                    /* ����һ��δ�����CID���м��� */
                    ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* ������PDP������˹���ʵ�� */
            case TAF_PDP_IPV4V6:
                /* ����PDP�л���IDLE̬ */
                AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

                AT_AppActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_AppIpv4ActCnfProc:WARNING: PDP type is invalid!");
                break;
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* ���DHCPv6��Ϣ */
    AT_AppDhcpv6Reset();

    /* ��¼PDP���Ͷ�Ӧ��CID */
    pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

    /* ����IPv6����״̬�л�������״̬ */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* ����IPV6��ַ */
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* IPv6���͵ļ���ָʾ��Ҫ�ڻ�ȡRA��Ϣ���ϱ� */

    /* ע�����ص� */
    AT_ProcAppRegFCPoint(pstEvent);

    /* �ϱ�RNIC������Ϣ */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV6);

    /* �����IPV4V6����Ҫ������һ��PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            case TAF_PDP_IPV6:
                /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
                   IPV6��PDP����, IPV6������ٷ���IPV4��PDP���� */
                break;

            /* ������PDP������˹���ʵ�� */
            case TAF_PDP_IPV4V6:
                /* ����PDP�л���IDLE̬ */
               AT_AppSetPdpState(AT_APP_GetActPdpType(), AT_PDP_STATE_IDLE);

               AT_AppActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_AppIpv6ActCnfProc: PDP type is invalid!");
               break;
        }
    }

    return;
}


VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* ���DHCP��Ϣ */
    AT_AppDhcpReset();

    /* ���DHCPv6��Ϣ */
    AT_AppDhcpv6Reset();

    /* ��¼PDP���Ͷ�Ӧ��CID */
    pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

    /* ����IPv6����״̬�л�������״̬ */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* ����IPV4��ַ */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* ����IPV6��ַ*/
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* ֪ͨAPPģ��IPv4����, IPv6���͵ļ���ָʾ��Ҫ�ڻ�ȡRA��Ϣ���ϱ� */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /* ע�����ص� */
    AT_ProcAppRegFCPoint(pstEvent);

    /* �ϱ�RNIC������Ϣ */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4V6);

    return;
}
#endif
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enPdpState;
#endif

    /* ��IPv4���͵�PDP�л���IDLE̬ */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* ���DHCP��Ϣ */
    AT_AppDhcpReset();

    /* ֪ͨAPPģ��IPv4�Ͽ� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* ֪ͨRNIC PDPȥ����ɹ� */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RM_NET_ID_0);

    /* ȥע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);

#if (FEATURE_ON == FEATURE_IPV6)
   /* ���IPv4���͵�PDP�����ڼ���״̬, ��Ҫ����ȥ���� */
    enPdpState = AT_AppGetPdpState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      pstEvent->stCtrl.usClientId,
                                      0,
                                      pstAppPdpEntity->ucIpv6Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv4DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPdpState;

    /* ��IPv6���͵�PDP�л���IDLE̬ */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* ���DHCPv6��Ϣ */
    AT_AppDhcpv6Reset();

    /* ֪ͨAPPģ��IPv6�Ͽ� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* ֪ͨRNIC PDPȥ����ɹ� */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RM_NET_ID_0);

    /* ȥע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);

    /* ���IPv4���͵�PDP�����ڼ���״̬, ��Ҫ����ȥ���� */
    enPdpState = AT_AppGetPdpState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      pstEvent->stCtrl.usClientId,
                                      0,
                                      pstAppPdpEntity->ucIpv4Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv6DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
}


VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* ��IPv6���͵�PDP�л���IDLE̬ */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* ���DHCP��Ϣ */
    AT_AppDhcpReset();

    /* ���DHCPv6��Ϣ */
    AT_AppDhcpv6Reset();

    /* ֪ͨAPPģ��IPv4�Ͽ� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* ֪ͨAPPģ��IPv6�Ͽ� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* ֪ͨRNIC PDPȥ����ɹ� */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RM_NET_ID_0);

    /* ȥע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);

    return;
}
#endif
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    enPreIpv4State = pstAppPdpEntity->enIpv4State;

    /* �û�����IPv4v6���͵�PDP����, ���ұ�����ܾ�, ԭ��Ϊ28, Э��ջ��Ҫ
       �ֱ���IPv4/IPv6���͵�PDP����, Э��ջ���ȷ���IPv4, �ٷ���IPv6,
       ���IPv4���͵�PDP�����ٴα�����ܾ�, Э��ջ����Ҫ����IPV6���͵�
       PDP����Ϊ�˷�ֹPDP����Ƕ��, ���IPv6���͵�PDP����ʧ��, �����ٳ���
       IPv4���͵�PDP���� */

    /* ��IPv4���͵�PDP״̬�л���IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv4����ʧ�� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);
#if (FEATURE_ON == FEATURE_IPV6)
    if ((TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
     && (AT_PDP_STATE_ACTING == enPreIpv4State) )
    {
        /* ���IPv6�����Ƿ��Ѿ�����, ���������, ����IPv6���͵�PDP���� */
        if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
        {
            /* ����IPv6���͵�PDP�������� */
            AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);

            /* ������Ų����Ĵ�����Ҫ�����һ��PDP�������̽�����, �˴�ֱ�ӷ��� */
            return;
        }

        /* ������Ų����Ĵ�����Ҫ�����һ��PDP�������̽�����, �˴�ֱ�ӷ��� */
        return;
    }
#endif

    /* ������Ų��� */
    PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* ���IPv6����, �Ͳ���Ҫ�ٳ���IPv4, ��Ϊǰ���Ѿ������IPv4���͵�PDP
       ����, ����ٷ���IPv4���͵�PDP����Ļ�, ���ܻᵼ��PDP����Ƕ�� */

    /* ��IPv6���͵�PDP״̬�л���IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv6����ʧ�� */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* ������Ų��� */
    PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* ��IPv4v6���͵�PDP״̬�л���IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* �����������Ҫ�ֱ���IPv4��IPv6��PDP���� */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
    {
        /* ����IPv4���͵�PDP���� */
        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
    }
    else
    {
        /* �ϱ�IPv4����ʧ�� */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV4);

        /* �ϱ�IPv6����ʧ�� */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV6);

        /* ������Ų��� */
        PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}
#endif
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* ����PDP���ͷֱ���*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            /* ����IPv4��PDP����ɹ��¼� */
            AT_AppIpv4PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ����IPv6��PDP����ɹ��¼� */
            AT_AppIpv6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* ����IPv4v6��PDP����ɹ��¼� */
            AT_AppIpv4v6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpActEvtCnfProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}


VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (AT_APP_GetActPdpType())
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspEvtPdpActRejProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}


VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /* ������Ų��� */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        PS_MEM_SET(pstAppDialPara, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /* ���APP���Ų��� */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        PS_MEM_SET(pstAppDialPara, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StartFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StopFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enDefaultFcPri;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* ����ͨ����RABIDӳ���ϵ */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    /* ����������������ȼ�RAB QoS���ȼ�������,���ȼ��ı�ʱ����Ҫ�ı����ȼ� */
    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */
    enDefaultFcPri          = FC_PRI_FOR_PDN_LOWEST;
    stRegFcPoint.enFcId     = enFcId;
    stRegFcPoint.enFcPri    = enDefaultFcPri;

    stRegFcPoint.enModemId  = enModemId;
    stRegFcPoint.pClrFunc   = AT_AppClearFlowCtrl;
    stRegFcPoint.pSetFunc   = AT_AppSetFlowCtrl;

    /* Paramter1����ΪRmNetId, Paramter2����ΪFCID */
    stRegFcPoint.ulParam1   = ucRmNetId;
    stRegFcPoint.ulParam2   = enFcId;
    stRegFcPoint.pRstFunc   = AT_ResetFlowCtl;

    /* ע�����ص�, ��Ҫ�ֱ�ע��MEM��CDS */
    stRegFcPoint.enPolicyId = FC_POLICY_ID_MEM;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }


    stRegFcPoint.enPolicyId = FC_POLICY_ID_CDS;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg CDS point Failed.");
        return VOS_ERR;
    }

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enDefaultFcPri;
    /* ��һ�������϶��RABID�������������Ҫ�����RABID��¼���� */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* �ڵ���FC_DeRegPointǰ,�ȵ���FC_ChannelMapDelete */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRslt = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* ��һ�������϶��RABID�������������Ҫ����Ӧ��RABID��������� */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}


VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    if (VOS_TRUE == AT_CheckAppUser(ucIndex))
    {
        enUserIndex = ucIndex;
    }
    else
    {
        enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUserIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}


FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
)
{

    FC_PRI_ENUM_UINT8                   enFCPri;
    VOS_UINT8                           ucTrafficClass;

    /* ��ʼ�� */
    enFCPri         = FC_PRI_FOR_PDN_NONGBR;

    ucTrafficClass              = pstUmtsQos->ucTrafficClass;

    /* ����QOS trafficClass������ȡQCI */
    if (AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_STREAMING == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_INTERACTIVE == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_LOWEST;
    }

    return enFCPri;
}


VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl = AT_GetUartLineCtrlInfo();
    usLength    = 0;
    ulResult    = AT_FAILURE;
    ulATHCmdFlg = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                  VOS_TRUE : VOS_FALSE;

    /* ȥע��Modem�˿ڵ����ص� */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* �ͷ�PPPʵ�� & HDLCȥʹ�� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        if (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
        {
            /* �������ⵥAT2D13296���ڱ���ȥ�����龰�£���PPP������
               PPP_AT_CTRL_REL_PPP_REQ�󣬲�������������̬�����ǵ�
               ��PPP��ӦAT_PPP_PROTOCOL_REL_IND_MSG֮������������̬ */
            /* ��������ʱ�������ڵȴ�PPP��ӦAT_PPP_PROTOCOL_REL_IND_MSG */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            if (AT_SUCCESS != At_StartTimer(AT_PPP_PROTOCOL_REL_TIME, ucIndex))
            {
                AT_ERR_LOG("At_UsbModemStatusPreProc:ERROR:Start Timer fail");
            }

            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAIT_PPP_PROTOCOL_REL_SET;

            return;
        }
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* �ͷ�PPPʵ�� & HDLCȥʹ�� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /* ��������ģʽ�����ô��� */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVATED OTHER MODE");
    }

    /* ��������ģʽ */
    At_SetMode(ucIndex, AT_CMD_MODE,AT_NORMAL_MODE);

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATH�Ͽ�PPP����ʱ, ���DCD�ź�ģʽΪCONNECT ON, ��Ҫ����DCD�ź� */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ModemPsRspPdpActEvtRejProc
 ��������  : pdp����ʧ�ܣ�AP MODEM����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��5��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��22��
    ��    ��   : f62575
    �޸�����   : AT PROJECT OM_GreenChannel -> OM_AppGreenChannel
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulErrInfo;

    ulResult                            = AT_FAILURE;
    usLength                            = 0;

    if ( (AT_CMD_D_PPP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
      || (AT_CMD_PPP_ORG_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
    {
        ulResult = AT_NO_CARRIER;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);

        /* ��PPP����HDLCȥʹ�ܲ��� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        /* ��������ģʽ */
        At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);

        ulErrInfo = AT_OM_GREENCHANNEL_PS_ACTIVE_PDP_REJ;

        OM_AppGreenChannel(OM_GREEN_FUNC,
                        AT_OM_GREEN_CHANNEL_PS,
                        (VOS_UINT8 *)&ulErrInfo,
                        sizeof(ulErrInfo));
    }
    else if (AT_CMD_D_IP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        ulResult = AT_ERROR;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* ��PPP����HDLCȥʹ�ܲ��� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        ulErrInfo = AT_OM_GREENCHANNEL_PS_ACTIVE_PDP_REJ;
        OM_AppGreenChannel(OM_GREEN_FUNC,
                        AT_OM_GREEN_CHANNEL_PS,
                        (VOS_UINT8 *)&ulErrInfo,
                        sizeof(ulErrInfo));
    }
    else
    {
        ulResult = AT_ERROR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    return;
}
VOS_VOID AT_FillPppIndConfigInfoPara(
    AT_PPP_IND_CONFIG_INFO_STRU        *pstPppIndConfigInfo,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* ��дIP��ַ */
    PS_MEM_CPY(pstPppIndConfigInfo->aucIpAddr,
               pstEvent->stPdpAddr.aucIpv4Addr,
               TAF_IPV4_ADDR_LEN);

    /* ��дDNS��ַ */
    if (VOS_TRUE == pstEvent->stDns.bitOpPrimDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriDns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucPriDns,
               pstEvent->stDns.aucPrimDnsAddr,
               TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stDns.bitOpSecDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecDns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucSecDns,
                       pstEvent->stDns.aucSecDnsAddr,
                       TAF_IPV4_ADDR_LEN);

    }

    /* ��дNBNS��ַ */
    if (VOS_TRUE == pstEvent->stNbns.bitOpPrimNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriNbns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucPriNbns,
                   pstEvent->stNbns.aucPrimNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stNbns.bitOpSecNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecNbns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucSecNbns,
                   pstEvent->stNbns.aucSecNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    /* ��дGATE WAY��ַ */
    if (VOS_TRUE == pstEvent->stGateWay.bitOpGateWayAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpGateWay = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucGateWay,
                   pstEvent->stGateWay.aucGateWayAddr,
                   TAF_IPV4_ADDR_LEN);
    }


}
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PPP_IND_CONFIG_INFO_STRU         stPppIndConfigInfo;

    /* ע��Modem�˿ڵ����ص� */
    AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);


    /* ��ʼ�� */
    PS_MEM_SET(&stPppIndConfigInfo, 0x00, sizeof(AT_PPP_IND_CONFIG_INFO_STRU));

    /* �������������� */
    AT_STOP_TIMER_CMD_READY(ucIndex);


    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

        /* ע���������ݷ��ͺ��� */
        Ppp_RegDlDataCallback(gastAtClientTab[ucIndex].usPppId);

        At_FormatResultData(ucIndex, AT_CONNECT);
    }
    else if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
    {
        /* ��дIP��ַ, DNS, NBNS */
        AT_FillPppIndConfigInfoPara(&stPppIndConfigInfo, pstEvent);

        /* ��AUTH��IPCP֡����PPP����: */
        Ppp_RcvConfigInfoInd(gastAtClientTab[ucIndex].usPppId, &stPppIndConfigInfo);

        AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else
    {
        /* �������Ͳ������� */
    }

    return;
}
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    usLength        = 0;
    ulResult        = AT_FAILURE;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) ?
                      VOS_TRUE : VOS_FALSE;

    if ( (AT_MODEM_USER != gastAtClientTab[ucIndex].UserType)
      && (AT_HSUART_USER != gastAtClientTab[ucIndex].UserType) )
    {
        return;
    }

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* �ͷ�PPPʵ�� & HDLCȥʹ�� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* �ͷ�PPPʵ�� & HDLCȥʹ�� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* ��PPP����HDLCȥʹ�ܲ��� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /* ��������ģʽ�����ô��� */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVE_CNF OTHER MODE");
    }

    /* ȥע��Modem�˿ڵ����ص� */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);

    /* ��������ģʽ */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* Ϊ�˹��Linux��̨���β���ʧ�����⣬�������¹�ܷ���:
       PDP�����Ͽ����̽����󣬽��յ�TAF_PS_EVT_PDP_DEACTIVE_CNF�¼����жϲ���
       ϵͳ�Ƿ�ΪLinux����������ԭ�����̴��������ǣ����ٷ���"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* ԭ�������У���At_FormatResultData�����ڲ���������"NO CARRIER"֮��
           ��Ҫ��DCD���ͣ��ڴ˹�ܷ����У�������"NO CARRIER"����DCD�źŵ�����
           �����Ծ���Ҫ����
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATH�Ͽ�PPP����ʱ, ���DCD�ź�ģʽΪCONNECT ON, ��Ҫ����DCD�ź� */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_DCE_MSC_STRU                     stDecMsc;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    ulResult        = AT_FAILURE;
    usLength        = 0;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                      VOS_TRUE : VOS_FALSE;

    PS_MEM_SET(&stDecMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    /* ��鵱ǰ�û��Ĳ������� */
    if ( (AT_CMD_PS_DATA_CALL_END_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex))
      && (AT_CMD_H_PS_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex)) )
    {
        return;
    }

    /* PS��������ڴ����Ͽ�����, ֱ�ӷ��� */
    if (TAF_ERR_NO_ERROR == pstEvent->enCause)
    {
        return;
    }

    /* �ͷ�PPPʵ�� & HDLCȥʹ�� */
    if (AT_PPP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else if (AT_IP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        ;
    }

    /* ��������ģʽ */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* Ϊ�˹��Linux��̨���β���ʧ�����⣬�������¹�ܷ���:
       PDP�����Ͽ����̽����󣬽��յ�TAF_PS_EVT_PDP_DEACTIVE_CNF�¼����жϲ���
       ϵͳ�Ƿ�ΪLinux����������ԭ�����̴��������ǣ����ٷ���"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* ԭ�������У���At_FormatResultData�����ڲ���������"NO CARRIER"֮��
           ��Ҫ��DCD���ͣ��ڴ˹�ܷ����У�������"NO CARRIER"����DCD�źŵ�����
           �����Ծ���Ҫ����
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    /* ATH�Ͽ�PPP����ʱ, ���DCD�ź�ģʽΪCONNECT ON, ��Ҫ����DCD�ź� */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}
VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT16                          usPppId;
    VOS_UINT32                          ulErrInfo;
    VOS_UINT32                          ulRslt;

    usPppId     = 0;

    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        if (VOS_OK != Ppp_CreateRawDataPppReq(&usPppId))
        {
            ulErrInfo = TAF_OM_GREENCHANNEL_PS_CREATE_RAW_DATA_PPP_REQ_ERR;
            OM_AppGreenChannel(OM_GREEN_FUNC, TAF_OM_GREEN_CHANNEL_PS, (VOS_UINT8 *)&ulErrInfo, sizeof(ulErrInfo));

            ulRslt = AT_ERROR;
        }
        else
        {
            /* ��¼PPP id��Index�Ķ�Ӧ��ϵ */
            gastAtPppIndexTab[usPppId]          = ucIndex;

            /* ����PPP id */
            gastAtClientTab[ucIndex].usPppId    = usPppId;


            /* ע��Modem�˿ڵ����ص� */
            AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);

            /* �л�����ͨ�� */
            At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

            /* ע���������ݷ��ͺ��� */
            Ppp_RegDlDataCallback(usPppId);

            ulRslt = AT_CONNECT;
        }

        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        /* ��������....*/
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, AT_CONNECT);
    }

    return;
}


TAF_UINT32 At_RcvTeConfigInfoReq(
    TAF_UINT16                          usPppId,
    AT_PPP_REQ_CONFIG_INFO_STRU        *pstPppReqConfigInfo
)
{
    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq usPppId Wrong");
        return AT_FAILURE;
    }

    if (TAF_NULL_PTR == pstPppReqConfigInfo)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq pPppReqConfigInfo NULL");
        return AT_FAILURE;
    }

    if (AT_CMD_D_PPP_CALL_SET != gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq NOT AT_CMD_D_PPP_CALL_SET");
        return AT_FAILURE;
    }

    if ( VOS_OK == TAF_PS_PppDialOrig(WUEPS_PID_AT,
                                      gastAtClientTab[gastAtPppIndexTab[usPppId]].usClientId,
                                      0,
                                      gastAtClientTab[gastAtPppIndexTab[usPppId]].ucCid,
                                      (TAF_PPP_REQ_CONFIG_INFO_STRU *)pstPppReqConfigInfo) )
    {
        /* ����ʱ�� */
        if (AT_SUCCESS != At_StartTimer(AT_ACT_PDP_TIME, gastAtPppIndexTab[usPppId]))
        {
            AT_ERR_LOG("At_RcvTeConfigInfoReq:ERROR:Start Timer");
            return AT_FAILURE;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt = AT_CMD_PPP_ORG_SET;

        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 �� �� ��  : At_RcvPppReleaseInd
 ��������  : AT����PPP�ͷ���·ָʾ
 �������  : TAF_UINT16                          usPppId  PPP ID
 �������  : ��
 �� �� ֵ  : TAF_UINT32
             0 --- �ɹ�
             1 --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 At_RcvPppReleaseInd(
    TAF_UINT16                          usPppId
)
{
    TAF_UINT8                           aucEventInfo[4];
    AT_PPP_RELEASE_IND_MSG_STRU        *pMsg;
    VOS_UINT32                          ulLength;

    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvPppReleaseInd usPppId Wrong");
        return AT_FAILURE;
    }

    /* EVENT- At_RcvPppReleaseInd:usPppId / gastAtPppIndexTab[usPppId] */
    aucEventInfo[0] = (TAF_UINT8)(usPppId >> 8);
    aucEventInfo[1] = (TAF_UINT8)usPppId;
    aucEventInfo[2] = gastAtPppIndexTab[usPppId];
    AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DTE_RELEASE_PPP,
                   aucEventInfo, sizeof(aucEventInfo));

    /* ��ATģ�鷢��AT_PPP_RELEASE_IND_MSG */
    ulLength       = sizeof(AT_PPP_RELEASE_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pMsg = (AT_PPP_RELEASE_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_APP_PPP, ulLength);
    if (VOS_NULL_PTR == pMsg)
    {
        /* ��ӡ������Ϣ---������Ϣ��ʧ�� */
        AT_ERR_LOG( "At_RcvPppReleaseInd:ERROR:Allocates a message packet for AT_PPP_RELEASE_IND_MSG_STRU msg FAIL!" );
        return AT_FAILURE;
    }
    /* ��д��Ϣͷ */
    pMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_AT;
    pMsg->MsgHeader.ulLength        = ulLength;

    pMsg->MsgHeader.ulMsgName       = AT_PPP_RELEASE_IND_MSG;
    /* ��д��Ϣ�� */
    pMsg->ucIndex                   = gastAtPppIndexTab[usPppId];

    /* ���͸���Ϣ */
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pMsg))
    {
        /* ��ӡ������Ϣ---������Ϣʧ�� */
        AT_WARN_LOG( "At_RcvPppReleaseInd:WARNING:SEND AT_PPP_RELEASE_IND_MSG msg FAIL!" );
        return AT_FAILURE;
    }
    else
    {
        /* ��ӡ������Ϣ---��������Ϣ */
        AT_WARN_LOG( "At_RcvPppReleaseInd:NORMAL:SEND AT_PPP_RELEASE_IND_MSG Msg" );
        return AT_SUCCESS;
    }
}


TAF_VOID At_PppReleaseIndProc(
    TAF_UINT8                           ucIndex
)
{
    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_WARN_LOG("At_PppReleaseIndProc:ERROR:ucIndex is abnormal!");
        return;
    }

    if (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ��ATͨ���л�Ϊ����ģʽ */
        At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

        /*ֹͣ��ʱ��*/
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /*�ظ�NO CARRIER*/
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_NO_CARRIER);

        return;
    }

    if (AT_CMD_PS_DATA_CALL_END_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return;
    }

    if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  gastAtClientTab[ucIndex].ucCid) )
    {
        /* ����ʱ�� */
        if (AT_SUCCESS != At_StartTimer(AT_DETACT_PDP_TIME, ucIndex))
        {
            AT_ERR_LOG("At_PppReleaseIndProc:ERROR:Start Timer");
            return;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;
    }

    return;
}

/*****************************************************************************
 Prototype      : At_PsRab2PppId
 Description    : ����֪Rab ID��ȡPPP ID
 Input          : RabId     --- ��֪��RAB ID
 Output         : pusPppId  --- PPP ID
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PsRab2PppId(
    TAF_UINT8                           ucRabId,
    TAF_UINT16                         *pusPppId
)
{
    TAF_UINT16                          usPppId;
    TAF_UINT8                           ucIndex;

    if (VOS_NULL_PTR == pusPppId)
    {
        AT_WARN_LOG("At_PsRab2PppId, pusPppId NULL");
        return TAF_FAILURE;
    }

    /* ͨ��PPP ID������ң�Ч�ʻ�Ƚϸ� */
    for (usPppId = 1; usPppId <= PPP_MAX_ID_NUM; usPppId++)
    {
        ucIndex = gastAtPppIndexTab[usPppId];

        if (AT_MAX_CLIENT_NUM <= ucIndex)
        {
            continue;
        }

        if ( AT_CLIENT_USED != gastAtClientTab[ucIndex].ucUsed )
        {
            continue;
        }

        if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
        {
            continue;
        }

        if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
          && (AT_IP_DATA_MODE != gastAtClientTab[ucIndex].DataMode) )
        {
            continue;
        }

        if (gastAtClientTab[ucIndex].ucPsRabId == ucRabId)
        {
            *pusPppId = usPppId;    /* ���ؽ�� */
            return TAF_SUCCESS;
        }

    }

    AT_LOG1("AT, At_PsRab2PppId, WARNING, Get PppId from Rab <1> Fail", ucRabId);

    return TAF_FAILURE;
} /* At_PsRab2PppId */


/*****************************************************************************
 Prototype      : At_PppId2PsRab
 Description    : ����֪PPP ID��ȡRab ID
 Input          : usPppId   ---  ��֪��PPP ID
 Output         : pucRabId  ---  RAB ID
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PppId2PsRab(
    TAF_UINT16                          usPppId,
    TAF_UINT8                          *pucRabId
)
{
    TAF_UINT8                           ucIndex;


    if ((usPppId < 1) || (usPppId > PPP_MAX_ID_NUM))
    {
        PS_LOG1(WUEPS_PID_AT, 0, PS_PRINT_WARNING,
            "AT, At_PppId2PsRab, WARNING, PppId <1> Wrong", usPppId);
        return TAF_FAILURE;
    }

    if (TAF_NULL_PTR == pucRabId)
    {
        AT_WARN_LOG("AT, At_PppId2PsRab, WARNING, pucRabId NULL");
        return TAF_FAILURE;
    }

    ucIndex = gastAtPppIndexTab[usPppId];

    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, index <1> Wrong", ucIndex);
        return TAF_FAILURE;
    }

    if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, Mode <1> Wrong", gastAtClientTab[ucIndex].Mode);
        return TAF_FAILURE;
    }

    if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
      && (AT_IP_DATA_MODE  != gastAtClientTab[ucIndex].DataMode) )
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, DataMode <1> Wrong", gastAtClientTab[ucIndex].DataMode);
        return TAF_FAILURE;
    }

    *pucRabId = gastAtClientTab[ucIndex].ucPsRabId;

    return TAF_SUCCESS;
} /* At_PppId2PsRab */

#if( FEATURE_ON == FEATURE_CSD )
VOS_UINT32 AT_VpResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRet;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;

    enFcId    = ulParam2;
    enModemId = g_stFcIdMaptoFcPri[enFcId].enModemId;

    if (VOS_TRUE == g_stFcIdMaptoFcPri[enFcId].ulUsed)
    {
        ulRet = FC_DeRegPoint(enFcId, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_VpResetFlowCtl: ERROR: de reg point Failed.");
            return VOS_ERR;
        }

        g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;
    }

    return VOS_OK;
}


VOS_UINT32 AT_RegModemVideoPhoneFCPoint(
    VOS_UINT8                           ucIndex,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFcPri;
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    stRegFcPoint.enFcId             = enFcId;

    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */
    enFcPri                         = FC_PRI_FOR_PDN_LOWEST;
    stRegFcPoint.enFcPri            = enFcPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.pClrFunc           = AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc           = AT_MODEM_StartFlowCtrl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)g_alAtUdiHandle[ucIndex];
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, End */
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_VpResetFlowCtl;

    /* ע�����ص�,��Ҫ�ֱ�ע��MEM,CPU,CST */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint CST Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint MEM Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CST;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint A CPU Failed.");
        return VOS_ERR;
    }

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed  = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri = enFcPri;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId = enModemId;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_VP);

    return VOS_OK;
}


VOS_UINT32 AT_DeRegModemVideoPhoneFCPoint(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemVideoPhoneFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    ulRet = FC_DeRegPoint(FC_ID_MODEM, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemVideoPhoneFCPoint: ERROR: FC DeRegPoint Failed.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, End */

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = FC_PRI_BUTT;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = MODEM_ID_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_VP);

    return VOS_OK;
}
#endif


VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFcPri;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART�˿����عر�ʱ��ע�����ص� */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
      && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* ����ͨ����RABIDӳ���ϵ */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* ����������������ȼ�RAB QoS���ȼ�������,���ȼ��ı�ʱ����Ҫ�ı����ȼ� */
    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFcPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFcPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFcPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
#if (FEATURE_ON == FEATURE_AT_HSUART)
    stRegFcPoint.pClrFunc           = (AT_CLIENT_TAB_HSUART_INDEX == ucIndex) ?
                                      AT_HSUART_StopFlowCtrl : AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc           = (AT_CLIENT_TAB_HSUART_INDEX == ucIndex) ?
                                      AT_HSUART_StartFlowCtrl : AT_MODEM_StartFlowCtrl;
#else
    stRegFcPoint.pClrFunc           = AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc            = AT_MODEM_StartFlowCtrl;

#endif
    stRegFcPoint.ulParam1           = (VOS_UINT32)g_alAtUdiHandle[ucIndex];
    stRegFcPoint.enModemId          = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* ע�����ص�,��Ҫ�ֱ�ע��MEM,CPU,CDS��GPRS�� */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint MEM Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint A CPU Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint GPRS Failed.");
        return VOS_ERR;
    }

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = enFcPri;
    /* ��һ�������϶��RABID�������������Ҫ�����RABID��¼���� */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = enModemId;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}
VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulRet;
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART�˿����عر�ʱ��ע�����ص� */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    /* ɾ������ģ��ӳ���ϵ */
    FC_ChannelMapDelete(ucRabId, enModemId);

    ulRet = FC_DeRegPoint(FC_ID_MODEM, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: ERROR: FC DeRegPoint Failed.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = FC_PRI_BUTT;
    /* ��һ�������϶��RABID�������������Ҫ����Ӧ��RABID��������� */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = MODEM_ID_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstCtrl->usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ChangeFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    if (FC_ID_BUTT != enFcId)
    {
        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_MEM, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CPU_A , enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CDS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_GPRS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_EnableHsicFlowCtl
 ��������  : ʹ��Hsic����
 �������  : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_ENABLE;

    if (0 != udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_DisableHsicFlowCtl
 ��������  : ȥʹ��HSIC����
 �������  : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_DISABLE;

    if (0 != udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID                       enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_RegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /* ����ͨ����RABIDӳ���ϵ */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    /* ����������������ȼ�RAB QoS���ȼ�������,���ȼ��ı�ʱ����Ҫ�ı����ȼ� */
    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);
    stRegFcPoint.enModemId          = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* ע�����ص�,��Ҫ�ֱ�ע��MEM,CPU,CDS��GPRS�� */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enFCPri;
    /* ��һ�������϶��RABID�������������Ҫ�����RABID��¼���� */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return VOS_OK;
}
VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID                       enDataChannelId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_DeRegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /* ɾ������ģ��ӳ���ϵ */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* ��һ�������϶��RABID�������������Ҫ����Ӧ��RABID��������� */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);


    return VOS_OK;
}
VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* ��DIPC�ϱ�PDP�Ѿ������¼� */
    AT_SndDipcPdpActInd(pstEvent->stCtrl.usClientId, pstEvent->ucCid, pstEvent->ucRabId);

    /* ��FCע�����ص� */
    AT_RegHsicFCPoint(pstEvent);

    /* ��ָ��CID��PDP�ļ���״̬����Ϊ����̬ */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstEvent->ucCid, VOS_TRUE);
    return;
}
VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* ��DIPC�ϱ�PDP�Ѿ�ȥ�����¼� */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* ��FCȥע�����ص� */
    AT_DeRegHsicFCPoint(pstEvent);

    /* ������CID������ͨ����ӳ���ϵ */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    return;
}
VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16  usLength;

    usLength    = 0;

    /* ��DIPC�ϱ�PDP�Ѿ�ȥ�����¼� */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* ��FCȥע�����ص� */
    AT_DeRegHsicFCPoint(pstEvent);

    /* ������CID������ͨ����ӳ���ϵ */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);

            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;

        case TAF_PDP_IPV4V6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;
#endif

        default:
            AT_ERR_LOG("AT_HsicPsRspEvtPdpDeactivatedProc:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/* Modified by l60609 for AP������Ŀ ��2012-09-10 Begin */
/*****************************************************************************
 �� �� ��  : AT_SendRnicCgactIpv4ActInd
 ��������  : AT+CGACT���ųɹ���RNIC��PDP������Ϣ
 �������  : VOS_UINT8                           ucRabId,
             VOS_UINT8                           ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* ����AT_RNIC_IPV4_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* ��д��Ϣ�� */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_ProcAppPsRspEvtPdpActCnf
 ��������  : ����RILͨ��AT+CGACT�����PDP��������
 �������  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��2��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��18��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;

    ucRmNetId = 0;

    /* ��ȡ����Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* ��ȡ����Idʧ�ܣ�������Լ����Ӧ��CID��Χ�ڣ���֧������ */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��ȡFcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    PS_MEM_SET(&stFCPriOrg, 0, sizeof(stFCPriOrg));

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* ���FC IDδע�ᣬ��ôע������ص㡣*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* ע��APP����ʹ�õ����ص� */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, ucRmNetId);
        }
        else
        {
            /* APP����ֻʹ����͵�����QOS���ȼ�FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppPsRspEvtPdpActCnf: No need to change the default QOS priority.");
        }
    }

    /* ĿǰAPPֻ֧��AT+CGACT����IPV4���� */
    AT_SendRnicCgactIpv4ActInd(pstEvent->ucRabId, ucRmNetId);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ProcAppPsRspEvtPdpDeActCnf
 ��������  : ����RILͨ��AT+CGACT�����PDPȥ��������
 �������  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��2��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��18��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    ucRmNetId = 0;

    /* ��ȡ����Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* ��ȡ����Idʧ�ܣ�������Լ����Ӧ��CID��Χ�ڣ���֧������ */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��ȡFcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    /* ֪ͨRNIC PDPȥ����ɹ� */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

    /* ȥע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}
/* Modified by l60609 for AP������Ŀ ��2012-09-10 End */
/*****************************************************************************
 �� �� ��  : AT_ProcAppPsRspEvtPdpDeactivated
 ��������  : APPͨ��AT+CGACT����PDP������෢��PDPȥ����
 �������  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16                          usLength;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    ucRmNetId   = 0;

    /* APP����Ĭ��ʹ��NDIS����1�����ص� */
    enDefaultFcId = FC_ID_NIC_1;

    /* ��ȡ����Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* ��ȡ����Idʧ�ܣ�������Լ����Ӧ��CID��Χ�ڣ���֧������ */
    if (VOS_OK == ulRslt)
    {
        /* ֪ͨRNIC PDPȥ����ɹ� */
        AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

        /* ȥע��APP����ʹ�õ����ص�(Ĭ��ʹ������1) */
        AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);
    }

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_ProcAppPsRspEvtPdpDeactivated:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_NotifyFcWhenAppPdpModify
 ��������  : ������PDP MODIFY(UE��������෢��)ʱ����FCָʾ�޸����ص�
 �������  : VOS_UINT8                           ucIndex,
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ucRmNetId = 0;

    /* ��ȡ����Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* ��ȡ����Idʧ�ܣ�������Լ����Ӧ��CID��Χ�ڣ���֧������ */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��ȡFcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);

    return;
}
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    if (pstEvent->bitOpPdpAddr)
    {
        ulIpAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);
        pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = ulIpAddr;
    }

    return;
}
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = 0;

    return;
}


VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (AT_PS_IS_RABID_VALID(ucRabId))
    {
        ulIpAddr = pstPsModemCtx->aulIpAddrRabIdMap[ucRabId - AT_PS_RABID_OFFSET];
    }

    return ulIpAddr;
}

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
/*****************************************************************************
 �� �� ��  : AT_PS_GetRmNetIdFromCid
 ��������  : ����Client Id��Cid��ȡ��Ӧ������Id
 �������  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucCid,
             VOS_UINT8                          *pucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
)
{
    VOS_UINT8                           i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    if (VOS_NULL_PTR == pucRmNetId)
    {
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    /* ��ȡmodem idʧ�� */
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    for (i = 0; i < (sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB)); i++)
    {
        if ((enModemId == g_astPsRmNetIdTab[i].enModemId)
         && (ucCid == g_astPsRmNetIdTab[i].ucUsrCid))
        {
            *pucRmNetId = i;
            break;
        }
    }

    /* ��ӳ�����δ�ҵ� */
    if (i >= sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT8                           ucRabIdIndex;
    VOS_UINT32                          ulRabIdMask;
    VOS_UINT32                          ulRet;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;

    enFcId      = (FC_ID_ENUM_UINT8)ulParam2;
    enModemId   = g_stFcIdMaptoFcPri[enFcId].enModemId;
    ulRabIdMask = g_stFcIdMaptoFcPri[enFcId].ulRabIdMask;

    if (VOS_TRUE == g_stFcIdMaptoFcPri[enFcId].ulUsed)
    {
        for (ucRabIdIndex = AT_PS_MIN_RABID; ucRabIdIndex <= AT_PS_MAX_RABID; ucRabIdIndex++)
        {
            if (1 == ((ulRabIdMask >> ucRabIdIndex) & 0x1))
            {
                FC_ChannelMapDelete(ucRabIdIndex, enModemId);
            }
        }

        ulRet = FC_DeRegPoint(enFcId, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ResetFlowCtl: ERROR: DeReg point failed.");
            return VOS_ERR;
        }

        g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    }

    return VOS_OK;
}

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */

/*****************************************************************************
 �� �� ��  : AT_PS_GetRnicRmNetIdFromChDataValue
 ��������  : ����CHDATA���õ�ͨ���Ż�ȡ��Ӧ��RNIC����ID
 �������  : VOS_UINT8                           ucIndex
             AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId
             RNIC_RM_NET_ID_ENUM_UINT8          *penRnicRmNetId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : L60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RM_NET_ID_ENUM_UINT8          *penRnicRmNetId
)
{
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;
    VOS_UINT32                          ulRslt;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    *penRnicRmNetId = RNIC_RM_NET_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /* MODEM0 RNIC ID Ϊ 0~2�� CHDATA��ֵΪ 1~3
       MODEM1 RNIC ID Ϊ 3~4�� CHDATA��ֵΪ 4~5
    */

    if (MODEM_ID_0 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_1)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_3))
        {
            return VOS_ERR;
        }
    }

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    if (MODEM_ID_1 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_4)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_5))
        {
            return VOS_ERR;
        }
    }
#endif

    /*  �����ж����ܱ�֤enDataChannelId����Ч�ԣ�����RM NET IDһ�����ڱ����ҵ� */
    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enDataChannelId == pstChdataRnicRmNetIdTab[i].enChdataValue)
        {
            *penRnicRmNetId = pstChdataRnicRmNetIdTab[i].enRnicRmNetId;
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetChDataValueFromRnicRmNetId
 ��������  : ���ݶ�Ӧ��RNIC����ID��ȡCHDATA���õ�ͨ����
 �������  : RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId
             AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
)
{
    VOS_UINT32                          i;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enRnicRmNetId == pstChdataRnicRmNetIdTab[i].enRnicRmNetId)
        {
            *penDataChannelId = pstChdataRnicRmNetIdTab[i].enChdataValue;
            break;
        }
    }

    if (i >= AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE())
    {
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetFcIdByUdiDeviceId
 ��������  : ͨ��DIPCͨ��ID���FCID
 �������  : UDI_DEVICE_ID                       enDataChannelId
 �������  : ��
 �� �� ֵ  : FC_ID_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��2��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID                       enDataChannelId
)
{
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            return FC_ID_DIPC_1;

        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            return FC_ID_DIPC_2;

        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            return FC_ID_DIPC_3;

        default:
            AT_WARN_LOG("AT_PS_GetFcIdByUdiDeviceId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetFcIdFromRnicByRmNetId
 ��������  : ��ȡRNIC������FCID
 �������  : VOS_UINT32                          ulRmNetId
 �������  : ��
 �� �� ֵ  : FC_ID_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��2��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
)
{
    switch (ulRmNetId)
    {
        case RNIC_RM_NET_ID_0:
            return FC_ID_NIC_1;

        case RNIC_RM_NET_ID_1:
            return FC_ID_NIC_2;

        case RNIC_RM_NET_ID_2:
            return FC_ID_NIC_3;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        case RNIC_RM_NET_ID_3:
            return FC_ID_NIC_4;

        case RNIC_RM_NET_ID_4:
            return FC_ID_NIC_5;
#endif

        default:
            AT_WARN_LOG("AT_PS_GetFcIdFromRnidRmNetId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetCallEntity
 ��������  : ��ȡPS�����ʵ��ָ��
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : AT_PS_CALL_ENTITY_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId]);
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetUserInfo
 ��������  : ��ȡPS������û���Ϣ
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : AT_PS_USER_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_PS_USER_INFO_STRU* AT_PS_GetUserInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId].stUserInfo);
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetDataChanlCfg
 ��������  : ��ȡ����ͨ��������Ϣ
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : AT_PS_DATA_CHANL_CFG_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astChannelCfg[ucCid]);
}
/*****************************************************************************
 �� �� ��  : AT_PS_TransCidToCallId
 ��������  : ��ȡ���CID������PSʵ������
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* cid ��Чֵ */
    if (ucCid > TAF_MAX_CID)
    {
        return AT_PS_CALL_INVALID_CALLID;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->aucCidToIndexTbl[ucCid];
}

/*****************************************************************************
 �� �� ��  : AT_PS_IsCallIdValid
 ��������  : PS�����ʵ�������Ƿ���Ч
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        return VOS_FALSE;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

#if (FEATURE_ON == FEATURE_IPV6)
    if ((AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv4Cid)
     && (AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv6Cid))
    {
        return VOS_FALSE;
    }
#else
    if (AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv4Cid)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : AT_PS_AssignCallIdToCid
 ��������  : ����cid��callid��ӳ���
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = ucCallId;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_FreeCallIdToCid
 ��������  : ���cid��callid��ӳ���
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = AT_PS_CALL_INVALID_CALLID;

    return;
}


VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->ucIpv4Cid = ucCid;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstCallEntity->ucIpv6Cid = ucCid;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->ucIpv4Cid = ucCid;
            pstCallEntity->ucIpv6Cid = ucCid;
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return;
}
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            ucCid = pstCallEntity->ucIpv4Cid;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            ucCid = pstCallEntity->ucIpv6Cid;
            break;
#endif

        default:
            ucCid = AT_PS_CALL_INVALID_CID;
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return ucCid;
}
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->enIpv4State = enPdpState;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstCallEntity->enIpv6State = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->enIpv4State = enPdpState;
            pstCallEntity->enIpv6State = enPdpState;
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_SetCallStateByType: PDP type is invalid!");
            break;
    }

    return;
}


AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstCallEntity->enIpv4State;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            enPdpState = pstCallEntity->enIpv6State;
            break;
#endif

        default:
            enPdpState = AT_PDP_STATE_IDLE;
            AT_ERR_LOG("AT_PS_GetCallStateByType: PDP type is invalid!");
            break;
    }

    return enPdpState;
}


AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (pstCallEntity->ucIpv4Cid == ucCid)
    {
        return pstCallEntity->enIpv4State;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (pstCallEntity->ucIpv6Cid == ucCid)
    {
        return pstCallEntity->enIpv6State;
    }
#endif

    return AT_PDP_STATE_IDLE;
}

/*****************************************************************************
 �� �� ��  : AT_PS_IsUsrDialTypeDualStack
 ��������  : �ж��Ƿ�˫ջ����
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  AT_PS_IsUsrDialTypeDualStack(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (TAF_PDP_IPV4V6 == pstCallEntity->stUsrDialParam.enPdpType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_ReportDCONN: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}


VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);

            break;
#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_ReportDEND: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}


AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_CONN_RESULT_STRU      *pstRptConnRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptConnRsltFuncTblPtr = AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR();

    /* �û�����ƥ�� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptConnRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptConnRsltFunc = pstRptConnRsltFuncTblPtr[ulCnt].pRptConnRsltFunc;
            break;
        }
    }

    return pRptConnRsltFunc;
}
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_END_RESULT_STRU       *pstRptEndRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptEndRsltFuncTblPtr = AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR();

    /* �û�����ƥ�� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptEndRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptEndRsltFunc = pstRptEndRsltFuncTblPtr[ulCnt].pRptEndRsltFunc;
            break;
        }
    }

    return pRptEndRsltFunc;
}
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstDialPara = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    pstDialPara   = &pstCallEntity->stUsrDialParam;
    ulIpAddr      = 0;

    pstCallEntity->stIpv4DhcpInfo.ucRabId                 = pstEvent->ucRabId;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* ����û���������DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == pstDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucPrimIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* ����û������˸�DNS����ʹ���û����õ�DNS�����緵�ص�DNS��ʹ�� */
    if (VOS_TRUE == pstDialPara->ulSndIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucSndIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriPCSCF   = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimPCSCF     = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* ��ȡ��PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP��ַ����Ч����APS��֤ */
        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4Secpcscf   = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4SecPCSCF      = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
    }

    return;
}


VOS_VOID AT_PS_ProcConnInd(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    PS_MEM_SET(&stParam, 0, sizeof(AT_DHCP_SETUP_PARAM_ST));
    PS_MEM_SET(&stConfig, 0, sizeof(AT_DHCP_CONFIG_STRU));

    /* ���PS�¼���DNS��ַ�����¼DNS��ַ*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* ��¼IP��ַ*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_PS_ProcConnInd : ERROR AT_DHCPServerSetUp Error!" );
    }
    else
    {
        /* ����IPv4��ַ���� */
        AT_PS_PdpAddrProc(ucCallId, &stConfig, pstEvent);
    }

    return;
}
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo          = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc    = VOS_NULL_PTR;

    /* ��ȡ��ǰ�����û���Ϣ */
    pstUsrInfo       = AT_PS_GetUserInfo(usClientId, ucCallId);

    /* ���¼��������в��Ҵ������� */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstUsrInfo->ucUsrType);

    /* �������������������� */
    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        pRptConnRsltFunc(pstUsrInfo->ucUsrCid,
                         pstUsrInfo->enPortIndex,
                         enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallConnectedResult:ERROR: User type is invalid!");
    }

    return;
}
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo      = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    /* ��ȡ��ǰ�����û���Ϣ */
    pstUsrInfo      = AT_PS_GetUserInfo(usClientId, ucCallId);

    /* ���¼��������в��Ҵ������� */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstUsrInfo->ucUsrType);

    /* �������������������� */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstUsrInfo->ucUsrCid,
                        pstUsrInfo->enPortIndex,
                        enPdpType,
                        enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallEndedResult:ERROR: User type is invalid!");
    }

    return;
}
VOS_VOID AT_PS_GenCallDialParam(
    AT_DIAL_PARAM_STRU                 *pstCallDialParam,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* ��ȡ�û����Ų��� */
    *pstCallDialParam           = *pstUsrDialParam;

    /* ˢ��CID��PDP���� */
    pstCallDialParam->ucCid     = ucCid;
    pstCallDialParam->enPdpType = enPdpType;

    return;
}


VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_STRU            *pstRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_FUNC             pRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo             = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstRegFcPointFuncTblPtr = AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR();

    /* ���¼��������в��Ҵ������� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /* ����ƥ�� */
            pRegFcPointFunc = pstRegFcPointFuncTblPtr[ulCnt].pRegFcPoint;
            break;
        }
    }

    /* �������������������� */
    if (VOS_NULL_PTR != pRegFcPointFunc)
    {
        pRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegFCPoint:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_DeRegFCPoint
 ��������  : ȥע�����ص�
 �������  : ucCallId   - ����ʵ��ID
             pstEvent   - �¼���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : C50 IPv6 ��Ŀ��������
*****************************************************************************/
VOS_VOID AT_PS_DeRegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_STRU          *pstDeRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_FUNC           pDeRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstDeRegFcPointFuncTblPtr = AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR();

    /* ���¼��������в��Ҵ������� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstDeRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /* ����ƥ�� */
            pDeRegFcPointFunc = pstDeRegFcPointFuncTblPtr[ulCnt].pDeRegFcPoint;
            break;
        }
    }

    /* �������������������� */
    if (VOS_NULL_PTR != pDeRegFcPointFunc)
    {
        pDeRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegFCPoint:ERROR: User type is invalid!");
    }

    return;
}
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_ACT_STRU               *pstAtDipcPdpAct = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ulLength        = sizeof( AT_DIPC_PDP_ACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpAct = ( AT_DIPC_PDP_ACT_STRU *)PS_ALLOC_MSG( WUEPS_PID_AT, ulLength );

    if (VOS_NULL_PTR == pstAtDipcPdpAct)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:ERROR:Allocates a message packet for AT_DIPC_PDP_ACT_STRU FAIL!" );
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*��д��Ϣͷ:*/
    pstAtDipcPdpAct->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpAct->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpAct->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pstAtDipcPdpAct->enMsgType       = ID_AT_DIPC_PDP_ACT_IND;
    pstAtDipcPdpAct->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpAct->enBearerType    = enBearerType;
    pstAtDipcPdpAct->enUdiDevId      = (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    /*���͸���Ϣ:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpAct))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:WARNING:SEND AT_DIPC_PDP_ACT_STRU msg FAIL!" );
    }

    return;
}
VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* ��DIPC�ϱ�PDP IPv4�Ѿ������¼� */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV4);
    }

    /* ��DIPC�ϱ�PDP IPv6�Ѿ������¼� */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV6);
    }

    return;
}


VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_DEACT_STRU             *pstAtDipcPdpDeact = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength          = sizeof( AT_DIPC_PDP_DEACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpDeact = (AT_DIPC_PDP_DEACT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstAtDipcPdpDeact)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:ERROR:Allocates a message packet for AT_DIPC_PDP_DEACT_STRU FAIL!" );
        return;
    }

    /*��д��Ϣͷ:*/
    pstAtDipcPdpDeact->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpDeact->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpDeact->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pstAtDipcPdpDeact->enMsgType       = ID_AT_DIPC_PDP_REL_IND;
    pstAtDipcPdpDeact->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpDeact->enBearerType    = enBearerType;

    /*���͸���Ϣ:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpDeact))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:WARNING:SEND AT_DIPC_PDP_DEACT_STRU msg FAIL!" );
    }

    return;
}
VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* ��DIPC�ϱ�PDP IPv4�Ѿ�ȥ�����¼� */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV4);
    }

    /* ��DIPC�ϱ�PDP IPv6�Ѿ�ȥ�����¼� */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV6);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicIpv4PdpActInd
 ��������  : ��RNIC����PDP�����¼�, IPv4����
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* �ж���������Ч�� */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RM_NET_ID_BUTT)
    {
        return;
    }

    /* ����AT_RNIC_IPV4_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: alloc msg fail!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* ��дrab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* ��дrmnet id����chdata�����л�ȡ */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicIpv6PdpActInd
 ��������  : ��RNIC����PDP�����¼�, IPv6����
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* �ж���������Ч�� */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RM_NET_ID_BUTT)
    {
        return;
    }

    /* ����AT_RNIC_IPV6_PDP_ACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: alloc msg fail!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /* ��дrab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* ��дrmnet id����chdata�����л�ȡ */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicPdpActInd
 ��������  : ����PDP���͸�RNIC���ͼ�����Ϣ
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* ��DIPC�ϱ�PDP IPv4�Ѿ������¼� */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndRnicIpv4PdpActInd(ucCid, pstEvent);
    }

    /* ��DIPC�ϱ�PDP IPv6�Ѿ������¼� */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndRnicIpv6PdpActInd(ucCid, pstEvent);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicPdpDeactInd
 ��������  : APP�˿ڲ���ʱ֪ͨ��������
 �������  : VOS_UINT8                           ucRabId
             VOS_UINT8                           ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* �ж���������Ч�� */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RM_NET_ID_BUTT)
    {
        return;
    }

    /* ����AT_NDIS_PDP_DEACT_IND_STRU��Ϣ */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /* ��д��Ϣ�� rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* ��д��Ϣ�� rmnet id����chdata�����л�ȡ */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_ActivateRmNet
 ��������  : ����������PDP�����¼�
 �������  : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_ActivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_STRU         *pstSndPdpActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_FUNC          pSndPdpActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpActIndFuncTblPtr = AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR();

    /* ���¼��������в��Ҵ������� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /* ����ƥ�� */
            pSndPdpActIndFunc = pstSndPdpActIndFuncTblPtr[ulCnt].pSndPdpActInd;
            break;
        }
    }

    /* �������������������� */
    if (VOS_NULL_PTR != pSndPdpActIndFunc)
    {
        pSndPdpActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ActivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_DeactivateRmNet
 ��������  : ����������PDPȥ�����¼�
 �������  : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_DeactivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_STRU       *pstSndPdpDeActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_FUNC        pSndPdpDeActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo                 = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpDeActIndFuncTblPtr = AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR();

    /* ���¼��������в��Ҵ������� */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpDeActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /* ����ƥ�� */
            pSndPdpDeActIndFunc = pstSndPdpDeActIndFuncTblPtr[ulCnt].pSndPdpDeActInd;
            break;
        }
    }

    /* �������������������� */
    if (VOS_NULL_PTR != pSndPdpDeActIndFunc)
    {
        pSndPdpDeActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeactivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_PS_IsIpv6CapabilityValid
 ��������  : �ж�ipv6������Ч
 �������  : VOS_UINT8 ucCapability
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability)
{
    if ((AT_IPV6_CAPABILITY_IPV4_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV6_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucCapability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_PS_IsIpv6Support
 ��������  : �ж��Ƿ�֧��IPV6
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��2��
    ��    ��   : L60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID)
{
    VOS_UINT8                           ucIpv6Capability;

    ucIpv6Capability = AT_GetCommPsCtxAddr()->ucIpv6Capability;

    if ((AT_IPV6_CAPABILITY_IPV6_ONLY == ucIpv6Capability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucIpv6Capability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
)
{
    VOS_UINT32                         *paulAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulTick;

    paulAddr = (VOS_UINT32 *)pucIpv6LanAddr;

    if (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN)
    {
        return VOS_ERR;
    }

    /* ����IPv6��ַǰ׺ */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    ulTick = VOS_GetTick();

    /* �ڽ���PC����ʱ����ʹ�����ֵ */
#if (VOS_WIN32 == VOS_OS_VER)
    paulAddr[2] = 0xFFFFFFFFU;

    paulAddr[3] = 0xFFFFFFFFU;

#else
    VOS_SetSeed(ulTick);
    paulAddr[2] = VOS_Rand(0xFFFFFFFFU);

    VOS_SetSeed(ulTick + 10);
    paulAddr[3] = VOS_Rand(0xFFFFFFFFU);

#endif

    *(VOS_UINT8 *)(&paulAddr[2]) &= ~0x02;

    return VOS_OK;
}


VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns    = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns    = VOS_FALSE;

    /* ��������DNS���յ�RA����ʱ��Ҫ����������ʱ��Ҫ֪ͨDRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns = VOS_TRUE;
    }

}
VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriPCSCF = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecPCSCF = VOS_FALSE;

    /* ����IPV6����PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucPrimPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* ����IPV6�ĸ�PCSCF��ַ */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucSecPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
}


VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.ucRabId  = pstEvent->ucRabId;

    /* ����IPv6��IP��ַ����ʽΪ������ */
    PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* ����IPV6������DNS��ַ����ʽΪ������ */
    AT_PS_SaveIPv6Dns(ucCallId, pstEvent);

    /* ����IPV6������PCSCF��ַ����ʽΪ������ */
    AT_PS_SaveIPv6Pcscf(ucCallId, pstEvent);

    return;
}
VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstRaInfoNotifyInd->stCtrl.usClientId, pstRaInfoNotifyInd->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcIpv6RaInfo: CallId is invalid!");
        return;
    }

    pstCallEntity = AT_PS_GetCallEntity(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId);
    pstIpv6RaInfo = &pstCallEntity->stIpv6RaInfo;

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* ��ȡ��IPv6��ַǰ׺��, �ϱ������ӽ��^DCONN */
    if (VOS_FALSE == pstIpv6RaInfo->bitOpPrefixAddr)
    {
        /* IPv6���ųɹ� */
        AT_PS_SndCallConnectedResult(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6);

        /* ��¼IPv6ǰ׺ */
        pstIpv6RaInfo->bitOpPrefixAddr    = VOS_TRUE;
        pstIpv6RaInfo->ulPrefixBitLen     = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        PS_MEM_CPY(pstIpv6RaInfo->aucPrefixAddr,
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* ����IPv6ȫ�ֵ�ַ */
        if (VOS_TRUE == AT_IsApPort((VOS_UINT8)pstRaInfoNotifyInd->stCtrl.usClientId))
        {
            AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr);
        }
        else
        {
            AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr,
                                             TAF_IPV6_ADDR_LEN);
        }

        /* ��¼IPv6ȫ�ֵ�ַ */
        pstIpv6RaInfo->bitOpLanAddr       = VOS_TRUE;
        PS_MEM_CPY(pstIpv6RaInfo->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* ����DHCPV6��Ϣ�е�IPv6ȫ�ֵ�ַ */
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
    }

    /* ��¼Preferred Lifetime */
    pstIpv6RaInfo->bitOpPreferredLifetime = VOS_TRUE;
    pstIpv6RaInfo->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* ��¼Valid Lifetime */
    pstIpv6RaInfo->bitOpValidLifetime     = VOS_TRUE;
    pstIpv6RaInfo->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* ��¼IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstIpv6RaInfo->bitOpMtuSize       = VOS_TRUE;
        pstIpv6RaInfo->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    return;
}


VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstBackProcExtCause = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulCnt;

    ulRslt = VOS_FALSE;

    /* ����Ƿ�ƥ��ܾ�ԭ��ֵΪ#28 */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == enCause)
    {
        ulRslt = VOS_TRUE;
    }

    /* ����Ƿ�ƥ���û�����ԭ��ֵ */
    pstBackProcExtCause = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);

    for (ulCnt = 0; ulCnt < pstBackProcExtCause->ulCauseNum; ulCnt++)
    {
        if (pstBackProcExtCause->aenPsCause[ulCnt] == enCause)
        {
            ulRslt = VOS_TRUE;
            break;
        }
    }

    return ulRslt;
}


VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    ulRslt          = VOS_ERR;
    ucCid           = 0;
    pstUsrDialParam = &(AT_PS_GetCallEntity(usClientId, ucCallId)->stUsrDialParam);
    enCallState     = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    if (AT_PDP_STATE_IDLE == enCallState)
    {
#ifdef DMT
        ucCid = TAF_APS_FindCidForDial(WUEPS_PID_AT);

        /* ��д���Ų��� */
        AT_PS_GenCallDialParam(&stCallDialParam,
                               pstUsrDialParam,
                               ucCid,
                               enPdpType);

        /* ���𼤻����� */
        if (VOS_OK == AT_PS_SetupCall(usClientId, ucCallId, &stCallDialParam))
        {
            ulRslt = VOS_OK;
        }
#else
        /* ����һ��δ�����CID���м��� */
        if (VOS_OK == TAF_AGENT_FindCidForDial(usClientId, &ucCid))
        {
            /* ��д���Ų��� */
            AT_PS_GenCallDialParam(&stCallDialParam,
                                   pstUsrDialParam,
                                   ucCid,
                                   enPdpType);

            /* ���𼤻����� */
            if (VOS_OK == AT_PS_SetupCall(usClientId, ucCallId, &stCallDialParam))
            {
                ulRslt = VOS_OK;
            }
        }
#endif
    }
    else
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}
VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    ulRslt      = VOS_ERR;
    ucCid       = AT_PS_GetCidByCallType(usClientId, ucCallId, enPdpType);
    enCallState = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    switch (enCallState)
    {
        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_ACTING:
            if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         usClientId,
                                         0,
                                         ucCid))
            {
                ulRslt = VOS_OK;

                AT_PS_SetCallStateByType(usClientId, ucCallId, enPdpType, AT_PDP_STATE_DEACTING);
            }
            else
            {
                AT_ERR_LOG("AT_PS_HangupSingleStackConn: Hangup call failed!");
            }
            break;

        case AT_PDP_STATE_DEACTING:
            ulRslt = VOS_OK;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            break;
    }

    return ulRslt;
}


VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* ����ԭ��ֵ��#52ԭ��ֵ����Ҫ������һ��PDP���� */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        switch (pstEvent->stPdpAddr.enPdpType)
        {
            case TAF_PDP_IPV4:
                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
                {
                    /* ��¼���д����� */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* �ϱ�IPv6����ʧ�� */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV6,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            case TAF_PDP_IPV6:
                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
                {
                    /* ��¼���д����� */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* �ϱ�IPv4����ʧ�� */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV4,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            default:
                AT_WARN_LOG("AT_PS_ProcDualStackCallConn: PDP type is invalid!");
                break;
        }
    }
    else
    {
        /* ����ԭ��ֵ, ֪ͨAPP���Ž�� */
        switch (pstEvent->enCause)
        {
            /* ԭ��ֵ#50 (IPv4 ONLY), ֪ͨAPPģ��IPv6����ʧ�� */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:

                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         pstEvent->enCause);

                break;

            /* ԭ��ֵ#51 (IPv6 ONLY), ֪ͨAPPģ��IPv4����ʧ�� */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:

                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV4,
                                         pstEvent->enCause);

                break;

            /* ����ԭ��ֵ, ������ */
            default:
                AT_NORM_LOG1("AT_PS_ProcDualStackCallConn: Other <Cause>", pstEvent->enCause);
                break;
        }
    }

    return;
}
VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
           IPV6��PDP������У�TAF_PDP_IPV6���쳣������û�����IPV6��PDP
           ���������ظ�IPV4�ļ����ʱҲ��Ҫ���·���IPV6��PDP���� */
        case TAF_PDP_IPV4:
            if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
            {
                /* ��¼���д����� */
                AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                /* �ϱ�IPv6����ʧ�� */
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
            }
            break;

        /* ������PDP������˹���ʵ�� */
        case TAF_PDP_IPV4V6:

            /* ����IPv6��Ӧ��CIDΪ��Ч */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

            /* ����PDP�л���IDLE̬ */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv4ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}
VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV6:
            /* �������������PDP���ˣ���ǰ��PDP����ܾ��󣬷ֱ���IPV4��
               IPV6��PDP����, IPV6������ٷ���IPV4��PDP���� */
            break;

        /* ������PDP������˹���ʵ�� */
        case TAF_PDP_IPV4V6:

            /* ����IPv4��Ӧ��CIDΪ��Ч */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

            /* ����PDP�л���IDLE̬ */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv6ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}
VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_OK;

    if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
    {
        /* ��д���Ų��� */
        AT_PS_GenCallDialParam(&stCallDialParam,
                               &pstCallEntity->stUsrDialParam,
                               pstCallEntity->stUserInfo.ucUsrCid,
                               TAF_PDP_IPV6);

        /* ����IPv4���͵�PDP�������� */
        if (VOS_OK != AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
        {
            ulRslt = VOS_ERR;
        }
    }

    return ulRslt;
}


VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_ERR;

    /* ��д���Ų��� */
    AT_PS_GenCallDialParam(&stCallDialParam,
                           &pstCallEntity->stUsrDialParam,
                           pstCallEntity->stUserInfo.ucUsrCid,
                           TAF_PDP_IPV4);

    /* ����IPv4���͵�PDP�������� */
    if (VOS_OK == AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}
#endif


VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* ����IPv4����PDP״̬�л�������״̬ */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* ����IPv4���͵�DHCP */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* �ϱ�IPv4����״̬ */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* ����������PDP�����¼� */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* ��FCע�����ص� */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* ��ָ��CID��PDP�ļ���״̬����Ϊ����̬ */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ����û��������IPV4V6����Ҫ������һ��PDP */
    if (VOS_TRUE == AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv4ConnSuccFallback(ucCallId, pstEvent);
    }
#endif

    return;
}
VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* �û�����IPv4v6���͵�PDP����, ���ұ�����ܾ�, ԭ��Ϊ28, Э��ջ��Ҫ
       �ֱ���IPv4/IPv6���͵�PDP����, Э��ջ���ȷ���IPv4, �ٷ���IPv6,
       ���IPv4���͵�PDP�����ٴα�����ܾ�, Э��ջ����Ҫ����IPV6���͵�
       PDP����Ϊ�˷�ֹPDP����Ƕ��, ���IPv6���͵�PDP����ʧ��, �����ٳ���
       IPv4���͵�PDP���� */

#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enPreCallState;

    enPreCallState = AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);
#endif

    /* ����IPv4��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* ��IPv4���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv4����ʧ�� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    if ( (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
      && (AT_PDP_STATE_ACTING == enPreCallState) )
    {
        if (VOS_OK == AT_PS_ProcIpv4ConnFailFallback(ucCallId, pstEvent))
        {
            return;
        }
        else
        {
            /* ��¼���д����� */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

            /* �ϱ�IPv6����ʧ�� */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
        }
    }
#endif

    /* �ͷź���ʵ�� */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}
VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* ����IPv4��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* ��IPv4���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv4ȥ���� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* ����������PDPȥ�����¼� */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* ��FCȥע�����ص� */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* ������CID������ͨ����ӳ���ϵ */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ���IPv6���͵�PDP�����ڼ���״̬, ��Ҫ����ȥ���� */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
        {
            return;
        }

        if (TAF_PDP_IPV4 == AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
        {
            /* �ϱ�IPv6���ŶϿ� */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     TAF_PS_CAUSE_SUCCESS);
        }
    }
#endif

    /* ���PDPʵ�� */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* ����IPv6����״̬�л�������״̬ */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* ����IPV6��ַ */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* ����������PDP�����¼� */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* ��FCע�����ص� */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* ��ָ��CID��PDP�ļ���״̬����Ϊ����̬ */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    /* ����û��������IPV4V6����Ҫ������һ��PDP */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv6ConnSuccFallback(ucCallId, pstEvent);
    }

    return;
}


VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4v6����״̬�л�������״̬ */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* ����IPV4��ַ */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* ����IPV6��ַ */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* �ϱ�IPv4����ָʾ, IPv6���͵ļ���ָʾ��Ҫ�ڻ�ȡRA��Ϣ���ϱ� */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* ����������PDP�����¼� */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* ��FCע�����ص� */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* ��ָ��CID��PDP�ļ���״̬����Ϊ����̬ */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    return;
}
VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* ���IPv6����, �Ͳ���Ҫ�ٳ���IPv4, ��Ϊǰ���Ѿ������IPv4���͵�PDP
       ����, ����ٷ���IPv4���͵�PDP����Ļ�, ���ܻᵼ��PDP����Ƕ�� */

    /* ����IPv6��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* ��IPv6���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv6ȥ���� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* ��ͬһ��ʵ���е�IPV4״̬ΪIDLE����Ҫ���ʵ�� */
    if (AT_PDP_STATE_IDLE == AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        /* �ͷź���ʵ�� */
        AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    }

    return;
}


VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* ����IPv4v6��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* ��IPv4v6���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPv4v6����ʧ�ܻ��˴��� */
    if (VOS_TRUE == AT_PS_MatchIpv4v6ConnFailFallbackCause(pstEvent->enCause))
    {
        if (VOS_OK == AT_PS_ProcIpv4v6ConnFailFallback(ucCallId, pstEvent))
        {
            return;
        }
        else
        {
            /* ��¼���д����� */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);
        }
    }

    /* �ϱ�IPv4����ʧ�� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
    /* �ϱ�IPv6����ʧ�� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));

    /* �ͷź���ʵ�� */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}


VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* ����IPv6��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* ��IPv6���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv6ȥ���� */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* ����������PDPȥ�����¼� */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* ��FCȥע�����ص� */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* ������CID������ͨ����ӳ���ϵ */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* ���IPv4���͵�PDP�����ڼ���״̬, ��Ҫ����ȥ���� */
    if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        return;
    }

    /* �ͷź���ʵ�� */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}
VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* ����IPv4v6��Ӧ��CIDΪ��Ч */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* ��IPv4v6���͵�PDP״̬�л���IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* �ϱ�IPv4��IPv6���ӶϿ�ָʾ */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4V6,
                             pstEvent->enCause);

    /* ����������PDPȥ�����¼� */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* ��FCȥע�����ص� */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* ������CID������ͨ����ӳ���ϵ */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* �ͷ�CALLID��CID��ӳ���ϵ */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* ���PDPʵ�� */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}
#endif


VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallConnectedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* ����PDP���ͷֱ���*/
    switch (pstEvent->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            /* ����IPv4��PDP����ɹ��¼� */
            AT_PS_ProcIpv4CallConnected(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ����IPv6��PDP����ɹ��¼� */
            AT_PS_ProcIpv6CallConnected(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* ����IPv4v6��PDP����ɹ��¼� */
            AT_PS_ProcIpv4v6CallConnected(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallConnectedEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}


VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallRejectEvent:ERROR: CallId is invalid!");
        return;
    }

    /* ����PDP���ͷֱ���*/
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV4:
            /* ����IPv4��PDP������¼� */
            AT_PS_ProcIpv4CallReject(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ����IPv6��PDP������¼� */
            AT_PS_ProcIpv6CallReject(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* ����IPv4v6��PDP������¼� */
            AT_PS_ProcIpv4v6CallReject(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}


VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallEndedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* ����PDP���ͷֱ���*/
    switch ( pstEvent->enPdpType )
    {
        case TAF_PDP_IPV4:
            /* ����IPv4��PDPȥ�����¼� */
            AT_PS_ProcIpv4CallEnded(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ����IPv6��PDPȥ�����¼� */
            AT_PS_ProcIpv6CallEnded(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* ����IPv4v6��PDPȥ�����¼� */
            AT_PS_ProcIpv4v6CallEnded(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}


VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf)
{
    /* (1) ��CID����ɺ���ʵ������
     * (2) ������ʵ��������Ч��
     * (3) �����д�����&��ǰ����״̬
     *     ����ɹ�
     *     ->�޴���
     *     ���ʧ��
     *     ->�ϱ�^DEND
     *     ->���CALLID��CID��ӳ��
     *     ->�ͷź���ʵ��
     */
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCallId;

    /* ��ȡCID�����ĺ���ʵ������(CallId) */
    ucCallId = AT_PS_TransCidToCallId(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    enCallState = AT_PS_GetCallStateByCid(pstCallOrigCnf->stCtrl.usClientId, ucCallId, pstCallOrigCnf->ucCid);

    if (TAF_PS_CAUSE_SUCCESS != pstCallOrigCnf->enCause)
    {
        switch (enCallState)
        {
            case AT_PDP_STATE_ACTING:
            case AT_PDP_STATE_DEACTING:

                /* ���ö�Ӧ��CIDΪ��Ч */
                AT_PS_SetCid2CurrCall(pstCallOrigCnf->stCtrl.usClientId,
                                      ucCallId,
                                      AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                      AT_PS_CALL_INVALID_CID);

                /* ���ö�Ӧ��PDP״̬�л���IDLE */
                AT_PS_SetCallStateByType(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         AT_PDP_STATE_IDLE);

                /* �ϱ�����ʧ�� */
                AT_PS_SndCallEndedResult(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         pstCallOrigCnf->enCause);

                /* ���CALLID��CID��ӳ�� */
                AT_PS_FreeCallIdToCid(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

                break;

            default:
                AT_WARN_LOG1("AT_PS_ProcCallOrigCnfEvent: State is invalid! <state>", enCallState);
                break;
        }

        if (VOS_TRUE == AT_PS_IsLinkDown(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
        {
            /* �ͷź���ʵ�� */
            AT_PS_FreeCallEntity(pstCallOrigCnf->stCtrl.usClientId, ucCallId);
        }
    }
    return;
}


VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf)
{
    /* (1) ��CID����ɺ���ʵ������
     * (2) ������ʵ��������Ч��
     * (3) �����д�����
     *     ����ɹ�
     *     ->�޴���
     *     ���ʧ��
     *     ->�쳣(��ӡ)
     */

    /* ��ȡCID�����ĺ���ʵ������(CallId)
     * (A) CallId��Ч
     *     -> ����
     * (B) CallId��Ч
     *     -> ����
     */
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstCallEndCnf->stCtrl.usClientId, pstCallEndCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallEndCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    if (TAF_ERR_NO_ERROR != pstCallEndCnf->enCause)
    {
        AT_ERR_LOG1("AT_PS_ProcCallOrigCnfEvent: End call failed! <cause>", pstCallEndCnf->enCause);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_ProcCallModifyEvent
 ��������  : APP�˿ڴ���modify��Ϣ
 �������  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucUserCid;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ulRmNetId = 0;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, pstEvent->ucCid);

    if (!AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        /* AT+CGACT���ţ��û�����CGCMODE�����෢��MODIFY IND */
        AT_NotifyFcWhenAppPdpModify(ucIndex, pstEvent);
    }
    else
    {
        /* AT^NDISDUP���ţ��û�����CGCMODE�����෢��MODIFY IND */
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

        /* ��ȡ��Ӧ���û�CID */
        ucUserCid = pstModemPsCtx->astCallEntity[ucCallId].stUserInfo.ucUsrCid;

        /* ��ȡ�û�CID��Ӧ������ID */
        ulRmNetId = pstModemPsCtx->astChannelCfg[ucUserCid].ulRmNetId;

        /* ��ȡ����ID��Ӧ��FC ID */
        enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

        if (enDefaultFcId >= FC_ID_BUTT)
        {
            return VOS_ERR;
        }

        AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);
    }

    return VOS_OK;
}
VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID                       enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    PS_MEM_SET(&stRegFcPoint, 0, sizeof(FC_REG_POINT_STRU));

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((VOS_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
         return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE         == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: data channel id is abnormal.\n");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
        return;
    }

    /* ��ȡ��ǰ����QOS��Ӧ���������ȼ� */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    /* ������ص��Ƿ��Ѿ�ע�� */
    ulRet = AT_GetFcPriFromMap(enFcId ,&stFCPriOrg);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: AT_GetFcPriFromMap Err.\n");
    }

    if (VOS_TRUE == stFCPriOrg.ulUsed)
    {
        /* �����ǰFC���ȼ���֮ǰ���ص�FC���ȼ���, ��ô�������ȼ� */
        if (enFCPri > stFCPriOrg.enFcPri)
        {
            AT_ChangeFCPoint(&pstEvent->stCtrl, enFCPri, enFcId);
        }

        /* ����ͨ����RABIDӳ���ϵ */
        FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

        AT_INFO_LOG("AT_PS_RegHsicFCPoint: FC is already registered.");

        return;
    }

    /* ����ͨ����RABIDӳ���ϵ */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    stRegFcPoint.enModemId          = enModemId;
    /* ����������������ȼ�RAB QoS���ȼ�������,���ȼ��ı�ʱ����Ҫ�ı����ȼ� */
    /*  FC_PRI_3        ��������ȼ��ĳ���
        FC_PRI_4        ��NONGBR����
        FC_PRI_5        ��GBR���� */
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);

    /* ע�����ص�,��Ҫ�ֱ�ע��MEM,CPU,CDS��GPRS�� */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return;
    }

    /* ����FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = enFCPri;

    /* ��������Ϣ */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_DeRegHsicFCPoint
 ��������  : ȥע��hsic���ص�
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID                       enDataChannelId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
         return;
    }

    /* ɾ������ģ��ӳ���ϵ */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return;
    }

    /* ���FCID��FC Pri��ӳ���ϵ */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = FC_PRI_BUTT;

    /* ��������Ϣ */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_RegAppFCPoint
 ��������  : ע��APPͨ�����ص�
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��24��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RM_NET_ID_BUTT))
    {
        ulRmNetId = pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /* ������֧���ܱ�֤��������Ч�� */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* ���FC IDδע�ᣬ��ôע������ص㡣*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* ע��APP����ʹ�õ����ص� */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, (VOS_UINT8)ulRmNetId);
        }
        else
        {
            /* APP����ֻʹ����͵�����QOS���ȼ�FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_PS_RegAppFCPoint: No need to change the default QOS priority.");
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_DeRegAppFCPoint
 ��������  : ȥע��APPͨ�����ص�
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��24��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* Ѱ�����׵�ͨ��ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RM_NET_ID_BUTT))
    {
        ulRmNetId = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /* ������֧���ܱ�֤��������Ч�� */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    /* ȥע��APP����ʹ�õ����ص� */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}
VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    for (ucCallId = 0; ucCallId < AT_PS_MAX_CALL_NUM; ucCallId++)
    {
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

        if (VOS_FALSE == pstCallEntity->ulUsedFlg)
        {
            break;
        }
    }

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        return VOS_ERR;
    }

    pstCallEntity->ulUsedFlg = VOS_TRUE;

    *pucCallId = ucCallId;

    return VOS_OK;
}


VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    /* ���CID��ͨ���Ĺ�ϵ */
    AT_CleanAtChdataCfg(usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    PS_MEM_SET(&pstCallEntity->stUserInfo,
               0x00, sizeof(AT_PS_USER_INFO_STRU));

    pstCallEntity->ulUsedFlg   = VOS_FALSE;
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&pstCallEntity->stIpv4DhcpInfo,
               0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&pstCallEntity->stIpv6RaInfo,
               0x00, sizeof(AT_IPV6_RA_INFO_STRU));
    PS_MEM_SET(&pstCallEntity->stIpv6DhcpInfo,
               0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));
#endif

    return;
}
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) �������״̬�����ѽ���/���ڽ���: ����TRUE
     * (2) ��������: ����FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkUpFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkUpFlg   = VOS_FALSE;

    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }
#endif

    return ulLinkUpFlg;
}


VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) ���Ⲧ�����Ӵ���DEACTING, ����TRUE
     * (2) ��������, ����FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_FALSE;

    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }
#endif

    return ulLinkDownFlg;
}


VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) IPv4��IPv6���Ӷ�����IDLE, ����TRUE
     * (2) ��������, ����FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_TRUE;

    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }
#endif

    return ulLinkDownFlg;
}


VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) ���ݺ���ʵ���е��û����Ͳ��, ��ȡ���ӽ���״̬�ϱ�����ָ��
     * (2) ��ȡ��������״̬, ��������״̬���ϱ�
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    pstCallEntity    = AT_PS_GetCallEntity(usClientId, ucCallId);

    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        if (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }

#if (FEATURE_ON == FEATURE_IPV6)
        if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
          && (VOS_TRUE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr) )
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallConnState: pRptConnRsltFunc is NULL.");
    }

    return;
}


VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) ���ݺ���ʵ���е��û����Ͳ��, ��ȡ���ӽ���״̬�ϱ�����ָ��
     * (2) ��ȡ��������״̬, ���ڶϿ�״̬���ϱ�
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    pstCallEntity   = AT_PS_GetCallEntity(usClientId, ucCallId);
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv4State)
        {
            pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                            pstCallEntity->stUserInfo.enPortIndex,
                            TAF_PDP_IPV4,
                            TAF_PS_CAUSE_SUCCESS);
        }

#if (FEATURE_ON == FEATURE_IPV6)
        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
            {
                pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                                pstCallEntity->stUserInfo.enPortIndex,
                                TAF_PDP_IPV6,
                                TAF_PS_CAUSE_SUCCESS);
            }
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}


VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex)
{
    /* (1) �����û����Ͳ��, ��ȡ���ӶϿ�״̬�ϱ�����ָ��
     * (2) �ϱ��������ӶϿ�״̬
     */

    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    PS_MEM_SET(&stUsrInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));

    AT_PS_ParseUsrInfo(ucIndex, &stUsrInfo);

    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(stUsrInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                        stUsrInfo.enPortIndex,
                        TAF_PDP_IPV4,
                        TAF_PS_CAUSE_SUCCESS);

#if (FEATURE_ON == FEATURE_IPV6)
        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                            stUsrInfo.enPortIndex,
                            TAF_PDP_IPV6,
                            TAF_PS_CAUSE_SUCCESS);
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportAllCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}


VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex)
{
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg = VOS_NULL_PTR;

    /* ����������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: No parameter input.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���������� */
    if (gucAtParaIndex > 6)
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Parameter number is %d.\n", gucAtParaIndex);
        return AT_TOO_MANY_PARA;
    }

    /* ��� CID */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing CID.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���� CONN: �ò�������ʡ��, 1��ʾ��������, 0��ʾ�Ͽ��Ͽ����� */
    if (0 == gastAtParaList[1].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing connect state.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��� APN */
    if (0 != gastAtParaList[2].usParaLen)
    {
        /* APN���ȼ�� */
        if (gastAtParaList[2].usParaLen > TAF_MAX_APN_LEN)
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: APN is too long.");
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* APN��ʽ��� */
        if (VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                        gastAtParaList[2].usParaLen))
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: Format of APN is wrong.");
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* ��� Username */
    if (gastAtParaList[3].usParaLen > TAF_MAX_GW_AUTH_USERNAME_LEN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��� Password */
    if (gastAtParaList[4].usParaLen > TAF_MAX_GW_AUTH_PASSWORD_LEN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ͨ��ӳ�� */
    pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if ( (VOS_FALSE == pstChanCfg->ulUsed)
      || (AT_PS_INVALID_RMNET_ID == pstChanCfg->ulRmNetId) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}


VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    enUserIndex = ucIndex;

    /* PCUI��������PCUI��ģ��NDISDUP���� */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            enUserIndex = (VOS_UINT8)AT_GetPcuiUserClientId();
        }
    }

    /* CTRL��������CTRL��ģ��NDISDUP���� */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            enUserIndex = (VOS_UINT8)AT_GetCtrlUserClientId();
        }
    }

    pstUserInfo->enPortIndex = ucIndex;
    pstUserInfo->enUserIndex = enUserIndex;
    pstUserInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUserInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}


VOS_UINT32 AT_PS_ParseUsrDialParam(
    VOS_UINT8                           ucIndex,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam
)
{
    /* �ɵ����߱�֤��κͳ�����Ч�� */

    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));

    /* CID */
    pstUsrDialParam->ucCid         = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* APN */
    pstUsrDialParam->ucAPNLen      = (VOS_UINT8)gastAtParaList[2].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucAPN,
               gastAtParaList[2].aucPara,
               gastAtParaList[2].usParaLen);

    /* Username */
    pstUsrDialParam->usUsernameLen = (VOS_UINT16)gastAtParaList[3].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucUsername,
               gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    /* Password */
    pstUsrDialParam->usPasswordLen = (VOS_UINT16)gastAtParaList[4].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucPassword,
               gastAtParaList[4].aucPara,
               gastAtParaList[4].usParaLen);


    /* AUTH TYPE */
    if (gastAtParaList[5].usParaLen > 0)
    {
        pstUsrDialParam->usAuthType = AT_CtrlGetPDPAuthType(gastAtParaList[5].ulParaValue,
                                                                gastAtParaList[5].usParaLen);
    }
    else
    {
        /* ����û��������볤�Ⱦ���Ϊ0, �Ҽ�Ȩ����δ����, ��Ĭ��ʹ��CHAP���� */
        if ( (0 != gastAtParaList[3].usParaLen)
          && (0 != gastAtParaList[4].usParaLen) )
        {
            pstUsrDialParam->usAuthType = PPP_CHAP_AUTH_TYPE;
        }
        else
        {
            pstUsrDialParam->usAuthType = PPP_NO_AUTH_TYPE;
        }
    }

    /* ADDR: �ݲ����� */

    /* PDN TYPE */
#ifdef DMT
    ulRslt = MN_APS_GetPdpCidPara(&stPdpCtxInfo, pstUsrDialParam->ucCid);
#else
    ulRslt = TAF_AGENT_GetPdpCidPara(&stPdpCtxInfo, ucIndex, pstUsrDialParam->ucCid);
#endif

    if ( (VOS_OK == ulRslt)
      && (AT_PS_IS_PDP_TYPE_SUPPORT(stPdpCtxInfo.stPdpAddr.enPdpType)) )
    {
        pstUsrDialParam->enPdpType = stPdpCtxInfo.stPdpAddr.enPdpType;
    }
    else
    {
        pstUsrDialParam->enPdpType = TAF_PDP_IPV4;
    }

#if(FEATURE_ON == FEATURE_IPV6)
    if (VOS_OK != AT_CheckIpv6Capability(pstUsrDialParam->enPdpType))
    {
        AT_INFO_LOG("AT_PS_ParseUsrDialParam: PDP type is not supported.");

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_PS_SetCurrCallType
 ��������  : ���õ�ǰ��������
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_SetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->enCurrPdpType = enPdpType;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_GetCurrCallType
 ��������  : ��ȡ��ǰ��������
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : TAF_PDP_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    return pstCallEntity->enCurrPdpType;
}

/*****************************************************************************
 �� �� ��  : AT_PS_TransferQosPara
 ��������  : QOS����ת��TAF_PS_PDP_QOS_QUERY_PARA_STRU-->TAF_PS_PDP_QOS_SET_PARA_STRU
 �������  : VOS_UINT8                           ucCid,
             TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
 �������  : TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PS_TransferQosPara(
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
)
{
    if (VOS_TRUE == pstQosQueryPara->ucQosFlag)
    {
        pstQosSetPara->stQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stQos.ucCid = ucCid;

        pstQosSetPara->stQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stQos.ucTrafficClass    = pstQosQueryPara->stQos.ucTrafficClass;

        pstQosSetPara->stQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverOrder    = pstQosQueryPara->stQos.ucDeliverOrder;

        pstQosSetPara->stQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverErrSdu    = pstQosQueryPara->stQos.ucDeliverErrSdu;

        pstQosSetPara->stQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stQos.usMaxSduSize    = pstQosQueryPara->stQos.usMaxSduSize;

        pstQosSetPara->stQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitUl    = pstQosQueryPara->stQos.ulMaxBitUl;

        pstQosSetPara->stQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitDl    = pstQosQueryPara->stQos.ulMaxBitDl;

        pstQosSetPara->stQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stQos.ucResidualBer    = pstQosQueryPara->stQos.ucResidualBer;

        pstQosSetPara->stQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stQos.ucSduErrRatio    = pstQosQueryPara->stQos.ucSduErrRatio;

        pstQosSetPara->stQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stQos.usTransDelay    = pstQosQueryPara->stQos.usTransDelay;

        pstQosSetPara->stQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stQos.ucTraffHandlePrior    = pstQosQueryPara->stQos.ucTraffHandlePrior;

        pstQosSetPara->stQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitUl    = pstQosQueryPara->stQos.ulGuarantBitUl;

        pstQosSetPara->stQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitDl     = pstQosQueryPara->stQos.ulGuarantBitDl;
    }
    else
    {
        pstQosSetPara->stQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stQos.ucCid = ucCid;
    }

    if (VOS_TRUE == pstQosQueryPara->ucMinQosFlag)
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stMinQos.ucCid = ucCid;

        pstQosSetPara->stMinQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTrafficClass    = pstQosQueryPara->stMinQos.ucTrafficClass;

        pstQosSetPara->stMinQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverOrder    = pstQosQueryPara->stMinQos.ucDeliverOrder;

        pstQosSetPara->stMinQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverErrSdu    = pstQosQueryPara->stMinQos.ucDeliverErrSdu;

        pstQosSetPara->stMinQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stMinQos.usMaxSduSize    = pstQosQueryPara->stMinQos.usMaxSduSize;

        pstQosSetPara->stMinQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitUl    = pstQosQueryPara->stMinQos.ulMaxBitUl;

        pstQosSetPara->stMinQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitDl    = pstQosQueryPara->stMinQos.ulMaxBitDl;

        pstQosSetPara->stMinQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stMinQos.ucResidualBer    = pstQosQueryPara->stMinQos.ucResidualBer;

        pstQosSetPara->stMinQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stMinQos.ucSduErrRatio    = pstQosQueryPara->stMinQos.ucSduErrRatio;

        pstQosSetPara->stMinQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stMinQos.usTransDelay    = pstQosQueryPara->stMinQos.usTransDelay;

        pstQosSetPara->stMinQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTraffHandlePrior    = pstQosQueryPara->stMinQos.ucTraffHandlePrior;

        pstQosSetPara->stMinQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitUl    = pstQosQueryPara->stMinQos.ulGuarantBitUl;

        pstQosSetPara->stMinQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitDl     = pstQosQueryPara->stMinQos.ulGuarantBitDl;

    }
    else
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stMinQos.ucCid = ucCid;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_PS_SetQosPara
 ��������  : ���ò��ŵ�QOS����
 �������  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucUserCid,
             VOS_UINT8                           ucActCid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
)
{
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;
    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosSetPara;

    PS_MEM_SET(&stQosQueryPara, 0, sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));
    PS_MEM_SET(&stQosSetPara, 0, sizeof(TAF_PS_PDP_QOS_SET_PARA_STRU));

    /* �ж���Ҫ���õ�CID�Ƿ��û��·���CID��ͬ */
    if (ucActCid == ucUserCid)
    {
        return VOS_OK;
    }

#ifdef DMT
    /* ��ȡ�û����õ�QOS���� */
    if (VOS_OK != TAF_APS_GetPdpCidQosPara(&stQosQueryPara,
                                           ucUserCid))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Get QOS Fail.");
        return VOS_ERR;
    }

    /* QOS����ת�� */
    AT_PS_TransferQosPara(ucActCid, &stQosQueryPara, &stQosSetPara);

    /* ��ȡ�û����õ�QOS���� */
    if (VOS_OK != TAF_APS_SetPdpCidQosPara(&stQosSetPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Set QOS Fail.");
        return VOS_ERR;
    }
#else
    /* ��ȡ�û����õ�QOS���� */
    if (VOS_OK != TAF_AGENT_GetPdpCidQosPara(usClientId,
                                             ucUserCid,
                                             &stQosQueryPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Get QOS Fail.");
        return VOS_ERR;
    }

    /* QOS����ת�� */
    AT_PS_TransferQosPara(ucActCid, &stQosQueryPara, &stQosSetPara);

    /* ��ȡ�û����õ�QOS���� */
    if (VOS_OK != TAF_AGENT_SetPdpCidQosPara(usClientId,
                                             &stQosSetPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Set QOS Fail.");
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}
VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) ����CID�����Ĳ���
     *     -> ʧ��: ����ERROR
     *     -> �ɹ�: ����
     * (2) ����PS�����
     *     -> ʧ��: ����ERROR
     *     -> �ɹ�: ����
     * (3) ����CallIdӳ��
     * (4) ���ú���PDP����
     * (5) ���ú���CID
     * (6) ���ú���״̬
     */

    TAF_PS_DIAL_PARA_STRU               stPsDialParamInfo;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stPsDialParamInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* ����QOS���� */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_PS_GetUserInfo(usClientId, ucCallId)->ucUsrCid, pstCallDialParam->ucCid))
    {
        return VOS_ERR;
    }

    /* ��дPS���в��� */
    AT_GetPsDialParamFromAtDialParam(&stPsDialParamInfo, pstCallDialParam);

    /* ����PS����� */
    ulRslt = TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stPsDialParamInfo);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_SetupCall: Setup call failed.");
        return VOS_ERR;
    }

    /* ����CALLIDӳ�� */
    AT_PS_AssignCallIdToCid(usClientId, stPsDialParamInfo.ucCid, ucCallId);

    /* ���ú���PDP���� */
    AT_PS_SetCurrCallType(usClientId, ucCallId, stPsDialParamInfo.enPdpType);

    /* ���ú���CID */
    AT_PS_SetCid2CurrCall(usClientId, ucCallId, stPsDialParamInfo.enPdpType, stPsDialParamInfo.ucCid);

    /* ���ú���״̬ */
    AT_PS_SetCallStateByType(usClientId, ucCallId, stPsDialParamInfo.enPdpType, AT_PDP_STATE_ACTING);

    return VOS_OK;
}
VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* (1) ���IPv4���ͺ����Ƿ��ѽ���/���ڽ���
     *     -> ��: �Ͽ��ú���, ���ú���״̬
     *     -> ��: ����
     * (2) ���IPv6���ͺ����Ƿ��ѽ���/���ڽ���
     *     -> ��: �Ͽ��ú���, ���ú���״̬
     *     -> ��: ����
     * (3) ����
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
      || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State) )
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                     usClientId,
                                     0,
                                     pstCallEntity->ucIpv4Cid))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP1->End call failed.");
            return VOS_ERR;
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if ( (pstCallEntity->ucIpv4Cid != pstCallEntity->ucIpv6Cid)
      && ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
        || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State) ) )
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                     usClientId,
                                     0,
                                     pstCallEntity->ucIpv6Cid))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP2->End call step2 failed.");
            return VOS_ERR;
        }
    }
#endif

    return VOS_OK;
}


VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
)
{
    /* ����ʵ������(CallId)�ɵ����߱�֤����Ч�� */

    /* ����������ڽ���, ����OK, ͬʱ�ϱ��ѽ���������״̬ */
    if (VOS_TRUE == AT_PS_IsLinkGoingUp(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going up.");

        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallConnState(ucIndex, ucCallId);

        return VOS_OK;
    }

    /* ����������ڶϿ�, ����ERROR */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going down.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    return VOS_ERR;
}
VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex)
{
    /* (1) ��CID����ɺ���ʵ������(CallId)
     * (2) ��ȡ���Ų���
     * (3) ������ʵ��������Ч��
     *     -> ��Ч: ��������״̬�ϱ��������
     *     -> ��Ч: ��������
     * (4) ��������ʵ��
     * (5) �������
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUserInfo;
    AT_DIAL_PARAM_STRU                  stUsrDialParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stUserInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));
    PS_MEM_SET(&stUsrDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    /* ��ȡ�û���Ϣ */
    AT_PS_ParseUsrInfo(ucIndex, &stUserInfo);

    /* ��ȡ���Ų��� */
    ulRslt = AT_PS_ParseUsrDialParam(ucIndex, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_ProcDialUp: Get dial parameter failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ��ȡCID�����ĺ���ʵ������ */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, stUsrDialParam.ucCid);

    if (AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        ulRslt = AT_PS_ProcConflictDialUpWithCurrCall(ucIndex, ucCallId);

        if (VOS_OK != ulRslt)
        {
            AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

            AT_PS_FreeCallEntity(ucIndex, ucCallId);

            AT_ERR_LOG("AT_PS_ProcCallDialUp: Call entity status error.");
            return AT_ERROR;
        }

        return AT_SUCCESS;
    }

    /* ��������ʵ�� */
    ulRslt = AT_PS_AllocCallEntity(ucIndex, &ucCallId);

    if (VOS_OK != ulRslt)
    {
        AT_NORM_LOG("AT_PS_ProcDialUp: Alloc call entity failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /* �����û���Ϣ */
    pstCallEntity->stUserInfo = stUserInfo;

    /* ���沦�Ų��� */
    pstCallEntity->stUsrDialParam = stUsrDialParam;

    /* �������� */
    ulRslt = AT_PS_SetupCall(stUserInfo.enUserIndex, ucCallId, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        /* ��¼���д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        /* �ͷź���ʵ�� */
        AT_PS_FreeCallEntity(ucIndex, ucCallId);

        AT_ERR_LOG("AT_PS_ProcDialUp: Setup call failed.");
        return AT_ERROR;
    }

    return AT_OK;
}
VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex)
{
    /* (1) ��CID����ɺ���ʵ������(CallId)
     * (2) ������ʵ��������Ч��
     *     -> ��Ч: ֱ���ϱ����ӶϿ�
     *     -> ��Ч: ����
     * (3) �������״̬
     * (4) �Ͽ�����
     */

    /* ��ȡCID�����ĺ���ʵ������(CallId)
     * (A) CallId��Ч
     *     -> �ϱ�OK
     *     -> �ϱ���������^DEND(or NDISSTAT)
     *     -> ����
     * (B) CallId��Ч
     *     -> ��������
     */
    VOS_UINT8                           ucCallId;
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    pstUserInfo = AT_PS_GetUserInfo(ucIndex, ucCallId);

    if (VOS_FALSE ==  AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportAllCallEndState(ucIndex);

        return AT_SUCCESS;
    }

    /* �������״̬�Ƿ�Ϊ���ڶϿ�
     * (A) ����������ڶϿ�
     *���� -> �ϱ�OK
     *     -> �ϱ��ѶϿ�����^DEND(or NDISSTAT)
     *     -> ����SUCCESS
     * (B) ����״̬
     *     -> ��������
     */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallEndState(ucIndex, ucCallId);

        return AT_SUCCESS;
    }

    /* �ҶϺ��� */
    if (VOS_OK != AT_PS_HangupCall(pstUserInfo->enUserIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcDialDown: Hangup call failed.");
        return AT_ERROR;
    }
    return AT_OK;
}
VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* ��������Ч�� */
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    if (AT_SUCCESS != ulRslt)
    {
        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return ulRslt;
    }

    if (0 != gastAtParaList[1].ulParaValue)
    {
        ulRslt = AT_PS_ProcDialUp(ucIndex);
    }
    else
    {
        ulRslt = AT_PS_ProcDialDown(ucIndex);
    }

    return ulRslt;
}
/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc  = VOS_NULL_PTR;

    /* SHARE-PDP����δ������ֱ�ӷ��� */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* ��ȡAPP PDPʵ����Ϣ */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /* ��ȡ���ӶϿ�����ϱ�����ָ�� */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    AT_PS_SendRnicPdnInfoRelInd(pstEvent->ucRabId);

    /* ֪ͨAPPģ��PDPȥ���� */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstEvent->ucCid,
                        pstAppPdpEntity->stUsrInfo.enPortIndex,
                        enPdpType,
                        pstEvent->enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ProcDeactSharePdpState:ERROR: Get End Report Func Failed!");
    }

    /* ���APP PDPʵ�� */
    AT_PS_ResetRnicPdpDhcpPara(enPdpType);

    return;
}
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    /* SHARE-PDP����δ������ֱ�ӷ��� */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* ��ȡAPP PDPʵ����Ϣ */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /* ��ȡ���ӽ�������ϱ�����ָ�� */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    if (TAF_PDP_IPV4 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* ֪ͨAPPģ��IPv4���� */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (TAF_PDP_IPV6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV6, pstEvent);
    }

    if (TAF_PDP_IPV4V6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4V6, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* ֪ͨAPPģ��IPv4���� */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_PS_ProcSharePdpIpv6RaInfo
 ��������  : Share-PDP���Կ�������£��յ�Router Advertisement IP����, �洢��ӦPDN��Ϣ
 �������  : pstRaInfoNotifyInd         - RA������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ����

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity                      = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr                     = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc                     = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    /* SHARE-PDP����δ������ֱ�ӷ��� */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* RaInfo��Ϣ�е�ַǰ׺Ϊ��ʱ��ֱ�ӷ��� */
    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcSharePdpIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* ��ȡAPP PDPʵ�塢RaInfo��Ϣ */
    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    /* ��ȡ���ӽ�������ϱ�����ָ�� */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    /* ��ȡ��IPv6��ַǰ׺��, �ϱ������ӽ��^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* ֪ͨAPPģ��IPv6���� */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstRaInfoNotifyInd->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcSharePdpIpv6RaInfo:ERROR: Get Connet Report Func Failed!");
        }

        /* ��¼IPv6ǰ׺ */
        pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
        pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        PS_MEM_CPY(pstAppRaInfoAddr->aucPrefixAddr,
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* ����IPv6ȫ�ֵ�ַ */
        AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                         pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                         aucIpv6LanAddr);

        /* ��¼IPv6ȫ�ֵ�ַ */
        pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
        PS_MEM_CPY(pstAppRaInfoAddr->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* ����DHCPV6��Ϣ�е�IPv6ȫ�ֵ�ַ */
        PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
    }

    /* ��¼Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* ��¼Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* ��¼IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* ����RNIC PDN������Ϣ */
    AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV6, pstRaInfoNotifyInd->ucRabId, AT_APP_GetPdpEntInfoAddr());

    return;
}
#endif


VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch(enPdpType)
    {
        case TAF_PDP_IPV4:

            /* ���DHCP��Ϣ */
            AT_AppDhcpReset();

            /* ��¼IPv4����PDP��Ӧ��CID */
            pstAppPdpEntity->ucIpv4Cid  = pstEvent->ucCid;

            /* PDP״̬�л�������״̬ */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

            /* ����IPv4���͵�DHCP */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ���DHCPv6��Ϣ */
            AT_AppDhcpv6Reset();

            /* ��¼PDP���Ͷ�Ӧ��CID */
            pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

            /* ����IPv6����״̬�л�������״̬ */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

            /* ����IPV6��ַ */
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* ���DHCP��Ϣ */
            AT_AppDhcpReset();

            /* ���DHCPv6��Ϣ */
            AT_AppDhcpv6Reset();

            /* ��¼PDP���Ͷ�Ӧ��CID */
            pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

            /* ����IPv6����״̬�л�������״̬ */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

            /* ����IPV4��ַ */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

            /* ����IPV6��ַ*/
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_SaveRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}


VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    switch(ucPdpType)
    {
        case TAF_PDP_IPV4:
            /* ��IPv4���͵�PDP�л���IDLE̬ */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            /* ���DHCP��Ϣ */
            AT_AppDhcpReset();
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* ��IPv6���͵�PDP�л���IDLE̬ */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            /* ���DHCPv6��Ϣ */
            AT_AppDhcpv6Reset();
            break;

        case TAF_PDP_IPV4V6:
            /* ��IPv4\IPv6���͵�PDP�л���IDLE̬ */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

            /* ���DHCP\DHCPv6��Ϣ */
            AT_AppDhcpReset();
            AT_AppDhcpv6Reset();
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ResetRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}


VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
)
{

    AT_RNIC_PDN_INFO_CFG_IND_STRU      *pstRnicPdnCfgInd;

    /* ����AT_RNIC_PDN_INFO_CFG_IND_STRU��Ϣ */
    pstRnicPdnCfgInd = (AT_RNIC_PDN_INFO_CFG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnCfgInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstRnicPdnCfgInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstRnicPdnCfgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnCfgInd->ulReceiverPid   = ACPU_PID_RNIC;

    /* ��д��Ϣ���� */
    pstRnicPdnCfgInd->enMsgId   = ID_AT_RNIC_PDN_INFO_CFG_IND;
    pstRnicPdnCfgInd->ucRabId   = ucRabId;
    pstRnicPdnCfgInd->ucRmNetId = RNIC_RM_NET_ID_0;

    if (TAF_PDP_IPV4 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv4PdnInfo  = VOS_TRUE;

        /* ���IPv4 PDN��Ϣ */
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr       = pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulSubnetMask    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulGateWayAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsPrimAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsSecAddr    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsPrimAddr = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsSecAddr  = pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfPrimAddr = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimPCSCF;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfSecAddr  = pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4Secpcscf;
    }
    else if(TAF_PDP_IPV6 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv6PdnInfo              = VOS_TRUE;

        /* ���IPv6 PDN��Ϣ */
        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsPrimAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsSecAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfPrimAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfSecAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd:PDP type is invaild!");

        PS_FREE_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd);
        return VOS_OK;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
)
{
    AT_RNIC_PDN_INFO_REL_IND_STRU      *pstRnicPdnRelInd;

    /* ����AT_RNIC_PDN_INFO_REL_IND_STRU��Ϣ������ʼ�� */
    pstRnicPdnRelInd = (AT_RNIC_PDN_INFO_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnRelInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstRnicPdnRelInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstRnicPdnRelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnRelInd->ulReceiverPid   = ACPU_PID_RNIC;

    /* ��д��Ϣ���� */
    pstRnicPdnRelInd->enMsgId         = ID_AT_RNIC_PDN_INFO_REL_IND;
    pstRnicPdnRelInd->ucRabId         = ucRabId;
    pstRnicPdnRelInd->ucRmNetId       = RNIC_RM_NET_ID_0;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnRelInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

#if 0
/*****************************************************************************
 �� �� ��  : AT_QosParaTransferToQci
 ��������  : ����QOS����ת��ΪQCI�ȼ�
 �������  : TAF_UMTS_QOS_STRU                   *pQos
 �������  : ��
 �� �� ֵ  : QCI����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��18��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

*****************************************************************************/
ADS_QCI_TYPE_ENUM_UINT8 AT_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                  *pQos
)
{
    ADS_QCI_TYPE_ENUM_UINT8             enQci;

    /* ת������μ�: 23.401
       Annex E (normative):
        Mapping between EPS and Release 99 QoS parameters
        QCI    Traffic_Class  Traffic_Handling_Priority Signalling_Indication  Src_Stats_Descriptor
         1     Conversational          NA                       NA                  SPEECH
         2     Conversational          NA                       NA                    NA
         3     Conversational          NA                       NA                   Unknown
         4     Streaming               NA                       NA                   Unknown
         5     Interactive              1                       YES                  Unknown
         6     Interactive              1                       NO                    NA
         7     Interactive              2                       NO                    NA
         8     Interactive              3                       NO                    NA
         9     Background              NA                       NA                    NA

      NOTE��1: When QCI 2 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 150 ms. When Release 99 QoS parameter values are mapped to a QCI,
               QCI 2 is used for conversational/unknown if the Transfer Delay parameter is greater
               or equal to 150 ms.
      NOTE��2: When QCI 3 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 80 ms as the lowest possible value, according to TS 23.107 [59]. When Release
               99 QoS parameter values are mapped to a QCI, QCI 3 is used for conversational/unknown if
               the Transfer Delay parameter is lower than 150 ms.
      NOTE  3: When QCI 4 is mapped to Release 99 QoS parameter values, it is mapped to Streaming/Unknown.
               When Release 99 QoS parameter values are mapped to a QCI, Streaming/Unknown and Streaming/Speech
               are both mapped to QCI 4.
    */
    /* ����QOS trafficClass������ȡQCI */
    if (AT_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL == pQos->ucTrafficClass)
    {
        if (AT_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH == pQos->ucSrcStatisticsDescriptor)
        {
            enQci       = ADS_QCI_TYPE_QCI1_GBR;
        }
        else if (pQos->usTransDelay >= AT_APP_QOS_TRANSFER_DELAY_150MS)
        {
            enQci       = ADS_QCI_TYPE_QCI2_GBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI3_GBR;
        }
    }
    else if (AT_APP_QOS_TRAFFIC_CLASS_STREAMING == pQos->ucTrafficClass)
    {
        enQci       = ADS_QCI_TYPE_QCI4_GBR;
    }
    else if (AT_APP_QOS_TRAFFIC_CLASS_INTERACTIVE == pQos->ucTrafficClass)
    {
        if (AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1 == pQos->ucTraffHandlePrior)
        {
            if (AT_APP_QOS_SIGNAL_IND_OPTIMISE == pQos->ucSignallingIndication)
            {
                enQci       = ADS_QCI_TYPE_QCI5_NONGBR;
            }
            else
            {
                enQci       = ADS_QCI_TYPE_QCI6_NONGBR;
            }
        }
        else if (AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2 == pQos->ucTraffHandlePrior)
        {
            enQci       = ADS_QCI_TYPE_QCI7_NONGBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI8_NONGBR;
        }
    }
    else
    {
        enQci       = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    return enQci;
}
#endif
#if 0
/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */

VOS_UINT32 AT_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
)
{
    ADS_PDP_STATUS_IND_STRU            *pstMsg;

    /* ����ADS_PDP_STATUS_IND_STRU��Ϣ */
    pstMsg = (ADS_PDP_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(ADS_PDP_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SendAdsPdpStatusInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_PDP_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->enMsgId         = ID_APS_ADS_PDP_STATUS_IND;

    /* ��д��Ϣ�� */
    pstMsg->enModemId       = pstAdsInd->enModemId;
    pstMsg->ucRabId         = pstAdsInd->ucRabId;
    pstMsg->enPdpStatus     = pstAdsInd->enPdpStatus;
    pstMsg->enPdpType       = pstAdsInd->enPdpType;
    pstMsg->enQciType       = pstAdsInd->enQciType;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SendAdsPdpStatusInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID AT_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpModify:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_MODIFY;
    stAdsInd.enPdpType      = TAF_PDP_TYPE_BUTT;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = AT_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* ��ADS_DL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}
VOS_VOID AT_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpAvtivated:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_ACT;
    stAdsInd.enPdpType      = pstEvent->stPdpAddr.enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = AT_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* ��ADS_DL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}
VOS_VOID AT_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpAvtivated:Get Modem Id fail");
        return;
    }

    /* ��д���� */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_DEACT;
    stAdsInd.enPdpType      = pstEvent->enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = ADS_QCI_TYPE_BUTT;

    /* ��ADS_DL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* ��ADS_UL����PDP�޸�ָʾ */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}
/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

