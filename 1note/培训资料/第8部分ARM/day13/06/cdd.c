#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("GPL v2");

#define CDD_MAJOR 100
#define CDD_MINOR 0
#define CDD_COUNT 1

static dev_t dev;
u32 cdd_major = 0;
u32 cdd_minor = 0;
struct cdev cdd_cdev;

struct class *dev_class = NULL;
struct device *dev_device = NULL;
//分配一个整型原子变量
static atomic_t v;

int cdd_open(struct inode *inode,struct file *filp)
{
	if(!atomic_dec_and_test(&v))
	{
		printk("cdd can be only open once!\n");
		atomic_inc(&v);
		return -EBUSY;
	}

	printk("open successed!\n");
	return 0;
}

ssize_t cdd_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	printk("enter cdd_read!\n");
	return 0;
}

ssize_t cdd_write(struct file *filp,const char __user *buf,size_t count,loff_t *offset)
{
	printk("enter cdd_write!\n");
	return 0;
}

int cdd_ioctl(struct inode *inode,struct file *filp,unsigned int cmd,unsigned long data)
{
	printk("enter cdd_ioctl!\n");
	return 0;
}

int cdd_release(struct inode *inode,struct file *filp)
{
	printk("enter cdd_release!\n");
	atomic_inc(&v);
	return 0;
}

struct file_operations cdd_fops = 
{
	.owner = THIS_MODULE,
	.open = cdd_open,
	.read = cdd_read,
	.write = cdd_write,
	.ioctl = cdd_ioctl,
	.release = cdd_release,
};

int __init cdd_init(void)
{
	int ret = 0;

	//动态申请
	ret = alloc_chrdev_region(&dev, cdd_minor, CDD_COUNT, "cdd_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//初始化cdev
	cdev_init(&cdd_cdev, &cdd_fops);
	//向内核注册cdev
	ret = cdev_add(&cdd_cdev, dev, CDD_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}

	/*动态创建设备文件*/
	// 1.注册设备类
	//会在/sys/class目录下创建以"cdd_class"命名的文件夹
	dev_class = class_create(THIS_MODULE, "cdd_class");
	if(IS_ERR(dev_class))
	{
		ret = PTR_ERR(dev_class);
		goto failure_class_create;
	}
	// 2.注册设备
	//会在/sys/class/cdd_class/创建一个文件夹
	//还会在/dev/创建一个设备文件
	dev_device = device_create(dev_class, NULL, dev, NULL, "cdd");
	if(IS_ERR(dev_device))
	{
		ret = PTR_ERR(dev_device);
		goto failure_device_create;
	}

	//初始阿虎整型原子变量
	atomic_set(&v, 1);
	return 0;

	failure_device_create:
		class_destroy(dev_class);
	failure_class_create:
		cdev_del(&cdd_cdev);
	failure_cdev_add:
		unregister_chrdev_region(dev, CDD_COUNT);
	failure_register_chrdev:
		return ret;
}

void __exit cdd_exit(void)
{
	//注销设备
	device_destroy(dev_class, dev);
	//注销设备类
	class_destroy(dev_class);
	//注销cdev
	cdev_del(&cdd_cdev);
	//释放设备号
	unregister_chrdev_region(dev, CDD_COUNT);
}

module_init(cdd_init);
module_exit(cdd_exit);

