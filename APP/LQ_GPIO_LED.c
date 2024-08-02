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

/*************************************************************************
*  �������ƣ�void LED_Init(void)
*  ����˵����GPIO��ʼ������ LED������PB12��PA4��PC13��PC14��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void GPIO_LED_Init(void)
{
  /*
  // �׿��
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOE|RCC_AHBENR_GPIOF, ENABLE);  
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  */
  //��װ��
  PIN_InitConfig(PE0, GPO, 1,GPIO_Mode_Out_PP);
  PIN_InitConfig(PE1, GPO, 1,GPIO_Mode_Out_PP);
  PIN_InitConfig(PF10, GPO, 1,GPIO_Mode_Out_PP);
  PIN_InitConfig(PF14, GPO, 1,GPIO_Mode_Out_PP);  
}

/*************************************************************************
*  �������ƣ�void LED_Ctrl(LEDn_e LEDno, LEDs_e sta)
*  ����˵����LED����
*  ����˵����LEDn_e LEDno���,LEDs_e sta״̬��/��/��ת
*  �������أ�����״̬��0/1
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void LED_Ctrl(LEDn_e LEDno, LEDs_e sta)
{
  switch(LEDno)
  {
  case LED0:
    if(sta==ON)        GPIO_ResetBits(LED0p);
    else if(sta==OFF)  GPIO_SetBits(LED0p);
    else if(sta==RVS) (GPIO_ReadOutputDataBit(LED0p))?(GPIO_ResetBits(LED0p)):(GPIO_SetBits(LED0p));
    break;
    
  case LED1:
    if(sta==ON)        GPIO_ResetBits(LED1p);
    else if(sta==OFF)  GPIO_SetBits(LED1p);
    else if(sta==RVS) (GPIO_ReadOutputDataBit(LED1p))?(GPIO_ResetBits(LED1p)):(GPIO_SetBits(LED1p));
    break;
    
  case LED2:
    if(sta==ON)        GPIO_ResetBits(LED2p);
    else if(sta==OFF)  GPIO_SetBits(LED2p);
    else if(sta==RVS) (GPIO_ReadOutputDataBit(LED2p))?(GPIO_ResetBits(LED2p)):(GPIO_SetBits(LED2p));
    break;
    
  case LED3:
    if(sta==ON)        GPIO_ResetBits(LED3p);
    else if(sta==OFF)  GPIO_SetBits(LED3p);
    else if(sta==RVS) (GPIO_ReadOutputDataBit(LED3p))?(GPIO_ResetBits(LED3p)):(GPIO_SetBits(LED3p));
    break;
  case LEDALL:
    if(sta==ON)
    {
      GPIO_ResetBits(LED0p);
      GPIO_ResetBits(LED1p);
      GPIO_ResetBits(LED2p);
      GPIO_ResetBits(LED3p);
    }
    else if(sta==OFF)
    {
      GPIO_SetBits(LED0p);
      GPIO_SetBits(LED1p);
      GPIO_SetBits(LED2p);
      GPIO_SetBits(LED3p);
    }
    else if(sta==RVS)
    {
      (GPIO_ReadOutputDataBit(LED0p))?(GPIO_ResetBits(LED0p)):(GPIO_SetBits(LED0p));
      (GPIO_ReadOutputDataBit(LED1p))?(GPIO_ResetBits(LED1p)):(GPIO_SetBits(LED1p));
      (GPIO_ReadOutputDataBit(LED2p))?(GPIO_ResetBits(LED2p)):(GPIO_SetBits(LED2p));
      (GPIO_ReadOutputDataBit(LED3p))?(GPIO_ResetBits(LED3p)):(GPIO_SetBits(LED3p));
    }
    break;
  default:
    break;
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void Test_GPIO_LED(void)
����  �ܡ� ����LED����˸
������ֵ�� ��
������ֵ�� ��
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ Test_GPIO_LED()
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_LED(void)
{
  GPIO_LED_Init();
  while(1)
  {
    LED_Ctrl(LEDALL,RVS);     //LED��ת��˸
    delayms(200);
  }
}


