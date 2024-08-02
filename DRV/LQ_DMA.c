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
#include "hal_rcc.h"
#include "hal_tim.h"

void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1)!=RESET)										
  {
    DMA_ClearFlag(DMA1_FLAG_TC1);        
    LED_Ctrl(LED2,RVS);
  }
}

void DMA1_Channel2_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC2)!=RESET)										
  {
    DMA_ClearFlag(DMA1_FLAG_TC2);												
  }
}

void DMA1_Channel3_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC3)!=RESET)										
  {
    DMA_ClearFlag(DMA1_FLAG_TC3);	
    
  }
}
void DMA1_Channel4_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
  {
    DMA_ClearFlag(DMA1_FLAG_TC4);   
    MT9V034_DMA_CLS();  //�ر�DMA1,�ɼ���־��һ
  }
}
void DMA1_Channel5_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC5)!=RESET)
  {
    DMA_ClearFlag(DMA1_FLAG_TC5);   
    
  }
}
/*************************************************************************
* @brief    ����ͷDMA�����ʼ��
*
* @param    srcStartAddr   ��Դ��ַ IO��ַ
* @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����
* @param    channel        ��DMA����ͨ�� 0-12    ע�� DMA����ͨ����Ҫ��PIX�����ж����ȼ�����һ��
* @param    lqsize          ���ݳ���
* @return   ��
*
* @note     ע�� DMA����ͨ����Ҫ��PIX�����ж����ȼ�����һ��
*
* @see      DMA_CameraInitConfig((unsigned long)(&MODULE_P02.IN.U), (unsigned long)Image_Data, PIN_INT2_PRIORITY);
*
* @date     2020/4/8
*************************************************************************/
void DMA_CameraInitConfig(DMA_Channel_TypeDef* dma_ch,u32 srcStartAddr, u32 dstStartAddr, u32 lqsize)
{
  DMA_InitTypeDef DMA_InitStructure;  
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA1���߳�ʼ��  
  
  DMA_DeInit(dma_ch);

  //MDA���ó�ʼ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = srcStartAddr;                //Դ��ַ��DMA�����ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = dstStartAddr;                    //Ŀ���ַ��DMA�ڴ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //����(�����赽�ڴ�)��������Ϊ���ݴ������Դ
  DMA_InitStructure.DMA_BufferSize = lqsize;                              //ָ��DMAͨ����DMA����Ĵ�С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //�����ַ�̶�
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //�ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //����ÿ�δ���һ���ֽ�
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //�ڴ�ÿ�δ���һ���ֽ�
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           //��ѭ��ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 //���ȼ����
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //��ֹ�ڴ浽�ڴ�Ĵ���
  DMA_InitStructure.DMA_Auto_reload = DMA_Auto_Reload_Enable;             //�Զ�����  
  DMA_Init(dma_ch, &DMA_InitStructure);                                   //��ʼ��
  
  DMA_ITConfig(dma_ch, DMA_IT_TC, ENABLE);                                //ʹ�ܴ�������ж�
  nvic_init(MT9V034_DMA_IRQN, 0, 1, ENABLE);                              //�ж�����
  DMA_Cmd(dma_ch, ENABLE);                                                //����DMA1
}

/*************************************************************************
//  @brief      ����ͷGPIO������ʱ����ʼ��
//  @param      timern ��ʱ��
//  @param      pin    ���ź�
* @return   ��
* @see     DMA_CameraTriggerTimerInit(TIMER_1, MT9V034_PCLK_PIN); //GPIO����TIM���Ź̶�
*
* @date     2020/4/8
* �޸Ĵ����ܽţ���Ҫ�޸���Ӧ���ж����õȡ�
*************************************************************************/
void DMA_CameraTriggerTimerInit(TIMER_Name_t timern, GPIO_Name_t pin)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
  
  if(TIMER_1 == timern)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  else if(TIMER_2 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if(TIMER_3 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if(TIMER_4 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  else if(TIMER_5 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM5, ENABLE);
  else if(TIMER_6 == timern)//��Ч
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM6, ENABLE);
  else if(TIMER_7 == timern)//��Ч
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7, ENABLE);
  else if(TIMER_8 == timern)
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8, ENABLE);
  
  //����ʱ�ӹܽŸ���  
  PIN_InitConfig(pin, GPI, 0, GPIO_Mode_IN_FLOATING);  
  GPIO_PinAFConfig((GPIO_TypeDef *)(PORTX[(pin&0x00F0) >> 4]),  pin & 0x0F, GPIO_AF1);    
  
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit((TIM_TypeDef*)(TIMERx[timern]), &TIM_TimeBaseStructure);
  
  //TIM_ExtTRGPolarity_Inverted  //TIM_ExtTRGPolarity_NonInverted
  TIM_ETRClockMode1Config((TIM_TypeDef*)(TIMERx[timern]), TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
  TIM_SelectInputTrigger((TIM_TypeDef*)(TIMERx[timern]), TIM_TS_ETRF);
  TIM_SelectSlaveMode((TIM_TypeDef*)(TIMERx[timern]), TIM_SlaveMode_Reset);  
  TIM_SelectMasterSlaveMode((TIM_TypeDef*)(TIMERx[timern]), TIM_MasterSlaveMode_Enable);
  
  TIM_Cmd((TIM_TypeDef*)(TIMERx[timern]), ENABLE);
  TIM_DMACmd((TIM_TypeDef*)(TIMERx[timern]), TIM_DMA_Trigger, ENABLE);
}

//��ʹ��PE7����
void DMA_CameraTriggerTimer1PE7Init()
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  
  
  PIN_InitConfig(PE7, GPI, 0, GPIO_Mode_IN_FLOATING);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF1);
  
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  //TIM_ExtTRGPolarity_Inverted  //TIM_ExtTRGPolarity_NonInverted
  TIM_ETRClockMode1Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
  TIM_SelectInputTrigger(TIM1, TIM_TS_ETRF);      //External Trigger input
  TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset); // Rising edge of the selected trigger signal (TRGI) re-initializes
                                                  // the counter and triggers an update of the registers.
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);//synchronization between the current timer
                                                              // and its slaves (through TRIG).
  
  TIM_Cmd(TIM1, ENABLE);
  TIM_DMACmd(TIM1, TIM_DMA_Trigger, ENABLE);
}

