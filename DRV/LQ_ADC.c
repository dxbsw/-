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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
��е�ѹ�ɼ�ģ��
�Ƽ�ʹ��ADC4--11����8·ADC�����������ų���е�ѹ�ɼ���
��Դ�ɼ���ADC12�� 
=================================================================
MM32F3277
**ADC1:               
**ADC1CH0 : A0      
**ADC1CH1 : A1
**ADC1CH2 : A2          
**ADC1CH3 : A3          
**ADC1CH4 : A4           
**ADC1CH5 : A5
**ADC1CH6 : A6
**ADC1CH7 : A7
**ADC1CH8 : B0
**ADC1CH9 : B1
**ADC1CH10: C0
**ADC1CH11: C1
**ADC1CH12: C2
**ADC1CH13: C3
**ADC1CH14TEMP	// �ڲ��¶ȴ�����
**ADC1CH15VS		// �ڲ��ο���ѹ
**ADC2:
**ADC2CH0 : A0      
**ADC2CH1 : A1
**ADC2CH2 : A2          
**ADC2CH3 : A3          
**ADC2CH4 : A4           
**ADC2CH5 : A5
**ADC2CH6 : A6
**ADC2CH7 : A7
**ADC2CH8 : B0
**ADC2CH9 : B1
**ADC2CH10: C0
**ADC2CH11: C1
**ADC2CH12: C2
**ADC2CH13: C3
**ADC2CH12: C4
**ADC2CH13: C5
**ADC3:
**ADC3CH0 : A0      
**ADC3CH1 : A1
**ADC3CH2 : A2          
**ADC3CH3 : A3          
**ADC3CH4 : F6           
**ADC3CH5 : F7
**ADC3CH6 : F8
**ADC3CH7 : F9
**ADC3CH8 : F10
**ADC3CH9 : B1
**ADC3CH10: C0
**ADC3CH11: C1
**ADC3CH12: C2
**ADC3CH13: C3
**ADC3CH12: C2
**ADC3CH13: C3
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void ADC1Init(ADCCHANNEL_TypeDef ADC_Channel_x)
����  �ܡ� ADC1��ʼ��,����ADC1����ת��ģʽ
������ֵ�� ADC_Channel_x , xΪ0~15
������ֵ�� 
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_CSHigh(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void ADC1Init(ADCCHANNEL_TypeDef ADC_Channel_x)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
  ADC_InitTypeDef  ADC_InitStructure;	
  ADC_StructInit(&ADC_InitStructure);    
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  
  
  if(ADC_Channel_x<8)
  {  
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
  }
  else if(ADC_Channel_x<10)
  {
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x-8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  }    
  else 
  {
    GPIO_InitStructure.GPIO_Pin  =   ADC_Channel_x-10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            
  }  
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//�ֱ���
  //ADC prescale factor
  ADC_InitStructure.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;//ʱ�ӷ�Ƶ
  //Set ADC mode to continuous conversion mode
  ADC_InitStructure.ADC_Mode = ADC_Mode_Continuous_Scan;//����ת��ģʽ
  //AD data right-justified
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_Init(ADC1, &ADC_InitStructure);  
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_x,0, ADC_SampleTime_1_5Cycles);//��������
  
  ADC_Cmd(ADC1, ENABLE);  
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void ADC2Init(ADCCHANNEL_TypeDef ADC_Channel_x)
����  �ܡ� ADC2��ʼ��,����ADC1����ת��ģʽ
������ֵ�� ADC_Channel_x , xΪ0~13
������ֵ�� 
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_CSHigh(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void ADC2Init(ADCCHANNEL_TypeDef ADC_Channel_x)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
  ADC_InitTypeDef  ADC_InitStructure;	
  ADC_StructInit(&ADC_InitStructure);    
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  
  
  if(ADC_Channel_x<8)
  {  
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
  }
  else if(ADC_Channel_x<10)
  {
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x-8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  }    
  else 
  {
    GPIO_InitStructure.GPIO_Pin  =   ADC_Channel_x-10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            
  }  
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//�ֱ���
  //ADC prescale factor
  ADC_InitStructure.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;//ʱ�ӷ�Ƶ
  //Set ADC mode to continuous conversion mode
  ADC_InitStructure.ADC_Mode = ADC_Mode_Continuous_Scan;//����ת��ģʽ
  //AD data right-justified
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_Init(ADC2, &ADC_InitStructure);  
  
  ADC_RegularChannelConfig(ADC2, ADC_Channel_x,0, ADC_SampleTime_1_5Cycles);//��������
  
  ADC_Cmd(ADC2, ENABLE);  
  ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void ADC3Init(ADCCHANNEL_TypeDef ADC_Channel_x)
����  �ܡ� ADC3��ʼ��,����ADC1����ת��ģʽ
������ֵ�� ADC_Channel_x , xΪ0~13
������ֵ�� 
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_CSHigh(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void ADC3Init(ADCCHANNEL_TypeDef ADC_Channel_x)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
  ADC_InitTypeDef  ADC_InitStructure;	
  ADC_StructInit(&ADC_InitStructure);    
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBENR_GPIOF, ENABLE);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  
  
  if(ADC_Channel_x<4)
  {  
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
  }
  else if(ADC_Channel_x<9)
  {
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x+2;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
  } 
  else if(ADC_Channel_x<10)
  {
    GPIO_InitStructure.GPIO_Pin  =  ADC_Channel_x-8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  } 	
  else 
  {
    GPIO_InitStructure.GPIO_Pin  =   ADC_Channel_x-10;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            
  }  
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//�ֱ���
  //ADC prescale factor
  ADC_InitStructure.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;//ʱ�ӷ�Ƶ
  //Set ADC mode to continuous conversion mode
  ADC_InitStructure.ADC_Mode = ADC_Mode_Continuous_Scan;//����ת��ģʽ
  //AD data right-justified
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_Init(ADC3, &ADC_InitStructure);  
  
  ADC_RegularChannelConfig(ADC3, ADC_Channel_x,0, ADC_SampleTime_1_5Cycles);//��������
  
  ADC_Cmd(ADC3, ENABLE);  
  ADC_SoftwareStartConvCmd(ADC3, ENABLE);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC1_Read(uint8_t ADC_Channel_x)
����  �ܡ���ȡADC1ת������
������ֵ��ADC_Channel_x , xΪ0~15
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC1_Read(uint8_t ADC_Channel_x)
{ 
  while(ADC_Channel_x!=(((ADC1->ADDATA) >>16) & 0xf)); //�ҵ���Ӧ��ͨ�� 
  while(!(ADC1->ADSTA&ADC_FLAG_EOC));                  //�ȴ�ת�����  
  return (ADC1->ADDATA&0xfff);                         //��ȡ����
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC2_Read(uint8_t ADC_Channel_x)
����  �ܡ���ȡADC2ת������
������ֵ��ADC_Channel_x , xΪ0~13
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC2_Read(uint8_t ADC_Channel_x)
{ 
  while(ADC_Channel_x!=(((ADC2->ADDATA) >>16) & 0xf)); //�ҵ���Ӧ��ͨ�� 
  while(!(ADC2->ADSTA&ADC_FLAG_EOC));                  //�ȴ�ת�����  
  return (ADC2->ADDATA&0xfff);                         //��ȡ����
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC3_Read(uint8_t ADC_Channel_x)
����  �ܡ���ȡADC3ת������
������ֵ��ADC_Channel_x , xΪ0~13
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC3_Read(uint8_t ADC_Channel_x)
{ 
  while(ADC_Channel_x!=(((ADC3->ADDATA) >>16) & 0xf)); //�ҵ���Ӧ��ͨ�� 
  while(!(ADC3->ADSTA&ADC_FLAG_EOC));                  //�ȴ�ת�����  
  return (ADC3->ADDATA&0xfff);                         //��ȡ����
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC1_Read_Average(uint8_t ADC_Channel_x,uint8_t times)  
����  �ܡ���ȡ����ADC1����ֵ��ƽ��ֵ
������ֵ��ADC_Channel_x , xΪ0~15
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read_Average(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC1_Read_Average(uint8_t ADC_Channel_x,uint8_t times)
{
  u32 temp_val=0;
  u8 t;
  u8 delay;
  for(t=0;t<times;t++)
  {
    temp_val+=ADC1_Read(ADC_Channel_x);
    for(delay=0;delay<100;delay++);
  }
  return temp_val/times;
} 

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC2_Read_Average(uint8_t ADC_Channel_x,uint8_t times)
����  �ܡ���ȡ����ADC2����ֵ��ƽ��ֵ
������ֵ��ADC_Channel_x , xΪ0~13
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read_Average(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC2_Read_Average(uint8_t ADC_Channel_x,uint8_t times)
{
  u32 temp_val=0;
  u8 t;
  u8 delay;
  for(t=0;t<times;t++)
  {
    temp_val+=ADC2_Read(ADC_Channel_x);
    for(delay=0;delay<100;delay++);
  }
  return temp_val/times;
} 

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 ADC3_Read_Average(uint8_t ADC_Channel_x,uint8_t times)
����  �ܡ���ȡ����ADC3����ֵ��ƽ��ֵ
������ֵ��ADC_Channel_x , xΪ0~13
������ֵ��ADC������ֵ
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ vbat=ADC1_Read_Average(ADC_Channel_12);   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 ADC3_Read_Average(uint8_t ADC_Channel_x,uint8_t times)
{
  u32 temp_val=0;
  u8 t;
  u8 delay;
  for(t=0;t<times;t++)
  {
    temp_val+=ADC3_Read(ADC_Channel_x);
    for(delay=0;delay<100;delay++);
  }
  return temp_val/times;
} 

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void Test_ADC(void)
����  �ܡ����Ժ���
������ֵ����
������ֵ����
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ Test_ADC()��//DC���ղ�Ϊ�㣬�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ADC(void)
{
  u16 vbat;
  char txt[16];
  
  ADC1Init(ADC_Channel_4);
  ADC1Init(ADC_Channel_5);
  ADC1Init(ADC_Channel_6);
  ADC2Init(ADC_Channel_7);
  
  ADC2Init(ADC_Channel_8);
  ADC2Init(ADC_Channel_9);
  ADC2Init(ADC_Channel_10);
  ADC2Init(ADC_Channel_11);
  ADC1Init(ADC_Channel_12);
  
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ	
  while(1)
  {
    vbat=ADC1_Read(ADC_Channel_12);   
    vbat = vbat * 11 / 25;  // x/4095*3.3*100*5.7   ��5.7Ϊ 1K+4.7K ��ѹ�����ѹ������
    sprintf(txt, "Bat:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095*3
    TFTSPI_P8X16Str(3, 0, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    UART_PutStr(UART1,txt); 
    
    vbat=ADC1_Read(ADC_Channel_4);   
    sprintf(txt, "ch4:%d", vbat);  // *3.3/4095
    TFTSPI_P8X16Str(3, 1, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    
    vbat=ADC1_Read(ADC_Channel_5);   
    sprintf(txt, "ch5:%d", vbat);  
    TFTSPI_P8X16Str(3, 2, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    vbat=ADC1_Read(ADC_Channel_6);   
    sprintf(txt, "ch6:%d ", vbat);  // *3.3/4095
    TFTSPI_P8X16Str(3, 3, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ

    vbat=ADC2_Read(ADC_Channel_7);   
    sprintf(txt, "ch7:%d ", vbat);  // *3.3/4095*3
    TFTSPI_P8X16Str(3, 4, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    
    vbat=ADC2_Read(ADC_Channel_8);   
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch8:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 5, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    
    vbat=ADC2_Read(ADC_Channel_9);   
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch9%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 6, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    vbat=ADC2_Read(ADC_Channel_10);   
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch10:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 7, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ    
    
    vbat=ADC2_Read(ADC_Channel_11);   
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch11:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 8, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ

    LED_Ctrl(LED0,RVS); 
    delayms(100); 
  }
  
}

