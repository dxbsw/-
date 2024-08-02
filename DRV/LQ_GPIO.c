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

extern unsigned char Image_Data[IMAGEH][IMAGEW];;
GPIO_TypeDef * PORTX[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

u16 hangcnt=0;
u16 hang=0,lie=0;


void EXTI0_IRQHandler(void)
{
  //���EXTI��·����λ//
  EXTI_ClearFlag(EXTI_Line0);   
  //LED_Ctrl(LED1,RVS);
}

void EXTI1_IRQHandler(void)
{   
  //���EXTI��·����λ//
  EXTI_ClearFlag(EXTI_Line1); 

  MT9V034_DMA_START();   //PG1 ����ͷ��ͬ���ж�    

  LED_Ctrl(LED1,RVS);    //���̵���˸ 
}

// �ɻɹ�A2
void EXTI2_IRQHandler(void)
{
  //���EXTI��·����λ//
  EXTI_ClearFlag(EXTI_Line2); 

  //���ܣ�ͣ�����
  LED_Ctrl(LED1,RVS);
}

void EXTI4_IRQHandler(void)
{
  //���EXTI��·����λ//
  EXTI_ClearFlag(EXTI_Line4);   
  //LED_Ctrl(LED1,RVS);
}

void EXTI9_5_IRQHandler(void)
{ //���EXTI5��·����λ//

#ifdef USETIMER1DMA   
  if(EXTI_GetITStatus(EXTI_Line5))	//��ȡ��Ӧ�ܵ��ж�״̬
  {
    EXTI_ClearFlag(EXTI_Line5);		  //����жϱ�־
  }
  if(EXTI_GetITStatus(EXTI_Line6))
  {
    EXTI_ClearFlag(EXTI_Line6);			
  }
  
  if(EXTI_GetITStatus(EXTI_Line7))    //�����ź�		
  {    	    
    EXTI_ClearFlag(EXTI_Line7); 
    
  } 
  if(EXTI_GetITStatus(EXTI_Line8))  	
  {
    EXTI_ClearFlag(EXTI_Line8);     
  }
#else  
  //���ж�  
  EXTI_ClearFlag(EXTI_Line8); 
  if(hang%2==0)
  {
    for(lie=0;lie<LCDW;lie++)
    {
      Image_Data[hangcnt][lie]=(u8)(GPIOF->IDR);
    }
    if(++hangcnt>LCDH)
    {
      hangcnt=LCDH;
      Camera_Flag=1;
    }
  }
  ++hang;
  
#endif  
  
//  {
//    EXTI_ClearFlag(EXTI_Line9);			
//  }  	
//  
//  LED_Ctrl(LED1,RVS);
}

void EXTI10_15_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line10))	//��ȡ��Ӧ�ܵ��ж�״̬			
  {
    EXTI_ClearFlag(EXTI_Line10);    //����жϱ�־
  }
  if(EXTI_GetITStatus(EXTI_Line11))
  {
    EXTI_ClearFlag(EXTI_Line11);	
  }
  if(EXTI_GetITStatus(EXTI_Line12))		
  {
    EXTI_ClearFlag(EXTI_Line12);		
  }
  if(EXTI_GetITStatus(EXTI_Line13))	
  {
    EXTI_ClearFlag(EXTI_Line13);		
  }
  if(EXTI_GetITStatus(EXTI_Line14))	
  {
    EXTI_ClearFlag(EXTI_Line14);		
  }
  if(EXTI_GetITStatus(EXTI_Line15))	
  {
    EXTI_ClearFlag(EXTI_Line15);		
  }
  //LED_Ctrl(LED1,RVS);
}

