#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include "synaptics.h"
#include <../../huawei_touchscreen_chips.h>
#include <linux/regulator/consumer.h>
#include <linux/hisi/hi6xxx-lcd_type.h>
//#include <hisi_udp_board_id.h>

#define SYNAPTICS_CHIP_INFO "synaptics-3207"
static struct ts_data* g_ts_data_synaptics= NULL;
unsigned int easywake_position[6]={0};
#ifdef  HUAWEI_EASY_WAKEUP
#define EASY_WAKEUP_FASTRATE 0x011D
#define F54_ANALOG_CMD0  0x016F

#define F51_LOCUS_DATA_NUM 24
#define F51_LOCUS_DATA_LENS 4
#define F51_LETTER_LOCUS_NUM 6
#define F51_LINEAR2_LOCUS_NUM 4
#define F51_LINEAR_LOCUS_NUM 2

//#define GESTURE_FROM_APP(_x) (_x)
//#define F51_CUSTOM_DATA24_OFFSET 24
#define F11_2D_DATA38_OFFSET 54
#define F11_2D_DATA39_OFFSET 55

/*Gesture register(F11_2D_data38) value*/
#define DOUBLE_CLICK_WAKEUP  (1<<0)
#define LINEAR_SLIDE_DETECTED  (1<<1)
#define CIRCLE_SLIDE_DETECTED  (1<<3)
#define SPECIFIC_LETTER_DETECTED  (1<<6)

/*Linear esture register(F51_custom_data0) value*/
#define LINEAR_SLIDE_LEFT_TO_RIGHT 0X01
#define LINEAR_SLIDE_RIGHT_TO_LEFT 0X02
#define LINEAR_SLIDE_TOP_TO_BOTTOM 0X04
#define LINEAR_SLIDE_BOTTOM_TO_TOP 0X08
#define LINEAR_SLIDE_TOP_TO_BOTTOM2 0X80

/*Letter gesture register(F11_2D_DATA39 (04)/01) value*/
#define SPECIFIC_LETTER_c 0x63
#define SPECIFIC_LETTER_e 0x65
#define SPECIFIC_LETTER_m 0x6D
#define SPECIFIC_LETTER_w 0x77

//#define RMI4_EASY_WAKE_UP_GESTURE_ENABLED 1
//#define RMI4_EASY_WAKE_UP_GESTURE_DISABLED 0
	

enum synaptics_gesture_num {
	GESTURE_DOUBLE_CLICK = 0,
	GESTURE_SLIDE_L2R,
	GESTURE_SLIDE_R2L,
	GESTURE_SLIDE_T2B,
	GESTURE_SLIDE_B2T,
	GESTURE_SLIDE_T2B2,
	GESTURE_CIRCLE_SLIDE,
	GESTURE_LETTER_c,
	GESTURE_LETTER_e,
	GESTURE_LETTER_m,
	GESTURE_LETTER_w,
	GESTURE_PALM,
	GESTURE_MAX,
};

static uint16_t  synaptics_gesture_key_event[GESTURE_MAX] = {
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
};
/*
static uint16_t synapitc_gesture_direction_dectected[GESTURE_MAX] ={
		0,
		1,
		2,
		3,
		4
};
*/
#define IS_APP_ENABLE_GESTURE(x)  ((u32)(1<<x))
//static struct device *core_dev_ptr = NULL;
static struct mutex  wrong_touch_lock;
static int off_motion_on=1;
#endif

#define GLOVE_SIGNAL
#ifdef  GLOVE_SIGNAL
#include <linux/time.h>
#include <linux/rtc.h>
#include <linux/ktime.h>
#define TP_FINGER 				1
#define TP_STYLUS				2
#define TP_GLOVE 				6
//#define GLOVE_REG_BIT 0x01

#define PEN_MOV_LENGTH      50   //move length (pixels)
#define FINGER_REL_TIME     300  //the time pen checked after finger released shouldn't less than this value(ms)
#define FILTER_GLOVE_NUMBER 4

enum TP_state_machine {
	INIT_STATE = 0,
	ZERO_STATE = 1,		//switch finger to glove
	FINGER_STATE = 2,	//finger state
	GLOVE_STATE = 3		//glove state
};
enum TP_state_machine  touch_state = INIT_STATE;

static struct timespec curr_time[FILTER_GLOVE_NUMBER] = {{0,0}};

static struct timespec pre_finger_time[FILTER_GLOVE_NUMBER] = {{0,0}};

static int touch_pos_x[FILTER_GLOVE_NUMBER] = {-1, -1, -1, -1};
static int touch_pos_y[FILTER_GLOVE_NUMBER] = {-1, -1, -1, -1};
#endif

static int synaptics_chip_detect (struct device_node *device, struct ts_device_data *chip_data, struct platform_device *ts_dev);
#ifdef HUAWEI_EASY_WAKEUP
static int synaptics_init_chip(struct  ts_data *g_ts_data);
static int synaptics_wrong_touch(void);
#else
static int synaptics_init_chip(void);
#endif
static int synaptics_parse_dts(struct device_node *device, struct ts_device_data *chip_data);
static int synaptics_irq_top_half(struct ts_cmd_node *cmd);
static int synaptics_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd);
static int synaptics_fw_update_boot(char *file_name);
static int synaptics_fw_update_sd(void);
static int synaptics_chip_get_info(struct ts_chip_info_param *info);
static int synaptics_before_suspend(void);
static int synaptics_suspend(void);
static int synaptics_resume(void);
static int synaptics_after_resume(void);
static void synaptics_shutdown(void);
static int synaptics_input_config(struct input_dev *input_dev);
static int synaptics_rmi4_reset_device(struct synaptics_rmi4_data *rmi4_data);
static void synaptics_rmi4_empty_fn_list(struct synaptics_rmi4_data *rmi4_data);
static void synaptics_rmi4_f1a_kfree(struct synaptics_rmi4_fn *fhandler);
static int synaptics_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd);
static int synaptics_glove_switch(struct ts_glove_info *info);
static int synaptics_get_glove_switch(u8 *glove_switch);
static int synaptics_set_glove_switch(u8 glove_switch);
static int synaptics_holster_switch(struct ts_holster_info *info);

#define REPORT_2D_W

#define RPT_TYPE (1 << 0)
#define RPT_X_LSB (1 << 1)
#define RPT_X_MSB (1 << 2)
#define RPT_Y_LSB (1 << 3)
#define RPT_Y_MSB (1 << 4)
#define RPT_Z (1 << 5)
#define RPT_WX (1 << 6)
#define RPT_WY (1 << 7)
#define RPT_DEFAULT (RPT_TYPE | RPT_X_LSB | RPT_X_MSB | RPT_Y_LSB | RPT_Y_MSB)

#define MAX_ABS_MT_TOUCH_MAJOR 15

#define F01_STD_QUERY_LEN 21
#define F01_BUID_ID_OFFSET 18
#define F11_STD_QUERY_LEN 9
#define F11_STD_CTRL_LEN 10
#define F11_STD_DATA_LEN 12
//dts
#define SYNAPTCS_IRQ_GPIO "attn_gpio"
//#define SYNAPTCS_RES_GPIO "res_gpio"
#define SYNAPTCS_RST_GPIO "reset_gpio"
#define SYNAPTICS_POWER_SUPPLY "power_gpio"
//#define SYNAPTCS_VDD_GPIO "vdd_gpio"
//#define SYNAPTCS_VIO_GPIO "vio_gpio"
#define SYNAPTCS_IRQ_CFG "irq_config"
#define SYNAPTICS_ALGO_ID "algo_id"
#define SYNAPTICS_VDD	 "synaptics-vdd"
#define SYNAPTICS_VBUS	 "synaptics-io"
//#define SYNAPTICS_IOMUX	 "block_tp"

/*set the synaptics vci ldo voltage 3.1V for JDI*/
#define SYNAPTICS_VCI_LDO_JDI_VALUE (3100000)

/*set the synaptics vci ldo voltage 2.8V for D2*/
//#define SYNAPTICS_VCI_LDO_D2_VALUE (2800000)

enum device_status {
	STATUS_NO_ERROR = 0x00,
	STATUS_RESET_OCCURRED = 0x01,
	STATUS_INVALID_CONFIG = 0x02,
	STATUS_DEVICE_FAILURE = 0x03,
	STATUS_CONFIG_CRC_FAILURE = 0x04,
	STATUS_FIRMWARE_CRC_FAILURE = 0x05,
	STATUS_CRC_IN_PROGRESS = 0x06
};

struct synaptics_rmi4_f54_query {
	union {
		struct {
			/* query 0 */
			unsigned char num_of_rx_electrodes;
			/* query 1 */
			unsigned char num_of_tx_electrodes;
			/* query 2 */
			unsigned char f54_query2_b0__1:2;
			unsigned char has_baseline:1;
			unsigned char has_image8:1;
			unsigned char f54_query2_b4__5:2;
			unsigned char has_image16:1;
			unsigned char f54_query2_b7:1;
			/* queries 3.0 and 3.1 */
			unsigned short clock_rate;
			/* query 4 */
			unsigned char touch_controller_family;
			/* query 5 */
			unsigned char has_pixel_touch_threshold_adjustment:1;
			unsigned char f54_query5_b1__7:7;
			/* query 6 */
			unsigned char has_sensor_assignment:1;
			unsigned char has_interference_metric:1;
			unsigned char has_sense_frequency_control:1;
			unsigned char has_firmware_noise_mitigation:1;
			unsigned char has_ctrl11:1;
			unsigned char has_two_byte_report_rate:1;
			unsigned char has_one_byte_report_rate:1;
			unsigned char has_relaxation_control:1;
		} __packed;
		unsigned char data[8];
	};
};

struct synaptics_rmi4_f1a_query {
	union {
		struct {
			unsigned char max_button_count:3;
			unsigned char reserved:5;
			unsigned char has_general_control:1;
			unsigned char has_interrupt_enable:1;
			unsigned char has_multibutton_select:1;
			unsigned char has_tx_rx_map:1;
			unsigned char has_perbutton_threshold:1;
			unsigned char has_release_threshold:1;
			unsigned char has_strongestbtn_hysteresis:1;
			unsigned char has_filter_strength:1;
		} __packed;
		unsigned char data[2];
	};
};

struct synaptics_rmi4_f1a_control_0 {
	union {
		struct {
			unsigned char multibutton_report:2;
			unsigned char filter_mode:2;
			unsigned char reserved:4;
		} __packed;
		unsigned char data[1];
	};
};

struct synaptics_rmi4_f1a_control {
	struct synaptics_rmi4_f1a_control_0 general_control;
	unsigned char *button_int_enable;
	unsigned char *multi_button;
	struct synaptics_rmi4_f1a_control_3_4 *electrode_map;
	unsigned char *button_threshold;
	unsigned char button_release_threshold;
	unsigned char strongest_button_hysteresis;
	unsigned char filter_strength;
};

struct synaptics_rmi4_f1a_handle {
	int button_bitmask_size;
	unsigned char button_count;
	unsigned char valid_button_count;
	unsigned char *button_data_buffer;
	unsigned char *button_map;
	struct synaptics_rmi4_f1a_query button_query;
	struct synaptics_rmi4_f1a_control button_control;
};
static struct synaptics_rmi4_data *rmi4_data;
/* when add/remove support TP module need to modify here */
static struct touch_settings synaptics_sett_param_regs_map[] = {
	[0]={
			.build_id[0] = '0',
			.build_id[1] = '0',
			.build_id[2] = '0',
			.module_name = "oflim",
		},
	[1]={
			.build_id[0] = '0',
			.build_id[1] = '0',
			.build_id[2] = '2',
			//.id = TRULY,
			.module_name = "truly",
		},
	[2]={
			.build_id[0] = '0',
			.build_id[1] = '0',
			.build_id[2] = '4',
			//.id = TRULY,
			.module_name = "GIS",
		},
	[3]={
			.build_id[0] = '0',
			.build_id[1] = '0',
			.build_id[2] = '7',
			//.id = TRULY,
			.module_name = "YASSY",
		},
	[4]={
			.build_id[0] = '0',
			.build_id[1] = '0',
			.build_id[2] = '6',
			.module_name = "lensone",
	},
	[5]={
			.build_id[0] = '1',
			.build_id[1] = '1',
			.build_id[2] = '1',
			//.id = 0xff,
			.module_name = "null",
		},
};
static struct touch_settings *synaptics_sett_param_regs = &synaptics_sett_param_regs_map[4];

static void synaptics_gpio_reset(void);
static void synaptics_power_on(void);
//static void synatpics_regulator_enable(void);
static void synaptics_power_on_gpio_set(void);
static void synaptics_power_off(void);
//static void synatpics_regulator_disable(void);
static void synaptics_power_off_gpio_set(void);
static bool synaptics_rmi4_crc_in_progress(struct synaptics_rmi4_data *rmi4_data,
			struct synaptics_rmi4_f01_device_status *status);
static int synaptics_rmi4_set_page(struct synaptics_rmi4_data *rmi4_data,
		unsigned int address);
static struct synaptics_rmi4_fn * synaptics_rmi4_alloc_fh(
		struct synaptics_rmi4_fn_desc *rmi_fd, int page_number);
static int synaptics_rmi4_query_device_info(
					struct synaptics_rmi4_data *rmi4_data);
static int synaptics_rmi4_query_device(struct synaptics_rmi4_data *rmi4_data);
static int synaptics_rmi4_f11_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count);
static int synaptics_rmi4_f12_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count);
static int synaptics_rmi4_f1a_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count);
static int synaptics_rmi4_i2c_read(struct synaptics_rmi4_data *rmi4_data,
		unsigned short addr, unsigned char *data, unsigned short length);
static int synaptics_rmi4_i2c_write(struct synaptics_rmi4_data *rmi4_data,
		unsigned short addr, unsigned char *data, unsigned short length);
static int synaptics_rmi4_sensor_report(struct synaptics_rmi4_data *rmi4_data, struct ts_fingers *info);

/*******************************************************************************
** TP VCC
* TP VCC/VDD  power control by GPIO in V8Rx, 
* if controled by ldo in other products, open "return -EINVAL"
*/
static int synaptics_regulator_get(void)
{
	rmi4_data->tp_vci = regulator_get(&rmi4_data->synaptics_dev->dev, SYNAPTICS_VDD);
	if (IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_ERR("regulator tp vci not used\n");
//		return  -EINVAL;
	}

	rmi4_data->tp_vddio = regulator_get(&rmi4_data->synaptics_dev->dev, SYNAPTICS_VBUS);
	if (IS_ERR(rmi4_data->tp_vddio)) {
		TS_LOG_ERR("regulator tp vddio not used\n");
//		regulator_put(rmi4_data->tp_vci);
//		return -EINVAL;
	}

	return 0;
}

