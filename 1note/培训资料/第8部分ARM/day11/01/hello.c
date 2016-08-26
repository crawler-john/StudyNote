#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

int __init hello_init(void)
{
	printk("hello everyone!\n");

	return 0;
}

void __exit hello_exit(void)
{
	printk("welcome to dy!\n");
}

module_init(hello_init);
module_exit(hello_exit);

