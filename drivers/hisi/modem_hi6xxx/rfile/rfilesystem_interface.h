

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __RFILESYSTEM_INTERFACE__
#define __RFILESYSTEM_INTERFACE__

#include "rfilesystem_process.h"

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
FILE *BSP_fopen(const char *path, const char *mode);
int BSP_fseek(FILE *stream, long offset, int whence);
long BSP_ftell(FILE *stream);
int BSP_fread(void*buf,unsigned int size,unsigned int count, FILE *stream);
int BSP_fwrite(const void* buf,unsigned int size,unsigned int count,FILE *stream);
int BSP_fclose(FILE *fp);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __RFILESYSTEM_INTERFACE__ */
