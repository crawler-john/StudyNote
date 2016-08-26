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

static int ispress;// 1.�а�������  0���ް�������
static unsigned char key_val;//��ֵ
static wait_queue_head_t wq;//�ȴ�����ͷ

struct btn_res{
	int irq;
	int gpio;
	char *name;
};

static struct btn_res btn_info[] = {
	[0] = {
		.irq = IRQ_EINT(16),
		.gpio = S5PV210_GPH2(0),
		.name = "KEY_1"
	},
	[1] = {
		.irq = IRQ_EINT(17),
		.gpio = S5PV210_GPH2(1),
		.name = "KEY_2"
	},
	[2] = {
		.irq = IRQ_EINT(18),
		.gpio = S5PV210_GPH2(2),
		.name = "KEY_3"
	},
	[3] = {
		.irq = IRQ_EINT(19),
		.gpio = S5PV210_GPH2(3),
		.name = "KEY_4"
	}
	
};


int btn_open(struct inode *inode,struct file *filp)
{
	printk("enter btn_open!\n");
	return 0;
}

ssize_t btn_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	//�Ƿ��а����������У��ϱ���ֵ��û�У�����
	printk("GO TO SLEEP.....\n");
	wait_event_interruptible(wq, ispress!=0);
	ispress = 0;
	printk("WAKE UP!\n");
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

static irqreturn_t btn_isr(int irq,void *dev_id)
{
	unsigned int pinstat;

	// 1.��ȡ�������ݹ�������Ϣ
	struct btn_res *pdata = (struct btn_res *)dev_id;
	// 2.��ȡ������״̬
	pinstat = gpio_get_value(pdata->gpio);
	switch(pdata->irq)
	{
		case IRQ_EINT(16):
			if(pinstat==0)//����
				key_val = 0x51;
			else
				key_val = 0x50;
			break;
		case IRQ_EINT(17):
			if(pinstat==0)//����
				key_val = 0x61;
			else
				key_val = 0x60;
			break;
		case IRQ_EINT(18):
			if(pinstat==0)//����
				key_val = 0x71;
			else
				key_val = 0x70;
			break;
		case IRQ_EINT(19):
			if(pinstat==0)//����
				key_val = 0x81;
			else
				key_val = 0x80;
			break;
		default:
			printk("irq num error!\n");
			return IRQ_NONE;
	}
	//���ѵȴ�����
	ispress = 1;
	wake_up_interruptible(&wq);

	return IRQ_HANDLED;
}

int __init btn_init(void)
{
	int ret = 0,i;

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

	//��ʼ���ȴ�����ͷ
	init_waitqueue_head(&wq);

	//�����жϺ�GPIO
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		gpio_request(btn_info[i].gpio, btn_info[i].name);
		request_irq(btn_info[i].irq, btn_isr, 
			IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, 
			btn_info[i].name, &btn_info[i]);
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
	int i;
	//�ͷ��жϺ�GPIO
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		free_irq(btn_info[i].irq, &btn_info[i]);
		gpio_free(btn_info[i].gpio);
	}
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

