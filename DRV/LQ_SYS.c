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
#include <stdint.h>

/********************************************************************************************************
**������Ϣ ��void delayms(u16 nms)    
**�������� ����ʱnms
**������� ��nms
**������� ��
**    ��ע ��SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK,72M������,nms<=1864 
********************************************************************************************************/
void delayus(u16 nus)
{
  u32 temp=SystemCoreClock/1000000;
  SysTick->CTRL = 0x0;                                                        //disable systick function
  SysTick->LOAD = nus *temp;                                                  //time nus for 1us with HSI as SYSCLK
  SysTick->VAL = 0x00;                                                        //clear counter
  SysTick->CTRL = 0x5;                                                        //start discrease with Polling
  do {
    temp = SysTick->CTRL;
  } while((temp & 0x01) && !(temp & (1 << 16)));                             //wait time nus done
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                                  //Close Counter
  SysTick->VAL = 0X00;                                                        //clear counter
}

void delayms(u16 nms)
{
  while(nms--)
  {
    delayus(1000);    
  }
}

/*************************************************************************
*  �������ƣ�void nvic_init(IRQn_Type irqn,u8 pre_prior, u8 sub_prior,u8 status)
*  ����˵�����жϳ�ʼ��
*  ����˵����//  
//  @param      irqn              �жϺţ����Բ鿴CH32V10x.h�ļ��е�IRQn_Typeö���嶨��
//  @param      pre_prior         ��ռ���ȼ�,ֵԽС���ȼ�Խ��
//  @param      sub_prior         �����ȼ�,ֵԽС���ȼ�Խ��
//  @param      status            ʹ�ܻ��߽�ֹ
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��    nvic_init(EXTI0_IRQn,1, 0, ENABLE); //�ⲿ�ж�1ʹ��,��ռ���ȼ��θߣ������ȼ���ߡ�
*************************************************************************/
void nvic_init(IRQn_Type irqn,u8 pre_prior, u8 sub_prior,u8 status)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = irqn;                        //�жϺ�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=pre_prior;   //��ռ���ȼ�,ֵԽС���ȼ�Խ��  		
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_prior;        //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = (FunctionalState)status;  //ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���//
}

/**
\brief   Disable Interrupt
\details Disables a device specific interrupt in the NVIC interrupt controller.
\param [in]      IRQn  Device specific interrupt number.
\note    IRQn must not be negative.
*/
void DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0) {
    NVIC->ICER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}
/**
\brief   Enable Interrupt
\details Enables a device specific interrupt in the NVIC interrupt controller.
\param [in]      IRQn  Device specific interrupt number.
\note    IRQn must not be negative.
*/
void EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0) {
    NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
  }
}
/********************************************************************************************************
**������Ϣ ��void delay_init(void)                         
**�������� ����ʼ���ӳٺ���
**������� ��
**������� ��
**���ú��� ��
********************************************************************************************************/
void LQ_Init3227(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  RCC_AHBPeriphClockCmd(0xFF, ENABLE);//����PORTA--G��ʱ��  
  NVIC_SetPriority(SysTick_IRQn, 0x00);					                              
}