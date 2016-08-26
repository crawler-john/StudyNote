#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/uaccess.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include "gpio_btn.h"

MODULE_LICENSE("GPL v2");


static struct timer_list btn_timer;//分配定时器
static struct input_dev *btn_dev;

static void btn_timer_func(unsigned long data)
{
	unsigned int pinstat;

	// 1.获取参数传递过来的信息
	struct gpio_btn *pdata = (struct gpio_btn *)data;
	// 2.获取按键的状态
	pinstat = gpio_get_value(pdata->gpio);
	if(pinstat)
	{
		//释放
		input_event(btn_dev,EV_KEY,pdata->code,0);
		input_event(btn_dev,EV_SYN,0,0);
	}
	else
	{
		//按下
		input_event(btn_dev,EV_KEY,pdata->code,1);
		input_sync(btn_dev);
	}
}

static irqreturn_t btn_isr(int irq,void *dev_id)
{
	btn_timer.data = (unsigned long)dev_id;
	//启动定时器
	mod_timer(&btn_timer, jiffies+HZ/100);

	return IRQ_HANDLED;
}


int btn_probe(struct platform_device *pdev)
{
	int ret = 0,i;
	struct resource *res = NULL;
	struct gpio_btn *data = pdev->dev.platform_data;

	btn_dev = input_allocate_device();

	//设置上报哪些事件,按键事件和同步事件
	set_bit(EV_KEY, btn_dev->evbit);
	set_bit(EV_SYN, btn_dev->evbit);

	for(i=0;i<pdev->num_resources;i++)
	{
		//设置上报的键值
		set_bit(data[i].code,btn_dev->keybit);
		//注册中断
		res = platform_get_resource(pdev, IORESOURCE_IRQ, i);
		ret = request_irq(res->start, btn_isr,
			IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
			data[i].name, &data[i]);
	}

	//向内核注册input_dev
	ret = input_register_device(btn_dev);

	//初始化定时器
	init_timer(&btn_timer);
	btn_timer.function = btn_timer_func;

	
	return 0;
}

int btn_remove(struct platform_device *pdev)
{
	int i;
	struct resource *res = NULL;
	struct gpio_btn *data = pdev->dev.platform_data;

	del_timer(&btn_timer);
	input_unregister_device(btn_dev);

	for(i=0;i<pdev->num_resources;i++)
	{
		res = platform_get_resource(pdev, IORESOURCE_IRQ, i);
		free_irq(res->start, &data[i]);
	}

	input_free_device(btn_dev);
	
	return 0;
}

struct platform_driver btn_drv = 
{
	.probe = btn_probe,
	.remove = btn_remove,
	.driver = 
	{
		.name = "mybtn",
	}
};

int __init btn_drv_init(void)
{
	platform_driver_register(&btn_drv);
	return 0;
}

void __exit btn_drv_exit(void)
{
	platform_driver_unregister(&btn_drv);
}

module_init(btn_drv_init);
module_exit(btn_drv_exit);

