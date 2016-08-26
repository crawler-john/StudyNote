#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

MODULE_LICENSE("GPL v2");

#define LED_MAJOR 100
#define LED_MINOR 0
#define LED_COUNT 1

#define LED_ON 0x100001
#define LED_OFF 0x100002

static dev_t dev;
u32 led_major = 0;
u32 led_minor = 0;
struct cdev led_cdev;

struct class *dev_class = NULL;
struct device *dev_device = NULL;

unsigned long led_gpio_table[2] = 
{
	S5PV210_GPJ2(0),
	S5PV210_GPJ2(1)
};

int led_open(struct inode *inode,struct file *filp)
{
	gpio_direction_output(led_gpio_table[0], 1);
	gpio_direction_output(led_gpio_table[1], 1);
	s3c_gpio_setpull(led_gpio_table[0], S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(led_gpio_table[1], S3C_GPIO_PULL_NONE);
	return 0;
}

ssize_t led_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	printk("enter led_read!\n");
	return 0;
}

ssize_t led_write(struct file *filp,const char __user *buf,size_t count,loff_t *offset)
{
	printk("enter led_write!\n");
	return 0;
}

int led_ioctl(struct inode *inode,struct file *filp,unsigned int cmd,unsigned long data)
{
	switch(cmd)
	{
		case LED_ON:
			gpio_set_value(led_gpio_table[data],0);
			break;
		case LED_OFF:
			gpio_set_value(led_gpio_table[data],1);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

int led_release(struct inode *inode,struct file *filp)
{
	printk("enter led_release!\n");
	return 0;
}

struct file_operations led_fops = 
{
	.owner = THIS_MODULE,
	.open = led_open,
	.read = led_read,
	.write = led_write,
	.ioctl = led_ioctl,
	.release = led_release,
};

int __init led_init(void)
{
	int ret = 0;

	//动态申请
	ret = alloc_chrdev_region(&dev, led_minor, LED_COUNT, "led_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//初始化cdev
	cdev_init(&led_cdev, &led_fops);
	//向内核注册cdev
	ret = cdev_add(&led_cdev, dev, LED_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}

	/*动态创建设备文件*/
	// 1.注册设备类
	//会在/sys/class目录下创建以"led_class"命名的文件夹
	dev_class = class_create(THIS_MODULE, "led_class");
	if(IS_ERR(dev_class))
	{
		ret = PTR_ERR(dev_class);
		goto failure_class_create;
	}
	// 2.注册设备
	//会在/sys/class/led_class/创建一个文件夹
	//还会在/dev/创建一个设备文件
	dev_device = device_create(dev_class, NULL, dev, NULL, "led");
	if(IS_ERR(dev_device))
	{
		ret = PTR_ERR(dev_device);
		goto failure_device_create;
	}

	gpio_request(led_gpio_table[0], "GPJ2_0");
	gpio_request(led_gpio_table[1], "GPJ2_1");
	return 0;

	failure_device_create:
		class_destroy(dev_class);
	failure_class_create:
		cdev_del(&led_cdev);
	failure_cdev_add:
		unregister_chrdev_region(dev, LED_COUNT);
	failure_register_chrdev:
		return ret;
}

void __exit led_exit(void)
{
	gpio_free(led_gpio_table[0]);
	gpio_free(led_gpio_table[1]);
	//注销设备
	device_destroy(dev_class, dev);
	//注销设备类
	class_destroy(dev_class);
	//注销cdev
	cdev_del(&led_cdev);
	//释放设备号
	unregister_chrdev_region(dev, LED_COUNT);
}

module_init(led_init);
module_exit(led_exit);

