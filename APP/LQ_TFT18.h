/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@��    д������Ƽ�
@E-mail  ��chiusir@163.com
@����IDE��IAR7.8 KEIL5.24�����ϰ汾
@ʹ��ƽ̨�������������ܿƼ�F3277���İ��ĸ��
@SYS  PLL��120MHz Ƶ��̫�߿����޷�����system_mm32f327x.c
@�����£�2022��02��22�գ��������£����ע���°棡
@���ܽ��ܣ�
@�����Ϣ�ο����е�ַ
@��    վ��http://www.lqist.cn
@�Ա����̣�http://longqiu.taobao.com
@
@����汾��V1.0 ��Ȩ���У���λʹ��������ϵ��Ȩ
@����������Ƶ��ַ��https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_SGP18T_TFTSPI_H__
#define __LQ_SGP18T_TFTSPI_H__	

#include "stdint.h"
#include "include.h"

//��Ļ Ӳ��/���SPI�л�(1��Ӳ���� 0�����)
#define use_heard_spi 1

/*******************�ӿڶ���******************************/

#define APP_LCD_WIDTH  LCD_WIDTH//Һ�������
#define APP_LCD_HEIGHT LCD_HEIGHT//Һ�����߶�

#define TFT18W        162         //��Ļ���
#define TFT18H        132         //��Ļ�߶�

#define u16RED		      0xf800    //��ɫ
#define u16GREEN	      0x07e0    //��ɫ
#define u16BLUE	        0x001f    //��ɫ
#define u16PURPLE	      0xf81f    //��ɫ
#define u16YELLOW	      0xffe0    //��ɫ
#define u16CYAN	        0x07ff 		//����ɫ
#define u16ORANGE	      0xfc08    //��ɫ
#define u16BLACK	      0x0000    //��ɫ
#define u16WHITE	      0xffff    //��ɫ
void TFTSPI_Init(unsigned short type);
void TFTSPI_Write_Cmd(unsigned short cmd);
void TFTSPI_Write_Byte(unsigned short dat);
void TFTSPI_Write_Word(unsigned short dat);
void TFTSPI_Set_Pos(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye);
void TFTSPI_Fill_Area(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color);
void TFTSPI_CLS(unsigned short color);
void TFTSPI_Draw_Part(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);
void TFTSPI_Draw_Rectangle(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);
void TFTSPI_Draw_Circle(unsigned short x,unsigned short y,unsigned short r,unsigned short color_dat);
void TFTSPI_Draw_Line(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,unsigned short color_dat);
void TFTSPI_Draw_Dot(unsigned short x,unsigned short y,unsigned short color_dat);
void TFTSPI_Show_Pic(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye,const unsigned char *ppic);
void TFTSPI_P6X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);
void TFTSPI_P8X8Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);
void TFTSPI_P8X16Str(unsigned short x, unsigned short y, char *s_dat,unsigned short word_color,unsigned short back_color);
void TFTSPI_P16x16Str(unsigned short x, unsigned short y, unsigned char *s_dat,unsigned short word_color,unsigned short back_color);
void TFTSPI_Show_Pic2(unsigned short xs,unsigned short ys,unsigned short w,unsigned short h,const unsigned char *ppic) ;
void TFTSPI_Show_Battery_Icon(void);
void TFTSPI_Show_Title(void);
void TFTSPI_Show_Logo(unsigned short xs,unsigned short ys);
void TFTSPI_Road( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
void TFTSPI_BinRoad( unsigned short wide_start, unsigned short high_start,unsigned short high, unsigned short wide, unsigned char *Pixle);
void TFTSPI_BinRoad2(unsigned short wide_start, unsigned short high_start, unsigned short high, unsigned short wide);
void Test_TFT18(void);


#endif /*SGP18T_ILI9163B.h*/
