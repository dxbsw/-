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
#ifndef __LQ_SPI_H_
#define __LQ_SPI_H_
#include "include.h"


typedef enum //SPI���
{
  SPI_1,
  SPI_2,
  SPI_3,
}SPIn_e;

typedef enum //SCK���ùܽ�
{
  SPI1_SCK_A05= 0x5005,// AF5 ���� PA�� A5
  SPI1_SCK_B03= 0x5013,
  SPI1_SCK_E12= 0x504C,
  
  SPI2_SCK_B10= 0x501A,				
  SPI2_SCK_B13= 0x501D,				
  SPI2_SCK_D03= 0x5033,				
  SPI2_SCK_E02= 0x5042,				
  
  SPI3_SCK_B03= 0x6013,				
  SPI3_SCK_C10= 0x602A,				
  SPI3_SCK_D04= 0x5034,				
  SPI3_SCK_D12= 0x603C,			
}SPI_SCK_e;


typedef enum//MOSI���ùܽ�
{
  SPI1_MOSI_A07= 0x5007,		
  SPI1_MOSI_B05= 0x5015,	
  SPI1_MOSI_E14= 0x504E,	
  
  SPI2_MOSI_B15= 0x501F,		
  SPI2_MOSI_C03= 0x5023,
  SPI2_MOSI_E06= 0x5046,				
  
  SPI3_MOSI_B05= 0x6015,		
  SPI3_MOSI_C12= 0x602C,	
  SPI3_MOSI_D06= 0x5036,				
  SPI3_MOSI_D14= 0x603E,		
}SPI_MOSI_e;


typedef enum//MISO���ùܽ�
{
  SPI1_MISO_A06= 0x5006,	
  SPI1_MISO_B04= 0x5014,
  SPI1_MISO_E13= 0x504D,
  
  SPI2_MISO_B14= 0x501E,
  SPI2_MISO_C02= 0x5022,	
  SPI2_MISO_C06= 0x5026,	
  SPI2_MISO_E05= 0x5045,	
  
  SPI3_MISO_B04= 0x6014,	
  SPI3_MISO_C07= 0x5027,	
  SPI3_MISO_C11= 0x602B,	
  SPI3_MISO_D05= 0x5035,
  SPI3_MISO_D13= 0x603D,
}SPI_MISO_e;


typedef enum//CS���ùܽ�
{	
  SPI1_NSS_A04= 0x5004,			
  SPI1_NSS_A15= 0x500F,
  SPI1_NSS_E11= 0x504B,		
  
  SPI2_NSS_B09= 0x5019,		
  SPI2_NSS_B12= 0x501C,		
  SPI2_NSS_E03= 0x5043,	
  SPI2_NSS_E04= 0x5044,	
  
  SPI3_NSS_A04= 0x6004,				
  SPI3_NSS_A15= 0x600F,				
  SPI3_NSS_D07= 0x5037,			
  SPI3_NSS_D15= 0x603F,		
}SPI_CS_e;

unsigned char SPI_WriteRead(SPI_TypeDef* SPIx, unsigned char tx_data);
void SPIM_Init(SPI_TypeDef* SPIx, SPI_BaudRatePrescaler_TypeDef spi_baud_div);
void SPI_Read_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len);
void SPI_Write_Nbytes(SPI_TypeDef* SPIx, unsigned char Addr, unsigned char* buf, unsigned short len);
void SPIM_TXEn(SPI_TypeDef* SPIx);
void SPIM_RXEn(SPI_TypeDef* SPIx);
void SPIM_CSLow(SPI_TypeDef* SPIx);
void SPIM_CSHigh(SPI_TypeDef* SPIx);


#endif

















