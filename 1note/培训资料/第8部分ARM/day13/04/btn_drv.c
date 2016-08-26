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

struct work_struct mywork;
struct delayed_work mydwork;
struct workqueue_struct *wq;

//��������ʱ�����Ĵ�����
static void mywork_func(struct work_struct *work)
{
	printk("%s\n",__func__);
}

static void mydwork_func(struct work_struct *work)
{
	printk("%s\n",__func__);
}

//�жϴ������
//irq:�жϺ�
//dev_id:���ݸ��жϴ������Ĳ���
static irqreturn_t btn_isr(int irq,void *dev_id)
{
	struct btn_res *pdata = (struct btn_res *)dev_id;

	printk("%s:irq = %d,name = %s\n",
		__func__,pdata->irq,pdata->name);

	//�Ǽǹ���/��ʱ����
	//schedule_work(&mywork);
	queue_delayed_work(wq,&mydwork, 3*HZ);

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

	//��ʼ��
	INIT_WORK(&mywork, mywork_func);
	INIT_DELAYED_WORK(&mydwork, mydwork_func);

	//�����Լ��Ĺ����߶��к��ں��߳�
	wq = create_workqueue("daoyi");
	
	return 0;
}

void __exit btn_exit(void)
{
	int i;
	//�����Լ��Ĺ����߶��к��ں��߳�
	destroy_workqueue(wq);
	for(i=0;i<ARRAY_SIZE(btn_info);i++)
	{
		free_irq(btn_info[i].irq, &btn_info[i]);
	}
}

module_init(btn_init);
module_exit(btn_exit);

