#ifndef _BMP_H_
#define _BMP_H_

#include "fb.h"

//位图文件文件头14bytes
typedef struct
{
	char cftype[2];//文件类型,必须是'B''M' 0x424d
	char cfsize[4];//文件大小
	char cfreserved[4];//保留
	char cfoffbits[4];//图像信息对于文件头的偏移量
} bitmap_fileheader_t;

//位图文件信息头40bytes
typedef struct
{
	char cisize[4];//信息头的大小
	char ciwidth[4];//位图的宽度(像素)
	char ciheight[4];//位图的高度
	char ciplanes[2];//位图平面数,必须为1
	char cibitcount[2];//每个像素的位数1,4,8,24,32
	char cicompress[4];//位图的压缩方式0=不压缩
	char cisizeimage[4];//图像大小(字节),可能是0
	char cixpelspermeter[4];//目标设备水平每米像素个数
	char ciypelspermeter[4];//目标设备垂直每米像素个数
	char ciclrused[4];//位图实际使用的颜色表的颜色数
	char ciclrimportant[4];//重要的颜色索引个数
} bitmap_infoheader_t;//

int draw_bmp(global_t * global, const char * pathbmp);

#endif

