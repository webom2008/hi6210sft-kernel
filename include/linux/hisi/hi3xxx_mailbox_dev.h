/* hi3xxx_mailbox_dev.h */

#ifndef __HI3XXX_MAILBOX_DEV_H__
#define __HI3XXX_MAILBOX_DEV_H__

#if defined(CONFIG_ARCH_HI3630)

#define HISI_MAILBOX_RP_GIC1		"HI3630_GIC_1"
#define HISI_MAILBOX_RP_GIC2		"HI3630_GIC_2"
#define HISI_MAILBOX_RP_IOM3		"HI3630_IOM3"
#define HISI_MAILBOX_RP_LPM3		"HI3630_LPM3"
#define HISI_MAILBOX_RP_LPM3_SYNC	"HI3630_LPM3_SYNC"
#define HISI_MAILBOX_RP_LPM3_ASYNC	HISI_MAILBOX_RP_LPM3
#define HISI_MAILBOX_RP_LPM3_FOR_RDR	"HI3630_LPM3_FOR_RDR"
#define HISI_MAILBOX_RP_HIFI		"HI3630_HIFI"
#define HISI_MAILBOX_RP_MCPU		"HI3630_MCPU"
#define HISI_MAILBOX_RP_BBE16		"HI3630_BBE16"
#define HISI_MAILBOX_RP_UNCERTAIN	"HI3630_UNCERTAIN"

#elif (defined(CONFIG_HISI_3635_FPGA) || defined(CONFIG_HISI_3635) || defined(CONFIG_HISI_3635_EMULATOR))

#define HISI_MAILBOX_RP_GIC1		"HI3635_GIC_1"
#define HISI_MAILBOX_RP_GIC2		"HI3635_GIC_2"
#define HISI_MAILBOX_RP_IOM3		"HI3635_IOM3"
#define HISI_MAILBOX_RP_LPM3		"HI3635_LPM3"
#define HISI_MAILBOX_RP_LPM3_SYNC	"HI3635_LPM3_SYNC"
#define HISI_MAILBOX_RP_LPM3_ASYNC	HISI_MAILBOX_RP_LPM3
#define HISI_MAILBOX_RP_LPM3_FOR_RDR	"HI3635_LPM3_FOR_RDR"
#define HISI_MAILBOX_RP_HIFI		"HI3635_HIFI"
#define HISI_MAILBOX_RP_MCPU		"HI3635_MCPU"
#define HISI_MAILBOX_RP_BBE16		"HI3635_BBE16"
#define HISI_MAILBOX_RP_UNCERTAIN	"HI3635_UNCERTAIN"

#elif (defined(CONFIG_HISI_3650_FPGA) || defined(CONFIG_HISI_3650))

#define HISI_MAILBOX_RP_GIC1		"HI3650_GIC_1"
#define HISI_MAILBOX_RP_GIC2		"HI3650_GIC_2"
#define HISI_MAILBOX_RP_IOM3		"HI3650_IOM3"
#define HISI_MAILBOX_RP_LPM3		"HI3650_LPM3"
#define HISI_MAILBOX_RP_LPM3_SYNC	"HI3650_LPM3_SYNC"
#define HISI_MAILBOX_RP_LPM3_ASYNC	HISI_MAILBOX_RP_LPM3
#define HISI_MAILBOX_RP_LPM3_FOR_RDR	"HI3650_LPM3_FOR_RDR"
#define HISI_MAILBOX_RP_HIFI		"HI3650_HIFI"
#define HISI_MAILBOX_RP_MCPU		"HI3650_MCPU"
#define HISI_MAILBOX_RP_BBE16		"HI3650_BBE16"
#define HISI_MAILBOX_RP_UNCERTAIN	"HI3650_UNCERTAIN"

#endif

#endif
