#include <linux/init.h>
#include <linux/module.h>

#include <linux/irq.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL v2");

struct btn_res{
	int irq;//�жϺ�
	char *name;//�ж���
};

//��ʼ���ж�Դ
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

//tasklet�Ĵ�����
static void btn_tasklet_func(unsigned long data)
{
	struct btn_res *pdata = (struct btn_res *)data;
	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);
}

//�����ʼ��tasklet
static DECLARE_TASKLET(btn_tasklet, btn_tasklet_func, (unsigned long)&btn_info[0]);
//�жϴ������
//irq:�жϺ�
//dev_id:���ݸ��жϴ������Ĳ���
static irqreturn_t btn_isr(int irq,void *dev_id)
{
	struct btn_res *pdata = (struct btn_res *)dev_id;

	//�Ǽǵװ벿
	tasklet_schedule(&btn_tasklet);
	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);

	return IRQ_HANDLED;//�ɹ���ʧ��:IRQ_NONE
}

int __init btn_init(void)
{
	//�����ж�
	/*
	  *irq:�жϺ�
	  *handler:�жϴ�����򣬷����жϺ��ں˵��ô˺���
	  *flags:�ⲿ�жϵĴ�����ʽ���ڲ��жϴ˲�������Ϊ0
	  *name:�ж���
	  *dev_id:���ݸ��жϴ������Ĳ���,�����ݸ�NULL
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