static void synaptics_regulator_put(void)
{
	if (!IS_ERR(rmi4_data->tp_vci)) {
		regulator_put(rmi4_data->tp_vci);
	}
	if (!IS_ERR(rmi4_data->tp_vddio)) {
		regulator_put(rmi4_data->tp_vddio);
	}
}

static int synaptics_vci_enable(void)
{
	int retval;
	int vol_vlaue;

	if (IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_ERR("tp_vci is err\n");
		return  -EINVAL;
	}
/*
	lcd_type = read_lcd_type();

	switch (lcd_type) {
	case TOSHIBA_MDY90_LCD:
		vol_vlaue = SYNAPTICS_VCI_LDO_D2_VALUE;
		TS_LOG_INFO("TOSHIBA_MDY90_LCD");
		break;
	case JDI_NT35695_LCD:
		vol_vlaue = SYNAPTICS_VCI_LDO_JDI_VALUE;
		TS_LOG_INFO("JDI_NT35695_LCD");
		break;
	case JDI_OTM1902B_LCD:
		vol_vlaue = SYNAPTICS_VCI_LDO_JDI_VALUE;
		TS_LOG_INFO("JDI_OTM1902B_LCD");
		break;
	default:
		TS_LOG_ERR("the board is no lcd\n");
		return -EINVAL;
	}
*/
	vol_vlaue = SYNAPTICS_VCI_LDO_JDI_VALUE;
       if (!IS_ERR(rmi4_data->tp_vci)) {
		retval = regulator_set_voltage(rmi4_data->tp_vci, vol_vlaue, vol_vlaue);
		if (retval < 0) {
			TS_LOG_ERR("failed to set voltage regulator tp_vci error: %d\n", retval);
			return -EINVAL;
		}

		retval = regulator_enable(rmi4_data->tp_vci);
		if (retval < 0) {
			TS_LOG_ERR("failed to enable regulator tp_vci\n");
			return -EINVAL;
		}
       }
	return 0;
}

static int synaptics_vci_disable(void)
{
	int retval;

	if (IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_ERR("tp_vci is err\n");
		return  -EINVAL;
	}
	retval = regulator_disable(rmi4_data->tp_vci);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vci\n");
		return -EINVAL;
	}

	return 0;
}

static int synaptics_vddio_enable(void)
{
	int retval;

	if (IS_ERR(rmi4_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}
	retval = regulator_enable(rmi4_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to enable regulator tp_vddio\n");
		return -EINVAL;
	}

	return 0;
}

static int synaptics_vddio_disable(void)
{
	int retval;

	if (IS_ERR(rmi4_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}

	retval = regulator_disable(rmi4_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vddio\n");
		return -EINVAL;
	}

	return 0;
}

static void synatpics_regulator_enable(void)
{
   if (!IS_ERR(rmi4_data->tp_vci)) {
	   synaptics_vci_enable();
   }
	
	mdelay(5);
	
	if (!IS_ERR(rmi4_data->tp_vddio)) {
		synaptics_vddio_enable();
	}
}

static void synatpics_regulator_disable(void)
{
    if (!IS_ERR(rmi4_data->tp_vddio) ) {
       synaptics_vddio_disable(); 
    }
	
	mdelay(2);	
	
	if (!IS_ERR(rmi4_data->tp_vci) ) {
		synaptics_vci_disable();
	}
}

/* dts */
static int synaptics_pinctrl_get_init(void)
{
	int ret = 0;

	rmi4_data->pctrl = devm_pinctrl_get(&rmi4_data->synaptics_dev->dev);
	if (IS_ERR(rmi4_data->pctrl)) {
		TS_LOG_ERR("failed to devm pinctrl get\n");
		ret = -EINVAL;
		return ret;
	}

	rmi4_data->pins_default = pinctrl_lookup_state(rmi4_data->pctrl, "default");
	if (IS_ERR(rmi4_data->pins_default)) {
		TS_LOG_ERR("failed to pinctrl lookup state default\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}

	rmi4_data->pins_idle = pinctrl_lookup_state(rmi4_data->pctrl, "idle");
	if (IS_ERR(rmi4_data->pins_idle)) {
		TS_LOG_ERR("failed to pinctrl lookup state idle\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}
	return 0;

err_pinctrl_put:
	devm_pinctrl_put(rmi4_data->pctrl);
	return ret;
}

static int synaptics_pinctrl_select_normal(void)
{
	int retval = NO_ERR;
	retval = pinctrl_select_state(rmi4_data->pctrl, rmi4_data->pins_default);
	if (retval < 0) {
		TS_LOG_ERR("set iomux normal error, %d\n", retval);
	}
	return retval;
}

static int synaptics_pinctrl_select_lowpower(void)
{
	int retval = NO_ERR;
	retval = pinctrl_select_state(rmi4_data->pctrl, rmi4_data->pins_idle);
	if (retval < 0) {
		TS_LOG_ERR("set iomux lowpower error, %d\n", retval);
	}
	return retval;
}

#ifdef  GLOVE_SIGNAL
/*initialize variable*/
static void rmi_f11_filter_glove_init(void)
{
	int i;
	touch_state = INIT_STATE;
	for (i = 0; i < FILTER_GLOVE_NUMBER; i++) {
		pre_finger_time[i].tv_sec = 0;
		pre_finger_time[i].tv_nsec = 0;
		touch_pos_x[i] = -1;
		touch_pos_y[i] = -1;
	}
}

/*
  * Description: filger the illegal signal while touching with finger.
  * Return Value: 1 means this signal is legal; 0 means this signal is illegal and should be ignored.
  * Parameters: @n_finger  the index of this signal.
  *             @x         the X axis of this signal.
  *             @y         the Y axis of this signal.
  */
static int rmi_f11_filter_illegal_glove(u8 n_finger, struct ts_fingers *in_info)
{
	u8 report_flag = 0;
	long interval_time;
	u8 new_mode;
	int x = in_info->fingers[n_finger].x;
	int y = in_info->fingers[n_finger].y;
	new_mode = in_info->fingers[n_finger].status;

	if (new_mode == TP_FINGER) { /*the new interrupt is a finger signal*/
		touch_state = FINGER_STATE;
		report_flag = 1;
	} else if ((new_mode == TP_GLOVE) || (new_mode == TP_STYLUS)) { /*the new interrupt is a glove signal.*/
		switch (touch_state) {
			case INIT_STATE:
				report_flag = 1;
				touch_state = GLOVE_STATE;
				break;

			case FINGER_STATE:
				ktime_get_ts(&curr_time[n_finger]);
				interval_time = (curr_time[n_finger].tv_sec - pre_finger_time[n_finger].tv_sec)*1000
					+ (curr_time[n_finger].tv_nsec - pre_finger_time[n_finger].tv_nsec)/1000000;
				if (interval_time > 0 && interval_time <= FINGER_REL_TIME) {
					ktime_get_ts(&pre_finger_time[n_finger]);
				} else {
					touch_state = ZERO_STATE;
				}
				break;

			case ZERO_STATE:
				if ((touch_pos_x[n_finger] == -1) && (touch_pos_y[n_finger] == -1)) {
					touch_pos_x[n_finger] = x;
					touch_pos_y[n_finger] = y;
				} else {
					if (((touch_pos_x[n_finger] - x)*(touch_pos_x[n_finger] - x)
						+ (touch_pos_y[n_finger] - y)*(touch_pos_y[n_finger] - y))
						>= (PEN_MOV_LENGTH * PEN_MOV_LENGTH)) {
						touch_state = GLOVE_STATE;
					}
				}
				break;

			case GLOVE_STATE:
				report_flag = 1;
				break;

			default:
				TS_LOG_ERR("error: touch_state = %d\n", touch_state);
				break;
		}
	}else {
		TS_LOG_ERR("error:cur_mode=%d\n", new_mode);
		report_flag = 1;
	}

	return report_flag;
}

static int rmi_f11_read_finger_state(struct ts_fingers *info)
{
	int i;
	int retval = 0;
	u8 finger_state = 0;
	u16 f51_custom_CTRL03 = 0x0015;
  
	retval = synaptics_rmi4_i2c_read(rmi4_data, f51_custom_CTRL03,
						(u8 *)&finger_state, sizeof(finger_state));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f51_custom_CTRL03, code: %d.\n", retval);
		return retval;
	}

	for (i = 0; i < FILTER_GLOVE_NUMBER; i++) {
		info->fingers[i].status = (finger_state >> (2 * i)) & MASK_2BIT;
		if (info->fingers[i].status == 2) {
			info->fingers[i].status = TP_GLOVE;
		}
	}
	return 0;
}
#endif

static int synaptics_algo_t2(struct ts_device_data *dev_data, struct ts_fingers *in_info, struct ts_fingers *out_info)
{
	int index;
	int id = 0;

	for(index = 0, id = 0; index < TS_MAX_FINGER; index++, id++) {
		if (in_info->cur_finger_number == 0) {
			out_info->fingers[0].status = TS_FINGER_RELEASE;
			if (id >= 1)
				out_info->fingers[id].status = 0;	
		} else {
			if ((in_info->fingers[index].x != 0) ||(in_info->fingers[index].y != 0)) {
				out_info->fingers[id].x = in_info->fingers[index].x;
				out_info->fingers[id].y = in_info->fingers[index].y;
				out_info->fingers[id].pressure = in_info->fingers[index].pressure;
				out_info->fingers[id].status = TS_FINGER_PRESS;
			} else
				out_info->fingers[id].status = 0;
		}
	}

	return NO_ERR;
}

static int synaptics_algo_t1(struct ts_device_data *dev_data, struct ts_fingers *in_info, struct ts_fingers *out_info)
{
	int index;
	int id;
	for(index = 0, id = 0; index < TS_MAX_FINGER; index++, id++) {
		if (in_info->cur_finger_number == 0) {
			if (index < FILTER_GLOVE_NUMBER) {
				touch_pos_x[index] = -1;
				touch_pos_y[index] = -1;
				if (touch_state == FINGER_STATE) {/*this is a finger release*/
				 	ktime_get_ts(&pre_finger_time[index]);
				}
			}
			out_info->fingers[0].status = TS_FINGER_RELEASE;
			if (id >= 1)
				out_info->fingers[id].status = 0;	
		} else {
			if ((in_info->fingers[index].x != 0) ||(in_info->fingers[index].y != 0)) {
				if (index < FILTER_GLOVE_NUMBER) {
					if (rmi_f11_filter_illegal_glove(index, in_info) == 0) {
						out_info->fingers[id].status = 0;
					} else {
						out_info->fingers[id].x = in_info->fingers[index].x;
						out_info->fingers[id].y = in_info->fingers[index].y;
						out_info->fingers[id].pressure = in_info->fingers[index].pressure;
						out_info->fingers[id].status = TS_FINGER_PRESS;
					}
				} else {
					out_info->fingers[id].x = in_info->fingers[index].x;
					out_info->fingers[id].y = in_info->fingers[index].y;
					out_info->fingers[id].pressure = in_info->fingers[index].pressure;
					out_info->fingers[id].status = TS_FINGER_PRESS;
				}
			} else
				out_info->fingers[id].status = 0;
		}
	}

	return NO_ERR;
}

static struct ts_algo_func synaptics_algo_f1=
{
	.algo_name = "synaptics_algo_f1",
	.chip_algo_func = synaptics_algo_t1,
};

static struct ts_algo_func synaptics_algo_f2 =
{
	.algo_name = "synaptics_algo_f2",
	.chip_algo_func = synaptics_algo_t2,
};

static int synaptics_register_algo(struct ts_device_data *chip_data)
{
	int retval = 0;
	retval = register_algo_func(chip_data, &synaptics_algo_f1);	//put algo_f1 into list contained in chip_data, named algo_t1
	if (retval < 0) {
		TS_LOG_ERR("alog 1 failed, retval = %d\n", retval);
		return retval;
	}

	retval = register_algo_func(chip_data, &synaptics_algo_f2);	//put algo_f2 into list contained in chip_data, named algo_t2
	if (retval < 0) {
		TS_LOG_ERR("alog 2 failed, retval = %d\n", retval);
		return retval;
	}


	return retval;
}

struct ts_device_ops ts_synaptics_ops = {
	.chip_detect = synaptics_chip_detect,
	.chip_init = synaptics_init_chip,
	.chip_parse_config = synaptics_parse_dts,
	.chip_register_algo = synaptics_register_algo, //synaptics_register_alog,
	.chip_input_config = synaptics_input_config,
	.chip_irq_top_half = synaptics_irq_top_half,
	.chip_irq_bottom_half = synaptics_irq_bottom_half,
	.chip_fw_update_boot = synaptics_fw_update_boot,
	.chip_fw_update_sd = synaptics_fw_update_sd,
	.chip_get_info = synaptics_chip_get_info,
	.chip_before_suspend = synaptics_before_suspend,
	.chip_suspend = synaptics_suspend,
	.chip_resume = synaptics_resume,
	.chip_after_resume = synaptics_after_resume,
	.chip_get_rawdata = synaptics_get_rawdata,
	.chip_glove_switch = synaptics_glove_switch,
	.chip_shutdown = synaptics_shutdown,
	.chip_holster_switch = synaptics_holster_switch,
	//.chip_reset = synaptics_rmi4_reset_device,
#ifdef HUAWEI_TOUCHSCREEN_TEST 
	.chip_test = test_dbg_cmd_test,
#endif
#ifdef HUAWEI_EASY_WAKEUP
	.chip_wrong_touch=synaptics_wrong_touch,
#endif
};

static int synaptics_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd)
{
#if 0
	int retval = 0;

	retval = synaptics_rmi4_f54_init(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to init f54\n");
		return retval;
	}

	retval = synaptics_get_cap_data(info);
	if (retval < 0) {
		TS_LOG_ERR("Failed to get rawdata\n");
		return retval;
	}
#endif
	return NO_ERR;
}

static int synaptics_chip_get_info(struct ts_chip_info_param *info)
{
	int retval = 0;
	u8 buf[CHIP_INFO_LENGTH];
	memset(buf, 0, sizeof(buf));
	TS_LOG_INFO("synaptics_chip_get_info called\n");

	retval = synaptics_fw_configid(rmi4_data, buf, sizeof(buf));
	if (retval < 0)
		TS_LOG_ERR("failed to get configid\n");

	memcpy(&info->ic_vendor,SYNAPTICS_CHIP_INFO, strlen(SYNAPTICS_CHIP_INFO));
	memcpy(info->mod_vendor, synaptics_sett_param_regs->module_name, strlen(synaptics_sett_param_regs->module_name));
	memcpy(&info->fw_vendor, buf, strlen(buf));
	return NO_ERR;
}

/*  query the configure from dts and store in prv_data */
static int synaptics_parse_dts(struct device_node *device,struct ts_device_data *chip_data)
{
	int retval  = NO_ERR;

	chip_data->irq_gpio = of_get_named_gpio(device, SYNAPTCS_IRQ_GPIO, 0);
	if (!gpio_is_valid(chip_data->irq_gpio)) {
		TS_LOG_ERR("irq gpio is not valid\n");
		retval = -EINVAL;
		goto err;
	}
	chip_data->reset_gpio = of_get_named_gpio(device, SYNAPTCS_RST_GPIO, 0);
	if (!gpio_is_valid(chip_data->reset_gpio)) {
		TS_LOG_ERR("reset gpio is not valid\n");
		retval = -EINVAL;
		goto err;
	}
	retval = of_property_read_u32(device, SYNAPTCS_IRQ_CFG, &chip_data->irq_config);
	if (retval) {
		TS_LOG_ERR("get irq config failed\n");
		retval = -EINVAL;
		goto err;
	}
	retval = of_property_read_u32(device, SYNAPTICS_ALGO_ID, &chip_data->algo_id);
	if (retval) {
		TS_LOG_ERR("get algo id failed\n");
		retval = -EINVAL;
		goto err;
	}
	chip_data->power_supply = of_get_named_gpio(device, SYNAPTICS_POWER_SUPPLY, 0);
	if (!gpio_is_valid(chip_data->power_supply)) {
		TS_LOG_ERR("SFT: ok; ASIC: Real err----power gpio is not valid\n");
	}

	TS_LOG_DEBUG("reset_gpio = %d, irq_gpio = %d, irq_config = %d, algo_id = %d\n", \
		chip_data->reset_gpio, chip_data->irq_gpio, chip_data->irq_config, chip_data->algo_id);
err:
	return retval;
}

static void synaptics_power_on_gpio_set(void)
{
	synaptics_pinctrl_select_normal();
	gpio_direction_input(rmi4_data->synaptics_chip_data->irq_gpio);
	//gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 1);
	if(rmi4_data->synaptics_chip_data->power_supply){
		gpio_direction_output(rmi4_data->synaptics_chip_data->power_supply, 1);
	}
	msleep(1);
}

static void synaptics_power_on(void)
{
	TS_LOG_DEBUG("synaptics_power_on called\n");
	synatpics_regulator_enable();
	synaptics_power_on_gpio_set();
}

static void synaptics_power_off_gpio_set(void)
{
	int power_gpio = rmi4_data->synaptics_chip_data->power_supply;
	synaptics_pinctrl_select_lowpower();
	gpio_direction_input(rmi4_data->synaptics_chip_data->reset_gpio);
	if(rmi4_data->synaptics_chip_data->power_supply){
		gpio_direction_output(power_gpio, 0);
	}
}

static void synaptics_power_off(void)
{
	synaptics_power_off_gpio_set();
	synatpics_regulator_disable();
}

static void synaptics_gpio_reset(void)
{
	TS_LOG_DEBUG("synaptics_gpio_reset\n");
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 1);
	msleep(20);
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 0);
	msleep(20);
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 1);
	msleep(250);
}

static int synaptics_gpio_request(void)
{
	int retval = NO_ERR;
	TS_LOG_INFO("synaptics_gpio_request\n");

	retval = gpio_request(rmi4_data->synaptics_chip_data->reset_gpio, "ts_reset_gpio");
	if (retval < 0) {
		TS_LOG_ERR("Fail request gpio:%d\n", rmi4_data->synaptics_chip_data->reset_gpio);
		goto ts_reset_out;
	}
	retval = gpio_request(rmi4_data->synaptics_chip_data->irq_gpio, "ts_irq_gpio");
	if (retval) {
		TS_LOG_ERR("unable to request gpio:%d\n", rmi4_data->synaptics_chip_data->irq_gpio);
		goto ts_irq_out;
	}
	retval = gpio_request(rmi4_data->synaptics_chip_data->power_supply, "ts_power_gpio");
	if (retval) {
		TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request gpio:%d\n", rmi4_data->synaptics_chip_data->power_supply);
		retval = 0;
	}
	TS_LOG_DEBUG("reset:%d, irq:%d\n", \
		rmi4_data->synaptics_chip_data->reset_gpio,\
		rmi4_data->synaptics_chip_data->irq_gpio);

	goto ts_reset_out;
ts_irq_out:
	gpio_free(rmi4_data->synaptics_chip_data->reset_gpio);
ts_reset_out:
	return retval;
}

static void synaptics_gpio_free(void)
{
	TS_LOG_INFO("synaptics_gpio_free\n");

	gpio_free(rmi4_data->synaptics_chip_data->irq_gpio);
	gpio_free(rmi4_data->synaptics_chip_data->reset_gpio);
	if(rmi4_data->synaptics_chip_data->power_supply){
		gpio_free(rmi4_data->synaptics_chip_data->power_supply);
	}
}

static int i2c_communicate_check(void)
{
	int retval = NO_ERR;
	int i;
	u8 pdt_entry_addr = PDT_START;
	struct synaptics_rmi4_fn_desc rmi_fd = {0};

	for (i = 0; i < I2C_RW_TRIES; i++) {
		retval = synaptics_rmi4_i2c_read(rmi4_data, pdt_entry_addr,
						(unsigned char *)&rmi_fd,
						sizeof(rmi_fd));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read register map, i = %d, retval = %d\n", i, retval);
			msleep(50);
		} else {
			TS_LOG_INFO("i2c communicate check success\n");
			retval = NO_ERR;
			return retval;
		}
	}

	return retval;
}

