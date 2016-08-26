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
#include "gpio_btn.h"

MODULE_LICENSE("GPL v2");

#define BTN_MAJOR 100
#define BTN_MINOR 0
#define BTN_COUNT 1

static dev_t dev;
u32 btn_major = 0;
u32 btn_minor = 0;
struct cdev btn_cdev;

struct class *dev_class = NULL;
struct device *dev_device = NULL;

static int ispress;// 1.有按键操作  0，无按键操作
static unsigned char key_val;//键值
static wait_queue_head_t wq;//等待队列头
static struct timer_list btn_timer;//分配定时器

int btn_open(struct inode *inode,struct file *filp)
{
	printk("enter btn_open!\n");
	return 0;
}

ssize_t btn_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	//是否有按键操作，有，上报键值，没有，阻塞
	//printk("GO TO SLEEP.....\n");
	wait_event_interruptible(wq, ispress!=0);
	ispress = 0;
	//printk("WAKE UP!\n");
	//上报键值
	copy_to_user(buf,&key_val,1);
	
	return 1;
}

int btn_release(struct inode *inode,struct file *filp)
{
	printk("enter btn_release!\n");
	return 0;
}

struct file_operations btn_fops = 
{
	.owner = THIS_MODULE,
	.open = btn_open,
	.read = btn_read,
	.release = btn_release,
};

static void btn_timer_func(unsigned long data)
{
	unsigned int pinstat;

	// 1.获取参数传递过来的信息
	struct gpio_btn *pdata = (struct gpio_btn *)data;
	// 2.获取按键的状态
	pinstat = gpio_get_value(pdata->gpio);
	switch(pdata->gpio)
	{
		case S5PV210_GPH2(0):
			if(pinstat==0)//按下
				key_val = 0x51;
			else
				key_val = 0x50;
			break;
		case S5PV210_GPH2(1):
			if(pinstat==0)//按下
				key_val = 0x61;
			else
				key_val = 0x60;
			break;
		case S5PV210_GPH2(2):
			if(pinstat==0)//按下
				key_val = 0x71;
			else
				key_val = 0x70;
			break;
		case S5PV210_GPH2(3):
			if(pinstat==0)//按下
				key_val = 0x81;
			else
				key_val = 0x80;
			break;
		default:
			printk("gpio num error!\n");
			return;
	}
	//唤醒等待队列
	ispress = 1;
	wake_up_interruptible(&wq);
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
	struct gpio_btn *btn = pdev->dev.platform_data;
	struct resource *res = pdev->resource;

	//动态申请
	ret = alloc_chrdev_region(&dev, btn_minor, BTN_COUNT, "btn_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//初始化cdev
	cdev_init(&btn_cdev, &btn_fops);
	//向内核注册cdev
	ret = cdev_add(&btn_cdev, dev, BTN_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}

	/*动态创建设备文件*/
	// 1.注册设备类
	//会在/sys/class目录下创建以"btn_class"命名的文件夹
	dev_class = class_create(THIS_MODULE, "btn_class");
	if(IS_ERR(dev_class))
	{
		ret = PTR_ERR(dev_class);
		goto failure_class_create;
	}
	// 2.注册设备
	//会在/sys/class/btn_class/创建一个文件夹
	//还会在/dev/创建一个设备文件
	dev_device = device_create(dev_class, NULL, dev, NULL, "btn");
	if(IS_ERR(dev_device))
	{
		ret = PTR_ERR(dev_device);
		goto failure_device_create;
	}

	//初始化等待队列头
	init_waitqueue_head(&wq);

	//申请中断和GPIO
	for(i=0;i<pdev->num_resources;i++)
	{
		gpio_request(btn[i].gpio, btn[i].name);
		request_irq(res[i].start, btn_isr, 
			IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, 
			btn[i].name, &btn[i]);
	}

	//初始化定时器
	init_timer(&btn_timer);
	btn_timer.function = btn_timer_func;
	return 0;

	failure_device_create:
		class_destroy(dev_class);
	failure_class_create:
		cdev_del(&btn_cdev);
	failure_cdev_add:
		unregister_chrdev_region(dev, BTN_COUNT);
	failure_register_chrdev:
		return ret;
	return 0;
}

int btn_remove(struct platform_device *pdev)
{
	int i;
	struct gpio_btn *btn = pdev->dev.platform_data;
	struct resource *res = pdev->resource;
	//释放中断和GPIO
	for(i=0;i<pdev->num_resources;i++)
	{
		free_irq(res[i].start, &btn[i]);
		gpio_free(btn[i].gpio);
	}
	//注销设备
	device_destroy(dev_class, dev);
	//注销设备类
	class_destroy(dev_class);
	//注销cdev
	cdev_del(&btn_cdev);
	//释放设备号
	unregister_chrdev_region(dev, BTN_COUNT);
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

