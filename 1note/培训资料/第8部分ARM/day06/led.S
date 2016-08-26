.text
.code 32

.global led_init
.global led_on
.global led_off

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


