#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	/*
	int *p1 = malloc(sizeof(int));
	int *p2 = malloc(sizeof(int));
	printf("%p %p\n",p1,p2);
	free(p2);
	p1[3] = 0;
	free(p1);
	
	char *p1 = malloc(13);
	printf("%p\n",p1);
	getchar();
	char *p2 = malloc(1);
	printf("%p\n",p2);
	getchar();
	free(p2);
	free(p1);
	getchar();
	*/

	printf("每页%d字节.\n",getpagesize());

	return 0;
}
