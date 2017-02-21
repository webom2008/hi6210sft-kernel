/** ****************************************************************************

                    Huawei Technologies Sweden AB (C), 2001-2011

 ********************************************************************************
 * @author    Automatically generated by DAISY
 * @version
 * @date      2014-09-04
 * @file
 * @brief
 * @copyright Huawei Technologies Sweden AB
 *******************************************************************************/
#ifndef CSDR1XCPROCDSPCM_H
#define CSDR1XCPROCDSPCM_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/
#include "uphy_type_define.h"
#include "csdr1x.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*******************************************************************************
 2. Macro definitions
*******************************************************************************/


/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/
/** ****************************************************************************
 * Name        : CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16
 * Description : 
 *******************************************************************************/
enum CSDR1XCPROCDSPCM_MSG_TYPE_ENUM
{
    ID_CPROC_CSDR_1X_RXOFF_REQ                              = 0x0100, /* _H2ASN_MsgChoice CPROC_CSDR_1X_RXOFF_REQ_STRU*/ /**< @sa CPROC_CSDR_1X_RXOFF_REQ_STRU */
    ID_CSDR_CPROC_1X_RXOFF_CNF                              = 0x0101, /* _H2ASN_MsgChoice CSDR_CPROC_1X_RXOFF_CNF_STRU*/ /**< @sa CSDR_CPROC_1X_RXOFF_CNF_STRU */
    ID_CPROC_CSDR_1X_RXON_REQ                               = 0x0102, /* _H2ASN_MsgChoice CPROC_CSDR_1X_RXON_REQ_STRU*/ /**< @sa CPROC_CSDR_1X_RXON_REQ_STRU */
    ID_CSDR_CPROC_1X_RXON_CNF                               = 0x0103, /* _H2ASN_MsgChoice CSDR_CPROC_1X_RXON_CNF_STRU*/ /**< @sa CSDR_CPROC_1X_RXON_CNF_STRU */
    ID_CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_BUTT                  = 0xFFFF
};
typedef PHY_UINT16 CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16;


/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/
/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_RXOFF_REQ_STRU
 * Description : This signal is used to request Rx Off at a specific time (or
 * NOW).
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                         /* _H2ASN_Skip */
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;       /* _H2ASN_Skip */
    PHY_UINT16                                              uhwOpId;
    PHY_UINT32                                              aulRX_OffTime[2]; /**<  0xFFFFFFFF, 0xFFFFFFFF =>NOW */
}CPROC_CSDR_1X_RXOFF_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_RXOFF_CNF_STRU
 * Description : This signal is sent when CSDR has turned the radio off after
 * an RXOFF request.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId; /* _H2ASN_Skip */
    PHY_UINT16                                              uhwOpId;
}CSDR_CPROC_1X_RXOFF_CNF_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_RXON_REQ_STRU
 * Description : This signal is used to request RxOn on a certain frequency at
 * a specific time (or NOW).
 * The signal is also used to change frequency if the radio was already on.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                        /* _H2ASN_Skip */
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;      /* _H2ASN_Skip */
    PHY_UINT16                                              uhwOpId;
    PHY_UINT32                                              auwRxOnTime[2];  /**<  Time or NOW = 0xFFFFFFFF, 0xFFFFFFFF */
    CSDR_1X_ANTENNA_IND_ENUM_UINT16                         enUseAntenna; /**<  In TCH Main and diversity antenna may be used. in other states Main antenna only */
    PHY_UINT16                                              uhwReserved;  /**<  32 bit alignment */
    CSDR_1X_FREQ_INFO_STRU                                  stFreqInfo;   /**<  Frequency and Band Class */
}CPROC_CSDR_1X_RXON_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_RXON_CNF_STRU
 * Description : This signal is sent when CSDR has turned the radio on after
 * an RXON request, or has changed frequency if the radio was already on.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId; /* _H2ASN_Skip */
    PHY_UINT16                                              uhwOpId;
}CSDR_CPROC_1X_RXON_CNF_STRU;


/*******************************************************************************
 8. Global  declaration
*******************************************************************************/

/*******************************************************************************
 9. Function declarations
*******************************************************************************/

/*******************************************************************************
 * Name        : CSDR_1X_Rxoff
 * Description : 
 *******************************************************************************/
void CSDR_1X_Rxoff(PHY_UINT32* aulRX_OffTime);

/*******************************************************************************
 * Name        : CSDR_1X_Rxon
 * Description : 
 *******************************************************************************/
void CSDR_1X_Rxon(PHY_UINT32* auwRxOnTime,
                  const CSDR_1X_FREQ_INFO_STRU * stFreqInfo);
/** ****************************************************************************
 * Name        : CSDR1XCPROCDSPCM_MSG_DATA
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;     /* _H2ASN_MsgChoice_Export CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16 */
    PHY_UINT8                                               aucMsgBlock[2];

    /* _H2ASN_MsgChoice_When_Comment CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16 */
}CSDR1XCPROCDSPCM_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : CSDR1XCPROCDSPCM
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XCPROCDSPCM_MSG_DATA           stMsgData;
}CSDR1XCPROCDSPCM;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif