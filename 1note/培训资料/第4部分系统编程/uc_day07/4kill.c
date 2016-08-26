#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	pid_t pid = fork();

	if(!pid)
	{
		printf("cpid = %d\n",getpid());
		signal(SIGINT,fa);
		while(1);
	}

	sleep(1);
	kill(pid,2);
	printf("父进程结束\n");

	return 0;
}

