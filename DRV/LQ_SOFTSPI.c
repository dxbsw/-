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

Ӳ��ʹ��SPI1
CS   PE10
SCK  PE12
MISO PE13 
MOSI PE14

#define Soft_SPI_CS_PIN       GPIOE,GPIO_Pin_10     //CS Ĭ����PE11,���ʹ�ñ�������������л���PE10
#define Soft_SPI_SCK_PIN      GPIOE,GPIO_Pin_12     //SCK
#define Soft_SPI_MISO_PIN     GPIOE,GPIO_Pin_13     //��Ƭ��MISO��ģ���--SDO
#define Soft_SPI_MOSI_PIN     GPIOE,GPIO_Pin_14     //��Ƭ��MOSI��ģ���--SDI

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "string.h"
#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"
////////////////////////////////////////////////////////////////////////////////

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void Soft_SPI_Init(void)
����  �ܡ� ģ��SPI��ʼ��
������ֵ�� ��
������ֵ�� ��
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ Soft_SPI_Init()
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Soft_SPI_Init(void)
{  
  /*
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  //Ĭ��ʹ��SPI1 E11-14��
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);   //SPI2 clk enable  
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  */
  
  //SPI_NSS  
  PIN_InitConfig(PE10, GPO, 1,GPIO_Mode_Out_PP);
  //SPI_SCK
  PIN_InitConfig(PE12, GPO, 1,GPIO_Mode_Out_PP);
  //SPI_MISO
  PIN_InitConfig(PE13, GPI, 1,GPIO_Mode_FLOATING);
  //SPI_MOSI
  PIN_InitConfig(PE14, GPO, 1,GPIO_Mode_Out_PP);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void Soft_SPI_ReadWriteNbyte(u8 *lqbuff, u8 len)
����  �ܡ� ģ��SPI��д���ݼ�����
������ֵ�� u8 *buf����ָ��,u16 len����
������ֵ�� u8 *buf����ָ��,u16 len����
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Soft_SPI_ReadWriteNbyte(u8 *lqbuff, u8 len)
{
  u8 i;
  
  Soft_SPI_CS_OUT_L;
  Soft_SPI_SCK_OUT_H;
  do
  {
    for(i = 0; i < 8; i++)
    {
      if((*lqbuff) >= 0x80)
      {
        Soft_SPI_MOSI_OUT_H;        
      }
      else
      {
        Soft_SPI_MOSI_OUT_L;       
      }        
      
      Soft_SPI_SCK_OUT_L;
      (*lqbuff) <<= 1;      
      
      Soft_SPI_SCK_OUT_H;
      
      (*lqbuff) |= Soft_SPI_MISO_IN;          
    }
    lqbuff++;
  }while(--len);
  Soft_SPI_CS_OUT_H;
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void LQ_SPI_Read(unsigned char reg, unsigned short len, unsigned char* buf)
����  �ܡ�SPI���豸��ȡ����
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ��unsigned char reg,�豸��ʼ��ַ
������ֵ��unsigned char* buf,���ݴ�ŵ�ַ
������ֵ��unsigned short len,����ȡ�����ݳ���
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_SPI_Read(unsigned char reg, unsigned short len, unsigned char* buf)
{  
#ifdef USE_SOFT_SPI
  unsigned short i;
  buf[0] = reg | 0x80;  
  Soft_SPI_ReadWriteNbyte(buf, len + 1); 
  for(i=0;i<len;i++)
    buf[i]=buf[i+1];
#else
  SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
#endif
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void LQ_SPI_Write(unsigned char reg, unsigned short len, unsigned char* buf)
����  �ܡ�SPI���豸д������
������ֵ��
������ֵ��unsigned char reg,�豸��ʼ��ַ
������ֵ��unsigned char* buf,���ݴ�ŵ�ַ
������ֵ��unsigned short len,��д������ݳ���
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_SPI_Write(unsigned char reg, unsigned short len, unsigned char* buf)
{   
#ifdef USE_SOFT_SPI
  unsigned short i;
  for(i=0;i<len;i++)
    buf[len-i]=buf[len-i-1];
  buf[0] = reg | 0x80;  
  
  Soft_SPI_ReadWriteNbyte(buf, len + 1);  
#else
  SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
#endif
}

