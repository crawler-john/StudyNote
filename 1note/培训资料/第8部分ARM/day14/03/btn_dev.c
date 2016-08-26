#include <linux/init.h>
#include <linux/module.h>

#include <linux/uaccess.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include "gpio_btn.h"

MODULE_LICENSE("GPL v2");

struct resource btn_res[] = 
{
	[0] = {
		.start = IRQ_EINT(16),
		.end = IRQ_EINT(16),
		.flags = IORESOURCE_IRQ
	},
	[1] = {
		.start = IRQ_EINT(17),
		.end = IRQ_EINT(17),
		.flags = IORESOURCE_IRQ
	},
	[2] = {
		.start = IRQ_EINT(18),
		.end = IRQ_EINT(18),
		.flags = IORESOURCE_IRQ
	},
	[3] = {
		.start = IRQ_EINT(19),
		.end = IRQ_EINT(19),
		.flags = IORESOURCE_IRQ
	}
};

struct gpio_btn gpio_btns[] = 
{
	[0] = {
		.gpio = S5PV210_GPH2(0),
		.name = "KEY_1"
	},
	[1] = {
		.gpio = S5PV210_GPH2(1),
		.name = "KEY_2"
	},
	[2] = {
		.gpio = S5PV210_GPH2(2),
		.name = "KEY_3"
	},
	[3] = {
		.gpio = S5PV210_GPH2(3),
		.name = "KEY_4"
	}
};

void btn_release(struct device *dev)
{
	printk("enter btn_release!\n");
}

struct platform_device btn_dev = 
{
	.name = "mybtn",
	.resource = btn_res,
	.num_resources = ARRAY_SIZE(btn_res),
	.dev = 
	{
		.platform_data = gpio_btns,
		.release = btn_release,
	}
};

int __init btn_dev_init(void)
{
	platform_device_register(&btn_dev);
	return 0;
}

void __exit btn_dev_exit(void)
{
	platform_device_unregister(&btn_dev);
}

module_init(btn_dev_init);
module_exit(btn_dev_exit);
