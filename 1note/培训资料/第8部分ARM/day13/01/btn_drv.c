#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/uaccess.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

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


int btn_open(struct inode *inode,struct file *filp)
{
	int ret;

	printk("enter btn_open!\n");
	//����GPIO
	ret = gpio_request(S5PV210_GPH2(0), "KEY_1");
	if(ret<0)
	{
		printk("request GPH2_0 failed!\n");
		return -EBUSY;
	}
	//���ó����빦��
	gpio_direction_input(S5PV210_GPH2(0));
	return 0;
}

ssize_t btn_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	unsigned int pinstat;
	unsigned char key_val;

	// 1.��ȡGPIO��״̬
	pinstat = gpio_get_value(S5PV210_GPH2(0));

	//����״̬��ȡ��Ӧ�ļ�ֵ
	if(pinstat==1)//�ɿ�
	{
		key_val = 0x81;
	}
	else
	{
		key_val = 0x80;
	}
	
	//�ϱ���ֵ
	copy_to_user(buf,&key_val,1);
	
	return 1;
}

ssize_t btn_write(struct file *filp,const char __user *buf,size_t count,loff_t *offset)
{
	printk("enter btn_write!\n");
	return 0;
}

int btn_ioctl(struct inode *inode,struct file *filp,unsigned int cmd,unsigned long data)
{
	printk("enter btn_ioctl!\n");
	return 0;
}

int btn_release(struct inode *inode,struct file *filp)
{
	printk("enter btn_release!\n");
	//�ͷ�GPIO
	gpio_free(S5PV210_GPH2(0));
	return 0;
}

struct file_operations btn_fops = 
{
	.owner = THIS_MODULE,
	.open = btn_open,
	.read = btn_read,
	.write = btn_write,
	.ioctl = btn_ioctl,
	.release = btn_release,
};

int __init btn_init(void)
{
	int ret = 0;

	//��̬����
	ret = alloc_chrdev_region(&dev, btn_minor, BTN_COUNT, "btn_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//��ʼ��cdev
	cdev_init(&btn_cdev, &btn_fops);
	//���ں�ע��cdev
	ret = cdev_add(&btn_cdev, dev, BTN_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}

	/*��̬�����豸�ļ�*/
	// 1.ע���豸��
	//����/sys/classĿ¼�´�����"btn_class"�������ļ���
	dev_class = class_create(THIS_MODULE, "btn_class");
	if(IS_ERR(dev_class))
	{
		ret = PTR_ERR(dev_class);
		goto failure_class_create;
	}
	// 2.ע���豸
	//����/sys/class/btn_class/����һ���ļ���
	//������/dev/����һ���豸�ļ�
	dev_device = device_create(dev_class, NULL, dev, NULL, "btn");
	if(IS_ERR(dev_device))
	{
		ret = PTR_ERR(dev_device);
		goto failure_device_create;
	}
	return 0;

	failure_device_create:
		class_destroy(dev_class);
	failure_class_create:
		cdev_del(&btn_cdev);
	failure_cdev_add:
		unregister_chrdev_region(dev, BTN_COUNT);
	failure_register_chrdev:
		return ret;
}

void __exit btn_exit(void)
{
	//ע���豸
	device_destroy(dev_class, dev);
	//ע���豸��
	class_destroy(dev_class);
	//ע��cdev
	cdev_del(&btn_cdev);
	//�ͷ��豸��
	unregister_chrdev_region(dev, BTN_COUNT);
}

module_init(btn_init);
module_exit(btn_exit);

