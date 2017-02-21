/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uttest_nas_AdsFilter.h
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年6月15日
  最近修改   :
  功能描述   : uttest_nas_AdsFilter.cpp的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年6月15日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/
#ifndef _UTTEST_NAS_ADS_FILTER_H_
#define _UTTEST_NAS_ADS_FILTER_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AdsCtx.h"
#include "AdsFilter.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_FILTER_C

/*****************************************************************************
3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern void UT_STUB_INIT(void);
extern void UT_IMM_STUB_INIT(void);

extern ADS_FILTER_CTX_STRU                     g_stAdsFilterCtx;
extern VOS_UINT32                              g_aulAdsFilterStats[ADS_FILTER_ORIG_PKT_BUTT];

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of uttest_nas_AdsFilter.h */


