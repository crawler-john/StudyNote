#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;//1.声明
char *data[6];//定义一个大小是6的字符串数组
int size = 0;//定义当前的下标，也就是人数

void *task(void *p)
{
	sem_wait(&sem);//3.-1
	data[size] = (char *)p;
	usleep(100000);
	size++;
	sem_post(&sem);//5.+1
}

int main()
{
	data[size++] = "liubie";
	sem_init(&sem,0,1);//2.初始化
	pthread_t id1,id2;
	pthread_create(&id1,0,task,"guanyu");
	pthread_create(&id2,0,task,"zhangfei");
	pthread_join(id1,0);
	pthread_join(id2,0);
	sem_destroy(&sem);//6.释放信号量的资源
	int i;
	for(i=0;i<size;i++)
		printf("%s\n",data[i]);

	return 0;
}

