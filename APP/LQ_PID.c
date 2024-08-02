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
#include <LQ_PID.h>

/*************************************************************************
*  �������ƣ�float constrain_float(float amt, float low, float high)
*  ����˵�����޷�����
*  ����˵����
* @param    amt   �� ����
* @param    low   �� ���ֵ
* @param    high  �� ���ֵ
*  �������أ���
*  �޸�ʱ�䣺2020��4��1��
*  ��    ע��
*************************************************************************/
float constrain_float(float amt, float low, float high)
{
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid������ʼ������
void PidInit(pid_param_t * pid)
{
  pid->kp        = 0;
  pid->ki        = 0;
  pid->kd        = 0;
  pid->imax      = 0;
  pid->out_p     = 0;
  pid->out_i     = 0;
  pid->out_d     = 0;
  pid->out       = 0;
  pid->integrator= 0;
  pid->last_error= 0;
  pid->last_derivative   = 0;
  pid->last_t    = 0;
}

/*************************************************************************
*  �������ƣ�float constrain_float(float amt, float low, float high)
*  ����˵����pidλ��ʽ���������
*  ����˵����
* @param    pid     pid����
* @param    error   pid�������
*  �������أ�PID������
*  �޸�ʱ�䣺2020��4��1��
*  ��    ע��
*************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{
  /* �ۻ���� */
  pid->integrator += error;
  
  /* ����޷� */
  constrain_float(pid->integrator, -pid->imax, pid->imax);
  
  
  pid->out_p = pid->kp * error;
  pid->out_i = pid->ki * pid->integrator;
  pid->out_d = pid->kd * (error - pid->last_error);
  
  pid->last_error = error;
  
  pid->out = pid->out_p + pid->out_i + pid->out_d;
  
  return pid->out;
}
/*************************************************************************
*  �������ƣ�float constrain_float(float amt, float low, float high)
*  ����˵����pid����ʽ���������
*  ����˵����
* @param    pid     pid����
* @param    error   pid�������
*  �������أ�PID������   ע���������Ѿ��������ϴν��
*  �޸�ʱ�䣺2020��4��1��
*  ��    ע��
*************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error)
{
  
  pid->out_p = pid->kp * (error - pid->last_error);
  pid->out_i = pid->ki * error;
  pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);
  
  pid->last_derivative = error - pid->last_error;
  pid->last_error = error;
  
  pid->out += pid->out_p + pid->out_i + pid->out_d;
  
  return pid->out;
}

/*************************************************************************

�����

************************************************************************/
struct B_pid {
     float SetSpeed; //�����趨ֵ
     float ActualSpeed; //����ʵ��ֵ
     float err; //����ƫ��ֵ
     float err_last; //������һ��ƫ��ֵ
     float Kp, Ki, Kd; //������������֡�΢��ϵ��
     float SetDuty; //���壨����ִ�����ı�����
     float integral; //�������ֵ
 }Bj_pid;



void PID_init(void) {
     Bj_pid.SetSpeed = 0.0;
     Bj_pid.ActualSpeed = 0.0;
     Bj_pid.err = 0.0;
     Bj_pid.err_last = 0.0;
     Bj_pid.SetDuty = 0.0;
     Bj_pid.integral = 0.0;
     Bj_pid.Kp = 0.8;
     Bj_pid.Ki = 0;    //�����˻���ϵ��
     Bj_pid.Kd = 0.40;

 }
/******************************************************
set_speed   �趨ֵ
actual_speed ����ֵ

*******************************************************/
 float PID_realize(float set_speed,float actual_speed) {
     float index;
     Bj_pid.SetSpeed = 100;
     Bj_pid.ActualSpeed = (actual_speed/set_speed)*100;
     Bj_pid.err = Bj_pid.SetSpeed - Bj_pid.ActualSpeed;

     if (abs(Bj_pid.err) > 30)           //����ֹ���
     {
         index = 0;
     }
     else if (abs(Bj_pid.err) <20) {
         index = 1.0;
         Bj_pid.integral += Bj_pid.err;
     }
     else {
         index = (100 - abs(Bj_pid.err)) / 10;
         Bj_pid.integral += Bj_pid.err;
     }
     Bj_pid.SetDuty = Bj_pid.Kp*Bj_pid.err + index * Bj_pid.Ki*Bj_pid.integral + Bj_pid.Kd*(Bj_pid.err - Bj_pid.err_last);

     Bj_pid.err_last = Bj_pid.err;
     if(Bj_pid.SetDuty>100)Bj_pid.SetDuty=100;
     if(Bj_pid.SetDuty<0)Bj_pid.SetDuty=0;
     return Bj_pid.SetDuty;
 }