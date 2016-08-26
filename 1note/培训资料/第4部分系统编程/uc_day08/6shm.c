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
	//通过key获取一个共享内存并且获取他的ID
	int shmid = shmget(key,0,0);
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

	printf("%d\n",*(int *)p);
	//解除映射(卸载)共享内存
	shmdt(p);

	//删除共享内存
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}

