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
#include "include.h"
#include "HAL_gpio.h"

extern GPIO_TypeDef * PORTX[8];

/*************************************************************************
*  �������ƣ�void PWM_PinConfig(PWM_Name_t pch)
*  ����˵�����ܽų�ʼ��
*  ����˵����pch,PWMͨ������Ӧ�ĵĶ�ʱ�����ܽ�
u32 dutyռ�ձ�Ϊ�ٷ�֮duty*100/PWM_DUTY_MAX
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��Set_TIM3PWM_Duty(1��1000);     // ���������PWMΪ12.5Khz��ռ�ձ�Ϊ10%
*************************************************************************/
void PWM_PinConfig(PWM_Name_t pch)
{   
  PIN_AFIO_Init((GPIO_Name_t)(pch &0xFF), GPO, GPO_AFPP,(GPIO_AF_t)((pch &0x700)>>8));//PWM���ų�ʼ��
}

/*************************************************************************
*  �������ƣ�void PWM_InitConfig(PWM_Name_t pch, u32 freq, u32 duty)
*  ����˵�������PWM��ʼ��
*  ����˵����pch,PWMͨ������Ӧ�ĵĶ�ʱ�����ܽ�
u32 dutyռ�ձ�Ϊ�ٷ�֮duty*100/PWM_DUTY_MAX
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��PWM_InitConfig(PWM3_CH1_C6, 50, 5000);   //��ʼ��PWM3 ͨ��1 ʹ������C6 ���PWMƵ��50HZ ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
*************************************************************************/
void PWM_InitConfig(PWM_Name_t pch, u32 freq, u32 duty)
{		
  TIM_TimeBaseInitTypeDef  TIM_StructInit;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  u16 tmduty;                                               //ռ�ձ�ֵ
  u16 tmperiod;                                             //����ֵ
  u16 freq_div = 0;                                         //��Ƶֵ
  
  PWM_PinConfig(pch);   
  
  if((pch >>13) == 0x00)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  //������ʱ��1ʱ��
  else if((pch >>13) == 0x01)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //������ʱ��2ʱ��
  else if((pch >>13) == 0x02)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //������ʱ��3ʱ��
  else if((pch >>13) == 0x03)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM4, ENABLE);     //������ʱ��
  else if((pch >>13) == 0x04)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM5, ENABLE);     //������ʱ��
  else if((pch >>13) == 0x05)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM6, ENABLE);     //������ʱ��
  else if((pch >>13) == 0x06)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7, ENABLE);     //������ʱ��
  else if((pch >>13) == 0x07)
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8, ENABLE);     //������ʱ��
  
  //��ȡϵͳ��Ƶ
  //SystemCoreClock = 8000000 * (((RCC->CFGR >> 18)&0x0F) + 2);		
  
  freq_div = (u16)((SystemCoreClock / freq) >> 15);                //���ٷ�Ƶ
  tmperiod = (u16)(SystemCoreClock/(freq*(freq_div + 1)));         //����
  tmduty = tmperiod * duty / PWM_DUTY_MAX;                         //ռ�ձ�
  
  if(freq_div<1) freq_div=1;
  if(tmperiod<1) tmperiod=1;
  
  //��ʼ��TIM
  TIM_StructInit.TIM_Period = tmperiod - 1;                        //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_StructInit.TIM_Prescaler = freq_div-1;                         //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
  TIM_StructInit.TIM_RepetitionCounter = 0;
  
  //��ʼ��TIM1 PWMģʽ
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                       //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = tmduty;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                //�������:TIM����Ƚϼ���
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;               //�������:TIM����Ƚϼ���
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  
  TIM_TimeBaseInit(((TIM_TypeDef *) TIMERx[pch >>13]), &TIM_StructInit);  //��ʼ��TIMx��ʱ��
  
  if((pch&0x1800>>11) == 0x00)                                                //ͨ��ѡ��
  {
    TIM_OC1Init(((TIM_TypeDef *) TIMERx[pch >>13]), &TIM_OCInitStructure );                       //��ʱ��ͨ��1��ʼ��
    TIM_OC1PreloadConfig(((TIM_TypeDef *) TIMERx[pch >>13]), TIM_OCPreload_Enable);               //��ʱ��Ԥװ������        
  }
  else if((pch&0x1800>>11) == 0x01)
  {
    TIM_OC2Init(((TIM_TypeDef *) TIMERx[pch >>13]), &TIM_OCInitStructure );
    TIM_OC2PreloadConfig(((TIM_TypeDef *) TIMERx[pch >>13]), TIM_OCPreload_Enable);
    
  }
  else if((pch&0x1800>>11) == 0x02)
  {
    TIM_OC3Init(((TIM_TypeDef *) TIMERx[pch >>13]), &TIM_OCInitStructure );
    TIM_OC3PreloadConfig(((TIM_TypeDef *) TIMERx[pch >>13]), TIM_OCPreload_Enable);        
  }
  else if((pch&0x1800>>11) == 0x03)
  {
    TIM_OC4Init(((TIM_TypeDef *) TIMERx[pch >>13]), &TIM_OCInitStructure );
    TIM_OC4PreloadConfig(((TIM_TypeDef *) TIMERx[pch >>13]), TIM_OCPreload_Enable);        
  }
  
  TIM_ARRPreloadConfig(((TIM_TypeDef *) TIMERx[pch >>13]), ENABLE );                                               
  TIM_CtrlPWMOutputs(((TIM_TypeDef *) TIMERx[pch >>13]), ENABLE );
  TIM_Cmd(((TIM_TypeDef *) TIMERx[pch >>13]), ENABLE);   //��ʱ��ʹ��
}

