#include <stdio.h>

int main()
{
	int result = 0;
	result = syscall(366,10,20);

	printf("result=%d\n",result);

	return 0;
}
