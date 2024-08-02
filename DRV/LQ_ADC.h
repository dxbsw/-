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
#ifndef __LQ_ADC_H_
#define __LQ_ADC_H_

#include "include.h"
#include "hal_adc.h"
#include "hal_rcc.h"

/* ADC Software start mask */
#define CTLR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define CTLR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)

void ADC1Init(ADCCHANNEL_TypeDef ADC_Channel_x);
u16 ADC1_Read(uint8_t ADC_Channel_x);
u16 ADC1_Read_Average(uint8_t ADC_Channel_x,uint8_t times);

void ADC2Init(ADCCHANNEL_TypeDef ADC_Channel_x);
u16 ADC2_Read(uint8_t ADC_Channel_x);
u16 ADC2_Read_Average(uint8_t ADC_Channel_x,uint8_t times);

void ADC3Init(ADCCHANNEL_TypeDef ADC_Channel_x);
u16 ADC3_Read(uint8_t ADC_Channel_x);
u16 ADC3_Read_Average(uint8_t ADC_Channel_x,uint8_t times);

void Test_ADC(void);

#endif
//



