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
#ifndef __LQ_ENC_H_
#define __LQ_ENC_H_
#include "include.h"


typedef enum
{
  //��ʱ��BIT15-12  ����BIT11-8 ����BIT7-4  �ܽ�BIT3-0
  
  TIM1_ENCA_A8 = 0x0108,// AF1 
  TIM1_ENCA_E9 = 0x0149,// AF1 
  TIM1_ENCB_A9 = 0x0109,// AF1 
  TIM1_ENCB_E11= 0x014B,// AF1 
    
  TIM2_ENCA_A0 = 0x1100,// AF1 
  TIM2_ENCA_A5 = 0x1105,// AF1 
  TIM2_ENCA_A15= 0x110F,// AF1  
  TIM2_ENCB_A1 = 0x1101,// AF1 
  TIM2_ENCB_B3 = 0x1113,// AF1 
  
  TIM3_ENCA_A6 = 0x2206,// AF2 
  TIM3_ENCA_B4 = 0x2214,// AF2 
  TIM3_ENCA_C6 = 0x2226,// AF2   
  TIM3_ENCB_A7 = 0x2207,// AF2 
  TIM3_ENCB_B5 = 0x2215,// AF2 
  TIM3_ENCB_C7 = 0x2227,// AF2 
 
  TIM4_ENCA_B6 = 0x3216,// AF2 
  TIM4_ENCA_D12= 0x323C,// AF2   
  TIM4_ENCB_B7 = 0x3217,// AF2 
  TIM4_ENCB_D13= 0x323D,// AF2 
  
  TIM5_ENCA_A0 = 0x4200,// AF2 
  TIM5_ENCB_A1 = 0x4201,// AF2 
  
  TIM8_ENCA_C6 = 0x7326,// AF3 
  TIM8_ENCB_C7 = 0x7327,// AF3 
  
}ENCODER_PIN_enum;


extern volatile int32_t RAllPulse;
extern int16_t ECPULSE1;
extern int16_t ECPULSE2;

void EncInit (void);
void Encoder_Init(ENCODER_PIN_enum ap,ENCODER_PIN_enum bp);
int Read_Encoder(u8 TIMX);
int Read_DirEncoder(u8 TIMX);
void TestEncoderOLED(void);
void TestEncoderTFT(void);
void TestEncoderTimerTFT(void);
#endif

//



