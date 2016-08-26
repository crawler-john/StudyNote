#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int const_global = 10;//常全局变量
int init_global = 10;//初始化全局变量
int uninit_global;//未初始化全局变量

int main(int argc,char *argv[])
{
	const static int const_static = 10;//常静态变量
	static int init_static = 10;//初始化静态变量
	static int uninit_static;//未初始化静态变量
	const int const_local = 10;//常局部变量
	int prev_local;//前局部变量
	int next_local;//后局部变量
	int *prev_heap = malloc(sizeof(int));//前堆变量
	int *next_heap = malloc(sizeof(int));//后堆变量
	const char *literal = "literal";
	extern char** environ;//环境变量
	printf("---命令行参数和环境变量-------\n");
	printf("	环境变量：%p\n",environ);
	printf("	命令行参数：%p\n",argv);
	printf("---------------栈-------------\n");
	printf("	常局部变量：%p\n",&const_local);
	printf("	前局部变量：%p\n",&prev_local);
	printf("	后局部变量：%p\n",&next_local);
	printf("---------------堆-------------\n");
	printf("	前堆变量：%p\n",&prev_heap);
	printf("	后堆变量：%p\n",&next_heap);
	printf("---------------BSS-------------\n");
	printf("	未初始化全局变量：%p\n",&uninit_global);
	printf("	未初始化静态变量：%p\n",&uninit_static);
	printf("---------------数据-------------\n");
	printf("	初始化全局变量：%p\n",&init_global);
	printf("	初始化静态变量：%p\n",&init_static);
	printf("---------------代码-------------\n");
	printf("	字面值常量：%p\n",literal);
	printf("	常全局变量：%p\n",&const_global);
	printf("	常静态变量：%p\n",&const_static);
	printf("	函数：%p\n",main);

	return 0;
}