/*************************************************************************
*  �������ƣ�void PIN_InitConfig(GPIO_Name_t pin, GPIO_DIR_t dir, unsigned char dat,unsigned short pinconf)
*  ����˵����GPIO��ʼ������
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���
*            dir     �� GPIO ģʽ   lq_gpio.h�еĺ궨����ѡ��
*            output   �� ���ģʽʱ�������ƽ 1���ߵ�ƽ  0���͵�ƽ
*            u32 pinconf :�ܽ�����,�ο�ch32v10x_gpio.h�е�ö��GPIO_Mode_AF_PP��
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ���� PIN_InitConfig(PA3, GPO, 1,GPIO_Mode_Out_PP);  //PA3��ʼ��������� �ߵ�ƽ
*************************************************************************/
void PIN_InitConfig(GPIO_Name_t pin, GPIO_DIR_t dir, unsigned char dat,unsigned short pinconf)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  u8 port_index = pin >> 4;
  
  //GPIO A--H����ʱ��ʹ��  
  RCC_AHBPeriphClockCmd(0xFF, ENABLE);
  
  //���ùܽ�����
  GPIO_InitStructure.GPIO_Pin = (u16)(1 << (pin & 0x0F));
  
  if(GPO == dir)
  {  //����GPIO�ٶ�
    if((u16)pinconf >> 8 == 0) GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)(GPIO_Speed_50MHz);  //��ֹû����д�������,Ĭ������50Mhz
    else GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)((u16)pinconf >> 8);                       //�Ѿ���д�˸ò���������ֵ������
  }
  
  //����ģʽ �����롢��������������á����ա�AD��
  GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)((u16)pinconf & 0xff);
  GPIO_Init((GPIO_TypeDef *)(PORTX[port_index]), &GPIO_InitStructure);
  
  if(GPO == dir)//��������ߵ͵�ƽ���ߵ�ƽĬ�ϣ���Ϊ����ڲ�����
  {
    GPIO_WriteBit((GPIO_TypeDef *)(PORTX[port_index]), (u16)(1 << (pin & 0x0F)), (BitAction)dat);
  }
}
/*************************************************************************
*  �������ƣ�void PIN_AFIO_Init(GPIO_Name_t pin, GPIO_MODE_enum mode,GPIO_AF_t af)
*  ����˵����GPIO���ܸ��ó�ʼ������
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���
*            dir     �� GPIO ģʽ  
*            GPIO_MODE_enum mode�� GPIO ģʽ   lq_gpio.h�еĺ궨����ѡ��
*            GPIO_AF_t af�ܽ�����,�ο�_gpio.h�е�ö��GPIO_Mode_AF_PP��
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ���� PIN_InitConfig(PA3, GPO, 1,GPIO_Mode_Out_PP);  //PA3��ʼ��������� �ߵ�ƽ
*************************************************************************/
void PIN_AFIO_Init(GPIO_Name_t pin, GPIO_DIR_t dir,GPIO_MODE_enum mode,GPIO_AF_t af)
{
  unsigned char port_index =(pin&0xF0)>>4;	
  unsigned char pin_index = pin&0x0F;	  
  
  RCC->AHBENR |= RCC_AHBENR_GPIOA << port_index;
  
  if(pin_index < 8)// ��8λ�ܽ�
  {
    PORTX[port_index]->CRL &= ~(0x0000000f << (pin_index*4));		
    PORTX[port_index]->CRL |= (((u32)dir|(u32)mode) << (pin_index*4));					
    PORTX[port_index]->AFRL &= ~(0x0000000f << (pin_index*4));	
    PORTX[port_index]->AFRL |= ((u32)af << (pin_index*4));		 
  }
  else	// ��8λ�ܽ�
  {
    PORTX[port_index]->CRH &= ~(0x0000000f << ((pin_index-8)*4));			
    PORTX[port_index]->CRH |= (((u32)dir|(u32)mode) << ((pin_index-8)*4));				
    PORTX[port_index]->AFRH &= ~(0x0000000f << ((pin_index-8)*4));			
    PORTX[port_index]->AFRH |= ((u32)af << ((pin_index-8)*4));				
  }
}
/*************************************************************************
*  �������ƣ�unsigned char PIN_Read(GPIO_Name_t pin)
*  ����˵������ȡGPIO��ƽ����
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���*
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ����uint8_t pinState = PIN_Read(PA2);  //��ȡPA2 �ĵ�ƽ״̬
*************************************************************************/
unsigned char PIN_Read(GPIO_Name_t pin)
{
  if((((GPIO_TypeDef *)(PORTX[pin>>4]))->IDR & (1<<((pin & 0x0F)))) != 0)
  {
    return 1;
  }
  return 0;
}

