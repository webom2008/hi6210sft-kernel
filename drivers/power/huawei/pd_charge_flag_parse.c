#include <linux/init.h>
//#include <linux/platform_device.h>
//#include <linux/io.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/kernel.h>
//#include <asm/setup.h>
//#include <mach/system.h>
//#include <mach/platform.h>
//#include <mach/irqs.h>
//#include <mach/io.h>
//#include <mach/boardid.h>
//#include <mach/gpio.h>

#define HEX_STRING_MAX    (10)
#define TRANSFER_BASE     (16)
#define HWLOG_TAG pd_charge
HWLOG_REGIST();

int pd_charge_flag;
/**
 * parse powerdown charge cmdline which is passed from fastoot. *
 * Format : pd_charge=0 or 1             *
 */
static int __init early_parse_pdcharge_cmdline(char * p)
{
	char pd_charge[HEX_STRING_MAX + 1];
	char *endptr = NULL;

	memset(pd_charge, 0, HEX_STRING_MAX + 1);

	memcpy(pd_charge, p, HEX_STRING_MAX);
	pd_charge[HEX_STRING_MAX] = '\0';

	pd_charge_flag = simple_strtoull(pd_charge, &endptr, TRANSFER_BASE);

	hwlog_info("power down charge p:%s, pd_charge_flag :%d\n", p, pd_charge_flag);

	return 0;
}
early_param("pd_charge", early_parse_pdcharge_cmdline);


unsigned int get_pd_charge_flag(void)
{
	return pd_charge_flag;
}
EXPORT_SYMBOL(get_pd_charge_flag);



