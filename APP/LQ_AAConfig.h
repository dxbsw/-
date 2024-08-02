#ifndef __LQ_AAConfig_H__
#define __LQ_AAConfig_H__
#include "include.h"

//#define USEOLED        //ʹ��OLED����TFT1.8ģ�飬Ĭ��ΪTFT1.8
#define USETFT           //Ĭ��ΪTFT1.8

#define USE_SOFT_SPI //ʹ��ģ��SPI,Ӳ��SPI��ͨ

//#define LQ_ICM20689_I2CDMP 
//#define LQ_ICM20689_SPIDMP
//#define USEMPU6050DMP  


#define USETIMER1DMA     //��������ʹ��DMA���䣬�رմ�����ʹ�ô��е��жϷ�ʽ�ɼ�

#define LQMT9V034        //Ĭ��Ϊ��������ͷ
#define USELQMT9V034     //ʹ����������ͷ

#define IMAGEH  MT9V034_IMAGEH   //����ͷ�ɼ��߶�
#define IMAGEW  MT9V034_IMAGEW   //����ͷ�ɼ����

// UART Printf Definition
#define DEBUG_UART1    1
#define DEBUG_UART2    2
#define DEBUG_UART3    3

// DEBUG UATR Definition
#define DEBUG   DEBUG_UART1
// #define DEBUG   DEBUG_UART2
// #define DEBUG   DEBUG_UART3


//GPIO�Ĵ��������궨��
#define GPIO_IDR_ADDR(p)	(0x40040008 + ((p&0xf0)>>4)*0x400 + (p&0x0f))
#define GPIO_ODR_ADDR(p)	(0x4004000C + ((p&0xf0)>>4)*0x400 + (p&0x0f))
#define GPIO_BSRR_ADDR(p)	(0x40040010 + ((p&0xf0)>>4)*0x400 + (p&0x0f))
#define GPIO_BRR_ADDR(p)	(0x40040014 + ((p&0xf0)>>4)*0x400 + (p&0x0f))


 
#endif









