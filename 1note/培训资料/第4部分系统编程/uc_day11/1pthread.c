#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *task(void *p)
{
	int i;
	for(i=0;i<30;i++)
		printf("task:%d\n",i);
}


int main()
{
	pthread_t id;
	int res = pthread_create(&id,0,task,0);
	if(res)
		printf("%s\n",strerror(res));
	int i;
	for(i=0;i<30;i++)
		printf("main:%d\n",i);
	
	sleep(1);

	pthread_t id2 = pthread_self();
	printf("%u %u\n",id,id2);
	return 0;
}
