.text
.code 32
.global start


start:
	bl led_init
	b led
	
led:
	bl led_on
	ldr r2,=0x4000000
	bl delay
	bl led_off
	ldr r2,=0x4000000
	bl delay
	b led

led_init:
	ldr r0,=0xe0200280
	ldr r1,=0x1111
	str r1,[r0]
	ldr r0,=0xe0200288
	mov r1,#0
	str r1,[r0]
	mov pc,lr

led_on:
	ldr r0,=0xe0200284
	mov r1,#0
	str r1,[r0]
	mov pc,lr


led_off:
	ldr r0,=0xe0200284
	mov r1,#0xf
	str r1,[r0]
	mov pc,lr

delay:
	subs r2,r2,#1
	bne delay
	mov pc,lr


