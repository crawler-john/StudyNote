#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void printenv(void)
{
	printf("-----环境变量-----\n");
	char **env;
	for(env=environ;env&&*env;++env)
	{
		printf("%s\n",*env);
		printf("---------------\n");
	}
}

int main(int argc,char *argv[],char *envp[])
{
	//argc表示命令行参数个数，包括可执行程序本身
	printf("argc = %d\n",argc);
	//argv表示参数本身，是一个字符串数组
	printf("argv[0] = %s\n",argv[0]);
	printf("argv[1] = %s\n",argv[1]);

	//添加环境变量
	putenv("MYNAME=贾子军");
	printenv();
	
	//修改环境变量
	putenv("MYNAME=杨威");
	printenv();
	printf("%p,%p\n",envp,environ);
	
	//获取环境变量
	printf("%s\n",getenv("MYNAME"));

	//有选择地修改环境变量
	setenv("MYNAME","王宁",0);
	printf("%s\n",getenv("MYNAME"));
	setenv("MYNAME","王宁",1);
	printf("%s\n",getenv("MYNAME"));
	
	//删除环境变量
	unsetenv("MYNAME");
	printenv();

	//清空环境变量
	clearenv();
	printenv();

	return 0;
}
