#ifndef _IRQ_H_
#define _IRQ_H_

#define GPH2CON			(*((volatile unsigned int *)0xe0200c40))
#define GPH2PUD			(*((volatile unsigned int *)0xe0200c48))
#define EXT2CON			(*((volatile unsigned int *)0xe0200e08))
#define EXT2MASK		(*((volatile unsigned int *)0xe0200f08))
#define EXT2PEND		(*((volatile unsigned int *)0xe0200f48))
#define TZIC0INTSELECT	(*((volatile unsigned int *)0xf2800008))
#define VIC0INTSELECT	(*((volatile unsigned int *)0xf200000c))
#define VIC0INTENABLE	(*((volatile unsigned int *)0xf2000010))
#define VIC0INTENCLEAR	(*((volatile unsigned int *)0xf2000014))
#define VIC0ADDRESS	(*((volatile unsigned int *)0xf2000f00))
#define VIC0VECTADDR16	(*((volatile unsigned int *)0xf2000140))


void exint_func(void);
void irq_init();

#endif