static int synaptics_chip_detect (struct device_node *device, 
		struct ts_device_data *chip_data, struct platform_device *ts_dev)
{
	int retval = NO_ERR;

	TS_LOG_INFO("synaptics chip detect called\n");

	if (!device || !chip_data || !ts_dev) {
		TS_LOG_ERR("device, chip_data or ts_dev is NULL \n");
		return -ENOMEM;
	}

	rmi4_data = kzalloc(sizeof(*rmi4_data) * 2, GFP_KERNEL);
	if (!rmi4_data) {
		TS_LOG_ERR("Failed to alloc mem for struct rmi4_data\n");
		return -ENOMEM;
	}
/*
	lcd_type = read_lcd_type();
	switch (lcd_type) {
	case TOSHIBA_MDY90_LCD:
		rmi4_data->flip_x = false;
		break;
	case JDI_NT35695_LCD:
	case JDI_OTM1902B_LCD:
		rmi4_data->flip_x = true;
		break;
	default:
		TS_LOG_ERR("the board is no lcd\n");
		retval = -EINVAL;
		goto get_udp_board_err;
	}
*/

      if (get_lcd_type() == JDI_1902B_LCD) {
          rmi4_data->flip_x = true;
	   rmi4_data->flip_y = true;
      	} else {
          rmi4_data->flip_x = false;
	   rmi4_data->flip_y = false;
	}
	

	rmi4_data->current_page = MASK_8BIT;
	rmi4_data->synaptics_chip_data = chip_data;
	rmi4_data->synaptics_dev = ts_dev;
	rmi4_data->synaptics_dev->dev.of_node = device;
	rmi4_data->reset_delay_ms = 100;
#ifdef RED_REMOTE
	rmi4_data->fw_debug = false;
	rmi4_data->i2c_client = chip_data->client;
#endif
	rmi4_data->i2c_read = synaptics_rmi4_i2c_read;
	rmi4_data->i2c_write = synaptics_rmi4_i2c_write;
	rmi4_data->reset_device = synaptics_rmi4_reset_device;

	rmi4_data->synaptics_chip_data->is_in_cell = true;

	rmi4_data->force_update = false;
	rmi4_data->sensor_max_x = X_RES - 1;
	rmi4_data->sensor_max_y = Y_RES - 1;
	
	retval = synaptics_regulator_get();
/*	if (retval < 0) {
		goto regulator_err;
	}
*/
	retval = synaptics_gpio_request();
	if (retval < 0) {
		goto gpio_err;
	}

	retval = synaptics_pinctrl_get_init();
	if (retval < 0) {
		goto pinctrl_get_err;
	}

	/*power up the chip*/
	synaptics_power_on();

	/*reset the chip*/
	synaptics_gpio_reset();
	/*after 100ms, allowed i2c operation*/
	//msleep(100);
	retval = i2c_communicate_check();
	if (retval < 0) {
		TS_LOG_ERR("not find synaptics device\n");
		goto check_err;
	} else {
		TS_LOG_INFO("find synaptics device\n");
		goto out;
	}

out:
	TS_LOG_INFO("synaptics chip detect done\n");
	return NO_ERR;

check_err:
	synaptics_power_off();
pinctrl_get_err:
	synaptics_gpio_free();
gpio_err:
	synaptics_regulator_put();
//get_udp_board_err:
//regulator_err:
	if (rmi4_data)
		kfree(rmi4_data);
	rmi4_data = NULL;
	TS_LOG_ERR("no power\n");
	return retval;
}

/*    init the chip.
* 
*     (1) power up;  (2) detect the chip thourgh bus(i2c).
*/
#ifdef HUAWEI_EASY_WAKEUP
static int synaptics_init_chip(struct  ts_data *g_ts_data )
{
	int rc = NO_ERR;
	unsigned char device_fastrate;
	struct ts_easy_wakeup_info *info;
	g_ts_data_synaptics= g_ts_data;
	
	mutex_init(&wrong_touch_lock);	
	info = &(g_ts_data_synaptics->easy_wakeup_info);
	info->easy_wakeup_gesture = 0x00;
	info->easy_wakeup_flag = 0x00;
	info->palm_cover_flag = 0x00;
	info->palm_cover_control = true;
	
	/*detect the chip*/
	rc = synaptics_rmi4_query_device(rmi4_data);
	if (rc < 0 ) {
		TS_LOG_ERR("Failed to synaptics_rmi4_query_device\n");
	}
	
	rc = synaptics_rmi4_i2c_read(rmi4_data,
			EASY_WAKEUP_FASTRATE,
			&device_fastrate,
			sizeof(device_fastrate));
	rmi4_data->easy_wakeup_fastrate = device_fastrate;
	if (rc < 0) {
		TS_LOG_ERR("Failed to get FASTRATE info\n");
		return rc;
	}
	return rc;
}
static int synaptics_wrong_touch(void)
{
	int rc=NO_ERR;
	mutex_lock(&wrong_touch_lock);
	off_motion_on=1;
	mutex_unlock(&wrong_touch_lock);
	TS_LOG_INFO("done\n");
	return rc;
}
#else
static int synaptics_init_chip(void)
{
	int retval = NO_ERR;

	/*detect the chip*/
	retval = synaptics_rmi4_query_device(rmi4_data);
	if (retval < 0 ) {
		TS_LOG_ERR("synaptics_rmi4_query_device failed: %d\n", retval);
	}

	return retval;
}
#endif
/*
static int synaptics_get_glove_enable_addr(struct synaptics_rmi4_data *rmi4_data, unsigned char *glove_enable_address)
{
	int retval = NO_ERR;
	unsigned short addr = 0;
	struct synaptics_rmi4_fn_desc rmi_fd;
	memset(&rmi_fd, 0, sizeof(struct synaptics_rmi4_fn_desc));

	for (addr = PDT_START; addr > PDT_END; addr -= PDT_ENTRY_SIZE)
	{
		retval = synaptics_rmi4_i2c_read(rmi4_data, addr, (unsigned char *)&rmi_fd, sizeof(rmi_fd));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read map register\n");
			return retval;
		}

		if (SYNAPTICS_RMI4_F12 == rmi_fd.fn_number) {
			*glove_enable_address = rmi_fd.ctrl_base_addr + 8;
			TS_LOG_INFO("Found F%02x, glove enable addr = 0x%x\n", rmi_fd.fn_number, *glove_enable_address);
			return NO_ERR;
		}
	}

	TS_LOG_ERR("Failed to get glove_enable_address\n");
	return -EINVAL;
}
*/
static int synaptics_fw_update_boot(char *file_name)
{
	int retval = NO_ERR;
	bool need_update = false;

#ifdef RED_REMOTE
	/*used for red remote fucntion*/
	synaptics_fw_debug_dev_init(rmi4_data);
#endif

	TS_LOG_INFO("synaptics_fw_update_boot called\n");
/*
	lcd_type = read_lcd_type();

	switch (lcd_type) {
	case TOSHIBA_MDY90_LCD:
		TS_LOG_INFO("D2 TYPE LCD, no need to fw update\n");
		return NO_ERR;
	case JDI_OTM1902B_LCD:
	case JDI_NT35695_LCD:
		retval = synaptics_fw_data_init(rmi4_data);
		if (retval) {
			TS_LOG_ERR("synaptics_fw_data_init failed\n");
			goto data_release;
		}
		msleep(1000);
		retval = synaptics_get_fw_data_boot(file_name);
		if (retval) {
			TS_LOG_ERR("load fw data from bootimage error\n");
			goto data_release;
		}
		break;
	default:
		TS_LOG_ERR("the board is no lcd\n");
		return NO_ERR;
	}
*/
	retval = synaptics_fw_data_init(rmi4_data);
	if (retval) {
		TS_LOG_ERR("synaptics_fw_data_init failed\n");
		goto data_release;
	}
	msleep(1000);
	retval = synaptics_get_fw_data_boot(file_name,synaptics_sett_param_regs);
	if (retval) {
		TS_LOG_ERR("load fw data from bootimage error\n");
		goto data_release;
	}	
	need_update = synaptics_check_fw_version();

	if (rmi4_data->force_update || need_update) {
		retval = synaptics_fw_update();
		if (retval) {
			TS_LOG_ERR("failed update fw\n");
		} else {
			TS_LOG_INFO("successfully update fw\n");
		}
	}

data_release:
	synaptics_fw_data_release();
	retval =synaptics_rmi4_f54_init(rmi4_data,synaptics_sett_param_regs->module_name); // for test report function 
	if(retval){
		TS_LOG_ERR("synaptics_rmi4_f54_init failed\n");
	}
	return retval;
}

static int synaptics_fw_update_sd(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("synaptics_fw_update_sd called\n");

	retval = synaptics_fw_data_init(rmi4_data);
	if (retval) {
		TS_LOG_ERR("synaptics_fw_data_init failed\n");
		goto data_release;
	}
	msleep(1000);
	retval = synaptics_get_fw_data_sd();
	if (retval) {
		TS_LOG_ERR("load fw data from bootimage error\n");
		goto data_release;
	}

	/*just check the fw version*/
	synaptics_check_fw_version();

	retval = synaptics_fw_update();
	if (retval < 0) {
		TS_LOG_ERR("failed update fw\n");
	} else {
		TS_LOG_INFO("success update fw\n");
	}

data_release:
	synaptics_fw_data_release();
	return retval;
}

