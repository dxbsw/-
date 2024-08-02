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

const u32 TIMERx[] = {TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE, TIM5_BASE, TIM6_BASE, TIM7_BASE, TIM8_BASE};
TIM_TypeDef *TIMERxP[8] = {TIM1,TIM2,TIM3,TIM4,TIM5,TIM6,TIM7,TIM8};

int16_t ECPULSE1 = 0;          // �ٶ�ȫ�ֱ���
int16_t ECPULSE2 = 0;         // �ٶ�ȫ�ֱ���
int16_t ECPULSE =0;
//int16_t last_ECPULSE = 0;
volatile int32_t RAllPulse = 0;// �ٶ�ȫ�ֱ���
extern volatile uint8_t Game_Over;    // С�����ȫ������ͣ��
//extern volatile int16_t targetSpeed;


short aacx, aacy, aacz;
short gyrox, gyroy, gyroz;

//ֱ��������
pid_param_t Gyro_PID,Angle_PID;
extern short gyro[3];
extern float Roll;
float ANGLE_OUT;
float BALANCE_OUT;

//�ٶȻ�����
pid_param_t BalSpeed_PID;
float SPEED_OUT;

//���򻷲���
pid_param_t BalDirgyro_PID,BalDir_PID;
extern int16_t LleftP, LleftV, LrightV, LrightP;   // ���ƫ����
float BalDirgyro_out;
float Dir_Error;
float last_error;
float last_hang;
float BalDir_out;
extern int bell_flag;

#define Angle_Set -36.9  // ���������ǰ�װ�ǶȽ���
#define Gyroy_Set 20     // ���������Ư��
#define Gyroz_Set -7    // ���������Ư��
#define PI 3.14159265

float *ANGLE;

//������ֻ������һ���жϣ�ͨ�����ñ�־λʵ�ֲ�ͬʱ������ʱ����ƣ�ֻ���ο�������
//������ֻ������һ���жϣ�ͨ�����ñ�־λʵ�ֲ�ͬʱ������ʱ����ƣ�ֻ���ο�������
//������ֻ������һ���жϣ�ͨ�����ñ�־λʵ�ֲ�ͬʱ������ʱ����ƣ�ֻ���ο�������
int count_LED = 0;
int count_5ms = 0;
int count_10ms = 0;
int count_20ms = 0;
void TIM1_UP_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ  
    
  }  
}
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
    LED_Ctrl(LED1,RVS);//LED��ת��˸
    
  }  
}
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
    LED_Ctrl(LED1,RVS);//LED��ת��˸
    
  }  
}
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
    LED_Ctrl(LED1,RVS);//LED��ת��˸
    
  }  
}


void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
    LED_Ctrl(LED0,RVS);//LED��ת��˸     
  }  
}

extern int16_t targetSpeed1 =60;  // ֱ����ǰ��Ŀ��

void TIM6_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
      
    LED_Ctrl(LED1,RVS);//LED��ת��˸ 
    ECPULSE1 = Read_DirEncoder(3);                                                   //����������3
    ECPULSE2 = Read_DirEncoder(2);                                                   //�ҵ��������2
    if(count_5ms == 0)
    {
      ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);                      //20689
      LQ_DMP_Read(); 
      
      
      BALANCE_OUT = PidLocCtrl(&Gyro_PID, ANGLE_OUT - (float)(gyroy-Gyroy_Set));           //���ٶȻ����
      
      BalDirgyro_out = PidLocCtrl(&BalDirgyro_PID, BalDir_out - (float)(gyroz-Gyroz_Set)); //�����ڻ����
    }
    if(count_10ms == 0)
    {
      if(Roll>-5) Roll=-1 ;//��С�Ƕ��޸������ⷢ������
      ANGLE = &Roll; //�ǶȲ�ֵ
      

      if(((ECPULSE1+ECPULSE2)>>2)>=(targetSpeed1-2)&&((ECPULSE1+ECPULSE2)>>2)<=(targetSpeed1+1)&&bell_flag) GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      else GPIO_SetBits(GPIOD,GPIO_Pin_6);
      
      kongzhi_2();     //1Ϊ���ٿ���    2Ϊ���ٿ���
      
     ANGLE_OUT = PidLocCtrl(&Angle_PID, *ANGLE - Angle_Set - SPEED_OUT);            //�ǶȻ����
      
      BalDir_out = PidLocCtrl(&BalDir_PID, Dir_Error);                               //�����⻷���
    }
    
