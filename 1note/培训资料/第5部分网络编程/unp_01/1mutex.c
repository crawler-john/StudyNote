#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;//1.声明
char *data[6];//定义一个大小是6的字符串数组
int size = 0;//定义当前的下标，也就是人数

void *task(void *p)
{
	pthread_mutex_lock(&lock);//3.加锁
	data[size] = (char *)p;
	usleep(100000);
	size++;
	pthread_mutex_unlock(&lock);//5.解锁
}

int main()
{
	data[size++] = "liubie";
	pthread_mutex_init(&lock,0);//2.初始化
	pthread_t id1,id2;
	pthread_create(&id1,0,task,"guanyu");
	pthread_create(&id2,0,task,"zhangfei");
	pthread_join(id1,0);
	pthread_join(id2,0);
	pthread_mutex_destroy(&lock);//6.释放锁的资源
	int i;
	for(i=0;i<size;i++)
		printf("%s\n",data[i]);

	return 0;
}

