#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("进程%d启动\n",getpid());
	pid_t pid = fork();
	if(!pid)//父子进程都判断,子进程符合
	{
		printf("我是子进程%d,父进程%d.\n",getpid(),getppid());
		sleep(2);
		printf("我是子进程%d,父进程%d.\n",getpid(),getppid());
		exit(0);
	}
	sleep(1);
	printf("父进程结束\n");

	return 0;
}
