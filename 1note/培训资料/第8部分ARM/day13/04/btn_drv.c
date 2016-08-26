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

struct work_struct mywork;
struct delayed_work mydwork;
struct workqueue_struct *wq;

//工作和延时工作的处理函数
static void mywork_func(struct work_struct *work)
{
	printk("%s\n",__func__);
}

static void mydwork_func(struct work_struct *work)
{
	printk("%s\n",__func__);
}

//中断处理程序
//irq:中断号
//dev_id:传递给中断处理程序的参数
static irqreturn_t btn_isr(int irq,void *dev_id)
{
	struct btn_res *pdata = (struct btn_res *)dev_id;

	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);

	//登记工作/延时工作
	//schedule_work(&mywork);
	queue_delayed_work(wq,&mydwork, 3*HZ);

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

	//初始化
	INIT_WORK(&mywork, mywork_func);
	INIT_DELAYED_WORK(&mydwork, mydwork_func);

	//创建自己的工作者队列和内核线程
	wq = create_workqueue("daoyi");
	
	return 0;
}

void __exit btn_exit(void)
{
	int i;
	//销毁自己的工作者队列和内核线程
	destroy_workqueue(wq);
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		free_irq(btn_info[i].irq, &btn_info[i]);
	}
}

module_init(btn_init);
module_exit(btn_exit);

