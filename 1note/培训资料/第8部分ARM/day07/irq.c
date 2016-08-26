#include "irq.h"
#include "uart.h"

void c_und_handler(void)
{
	uart_puts("\nc_und_handler\n");
	while(1);
}

void c_pabt_handler(void)
{
	uart_puts("\nc_pabt_handler\n");
	while(1);
}

void c_dabt_handler(void)
{
	uart_puts("\nc_dabt_handler\n");
	while(1);
}

void c_irq_handler(void)
{
	uart_puts("\nc_irq_handler\n");
	void(*func)(void) = (void(*)(void))VIC0ADDRESS;
	if(func)
	{
		func();
	}
	VIC0ADDRESS = 0;
}

void c_fiq_handler(void)
{
	uart_puts("\nc_fiq_handler\n");
}

void c_swi_handler(unsigned int num)
{
	uart_puts("\nc_swi_handler\n");
	switch(num)
	{
		case 1:
			uart_puts("\nc_swi_1\n");
			break;
		case 2:
			uart_puts("\nc_swi_2\n");
			break;
		default:
			uart_puts("\nnum error\n");
			break;
	}
}

void exint_func(void)
{
	if(EXT2PEND&(1<<0))
		uart_puts("\nkey1_isr!\n");
	if(EXT2PEND&(1<<1))
		uart_puts("\nkey2_isr!\n");

	//清除中断标志
	EXT2PEND |= 0x3;
}

void irq_init()
{
	//中断源的配置
	EXT2MASK |= 0x3;
	EXT2PEND |= 0x3;

	GPH2CON |= 0xff;
	GPH2PUD &= ~(0xf);
	EXT2CON = (EXT2CON&(~0xff))|0x22;

	//中断控制器的配置
	VIC0INTENCLEAR |= (1<<16);
	TZIC0INTSELECT &= ~(1<<16);
	VIC0INTSELECT &= ~(1<<16);

	VIC0ADDRESS = 0;
	VIC0VECTADDR16 = (unsigned int)exint_func;

	//开启中断
	EXT2MASK &= ~0x3;
	VIC0INTENABLE |= (1<<16);
	enable_irq();
}


