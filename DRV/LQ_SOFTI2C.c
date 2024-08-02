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
#include <stdint.h>
#include "LQ_SOFTI2C.h"

/*************************************************************************
*  �������ƣ�IIC��ʱ
*  ����˵����ADC��ʼ������
*  ����˵����us      ��  ��ʱʱ��
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����iic_delay(1);  //�򵥵���ʱ
*  �ڲ����� �޸�������Ե���IIC����
*************************************************************************/
void SOFT_IIC_delay(u16 us)
{
  delayus(us);  
}

/*************************************************************************
*  �������ƣ�void IIC_Init(void)
*  ����˵����ģ��IIC��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_Init();  //ģ��IIC��ʼ�� IIC�ܽ���LQ_SOFTI2C.h�ж���
*************************************************************************/
void SOFT_IIC_Init(void)
{			
  PIN_InitConfig(PD10, GPO, 1,GPIO_Mode_Out_PP);
  SDA_OUT;
  IIC_SCL_H;
  IIC_SDA_H;
  SOFT_IIC_Stop();
}

/*************************************************************************
*  �������ƣ�void SOFT_IIC_Start(void)
*  ����˵����ģ��IIC��ʼ�ź�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_Start();
*************************************************************************/
void SOFT_IIC_Start(void)
{
  IIC_SCL_L;
  SDA_OUT;   //sda����� 
  IIC_SDA_H;	
  IIC_SCL_H;
  SOFT_IIC_delay(1);
  IIC_SDA_L; //START:when CLK is high,DATA change form high to low 
  SOFT_IIC_delay(1);
  IIC_SCL_L; //ǯסI2C���ߣ�׼�����ͻ�������� 
  SOFT_IIC_delay(1);
}


/*************************************************************************
*  �������ƣ�void SOFT_IIC_Stop(void)
*  ����˵����ģ��IICֹͣ�ź�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_Stop();
*************************************************************************/
void SOFT_IIC_Stop(void)
{  
  IIC_SCL_L;
  SDA_OUT; //sda�����
  IIC_SDA_L; //STOP:when CLK is high DATA change form low to high
  SOFT_IIC_delay(1);
  IIC_SCL_H; 
  SOFT_IIC_delay(1);
  IIC_SDA_H; //����I2C���߽����ź�
  SOFT_IIC_delay(1);							   	
}
/*************************************************************************
*  �������ƣ�void SOFT_IIC_Ack(void)
*  ����˵����ģ��IIC����ACKӦ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ������ڲ����� ����������һ���ֽ����ݺ�����������ACK֪ͨ�ӻ�һ���ֽ���������ȷ����
*************************************************************************/
void SOFT_IIC_Ack(void)
{
  IIC_SCL_L;
  SDA_OUT;
  IIC_SDA_L;
  SOFT_IIC_delay(1);
  IIC_SCL_H;
  SOFT_IIC_delay(2);
  IIC_SCL_L;
}


/*************************************************************************
*  �������ƣ�void SOFT_IIC_NAck(void)
*  ����˵����ģ��IIC������ACKӦ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ������ڲ����� �������������һ���ֽ����ݺ�����������NACK֪ͨ�ӻ����ͽ������ͷ�SDA,�Ա���������ֹͣ�ź�
*************************************************************************/
void SOFT_IIC_NAck(void)
{
  IIC_SCL_L;
  SDA_OUT;
  SOFT_IIC_delay(1);
  IIC_SDA_H;
  SOFT_IIC_delay(1);
  IIC_SCL_H;
  SOFT_IIC_delay(2);
  IIC_SCL_L;
}						     

