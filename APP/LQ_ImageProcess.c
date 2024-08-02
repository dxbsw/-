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



int16_t OFFSET=0;  // ��������ƫ�����ۺ�ֵ
/*************************************************************************
*  �������ƣ�void TFT_Show_Camera_Info(void)
*  ����˵������ʾ����������Ϣ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��18��
*  ��    ע��      ��������ͷ��
*************************************************************************/
void TFT_Show_Camera_Info (void)
{
  char txt[16] = "X:";
  
  int16_t mps = 0;    // �ٶȣ�m/s,������ֵ
  int16_t pulse100 = 0;
  uint16_t bat = 0;
  
//  pulse100 = (int16_t) (RAllPulse / 100);
//  sprintf(txt, "AP:%05d00", pulse100);           //
//  TFTSPI_P8X16Str(3, 4, txt, u16RED, u16BLUE);   // ��ʾ����ƫ�����
  
  // TFTSPI_Road(18, 0, LCDH, LCDW, (unsigned char *)Image_Use); // TFT1.8��̬��ʾ����ͷ�Ҷ�ͼ��
 // TFTSPI_BinRoad(18, 0, LCDH, LCDW, (unsigned char *) Bin_Image);  // TFT1.8��̬��ʾ����ͷ������ͼ��
  sprintf(txt, "%04d", OFFSET0);
  TFTSPI_P8X16Str(0, 5, txt, u16RED, u16BLUE);       // ��ʾ����ƫ�����
 // BatVolt       = ADC1_Read(12);  // ˢ�µ�ص�ѹ
//  bat = BatVolt * 11 / 25;  // x/4095*3.3*100*5.7
//  sprintf(txt, "B:%d.%02dV %d.%02dm/s", bat / 100, bat % 100, mps / 1000, (mps / 10) % 100);  // *3.3/4095*3
//  TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLUE);   // �ַ�����ʾ
  // ����Ͷ��������ʾ
  //sprintf(txt, "Sv:%04d Rno:%d", ServoDuty, CircleNumber);
 // TFTSPI_P8X16Str(1, 7, txt, u16RED, u16BLUE);     // ��ʾ��������1��������1��ֵ
  sprintf(txt, "M1:%04d, M2:%04d ", MotorDuty1, MotorDuty2);
  TFTSPI_P8X16Str(0, 6, txt, u16RED, u16BLUE);     // ���1-2��ֵ
  sprintf(txt, "E1:%04d, E2:%04d ", ECPULSE1, ECPULSE2);
  TFTSPI_P8X16Str(0, 7, txt, u16RED, u16BLUE);     // ������1-2��ֵ
}
/*************************************************************************
*  �������ƣ�void CameraCar(void)
*  ����˵������ų�˫������ٿ���
-->1.�����㷨���򵥵ķֶα��������㷨����ѧ��ʾ�����㷨��
2.�����㷨��PID����Ӧ�ÿ����㷨����ѧ��ʾ�����㷨��
3.�߶��㷨���Ľ�����ȺЭͬ�����㷨��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��10��28��
*  ��    ע������2�����
*************************************************************************/
void CameraCar (void)
{
  // ����ͷ��ʼ��
  CAMERA_Init(50);
  TFTSPI_P8X16Str(2, 3, "LQ 9V034 Car", u16RED, u16GREEN);
  TFTSPI_P8X16Str(1, 5, "K2 Show Video", u16RED, u16GREEN);
  delayms(500);
  Encoder_Init(TIM3_ENCA_B4,TIM3_ENCB_B5);// ��ʼ������������
  Encoder_Init(TIM4_ENCA_B6,TIM4_ENCB_B7); 	
  MotorInit(12500);     // ���������PWMΪ12.5Khz
  TIMER_InitConfig(TIMER_6, 20);//��������ȡ�жϺ���
  TFTSPI_CLS(u16BLUE);     // ����
  RAllPulse = 0;           // ȫ�ֱ����������������
  while (1)
  {
    //TFT_Show_Camera_Info();
    LED_Ctrl(LED1, RVS);   // LED��˸ ָʾ��������״̬
    if (Camera_Flag == 1)
    {
      Camera_Flag = 0;     // �������ͷ�ɼ���ɱ�־λ  �����������򲻻��ٴβɼ�����
      Get_Use_Image();     // ��ȡ����ʹ�õ�����
      Get_Bin_Image(0);    // ת��Ϊ01��ʽ���ݣ�0��1ԭͼ��2��3������ȡ
      Bin_Image_Filter();  // �˲������汻Χ�����ݽ����޸�Ϊͬһ��ֵ
      Seek_Road();         // ͨ���ڰ�����������������ƫ��ֵ
      
    }
    OFFSET = OFFSET1 + OFFSET2 +OFFSET2;
    MotorDuty1 = MtTargetDuty + OFFSET*4/3- ECPULSE1 * 5;        // ���PWM
    MotorDuty2 = MtTargetDuty - OFFSET*4/3+ ECPULSE2 * 5;        // ˫�����֣���Ҫȥ��abs
  
    MotorCtrl(MotorDuty1, MotorDuty2);        // ����˫�������
    if(0==KEY_Read(KEY1)) //������ʾ��Ļ��Ϣ,��ʡ����ʱ�䣬��Ӧ�Ͽ�
    {
      TFT_Show_Camera_Info();
    }  
  }
}
