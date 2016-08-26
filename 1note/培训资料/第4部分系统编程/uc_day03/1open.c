#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	umask(0111);
	printf("%d,%d,%d,%d\n",O_RDONLY,O_WRONLY,O_RDWR,O_CREAT);

	int fd = open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0755);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}
	close(fd);

	return 0;
}