/*************************************************************************
*  �������ƣ�unsigned char SOFT_IIC_Wait_Ack(void)
*  ����˵����ģ��IIC�ȴ�Ӧ���ź�
*  ����˵������
*  �������أ�1������Ӧ��ʧ��    0������Ӧ��ɹ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ������ڲ����� ��ЧӦ�𣺴ӻ���9�� SCL=0 ʱ SDA ���ӻ�����,���� SCL = 1ʱ SDA��ȻΪ��
*************************************************************************/
unsigned char SOFT_IIC_Wait_Ack(void)
{
  unsigned char  ucErrTime=0;
  SDA_IN; //SDA����Ϊ����  ���ӻ���һ���͵�ƽ��ΪӦ�� 
  IIC_SCL_L;
  IIC_SDA_H;
  SOFT_IIC_delay(1);	   
  IIC_SCL_H;
  SOFT_IIC_delay(1);	 
  while(IIC_SDA_READ&0x1)
  {
    ucErrTime++;
    if(ucErrTime>200)
    {
      //SOFT_IIC_Stop();
      return 1;
    }
    SOFT_IIC_delay(1);	 
  }
  SOFT_IIC_delay(1);	 
  IIC_SCL_L; //ʱ�����0 	   
  return 0;  
} 
/*************************************************************************
*  �������ƣ�void SOFT_IIC_Send_Byte(unsigned char data_t)
*  ����˵����ģ��IIC����һ���ֽ�
*  ����˵����data   :  ���͵��ֽ�
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_SendByte(0x12);
*************************************************************************/
void SOFT_IIC_Send_Byte(unsigned char data_t)
{                        
  unsigned char  t;
      
  IIC_SCL_L; //����ʱ�ӿ�ʼ���ݴ���
  SDA_OUT; 	
  for(t=0;t<8;t++)
  {   
    SOFT_IIC_delay(1);
    if(data_t&0x80)
    {
      IIC_SDA_H;
    }
    else 
    {
      IIC_SDA_L;
    }
    SOFT_IIC_delay(1);
    IIC_SCL_H;   
    data_t<<=1;
    SOFT_IIC_delay(2);   
    IIC_SCL_L;	     	
  }
  IIC_SDA_H;
  SOFT_IIC_delay(1);
} 	 


/*************************************************************************
*  �������ƣ�unsigned char SOFT_IIC_Read_Byte(unsigned char ack)
*  ����˵����ģ��IIC��ȡһ���ֽ�
*  ����˵����ack=1 ʱ���������ݻ�û������ ack=0 ʱ����������ȫ���������
*  �������أ����յ����ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IC_ReadByte(0x12);
*************************************************************************/
unsigned char SOFT_IIC_Read_Byte(unsigned char ack)
{
  unsigned char  i,tem=0;
  SDA_IN; //SDA����Ϊ����ģʽ �ȴ����մӻ���������
  IIC_SCL_L;
  IIC_SDA_L;
  for(i=0;i<8;i++ )
  {
    SOFT_IIC_delay(2);
    IIC_SCL_H; 
    if(IIC_SDA_READ) tem++; //�ӻ����͵ĵ�ƽ
    if(i < 7) tem <<= 1;
    SOFT_IIC_delay(2);    
    IIC_SCL_L;       
  }					 
  if(ack)
    SOFT_IIC_Ack(); //����ACK 
  else
    SOFT_IIC_NAck(); //����nACK  
  return tem;
}

