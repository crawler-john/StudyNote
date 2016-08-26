#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>

int main(int argc,char *argv[])
{
	int fd;
	struct input_event button;

	if(argc<2)
	{
		printf("usage:\n%s /dev/event<0,1...>\n",argv[0]);
		return -1;
	}
	fd = open(argv[1],O_RDWR);
	if(fd<0)
	{
		printf("open failed!\n");
		return -1;
	}


	while(1)
	{
		if(read(fd,&button,sizeof(button))<0)
		{
			printf("read error!\n");
			break;
		}
		printf("type = %#x,code = %#x,value = %#x\n",
			button.type,button.code,button.value);
	}

	close(fd);
	return 0;
}

