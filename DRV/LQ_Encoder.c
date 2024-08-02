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

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

/*************************************************************************
*  �������ƣ�int Read_Encoder(u8 TIMX)
*  ����˵������ȡ����������
*  ����˵����u8 TIMX��ʱ��
*  �������أ���������
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ECPULSE1 = Read_Encoder(3); //���� ĸ���ϱ�����3��С��ǰ��Ϊ��ֵ
*************************************************************************/
int Read_Encoder(u8 TIMX)
{
  int Encoder_TIM;    
  switch(TIMX)
  {
  case 1:  Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;//����ͷ��	
  case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;//������2��
  case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;//������3��	
  case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;//��������
  case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;//�����	
  //case 6:  Encoder_TIM= (short)TIM6 -> CNT;  TIM6 -> CNT=0;break;//��ʱ����
  //case 7:  Encoder_TIM= (short)TIM7 -> CNT;  TIM7 -> CNT=0;break;//��ʱ����
  case 8:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0;break;//�����
  default:  Encoder_TIM=0;
  }
  return Encoder_TIM;
}

int Read_DirEncoder(u8 TIMX)
{
  int Encoder_TIM;    
  switch(TIMX)
  {
  case 1:  Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;//����ͷ��	
  case 2: 
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)){ Encoder_TIM=-abs((short)TIM2 -> CNT);  TIM2 -> CNT=0;}
    else {Encoder_TIM=abs((short)TIM2 -> CNT);  TIM2 -> CNT=0;}
      break;//������2��
    
  case 3:  
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)){ Encoder_TIM=abs((short)TIM3 -> CNT);  TIM3 -> CNT=0;}
    else {Encoder_TIM=-abs((short)TIM3 -> CNT);  TIM3 -> CNT=0;}
      break;//������2��
    
  case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;//��������
  case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;//�����	
  //case 6:  Encoder_TIM= (short)TIM6 -> CNT;  TIM6 -> CNT=0;break;//��ʱ����
  //case 7:  Encoder_TIM= (short)TIM7 -> CNT;  TIM7 -> CNT=0;break;//��ʱ����
  case 8:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0;break;//�����
  default:  Encoder_TIM=0;
  }
  return Encoder_TIM;
}

/*************************************************************************
*  �������ƣ�void Encoder_Init(ENCODER_PIN_enum ap,ENCODER_PIN_enum bp)
*  ����˵������������ʼ��
*  ����˵����ENCODER_PIN_enum ap,ͨ��A����Ӧ�ĵĶ�ʱ�����ܽ�
             ENCODER_PIN_enum bp,ͨ��B����Ӧ�ĵĶ�ʱ�����ܽ�
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��Encoder_Init(TIM4_ENCA_B06,TIM4_ENCB_B07);//����Ҫ�ɶԳ���
*************************************************************************/
void Encoder_Init(ENCODER_PIN_enum ap,ENCODER_PIN_enum bp)
{  
  unsigned char timern =(ap & 0xF000) >>12;  
  
  PIN_AFIO_Init((GPIO_Name_t)(ap &0xFF), GPI, GPI_FL,(GPIO_AF_t)((ap &0xF00)>>8));//���Ÿ��ó�ʼ��
  PIN_AFIO_Init((GPIO_Name_t)(bp &0xFF), GPI, GPI_FL,(GPIO_AF_t)((bp &0xF00)>>8));//���Ÿ��ó�ʼ��

  if(timern==0) 
  {    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  
  }
  else if(timern==7) 
  {   
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8, ENABLE);      
  }
  else
  {
    //RCC->APB1ENR |= ((uint32_t)0x00000001 << (timern-1));// ����TIM2345ʱ��      
    RCC_APB1PeriphClockCmd(0x01U << (timern-1), ENABLE);      
  }

  TIMERxP[timern]->ARR = 0xFFFF;	            //�趨�������Զ���װֵ
  TIMERxP[timern]->PSC = 0;		            //Ԥ��Ƶ��  
  TIMERxP[timern]->CCMR1 |= TIM_CCMR1_CC1S_DIRECTTI;// ���벶��IC1ӳ�䵽TI1
  TIMERxP[timern]->CCMR1 |= TIM_CCMR1_CC2S_DIRECTTI;// ���벶��IC2ӳ�䵽TI2  
  TIMERxP[timern]->SMCR |= TIM_SMCR_SMS_ENCODER3;   // ʹ�ñ�����ģʽΪTI12֧�ִ���-����ı����� ,�ֱ����ѡ��1��2��3 ģʽ
  TIMERxP[timern]->CR1 |= TIM_CR1_UDIS;		    // ��ֹUEV�¼��Ĳ���
  TIMERxP[timern]->CR1 |= TIM_CR1_CEN;              // ��ʱ��ʹ��
}


