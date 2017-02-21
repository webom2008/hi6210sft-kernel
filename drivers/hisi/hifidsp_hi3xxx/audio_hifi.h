/*
 *  HIFI MISC TRANS MSG
 *  Copyright (c) 1994-2013 by HISI
 *
 *   This program is distributed in the hope that we can send msg and
 *   data to hifi
 *
 */

#ifndef _AUDIO_HIFI_H
#define _AUDIO_HIFI_H

#include <linux/types.h>


typedef enum
{
    HIFI_CHN_SYNC_CMD = 0,
    HIFI_CHN_READNOTICE_CMD,
    HIFI_CHN_INVAILD_CMD
} HIFI_CHN_CMD_TYPE;

typedef struct HIFI_CHN_CMD_STRUCT
{
    HIFI_CHN_CMD_TYPE cmd_type;
    unsigned int           sn;
} HIFI_CHN_CMD;


/*
    ��Σ�͸����HIFI�Ĳ���
    ���Σ�HIFI���صģ�͸����AP�Ĳ���
*/
#if 0
struct misc_io_async_param {
    void *                  para_in;        /*���buffer*/
    unsigned int            para_size_in;   /*���buffer����*/
};
#endif
struct misc_io_async_param {
    unsigned int            para_in_l;      /*���buffer*/
    unsigned int            para_in_h;      /*���buffer*/
    unsigned int            para_size_in;   /*���buffer����*/
};


/* misc_io_sync_cmd */
#if 0
struct misc_io_sync_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  para_out;           /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};
#endif

struct misc_io_sync_param {
    unsigned int            para_in_l;           /*���buffer*/
    unsigned int            para_in_h;           /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/

    unsigned int            para_out_l;           /*����buffer*/
    unsigned int            para_out_h;           /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};

/* misc_io_senddata_cmd */
#if 0
struct misc_io_senddata_async_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  data_src;           /*������Դ��ַ*/
    unsigned int            data_src_size;      /*������Դ����*/
};
#endif
struct misc_io_senddata_async_param {
    unsigned int            para_in_l;           /*���buffer*/
    unsigned int            para_in_h;           /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/

    unsigned int            data_src_l;           /*������Դ��ַ*/
    unsigned int            data_src_h;           /*������Դ��ַ*/
    unsigned int            data_src_size;      /*������Դ����*/
};
#if 0
/* misc_io_send_recv_data_sync_cmd */
struct misc_io_senddata_sync_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  src;                /*����Դ��ַ*/
    unsigned int            src_size;           /*����Դ����*/
    void *                  dst;                /*��ַ*/
    unsigned int            dst_size;           /*����*/
    void *                  para_out;           /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};
#endif
struct misc_io_senddata_sync_param {
    unsigned int            para_in_l;          /*���buffer*/
    unsigned int            para_in_h;          /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/

    unsigned int            src_l;              /*����Դ��ַ*/
    unsigned int            src_h;              /*����Դ��ַ*/
    unsigned int            src_size;           /*����Դ����*/

    unsigned int            dst_l;              /*��ַ*/
    unsigned int            dst_h;              /*��ַ*/
    unsigned int            dst_size;           /*����*/

    unsigned int            para_out_l;         /*����buffer*/
    unsigned int            para_out_h;         /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};

#if 0
struct misc_io_get_phys_param {
    unsigned int           flag;               /**/
    unsigned int           phys_addr;          /*��ȡ��������ַ*/
};
#endif

struct misc_io_get_phys_param {
    unsigned int           flag;               /**/
    unsigned int           phys_addr_l;          /*��ȡ��������ַ*/
    unsigned int           phys_addr_h;          /*��ȡ��������ַ*/
};

#if 0
struct misc_io_dump_buf_param {
    unsigned int            user_buf;           /*�û��ռ������ڴ��ַ*/
    unsigned int            buf_size;           /*�û��ռ������ڴ泤��*/
};
#endif
struct misc_io_dump_buf_param {
    unsigned int            user_buf_l;           /*�û��ռ������ڴ��ַ*/
    unsigned int            user_buf_h;           /*�û��ռ������ڴ��ַ*/
    unsigned int            buf_size;           /*�û��ռ������ڴ泤��*/
};

//������AP����HiFi Misc�豸��ioctl�����ҪHiFi Misc�豸������Ӧ
#define HIFI_MISC_IOCTL_ASYNCMSG        _IOWR('A', 0x70, struct misc_io_async_param)          //AP��HiFi�����첽��Ϣ
#define HIFI_MISC_IOCTL_SYNCMSG         _IOW('A', 0x71, struct misc_io_sync_param)            //AP��HiFi����ͬ����Ϣ
#define HIFI_MISC_IOCTL_SENDDATA_SYNC   _IOW('A', 0x72, struct misc_io_senddata_sync_param)    //AP��HiFiͬ����������
#define HIFI_MISC_IOCTL_GET_PHYS        _IOWR('A', 0x73, struct misc_io_get_phys_param)        //AP��ȡ������ַ
#define HIFI_MISC_IOCTL_TEST            _IOWR('A', 0x74, struct misc_io_senddata_sync_param)   //AP������Ϣ
#define HIFI_MISC_IOCTL_WRITE_PARAMS    _IOWR('A', 0x75, struct misc_io_sync_param)            //д�㷨������HIFI

#define HIFI_MISC_IOCTL_DUMP_HIFI       _IOWR('A', 0x76, struct misc_io_dump_buf_param)        //��ȡHIFI��DDR�ϵ����ݲ��������û��ռ�
#define HIFI_MISC_IOCTL_DUMP_CODEC      _IOWR('A', 0x77, struct misc_io_dump_buf_param)        //��ȡCODEC�Ĵ������������û��ռ�
#define HIFI_MISC_IOCTL_DUMP_MP3_DATA   _IOWR('A', 0x78, unsigned long)        //����DDR�ϵ����ݵ�dataĿ¼��
#define HIFI_MISC_IOCTL_WAKEUP_THREAD   _IOW('A',  0x79, unsigned long)        //����read�߳�,�����˳�
#define INT_TO_ADDR(low,high) (void*) (unsigned long)((unsigned long long)(low) | ((unsigned long long)(high)<<32))
#define GET_LOW32(x) (unsigned int)(((unsigned long long)(unsigned long)(x))&0xffffffffULL)
#define GET_HIG32(x) (unsigned int)((((unsigned long long)(unsigned long)(x))>>32)&0xffffffffULL)
#endif // _AUDIO_HIFI_H
