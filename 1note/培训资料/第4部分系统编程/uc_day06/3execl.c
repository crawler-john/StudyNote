#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("begin\n");
	/*第一个参数是程序的路径
	 *第二个参数是命令
	 *第三个参数是选项
	 *后面还可以跟有命令的参数,以NULL结束*/
	int res = execl("/bin/ls","ls","-l",NULL);
	if(res==-1)
	{
		perror("execl");
		exit(-1);
	}

	printf("over\n");

	return 0;
}

