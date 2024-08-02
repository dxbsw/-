/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�F3277���İ��ĸ��
����    д������Ƽ�
��E-mail  ��chiusir@163.com
������汾��V1.0 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��12��24�գ��������£����ע���°棡
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��IDE��IAR7.8 KEIL5.24�����ϰ汾
��Target �� MM32F3277
��SYS PLL�� 120MHz Ƶ��̫�߿����޷�����system_mm32f327x.c
=================================================================
����������Ƶ��ַ��https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_Soft_SPI_H_
#define __LQ_Soft_SPI_H_
#include "include.h"

//                            ��Ƭ��    ����20689ģ��
#define Soft_SPI_SCK_PIN      GPIOE,GPIO_Pin_12     //SCK
#define Soft_SPI_MISO_PIN     GPIOE,GPIO_Pin_13     //��Ƭ��MISO��ģ���--SDO
#define Soft_SPI_MOSI_PIN     GPIOE,GPIO_Pin_14     //��Ƭ��MOSI��ģ���--SDI
#define Soft_SPI_CS_PIN       GPIOE,GPIO_Pin_10     //CS Ĭ����PE11,���ʹ�ñ�������������л���PE10

#define Soft_SPI_SCK_OUT_H    GPIO_SetBits(Soft_SPI_SCK_PIN)          //��������ߵ�ƽ
#define Soft_SPI_SCK_OUT_L    GPIO_ResetBits(Soft_SPI_SCK_PIN)        //��������͵�ƽ

#define Soft_SPI_MISO_IN      GPIO_ReadInputDataBit(Soft_SPI_MISO_PIN)//��ȡ�����ϵ�����״̬

#define Soft_SPI_MOSI_OUT_H   GPIO_SetBits(Soft_SPI_MOSI_PIN)        //��������ߵ�ƽ
#define Soft_SPI_MOSI_OUT_L   GPIO_ResetBits(Soft_SPI_MOSI_PIN)      //��������͵�ƽ

#define Soft_SPI_CS_OUT_H     GPIO_SetBits(Soft_SPI_CS_PIN)          //��������ߵ�ƽ
#define Soft_SPI_CS_OUT_L     GPIO_ResetBits(Soft_SPI_CS_PIN)        //��������͵�ƽ

void Soft_SPI_Init(void);
void Soft_SPI_ReadWriteNbyte(unsigned char *lqbuff, unsigned char len);
void LQ_SPI_Read(unsigned char reg, unsigned short len, unsigned char* buf);
void LQ_SPI_Write(unsigned char reg, unsigned short len, unsigned char* buf);
#endif

















