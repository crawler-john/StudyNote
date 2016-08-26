#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	//使用路径产生key
	key_t key = ftok(".",100);
	if(key<0)
	{
		perror("ftok");
		exit(-1);
	}
	//通过key创建一个共享内存并且获取他的ID
	int shmid = shmget(key,4,IPC_CREAT|0666);
	if(shmid<0)
	{
		perror("shmid");
		exit(-1);
	}

	//挂载(映射)共享内存
	void *p = shmat(shmid,0,0);
	if(p==(void *)-1)
	{
		perror("shmat");
		exit(-1);
	}

	*(int *)p = 10;
	sleep(10);
	//解除映射(卸载)共享内存
	shmdt(p);

	return 0;
}

