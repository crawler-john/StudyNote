#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "bmp.h"

bitmap_fileheader_t g_fileheader;//文件头14
bitmap_infoheader_t g_infoheader;//信息头40

static unsigned int chartoint(char *string,int len)
{
	unsigned int num;

	if(len<=4)
	{
		memset(&num,0x00,sizeof(int));
		memcpy(&num,string,len);
	}

	return num;
}

static int bmp_open(global_t *global,const char *pathbmp)
{
	FILE *fp = NULL;
	size_t rc = 0;
	unsigned int skip =  4 - ((global->pic_info.wdata*global->pic_info.pbpp)>>3) & 3;

	fp = fopen(pathbmp,"rb");
	if(fp==NULL)
	{
		printf("open %s failed!\n",pathbmp);
		return -1;
	}

	//读取位图文件头
	rc = fread(&g_fileheader,sizeof(bitmap_fileheader_t),1,fp);
	if(rc != 1)
	{
		printf("read bmp file header failed!\n");
		fclose(fp);
		return -2;
	}

	//查看文件是否为位图文件
	if(memcmp(g_fileheader.cftype,"BM",2) !=0)
	{
		printf("it's not a bmp file!\n");
		fclose(fp);
		return -3;
	}

	//读取位图信息头
	rc = fread(&g_infoheader,sizeof(bitmap_infoheader_t),1,fp);
	if(rc != 1)
	{
		printf("read bmp info header failed!\n");
		fclose(fp);
		return -4;
	}

	//将位图信息保存到gloabl结构中
	global->pic_info.wdata = chartoint(g_infoheader.ciwidth,4);
	global->pic_info.hdata = chartoint(g_infoheader.ciheight,4);
	global->pic_info.pbpp = chartoint(g_infoheader.cibitcount,2);
	global->pic_info.len = (global->pic_info.wdata*(global->pic_info.pbpp/8)+skip)*global->pic_info.hdata;

	printf("picture info: %u X %u,%ubpp.\n",global->pic_info.wdata,global->pic_info.hdata,global->pic_info.pbpp);

	//移动文件读取指针到图像数据
	fseek(fp,chartoint(g_fileheader.cfoffbits,4),SEEK_SET);
	
	//将图像数据读取到global结构中
	rc = fread(global->pic_info.pdata,sizeof(char),global->pic_info.len,fp);

	if(rc != global->pic_info.len)
	{
		printf("read bmp image data error!\n");
		fclose(fp);
		return -5;
	}

	return 0;
}

int draw_bmp(global_t *global,const char *pathbmp)
{
	int ret;

	ret = bmp_open(global,pathbmp);
	if(ret<0)
	{
		return ret;
	}

	ret = fb_draw(global);

	return ret;
	
}

