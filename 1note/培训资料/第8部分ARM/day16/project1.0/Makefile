picture:main.o fb.o bmp.o
	arm-linux-gcc main.o fb.o bmp.o -o picture
main.o:main.c
	arm-linux-gcc -c main.c
fb.o:fb.c
	arm-linux-gcc -c fb.c
bmp.o:bmp.c
	arm-linux-gcc -c bmp.c

clean:
	rm -rf *.o picture
