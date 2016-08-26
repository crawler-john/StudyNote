#include <stdio.h>
#include <unistd.h>

void *g_begin = NULL;
//初始化
void init()
{
	g_begin = sbrk(0);
}

//终结化
void deinit()
{
	brk(g_begin);
}

//压入
void push(int data)
{
	*(int *)sbrk(sizeof(int)) = data;
}

//弹出
void pop()
{
	sbrk(-sizeof(int));
}

//获取栈顶
int top()
{
	return *((int *)sbrk(0)-1);
}

//判空
int empty()
{
	return sbrk(0)==g_begin;
}

//按任意进制打印
void print(unsigned int data,int base)
{
	init();
	do{
		push(data%base);
	}while(data/=base);

	for(;!empty();pop())
	{
		if(top()<10)
			printf("%d",top());
		else
			printf("%c",top()-10+'A');
	}
	printf("\n");
	deinit();
}

int main()
{
	printf("整数:");
	int data;
	scanf("%d",&data);
	printf("进制:");
	int base;
	scanf("%d",&base);
	printf("结果:");
	print(data,base);

	return 0;
}