static int synaptics_get_holster_addr(struct synaptics_rmi4_data *rmi4_data, unsigned short *holster_enable_addr)
{
	int retval = NO_ERR;
	unsigned char page_number = 4;
	unsigned short addr = 0;
	unsigned short holster_addr = 0;

	struct synaptics_rmi4_fn_desc rmi_fd;
	memset(&rmi_fd, 0, sizeof(struct synaptics_rmi4_fn_desc));

	for (addr = PDT_START; addr > PDT_END; addr -= PDT_ENTRY_SIZE)
	{
		addr |= (page_number << 8);
		retval = synaptics_rmi4_i2c_read(rmi4_data, addr, (unsigned char *)&rmi_fd, sizeof(rmi_fd));
		if (retval < 0) {
			TS_LOG_ERR("Failed to read map register\n");
			return retval;
		}

		if (SYNAPTICS_RMI4_F51 == rmi_fd.fn_number) {
			holster_addr = rmi_fd.ctrl_base_addr |(page_number << 8);
			*holster_enable_addr = holster_addr  + 10;
			TS_LOG_INFO("Found F%02x, glove enable addr = 0x%04x\n", rmi_fd.fn_number, *holster_enable_addr);
			return NO_ERR;
		}
	}

	TS_LOG_ERR("Failed to get glove_enable_address\n");
	return -EINVAL;
}

static int synaptics_set_holster_switch(u8 holster_switch)
{
	int retval = NO_ERR;
	unsigned short holster_enable_addr = 0;

	TS_LOG_INFO("synaptics_set_holster_switch called\n");

	retval = synaptics_get_holster_addr(rmi4_data, &holster_enable_addr);
	if (retval < 0) {
		TS_LOG_ERR("get holster addr err: %d\n", retval);
		goto out;
	}

	retval = synaptics_rmi4_i2c_write(rmi4_data, holster_enable_addr, &holster_switch, 1);
	if (retval < 0) {
		TS_LOG_ERR("open holster function failed: %d\n", retval);
	}
out:
	return retval;
}

static int synaptics_holster_switch(struct ts_holster_info *info)
{
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("synaptics_holster_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
		case TS_ACTION_WRITE:
			retval = synaptics_set_holster_switch(info->holster_switch);
			if (retval < 0) {
				TS_LOG_ERR("set holster switch(%d), failed: %d", info->holster_switch, retval);
			}
			break;
		default:
			TS_LOG_ERR("invalid holster switch status: %d", info->holster_switch);
			retval = -EINVAL;
			break;
	}

	return retval;
}
static int synaptics_get_glove_switch(u8 *glove_switch)
{
	int retval = NO_ERR;
	u8 value = 0;
	if (!glove_switch) {
		TS_LOG_ERR("synaptics_get_glove_switch: glove_switch is Null\n");
		return -ENOMEM;
	}
/*
	retval = synaptics_get_glove_enable_addr(rmi4_data, &glove_enable_addr);
	if (retval < 0) {
		TS_LOG_ERR("get glove addr failed (0x%x), err: %d\n", glove_enable_addr, retval);
		goto out;
	}
*/
	retval = synaptics_rmi4_i2c_read(rmi4_data, cherry_glove_enable_addr, &value,
			sizeof(value));
	if (retval < 0) {
		TS_LOG_ERR("read glove switch(%d) err : %d\n", *glove_switch, retval);
		goto out;
	}
	if(0 == value)
	{
		*glove_switch = GLOVE_SWITCH_ON;
	}
	else if(2 == value)
	{
		*glove_switch = GLOVE_SWITCH_OFF;
	}
	else
	{
		TS_LOG_ERR("read glove switch value err : %d\n", value);
		retval = -EINVAL;
		goto out;
	}
out:
	return retval;
}

static int synaptics_set_glove_switch(u8 glove_switch)
{
	int retval = NO_ERR;
	u8 value = 0;
/*
	retval = synaptics_get_glove_enable_addr(rmi4_data, &glove_enable_addr);
	if (retval < 0) {
		TS_LOG_ERR("get glove addr err : %d\n", retval);
		goto out;
	}
*/
	if(GLOVE_SWITCH_ON==glove_switch)
		value =0;
	else if(GLOVE_SWITCH_OFF==glove_switch)
		value =2;
	retval = synaptics_rmi4_i2c_write(rmi4_data, cherry_glove_enable_addr, &value, 1);
	if (retval < 0) {
		TS_LOG_ERR("open glove function failed: %d\n", retval);
	}
	return retval;
}

static int synaptics_glove_switch(struct ts_glove_info *info)
{
	int retval = NO_ERR;
	u8 buf = 0;

	if (!info) {
		TS_LOG_ERR("synaptics_glove_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}
	switch (info->op_action) {
		case TS_ACTION_READ:
			retval = synaptics_get_glove_switch(&buf);
			if (retval < 0) {
				TS_LOG_ERR("get glove switch(%d), failed : %d", info->glove_switch, retval);
				break;
			}
			info->glove_switch = buf;
			TS_LOG_INFO("read_glove_switch=%d\n",info->glove_switch);
			break;
		case TS_ACTION_WRITE:
			buf = info->glove_switch;
			TS_LOG_INFO("write_glove_switch=%d\n",info->glove_switch);
			if((GLOVE_SWITCH_ON != info->glove_switch)&&(GLOVE_SWITCH_OFF != info->glove_switch))
			{
				TS_LOG_ERR("write wrong state: buf = %d\n", buf);
				retval = -EFAULT;
				break;
			}
			retval = synaptics_set_glove_switch(buf);
			if (retval < 0) {
				TS_LOG_ERR("set glove switch(%d), failed : %d", buf, retval);
			}
			break;
		default:
			TS_LOG_ERR("invalid switch status: %d", info->glove_switch);
			retval = -EINVAL;
			break;
	}

	return retval;
}
static void synaptics_shutdown(void)
{
	TS_LOG_INFO("synaptics_shutdown\n");
	synaptics_gpio_free();
	synaptics_regulator_put();
	return;
}

/*  do some things before power off. 
*/
static int synaptics_before_suspend(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("before_suspend +\n");
#ifdef GLOVE_SIGNAL
	retval = synaptics_get_glove_switch(&rmi4_data->rmi4_feature.glove_switch);
	if (retval < 0) {
		TS_LOG_ERR("Failed to get glove switch(%d), err: %d", 
			rmi4_data->rmi4_feature.glove_switch, retval);
	}
#endif
	TS_LOG_INFO("before_suspend -\n");
	return retval;
}
#ifdef HUAWEI_EASY_WAKEUP
static void synaptics_put_device_into_easy_wakeup(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char device_ctrl;
	struct ts_easy_wakeup_info *info = &(g_ts_data_synaptics->easy_wakeup_info);
	TS_LOG_DEBUG("synaptics_put_device_into_easy_wakeup  info->easy_wakeup_flag =%x \n",info->easy_wakeup_flag);
	//if the sleep_gesture_flag is ture,it presents that  the tp is at sleep state	

	if (true == info->easy_wakeup_flag)	{
		TS_LOG_INFO("synaptics_put_device_into_easy_wakeup  info->easy_wakeup_flag =%x \n",info->easy_wakeup_flag);
		return;
	}
	
	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f11_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR(" Failed to enter sleep mode1\n");
		rmi4_data->sensor_sleep = false;
		return;
	}

	device_ctrl = (device_ctrl & ~MASK_3BIT);  // get the high five bits,i'dont
	device_ctrl = (device_ctrl | 0x04);		//easy-wakeup bit  
	retval = synaptics_rmi4_i2c_write(rmi4_data,
			rmi4_data->f11_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));
	
	if (retval < 0) {
		TS_LOG_ERR("Failed to enter sleep mode2\n");
		rmi4_data->sensor_sleep = false;
		return;
	} else{
		rmi4_data->sensor_sleep = true;
	}

	/*set fast_rate*/
	device_ctrl = 0x07;
	retval = synaptics_rmi4_i2c_write(rmi4_data,
			EASY_WAKEUP_FASTRATE,
			&device_ctrl,
			sizeof(device_ctrl));
			
	if (retval < 0) {
		TS_LOG_ERR("Failed to set fastrate\n");
		rmi4_data->sensor_sleep = false;
		return;
	} else{
		rmi4_data->sensor_sleep = true;
	}
	
	TS_LOG_DEBUG(" read from  f11_ctrl_base_addr92  rmi4_data->f11_ctrl_base_addr  = 0x%0x rmi4_data->f11_ctrl_base_addr+92 =0x%0x\n",rmi4_data->f11_ctrl_base_addr,
		rmi4_data->f11_ctrl_base_addr+45);
		
    	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f11_ctrl_base_addr+45,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("%s: Failed to set wakeup mode3\n",__func__);
		rmi4_data->sensor_sleep = false;
		return;
	}else {
		rmi4_data->sensor_sleep = true;
	}	
	
    	TS_LOG_DEBUG(" read from  f11_ctrl_base_addr92  ctrl1 = %0x retval =%0x\n",device_ctrl,retval);

	/*set no_sleep bit = 0*/
	/*retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f01_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("%s: Failed to set wakeup mode5\n",__func__);
		rmi4_data->sensor_sleep = false;
		return;
	}else {
		rmi4_data->sensor_sleep = true;
	}

	device_ctrl = device_ctrl & 0xFB;
	TS_LOG_DEBUG(" read from  f11_ctrl_base_addr92  ctrl1 = %0x retval =%0x\n",device_ctrl,retval);

	retval = synaptics_rmi4_i2c_write(rmi4_data,
			rmi4_data->f01_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));

	if (retval < 0) {
		TS_LOG_ERR("Failed to set wakeup mode6\n");
		rmi4_data->sensor_sleep = false;
		return;
	} else {
		rmi4_data->sensor_sleep = true;
	}*/
	/*force Update register*/
	retval = synaptics_rmi4_i2c_read(rmi4_data,
			F54_ANALOG_CMD0,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("Failed to set wakeup mode7\n");
		rmi4_data->sensor_sleep = false;
		return;
	}else {
		rmi4_data->sensor_sleep = true;
	}

	device_ctrl = device_ctrl |0x04;
	TS_LOG_DEBUG(" read from  f11_ctrl_base_addr92  ctrl1 = %0x retval =%0x\n",device_ctrl,retval);

	retval = synaptics_rmi4_i2c_write(rmi4_data,
			F54_ANALOG_CMD0,
			&device_ctrl,
			sizeof(device_ctrl));

	if (retval < 0) {
		TS_LOG_ERR("Failed to set wakeup mode8\n");
		rmi4_data->sensor_sleep = false;
		return;
	} else {
		rmi4_data->sensor_sleep = true;
	}
	info->easy_wakeup_flag=true;

	return;
}


static void synaptics_put_device_outof_easy_wakeup(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char device_ctrl;
	struct ts_easy_wakeup_info *info = &(g_ts_data_synaptics->easy_wakeup_info);
	
	TS_LOG_DEBUG("synaptics_put_device_outof_easy_wakeup  info->easy_wakeup_flag =%d\n",info->easy_wakeup_flag);

	if (false == info->easy_wakeup_flag)	{
			return;
	}

	//set fastrate
	device_ctrl = rmi4_data->easy_wakeup_fastrate;
	retval = synaptics_rmi4_i2c_write(rmi4_data,
			EASY_WAKEUP_FASTRATE,
			&device_ctrl,
			sizeof(device_ctrl));
			
	if (retval < 0) {
		TS_LOG_ERR("Failed to out of  sleep mode1\n");
		rmi4_data->sensor_sleep = true;
		return;
	}

	/*set no_sleep bit = 1*/
	/*retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f01_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));

	if (retval < 0) {
		TS_LOG_ERR(" Failed to out of  sleep mode2\n");
		rmi4_data->sensor_sleep = true;
		return;
	}
	device_ctrl = device_ctrl | 0x04;
	retval = synaptics_rmi4_i2c_write(rmi4_data,
			rmi4_data->f01_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("Failed to out of  sleep mode3\n");
		rmi4_data->sensor_sleep = true;
		return;
	} else {
		rmi4_data->sensor_sleep = false;
	}*/
	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f11_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));

	if (retval < 0) {
		TS_LOG_ERR("Failed to out of  sleep mode4\n");
		rmi4_data->sensor_sleep = true;
		return;
	}	
	device_ctrl = ((device_ctrl & (~MASK_3BIT))|MASK_1BIT);
	retval = synaptics_rmi4_i2c_write(rmi4_data,
			rmi4_data->f11_ctrl_base_addr,
			&device_ctrl,
			sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("Failed to out of  sleep mode5\n");
		rmi4_data->sensor_sleep = true;
		return;
	} else {
		rmi4_data->sensor_sleep = false;
	}
	info->easy_wakeup_flag=false;
	return;
}


static void synaptics_put_device_into_sleep(struct synaptics_rmi4_data *rmi4_data)
{
	struct ts_easy_wakeup_info *info = &(g_ts_data_synaptics->easy_wakeup_info);
	TS_LOG_INFO("synaptics_put_device_into_sleep easy_wakeup_gesture=%0x\n",info->easy_wakeup_gesture);
	if(true == info->palm_cover_flag)
		info->palm_cover_control = false;
	if (  info->easy_wakeup_gesture != 0 ){		
		synaptics_put_device_into_easy_wakeup(rmi4_data);
	}
	else{
		synaptics_power_off();	
	}
	return;
}

static void synaptics_put_device_into_wake(struct synaptics_rmi4_data *rmi4_data)
{
	struct ts_easy_wakeup_info *info = &(g_ts_data_synaptics->easy_wakeup_info);
	TS_LOG_INFO("synaptics_put_device_into_sleep easy_wakeup_gesture=%0x\n",info->easy_wakeup_gesture);
	if(true == info->palm_cover_flag)
		info->palm_cover_control = true;
	if (info->easy_wakeup_gesture != 0 && (rmi4_data->touch_stopped != true) ) {	
		synaptics_put_device_outof_easy_wakeup(rmi4_data);
	}
	else{
		synaptics_power_on();
		synaptics_gpio_reset();
	}
	return;
}
#endif
/*    just power off the device.
*/
static int synaptics_suspend(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("suspend +\n");
#ifdef HUAWEI_EASY_WAKEUP
	synaptics_put_device_into_sleep(rmi4_data);
	mutex_lock(&wrong_touch_lock);
	off_motion_on=1;
	mutex_unlock(&wrong_touch_lock);
#else
	/*for in_cell, tp will power off in suspend.*/
	synaptics_power_off();
#endif
	TS_LOG_INFO("suspend -\n");
	return retval;
}

/*    do not add time-costly function here.
*/
static int synaptics_resume(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("resume +\n");
#ifdef HUAWEI_EASY_WAKEUP
	synaptics_put_device_into_wake(rmi4_data);
#else
	synaptics_power_on();
	synaptics_gpio_reset();
#endif
	TS_LOG_INFO("resume -\n");
	return retval;
}

