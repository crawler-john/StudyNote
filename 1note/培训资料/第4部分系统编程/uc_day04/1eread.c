#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "emp.h"

int main()
{
	int fd = open("emp.dat",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	Emp emp;
	while(1)
	{
		int res = read(fd,&emp,sizeof(emp));
		if(res<0)
		{
			perror("read");
			break;
		}
		if(res==0)
			break;
		printf("%d,%s,%g\n",emp.id,emp.name,emp.salary);
	}

	close(fd);

	return 0;
}