/**************************************************
��ͨ����ʽ�ٶȿ���pid
***************************************************/    
//    if(count_20ms == 0)
//    {
//     ECPULSE = ECPULSE1+ECPULSE2;
//     SPEED_OUT = PidIncCtrl(&BalSpeed_PID, targetSpeed1 - (int)(ECPULSE/4)); //�ٶȻ����
//     SPEED_OUT = constrain_float(SPEED_OUT, -20, 20);                               //�ٶȻ��޷�
//     //BalSpeed_PID.out = constrain_float(BalSpeed_PID.out, -100, 100);                 //�ٶȻ��޷�
//    }
/**************************************************
�����pid�ٶȿ��ƣ����õ������ƣ���Ҫ�Ľ�
***************************************************/
    if(count_20ms == 0)
    {
     ECPULSE = ECPULSE1+ECPULSE2;
     SPEED_OUT = PID_realize(targetSpeed1,(int)(ECPULSE/4)); //�ٶȻ����
     SPEED_OUT = constrain_float(SPEED_OUT, -10, 10);                               //�ٶȻ��޷�
     //BalSpeed_PID.out = constrain_float(BalSpeed_PID.out, -100, 100);                 //�ٶȻ��޷�
    }
    

    //��ֱ�����뷽�����
    MotorDuty1 =  (int)(BALANCE_OUT + BalDirgyro_out);
    MotorDuty2 =  (int)(BALANCE_OUT - BalDirgyro_out);
    
    //���ռ�ձ��޷�
    if(MotorDuty1 > 8000)        MotorDuty1 = 8000;
    else if(MotorDuty1 < -8000) MotorDuty1 = -8000;
    if(MotorDuty2 > 8000)        MotorDuty2 = 8000;
    else if(MotorDuty2 < -8000) MotorDuty2 = -8000;
    BalMotorCtrl(MotorDuty1, MotorDuty2);
    
    count_5ms++;
    count_10ms++;
    count_20ms++;
    if(count_5ms  == 1)count_5ms  = 0;
    if(count_10ms == 2)count_10ms = 0;
    if(count_20ms == 4)count_20ms = 0;
    
    
    count_LED++;
    if(count_LED == 200)
    {
      LED_Ctrl(LED0,RVS);//LED��ת��˸ ֱ�ۼ���ж�ʱ���Ƿ����
      count_LED = 0;
    }  
  }  
}
void TIM7_IRQHandler(void)
{
  long sta = TIM1->SR;			// ��ȡ�ж�״̬
  TIM1->SR &= ~sta;					// ����ж�״̬
  //�û�����    
  LED_Ctrl(LED1,RVS);//LED��ת��˸
  
  
}
void TIM8_UP_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
  {
    TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
    //�û�����    
    LED_Ctrl(LED1,RVS);//LED��ת��˸
    
  }  
}

/*************************************************************************
*  �������ƣ�void TIMER_InitConfig(TIMER_Name_t timern, u16 nms)
*  ����˵�������PWM��ʼ��
*  ����˵����
//  @param      timern      ��ʱ��ͨ��
//  @param      nms          ��ʱ����pch,PWMͨ������Ӧ�ĵĶ�ʱ�����ܽ�

*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��TIMER_InitConfig(TIMER_1, 5); ʹ�ö�ʱ��1��Ϊ5msһ�ε������ж�
*************************************************************************/
void TIMER_InitConfig(TIMER_Name_t timern, u16 nms)
{  
  u32 freq_div = 0;                                          //��Ƶֵ
  u32 tmperiod;                                             //����ֵ
  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  if(TIMER_1 == timern)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);                //ʱ��ʹ��
  else if(TIMER_2 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if(TIMER_3 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
  else if(TIMER_4 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    
  else if(TIMER_5 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM5, ENABLE);
  else if(TIMER_6 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM6, ENABLE);    
  else if(TIMER_7 == timern)
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7, ENABLE);
  else if(TIMER_8 == timern)
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8, ENABLE);
  
  freq_div = SystemCoreClock/10000;                                       //���ٷ�Ƶ ,����Ϊ10K ,100us����һ��                        
  if(freq_div<1) freq_div=1;
  tmperiod = nms*10;                                                      //����ֵ nms*10*100us=nms
  if(tmperiod<1) tmperiod=1;
  
  //��ʱ����ʼ��
  TIM_TimeBaseStructure.TIM_Period = tmperiod-1;                          //�����Զ���װ�ؼĴ�������nms*10*100us=nms
  TIM_TimeBaseStructure.TIM_Prescaler = freq_div-1;                       //����Ϊ100us����һ��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ��Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                        //�ظ�����������Ϊ0
  TIM_TimeBaseInit((TIM_TypeDef *)TIMERx[timern], &TIM_TimeBaseStructure);//��ʼ��TIMxʱ��
  
  TIM_ITConfig((TIM_TypeDef *)TIMERx[timern],TIM_IT_Update,ENABLE );      //ʹ��TIM�ж�
  
  //�ж����ȼ�����
  if(TIMER_1 == timern)   nvic_init(TIM1_UP_IRQn, 0, 2, ENABLE);
  else if(TIMER_2 == timern)   nvic_init(TIM2_IRQn, 0, 2, ENABLE);
  else if(TIMER_3 == timern)   nvic_init(TIM3_IRQn, 0, 2, ENABLE);
  else if(TIMER_4 == timern)   nvic_init(TIM4_IRQn, 0, 2, ENABLE);
  else if(TIMER_5 == timern)   nvic_init(TIM5_IRQn, 0, 2, ENABLE);
  else if(TIMER_6 == timern)   nvic_init(TIM6_IRQn, 0, 2, ENABLE);
  else if(TIMER_7 == timern)   nvic_init(TIM7_IRQn, 0, 2, ENABLE);
  else if(TIMER_8 == timern)   nvic_init(TIM8_UP_IRQn, 0, 2, ENABLE);
  
  TIM_Cmd((TIM_TypeDef *)TIMERx[timern], ENABLE);  //ʹ��TIMx  
}



