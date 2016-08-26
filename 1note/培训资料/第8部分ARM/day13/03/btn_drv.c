#include <linux/init.h>
#include <linux/module.h>

#include <linux/irq.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL v2");

struct btn_res{
	int irq;//中断号
	char *name;//中断名
};

//初始化中断源
static struct btn_res btn_info[] = 
{
	[0] = {
		.irq = IRQ_EINT(16),
		.name = "KEY_1"
	},
	[1] = {
		.irq = IRQ_EINT(17),
		.name = "KEY_2"
	}
};

//tasklet的处理函数
static void btn_tasklet_func(unsigned long data)
{
	struct btn_res *pdata = (struct btn_res *)data;
	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);
}

//分配初始化tasklet
static DECLARE_TASKLET(btn_tasklet, btn_tasklet_func, (unsigned long)&btn_info[0]);
//中断处理程序
//irq:中断号
//dev_id:传递给中断处理程序的参数
static irqreturn_t btn_isr(int irq,void *dev_id)
{
	struct btn_res *pdata = (struct btn_res *)dev_id;

	//登记底半部
	tasklet_schedule(&btn_tasklet);
	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);

	return IRQ_HANDLED;//成功，失败:IRQ_NONE
}

int __init btn_init(void)
{
	//申请中断
	/*
	  *irq:中断号
	  *handler:中断处理程序，发生中断后，内核调用此函数
	  *flags:外部中断的触发方式，内部中断此参数设置为0
	  *name:中断名
	  *dev_id:传递给中断处理程序的参数,不传递给NULL
	*/
	int i;
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		request_irq(btn_info[i].irq, btn_isr, 
			IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, 
			btn_info[i].name, &btn_info[i]);
	}

	return 0;
}

void __exit btn_exit(void)
{
	int i;
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		free_irq(btn_info[i].irq, &btn_info[i]);
	}
}

module_init(btn_init);
module_exit(btn_exit);

