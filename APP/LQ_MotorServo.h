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
#ifndef SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_
#define SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_

#include "include.h"

#define  Kbat       2    // ��ص�ѹ�Ե��ռ�ձȵ�Ӱ��ϵ��
#define  Kencoder   5    // �������ٶȶԵ��ռ�ձȵ�Ӱ��ϵ��
#define  Koffset    1    // �������ʶԵ��ռ�ձȵ�Ӱ��ϵ��

#define TURN_LEFT    0   // ��ת
#define TURN_RIGHT   1   // ��ת
#define IN_GARAGE    1   // ���
#define OUT_GARAGE   0   // ����

#define Servo_Delta 150            //�������ת���Ĳ�ֵ�������ͺţ����˺Ͷ���۳��й�
#define Servo_Center_Mid 1440      //���ֱ����ֵ��
#define Servo_Left_Max   (Servo_Center_Mid+Servo_Delta)      //�����ת����ֵ
#define Servo_Right_Min  (Servo_Center_Mid-Servo_Delta)      //�����ת����ֵ����ֵ��������÷�ʽ�йأ���ʽ

#define MtTargetDuty  2000  //���ռ�ձ�ֵ�����ֵ��ʵ����Ҫ��ȥ��ص�ѹ�����������������ʣ��ﲻ����ֵ

#define MTGPIO1p      GPIOG,GPIO_Pin_5 
#define MTGPIO2p      GPIOG,GPIO_Pin_6   
#define MTGPIO3p      GPIOG,GPIO_Pin_7   
#define MTGPIO4p      GPIOG,GPIO_Pin_8  

extern int16_t ServoDuty;
extern int MotorDuty1;      // �������ռ�ձ���ֵ
extern int MotorDuty2;      // �������ռ�ձ���ֵ

extern uint16_t BatVolt;         // ��ص�ѹ�ɼ�
extern unsigned char Camera_Flag; // ����ʶ
extern uint8_t CircleNumber;// �뻷������0������Ĭ��1�� ;���ĸ���һ���ڱ���ǰ��������ʱ��֪����
extern int16_t OFFSET0;    // ��Զ������������ֵ�ۺ�ƫ����
extern int16_t OFFSET1;    // �ڶ���
extern int16_t OFFSET2;    // �����������

void EncInit(void);
void MotorInit(u16 freq);
void MotorCtrl(int16_t motor1, int16_t motor2);
void MotorCtrl4w(int16_t motor1, int16_t motor2,int16_t motor3, int16_t motor4);
void BalMotorCtrl(int16_t motor1, int16_t motor2);
void TestMotor(void);
void ServoInit(u16 freq);
void ServoCtrl(uint16_t duty);
void TestServo(void);
void SpeedCtrl(signed short x, signed short y, signed short z);
#endif /* SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_ */
