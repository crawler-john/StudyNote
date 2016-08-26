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
	printf("pid = %d\n",getpid());

	int res = sleep(10);
	usleep(10000);//休眠0.01秒

	printf("进程结束,剩余%d秒\n",res);

	return 0;
}
