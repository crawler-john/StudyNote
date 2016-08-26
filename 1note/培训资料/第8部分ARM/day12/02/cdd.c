#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL v2");

#define CDD_MAJOR 100
#define CDD_MINOR 0
#define CDD_COUNT 1

static dev_t dev;
u32 cdd_major = 0;
u32 cdd_minor = 0;
struct cdev cdd_cdev;

struct file_operations cdd_fops = 
{
	.owner = THIS_MODULE,
};

int __init cdd_init(void)
{
	int ret = 0;

	//��̬����
	ret = alloc_chrdev_region(&dev, cdd_minor, CDD_COUNT, "cdd_demo");

	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}

	//��ʼ��cdev
	cdev_init(&cdd_cdev, &cdd_fops);
	//���ں�ע��cdev
	ret = cdev_add(&cdd_cdev, dev, CDD_COUNT);
	if(ret<0)
	{
		printk("cdev_add failed!\n");
		goto failure_cdev_add;
	}
	
	return 0;
	
	failure_cdev_add:
		unregister_chrdev_region(dev, CDD_COUNT);
	failure_register_chrdev:
		return ret;
}

void __exit cdd_exit(void)
{
	//ע��cdev
	cdev_del(&cdd_cdev);
	//�ͷ��豸��
	unregister_chrdev_region(dev, CDD_COUNT);
}

module_init(cdd_init);
module_exit(cdd_exit);

