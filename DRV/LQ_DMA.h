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

#ifndef _LQ_DMA_H_
#define _LQ_DMA_H_
#include "include.h"
#include "hal_dma.h"
#include "hal_rcc.h"
#include "hal_tim.h"

void DMA_CameraInitConfig(DMA_Channel_TypeDef* dma_ch,u32 src_addr, u32 des_addr, u32 size);
void DMA_CameraTriggerTimerInit(TIMER_Name_t timern, GPIO_Name_t pin);
void DMA_CameraTriggerTimer1PE7Init();
#endif /* 0_APPSW_TRICORE_APP_LQ_GPIO_H_ */