/*************************************************************************
*  �������ƣ�void PIN_Write(GPIO_Name_t pin, BitAction dat)
*  ����˵��������GPIO���״̬
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���*
*            dat   �� ���ģʽʱ�������ƽ 1���ߵ�ƽ  0���͵�ƽ
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ����PIN_Write(PE0, 1);//PE0��Ϊ�ߵ�ƽ
*************************************************************************/
void PIN_Write(GPIO_Name_t pin, BitAction dat)
{
  if (dat == 1)
    ((GPIO_TypeDef *)(PORTX[pin>>4]))->BSRR = (1<<((pin & 0x0F)));
  else
    ((GPIO_TypeDef *)(PORTX[pin>>4]))->BRR = (1<<((pin & 0x0F)));
}

/*************************************************************************
*  �������ƣ�void PIN_Reverse(GPIO_Name_t pin)
*  ����˵����GPIO��ƽ��ת������ʹ��ǰ���ȳ�ʼ��
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���*
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ����PIN_Reverse(P00_0); //��תP00_0�ܽŵĵ�ƽ״̬
*************************************************************************/
void PIN_Reverse(GPIO_Name_t pin)
{
  ((GPIO_TypeDef *)(PORTX[pin>>4]))->ODR ^= (u16)(1<<((pin & 0x0F)));
}

/*************************************************************************
*  �������ƣ�void PIN_Dir(PIN_enum pin, GPIO_DIR_t dir)
*  ����˵����GPIO��ʼ������
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���
*            dir     �� GPIO ģʽ   lq_gpio.h�еĺ궨����ѡ��*            
*            
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ���� PIN_Dir(PA3, GPO);  //PA3��ʼ��������� �ߵ�ƽ
*************************************************************************/
void PIN_Dir(GPIO_Name_t pin, GPIO_DIR_t dir)
{
  unsigned char port_index = ((pin&0xf0)>>4);		                        // ��ȡGPIO����
  unsigned char pin_index = (pin&0x0F);					// ��ȡGPIO����
  if(pin_index < 0x08)								          // ��8λ
  {
    PORTX[port_index]->CRL &= ~(0x0000000f << (pin_index*4));			// ���
    PORTX[port_index]->CRL |= ((u32)dir << (pin_index*4));			// ��λ
  }
  else// ��8λ
  {
    PORTX[port_index]->CRH &= ~(0x0000000f << ((pin_index-8)*4));		// ���
    PORTX[port_index]->CRH |= ((u32)dir << ((pin_index-8)*4));			// ��λ
  }
}

/*************************************************************************
*  �������ƣ�void PIN_Exti(GPIO_Name_t pin, EXTITrigger_TypeDef edge,u32 pinconf,unsigned char prior, unsigned char sub_prior)
*  ����˵����GPIO�ⲿ�жϳ�ʼ��
*  ����˵����pin      �� �ܽű��    lq_gpio.h�ж���
*            dir     �� GPIO ģʽ   lq_gpio.h�еĺ궨����ѡ��*
*            u32 pinconf :�ܽ�����,�ο�ch32v10x_gpio.h�е�ö��GPIO_Mode_AF_PP��
*            unsigned char prior �ж����ȼ�
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ����PIN_Exti(PA2, EXTI_Trigger_Falling,GPIO_Mode_IPU);//����PA2�½��ش����ж�
*  ��    ע��
*************************************************************************/
void PIN_Exti(GPIO_Name_t pin, EXTITrigger_TypeDef edge,u32 pinconf,unsigned char prior, unsigned char sub_prior)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  
  GPIO_PinAFConfig((GPIO_TypeDef *)(PORTX[pin>>4]), (pin & 0x0F), GPIO_AF_0);  
  
  PIN_InitConfig(pin, GPI, 0, pinconf);
  SYSCFG_EXTILineConfig(pin>>4, (pin & 0x0F));            //�ܽ��жϺ�����
  EXTI_InitStructure.EXTI_Line = 1<<((pin & 0x0F));       //�ܽź�����
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //����ģʽ
  EXTI_InitStructure.EXTI_Trigger = edge;                 //������ʽ
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;               //ʹ�ܻ���ʧ��
  EXTI_Init(&EXTI_InitStructure);
  
  // �жϷ���
  if((pin&0x0F) < 1)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;								
  else if((pin&0x0F) < 2)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;									
  else if((pin&0x0F) < 3)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  else if((pin&0x0F) < 4)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  else if((pin&0x0F) < 5)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;									
  else if((pin&0x0F) < 10)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;								
  else
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  
  //���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = prior;  
  //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_prior;							
  //ʹ���ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���//
  NVIC_Init(&NVIC_InitStructure);
  
}
