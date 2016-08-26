#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fb.h"
#include "bmp.h"

#define MAX_PIC_WIDTH 1366
#define MAX_PIC_HIGHT 768
#define MAX_BPP_IN_BYTE 4

unsigned char picture_data[MAX_PIC_WIDTH*MAX_PIC_HIGHT*MAX_BPP_IN_BYTE];

int main(int argc,char **argv)
{
	global_t ginfo;
	memset(&ginfo,0,sizeof(global_t));

	ginfo.pic_info.pdata = picture_data;

	ginfo.x0 = 0;
	ginfo.y0 = 0;

	fb_open(&ginfo);

	fb_drawback(&ginfo);

	sleep(2);

	draw_bmp(&ginfo,"1.bmp");

	sleep(2);

	draw_bmp(&ginfo,"2.bmp");

	sleep(2);

	fb_close(&ginfo);

	return 0;
}
