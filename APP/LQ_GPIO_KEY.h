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
#ifndef __LQ_KEY_H_
#define __LQ_KEY_H_

#include "include.h"

//����ģ���
typedef enum
{
  KEY0 = 0,  //ĸ���ϰ���0
  KEY1 = 1,
  KEY2 = 2,
  DSW0 = 3,    //ĸ���ϲ��뿪��0
  DSW1 = 4,
} KEYn_e;

typedef enum
{
  LOW = 0,  //����
  HIGH = 1, //�ɿ�
  FAIL = 0xff, //����
} KEYs_e;

//����Ĺܽ�Ҫ��Ӧʵ�ʰ���
#define KEY0p      PD4//GPIOD,GPIO_Pin_4   //ĸ���ϰ���0
#define KEY1p      PD2//GPIOD,GPIO_Pin_2   //ĸ���ϰ���1
#define KEY2p      PD3//GPIOD,GPIO_Pin_3   //ĸ���ϰ���2
#define DSW0p      PD0//GPIOD,GPIO_Pin_0   //ĸ���ϲ��뿪��0,Ĭ�ϲ����·��Ǹߵ�ƽ���Ϸ�Ϊ�͵�ƽ
#define DSW1p      PD1//GPIOD,GPIO_Pin_1  //ĸ���ϲ��뿪��1
#define REEDp      GPIOA,GPIO_Pin_2   //ĸ���ϸɻɹ�
/*********************** UART���ܺ��� **************************/
//��ʼ��
void GPIO_KEY_Init (void);
int KEY_Read_All (void);
/*************************************************************************
*  �������ƣ�void Reed_Init(void)
*  ����˵�����ɻɹ�GPIO���жϳ�ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��21��
*  ��    ע��   �ж����Ǹ��˳�ʼ�����ж�VECTABNUM�ű����Ӧ��cpu,���򲻻�����жϺ���
*          �жϷ�����PIN_INT0_IRQHandler��LQ_GPIO.c��
*************************************************************************/
void Reed_Init(void);
u8 KEY_Scan(u8 mode);
unsigned char KEY_Read(KEYn_e KEYno);


#endif/* 0_APPSW_TRICORE_APP_LQ_ASC_H_ */
