#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "emp.h"

int main()
{
	int fd = open("emp.dat",O_RDWR|O_CREAT|O_APPEND,0666);
	if(fd<0)perror("open"),exit(-1);

	Emp emp = {};
	printf("请输入员工id,姓名,薪水\n");
	scanf("%d%s%f",&emp.id,emp.name,&emp.salary);
	int res = write(fd,&emp,sizeof(emp));
	if(res<=0)
		printf("注册失败!\n");
	else 
		printf("注册成功!\n");

	close(fd);
}

