#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

sem_t sem;

void *task(void *p)
{
	int i = (int)p;
	printf("第%d号线程申请资源!\n",i);
	sem_wait(&sem);//-1
	printf("第%d号线程申请资源成功!\n",i);
	srand(time(0));
	sleep(rand()%8);
	printf("第%d号线程释放资源成功!\n",i);
	sem_post(&sem);//+1
}

int main()
{
	sem_init(&sem,0,8);
	int i;
	for(i=0;i<16;i++)
	{
		pthread_t id;
		pthread_create(&id,0,task,(void *)i);
	}

	while(1);
}

