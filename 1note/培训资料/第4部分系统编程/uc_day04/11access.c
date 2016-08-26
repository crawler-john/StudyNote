#include <stdio.h>
#include <unistd.h>

int main()
{
	if(!access("a.txt",R_OK))
		printf("可读!\n");
	if(!access("a.txt",W_OK))
		printf("可写!\n");
	if(!access("a.txt",X_OK))
		printf("可执行!\n");
	if(!access("a.txt",F_OK))//读文件之前判断文件是否存在
		printf("文件存在!\n");

	return 0;
	
}
