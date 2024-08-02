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
#ifndef __LQ_ICM20689_H
#define __LQ_ICM20689_H

#define ICM20689_ADDR                   0x68  //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
#define ICM20689_ADDR2                  0x69  //ȡ����AD0��״̬

#define ICM20689_ID	                0x98	//IIC��ַ�Ĵ���(Ĭ����ֵ0x98��ֻ��)

#define ICM_SELF_TEST_X_GYRO            0x00
#define ICM_SELF_TEST_Y_GYRO            0x01 
#define ICM_SELF_TEST_Z_GYRO            0x02

#define ICM_SELF_TESTX_REG		0X0D	//ACCEL�Լ�Ĵ���X
#define ICM_SELF_TESTY_REG		0X0E	//ACCEL�Լ�Ĵ���Y
#define ICM_SELF_TESTZ_REG		0X0F	//ACCEL�Լ�Ĵ���Z

#define ICM_SELF_TESTA_REG		0X10	//�Լ�Ĵ���A

#define ICM_XG_OFFS_USRH                0x13	
#define ICM_XG_OFFS_USRL                0x14
#define ICM_YG_OFFS_USRH                0x15
#define ICM_YG_OFFS_USRL                0x16
#define ICM_ZG_OFFS_USRH                0x17
#define ICM_ZG_OFFS_USRL                0x18

#define ICM_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define ICM_CFG_REG			0X1A	//���üĴ���
#define ICM_GYRO_CFG_REG		0X1B	//���������üĴ���
#define ICM_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define ICM_ACCEL_CONFIG_2              0x1D
#define ICM_LOW_POWER_MODE		0x1E
#define ICM_MOTION_DET_REG		0X1F	//�˶���ֵⷧ���üĴ���
#define ICM_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���

#define ICM_I2CMST_STA_REG		0X36	//IIC����״̬�Ĵ���
#define ICM_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define ICM_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define ICM_INT_STA_REG			0X3A	//�ж�״̬�Ĵ���

#define ICM_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define ICM_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define ICM_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define ICM_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define ICM_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define ICM_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define ICM_TEMP_OUTH_REG		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define ICM_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

#define ICM_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define ICM_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define ICM_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define ICM_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define ICM_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define ICM_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���

#define ICM_I2CSLV0_DO_REG		0X63	//IIC�ӻ�0���ݼĴ���
#define ICM_I2CSLV1_DO_REG		0X64	//IIC�ӻ�1���ݼĴ���
#define ICM_I2CSLV2_DO_REG		0X65	//IIC�ӻ�2���ݼĴ���
#define ICM_I2CSLV3_DO_REG		0X66	//IIC�ӻ�3���ݼĴ���

#define ICM_I2CMST_DELAY_REG	        0X67	//IIC������ʱ����Ĵ���
#define ICM_SIGPATH_RST_REG		0X68	//�ź�ͨ����λ�Ĵ���
#define ICM_MDETECT_CTRL_REG	        0X69	//�˶������ƼĴ���
#define ICM_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define ICM_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define ICM_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define ICM_FIFO_CNTH_REG		0X72	//FIFO�����Ĵ����߰�λ
#define ICM_FIFO_CNTL_REG		0X73	//FIFO�����Ĵ����Ͱ�λ
#define ICM_FIFO_RW_REG			0X74	//FIFO��д�Ĵ���

#define WHO_AM_I		        0X75	//����ID�Ĵ���

void ICM_SPI_Init(void);
unsigned char ICM_Read_Byte(unsigned char reg);
void  ICM_Write_Byte(unsigned char reg,unsigned char value);
void  ICM_Read_Len(unsigned char reg,unsigned char len,unsigned char *buf);
void  ICM_Get_Raw_data(unsigned short *ax,unsigned short *ay,unsigned short *az,unsigned short *gx,unsigned short *gy,unsigned short *gz);
void  ICM_Get_Accelerometer(unsigned short *ax,unsigned short *ay,unsigned short *az);
void  ICM_Get_Gyroscope(unsigned short *gx,unsigned short *gy,unsigned short *gz);
unsigned short ICM_Get_Temperature(void);
void  ICM_Set_Rate(unsigned short rate);
void  ICM_Set_LPF(unsigned short lpf);
void  ICM_Set_Accel_Fsr(unsigned char fsr);
void  ICM_Set_Gyro_Fsr(unsigned char fsr);
unsigned char ICM20689_Init(void);
void Test_ICM20689(void);
void Test_ICM20689DMP(void);
void icm20689_reset(void);

#endif


