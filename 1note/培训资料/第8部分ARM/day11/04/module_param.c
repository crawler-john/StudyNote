#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

short mpshort = 1;
int mpint = 10;
char * mpstring = "hello";
int mparr[2] = {100,200};

/*Ä£¿é²ÎÊý*/
module_param(mpshort, short, S_IRUSR);
module_param(mpint,int,S_IRWXU);
module_param(mpstring, charp, 0);
module_param_array(mparr, int, NULL, 00644);

int __init modparam_init(void)
{
	printk("mpshort = %d\n",mpshort);
	printk("mpint = %d\n",mpint);
	printk("mpstring = %s\n",mpstring);
	printk("mparr = %d %d\n",mparr[0],mparr[1]);

	return 0;
}

void __exit modparam_exit(void)
{
	printk("mpshort = %d\n",mpshort);
	printk("mpint = %d\n",mpint);
	printk("mpstring = %s\n",mpstring);
	printk("mparr = %d %d\n",mparr[0],mparr[1]);
}

module_init(modparam_init);
module_exit(modparam_exit);