/*************************************************************************
*  �������ƣ�void EncInit (void)
*  ����˵������������ʼ����������ͳ�ṹ�巽ʽ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��1��
*  ��    ע������4��������
*************************************************************************/
void EncInit (void)
{    
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);//�ܽŸ���AF2
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_2);//�ܽŸ���AF2
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_2);//�ܽŸ���AF2  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_7;//PB4,6,7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//���룬����
  GPIO_Init( GPIOB, &GPIO_InitStructure); 
  
  //������3
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 1;                                        //Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                                      //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     //TIM���ϼ���
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                                //�ظ�������
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);       //��ʼ���ṹ��
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12 , TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽΪTI12֧�ִ���-����ı�����
  TIM_Cmd(TIM3, ENABLE);                                //��ʱ��ʹ��
    
  //������4  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 1;                                        //Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                                      //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     //TIM���ϼ���
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                                //�ظ�������
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);       //��ʼ���ṹ��
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12 , TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽΪTI12֧�ִ���-����ı�����
  TIM_Cmd(TIM4, ENABLE);                                //��ʱ��ʹ��  
	
  //������2
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_1);//�ܽŸ���AF1
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_1); //�ܽŸ���AF1
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           //PA15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//���룬����
  GPIO_Init( GPIOA, &GPIO_InitStructure);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE );
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 1;                                        //Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                                      //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     //TIM���ϼ���
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                                //�ظ�������
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);       //��ʼ���ṹ��
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12 , TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽΪTI12֧�ִ���-����ı�����
  TIM_Cmd(TIM2, ENABLE);   //��ʱ��ʹ��
  //�������ų�ʼ��
  PIN_InitConfig(PB5, GPI, 1,GPIO_Mode_IPU);
  PIN_InitConfig(PB3, GPI, 1,GPIO_Mode_IPU);
  
  
}


/*************************************************************************
*  �������ƣ�void TestEncoder(void)
*  ����˵�������Գ���TFT1.8��ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��
*************************************************************************/
void TestEncoderTFT(void)
{
  char txt[32];
  
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
  TFTSPI_P8X16Str(3, 2,"LQ encoder", u16PURPLE, u16BLACK); // �ַ�����ʾ
  //EncInit();
  Encoder_Init(TIM1_ENCA_E9, TIM1_ENCB_E11);
  Encoder_Init(TIM2_ENCA_A15,TIM2_ENCB_B3);
  Encoder_Init(TIM3_ENCA_B4, TIM3_ENCB_B5);
  Encoder_Init(TIM4_ENCA_B6, TIM4_ENCB_B7);  
  while (1)
  {
    /* ��ȡ������ֵ */ 
    ECPULSE1 = Read_Encoder(1); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    ECPULSE2 = Read_Encoder(2); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ    
    sprintf(txt, "Enc1: %05d;", ECPULSE1);
    TFTSPI_P8X16Str(3, 4, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf(txt, "Enc2: %05d;", ECPULSE2);
    TFTSPI_P8X16Str(3, 5, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ    
    
    ECPULSE1 = Read_Encoder(3); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    ECPULSE2 = Read_Encoder(4); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ    
    sprintf(txt, "Enc3: %05d;", ECPULSE1);
    TFTSPI_P8X16Str(3, 6, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf(txt, "Enc4: %05d;", ECPULSE2);
    TFTSPI_P8X16Str(3, 7, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ    
    UART_PutStr(UART1,txt); 
    LED_Ctrl(LED0, RVS);        //��ƽ��ת,LED��˸
    delayms(200);               //��ʱ�ȴ�
  }
}

void TestEncoderTimerTFT(void)
{
  char txt[32];
  
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
  TFTSPI_P8X16Str(3, 2,"LQ encoder", u16PURPLE, u16BLACK); // �ַ�����ʾ
  Encoder_Init(TIM1_ENCA_E9, TIM1_ENCB_E11);
  Encoder_Init(TIM2_ENCA_A15,TIM2_ENCB_B3);
  Encoder_Init(TIM3_ENCA_B4, TIM3_ENCB_B5);
  Encoder_Init(TIM4_ENCA_B6, TIM4_ENCB_B7); 
  TIMER_InitConfig(TIMER_6, 20);//��������ȡ�жϺ���
  while (1)
  {   
    sprintf(txt, "Enc3: %05d;", ECPULSE1);
    TFTSPI_P8X16Str(3, 6, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    UART_PutStr(UART1,txt); 
    
    sprintf(txt, "Enc4: %05d;", ECPULSE2);    
    TFTSPI_P8X16Str(3, 7, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ    
    UART_PutStr(UART1,txt); 
    LED_Ctrl(LED0, RVS);        //��ƽ��ת,LED��˸
    delayms(200);               //��ʱ�ȴ�
  }
}















/*************************************************************************
*  �������ƣ�void TestEncoder(void)
*  ����˵�������Գ���OLED��ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��
*************************************************************************/
void TestEncoderOLED(void)
{
  char txt[32];
  OLED_Init();
  OLED_CLS();   //����
  OLED_P6x8Str(0, 0, "Test Encoder");      //�ַ�����ʾ
  EncInit();
  while (1)
  {
    /* ��ȡ������ֵ */
    ECPULSE1 = Read_Encoder(3); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    ECPULSE2 = Read_Encoder(4); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ
    
    sprintf(txt, "Enc1: %05d;", ECPULSE1);
    OLED_P6x8Str(0, 3, txt);   //�ַ�����ʾ
    sprintf(txt, "Enc2: %05d;", ECPULSE2);
    OLED_P6x8Str(0, 5, txt);   //�ַ�����ʾ
    
    LED_Ctrl(LED0, RVS);       //��ƽ��ת,LED��˸
    delayms(200);              //��ʱ�ȴ�
  }
}



