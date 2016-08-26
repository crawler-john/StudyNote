#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(!pid)//父子进程都判断,子进程符合
	{
		printf("我是子进程%d,父进程%d.\n",getpid(),getppid());
	}
	else//父进程的分支
	{
		printf("我是父进程%d,子进程%d.\n",getpid(),pid);
		sleep(10);
	}

	return 0;
}
