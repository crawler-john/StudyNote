#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
	char *p1 = malloc(0xffffffff);
	FILE *p = fopen("no","r");

	if(!p1)
	{
		printf("malloc:%d,%d\n",errno,ENOMEM);

		if(errno==ENOMEM)
		{
			printf("内存不足!\n");
			return -1;
		}

		printf("malloc:%s\n",strerror(errno));
		printf("malloc:%m\n");
		perror("malloc");
		return -1;
	}

	return 0;
}
