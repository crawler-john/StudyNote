#ifndef __fb_h_
#define __fb_h_

struct framebuffer
{
	int fbfd;//文件描述符
	unsigned int wfb;//宽
	unsigned int hfb;//高
	unsigned int bpp;//像素位数
	unsigned int sizefb;//显存大小
	unsigned int *fbp32;//显存地址 
};

struct picture
{
	unsigned int pbpp;//像素位数
	unsigned int wdata;//宽
	unsigned int hdata;//高
	unsigned int len;//大小
	unsigned char *pdata;//数据地址
	unsigned int type;//图片类型
};

struct _global
{
	struct framebuffer fb_info;
	struct picture pic_info;
	unsigned int x0;
	unsigned int y0;
};

typedef struct _global global_t;

int fb_drawtest(global_t *);
int fb_open(global_t *);
int fb_drawback(global_t * global);
void fb_close(global_t * global);
int fb_draw(global_t * global);


#endif
