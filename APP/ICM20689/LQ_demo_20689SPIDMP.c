/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�F3277���İ��ĸ��
����    д������Ƽ�
��E-mail  ��chiusir@163.com
������汾��V1.0 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2021��3��31�գ��������£����ע���°棡
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��IDE��IAR7.8 KEIL5.24�����ϰ汾
��Target �� MM32F3277
��SYS PLL�� 120MHz Ƶ��̫�߿����޷�����system_mm32f327x.c
=================================================================
����������Ƶ��ַ��https://space.bilibili.com/95313236
=================================================================
���������MPU6050DMP���ܣ�������������վ4.34��ʾ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

extern short   gyro[3], accel[3], sensors;
extern float   Pitch, Roll; 

void Test_LQDMP(void)
{
  char  txt[10];
  u8 tm[2];
  u8 res;
  
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������  
  ICM_SPI_Init(); 
  TFTSPI_P8X16Str(2,0,"LQ DMP Test", u16RED, u16BLACK);
  UART_PutStr(UART1, "LQ DMP Test\r\n");
  delayms(100);  
  res=ICM_Read_Byte(WHO_AM_I);                       //��ȡICM20689��ID  
  sprintf(txt,"ID:0x%02X",res);  
  TFTSPI_P8X16Str(0, 9, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
  LQ_SPI_Read(WHO_AM_I, 1, tm);  
  sprintf(txt,"ID:0x%02X",tm[0]);  
  TFTSPI_P8X16Str(8, 9, txt, u16PURPLE, u16BLACK);   // �ַ�����ʾ
  LQ_DMP_Init();
  delayms(100);
  while(1)
  {       
    LQ_DMP_Read();    
    
    sprintf((char*)txt,"Pitch:%.2f", Pitch);
    TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"Roll:%.2f", Roll);
    TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLACK);
    
    sprintf((char*)txt,"ax:%06d",accel[0]);
    TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"ay:%06d",accel[1]);
    TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"az:%06d",accel[2]);
    TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"gx:%06d",gyro[0]);
    TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"gy:%06d",gyro[1]);
    TFTSPI_P8X16Str(0,7,txt,u16RED,u16BLACK);
    sprintf((char*)txt,"gz:%06d",gyro[2]);
    
    //��λ��
    ANO_DT_send_int16((short)Pitch, (short)Roll, 0, 0, 0, 0, 0, 0 );
  }
}

