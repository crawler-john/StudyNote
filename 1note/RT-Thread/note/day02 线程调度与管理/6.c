/*
* 程序清单：挂起线程
*
RT-Thread 1.2.0 23
2.7节 线程相关接口 RT-Thread编程指南
* 这个例子中将创建两个动态线程(t1和t2)
* 低优先级线程t1在启动后将一直持续运行；
* 高优先级线程t2在一定时刻后唤醒并挂起低优先级线程。
*/
#include <rtthread.h>
#include "tc_comm.h"
/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* 线程1入口 */
static void thread1_entry(void* parameter)
{
	rt_uint32_t count = 0;
	while (1)
	{
		/* 线程1采用低优先级运行，一直打印计数值 */
		rt_kprintf("thread count: %d\n", count ++);
	}
}
/* 线程2入口 */
static void thread2_entry(void* parameter)
{
	/* 延时10个OS Tick */
	rt_thread_delay(10);
	/* 挂起线程1 */
	rt_thread_suspend(tid1);
	/* 延时10个OS Tick */
	rt_thread_delay(10);
	/* 线程2自动退出 */
}
int rt_application_init(void)
{
	/* 创建线程1 */
	tid1 = rt_thread_create("t1",
				thread1_entry, /* 线程入口是thread1_entry */
				RT_NULL, /* 入口参数是RT_NULL */
				THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);
	/* 创建线程2 */
	tid2 = rt_thread_create("t2",
				thread2_entry, /* 线程入口是thread2_entry */
				RT_NULL, /* 入口参数是RT_NULL */
				THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
	if (tid2 != RT_NULL)
		rt_thread_startup(tid2);
	return 0;
}