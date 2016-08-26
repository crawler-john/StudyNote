#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
	//int fd = open("a.txt",O_RDWR|O_CREAT,0666);
	char *psz = mmap(sbrk(0)/*NULL*/,8192/*256*/,PROT_READ|PROT_WRITE,
					MAP_PRIVATE|MAP_ANONYMOUS/*MAP_SHARED*/,0,0);
	if(psz==MAP_FAILED)
	{
		perror("mmap");
		exit(-1);
	}
	printf("psz = %p\n",psz);
	sprintf(psz,"hello,everyone!");
	printf("%s\n",psz);
	printf("%d\n",getpid());
	getchar();

	if(munmap(psz,4096)==-1)
	{
		perror("mmmap1");
		exit(-1);
	}
	getchar();

	if(munmap(psz+4096,4096)==-1)
	{
		perror("mmmap2");
		exit(-1);
	}
	getchar();

	return 0;
}