/*  do some things after power on. */
static int synaptics_after_resume(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("after_resume +\n");

	msleep(100);
	/*empty list and query device again*/
	synaptics_rmi4_empty_fn_list(rmi4_data);
	retval = synaptics_rmi4_query_device(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to query device\n");
		return retval;
	}

#ifdef GLOVE_SIGNAL
	rmi_f11_filter_glove_init();
	retval = synaptics_set_glove_switch(rmi4_data->rmi4_feature.glove_switch);
	if (retval < 0) {
		TS_LOG_ERR("Failed to set glove switch(%d), err: %d\n", 
			rmi4_data->rmi4_feature.glove_switch, retval);
	}
#endif
	TS_LOG_INFO("after_resume -\n");
	return retval;
}

static int synaptics_rmi4_reset_command(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	int page_number;
	unsigned char command = 0x01;
	unsigned short pdt_entry_addr = 0;
	struct synaptics_rmi4_fn_desc rmi_fd = {0};
	struct synaptics_rmi4_f01_device_status status;
	bool done = false;

rescan:
	/* Scan the page description tables of the pages to service */
	for (page_number = 0; page_number < PAGES_TO_SERVICE; page_number++) {
		for (pdt_entry_addr = PDT_START; pdt_entry_addr > PDT_END;
				pdt_entry_addr -= PDT_ENTRY_SIZE) {
			pdt_entry_addr |= (page_number << 8);

			retval = synaptics_rmi4_i2c_read(rmi4_data,
					pdt_entry_addr,
					(unsigned char *)&rmi_fd,
					sizeof(rmi_fd));
			if (retval < 0)
				return retval;

			if (rmi_fd.fn_number == 0)
				break;

			switch (rmi_fd.fn_number) {
			case SYNAPTICS_RMI4_F01:
				rmi4_data->f01_cmd_base_addr =
						rmi_fd.cmd_base_addr;
				rmi4_data->f01_data_base_addr =
						rmi_fd.data_base_addr;
				if (synaptics_rmi4_crc_in_progress(rmi4_data, &status))
					goto rescan;
				done = true;
				break;
			}
		}
		if (done) {
			TS_LOG_DEBUG("Find F01 in page description table 0x%x\n", rmi4_data->f01_cmd_base_addr);
			break;
		}
	}

	if (!done) {
		TS_LOG_ERR("Cannot find F01 in page description table\n");
		return -EINVAL;;
	}

	retval = synaptics_rmi4_i2c_write(rmi4_data,
			rmi4_data->f01_cmd_base_addr,
			&command,
			sizeof(command));
	if (retval < 0) {
		TS_LOG_ERR("Failed to issue reset command, error = %d\n", retval);
		return retval;
	}

	msleep(rmi4_data->reset_delay_ms);
	return retval;
}

static void synaptics_rmi4_empty_fn_list(struct synaptics_rmi4_data *rmi4_data)
{
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_fn *fhandler_temp = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;

	rmi = &(rmi4_data->rmi4_mod_info);

	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry_safe(fhandler, fhandler_temp, &rmi->support_fn_list, link) {
			list_del(&fhandler->link);
			if (fhandler->fn_number == SYNAPTICS_RMI4_F1A) {
				synaptics_rmi4_f1a_kfree(fhandler);
			} else {
				if (fhandler->data) {
					kfree(fhandler->data);
					fhandler->data = NULL;
				}
			}
			kfree(fhandler);
			fhandler = NULL;
		}
	}

	return;
}

static int synaptics_rmi4_reset_device(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = NO_ERR;

	if (!rmi4_data) {
		TS_LOG_ERR("rmi4_data is NULL \n");
		retval = -ENOMEM;
		return retval;
	}

	TS_LOG_DEBUG("synaptics_rmi4_reset_device called\n");

	retval = synaptics_rmi4_reset_command(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to send command reset\n");
		return retval;
	}

	synaptics_rmi4_empty_fn_list(rmi4_data);

	retval = synaptics_rmi4_query_device(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to query device\n");
		return retval;
	}

	TS_LOG_DEBUG("synaptics_rmi4_reset_device end\n");
	return 0;
}

/**
 * synaptics_rmi4_i2c_read()
 *
 * Called by various functions in this driver, and also exported to
 * other expansion Function modules such as rmi_dev.
 *
 * This function reads data of an arbitrary length from the sensor,
 * starting from an assigned register address of the sensor, via I2C
 * with a retry mechanism.
 */
static int synaptics_rmi4_i2c_read(struct synaptics_rmi4_data *rmi4_data,
		unsigned short addr, unsigned char *data, unsigned short length)
{
	int retval;
	unsigned char reg_addr = addr & MASK_8BIT;

	retval = synaptics_rmi4_set_page(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		TS_LOG_ERR("error, retval != PAGE_SELECT_LEN\n");
		goto exit;
	}

	if (!rmi4_data->synaptics_chip_data->bops->bus_read) {
		TS_LOG_ERR("error, invalid bus_rad\n");
		retval = -EIO;
		goto exit;
	}
	retval = rmi4_data->synaptics_chip_data->bops->bus_read(&reg_addr,1, data, length);
	if (retval < 0) {
		TS_LOG_ERR("error, bus read failed, retval  = %d\n", retval);
		goto exit;
	}

exit:
	return retval;
}

 /**
 * synaptics_rmi4_i2c_write()
 *
 * Called by various functions in this driver, and also exported to
 * other expansion Function modules such as rmi_dev.
 *
 * This function writes data of an arbitrary length to the sensor,
 * starting from an assigned register address of the sensor, via I2C with
 * a retry mechanism.
 */
static int synaptics_rmi4_i2c_write(struct synaptics_rmi4_data *rmi4_data,
		unsigned short addr, unsigned char *data, unsigned short length)
{
	int retval;
	unsigned char reg_addr = addr & MASK_8BIT;
	unsigned char wr_buf[length+1];
	wr_buf[0] = reg_addr;
	memcpy(wr_buf+1, data, length);
	
	retval = synaptics_rmi4_set_page(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		TS_LOG_ERR("retval != PAGE_SELECT_LEN, retval = %d\n", retval);
		goto exit;
	}

	if (!rmi4_data->synaptics_chip_data->bops->bus_write) {
		TS_LOG_ERR("bus_write not exits\n");
		retval = -EIO;
		goto exit;
	}
	retval = rmi4_data->synaptics_chip_data->bops->bus_write(wr_buf, length+1);
	if (retval < 0) {
		TS_LOG_ERR("bus_write failed, retval = %d\n", retval);
		goto exit;
	}

exit:
	return retval;
}
static int synaptics_rmi4_f51_init(struct synaptics_rmi4_data *rmi4_data,
		 struct synaptics_rmi4_fn_desc *fd,
		 unsigned char page)
{
	 rmi4_data->f51_query_base_addr = fd->query_base_addr | (page << 8);
	 rmi4_data->f51_ctrl_base_addr = fd->ctrl_base_addr | (page << 8);
	 rmi4_data->f51_data_base_addr = fd->data_base_addr | (page << 8);
	 rmi4_data->f51_cmd_base_addr = fd->cmd_base_addr | (page << 8);
	 return 0;
}
 /**
 * synaptics_rmi4_query_device()
 *
 * Called by synaptics_init_chip().
 *
 * This funtion scans the page description table, records the offsets
 * to the register types of Function $01, sets up the function handlers
 * for Function $11 and Function $12, determines the number of interrupt
 * sources from the sensor, adds valid Functions with data inputs to the
 * Function linked list, parses information from the query registers of
 * Function $01, and enables the interrupt sources from the valid Functions
 * with data inputs.
 */
static int synaptics_rmi4_query_device(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char ii;
	unsigned char page_number;
	unsigned char intr_count;
	unsigned char data_sources;
	unsigned short pdt_entry_addr;
	unsigned short intr_addr;
	struct synaptics_rmi4_f01_device_status status;
	struct synaptics_rmi4_fn_desc rmi_fd = {0};
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;

	rmi = &(rmi4_data->rmi4_mod_info);

rescan:
	INIT_LIST_HEAD(&rmi->support_fn_list);
	intr_count = 0;
	data_sources = 0;

	/* Scan the page description tables of the pages to service */
	for (page_number = 0; page_number < PAGES_TO_SERVICE; page_number++) {
		for (pdt_entry_addr = PDT_START; pdt_entry_addr > PDT_END;
				pdt_entry_addr -= PDT_ENTRY_SIZE) {
			pdt_entry_addr |= (page_number << 8);
			retval = synaptics_rmi4_i2c_read(rmi4_data,
					pdt_entry_addr,
					(unsigned char *)&rmi_fd,
					sizeof(rmi_fd));
			if (retval < 0){
				TS_LOG_ERR("read pdt_entry_addr = %d regiseter error happened\n", pdt_entry_addr);
				return retval;
			}
			fhandler = NULL;

			if (rmi_fd.fn_number == 0) {
				TS_LOG_DEBUG("Reached end of PDT\n");
				break;
			}

			TS_LOG_DEBUG("F%02x found (page %d)\n", rmi_fd.fn_number, page_number);

			switch (rmi_fd.fn_number) {
			case SYNAPTICS_RMI4_F01:
				rmi4_data->f01_query_base_addr = rmi_fd.query_base_addr;
				rmi4_data->f01_ctrl_base_addr = rmi_fd.ctrl_base_addr;
				rmi4_data->f01_data_base_addr = rmi_fd.data_base_addr;
				rmi4_data->f01_cmd_base_addr = rmi_fd.cmd_base_addr;

				if (synaptics_rmi4_crc_in_progress(rmi4_data, &status))
					goto rescan;

				retval = synaptics_rmi4_query_device_info(rmi4_data);
				if (retval < 0){
					TS_LOG_ERR("Failed to read device_info \n");
					return retval;
				}
				if (status.flash_prog == 1) {
					TS_LOG_INFO("In flash prog mode, status = 0x%02x\n", status.status_code);
					rmi4_data->force_update = true;	/*crc error, force update fw to workaround*/
				}
				break;

			case SYNAPTICS_RMI4_F11:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler = synaptics_rmi4_alloc_fh(&rmi_fd, page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n", rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval = synaptics_rmi4_f11_init(rmi4_data, fhandler, &rmi_fd, intr_count);
				if (retval < 0){
					TS_LOG_ERR("Failed to init f12 handler , retval = %d\n", retval);
					return retval;
				}
				break;

			case SYNAPTICS_RMI4_F12:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler = synaptics_rmi4_alloc_fh(&rmi_fd, page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n", rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval = synaptics_rmi4_f12_init(rmi4_data, fhandler, &rmi_fd, intr_count);
				if (retval < 0)
					return retval;
				break;

			case SYNAPTICS_RMI4_F1A:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler = synaptics_rmi4_alloc_fh(&rmi_fd, page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n", rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval = synaptics_rmi4_f1a_init(rmi4_data, fhandler, &rmi_fd, intr_count);
				if (retval < 0){
					TS_LOG_ERR("Failed to init f1a handler , retval = %d\n", retval);
					return retval;
				}
				break;
			case SYNAPTICS_RMI4_F51:
					TS_LOG_INFO("SYNAPTICS_RMI4_F51\n");
					TS_LOG_INFO("rmi_fd.intr_src_count =0x%x\n",rmi_fd.intr_src_count);
				fhandler = synaptics_rmi4_alloc_fh(&rmi_fd, page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",rmi_fd.fn_number);
					return retval;
				}
			
				retval = synaptics_rmi4_f51_init(rmi4_data,
						&rmi_fd, page_number);
				if (retval < 0)
					return retval;
				break;
			case SYNAPTICS_RMI4_F54:
			case SYNAPTICS_RMI4_F55:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler = synaptics_rmi4_alloc_fh(&rmi_fd, page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n", rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}
				break;

			default:
				break;
			}

			/* Accumulate the interrupt count */
			intr_count += (rmi_fd.intr_src_count & MASK_3BIT);

			if (fhandler && rmi_fd.intr_src_count) {
				list_add_tail(&fhandler->link, &rmi->support_fn_list);
			}
		}
	}

	rmi4_data->num_of_intr_regs = (intr_count + 7) / 8;
	TS_LOG_DEBUG("Number of interrupt registers = %d\n", rmi4_data->num_of_intr_regs);

	memset(rmi4_data->intr_mask, 0x00, sizeof(rmi4_data->intr_mask));

	/*
	 * Map out the interrupt bit masks for the interrupt sources
	 * from the registered function handlers.
	 */
	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry(fhandler, &rmi->support_fn_list, link)
			data_sources += fhandler->num_of_data_sources;
	}
	if (data_sources) {
		if (!list_empty(&rmi->support_fn_list)) {
			list_for_each_entry(fhandler,
						&rmi->support_fn_list, link) {
				if (fhandler->num_of_data_sources) {
					rmi4_data->intr_mask[fhandler->intr_reg_num] |=
							fhandler->intr_mask;
				}
			}
		}
	}else{
	TS_LOG_ERR("the num of data sources init fail from IC == %d\n", data_sources);
	}

	/* Enable the interrupt sources */
	for (ii = 0; ii < rmi4_data->num_of_intr_regs; ii++) {
		if (rmi4_data->intr_mask[ii] != 0x00) {
			TS_LOG_DEBUG("Interrupt enable mask %d = 0x%02x\n", ii, rmi4_data->intr_mask[ii]);
			intr_addr = rmi4_data->f01_ctrl_base_addr + 1 + ii;
			retval = synaptics_rmi4_i2c_write(rmi4_data,
					intr_addr,
					&(rmi4_data->intr_mask[ii]),
					sizeof(rmi4_data->intr_mask[ii]));
			if (retval < 0) {
				TS_LOG_ERR("Failed to enable interrupt sources, error:%d", retval);
				return retval;
			}
		}
	}

	return 0;
}

  /**
 * synaptics_rmi4_crc_in_progress()
 *
 * Check if crc in progress ever occured
 *
 */
static bool synaptics_rmi4_crc_in_progress(struct synaptics_rmi4_data *rmi4_data, 
			struct synaptics_rmi4_f01_device_status *status)
{
	int retval;
	int times = 0;
	bool rescan = false;

	while (1) {
		retval = synaptics_rmi4_i2c_read(rmi4_data,
				rmi4_data->f01_data_base_addr,
				status->data,
				sizeof(status->data));
		if (retval < 0) {
			TS_LOG_ERR("read rmi4_data->f01_data_base_addr = %d status register failed\n", rmi4_data->f01_data_base_addr);
			return false;
		}
		if (status->status_code == STATUS_CRC_IN_PROGRESS) {
			TS_LOG_ERR("CRC is in progress..., the statu_scode is %d \n", status->status_code);
			rescan = true;
			msleep(20);
		} else {
			TS_LOG_DEBUG("CRC is success, CRC test times = %d\n", times);
			break;
		}
		if (times++ > 500)
			return false;
	}
	return rescan;
}

/**
 * synaptics_rmi4_set_page()
 *
 * Called by synaptics_rmi4_i2c_read() and synaptics_rmi4_i2c_write().
 *
 * This function writes to the page select register to switch to the
 * assigned page.
 */
static int synaptics_rmi4_set_page(struct synaptics_rmi4_data *rmi4_data,
		unsigned int address)
{
	int retval = NO_ERR;
	unsigned char buf[PAGE_SELECT_LEN];
	unsigned char page;

	page = ((address >> 8) & MASK_8BIT);
	if (page != rmi4_data->current_page) {
		buf[0] = MASK_8BIT;
		buf[1] = page;
		retval = rmi4_data->synaptics_chip_data->bops->bus_write(buf, PAGE_SELECT_LEN);
		if (retval != NO_ERR) {
			TS_LOG_ERR("bus_write failed\n");
		} else {
			rmi4_data->current_page = page;
		}
	} else {
		return PAGE_SELECT_LEN;
	}
	return (retval == NO_ERR) ? PAGE_SELECT_LEN : -EIO;	
}

static struct synaptics_rmi4_fn * synaptics_rmi4_alloc_fh(
		struct synaptics_rmi4_fn_desc *rmi_fd, int page_number)
{
	struct synaptics_rmi4_fn *fhandler;

	fhandler = kzalloc(sizeof(struct synaptics_rmi4_fn), GFP_KERNEL);
	if (!fhandler) {
		TS_LOG_ERR("Failed to alloc memory for fhandler\n");
		return NULL;
	}

	fhandler->full_addr.data_base = (rmi_fd->data_base_addr |(page_number << 8));
	fhandler->full_addr.ctrl_base = (rmi_fd->ctrl_base_addr |(page_number << 8));
	fhandler->full_addr.cmd_base = (rmi_fd->cmd_base_addr |	(page_number << 8));
	fhandler->full_addr.query_base = (rmi_fd->query_base_addr |(page_number << 8));
	fhandler->fn_number = rmi_fd->fn_number;
	TS_LOG_DEBUG("handler number is %d, it's data_base_addr = %d, ctrl_base_addr = %d, cmd_base_addr = %d,query_base_addr = %d, page_number = %d\n",
		rmi_fd->fn_number, rmi_fd->data_base_addr, rmi_fd->ctrl_base_addr, rmi_fd->cmd_base_addr, rmi_fd->query_base_addr, page_number);
	return fhandler;
}

 /**
 * synaptics_rmi4_query_device_info()
 *
 * Called by synaptics_rmi4_query_device().
 *
 */
static int synaptics_rmi4_query_device_info(
					struct synaptics_rmi4_data *rmi4_data)
{
	int count=0; 
	int retval = 0;
	unsigned char f01_query[F01_STD_QUERY_LEN] = {0};
	struct synaptics_rmi4_device_info *rmi = &(rmi4_data->rmi4_mod_info);

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f01_query_base_addr,
			f01_query,
			sizeof(f01_query));
	if (retval < 0){
		TS_LOG_ERR("Failed to read f01_query_base_addr %d\n", rmi4_data->f01_query_base_addr);
		return retval;
	}
	/* RMI Version 4.0 currently supported */
	rmi->version_major = 4;
	rmi->version_minor = 0;

	rmi->manufacturer_id = f01_query[0];
	rmi->product_props = f01_query[1];
	rmi->product_info[0] = f01_query[2] & MASK_7BIT;
	rmi->product_info[1] = f01_query[3] & MASK_7BIT;
	rmi->date_code[0] = f01_query[4] & MASK_5BIT;
	rmi->date_code[1] = f01_query[5] & MASK_4BIT;
	rmi->date_code[2] = f01_query[6] & MASK_5BIT;
	rmi->tester_id = ((f01_query[7] & MASK_7BIT) << 8) |(f01_query[8] & MASK_7BIT);
	rmi->serial_number = ((f01_query[9] & MASK_7BIT) << 8) |(f01_query[10] & MASK_7BIT);
	memcpy(rmi->product_id_string, &f01_query[11], 10);
	
	for (count =0;synaptics_sett_param_regs_map[count].module_name  !=NULL;count++)
	{
		if ((synaptics_sett_param_regs_map[count].build_id[0] == f01_query[18])&&
			(synaptics_sett_param_regs_map[count].build_id[1] == f01_query[19])&&(synaptics_sett_param_regs_map[count].build_id[2] == f01_query[20]))
		{
			synaptics_sett_param_regs = &synaptics_sett_param_regs_map[count];
			break;
		}
	}
	TS_LOG_INFO("module id is %s(%c%c%c)\n", synaptics_sett_param_regs->module_name,f01_query[18],f01_query[19],f01_query[20]);
	if (rmi->manufacturer_id != 1) {
		TS_LOG_ERR("Non-Synaptics device found, manufacturer ID = %d\n",
			rmi->manufacturer_id);
	}

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f01_query_base_addr + F01_BUID_ID_OFFSET,
			rmi->build_id,
			sizeof(rmi->build_id));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read firmware build id (code %d)\n", retval);
		return retval;
	}
	return 0;
}

  /**
 * synaptics_rmi4_f11_init()
 *
 * Called by synaptics_rmi4_query_device().
 *
 * This funtion parses information from the Function 11 registers
 * and determines the number of fingers supported, x and y data ranges,
 * offset to the associated interrupt status register, interrupt bit
 * mask, and gathers finger data acquisition capabilities from the query
 * registers.
 */
