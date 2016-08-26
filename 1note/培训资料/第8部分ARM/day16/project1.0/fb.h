#ifndef __fb_h_
#define __fb_h_

struct framebuffer
{
	int fbfd;//�ļ�������
	unsigned int wfb;//��
	unsigned int hfb;//��
	unsigned int bpp;//����λ��
	unsigned int sizefb;//�Դ��С
	unsigned int *fbp32;//�Դ��ַ 
};

struct picture
{
	unsigned int pbpp;//����λ��
	unsigned int wdata;//��
	unsigned int hdata;//��
	unsigned int len;//��С
	unsigned char *pdata;//���ݵ�ַ
	unsigned int type;//ͼƬ����
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
