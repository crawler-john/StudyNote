#include <stdio.h>
#include <signal.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	printf("pid = %d\n",getpid());
	signal(SIGINT,fa);
	signal(/*SIGQUIT*/45,fa);
	printf("执行普通代码，没有屏蔽!\n");
	sleep(10);
	printf("执行关键代码，信号屏蔽!\n");
	sigset_t set,old;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,/*SIGQUIT*/45);
	sigprocmask(SIG_SETMASK,&set,&old);
	sleep(15);
	printf("关键代码执行完毕,解除屏蔽!\n");
	sigset_t arset;
	sigpending(&arset);
	if(sigismember(&arset,SIGINT))
		printf("信号SIGINT来过！\n");
	if(sigismember(&arset,45))
		printf("信号45来过!\n");
	sigprocmask(SIG_SETMASK,&old,NULL);//解除屏蔽

	while(1);
}
