#include <stdio.h>
#include <unistd.h>

void presskey(void)
{
	printf("查看/proc/%d/maps,按<回车>继续...",getpid());
	getchar();
}

int main()
{
	void *p1 = sbrk(4);
	printf("p1 = %p\n",p1);
	void *p2 = sbrk(4);
	printf("p2 = %p\n",p2);
	void *p3 = sbrk(4);
	printf("p3 = %p\n",p3);
	void *p4 = sbrk(4);
	printf("p4 = %p\n",p4);
	void *p5 = sbrk(0);
	printf("p5 = %p\n",p5);
	int *pn = (int *)p1;
	pn[0] = 0;
	pn[1] = 1;
	pn[2] = 2;
	pn[3] = 3;
	pn[1023] = 1023;

	printf("%d %d %d %d %d\n",pn[0],pn[1],pn[2],pn[3],pn[1023]);
	//pn[1024] = 1024;
	void *p6 = sbrk(-8);
	printf("p6 = %p\n",p6);
	void *p7 = sbrk(-8);
	printf("p7 = %p\n",p7);
	int page = getpagesize();
	printf("%p\n",sbrk(page));
	presskey();
	printf("%p\n",sbrk(1));
	presskey();
	printf("%p\n",sbrk(-1));
	presskey();
	printf("%p\n",sbrk(-page));
	p1 = sbrk(0);
	printf("p1 = %p\n",p1);

	brk(p2=p1+4);
	printf("p2 = %p\n",p2);
	brk(p3=p2+4);
	printf("p3 = %p\n",p3);
	brk(p4=p3+4);
	printf("p4 = %p\n",p4);
	brk(p5=p4+4);
	printf("p5 = %p\n",p5);

	pn = (int *)p1;
	pn[0] = 0;
	pn[1] = 1;
	pn[2] = 2;
	pn[3] = 3;
	pn[1023] = 1023;

	printf("%d %d %d %d %d\n",pn[0],pn[1],pn[2],pn[3],pn[1023]);
	//pn[1024] = 1024;
	brk(p1);
	void *begin = sbrk(sizeof(int));
	pn = (int *)begin;
	*pn = 1234;
	double *pd = sbrk(sizeof(double));
	*pd = 3.14;
	char *ps = sbrk(256*sizeof(char));
	sprintf(ps,"welcome,everyone!");
	printf("%d %g %s\n",*pn,*pd,ps);
	brk(begin);

	return 0;
}
