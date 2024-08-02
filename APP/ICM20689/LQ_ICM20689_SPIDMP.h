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
���������_LQ_ICM20689_DMP_���ܣ�������������վ4.34��ʾ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_ICM20689_DMP_
#define _LQ_ICM20689_DMP_

#include "LQ_SOFTI2C.h"

extern short   gyro[3], accel[3], sensors;
extern float   Pitch, Roll; 

extern int LQ_I2C_Write(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *dat);
extern int LQ_I2C_Read(unsigned char addr, unsigned char reg, unsigned int len, unsigned char *buf);
extern void delayms(u16 nms);
extern void delayus(u16 nus);

void Test_LQDMP(void);
int LQ_DMP_Init(void);
int LQ_DMP_Read(void);
int LQ_ICM20689_DMP_Init(void);
int LQ_ICM20689_DMP_Read(void);

// ��ʼ�����
int icm20689_disable_dmp(unsigned char wake_state);
int icm20689_disable_fifo(unsigned char wake_state);
int icm20689_reset_fifo(unsigned char wake_state);
int icm20689_enable_fifo(unsigned char wake_state);
int icm20689_enable_dmp(unsigned char wake_state);
int icm20689_write_mems(unsigned char wake_state, unsigned int reg, unsigned int len, unsigned char *buf);

// ��ֵ���
long inv_icm20689_convert_mult_q30_fxp(long a_q30, long b_q30);
long inv_icm20689_convert_fast_sqrt_fxp(long x0_q30);
int inv_icm20689_convert_test_limits_and_scale_fxp(long *x0_q30, int *pow);
int inv_icm20689_convert_get_highest_bit_position(unsigned long *value);
	
// ����
int do_test(int self_test_flag, int *gyro_result, int *accel_result, int lp_mode);
	
#endif
 