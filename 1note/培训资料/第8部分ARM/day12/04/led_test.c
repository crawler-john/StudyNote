#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define LED_ON 0x100001
#define LED_OFF 0x100002

int main()
{
	int fd = open("/dev/led",O_RDWR);
	if(fd<0)
	{
		printf("open failed!\n");
		return -1;
	}

	while(1)
	{
		ioctl(fd,LED_ON,0);
		sleep(1);
		ioctl(fd,LED_OFF,0);
		sleep(1);
		ioctl(fd,LED_ON,1);
		sleep(1);
		ioctl(fd,LED_OFF,1);
		sleep(1);
	}

	close(fd);
	return 0;
}

