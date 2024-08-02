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
#ifndef __LQ_PWM_H_
#define __LQ_PWM_H_
#include "include.h"

#define PWM_DUTY_MAX  10000

typedef enum
{ //��ʱ��BIT15-13 ͨ��BIT12-11  ����BIT10-8 ����BIT7-4  �ܽ�BIT3-0
  PWM1_CH1_PA8	= 0x0108,// 000 00  001   0000  1000
  PWM1_CH1_PE9	= 0x0149,// 000 00  001   0100  1001  
  PWM1_CH2_PA9	= 0x0909,// 000 01  001  
  PWM1_CH2_PE11	= 0x094B,// 000 01  001  
  PWM1_CH3_PA10	= 0x110A,// 000 10  001 
  PWM1_CH3_PE13	= 0x114D,
  PWM1_CH4_PA11	= 0x190B,// 000 11  001 	
  PWM1_CH4_PE14	= 0x194E,	
  
  PWM2_CH1_PA0	= 0x2100,//001 00 001 TIMER2 CH1 AF1	
  PWM2_CH1_PA5	= 0x2105,//001 00 001	
  PWM2_CH1_PA15	= 0x210F,//001 00 001  
  PWM2_CH2_PA1	= 0x2901,//001 01 001	������	
  PWM2_CH2_PB3	= 0x2913,//001 01 001  
  PWM2_CH3_PA2	= 0x3102,//001 10 001
  PWM2_CH3_PB10	= 0x311A,//001 10 001
  PWM2_CH4_PA3	= 0x3903,//001 11 001	
  PWM2_CH4_PB11	= 0x391B,//001 11 001	
  
  PWM3_CH1_PA6	= 0x4206,//010 00 010 TIMER3 CH1 AF2
  PWM3_CH1_PB4	= 0x4214,//010 00 010	
  PWM3_CH1_PC6	= 0x4226,//010 00 010 	  
  PWM3_CH2_PA7	= 0x4A07,//010 01 010 	
  PWM3_CH2_PB5	= 0x4A15,//010 01 010 	
  PWM3_CH2_PC7	= 0x4A27,//010 01 010 
  PWM3_CH3_PB0	= 0x5210,//010 10 010
  PWM3_CH3_PC8	= 0x5228,//010 10 010 
  PWM3_CH4_PB1	= 0x5A11,//010 11 010 
  PWM3_CH4_PC9	= 0x5A29,//010 11 010     
  
  PWM4_CH1_PB6	= 0x6216,//011 00 010 TIMER4 CH1 AF2	
  PWM4_CH1_PD12	= 0x623C,//011 00 010
  PWM4_CH2_PB7	= 0x6A17,//011 01 010
  PWM4_CH2_PD13	= 0x6A3D,//011 01 010
  PWM4_CH3_PB8	= 0x7218,//011 10 010
  PWM4_CH3_PD14	= 0x723E,//011 10 010
  PWM4_CH4_PB9	= 0x7A19,//011 11 010
  PWM4_CH4_PD15	= 0x7A3F,//011 11 010
  
  PWM5_CH1_PA0	= 0x8200,//100 00 010 TIMER5 CH1 AF2
  PWM5_CH2_PA1	= 0x8A01,//100 01 010
  PWM5_CH3_PA2	= 0x9202,//100 10 010
  PWM5_CH4_PA3	= 0x9A03,//100 11 010
  
  PWM8_CH1_PC6	= 0xE326,//111 00 011 TIMER8 CH1 AF3	
  PWM8_CH2_PC7	= 0xEB27,//111 01 011
  PWM8_CH3_PC8	= 0xF328,//111 10 011	
  PWM8_CH4_PC9	= 0xFB29,//111 11 011
  
}PWM_Name_t;
void PWM_PinConfig(PWM_Name_t pch);
void PWM_InitConfig(PWM_Name_t pch, u32 freq, u32 duty);
void PWM_Set_Duty(PWM_Name_t pch, u32 duty);
void TIM8PWM_Init(u16 freq, u16 dutyCycle);
void Set_TIM8PWM_Duty(u8 ch,u16 duty);
#endif



