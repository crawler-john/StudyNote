#ifndef _UART_H_
#define _UART_H_

#define GPA0CON		(*((volatile unsigned int *)0xe0200000))
#define GPA0PUD		(*((volatile unsigned int *)0xe0200008))
#define ULCON0		(*((volatile unsigned int *)0xe2900000))
#define UCON0		(*((volatile unsigned int *)0xe2900004))
#define UTRSTAT0	(*((volatile unsigned int *)0xe2900010))
#define UTXH0		(*((volatile unsigned int *)0xe2900020))
#define URXH0		(*((volatile unsigned int *)0xe2900024))
#define UBRDIV0		(*((volatile unsigned int *)0xe2900028))
#define UDIVSLOT0	(*((volatile unsigned int *)0xe290002c))

#define PCLK	66700000
#define BDR		115200

void uart_init();
void uart_putc(char c);
void uart_puts(const char *s);
char uart_getc();
const char *uart_gets();
int uart_strcmp(const char *s1,const char *s2);
int do_test(const char *s);
int do_ledon(const char *s);
int do_ledoff(const char *s);
int do_readid(const char *s);
int do_boot(const char *s);
int parse_cmd(const char *s);
void uart_run();
void delay(int n);

char str_buf[1024];
int flag;

#endif
