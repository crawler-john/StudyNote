#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

int semid;

void fa(int signo)
{
	int res = semctl(semid,0,IPC_RMID);
	if(!res)
		printf("删除成功!\n");
	else
		perror("semctl");
	exit(0);
}


int main()
{
	signal(SIGINT,fa);//登记信号处理函数
	//1.获取key
	key_t key = ftok(".",100);
	//2.通过key创建信号量集，并得到信号量集的ID
	semid = semget(key,1,IPC_CREAT|0666);
	if(semid<0)
	{
		printf("semget:%m\n");
		exit(-1);
	}
	//3.设置信号量的初始计数
	int res = semctl(semid,0,SETVAL,4);
	if(res<0)
	{
		perror("semctl");
		exit(-1);
	}
	printf("初始化信号量成功!\n");

	while(1);
}
//用信号SIGINT实现退出死循环时删除信号量集

