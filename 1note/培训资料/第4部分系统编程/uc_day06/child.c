#include <stdio.h>

int main()
{
	printf("cpid = %d\n",getpid());
	int i;
	for(i=0;i<50;i++)
		printf("c:%d\n",i);

	return 0;
}