static int synaptics_rmi4_f11_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count)
{
	int retval = 0;
	unsigned char ii = 0;
	unsigned char intr_offset = 0;
	unsigned char abs_data_size = 0;
	unsigned char abs_data_blk_size = 0;
	unsigned char query[F11_STD_QUERY_LEN] = {0};
	unsigned char control[F11_STD_CTRL_LEN] = {0};

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.query_base,
			query,
			sizeof(query));
	if (retval < 0){
		TS_LOG_ERR("Failed to read f11 query base reg\n");
		return retval;
	}
	/* Maximum number of fingers supported */
	if ((query[1] & MASK_3BIT) <= 4)
		fhandler->num_of_data_points = (query[1] & MASK_3BIT) + 1;
	else if ((query[1] & MASK_3BIT) == 5)
		fhandler->num_of_data_points = 10;

	rmi4_data->num_of_fingers = fhandler->num_of_data_points;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.ctrl_base,
			control,
			sizeof(control));
	if (retval < 0){
		TS_LOG_ERR("Failed to read f11 ctrl base reg\n");
		return retval;
	}
	/* Maximum x and y */
	rmi4_data->sensor_max_x = ((control[6] & MASK_8BIT) << 0) |
			((control[7] & MASK_4BIT) << 8);
	rmi4_data->sensor_max_y = ((control[8] & MASK_8BIT) << 0) |
			((control[9] & MASK_4BIT) << 8);

	TS_LOG_INFO("Function %02x max x = %d max y = %d\n", fhandler->fn_number,
			rmi4_data->sensor_max_x,
			rmi4_data->sensor_max_y);

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset; ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	abs_data_size = query[5] & MASK_2BIT;
	abs_data_blk_size = 3 + (2 * (abs_data_size == 0 ? 1 : 0));
	fhandler->size_of_data_register_block = abs_data_blk_size;
	rmi4_data->f11_query_base_addr = fd->query_base_addr;
	rmi4_data->f11_ctrl_base_addr = fd->ctrl_base_addr;
	rmi4_data->f11_data_base_addr = fd->data_base_addr;
	rmi4_data->f11_cmd_base_addr = fd->cmd_base_addr;
	return retval;
}

static int synaptics_rmi4_f12_set_enables(struct synaptics_rmi4_data *rmi4_data,
		unsigned short ctrl28)
{
	int retval;
	static unsigned short ctrl_28_address;

	if (ctrl28)
		ctrl_28_address = ctrl28;

	retval = synaptics_rmi4_i2c_write(rmi4_data,
			ctrl_28_address,
			&rmi4_data->report_enable,
			sizeof(rmi4_data->report_enable));
	if (retval < 0) {
		TS_LOG_ERR("Failed to set enable f12, error:%d\n", retval);
		return retval;
	}

	return retval;
}

 /**
 * synaptics_rmi4_f12_init()
 *
 * Called by synaptics_rmi4_query_device().
 *
 * This funtion parses information from the Function 12 registers and
 * determines the number of fingers supported, offset to the data1
 * register, x and y data ranges, offset to the associated interrupt
 * status register, interrupt bit mask, and allocates memory resources
 * for finger data acquisition.
 */
static int synaptics_rmi4_f12_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count)
{
	int retval;
	unsigned char ii;
	unsigned char intr_offset;
	unsigned char size_of_2d_data;
	unsigned char size_of_query8 = 0;
	unsigned char ctrl_8_offset;
	unsigned char ctrl_23_offset;
	unsigned char ctrl_28_offset;
	unsigned char num_of_fingers;
	struct synaptics_rmi4_f12_extra_data *extra_data;
	struct synaptics_rmi4_f12_query_5 query_5;
	struct synaptics_rmi4_f12_query_8 query_8;
	struct synaptics_rmi4_f12_ctrl_8 ctrl_8;
	struct synaptics_rmi4_f12_ctrl_23 ctrl_23;

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;
	fhandler->extra = kmalloc(sizeof(*extra_data), GFP_KERNEL);
	if (fhandler->extra == NULL) {
		TS_LOG_ERR("Failed to alloc memory for fhandler->extra\n");
		retval = -ENOMEM;
		return retval;
	}

	extra_data = (struct synaptics_rmi4_f12_extra_data *)fhandler->extra;
	size_of_2d_data = sizeof(struct synaptics_rmi4_f12_finger_data);

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.query_base + 5,
			query_5.data,
			sizeof(query_5.data));
	if (retval < 0)
		return retval;

	ctrl_8_offset = query_5.ctrl0_is_present +
			query_5.ctrl1_is_present +
			query_5.ctrl2_is_present +
			query_5.ctrl3_is_present +
			query_5.ctrl4_is_present +
			query_5.ctrl5_is_present +
			query_5.ctrl6_is_present +
			query_5.ctrl7_is_present;

	ctrl_23_offset = ctrl_8_offset +
			query_5.ctrl8_is_present +
			query_5.ctrl9_is_present +
			query_5.ctrl10_is_present +
			query_5.ctrl11_is_present +
			query_5.ctrl12_is_present +
			query_5.ctrl13_is_present +
			query_5.ctrl14_is_present +
			query_5.ctrl15_is_present +
			query_5.ctrl16_is_present +
			query_5.ctrl17_is_present +
			query_5.ctrl18_is_present +
			query_5.ctrl19_is_present +
			query_5.ctrl20_is_present +
			query_5.ctrl21_is_present +
			query_5.ctrl22_is_present;

	ctrl_28_offset = ctrl_23_offset +
			query_5.ctrl23_is_present +
			query_5.ctrl24_is_present +
			query_5.ctrl25_is_present +
			query_5.ctrl26_is_present +
			query_5.ctrl27_is_present;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.ctrl_base + ctrl_23_offset,
			ctrl_23.data,
			sizeof(ctrl_23.data));
	if (retval < 0)
		return retval;

	/* Maximum number of fingers supported */
	fhandler->num_of_data_points = min(ctrl_23.max_reported_objects,
			(unsigned char)F12_FINGERS_TO_SUPPORT);

	num_of_fingers = fhandler->num_of_data_points;
	rmi4_data->num_of_fingers = num_of_fingers;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.query_base + 7,
			&size_of_query8,
			sizeof(size_of_query8));
	if (retval < 0)
		return retval;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.query_base + 8,
			query_8.data,
			size_of_query8);
	if (retval < 0)
		return retval;

	/* Determine the presence of the Data0 register */
	extra_data->data1_offset = query_8.data0_is_present;

	if ((size_of_query8 >= 3) && (query_8.data15_is_present)) {
		extra_data->data15_offset = query_8.data0_is_present +
				query_8.data1_is_present +
				query_8.data2_is_present +
				query_8.data3_is_present +
				query_8.data4_is_present +
				query_8.data5_is_present +
				query_8.data6_is_present +
				query_8.data7_is_present +
				query_8.data8_is_present +
				query_8.data9_is_present +
				query_8.data10_is_present +
				query_8.data11_is_present +
				query_8.data12_is_present +
				query_8.data13_is_present +
				query_8.data14_is_present;
		extra_data->data15_size = (num_of_fingers + 7) / 8;
	} else {
		extra_data->data15_size = 0;
	}

	rmi4_data->report_enable = RPT_DEFAULT;
#ifdef REPORT_2D_Z
	rmi4_data->report_enable |= RPT_Z;
#endif
#ifdef REPORT_2D_W
	rmi4_data->report_enable |= (RPT_WX | RPT_WY);
#endif

	retval = synaptics_rmi4_f12_set_enables(rmi4_data,
			fhandler->full_addr.ctrl_base + ctrl_28_offset);
	if (retval < 0)
		return retval;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.ctrl_base + ctrl_8_offset,
			ctrl_8.data,
			sizeof(ctrl_8.data));
	if (retval < 0)
		return retval;

	/* Maximum x and y */
	rmi4_data->sensor_max_x =
			((unsigned short)ctrl_8.max_x_coord_lsb << 0) |
			((unsigned short)ctrl_8.max_x_coord_msb << 8);
	rmi4_data->sensor_max_y =
			((unsigned short)ctrl_8.max_y_coord_lsb << 0) |
			((unsigned short)ctrl_8.max_y_coord_msb << 8);
	TS_LOG_INFO("Function %02x max x = %d max y = %d\n",
			fhandler->fn_number,
			rmi4_data->sensor_max_x,
			rmi4_data->sensor_max_y);

	rmi4_data->num_of_rx = ctrl_8.num_of_rx;
	rmi4_data->num_of_tx = ctrl_8.num_of_tx;
	rmi4_data->max_touch_width = max(rmi4_data->num_of_rx,
			rmi4_data->num_of_tx);

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset;
			ii < ((fd->intr_src_count & MASK_3BIT) +
			intr_offset);
			ii++)
		fhandler->intr_mask |= 1 << ii;

	/* Allocate memory for finger data storage space */
	fhandler->data_size = num_of_fingers * size_of_2d_data;
	fhandler->data = kmalloc(fhandler->data_size, GFP_KERNEL);
	if (fhandler->data == NULL) {
		TS_LOG_ERR("Failed to alloc memory for fhandler->data\n");
		retval = -ENOMEM;
		return retval;
	}

	return retval;
}

