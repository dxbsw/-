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
SCK  PE12
MOSI PE13
MISO PE14 
CS   PE10
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "string.h"
#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"
////////////////////////////////////////////////////////////////////////////////


#define SPI_CS_PIN       GPIOE,GPIO_Pin_10           //CS Ĭ����PE11,���ʹ�ñ�������������л���PE10
#define SPI_CS_OUT_H     GPIO_SetBits(SPI_CS_PIN)    //��������ߵ�ƽ
#define SPI_CS_OUT_L     GPIO_ResetBits(SPI_CS_PIN)  //��������͵�ƽ

#define Dummy_Byte       0x00

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void SPI_Read_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len)
����  �ܡ�SPI���豸��ȡ����
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ��unsigned char Addr,�豸��ַ
������ֵ��unsigned char* buf,���ݴ�ŵ�ַ
������ֵ��unsigned short len,����ȡ�����ݳ���
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPI_Read_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len)
{
  SPIM_CSLow(SPIx);
  //Send destination address 0-7 bits
  SPI_WriteRead(SPIx, Addr);
  len++;
  while (len--)
  {
    buf++;
    //Save the data read from flash into the specified array
    *buf = SPI_WriteRead(SPIx, Dummy_Byte);        
  }
  SPIM_CSHigh(SPIx);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void SPI_Write_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len)
����  �ܡ�SPI���豸д������
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ��unsigned char Addr,�豸��ַ
������ֵ��unsigned char* buf,���ݴ�ŵ�ַ
������ֵ��unsigned short len,��д������ݳ���
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPI_Write_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len)
{    
  SPIM_CSLow(SPIx);
  SPI_WriteRead(SPIx, Addr);
  len++;
  while (len--)
  {
    buf++;
    //Save the data read from flash into the specified array
    *buf = SPI_WriteRead(SPIx, Dummy_Byte);        
  }
  SPIM_CSHigh(SPIx);    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void SPIM_CSLow(SPI_TypeDef* SPIx)
����  �ܡ�SPIƬѡ
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPIM_CSLow(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPIM_CSLow(SPI_TypeDef* SPIx)
{
  SPI_CSInternalSelected(SPIx,  ENABLE);     
  SPI_CS_OUT_L;//��������͵�ƽ
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void SPIM_TXEn(SPI_TypeDef* SPIx)
����  �ܡ�SPI����ʹ��
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ���� 
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������SPIM_TXEn(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPIM_TXEn(SPI_TypeDef* SPIx)
{
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void SPIM_RXEn(SPI_TypeDef* SPIx)
����  �ܡ� SPI����ʹ��
������ֵ�� SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_RXEn(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPIM_RXEn(SPI_TypeDef* SPIx)
{
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void SPIM_CSHigh(SPI_TypeDef* SPIx)
����  �ܡ� SPI�ͷ��豸
������ֵ�� SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_CSHigh(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPIM_CSHigh(SPI_TypeDef* SPIx)
{
  SPI_CSInternalSelected(SPIx, DISABLE);  
  SPI_CS_OUT_H;//��������ߵ�ƽ  
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������unsigned char SPI_WriteRead(SPI_TypeDef* SPIx, unsigned char tx_data)
����  �ܡ�SPI��д����
������ֵ��SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ��unsigned char tx_data,��д�������
������ֵ�����豸��ȡ������
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������ x=SPI_Read_Nbytes(SPI1,buf);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
unsigned char SPI_WriteRead(SPI_TypeDef* SPIx, unsigned char tx_data)
{
  SPI_SendData(SPIx, tx_data);
  while(!(SPIx->CSTAT & SPI_FLAG_TXEPT));
  while(!(SPIx->CSTAT & SPI_CSTAT_RXAVL));
  return (unsigned char)SPIx->RXREG;
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void SPIM_Init(SPI_TypeDef* SPIx, SPI_BaudRatePrescaler_TypeDef spi_baud_div)
����  �ܡ� SPI��ʼ��
������ֵ�� SPI_TypeDef* SPIx, SPIͨ��ѡ��
������ֵ�� SPI_BaudRatePrescaler_TypeDef spi_baud_div, SPI�����ʷ�Ƶ
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SPIM_CSHigh(SPI1)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void SPIM_Init(SPI_TypeDef* SPIx, SPI_BaudRatePrescaler_TypeDef spi_baud_div)
{
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;

//////////////////////////////////SPI�ܽų�ʼ��/////////////////////////////////////  
  //Ĭ��ʹ��SPI1 E11-14��
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);   //SPI2 clk enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
  //SPI_NSS
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_5);
  //SPI_SCK
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_5);
  //SPI_MISO
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_5);
  //SPI_MOSI
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_5);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
///////////////////////////////////////////////////////////////////////////    
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  //	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
  SPI_InitStructure.SPI_BaudRatePrescaler = spi_baud_div;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_Init(SPIx, &SPI_InitStructure);
  
  SPI_Cmd(SPIx, ENABLE);
  SPIM_TXEn(SPIx);
  SPIM_RXEn(SPIx);
  
  //SPI_NSS  
  PIN_InitConfig(PE10, GPO, 0,GPIO_Mode_Out_PP);
}



