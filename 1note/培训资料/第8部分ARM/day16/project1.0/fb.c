#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "fb.h"

#define COLOR_RED    0X00FF0000
#define COLOR_GREEN   0X0000FF00
#define COLOR_BLUE 0X000000FF
#define COLOR_BACK 0x00000000

int fb_open(global_t *global)
{
	struct fb_fix_screeninfo fbfix = {0};//¹Ì¶¨
	struct fb_var_screeninfo fbvar = {0};//¿É±ä

	global->fb_info.fbfd= open("/dev/fb0",O_RDWR);

	if(global->fb_info.fbfd<0)
	{
		printf("open failed!\n");
		return -1;
	}

	//»ñÈ¡ÆÁÄ»²ÎÊýÐÅÏ¢
	ioctl(global->fb_info.fbfd,FBIOGET_FSCREENINFO,&fbfix);
	ioctl(global->fb_info.fbfd,FBIOGET_VSCREENINFO,&fbvar);

	//¼ÆËãÏÔ´æ´óÐ¡
	global->fb_info.sizefb = fbvar.xres*fbvar.yres*(fbvar.bits_per_pixel/8);
	global->fb_info.wfb = fbvar.xres;
	global->fb_info.hfb = fbvar.yres;
	global->fb_info.bpp = fbvar.bits_per_pixel;

	//Ó³ÉäÏÔ´æµ½ÓÃ»§¿Õ¼ä
	global->fb_info.fbp32 = mmap(0, global->fb_info.sizefb, PROT_WRITE|PROT_READ, MAP_SHARED, global->fb_info.fbfd, 0);

	if(global->fb_info.fbp32==NULL)
	{
		printf("mmap framebuffer to user failed!\n");
		return -2;
	}
	
	return 0;
}

int fb_drawtest(global_t *global)
{
	int x,y;
	//²Ù×÷ÏÔ´æ

	if(global->fb_info.bpp == 32)
	{
		printf("start 32bpp framebuffer test!\n");
		for(y=0;y<global->fb_info.hfb/3;y++)
		{
			for(x=0;x<global->fb_info.wfb;x++)
			{
				*(global->fb_info.fbp32+y*global->fb_info.wfb+x) = COLOR_RED;
			}
		}

		for(;y<global->fb_info.hfb*2/3;y++)
		{
			for(x=0;x<global->fb_info.wfb;x++)
			{
				*(global->fb_info.fbp32+y*global->fb_info.wfb+x) = COLOR_BLUE;
			}
		}

		for(;y<global->fb_info.hfb;y++)
		{
			for(x=0;x<global->fb_info.wfb;x++)
			{
				*(global->fb_info.fbp32+y*global->fb_info.wfb+x) = COLOR_GREEN;
			}
		}
	}
	else
	{
		printf("can't find framebuffer test!\n");
	}
}

int fb_drawback(global_t *global)
{
	int x;

	if(global->fb_info.bpp == 32)
	{
		for(x=0;x<global->fb_info.sizefb/4;x++)
		{
			*(global->fb_info.fbp32+x) = COLOR_BACK;
		}

		return 0;
	}
}

int fb_draw(global_t *global)
{
	//Í¼Æ¬Æ«³öÆÁÄ»³¤¶È
	unsigned int x_excess;
	//Í¼Æ¬ÓÒ¶ËÀëÆÁÄ»×ó¶ËµÄ¾àÀë
	unsigned int x_edge;
	//Í¼Æ¬ÏÂ¶ËÀëÆÁÄ»ÉÏ¶ËµÄ¾àÀë
	unsigned int y_edge;
	//Í¼Æ¬³¬³öÆÁÄ»±êÊ¶
	unsigned int x_beyond_screen;

	unsigned int c32;
	unsigned int p;

	unsigned int skip =  4 - ((global->pic_info.wdata*global->pic_info.pbpp)>>3) & 3;

	int x,y;
		
	if((global->pic_info.wdata > global->fb_info.wfb) || (global->pic_info.hdata > global->fb_info.hfb))
	{
		printf("the picture is too big!\n");
		return -1;
	}

	if(global->x0 + global->pic_info.wdata > global->fb_info.wfb)
	{
		x_excess = global->x0 + global->pic_info.wdata - global->fb_info.wfb;
		x_beyond_screen = 1;
		x_edge = global->fb_info.wfb;
	}
	else
	{
		x_beyond_screen = 0;
		x_edge = global->x0 + global->pic_info.wdata;
	}

	y_edge = (global->y0 + global->pic_info.hdata > global->fb_info.hfb) ? (global->fb_info.hfb):(global->y0 + global->pic_info.hdata);
	
	if(global->fb_info.bpp == 32)
	{
		if(global->pic_info.pbpp<24)
		{
			printf("fb bpp is 32,picture bpp is %d!\n",global->pic_info.pbpp);
		}
		
		for(y=global->y0;y<y_edge;y++)
		{
			for(x=global->x0;x<x_edge;x++)
			{
				c32 = (global->pic_info.pdata[p]) | (global->pic_info.pdata[p+1]<<8) | (global->pic_info.pdata[p+2]<<16);
				*(global->fb_info.fbp32+(y_edge-y-1)*global->fb_info.wfb+x) = c32;
				p += 3;
			}
			
			if(x_beyond_screen)
			{
				p += 3*x_excess;
			}
			p += skip;
		}
	}

	return 0;
}

void fb_close(global_t *global)
{
	munmap(global->fb_info.fbp32,global->fb_info.sizefb);
	close(global->fb_info.fbfd);
}