static int synaptics_rmi4_f1a_alloc_mem(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler)
{
	int retval;
	struct synaptics_rmi4_f1a_handle *f1a;

	f1a = kzalloc(sizeof(*f1a), GFP_KERNEL);
	if (!f1a) {
		TS_LOG_ERR("Failed to alloc mem for function handle\n");
		return -ENOMEM;
	}

	fhandler->data = (void *)f1a;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			fhandler->full_addr.query_base,
			f1a->button_query.data,
			sizeof(f1a->button_query.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read query registers\n");
		return retval;
	}

	f1a->button_count = f1a->button_query.max_button_count + 1;
	f1a->button_bitmask_size = (f1a->button_count + 7) / 8;

	f1a->button_data_buffer = kcalloc(f1a->button_bitmask_size,
			sizeof(*(f1a->button_data_buffer)), GFP_KERNEL);
	if (!f1a->button_data_buffer) {
		TS_LOG_ERR("Failed to alloc mem for data buffer\n");
		return -ENOMEM;
	}

	f1a->button_map = kcalloc(f1a->button_count,
			sizeof(*(f1a->button_map)), GFP_KERNEL);
	if (!f1a->button_map) {
		TS_LOG_ERR("Failed to alloc mem for button map\n");
		return -ENOMEM;
	}

	return 0;
}

static int synaptics_rmi4_cap_button_map(
				struct synaptics_rmi4_data *rmi4_data,
				struct synaptics_rmi4_fn *fhandler)
{
#if 0
	unsigned char ii;
	struct synaptics_rmi4_f1a_handle *f1a = fhandler->data;
	const struct synaptics_dsx_platform_data *pdata = rmi4_data->board;

	if (!pdata->cap_button_map) {
		TS_LOG_ERR("%s: cap_button_map is" \
				"NULL in board file\n",
				__func__);
		return -ENODEV;
	} else if (!pdata->cap_button_map->map) {
		TS_LOG_ERR("%s: Button map is missing in board file\n",
				__func__);
		return -ENODEV;
	} else {
		if (pdata->cap_button_map->nbuttons !=
			f1a->button_count) {
			f1a->valid_button_count = min(f1a->button_count,
				pdata->cap_button_map->nbuttons);
		} else {
			f1a->valid_button_count = f1a->button_count;
		}

		for (ii = 0; ii < f1a->valid_button_count; ii++)
			f1a->button_map[ii] =
					pdata->cap_button_map->map[ii];
	}

	return 0;
#else
	return 0;
#endif
}

static void synaptics_rmi4_f1a_kfree(struct synaptics_rmi4_fn *fhandler)
{
	struct synaptics_rmi4_f1a_handle *f1a = fhandler->data;

	if (f1a) {
		kfree(f1a->button_data_buffer);
		f1a->button_data_buffer = NULL;
		kfree(f1a->button_map);
		f1a->button_map = NULL;
		kfree(f1a);
		f1a = NULL;
		fhandler->data = NULL;
	}

	return;
}

static int synaptics_rmi4_f1a_init(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler,
		struct synaptics_rmi4_fn_desc *fd,
		unsigned int intr_count)
{
	int retval;
	unsigned char ii;
	unsigned short intr_offset;

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset; ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	retval = synaptics_rmi4_f1a_alloc_mem(rmi4_data, fhandler);
	if (retval < 0)
		goto error_exit;

	retval = synaptics_rmi4_cap_button_map(rmi4_data, fhandler);
	if (retval < 0)
		goto error_exit;

	rmi4_data->button_0d_enabled = 1;

	return 0;

error_exit:
	synaptics_rmi4_f1a_kfree(fhandler);

	return retval;
}

static int synaptics_input_config(struct input_dev *input_dev)
{
	int i=0;
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);

#ifdef HUAWEI_EASY_WAKEUP
	for(i =0;i < GESTURE_MAX ;i++ ){
		set_bit(synaptics_gesture_key_event[i], input_dev->keybit);
	}
#endif

#ifdef INPUT_PROP_DIRECT
	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
#endif

	input_set_abs_params(input_dev, ABS_X,
			     0, rmi4_data->sensor_max_x, 0, 0);
	input_set_abs_params(input_dev, ABS_Y,
			     0, rmi4_data->sensor_max_y, 0, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, 15, 0, 0);

      if (get_lcd_type() == JDI_1902B_LCD) {
		input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, FHD_LCD_WIDTH, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, FHD_LCD_HIGHT, 0, 0);
      	} else {
		input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, LCD_WIDTH, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, LCD_HIGHT, 0, 0);
	}
	
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
#ifdef REPORT_2D_W
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, MAX_ABS_MT_TOUCH_MAJOR, 0, 0);
#endif

#ifdef TYPE_B_PROTOCOL
#ifdef KERNEL_ABOVE_3_7
	/* input_mt_init_slots now has a "flags" parameter */
	input_mt_init_slots(input_dev, rmi4_data->num_of_fingers, INPUT_MT_DIRECT);
#else
	input_mt_init_slots(input_dev, rmi4_data->num_of_fingers);
#endif
#endif

#ifdef RED_REMOTE
	/*used for red remote fucntion*/
	rmi4_data->input_dev = input_dev;
#endif

	return NO_ERR;
}
#ifdef  HUAWEI_EASY_WAKEUP
static int easy_wakeup_gesture_report_locus(struct synaptics_rmi4_data *rmi4_data,
		unsigned int reprot_gesture_point_num,unsigned int reprot_gesture_key_value)
{
	int retval = 0;
	unsigned char f51_custom_data[F51_LOCUS_DATA_NUM] = {0};
	int x = 0;
	int y = 0;
	int i = 0;

	TS_LOG_DEBUG("reprot_gesture_point_num =%0x \n)",reprot_gesture_point_num);
	if (reprot_gesture_point_num != 0)
	{
		retval = synaptics_rmi4_i2c_read(rmi4_data,
				rmi4_data->f51_data_base_addr,
				f51_custom_data,
				(reprot_gesture_point_num*F51_LOCUS_DATA_LENS));
		if (retval < 0)
		{
			TS_LOG_ERR("f51_data_base_addr read error!retval = %d",retval);
			return retval;
		}

		memset(easywake_position,0,sizeof(easywake_position));
	
		for(i = 0;i < reprot_gesture_point_num;i ++)
		{
			/*
			  *F51_CUSTOM_DATA[00]~[23],every 4 bytes save 1 x/y position of the gesture locus;
			  *i.e.Point 1 has 4 bytes from [00] to [03] :
			  * [00] means LSB of x position,[01] means MSB of x position,
			  * [02] means LSB of y position,[03] means MSB of y position,
			  *The most points num is 6,point from 1(lower address) to 6(higher address) means:
			  *1.beginning 2.end 3.top 4.leftmost 5.bottom 6.rightmost
			*/
			x = ((f51_custom_data[F51_LOCUS_DATA_LENS*i + 1] << 8) | (f51_custom_data[F51_LOCUS_DATA_LENS*i + 0]));
			y = ((f51_custom_data[F51_LOCUS_DATA_LENS*i + 3] << 8) | (f51_custom_data[F51_LOCUS_DATA_LENS*i + 2]));			
			x = x * LCD_WIDTH / rmi4_data->sensor_max_x;
			y = y * JISUAN/ rmi4_data->sensor_max_y;
			if( (x > LCD_WIDTH ) ||( x <0)){
				TS_LOG_ERR("x position over the size ,x = %d ",x );
			}
			if( (y > JISUAN) ||( y <0)){
				TS_LOG_ERR("x position over the size ,y = %d ",y );
			}			
			easywake_position[i]=x<<16|y;		
		}		
		
	}

	input_report_key(rmi4_data->input_dev,reprot_gesture_key_value, 1);
	input_sync(rmi4_data->input_dev);
	input_report_key(rmi4_data->input_dev,reprot_gesture_key_value, 0);
	input_sync(rmi4_data->input_dev);
	
	return retval;
}

static int synaptics_rmi4_f11_gesture_report(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler)
{
	int retval;
	unsigned char device_data = 0;
	unsigned char f51_custom_data0 = 0;
	unsigned char f11_2d_data39[8] = {0};
	unsigned int reprot_gesture_key_value = 0;
	unsigned int reprot_gesture_point_num = 0;

	struct ts_easy_wakeup_info *info = &(g_ts_data_synaptics->easy_wakeup_info);
	
	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f11_data_base_addr+F11_2D_DATA38_OFFSET,
			&device_data,
			sizeof(device_data));
	if (retval < 0)
		return 0;

	TS_LOG_DEBUG("f11_data_base_addr = %d,device_data = %d",
							 rmi4_data->f11_data_base_addr,device_data);

	switch(device_data)
	{
		case DOUBLE_CLICK_WAKEUP:
			if(IS_APP_ENABLE_GESTURE(GESTURE_DOUBLE_CLICK)&info->easy_wakeup_gesture)
			{
				TS_LOG_INFO("@@@DOUBLE_CLICK_WAKEUP detected!@@@\n");
				reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_DOUBLE_CLICK];
				
			}
			reprot_gesture_point_num = 0;
			break;
		case LINEAR_SLIDE_DETECTED:
			TS_LOG_INFO("@@@LINEAR_SLIDE_DETECTED detected!@@@ \n");
			retval = synaptics_rmi4_i2c_read(rmi4_data,
					cherry_guesture_pattern_addr,
					&f51_custom_data0,
					sizeof(f51_custom_data0));
			if (retval < 0)
			{
				TS_LOG_ERR("LINEAR_SLIDE_DETECTED error!retval = %d\n",retval);
				return 0;
			}
			switch(f51_custom_data0)
			{
				case LINEAR_SLIDE_LEFT_TO_RIGHT:
					if(IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_L2R)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@LINEAR_SLIDE_LEFT_TO_RIGHT detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_SLIDE_L2R];
						reprot_gesture_point_num = F51_LINEAR_LOCUS_NUM;
					}
					break;
				case LINEAR_SLIDE_RIGHT_TO_LEFT:
					if(IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_R2L)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@LINEAR_SLIDE_RIGHT_TO_LEFT detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_SLIDE_R2L];
						reprot_gesture_point_num = F51_LINEAR_LOCUS_NUM;
					}
					break;
				case LINEAR_SLIDE_TOP_TO_BOTTOM:
					if(IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_T2B)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@LINEAR_SLIDE_TOP_TO_BOTTOM detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_SLIDE_T2B];
						reprot_gesture_point_num = F51_LINEAR_LOCUS_NUM;
					}
					break;
				case LINEAR_SLIDE_BOTTOM_TO_TOP:
					if(IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_B2T)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@LINEAR_SLIDE_BOTTOM_TO_TOP detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_SLIDE_B2T];
						reprot_gesture_point_num = F51_LINEAR_LOCUS_NUM;
					}
					break;
				case LINEAR_SLIDE_TOP_TO_BOTTOM2:
					if(IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_T2B2)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@LINEAR_SLIDE_TOP_TO_BOTTOM2 detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_SLIDE_T2B2];
						reprot_gesture_point_num = F51_LINEAR2_LOCUS_NUM;
					}
					break;
				default:
					TS_LOG_INFO("@@@unknow LINEAR!f51_custom_data0 = %d@@@\n",f51_custom_data0);
					return 0;
			}
			break;
		case CIRCLE_SLIDE_DETECTED:
			if(IS_APP_ENABLE_GESTURE(GESTURE_CIRCLE_SLIDE)&info->easy_wakeup_gesture)
			{
				TS_LOG_INFO("@@@CIRCLE_SLIDE_DETECTED detected!@@@\n");
				reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_CIRCLE_SLIDE];
				reprot_gesture_point_num = F51_LETTER_LOCUS_NUM;		
			}
			break;
		case SPECIFIC_LETTER_DETECTED:
			TS_LOG_INFO("@@@SPECIFIC_LETTER_DETECTED detected!@@@\n");
			retval = synaptics_rmi4_i2c_read(rmi4_data,
					rmi4_data->f11_data_base_addr+F11_2D_DATA39_OFFSET,
					&f11_2d_data39[0],
					sizeof(f11_2d_data39));
			TS_LOG_DEBUG("%s:###read### f11_2d_data39[7] = 0x%x\n",__func__,f11_2d_data39[7]);

			switch(f11_2d_data39[6])
			{
				case SPECIFIC_LETTER_c:
					if(IS_APP_ENABLE_GESTURE(GESTURE_LETTER_c)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@SPECIFIC_LETTER_c detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_LETTER_c];
						reprot_gesture_point_num = F51_LETTER_LOCUS_NUM;	

					}
					break;
				case SPECIFIC_LETTER_e:
					if(IS_APP_ENABLE_GESTURE(GESTURE_LETTER_e)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@SPECIFIC_LETTER_e detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_LETTER_e];
						reprot_gesture_point_num = F51_LETTER_LOCUS_NUM;				
					}
					break;
				case SPECIFIC_LETTER_m:
					if(IS_APP_ENABLE_GESTURE(GESTURE_LETTER_m)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@SPECIFIC_LETTER_m detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_LETTER_m];
						reprot_gesture_point_num = F51_LETTER_LOCUS_NUM;			
					}
					break;
				case SPECIFIC_LETTER_w:
					if(IS_APP_ENABLE_GESTURE(GESTURE_LETTER_w)&info->easy_wakeup_gesture)
					{
						TS_LOG_INFO("@@@SPECIFIC_LETTER_w detected!@@@\n");
						reprot_gesture_key_value = synaptics_gesture_key_event[GESTURE_LETTER_w];
						reprot_gesture_point_num = F51_LETTER_LOCUS_NUM;				
					}
					break;
				default:
					TS_LOG_INFO("@@@unknow letter!f11_2d_data39[6] = %d@@@\n",f11_2d_data39[6]);
					return 0;
			}
			break;
		default:
			TS_LOG_INFO("@@@unknow gesture detected!\n");
			return 0;
	}
	if(0 != reprot_gesture_key_value)
	{			
		/*if(true == first_int_flag) 
		{
			lTimerPre = jiffies;
			lTimerCur = jiffies;
			first_int_flag = false;
			TS_LOG_INFO("Gesture first interrupt!\n");
		}
		TS_LOG_INFO("lTimerCur = %ld,lTimerPre + lTimerNext = %ld",lTimerCur,(lTimerPre + lTimerNext));
		if(time_before(lTimerCur, lTimerPre + lTimerNext)) 
		{
			TS_LOG_INFO("Gesture Timer Interval is less than 1 senond!\n");
			return 0;
		}
		else
		{
			lTimerNext = 2*HZ;
			lTimerPre = jiffies;
			TS_LOG_INFO("lTimerPre + lTimerNext = %ld",(lTimerPre + lTimerNext));
		}*/
		mutex_lock(&wrong_touch_lock);
		if(1==off_motion_on)
		{
			
			off_motion_on=0;
			retval = easy_wakeup_gesture_report_locus(rmi4_data,reprot_gesture_point_num,reprot_gesture_key_value);
			TS_LOG_INFO("Gesture is  reported,reprot_gesture_key_value=%d \n",reprot_gesture_key_value);
			if (retval < 0)
			{
				mutex_unlock(&wrong_touch_lock);
				return 0;
			}
		}
		else
		{
			TS_LOG_INFO("Gesture is  not reported because framwork \n");
		}
		mutex_unlock(&wrong_touch_lock);
	}
	return 0;
}

