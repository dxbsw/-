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

ʹ��˵����
����ѧ��ʾ���������ڵ�����ֻ������ֳ���
������ԴΪ��
ģ�飺����TC264DA���İ塢����ĸ�塢˫·ȫ�ŵ��������˫������512������TFT1.8��Ļ�����������·���ģ�飻
��ģ�����ֻ������־��ɣ�
��зֲ���
||----------��------------------------------------��--------------||
||---------��--------------------------------------��-------------||
||--------��----------------------------------------��------------||
||-------1----����2����� -------�Ҳ��2����� -----1-----------||
||------��--------------------------------------------��----------||
||-----��----------------------------------------------��---------||
||----��------------------------------------------------��--------||
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

int16_t TempAngle = 0;        // ���ݵ��ƫ�������������ʱ���ֵ

int16_t Offset = 0;      // ���ݵ��ƫ�������������ʱ���ֵ
int16_t LastAngle = 0;        // ����������ǰ����Чƫ�Ʒ���
// Front Back Vertical Parallel
int16_t LleftP = 0, LleftV = 0, LrightV = 0, LrightP = 0;  // ���ƫ����
int16_t LnowADC[4];           // ��е�ǰADC��ֵ

int16_t ad_max[4] = {2500, 2300, 999, 999}; // �°��ӷŵ������궨���ֵ,�ᱻ����ˢ��
int16_t ad_min[4] = { 120,  120, 120, 120}; // �°��Ӿ���Ҫ�궨��Сֵ,�ᱻ����ˢ��

u8 CircleNumber = 1;    // �뻷������0������Ĭ��1�� ;���ĸ���һ���ڱ���ǰ��������ʱ��֪����
u8 TangentPoint = 1;    // �е��ж�   0�е������Ĭ��1�����뻷����ȡ����Ϊ�뻷׼��
u8 EnterCircle = 0;     // �������  Ĭ�� 0���ɽ�����1���Խ���
u8 OutCircle = 0;       // �������   Ĭ��0���ɳ�����1���Գ���
u8 LeftRightCircle = 0; // ��໷�����Ҳ໷ Ĭ��0ԭʼ��1�󻷣�2�һ�

int32_t TangentPointpulse = 0; // ���������ʱ����1
int32_t EnterCirclePulse = 0;  // ���������ʱ����2
int32_t OutCirclePulse = 0;    // ���������ʱ����3
int32_t EnterCircleOKPulse = 0;// ���������ʱ����4
int16_t LowSpeed = 0;          // Բ��/ʮ�ֿڼ���
u8 Flag_Show=0;
u16 MagneticField = 0;     // �ų�ǿ��    magnetic field intensity,�ж�Բ���Ƿ����
int16_t OffsetDelta = 0;
extern pid_param_t pid1;


/*************************************************************************
*  �������ƣ�void InductorInit (void)
*  ����˵�����ĸ����ADC��ʼ��������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��18��
*  ��    ע��
*************************************************************************/
void InductorInit (void)
{
  ADC1Init(ADC_Channel_4);
  ADC1Init(ADC_Channel_5);
  ADC1Init(ADC_Channel_6);
  ADC2Init(ADC_Channel_7);	
}
/*************************************************************************
*  �������ƣ�void InductorNormal(void)
*  ����˵�����ɼ���е�ѹ����һ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��18��
*  ��    ע��   ע��Ҫ�ȱ궨�˷ŵķŴ����������ĸ�һ�»��߽ӽ�
*************************************************************************/
void InductorNormal (void)
{
  LnowADC[0] = ADC1_Read(ADC_Channel_4);   // ��ǰ���1����У�������ƽ�У��ɼ�������е�ADֵ
  LnowADC[1] = ADC1_Read(ADC_Channel_5);   // ��ǰ���2����У��봹ֱ������
  LnowADC[2] = ADC1_Read(ADC_Channel_6);  // ��ǰ���2����У��봹ֱ������
  LnowADC[3] = ADC2_Read(ADC_Channel_7);  // ��ǰ���1����У�������ƽ�У�
  
  if (LnowADC[0] < ad_min[0])       
    ad_min[0] = LnowADC[0];    // ˢ����Сֵ
  else if (LnowADC[0] > ad_max[0])  
    ad_max[0] = LnowADC[0];    // ˢ�����ֵ
  
  if (LnowADC[1] < ad_min[1])        
    ad_min[1] = LnowADC[1];
  else if (LnowADC[1] > ad_max[1])   
    ad_max[1] = LnowADC[1];
  
  if (LnowADC[2] < ad_min[2])       
    ad_min[2] = LnowADC[2];
  else if (LnowADC[2] > ad_max[2])  
    ad_max[2] = LnowADC[2];
  
  if (LnowADC[3] < ad_min[3])      
    ad_min[3] = LnowADC[3];
  else if (LnowADC[3] > ad_max[3])  
    ad_max[3] = LnowADC[3];
  
  LleftP  = (LnowADC[0] - ad_min[0]) * 100 / (ad_max[0] - ad_min[0]);     // ��ƫ������һ����0--100����
  LleftV  = (LnowADC[1] - ad_min[1]) * 100 / (ad_max[1] - ad_min[1]);
  LrightV = (LnowADC[2] - ad_min[2]) * 100 / (ad_max[2] - ad_min[2]);
  LrightP = (LnowADC[3] - ad_min[3]) * 100 / (ad_max[3] - ad_min[3]);
  

}


