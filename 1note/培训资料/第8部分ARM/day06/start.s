   .text
   .global  start
   .extern  main

    .extern irq_stack_end
    .extern fiq_stack_end
    .word 0x2000
    .word 0x0
    .word 0x0
    .word 0x0
    
start:

    msr cpsr_c,#0xd2
    ldr	sp, =irq_stack_end   
    sub	sp, sp, #8	         /* set irq stack */

    msr cpsr_c,#0xd1
    ldr	sp, =fiq_stack_end   
    sub	sp, sp, #8	         /* set fiq stack */

    msr cpsr_c,#0xd3
    ldr	sp, =0xd0036000  
    sub	sp, sp, #12	     /* set svc stack */

    bl	disable_l2cache

    bl	set_l2cache_auxctrl_cycle

    bl	enable_l2cache


    /*
     * Invalidate L1 I/D
     */
    mov	r0, #0                  @ set up for MCR
    mcr	p15, 0, r0, c8, c7, 0   @ invalidate TLBs
    mcr	p15, 0, r0, c7, c5, 0   @ invalidate icache

    /*
     * disable MMU stuff and caches
     */
    mrc	p15, 0, r0, c1, c0, 0
    bic	r0, r0, #0x00002000     @ clear bits 13 (--V-)
    bic	r0, r0, #0x00000007     @ clear bits 2:0 (-CAM)
    orr	r0, r0, #0x00000002     @ set bit 1 (--A-) Align
    orr	r0, r0, #0x00000800     @ set bit 12 (Z---) BTB
    mcr 	p15, 0, r0, c1, c0, 0

	/*电源管理，保持供电*/
	/* PS_HOLD(GPJ2_5) set to output high */
	
