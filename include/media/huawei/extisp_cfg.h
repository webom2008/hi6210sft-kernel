


#ifndef __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__
#define __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>

typedef struct _tag_hwcam_config_data hwcam_config_data_t;


typedef enum _tag_hwcam_config_type
{
    HWCAM_EXTISP_POWERON,
    HWCAM_EXTISP_POWEROFF,
    HWCAM_EXTISP_LOADFW,
    HWCAM_EXTISP_CMD,

    //TODO...

} hwcam_config_type_t;

/* 32-bit cmd mask */
enum
{
	EXTISP_CMD_DIR_FLAG_SHIT = 30,		/* [31:30] CMD dirction type */
	EXTISP_CMD_RESP_FLAG_SHIT = 29,		/* [   29] CMD response type */
	EXTISP_CMD_LEN_SHIT = 16,			/* [27:16] CMD len */
	EXTISP_CMD_OPCODE_SHIT = 0,			/* [15: 0] CMD opcode */

	EXTISP_CMD_DIR_FLAG_MASK = (0x3UL << EXTISP_CMD_DIR_FLAG_SHIT),
	EXTISP_CMD_RESP_FLAG_MASK = (0x1UL << EXTISP_CMD_RESP_FLAG_SHIT),
	EXTISP_CMD_LEN_MASK = (0xfffUL << EXTISP_CMD_LEN_SHIT),
	EXTISP_CMD_OPCODE_MASK = (0xffffUL << EXTISP_CMD_OPCODE_SHIT),
};

/* cmd direction type */
enum
{
	EXTISP_SET_CMD	 = 0x1 << EXTISP_CMD_DIR_FLAG_SHIT,
	EXTISP_GET_CMD	 = 0x2 << EXTISP_CMD_DIR_FLAG_SHIT,
	EXTISP_INOUT_CMD = 0x3 << EXTISP_CMD_DIR_FLAG_SHIT,
};

/* cmd response type */
enum
{
	EXTISP_BLOCK_RESPONSE_CMD = 1 << EXTISP_CMD_RESP_FLAG_SHIT,
	EXTISP_NORMAL_RESPONSE_CMD = 0 << EXTISP_CMD_RESP_FLAG_SHIT,
};

struct extented_block_response_buf {
	union {
    void 	*user_buf_ptr;
		 int64_t	_user_buf_ptr;
	};
    uint32_t user_buf_len;
};

typedef struct _tag_hwcam_config_data
{
    uint32_t cfgtype;
    uint32_t cmd;

    union {
        uint8_t  buf[64];
        uint16_t buf16[32];
    } u;
    struct extented_block_response_buf ext_buf;
}hwcam_config_data_t;


enum 
{
    HWEXTISP_NAME_SIZE                          =   32, 
}; 

typedef struct _tag_hwextisp_info
{
    char                                        name[HWEXTISP_NAME_SIZE]; 
} hwextisp_info_t; 


#define HWEXTISP_IOCTL_GET_INFO                 _IOR('S', BASE_VIDIOC_PRIVATE + 1, hwextisp_info_t)
#define HWCAM_V4L2_IOCTL_CONFIG               _IOW('A', BASE_VIDIOC_PRIVATE + 2, hwcam_config_data_t)

#endif // __HW_ALAN_KERNEL_HWCAM_EXTISP_CFG_H__

