#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	signal(SIGINT,fa);
	signal(SIGQUIT,SIG_IGN);
	pid_t pid = vfork();
	if(!pid)
	{
		printf("cpid = %d\n",getpid());
		execl("./c.out","c.out",NULL);
	}

	printf("over\n");
}

