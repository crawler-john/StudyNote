#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

int __init printk_init(void)
{
	printk("<0>""welcome to dy 0!\n");
	printk("<1>""welcome to dy 1!\n");
	printk("<2>""welcome to dy 2!\n");
	printk("<3>""welcome to dy 3!\n");
	printk("<4>""welcome to dy 4!\n");
	printk("<5>""welcome to dy 5!\n");
	printk("<6>""welcome to dy 6!\n");
	printk("<7>""welcome to dy 7!\n");
	printk("welcome to dy!\n");
	
	return 0;
}

void __exit printk_exit(void)
{
	printk("<0>""welcome to dy 0!\n");
	printk("<1>""welcome to dy 1!\n");
	printk("<2>""welcome to dy 2!\n");
	printk("<3>""welcome to dy 3!\n");
	printk("<4>""welcome to dy 4!\n");
	printk("<5>""welcome to dy 5!\n");
	printk("<6>""welcome to dy 6!\n");
	printk("<7>""welcome to dy 7!\n");
	printk("welcome to dy!\n");
}

module_init(printk_init);
module_exit(printk_exit);
