#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fa()
{
	printf("fa() is called!\n");
}

int main()
{
	atexit(fa);//注册，不是调用
	printf("begin\n");
	//exit(0);//会调用
	//_exit(0);//不调用
	_Exit(0);//不调用

	//return 0;//会掉用
	printf("end\n");
}
