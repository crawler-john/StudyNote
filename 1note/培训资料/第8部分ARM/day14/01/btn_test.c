#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int fd;
	unsigned char key_val;

	fd = open("/dev/btn",O_RDWR);
	if(fd<0)
	{
		printf("open failed!\n");
		return -1;
	}


	while(1)
	{
		read(fd,&key_val,1);
		printf("key_val = %#x\n",key_val);
	}

	close(fd);
	return 0;
}