/*************************************************************************
*  �������ƣ�void ADC_init(void)
*  ����˵����ģ��IIC��ȡָ���豸 ָ���Ĵ�����һ��ֵ
*  ����˵����
* @param    I2C_Addr  Ŀ���豸��ַ
* @param    reg       Ŀ��Ĵ���
* @param    buf       ��Ŷ����ֽ�
*  �������أ�1ʧ�� 0�ɹ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_ReadByteFromSlave(0xD0, 0x75, &data);   //�� IIC��ַΪ 0xD0������SOFT_I2C���Ĵ���0x75
*************************************************************************/
unsigned char IIC_ReadByteFromSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char *buf)
{
  SOFT_IIC_Start();	
  SOFT_IIC_Send_Byte(I2C_Addr);	 //���ʹӻ���ַ
  if(SOFT_IIC_Wait_Ack()) //����ӻ�δӦ�������ݷ���ʧ��
  {
    SOFT_IIC_Stop();
    return 1;
  }
  SOFT_IIC_Send_Byte(reg); //���ͼĴ�����ַ
  SOFT_IIC_Wait_Ack();	  
  
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(I2C_Addr+1); //�������ģʽ			   
  SOFT_IIC_Wait_Ack();
  *buf=SOFT_IIC_Read_Byte(0);	   
  SOFT_IIC_Stop(); //����һ��ֹͣ����
  return 0;
}
unsigned char IIC_ReadByte(unsigned char I2C_Addr,unsigned char reg,unsigned char *buf)
{
  SOFT_IIC_Start();	
  SOFT_IIC_Send_Byte(I2C_Addr);	 //���ʹӻ���ַ
  if(SOFT_IIC_Wait_Ack()) //����ӻ�δӦ�������ݷ���ʧ��
  {
    SOFT_IIC_Stop();
    return 1;
  }
  SOFT_IIC_Send_Byte(reg); //���ͼĴ�����ַ
  SOFT_IIC_Wait_Ack();	  
  
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(I2C_Addr+1); //�������ģʽ			   
  SOFT_IIC_Wait_Ack();
  *buf=SOFT_IIC_Read_Byte(0);	   
  SOFT_IIC_Stop(); //����һ��ֹͣ����
  return 0;
}

/*************************************************************************
*  �������ƣ�void ADC_init(void)
*  ����˵����ģ��IICдָ���豸 ָ���Ĵ�����һ��ֵ
*  ����˵����
* @param    I2C_Addr  Ŀ���豸��ַ
* @param    reg       Ŀ��Ĵ���
* @param    data      д�������
*  �������أ�1ʧ�� 0�ɹ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_ReadByteFromSlave(0xD0, 0X6B, 0X80);   //IIC��ַΪ 0xD0������SOFT_I2C���Ĵ���0x6B д��0x80
*************************************************************************/
unsigned char IIC_WriteByteToSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char data_t)
{
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(I2C_Addr); //���ʹӻ���ַ
  if(SOFT_IIC_Wait_Ack())
  {
    SOFT_IIC_Stop();
    return 1; //�ӻ���ַд��ʧ��
  }
  SOFT_IIC_Send_Byte(reg); //���ͼĴ�����ַ
  SOFT_IIC_Wait_Ack();	  
  SOFT_IIC_Send_Byte(data_t); 
  if(SOFT_IIC_Wait_Ack())
  {
    SOFT_IIC_Stop(); 
    return 1; //����д��ʧ��
  }
  SOFT_IIC_Stop(); //����һ��ֹͣ����
  
  //return 1; //status == 0;
  return 0;
}

/*************************************************************************
*  �������ƣ�unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char len, unsigned char *data_t)
*  ����˵����ģ��IIC��ȡָ���豸 ָ���Ĵ�����n��ֵ
*  ����˵����
* @param    dev       Ŀ���豸��ַ
* @param    reg       Ŀ��Ĵ���
* @param    len    ��ȡ����
* @param    data      ��Ŷ�������
*  �������أ�1ʧ�� 0�ɹ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_ReadByteFromSlave(0xD0, 0X3B, 14, &data);   //�� 14���ֽ�
*************************************************************************/
unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char len, unsigned char *data_t)
{
  unsigned char  count = 0;
  unsigned char  temp;
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(dev); //���ʹӻ���ַ
  if(SOFT_IIC_Wait_Ack())
  {
    SOFT_IIC_Stop(); 
    return 1; //�ӻ���ַд��ʧ��
  }
  SOFT_IIC_Send_Byte(reg); //���ͼĴ�����ַ
  SOFT_IIC_Wait_Ack();	  
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(dev+1); //�������ģʽ	
  SOFT_IIC_Wait_Ack();
  for(count=0;count<len;count++)
  {
    if(count!=(len-1))
      temp = SOFT_IIC_Read_Byte(1); //��ACK�Ķ�����
    else  
      temp = SOFT_IIC_Read_Byte(0); //���һ���ֽ�NACK
    
    data_t[count] = temp;
  }
  SOFT_IIC_Stop(); //����һ��ֹͣ����
  //return count;
  return 0;
}

