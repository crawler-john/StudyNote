#ifndef _BMP_H_
#define _BMP_H_

#include "fb.h"

//λͼ�ļ��ļ�ͷ14bytes
typedef struct
{
	char cftype[2];//�ļ�����,������'B''M' 0x424d
	char cfsize[4];//�ļ���С
	char cfreserved[4];//����
	char cfoffbits[4];//ͼ����Ϣ�����ļ�ͷ��ƫ����
} bitmap_fileheader_t;

//λͼ�ļ���Ϣͷ40bytes
typedef struct
{
	char cisize[4];//��Ϣͷ�Ĵ�С
	char ciwidth[4];//λͼ�Ŀ��(����)
	char ciheight[4];//λͼ�ĸ߶�
	char ciplanes[2];//λͼƽ����,����Ϊ1
	char cibitcount[2];//ÿ�����ص�λ��1,4,8,24,32
	char cicompress[4];//λͼ��ѹ����ʽ0=��ѹ��
	char cisizeimage[4];//ͼ���С(�ֽ�),������0
	char cixpelspermeter[4];//Ŀ���豸ˮƽÿ�����ظ���
	char ciypelspermeter[4];//Ŀ���豸��ֱÿ�����ظ���
	char ciclrused[4];//λͼʵ��ʹ�õ���ɫ�����ɫ��
	char ciclrimportant[4];//��Ҫ����ɫ��������
} bitmap_infoheader_t;//

int draw_bmp(global_t * global, const char * pathbmp);

#endif

