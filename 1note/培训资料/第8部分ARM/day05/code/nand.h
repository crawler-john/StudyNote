#ifndef _NAND_H_
#define _NAND_H_

#define NFCONF		(*((volatile unsigned int *)0xb0e00000))
#define NFCONT		(*((volatile unsigned int *)0xb0e00004))
#define NFCMMD		(*((volatile unsigned int *)0xb0e00008))
#define NFADDR		(*((volatile unsigned int *)0xb0e0000c))
#define NFDATA		(*((volatile unsigned int *)0xb0e00010))
#define NFSTAT		(*((volatile unsigned int *)0xb0e00028))

#define NAND_PAGESIZE 2048

void nand_init();
void nand_ce1_en();
void nand_ce1_dis();
void nand_itoa(unsigned int a,char *buf);
void nand_clear_stat();
void nand_wait_rb();
void nand_readid();
void nand_readpage(unsigned int faddr,unsigned int addr);

char nand_id[11];

#endif

