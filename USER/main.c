/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 7.19 �� ���37��ƽ��45ǰ
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
  int main(void)
{
  // ϵͳ����ʱ������ʼ��
  LQ_Init3227();	    
  //LED KEY��ʼ��
  GPIO_LED_Init();
  SIR_BELL_Init();

  
  //TFT��Ļ��ʼ��
  TFTSPI_Init(0);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ

  //��Ҫ���г���
  Balance_CAR ();

  while(1)
  {
    //2024.12.3
    //Test_ICM20689();
  }
}




