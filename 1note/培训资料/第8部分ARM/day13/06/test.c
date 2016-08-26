#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("/dev/cdd",O_RDWR);
	if(fd<0)
	{
		printf("open failed!\n");
		return -1;
	}

	while(1);
	
	close(fd);
	return 0;
}
