#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *task(void *p)//传值
{
	int y = (int)p;
	printf("y = %d\n",y);
}
//传入圆的半径，在线程中打印圆的面积

void *task2(void *p)
{
	int *pi = p;
	printf("%d\n",*pi);
}

int main()
{
	pthread_t id;
	int x = 100;
	//创建线程
	pthread_create(&id,0,task,(void *)x);
	//等待线程结束
	pthread_join(id,0);

	int *p1 = malloc(4);
	*p1 = 200;
	pthread_create(&id,0,task2,p1);
	free(p1);//回收虚拟地址,不一定解除映射
	pthread_join(id,0);
	return 0;
}

