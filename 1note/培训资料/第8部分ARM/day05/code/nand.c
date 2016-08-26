#include "nand.h"
#include "uart.h"

void nand_init()
{
	NFCONF = (1<<1)|(0xf<<4)|(0xf<<8)|(0xf<<12);
	NFCONT = (7)|(3<<4)|(3<<22);
}

void nand_ce1_en()
{
	NFCONT &= ~(1<<1);
}

void nand_ce1_dis()
{
	NFCONT |= (1<<1);
}

void nand_itoa(unsigned int a,char *buf)
{
	int i;
	unsigned int c;
	buf[0] = '0';
	buf[1] = 'x';
	i = 9;
	while(a)
	{
		c = a%16;
		if(c>=10)
		{
			buf[i] = c-10+'A';
		}
		else
		{
			buf[i] = c+'0';
		}
		a = a/16;
		i--;
	}
	//剩余的位要清0
	while(i>=2)
	{
		buf[i--] = '0';
	}
	buf[10] = '\0';
}

void nand_clear_stat()
{
	NFSTAT |= (1<<4);
}

void nand_wait_rb()
{
	while(!(NFSTAT&(1<<4)));
}

void nand_readid()
{
	//芯片使能
	nand_ce1_en();
	//发送90H命令
	NFCMMD = 0x90;
	//放送00H地址
	NFADDR = 0x0;
	//延时一下
	int i;
	for(i=0;i<256;i++)
	{
		;
	}
	//读取ID
	unsigned int id1,id2;
	id1 = NFDATA;
	id2 = NFDATA;
	//片选禁止
	nand_ce1_dis();
	id2 &= 0xff;
	nand_itoa(id1,nand_id);
	uart_puts("\nid1 = ");
	uart_puts(nand_id);
	nand_itoa(id2,nand_id);
	uart_puts("\nid2 = ");
	uart_puts(nand_id);
	uart_puts("\n");
}

void nand_readpage(unsigned int faddr,unsigned int addr)
{
	int pagenum,i;
	int *ptr;
	pagenum = faddr/NAND_PAGESIZE;
	nand_clear_stat();
	nand_ce1_en();

	//发送命令00H
	NFCMMD = 0x0;

	//发送地址
	NFADDR = 0;
	NFADDR = 0;
	NFADDR = (pagenum&0xff);
	NFADDR = ((pagenum>>8)&0xff);
	NFADDR = ((pagenum>>16)&0xff);

	//发送命令30H
	NFCMMD = 0x30;

	//等待RnB的跳变发生
	nand_wait_rb();

	ptr = (int *)addr;
	for(i=0;i<NAND_PAGESIZE/4;i++)
	{
		ptr[i] = NFDATA;
	}
	
	nand_ce1_dis();
}


