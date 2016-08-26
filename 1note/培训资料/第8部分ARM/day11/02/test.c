#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

int test_mul(int x,int y)
{
	printk("enter test_mul!\n");

	return x*y;
}

int test_div(int x,int y)
{
	printk("enter test_div!\n");

	return x/y;
}


/*ÄÚºËµ¼³ö·ûºÅ*/
EXPORT_SYMBOL(test_mul);
EXPORT_SYMBOL(test_div);
	