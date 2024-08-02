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
#ifndef __LQ_UART_BT_H_
#define __LQ_UART_BT_H_

#include "include.h"
#include "hal_uart.h"

//L.Q UART RX �ܽ�ö��
typedef enum
{//UART�л� ���ܸ���BIT15-12 ����BIT10-8 PORT����BIT7-4  �ܽ�˳��BIT3-0
  UART1_RX_A10 = 0x700A,  // AF7 Ĭ������
  UART1_RX_B7  = 0x7017,  // AF7 PORTB B10
  UART2_RX_A3  = 0x7003,  // AF7
  UART2_RX_D6  = 0x7036,  // AF7
  UART3_RX_B11 = 0x701B,  // AF7
  UART3_RX_C11 = 0x702B,  // AF7
  UART3_RX_D9  = 0x7039,  // AF7
  UART4_RX_A1  = 0x8001,  // AF8
  UART4_RX_C11 = 0x802B,  // AF8
  UART5_RX_A5  = 0x8005,  // AF8
  UART5_RX_D2  = 0x8032,  // AF8
  UART6_RX_B1  = 0x8011,  // AF8
  UART6_RX_C7  = 0x8027,  // AF8
  UART7_RX_B7  = 0x8017,  // AF8
  UART7_RX_E7  = 0x8047,  // AF8
  UART8_RX_D1  = 0x8031,  // AF8
  UART8_RX_E0  = 0x8040,  // AF8
}UART_RX_e;

//L.Q UART TX �ܽ�ö��
typedef enum
{  
  UART1_TX_A9  = 0x7009,  //Ĭ������
  UART1_TX_B6  = 0x7016,  // AF7
  UART2_TX_A2  = 0x7002,  // AF7
  UART2_TX_D5  = 0x7035,  // AF7
  UART3_TX_B10 = 0x701A,  // AF7
  UART3_TX_C10 = 0x702A,  // AF7
  UART3_TX_D08 = 0x7038,  // AF7
  UART4_TX_A00 = 0x8000,  // AF8
  UART4_TX_C10 = 0x802A,  // AF8
  UART5_TX_A04 = 0x8004,  // AF8
  UART5_TX_C12 = 0x802C,  // AF8	
  UART6_TX_B00 = 0x8010,  // AF8
  UART6_TX_C06 = 0x8026,  // AF8
  UART7_TX_B06 = 0x8016,  // AF8
  UART7_TX_E08 = 0x8048,  // AF8
  UART8_TX_D00 = 0x8030,  // AF8
  UART8_TX_E01 = 0x8041,  // AF8  
}UART_TX_e;

typedef enum
{
  UART_1,
  UART_2,
  UART_3,
  UART_4,
  UART_5,
  UART_6,
  UART_7,
  UART_8,
}UARTn_e;

void UART_RX_IRQ_Config(UART_TypeDef* UARTx,u8 status);
void UART_TX_IRQ_Config(UART_TypeDef* UARTx,u8 status);
void UART_InitConfig(UART_TypeDef* UARTx,unsigned long baudrate,UART_TX_e tx_pin, UART_RX_e rx_pin);
void UART_PutChar(UART_TypeDef* UARTx,char ch);
void UART_PutStr(UART_TypeDef* UARTx,char *str);
//��������վ��λ���ӿں���
void UART_PutBuff(UART_TypeDef* UARTx, u8 *buff, u16 len);
char UART_GetChar(UART_TypeDef* UARTx);
void Test_Bluetooth(void);

#endif