#endif
static int synaptics_rmi4_palm_sleep_report(struct synaptics_rmi4_data *rmi4_data)
{
	unsigned char palm_status = 0;
	unsigned int reprot_gesture_key_value;
	int retval = 0;

	retval = synaptics_rmi4_i2c_read(rmi4_data, cherry_palm_status_addr, &palm_status, sizeof(palm_status));
	if (retval < 0) {
		TS_LOG_ERR("read plam object_type_and_status fail !\n");
	} else {
		TS_LOG_DEBUG("read plam object_type_and_status OK object_type_and_status = 0x%x  \n",palm_status);
	}

	if (PALM_COVER_SLEEP==(palm_status&0x02)) {
		TS_LOG_INFO("%s:palm gesture detected!\n",__func__);
		reprot_gesture_key_value =  synaptics_gesture_key_event[GESTURE_PALM];
		input_report_key(rmi4_data->input_dev,reprot_gesture_key_value, 1);
		input_sync(rmi4_data->input_dev);
		input_report_key(rmi4_data->input_dev,reprot_gesture_key_value, 0);
		input_sync(rmi4_data->input_dev);
		return PALM_COVER_SLEEP;
	} else {
		TS_LOG_DEBUG("%s:no palm_data!, palm_data read from ic is\n",__func__);
	}
	return PALM_COVER_NOSLEEP;
}
 /**
 * synaptics_rmi4_f11_abs_report()
 *
 * Called by synaptics_rmi4_report_touch() when valid Function $11
 * finger data has been detected.
 *
 * This function reads the Function $11 data registers, determines the
 * status of each finger supported by the Function, processes any
 * necessary coordinate manipulation, reports the finger data to
 * the input subsystem, and returns the number of fingers detected.
 */
static void synaptics_rmi4_f11_abs_report(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler, struct ts_fingers *info)
{
	int retval;
	unsigned char touch_count = 0; /* number of touch points */
	unsigned char reg_index;
	unsigned char finger;
	unsigned char fingers_supported;
	unsigned char num_of_finger_status_regs;
	unsigned char finger_shift;
	unsigned char finger_status;
	unsigned char data_reg_blk_size;
	unsigned char finger_status_reg[3] = {0};
	unsigned char data[F11_STD_DATA_LEN] = {0};
	unsigned short data_addr;
	unsigned short data_offset;
	int x;
	int y;
	int wx;
	int wy;
	int z;
#ifdef HUAWEI_EASY_WAKEUP
	struct ts_easy_wakeup_info *easy_wakeup= &(g_ts_data_synaptics->easy_wakeup_info);
	TS_LOG_DEBUG("in! easy_wakeup_flag =%d",easy_wakeup->easy_wakeup_flag);
	if(true == easy_wakeup->easy_wakeup_flag)
	{
		retval = synaptics_rmi4_f11_gesture_report(rmi4_data,fhandler);
		return;
	}
#endif
	if((true == easy_wakeup->palm_cover_flag)&&(true == easy_wakeup->palm_cover_control))
	{
		retval = synaptics_rmi4_palm_sleep_report(rmi4_data);
		if(PALM_COVER_SLEEP == retval)
		{
			easy_wakeup->palm_cover_control = false;
			return;
		}
	}
	/*
	 * The number of finger status registers is determined by the
	 * maximum number of fingers supported - 2 bits per finger. So
	 * the number of finger status registers to read is:
	 * register_count = ceil(max_num_of_fingers / 4)
	 */
	fingers_supported = fhandler->num_of_data_points;
	num_of_finger_status_regs = (fingers_supported + 3) / 4;
	data_addr = fhandler->full_addr.data_base;
	data_reg_blk_size = fhandler->size_of_data_register_block;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			data_addr,
			finger_status_reg,
			num_of_finger_status_regs);
	if (retval < 0){
		TS_LOG_ERR("Failed to read: %d\n", retval);
		return;
	}
#ifdef GLOVE_SIGNAL
	retval = rmi_f11_read_finger_state(info);
	if (retval < 0) {
	    TS_LOG_ERR("error: finger_state = %d\n", retval);
	    return;
	}
#endif

	for (finger = 0; finger < fingers_supported; finger++) {
		reg_index = finger / 4;
		finger_shift = (finger % 4) * 2;
		finger_status = (finger_status_reg[reg_index] >> finger_shift)
				& MASK_2BIT;

		/*
		 * Each 2-bit finger status field represents the following:
		 * 00 = finger not present
		 * 01 = finger present and data accurate
		 * 10 = finger present but data may be inaccurate
		 * 11 = reserved
		 */
		if (finger_status) {
			data_offset = data_addr + num_of_finger_status_regs + (finger * data_reg_blk_size);
			retval = synaptics_rmi4_i2c_read(rmi4_data,
					data_offset,
					data,
					data_reg_blk_size);
			if (retval < 0){
				TS_LOG_ERR("Failed to read: %d\n", retval);
				return;
			}
			
			x = (data[0] << 4) | (data[2] & MASK_4BIT);
			y = (data[1] << 4) | ((data[2] >> 4) & MASK_4BIT);
			wx = (data[3] & MASK_4BIT);
			wy = (data[3] >> 4) & MASK_4BIT;
			z = data[4];
			
			if (rmi4_data->flip_x)
				x = rmi4_data->sensor_max_x - x;
			if (rmi4_data->flip_y)
				y = rmi4_data->sensor_max_y - y;
			
			x = x * LCD_WIDTH /rmi4_data->sensor_max_x;
			if(!strcmp(g_ts_data.product_name,"g760s"))
			{	
				y = y * LCD_HIGHT/ rmi4_data->sensor_max_y;
			}
			else
			{
				y = y * JISUAN/ rmi4_data->sensor_max_y;
			}
			TS_LOG_DEBUG("Finger %d:\n"
					"status = 0x%02x\n"
					"x = %d\n"
					"y = %d\n"
					"wx = %d\n"
					"wy = %d\n",
					finger,
					finger_status,
					x, y, wx, wy);

			info->fingers[finger].x = x;
			info->fingers[finger].y = y;
			info->fingers[finger].major = wx;
			info->fingers[finger].minor= wy;
			info->fingers[finger].pressure = z;

			touch_count++;
		}
	}
	info->cur_finger_number = touch_count;
	TS_LOG_DEBUG("f11_abs_report, touch_count = %d\n", touch_count);
	return;
}

 /**
 * synaptics_rmi4_f12_abs_report()
 *
 * Called by synaptics_rmi4_report_touch() when valid Function $12
 * finger data has been detected.
 *
 * This function reads the Function $12 data registers, determines the
 * status of each finger supported by the Function, processes any
 * necessary coordinate manipulation, reports the finger data to
 * the input subsystem, and returns the number of fingers detected.
 */
static void synaptics_rmi4_f12_abs_report(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler, struct ts_fingers *info)
{
	int retval;
	unsigned char touch_count = 0; /* number of touch points */
	unsigned char finger;
	unsigned char fingers_to_process;
	unsigned char finger_status;
	unsigned char size_of_2d_data;
	unsigned short data_addr;
	int x = 0;
	int y = 0;
	int wx = 0;
	int wy = 0;
#ifdef USE_F12_DATA_15
	int temp = 0;
#endif
	int z = 1;
	struct synaptics_rmi4_f12_extra_data *extra_data;
	struct synaptics_rmi4_f12_finger_data *data;
	struct synaptics_rmi4_f12_finger_data *finger_data;

	fingers_to_process = fhandler->num_of_data_points;
	data_addr = fhandler->full_addr.data_base;
	extra_data = (struct synaptics_rmi4_f12_extra_data *)fhandler->extra;
	size_of_2d_data = sizeof(struct synaptics_rmi4_f12_finger_data);

#ifdef USE_F12_DATA_15
	/* Determine the total number of fingers to process */
	if (extra_data->data15_size) {
		retval = synaptics_rmi4_i2c_read(rmi4_data,
				data_addr + extra_data->data15_offset,
				extra_data->data15_data,
				extra_data->data15_size);
		if (retval < 0){
			TS_LOG_ERR("Failed to read: %d\n", retval);
			return;
		}

		/* Start checking from the highest bit */
		temp = extra_data->data15_size - 1; /* Highest byte */
		finger = (fingers_to_process - 1) % 8; /* Highest bit */
		do {
			if (extra_data->data15_data[temp] & (1 << finger))
				break;

			if (finger) {
				finger--;
			} else {
				temp--; /* Move to the next lower byte */
				finger = 7;
			}

			fingers_to_process--;
		} while (fingers_to_process);

		TS_LOG_INFO("Number of fingers to process = %d\n", fingers_to_process);
	}

	if (!fingers_to_process) {
		TS_LOG_ERR("fingers to process is 0\n");
		return;
	}
#endif

	retval = synaptics_rmi4_i2c_read(rmi4_data,
			data_addr + extra_data->data1_offset,
			(unsigned char *)fhandler->data,
			fingers_to_process * size_of_2d_data);
	if (retval < 0){
			TS_LOG_ERR("Failed to read: %d\n", retval);
			return;
	}

	data = (struct synaptics_rmi4_f12_finger_data *)fhandler->data;

	TS_LOG_DEBUG("Number of fingers = %d\n", fingers_to_process);

	for (finger = 0; finger < fingers_to_process; finger++) {
		finger_data = data + finger;
		finger_status = finger_data->object_type_and_status;

		/*
		 * Each 2-bit finger status field represents the following:
		 * 00 = finger not present
		 * 01 = finger present and data accurate
		 * 10 = finger present but data may be inaccurate
		 * 11 = reserved
		 */

		if (finger_status) {
			x = (finger_data->x_msb << 8) | (finger_data->x_lsb);
			y = (finger_data->y_msb << 8) | (finger_data->y_lsb);
#ifdef REPORT_2D_W
			wx = finger_data->wx;
			wy = finger_data->wy;
#endif

#ifdef REPORT_2D_Z
			z = finger_data->z;
#endif

			if (!rmi4_data->flip_x)
				x = rmi4_data->sensor_max_x - x;
			if (!rmi4_data->flip_y)
				y = rmi4_data->sensor_max_y - y;

			if (get_lcd_type() == JDI_1902B_LCD) {			
				x = x * FHD_LCD_WIDTH /rmi4_data->sensor_max_x;
				y = y * FHD_LCD_JISUAN / rmi4_data->sensor_max_y;
			} else {
				x = x * LCD_WIDTH /rmi4_data->sensor_max_x;
				y = y * JISUAN / rmi4_data->sensor_max_y;
			}
			

			TS_LOG_DEBUG("Finger %d:\n"
					"status = 0x%02x\n"
					"x = %d\n"
					"y = %d\n"
					"wx = %d\n"
					"wy = %d\n"
					"z = %d\n",
					finger,
					finger_status,
					x, y, wx, wy, z);

			info->fingers[finger].status = finger_status;
			info->fingers[finger].x = x;
			info->fingers[finger].y = y;
			info->fingers[finger].major = wx;
			info->fingers[finger].minor = wy;
			info->fingers[finger].pressure = z;
			touch_count++;
		}
	}
	info->cur_finger_number = touch_count;
	TS_LOG_DEBUG("f12_abs_report, touch_count = %d\n", touch_count);
	return;
}

 /**
 * synaptics_rmi4_report_touch()
 *
 * Called by synaptics_rmi4_sensor_report().
 *
 * This function calls the appropriate finger data reporting function
 * based on the function handler it receives and returns the number of
 * fingers detected.
 */
static void synaptics_rmi4_report_touch(struct synaptics_rmi4_data *rmi4_data,
		struct synaptics_rmi4_fn *fhandler, struct ts_fingers *info)
{
	TS_LOG_DEBUG("Function %02x reporting\n", fhandler->fn_number);

	switch (fhandler->fn_number) {
	case SYNAPTICS_RMI4_F11:
		synaptics_rmi4_f11_abs_report(rmi4_data,
				fhandler, info);
		break;
		
	case SYNAPTICS_RMI4_F12:
		synaptics_rmi4_f12_abs_report(rmi4_data,
				fhandler, info);
		break;

	case SYNAPTICS_RMI4_F1A:
		//synaptics_rmi4_f1a_report(rmi4_data, fhandler);
		break;

	default:
		break;
	}
	return;
}

 /**
 * synaptics_rmi4_sensor_report()
 *
 * Called by synaptics_rmi4_irq().
 *
 * This function determines the interrupt source(s) from the sensor
 * and calls synaptics_rmi4_report_touch() with the appropriate
 * function handler for each function with valid data inputs.
 */
static int synaptics_rmi4_sensor_report(struct synaptics_rmi4_data *rmi4_data, struct ts_fingers *info)
{
	int retval;
	unsigned char intr[MAX_INTR_REGISTERS] = {0};
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;

	rmi = &(rmi4_data->rmi4_mod_info);

	/*
	 * Get interrupt status information from F01 Data1 register to
	 * determine the source(s) that are flagging the interrupt.
	 */
	retval = synaptics_rmi4_i2c_read(rmi4_data,
			rmi4_data->f01_data_base_addr + 1,
			intr,
			rmi4_data->num_of_intr_regs);
	if (retval < 0) {
		TS_LOG_ERR("get interrupts status information failed, retval = %d\n", retval);
		return retval;
	}

	/*
	 * Traverse the function handler list and service the source(s)
	 * of the interrupt accordingly.
	 */
	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry(fhandler, &rmi->support_fn_list, link) {
			if (fhandler->num_of_data_sources) {
				if (fhandler->intr_mask & intr[fhandler->intr_reg_num]) {
					synaptics_rmi4_report_touch(rmi4_data, fhandler, info);
				}
			}
		}
	}
	return NO_ERR;
}

static int synaptics_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	TS_LOG_DEBUG("synaptics irq top half called\n");
	return NO_ERR;
}

static int synaptics_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd)
{
	int retval = NO_ERR;
	struct ts_fingers *info = &out_cmd->cmd_param.pub_params.algo_param.info;

#ifdef RED_REMOTE
	/*This interrupts is used for redremote, not report*/
	if (rmi4_data->fw_debug == true) {
		out_cmd->command = TS_INVAILD_CMD;
		rmidev_sysfs_irq(rmi4_data);
		return NO_ERR;
	}
#endif

	out_cmd->command = TS_INPUT_ALGO;
	out_cmd->cmd_param.pub_params.algo_param.algo_order = rmi4_data->synaptics_chip_data->algo_id;
	TS_LOG_DEBUG("order: %d\n", out_cmd->cmd_param.pub_params.algo_param.algo_order);

	retval = synaptics_rmi4_sensor_report(rmi4_data, info);
	if (retval < 0) {
		TS_LOG_ERR("synaptics_rmi4_sensor_report, error: %d\n", retval);
		return retval;
	}

	return NO_ERR;
}

