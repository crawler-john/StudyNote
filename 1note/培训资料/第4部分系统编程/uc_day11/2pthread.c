#include <stdio.h>
#include <pthread.h>

void *task(void *p)
{
	int *pi = (int *)p;
	printf("pi = %d\n",*pi);
	*pi = 200;
}
//传入圆的半径，在线程中打印圆的面积

void *task2(void *p)
{
	double r = *(double *)p;
	printf("%g\n",3.14*r*r);
}

int main()
{
	pthread_t id;
	int x = 100;
	//创建线程
	pthread_create(&id,0,task,&x);
	//等待线程结束
	pthread_join(id,0);
	printf("x = %d\n",x);

	double d = 1.0;
	pthread_create(&id,0,task2,&d);
	pthread_join(id,0);
	return 0;
}
