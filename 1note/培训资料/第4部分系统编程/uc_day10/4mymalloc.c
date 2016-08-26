#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

//内存控制块
typedef struct mem_control_block{
	bool	free;//自由标志
	struct	mem_control_block *prev;//前块指针
	size_t	size;//本块大小
}MCB;

//栈顶指针
MCB *g_top = NULL;

//分配内存
void *mymalloc(size_t size)
{
	MCB *mcb;
	for(mcb=g_top;mcb;mcb=mcb->prev)
	{
		if(mcb->free&&mcb->size>=size)
			break;
	}

	if(!mcb)
	{
		mcb = sbrk(sizeof(MCB)+size);
		if(mcb==(void *)-1)
			return NULL;
		mcb->prev = g_top;
		mcb->size = size;
		g_top = mcb;
	}
	mcb->free = false;
	return mcb+1;
}

//释放内存
void myfree(void *ptr)
{
	if(!ptr)
		return;
	MCB *mcb = (MCB *)ptr-1;
	mcb->free = true;
	for(mcb=g_top;mcb->prev;mcb=mcb->prev)
	{
		if(!mcb->free)
			break;
	}
	//如果释放的块是最后一块，且前面的块都是自由的
	//需要将堆内存置空
	if(mcb->free)
	{
		g_top = mcb->prev;
		brk(mcb);
	}
	//释放的块是最后一块，但是前面有非空的块
	//需要把前面最后一个非空的块后面的空间释放
	else if(mcb!=g_top)
	{
		g_top = mcb;
		brk((void*)mcb+sizeof(MCB)+mcb->size);
	}
}

int main()
{
	printf("pid = %d\n",getpid());
	int *pn  = mymalloc(sizeof(int));
	double *pd = mymalloc(sizeof(double));
	char *ps = mymalloc(4096*sizeof(char));

	*pn = 1234;
	myfree(pn);
	printf("%d\n",*pn);
	*pd = 3.14;
	myfree(pd);
	printf("%g\n",*pd);
	sprintf(ps,"hello world!");
	myfree(ps);
	printf("%s\n",ps);
	return 0;
}

