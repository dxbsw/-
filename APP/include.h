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
#ifndef __LQINCLUDES_H
#define __LQINCLUDES_H	  

#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "assert.h" 
#include "reg_common.h"
#include "reg_adc.h"
#include "reg_dma.h"
#include "reg_exti.h"
#include "reg_flash.h"
#include "reg_gpio.h" 
#include "reg_i2c.h"
#include "reg_rcc.h"
#include "reg_spi.h"
#include "reg_tim.h"
#include "reg_uart.h"
#include "hal_spi.h"

#include <LQ_AAConfig.h>
#include <LQ_AnoScope.h>
#include <LQ_ADC.h>
#include <LQ_CAMERA.h>
#include <LQ_Encoder.h>
#include <LQ_GPIO.h>
#include <LQ_GPIO_KEY.h>
#include <LQ_GPIO_LED.h>
#include <LQ_GPIO_EXIT.h>
#include <LQ_I2C.h>
#include <LQ_SOFTI2C.h>
#include <LQ_SPI.h>
#include <LQ_SOFTSPI.h>

#include "LQ_ImageProcess.h"
#include <LQ_Inductor.h>
#include <LQ_MotorServo.h>
#include <LQ_MT9V034.h>
#include <LQ_OLED096.h>
#include <LQ_PWM.h>
#include <LQ_SYS.h>
#include <LQ_TFT18.h>
#include <LQ_TIMER.h>
#include <LQ_UART.h>
#include <LQ_DMA.h>
#include <LQ_PID.h>
#include <LQ_ICM20689.h>
#include <LQ_I2C_MPU9250.h>
#include <LQ_MPU6050_DMP.h>
#include <LQ_Balance.h>

#define true 1
#define false 0


typedef struct
{
  int16_t ECPULSE1 ;          // �ٶ�ȫ�ֱ���
  int16_t ECPULSE2 ;          // �ٶ�ȫ�ֱ���
}TK_TypeDef;

extern float BALANCE_OUT;


#define EnableInterrupts asm(" CPSIE i");//�����ж�
#define DisableInterrupts asm(" CPSID i");//�����ж�
#endif











