#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>

int main()
{
	srand(time(0));
	//1.得到key
	key_t key = ftok(".",100);
	if(key<0)
	{
		perror("ftok");
		exit(-1);
	}
	//2.获取信号量集的ID
	int semid = semget(key,0,0);
	if(semid<0)
	{
		perror("semget");
		exit(-1);
	}
	//3.获取信号量
	int i;
	for(i=0;i<10;i++)
	{
		pid_t pid = fork();
		if(!pid)//子进程
		{
			printf("进程%d申请共享资源\n",i+1);
			struct sembuf sem;
			sem.sem_num = 0;//下标
			sem.sem_op = -1;//-1操作
			sem.sem_flg = 0;//阻塞
			semop(semid,&sem,1);//首元素的地址就是数组的地址
			printf("进程%d获得了共享资源\n",i+1);
			int n = rand()%10;
			sleep(n);
			sem.sem_op = 1;//+1操作
			semop(semid,&sem,1);
			printf("进程%d释放了共享资源\n",i+1);
			exit(0);
		}
	}
}

