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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�chiusir
������˵������ȡ ICM20689 ��ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_ICM20689(void)
{
  char  txt[16];
  unsigned char cnt=0; 
  u16 aacx,aacy,aacz;	 //���ٶȴ�����ԭʼ����
  u16 gyrox,gyroy,gyroz; //������ԭʼ����   
  
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
  TFTSPI_P8X16Str(1, 0,"LQ20689M Test", u16PURPLE, u16BLACK);   // �ַ�����ʾ
  if(ICM20689_Init())
  {       
    TFTSPI_P8X16Str(1, 2,"LQ20689M Fail", u16PURPLE, u16BLACK);   // �ַ�����ʾ
    //while(1)     
  }
  
  while(1)
  {
    ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
    sprintf((char*)txt,"ax:%06d",aacx);
    TFTSPI_P8X16Str(1, 3, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf((char*)txt,"ay:%06d",aacy);
    TFTSPI_P8X16Str(1, 4, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf((char*)txt,"az:%06d",aacz);
    TFTSPI_P8X16Str(1, 5, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf((char*)txt,"gx:%06d",gyrox);
    TFTSPI_P8X16Str(1, 6, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf((char*)txt,"gy:%06d",gyroy);
    TFTSPI_P8X16Str(1, 7, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    sprintf((char*)txt,"gz:%06d",gyroz);
    TFTSPI_P8X16Str(1, 8, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
    
    cnt++; 
    sprintf((char*)txt,"%03d",cnt);
    TFTSPI_P8X16Str(10, 1, txt, u16PURPLE, u16BLACK);  
    LED_Ctrl(LED1,RVS); //LED��ת��˸
    
    //ANO_DT_send_int16(0,0,aacx,aacy,aacz,gyrox,gyroy,gyroz);
    
  }  
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�
������˵������ʼ�� ICM20689
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u8 ICM20689_Init(void)
{
  char  txt[10];
  u8 res;
  
  ICM_SPI_Init(); 
  delayms(100);  
  res=ICM_Read_Byte(WHO_AM_I);                         //��ȡICM20689��ID  
  sprintf(txt,"ID:0x%02X",res);  
  TFTSPI_P8X16Str(1, 1, txt, u16PURPLE, u16BLACK);     // �ַ�����ʾ
  if(res!=ICM20689_ID)                                 //����ID��ȷ
  {    
    //printf("ID=%#X\r\n",res);
    //OLED_P6x8Str(1,4,"ID is fail!");
    return 1;
  }
  else  
  {
    //printf("ICM20689 is OK!\n");  
  }   
  
  ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//��λ
  delayms(100);  //��ʱ100ms
  ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//����
  delayms(100);  //��ʱ100ms
  
  ICM_Set_Gyro_Fsr(3);			 //�����Ǵ�����,��2000dps   
  ICM_Set_Accel_Fsr(1);			 //���ٶȴ�����,0:��2g   1:��4g    2:��8g
  ICM_Set_Rate(1000);			 //���ò�����1000Hz
  //ICM_Write_Byte(ICM_CFG_REG,0x02);    //�������ֵ�ͨ�˲���   98hz
  ICM_Write_Byte(ICM_CFG_REG,4);	 //��ͨ�˲�Ƶ�ʣ�����ֵ��0x07(3600Hz)�˼Ĵ����ھ���Internal_Sample_Rate==8K
  ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //�ر������ж�
  ICM_Write_Byte(ICM_FIFO_EN_REG,0X00);	 //�ر�FIFO
  ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
  ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
  ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ����� 
  
  return 0;
}

/*************************************************************************
*  �������ƣ�void SPI_SoftInit(void)
*  ����˵����ģ��SPI�ڳ�ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/

void ICM_SPI_Init(void)
{
#ifdef USE_SOFT_SPI
  Soft_SPI_Init();
#else
  SPIM_Init(SPI1, SPI_BaudRatePrescaler_32);//0x20
#endif
}


/*************************************************************************
*  �������ƣ�void ICM_Read_Len(u8 reg,u8 len,u8 *buf)
*  ����˵����u8 reg��ʼ�Ĵ���,u8 *buf����ָ��,u16 len����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Read_Len(u8 reg,u8 len,u8 *buf)
{  
#ifdef USE_SOFT_SPI
  buf[0] = reg | 0x80;  
  Soft_SPI_ReadWriteNbyte(buf, len + 1);  
#else
  SPI_Read_Nbytes(SPI1,reg|0x80,buf,len);
#endif
}
/*************************************************************************
*  �������ƣ�void ICM_Get_Gyroscope(u16 *gx,u16 *gy,u16 *gz)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Gyroscope(u16 *gx,u16 *gy,u16 *gz)
{
  u8 buf[7]; 
  ICM_Read_Len(ICM_GYRO_XOUTH_REG,6,buf);
  
  *gx=((u16)buf[1]<<8)|buf[2];  
  *gy=((u16)buf[3]<<8)|buf[4];  
  *gz=((u16)buf[5]<<8)|buf[6];
  
}
/*************************************************************************
*  �������ƣ�void ICM_Get_Accelerometer(u16 *ax,u16 *ay,u16 *az)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Accelerometer(u16 *ax,u16 *ay,u16 *az)
{
  u8 buf[7];  
  ICM_Read_Len(ICM_ACCEL_XOUTH_REG,6,buf);
  
  *ax=((u16)buf[1]<<8)|buf[2];  
  *ay=((u16)buf[3]<<8)|buf[4];  
  *az=((u16)buf[5]<<8)|buf[6];  
}

/*************************************************************************
*  �������ƣ�void ICM_Get_Raw_data(u16 *ax,u16 *ay,u16 *az,u16 *gx,u16 *gy,u16 *gz)
*  ����˵������ȡ���ٶ�����������
*  ����˵��������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Raw_data(u16 *ax,u16 *ay,u16 *az,u16 *gx,u16 *gy,u16 *gz)
{
  u8 buf[16];  
  ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);
  
  *ax=((u16)buf[1]<<8)|buf[2];  
  *ay=((u16)buf[3]<<8)|buf[4];  
  *az=((u16)buf[5]<<8)|buf[6];
  *gx=((u16)buf[9]<<8)|buf[10];  
  *gy=((u16)buf[11]<<8)|buf[12];  
  *gz=((u16)buf[13]<<8)|buf[14];
}

/*************************************************************************
*  �������ƣ�void ICM_Write_Byte(u8 reg,u8 value)
*  ����˵������Ĵ���д����
*  ����˵����u8 reg�Ĵ���,u8 value����
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Write_Byte(u8 reg,u8 value)
{
#ifdef USE_SOFT_SPI
  uint8_t buff[2];  
  buff[0] = reg;          //�ȷ��ͼĴ���
  buff[1] = value;        //�ٷ�������  
  Soft_SPI_ReadWriteNbyte(buff, 2);//����buff�����ݣ����ɼ��� buff��  
  
#else
  SPIM_CSLow(SPI1);
  SPI_WriteRead(SPI1, reg | 0x80);
  SPI_WriteRead(SPI1, value);
  SPIM_CSHigh(SPI1);  
#endif
}

/*************************************************************************
*  �������ƣ�void ICM_Write_Byte(u8 reg,u8 value)
*  ����˵������Ĵ���д����
*  ����˵����u8 reg�Ĵ���,
*  �������أ�u8 value����
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
u8 ICM_Read_Byte(u8 reg)
{  
  u8 buff[2];
#ifdef USE_SOFT_SPI
  buff[0] = reg | 0x80;          //�ȷ��ͼĴ���  
  Soft_SPI_ReadWriteNbyte(buff, 2);   
  return buff[1];
#else
  SPIM_CSLow(SPI1);
  SPI_WriteRead(SPI1, reg | 0x80);
  buff[1]=SPI_WriteRead(SPI1, 0);
  SPIM_CSHigh(SPI1);
  return buff[1];
  
#endif  
}
/*************************************************************************
*  �������ƣ�void ICM_Set_Gyro_Fsr(u8 fsr)
*  ����˵�������������Ǵ����������̷�Χ
*  ����˵����Fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
*  �������أ�
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Set_Gyro_Fsr(u8 fsr)
{
  ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
/*************************************************************************
*  �������ƣ�void ICM_Set_Accel_Fsr(u8 fsr)
*  ����˵��������LQ20689�����Ǵ����������̷�Χ
*  ����˵����fsr:0,��2g;1,��4g;2,��8g;3,��16g
*  �������أ�
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Set_Accel_Fsr(u8 fsr)
{
  ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
/*************************************************************************
*  �������ƣ�void ICM_Set_LPF(u16 lpf)
*  ����˵��������LQ20689���ֵ�ͨ�˲���
*  ����˵����lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
*  �������أ�
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Set_LPF(u16 lpf)
{
  u8 dat=0;
  if(lpf>=188)dat=1;
  else if(lpf>=98)dat=2;
  else if(lpf>=42)dat=3;
  else if(lpf>=20)dat=4;
  else if(lpf>=10)dat=5;
  else dat=6; 
  ICM_Write_Byte(ICM_CFG_REG,dat);//�������ֵ�ͨ�˲���  
}
/*************************************************************************
*  �������ƣ�void ICM_Set_Rate(u16 rate)
*  ����˵��������LQ20689�����Ǵ����������̷�Χ
*  ����˵����rate:4~1000(Hz)
*  �������أ�
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Set_Rate(u16 rate)
{
  u8 dat;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  dat=1000/rate-1;
  ICM_Write_Byte(ICM_SAMPLE_RATE_REG,dat);	//�������ֵ�ͨ�˲���
  ICM_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}
/*************************************************************************
*  �������ƣ�u16 ICM_Get_Temperature(void)
*  ����˵�����õ��¶�ֵ
*  ����˵����
*  �������أ�����ֵ:�¶�ֵ(������100��)
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע������ֵ:�¶�ֵ(������100��)   
*************************************************************************/
u16 ICM_Get_Temperature(void)
{
  u8 buf[3]; 
  u16 raw;
  float temp;
  ICM_Read_Len(ICM_TEMP_OUTH_REG,2,buf); 
  raw=((u16)buf[0]<<8)|buf[1];  
  temp=21+((double)raw)/333.87;  
  return (u16)temp*100;
}


//**********************************************************************************************************************************************************
void icm20689_reset(void)
{
  ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);	//��λ
  delayms(100);
  ICM_Write_Byte(ICM_PWR_MGMT1_REG, 0x00);	//�������״̬
}


//