/*************************************************************************
*  �������ƣ�void Set_TIM3PWM_Duty(u8 ch,u16 duty)
*  ����˵�������PWM��ʼ��
*  ����˵����pch,PWMͨ������Ӧ�ĵĶ�ʱ�����ܽ�
u32 dutyռ�ձ�Ϊ�ٷ�֮duty*100/PWM_DUTY_MAX
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��PWM_Set_Duty(PWM3_CH1_PC6, 5000);
*************************************************************************/
void PWM_Set_Duty(PWM_Name_t pch, u32 duty)
{
  switch(pch&0x1800)
  {
  case 0x0000: ((TIM_TypeDef *) TIMERx[pch >>13])->CCR1=duty;break;
  case 0x0800: ((TIM_TypeDef *) TIMERx[pch >>13])->CCR2=duty;break;
  case 0x1000: ((TIM_TypeDef *) TIMERx[pch >>13])->CCR3=duty;break;
  case 0x1800: ((TIM_TypeDef *) TIMERx[pch >>13])->CCR4=duty;break;
  default: break;;
  }  
}

/*************************************************************************
*  �������ƣ�void TIM8PWM_Init(u16 freq, u16 dutyCycle)
*  ����˵�������PWM��ʼ��
*  ����˵����u16 freq, Ҫ�����ں�Ƶ��ԼΪ94M������Ӧ����96M,��׼ȷ
u16 dutyCycle 0--TIM3_PWM_DUTY_MAX 10000��Ӧ0--100%
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��TIM8PWM_Init(100��1500);     // ���������PWMΪ100hz��ռ�ձ�Ϊ1.5ms
*************************************************************************/
void TIM8PWM_Init(u16 freq, u16 dutyCycle)
{
  TIM_TimeBaseInitTypeDef TIM_StructInit;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,GPIO_AF_3); 
  
  //TIM8_CH1
  GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
  
  TIM_TimeBaseStructInit(&TIM_StructInit);
  TIM_StructInit.TIM_Period = SystemCoreClock/freq;
  TIM_StructInit.TIM_Prescaler = 0; //����Ƶ����ƵֵΪ��n+1
  TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_StructInit.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_StructInit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM8, &TIM_StructInit);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = dutyCycle*TIM_StructInit.TIM_Period/PWM_DUTY_MAX;//ռ�ձ�����
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);                    //ֻ����һ��ͨ��
  //TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  //TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  //TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);           //ֻ����һ��ͨ��
  //TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
  //TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
  //TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
  
  TIM_ARRPreloadConfig(TIM8, ENABLE);    
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
  TIM_Cmd(TIM8, ENABLE);   
}
