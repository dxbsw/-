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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef SRC_APPSW_TRICORE_MAIN_LQ_BALANCE_H_
#define SRC_APPSW_TRICORE_MAIN_LQ_BALANCE_H_

extern float Dir_Error;

void Balance_CAR (void);
extern volatile int sumlie,sumhang;
extern unsigned short Threshold;
extern volatile uint8_t dotcnt;
void Seek_Beacon (void);
void TFT_show(void);

void quanzhong_light(void);
int find_max(void);
void quanzhong_light_panduan(void);
float Square_detection (int x,int y);
void eye_show (void);//��ʾʮ��

#endif /* SRC_APPSW_TRICORE_MAIN_LQ_BALANCE_H_ */