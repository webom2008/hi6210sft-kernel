#ifndef __LM_H__
#define __LM_H__

#include <linux/device.h>
#include <linux/huawei/usb/hisi_susb.h>

struct lm_device {
    struct hiusb_info   *hiusb_info;
    struct device       dev;
    struct resource     resource;
    unsigned int        irq;
    unsigned int        id;
};

struct lm_driver {
    struct device_driver    drv;
    int         (*probe)(struct lm_device *);
    void        (*remove)(struct lm_device *);
    int         (*suspend)(struct lm_device *, pm_message_t);
    int         (*resume)(struct lm_device *);
};

int lm_driver_register(struct lm_driver *drv);
void lm_driver_unregister(struct lm_driver *drv);

int lm_device_register(struct lm_device *dev);

#define lm_get_drvdata(lm)  dev_get_drvdata(&(lm)->dev)
#define lm_set_drvdata(lm, d)   dev_set_drvdata(&(lm)->dev, d)

extern struct lm_device usb_sft_otg;

#endif
