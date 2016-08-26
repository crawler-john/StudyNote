
void delay(int);

int led()
{
	volatile unsigned int *pcon = (unsigned int *)0xe0200280;
	volatile unsigned int *pdat = (unsigned int *)0xe0200284;
	volatile unsigned int *ppud = (unsigned int *)0xe0200288;

	//初始化
	*pcon = 0x1111;
	*ppud = 0;

	//闪烁
	while(1)
	{
		*pdat = 0;
		delay(500);
		*pdat = 0xf;
		delay(500);
	}

	return 0;
}

void delay(int n)
{
	int i,j;
	for(i=0;i<500;i++)
		for(j=0;j<n;j++);
}

