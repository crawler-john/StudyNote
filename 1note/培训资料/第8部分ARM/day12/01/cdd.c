#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>

MODULE_LICENSE("GPL v2");

#define CDD_MAJOR 100
#define CDD_MINOR 0
#define CDD_COUNT 1

static dev_t dev;
u32 cdd_major = 0;
u32 cdd_minor = 0;
int __init cdd_init(void)
{
	int ret = 0;
	if(cdd_major)
	{
		dev = MKDEV(CDD_MAJOR,CDD_MINOR);
		//æ≤Ã¨…Í«Î
		ret = register_chrdev_region(dev, CDD_COUNT, "cdd_demo");
	}
	else
	{
		//∂ØÃ¨…Í«Î
		ret = alloc_chrdev_region(&dev, cdd_minor, CDD_COUNT, "cdd_demo");
	}
	if(ret<0)
	{
		printk("register_chrdev_region failed!\n");
		goto failure_register_chrdev;
	}
	return 0;

	failure_register_chrdev:
		return ret;
}

void __exit cdd_exit(void)
{
	// Õ∑≈…Ë±∏∫≈
	unregister_chrdev_region(dev, CDD_COUNT);
}

module_init(cdd_init);
module_exit(cdd_exit);