/*************************************************************************
*  �������ƣ�unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char len, unsigned char* data_t)
*  ����˵����ģ��IICдָ���豸 ָ���Ĵ�����n��ֵ
*  ����˵����
* @param    dev       Ŀ���豸��ַ
* @param    reg       Ŀ��Ĵ���
* @param    len    д�볤��
* @param    data      ���д������
*  �������أ� 1ʧ�� 0�ɹ�
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����IIC_WriteMultByteToSlave(0xD0, 0X6B, 1, 0X80);   //��Ĵ���0x6Bд��0x80
*************************************************************************/
unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char len, unsigned char* data_t)
{
  
  unsigned char  count = 0;
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(dev); //���ʹӻ���ַ
  if(SOFT_IIC_Wait_Ack())
  {
    SOFT_IIC_Stop();
    return 1; //�ӻ���ַд��ʧ��
  }
  SOFT_IIC_Send_Byte(reg); //���ͼĴ�����ַ
  SOFT_IIC_Wait_Ack();	  
  for(count=0;count<len;count++)
  {
    SOFT_IIC_Send_Byte(data_t[count]); 
    if(SOFT_IIC_Wait_Ack()) //ÿһ���ֽڶ�Ҫ�ȴӻ�Ӧ��
    {
      SOFT_IIC_Stop();
      return 1; //����д��ʧ��
    }
  }
  SOFT_IIC_Stop(); //����һ��ֹͣ����
  
  return 0;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� int LQ_I2C_Write(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *dat)
����  �ܡ� ģ��SPI��д���ݼ�����
* @param    addr   ���豸��ַ
* @param    reg    Ŀ��Ĵ���
* @param    len    д�볤��
* @param    *dat   ���д������
������ֵ�� 1ʧ�� 0�ɹ�
����  �ߡ� L Q
�������¡� 2021��4��3�� 
������汾�� V1.1
������������ LQ_I2C_Write(0x68, 0x38, 1, tmp)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
int LQ_I2C_Write(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *dat)
{
  unsigned int i = 0;
  
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(addr << 1);
  SOFT_IIC_Wait_Ack();
 
  SOFT_IIC_Send_Byte(reg);
  SOFT_IIC_Wait_Ack();
  
  for (i = 0; i < len; i++) 
  {
    SOFT_IIC_Send_Byte(dat[i]);
    SOFT_IIC_Wait_Ack();   
  }
  SOFT_IIC_Stop();
  return 0;
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� int LQ_I2C_Read(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *buf)
����  �ܡ� ģ��SPI��д���ݼ�����
* @param    addr   ���豸��ַ
* @param    reg    Ŀ��Ĵ���
* @param    len    д�볤��
* @param    *buf   ���д������
������ֵ�� 1ʧ�� 0�ɹ�
����  �ߡ� L Q
�������¡� 2021��4��3�� 
������汾�� V1.1
������������ LQ_I2C_Write(0x68, 0x38, 1, tmp)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
int LQ_I2C_Read(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *buf)
{
  SOFT_IIC_Start();
  SOFT_IIC_Send_Byte(addr << 1);
  SOFT_IIC_Wait_Ack();
  
  SOFT_IIC_Send_Byte(reg);
  SOFT_IIC_Wait_Ack();
  SOFT_IIC_delay(2);//Ӧ����Ҫһ����ʱ��
  SOFT_IIC_Start();
  
  SOFT_IIC_Send_Byte((addr << 1)+1);
  SOFT_IIC_Wait_Ack();
  while (len) 
  {
    if (len == 1)
      *buf = SOFT_IIC_Read_Byte(0);
    else
      *buf = SOFT_IIC_Read_Byte(1);
    buf++;
    len--;
  }
  SOFT_IIC_Stop();
  return 0;
}
