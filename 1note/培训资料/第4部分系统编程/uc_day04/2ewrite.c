#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "emp.h"

int main()
{
	int fd = open("em.dat",O_RDWR|O_CREAT|O_APPEND,0777);
	if(fd<0)perror("open"),exit(-1);

	Emp emp = {};
	printf("请输入员工id,姓名,薪水\n");
	scanf("%d%s%f",&emp.id,emp.name,&emp.salary);
	char buf[50] = {};
	sprintf(buf,"%d,%s,%g",emp.id,emp.name,emp.salary);
	int res = write(fd,buf,strlen(buf));
	if(res<=0)
		printf("注册失败!\n");
	else 
		printf("注册成功!\n");

	close(fd);
}