/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
���������� void Test_Timer56(void)
����  �ܡ� ���Զ�ʱ�жϺ�LED����˸
������ֵ�� ��
������ֵ�� ��
������ֵ�� �� 
����  �ߡ� L Q
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ Test_GPIO_LED()
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_TimerPIT56(void)
{
  GPIO_LED_Init();
  TIMER_InitConfig(TIMER_5, 50);
  TIMER_InitConfig(TIMER_6, 25);
  while(1)
  {
    LED_Ctrl(LED2,RVS);     //LED��ת��˸
    delayms(50);
  }
}


/***************************************************************
���Ʋ���
****************************************************************/
void kongzhi_1(void)//��򵥰�����ٿ���
{
     if(dotcnt) // �����ű��
      {
        
        Dir_Error = -(sumlie-65);//93���� 63
        if(Dir_Error>55)
           Dir_Error = 75;
        }
      else
      {
        
        Dir_Error = 65 ;
        
      }    
}

void kongzhi_2(void)
{
  
    if(dotcnt)
    {
        Dir_Error = -(sumlie-63);
        last_error = Dir_Error;   //��һ��Ŀ���λ��
        last_hang = sumhang;
        
        
        //����ٶȿ���
        if(sumhang>0 && sumhang<=40 )
        {
            targetSpeed1 = 80;//************************
            GPIO_SetBits(GPIOD,GPIO_Pin_6);
        }    
        else if(sumhang>40 && sumhang<=55 )
        {
            targetSpeed1 = 80;//************************
            GPIO_SetBits(GPIOD,GPIO_Pin_6);
        }
        else if(sumhang>55 && sumhang<=65 )
        {
            targetSpeed1 = 80;//************************
            GPIO_ResetBits(GPIOD,GPIO_Pin_6);
        }
        else if(sumhang>65 && sumhang<=80 )
        {
            targetSpeed1 = 70;//************************
            GPIO_ResetBits(GPIOD,GPIO_Pin_6);
//            if(abs(Dir_Error)>5)
//            {
//                Dir_Error = Dir_Error + 5;
//            }
        }
        else if(sumhang>80 && sumhang<=110 )
        {
            targetSpeed1 = 60;//************************
            GPIO_ResetBits(GPIOD,GPIO_Pin_6);
//            if(abs(Dir_Error)>3)
//            {
//                Dir_Error = Dir_Error + 3;
//            }
        }
        
        else if(sumhang>110 && sumhang<=120 )
        {
            Dir_Error = 50;
            targetSpeed1 = 70;//************************
        }
    }
    else if(!dotcnt)
    {
      dotcnt = 0;
      //�˴������ж�Ϊ�򵥵ļ��书�ܣ��������Ҳ��������ȶԵƵ���һ��λ�ý����ж�
      //���Խ����Ϊ����������ͷ��Ե��Ϊת�ٹ������ʧĿ������������ת3/4Ȧ
      //�˴��޸�����������ײ���bug
      if(last_error > 10 )
      {
        Dir_Error = 50 ;
      }
      else if(last_error < -10 )
      {
        Dir_Error = -50 ;
        
      }
      else if(last_error>=-10 && last_error<=10)
      {
          Dir_Error = 50;
      }
      targetSpeed1 =60;
        //Dir_Error = 65 ;
    }
}