/*************************************************************************
*  �������ƣ�void TFT_Show_EleMag_Info(void)
*  ����˵������ʾ����������Ϣ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��18��
*  ��    ע��
*************************************************************************/
void TFT_Show_EleMag_Info(void)
{ 
  char txt[16] = "X:"; 
  //��ʾ����й�һ�����ƫ����  ��ǰ����е�ѹֵ ����п�������ʷ��Сֵ ����п�������ʷ���ֵ
  sprintf(txt, "0:%04d %04d  ", LleftP, LnowADC[0]);
  TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
  sprintf(txt, "1:%04d %04d", LleftV, LnowADC[1]);
  TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
  sprintf(txt, "2:%04d %04d  ", LrightV, LnowADC[2]);
  TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
  sprintf(txt, "3:%04d %04d  ", LrightP, LnowADC[3]);
  TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK); 
  sprintf(txt, "4:%04d %04d  ", ECPULSE1, ECPULSE2);
  TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK); 
  sprintf(txt, "5:%04d ", MagneticField );
  TFTSPI_P8X16Str(0, 7, txt, u16WHITE, u16BLACK);   
}
/*************************************************************************
*  �������ƣ�void ElectroMagneticCar(void)
*  ����˵������ų�˫������ٿ���
-->1.�����㷨���򵥵ķֶα��������㷨����ѧ��ʾ�����㷨��
---2.�����㷨��PID����Ӧ�ÿ����㷨����ѧ��ʾ�����㷨��
---3.�߶��㷨���ݶ��Ľ�����ȺЭͬ�����㷨��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��10��28��
*  ��    ע������2�����
*************************************************************************/
void ElectroMagneticMWCar (void)
{
  InductorInit();       // �����ADC��ʼ��    
  Encoder_Init(TIM3_ENCA_B4,TIM3_ENCB_B5);// ��ʼ������������
  Encoder_Init(TIM4_ENCA_B6,TIM4_ENCB_B7); 	
  MotorInit(12500);     // ���������PWMΪ12.5Khz
  TIMER_InitConfig(TIMER_6, 20);//��������ȡ�жϺ���
 
  TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLACK);         // ����
  while (1)
  {
    InductorNormal();           // �ɼ���е�ѹ������һ����
    MagneticField = LleftP + LleftV + LrightV + LrightP;// �ų�����ǿ��
    if((LleftV>28)&&(LrightV>28))
    {
      Offset = (LleftV-LrightV)*20;
    }
    else 
    {
      Offset = (LleftV-LrightV)*35;
    }
   // TFT_Show_EleMag_Info();
    MotorDuty1 = MtTargetDuty - Offset*8/5- ECPULSE1 * 3;        // ���PWM
    MotorDuty2 = MtTargetDuty + Offset*8/5+ ECPULSE2 * 3;        // ˫�����֣���Ҫȥ��abs
    
    MotorCtrl(MotorDuty1, MotorDuty2);        // ����˫�������
  }
} 

