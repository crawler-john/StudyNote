#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/uaccess.h>
#include <linux/io.h>

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
static void *gpj2base;
static unsigned int *gpj2con,*gpj2dat,*gpj2pud;

struct class *dev_class = NULL;
struct device *dev_device = NULL;


int led_open(struct inode *inode,struct file *filp)
{
	printk("enter led_open!\n");
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
			*gpj2dat = 0;
			break;
		case LED_OFF:
			*gpj2dat = 0xf;
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

	//��̬����
	ret = alloc_chrdev_region(&dev, led_minor, LED_COUNT, "led_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//��ʼ��cdev
	cdev_init(&led_cdev, &led_fops);
	//���ں�ע��cdev
	ret = cdev_add(&led_cdev, dev, LED_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}

	/*��̬�����豸�ļ�*/
	// 1.ע���豸��
	//����/sys/classĿ¼�´�����"led_class"�������ļ���
	dev_class = class_create(THIS_MODULE, "led_class");
	if(IS_ERR(dev_class))
	{
		ret = PTR_ERR(dev_class);
		goto failure_class_create;
	}
	// 2.ע���豸
	//����/sys/class/led_class/����һ���ļ���
	//������/dev/����һ���豸�ļ�
	dev_device = device_create(dev_class, NULL, dev, NULL, "led");
	if(IS_ERR(dev_device))
	{
		ret = PTR_ERR(dev_device);
		goto failure_device_create;
	}

	//��ַӳ��
	gpj2base = ioremap(0xe0200280, 12);
	gpj2con = (unsigned int *)gpj2base;
	gpj2dat = (unsigned int *)(gpj2base+0x4);
	gpj2pud = (unsigned int *)(gpj2base+0x8);

	//����Ϊ������ܣ���ֹ�������������1
	*gpj2con = 0x1111;
	*gpj2pud = 0;
	*gpj2dat = 0xf;
		
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
	//���1
	*gpj2dat = 0xf;
	//���ӳ��
	iounmap(gpj2base);
	//ע���豸
	device_destroy(dev_class, dev);
	//ע���豸��
	class_destroy(dev_class);
	//ע��cdev
	cdev_del(&led_cdev);
	//�ͷ��豸��
	unregister_chrdev_region(dev, LED_COUNT);
}

module_init(led_init);
module_exit(led_exit);

