#include "uart.h"
#include "nand.h"
#include "irq.h"

void uart_init()
{
	flag = 0;
	//将管脚配置成串口功能
	GPA0CON = 0x22;
	GPA0PUD = 0;

	//配置串口控制器
	ULCON0 = 0x3;
	UCON0 = 0x5;
	UBRDIV0 = PCLK/(BDR*16)-1;
	UDIVSLOT0 = 0x0888;
}

void uart_putc(char c)
{
	//如果UTRSTAT0的BIT1为1，退出循环，发送数据
	//如果UTRSTAT0的BIT1为0，应该继续循环
	while(!(UTRSTAT0&0x2));
	UTXH0 = c;

	if(c=='\n')
		uart_putc('\r');
}

void uart_puts(const char *s)
{
	while(*s)
		uart_putc(*s++);
}

char uart_getc()
{
	//如果UTRSTAT0的BIT0为1，退出循环，接收数据
	//如果UTRSTAT0的BIT0为0，应该继续循环
	while(!(UTRSTAT0&0x1));
	return URXH0;
}

const char *uart_gets()
{
	int i = 0;
	while(1)
	{
		char c = uart_getc();
		if((c=='\b')||(c==127))
		{
			i--;
			if(i<0)
			{
				i=0;
				continue;
			}
			uart_putc('\b');
			uart_putc(' ');
			uart_putc('\b');
			continue;
		}
		if(c=='\r')
			break;
		str_buf[i++] = c;
		uart_putc(c);
	}
	str_buf[i] = '\0';

	return str_buf;
}

int uart_strcmp(const char *s1,const char *s2)
{
	while(*s1)
	{
		if(*s1!=*s2)
			return -1;
		s1++;
		s2++;
	}

	if(*s2)
		return -1;
	else
		return 0;
}

int do_test(const char *s)
{
	uart_puts("\ntest finished!\n");

	return 0;
}

int do_ledon(const char *s)
{
	led_on();
	uart_puts("\n");
	return 0;
}

int do_ledoff(const char *s)
{
	led_off();
	uart_puts("\n");
	return 0;
}

int do_readid(const char *s)
{
	nand_readid();
	return 0;
}

int do_boot(const char *s)
{
	int i;
	unsigned int ptr = 0x20008000;
	void(*linux_start)(int a0,int a1,unsigned int a2) = (void(*)(int a0,int a1,unsigned int a2))0x20008000;
	unsigned int addr = 0x600000;
	uart_puts("\nloading linux kernel,wait...\n");
	for(i=0;i<0xc00000/NAND_PAGESIZE;i++)
	{
		uart_puts(".");
		nand_readpage(addr,ptr);
		ptr += NAND_PAGESIZE;
		addr += NAND_PAGESIZE;
	}
	uart_puts("\n");
	uart_puts("\nboot linux\n");
	uart_puts("\n");
	linux_start(0,2456,0);
}

int do_swi1(const char *s)
{
	swi_test1();
	return 0;
}

int do_swi2(const char *s)
{
	swi_test2();
	return 0;
}

int parse_cmd(const char *s)
{
	//uart_puts("\n");
	//uart_puts(s);
	//uart_puts("\n");
	if(!uart_strcmp("test",s))
		return do_test(s);
	else if(!uart_strcmp("ledon",s))
		return do_ledon(s);
	else if(!uart_strcmp("ledoff",s))
		return do_ledoff(s);
	else if(!uart_strcmp("nandid",s))
		return do_readid(s);
	else if(!uart_strcmp("boot",s))
		return do_boot(s);
	else if(!uart_strcmp("swi1",s))
		return do_swi1(s);
	else if(!uart_strcmp("swi2",s))
		return do_swi2(s);
	else if(!uart_strcmp("bye",s))
	{
		flag = 1;
		return 0;
	}
	else
	{
		uart_puts("\ncommand not found!\n");
		return 0;
	}

}

void main()
{
	led_init();
	uart_init();
	nand_init();
	irq_init();
	while(1)
	{
		uart_puts("###");
		const char *s = uart_gets();
		parse_cmd(s);
		if(flag==1)
			break;
	}
}

void delay(int n)
{
	int i,j;
	for(i=0;i<500;i++)
		for(j=0;j<n;j++);
}

