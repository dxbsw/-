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
#ifndef __LQ_TIMER_H_
#define __LQ_TIMER_H_
#include "include.h"
extern float BalDirgyro_out;
extern float BALANCE_OUT;
extern float BalDir_out;
extern float SPEED_OUT;
typedef enum
{
  TIMER_1,//����ͷ��
  TIMER_2,//��������2
  TIMER_3,//��������3	
  TIMER_4,//��������4
  TIMER_5,//�����	
  TIMER_6,//��ʱ����
  TIMER_7,//��ʱ����,pid��
  TIMER_8,//�����
}TIMER_Name_t;
extern const u32 TIMERx[] ;
extern TIM_TypeDef *TIMERxP[8];
void TIM1_Int_Init(u16 x100us);
void TIMER_InitConfig(TIMER_Name_t timern, u16 nms);
void Test_TimerPIT56(void);

void kongzhi_1(void);//����
void kongzhi_2(void);
#endif
