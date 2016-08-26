#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	signal(SIGALRM,fa);
	struct itimerval ti;
	ti.it_interval.tv_sec = 1;//间隔时间
	ti.it_interval.tv_usec = 100000;
	ti.it_value.tv_sec = 3;//起始时间
	ti.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL,&ti,NULL);
	while(1);
}

