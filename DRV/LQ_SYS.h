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
#ifndef __LQ_SYSDELAY_H_
#define __LQ_SYSDELAY_H_
#include "include.h"

#ifdef __CC_ARM	
  #define ALIGN(n) __attribute__((aligned(n)))
#elif defined (__IAR_SYSTEMS_ICC__)  
  #define PRAGMA(x) _Pragma(#x)
  #define ALIGN(n) PRAGMA(data_alignment=n)
#elif defined (__GNUC__) 
  #define ALIGN(n) __attribute__((aligned(n)))
#endif 

#define true 1
#define false 0

extern u32 SystemCoreClock;
void delayus(u16 count);
void delayms(u16 nms);
void LQ_Init3227(void);
void nvic_init(IRQn_Type irqn,u8 pre_prior, u8 sub_prior,u8 status);
void DisableIRQ(IRQn_Type IRQn);
void EnableIRQ(IRQn_Type IRQn);

#endif