.equ  ELFIN_GPIO_BASE,	0xE0200000
.equ  GPJ2CON_OFFSET,	0x280 
.equ  GPJ2DAT_OFFSET,	0x284 
.equ  GPJ2PUD_OFFSET,	0x288 

    ldr		r0, =ELFIN_GPIO_BASE
    ldr		r1, =0x00100000
    str		r1, [r0, #GPJ2CON_OFFSET]
    ldr		r1, =0x0400
    str		r1, [r0, #GPJ2PUD_OFFSET]
    ldr		r1, =0x20
    str		r1, [r0, #GPJ2DAT_OFFSET]

	/*
	 * Go setup Memory and board specific bits prior to relocation.
	 */
    bl	lowlevel_init     	 /* go setup pll,mux,memory */

	/* enable domain access */
	ldr	r5, =0x0000ffff
	mcr	p15, 0, r5, c3, c0, 0		@load domain access register

    .extern set_mmu_table
    ldr  r0, =0x23e00000
    bl   set_mmu_table

    ldr r1, =0x23e00000
	mcr	p15, 0, r1, c2, c0, 0

	/* Enable the MMU */
mmu_on:
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #1
	mcr	p15, 0, r0, c1, c0, 0

	nop
	nop
	nop
	nop
    nop 
    nop

	nop
	nop
	nop
	nop
    nop 
    nop


clear_bss:
    ldr	r0, bss_start		        /* find start of bss segment    */
    ldr	r1, bss_end		        /* stop here                        */
    mov 	r2, #0x00000000		/* clear                            */

clbss_l:
    str	r2, [r0]		/* clear loop...                    */
    add	r0, r0, #4
    cmp	r0, r1
    ble	clbss_l

    .extern install_vector_handler
    bl install_vector_handler

    ldr	pc, start_armboot
    b  start

start_armboot:
    .word   main

bss_start:
    .word   __bss_start

bss_end:
    .word   __end


    .align  5
.global  disable_l2cache
disable_l2cache:
    mrc     p15, 0, r0, c1, c0, 1
    bic     r0, r0, #(1<<1)
    mcr     p15, 0, r0, c1, c0, 1
    mov 	pc, lr

    .align  5
.global  enable_l2cache
enable_l2cache:
    mrc     p15, 0, r0, c1, c0, 1
    orr     r0, r0, #(1<<1)
    mcr     p15, 0, r0, c1, c0, 1
    mov     pc, lr
       .align  5
.global  set_l2cache_auxctrl_cycle
set_l2cache_auxctrl_cycle:
    mrc  p15, 1, r0, c9, c0, 2
    bic 	 r0, r0, #(0x1<<29)
    bic 	 r0, r0, #(0x1<<21)
    bic 	 r0, r0, #(0x7<<6)
    bic 	 r0, r0, #(0x7<<0)
    mcr  p15, 1, r0, c9, c0, 2
    mov     pc,lr

	.globl  lowlevel_init
lowlevel_init:
    stmfd  sp!, {lr}

.equ  ELFIN_WATCHDOG_BASE,		0xE2700000
	/* Disable Watchdog */
    ldr	r0, =ELFIN_WATCHDOG_BASE	/* 0xE2700000 */
    mov	r1, #0
    str	r1, [r0]

	/* init system clock */
    bl  system_clock_init

	/* Memory initialize */
    bl  mem_init

    ldmfd  sp!,  {pc}
/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
system_clock_init:
.equ  ELFIN_CLOCK_POWER_BASE,         0xE0100000
    ldr	r0, =ELFIN_CLOCK_POWER_BASE	@0xe0100000

.equ  APLL_LOCKTIME_VAL,				0x2cf
.equ  CLK_SRC0_OFFSET, 	    		0x200

/* Clock & Power Controller for s5pc110*/
.equ  APLL_LOCK_OFFSET,  0x00
.equ  APLL_CON0_OFFSET,  0x100
.equ  APLL_CON1_OFFSET,  0x104
.equ  MPLL_CON_OFFSET , 	0x108
.equ  VPLL_CON_OFFSET , 	0x120

	/* Set Mux to FIN */
    ldr	r1, =0x0
    str	r1, [r0, #CLK_SRC0_OFFSET]

    ldr	r1,	=APLL_LOCKTIME_VAL
    str	r1,	[r0, #APLL_LOCK_OFFSET]

	/* Disable PLL */

    ldr	r1, =0x0
    str	r1, [r0, #APLL_CON0_OFFSET]
    ldr	r1, =0x0
    str	r1, [r0, #MPLL_CON_OFFSET]

    ldr	r1, =0x0
    str	r1, [r0, #MPLL_CON_OFFSET]


.equ  APLL_MDIV,				0x7d
.equ  APLL_PDIV,				0x3
.equ  APLL_SDIV,				0x1
.equ  MPLL_MDIV,				0x29b
.equ  MPLL_PDIV,				0xc
.equ  MPLL_SDIV,				0x1
.equ  EPLL_MDIV,				0x60
.equ  EPLL_PDIV,				0x6
.equ  EPLL_SDIV,				0x2

.equ  VPLL_MDIV,					0x6c
.equ  VPLL_PDIV,					0x6
.equ  VPLL_SDIV,					0x3

.equ  CLK_DIV0_OFFSET,		  	0x300

.equ  CLK_DIV0_MASK,					0x7fffffff


/* CLK_DIV0 */
.equ  APLL_RATIO,				0
.equ  A2M_RATIO,				4
.equ  HCLK_MSYS_RATIO,				8
.equ  PCLK_MSYS_RATIO,				12
.equ  HCLK_DSYS_RATIO,				16
.equ  PCLK_DSYS_RATIO,				20
.equ  HCLK_PSYS_RATIO,				24
.equ  PCLK_PSYS_RATIO,				28


.equ  APLL_VAL, (1<<31 | APLL_MDIV<<16 | APLL_PDIV<<8 | APLL_SDIV)	
.equ  MPLL_VAL, (1<<31 | MPLL_MDIV<<16 | MPLL_PDIV<<8 | MPLL_SDIV) 
.equ  VPLL_VAL, (1<<31 | VPLL_MDIV<<16 | VPLL_PDIV<<8 | VPLL_SDIV) 


.equ  CLK_DIV0_VAL,	((0<<APLL_RATIO)|(4<<A2M_RATIO)|(4<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))

    ldr   	r1, [r0, #CLK_DIV0_OFFSET]
    ldr	r2, =CLK_DIV0_MASK
    bic	r1, r1, r2
    
    ldr	r2, =CLK_DIV0_VAL
    orr	r1, r1, r2
    str	r1, [r0, #CLK_DIV0_OFFSET]
    
    ldr	r1, =APLL_VAL
    str	r1, [r0, #APLL_CON0_OFFSET]
    
    ldr	r1, =MPLL_VAL
    str	r1, [r0, #MPLL_CON_OFFSET]
    
    ldr	r1, =VPLL_VAL
    str	r1, [r0, #VPLL_CON_OFFSET]

.equ  AFC_ON,								0x00000000

    ldr	r1, =AFC_ON
    str	r1, [r0, #APLL_CON1_OFFSET]
    
    mov	r1, #0x10000
1:	
    subs	r1, r1, #1
    bne	1b

    ldr	r1, [r0, #CLK_SRC0_OFFSET]
    ldr	r2, =0x10001111
    orr	r1, r1, r2
    str	r1, [r0, #CLK_SRC0_OFFSET]


	mov	pc, lr

   .end
