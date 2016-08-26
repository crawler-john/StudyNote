/*链接文件会指定生成的可执行程序在内存中的大体布局*/

SECTIONS
{
	. = 0xd0020000;
	.text :
	{
		start.o(.text);
		*.o(.text);
	}

	.rodata :
	{
		*.o(.rodata);
	}

	. = ALIGN(4);
	.data :
	{
		*.o(.data);
	}

	. = ALIGN(4);
	__bss_start = .;
	.bss :
	{
		*.o(.bss);
	}
	__end = .;
}

