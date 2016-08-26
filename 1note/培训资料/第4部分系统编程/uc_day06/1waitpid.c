#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid1,pid2;
	pid1 = fork();//父子进程
	if(pid1>0)//父进程
	{
		pid2 = fork();
	}

	if(!pid1)//子进程1的分支
	{
		printf("子进程1开始运行!\n");
		sleep(1);
		printf("子进程1结束!\n");
		exit(10);
	}
	if(!pid2)//子进程2的分支
	{
		printf("子进程2开始运行!\n");
		sleep(3);
		printf("子进程2结束!\n");
		exit(20);
	}

	int status;

	waitpid(/*-1*/pid2,&status,0);

	if(WIFEXITED(status))
		printf("%d\n",WEXITSTATUS(status));

	return 0;
}
