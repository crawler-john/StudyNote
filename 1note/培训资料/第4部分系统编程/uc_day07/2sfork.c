#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	signal(SIGINT,fa);//自定义信号2的处理
	signal(SIGQUIT,SIG_IGN);//忽略信号3
	pid_t pid = fork();
	if(!pid)//子进程会继承父进程的信号处理方式
	{
		printf("cpid = %d\n",getpid());
		while(1);
	}

	printf("over\n");

	return 0;
}


