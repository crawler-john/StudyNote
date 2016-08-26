#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

extern int test_mul(int x, int y);
extern int test_div(int x, int y);

int __init test_import_init(void)
{
	int result = 0;
	printk("enter test_import_init!\n");
	result = test_mul(2, 3);
	printk("the result is %d\n",result);

	return 0;
}

void __exit test_import_exit(void)
{
	int result = 0;
	printk("enter test_import_exit!\n");
	result = test_div(15, 3);
	printk("the result is %d\n",result);	
}

module_init(test_import_init);
module_exit(test_import_exit);
