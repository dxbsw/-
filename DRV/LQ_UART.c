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
#include <LQ_GPIO.h>
#include "stdio.h"

//////////////////////////////////���²���Ϊ���ܲ���/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
u8 RX2CHAR=0;
extern signed short realSpeed3, realSpeed4;
void UART1_IRQHandler(void)
{
  //�����ж�
  if(UART_GetFlagStatus(UART1, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART1,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART1,UART_GetChar(UART1));
  }
}

void UART2_IRQHandler(void)
{
  //�����ж�
  if(UART_GetFlagStatus(UART2, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART2,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART2,UART_GetChar(UART2));
    
  }
}
void UART3_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART3, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART3,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART3,UART_GetChar(UART3));
    
  }
}
void UART4_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART4, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART4,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART4,UART_GetChar(UART4));
    
  }
}
void UART5_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART5, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART5,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART5,UART_GetChar(UART5));
    
  }
}
void UART6_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART6, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART6,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART6,UART_GetChar(UART6));
    
  }
}
void UART7_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART7, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART7,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART7,UART_GetChar(UART7));
    
  }
}
void UART8_IRQHandler(void)
{  
  if(UART_GetFlagStatus(UART8, UART_IT_RXIEN)  != RESET)
  {
    UART_ClearITPendingBit(UART8,UART_IT_RXIEN);
    /* �û����� */
    UART_PutChar(UART8,UART_GetChar(UART8));
    
  }
}
/*************************************************************************
*  �������ƣ�void UART1_InitConfig(unsigned long baudrate)
*  ����˵��������ģ���ʼ��
*  ����˵����
* @param    RxPin   �� ���ڽ��չܽ�
* @param    TxPin   �� ���ڷ��͹ܽ�
* @param    baudrate�� ������
*  �������أ��ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��void UART1_InitConfig(115200);   //��ʼ������1 ������ 115200 ����żУ�� 1ֹͣλ ʹ�ùܽ�
*************************************************************************/
void UART_PinConfig(UART_TX_e tx_pin, UART_RX_e rx_pin)
{
  PIN_InitConfig((GPIO_Name_t)(tx_pin &0xFF), GPO, 0, GPIO_Mode_AF_PP);  
  GPIO_PinAFConfig((GPIO_TypeDef *)(PORTX[(tx_pin&0x00F0) >> 4]),  tx_pin & 0x0F, (u16)tx_pin >> 12);
  PIN_InitConfig((GPIO_Name_t)(rx_pin &0xFF), GPI, 0, GPIO_Mode_IN_FLOATING);  
  GPIO_PinAFConfig((GPIO_TypeDef *)(PORTX[(rx_pin&0x00F0) >> 4]),  rx_pin & 0x0F, (u16)rx_pin >> 12);  
}
/*************************************************************************
*  �������ƣ�void UART_InitConfig(UART_TypeDef* UARTx,unsigned long baudrate,UART_TX_e tx_pin, UART_RX_erx_pin)
*  ����˵��������ģ���ʼ��
*  ����˵����
* @param    RxPin   �� ���ڽ��չܽ�
* @param    TxPin   �� ���ڷ��͹ܽ�
* @param    baudrate�� ������
*  �������أ��ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_InitConfig(USAR1,9600,UART1_TX_A9,UART1_RX_A10); //��ʼ������1 ������ 115200 ����żУ�� 1ֹͣλ ʹ�ùܽ�
*************************************************************************/
void UART_InitConfig(UART_TypeDef* UARTx,unsigned long baudrate,UART_TX_e tx_pin, UART_RX_e rx_pin)
{
  UART_InitTypeDef UART_InitStructure;  
  
  //��������ʹ��
  if(UART1 == UARTx) RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE); //APB2
  else if(UART2 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);  
  else if(UART3 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE); 
  else if(UART4 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART4, ENABLE); 
  else if(UART5 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART5, ENABLE); 
  else if(UART6 == UARTx) RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART6, ENABLE);    //APB2
  else if(UART7 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART7, ENABLE);
  else if(UART8 == UARTx) RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART8, ENABLE); 	
  //���ų�ʼ��
  UART_PinConfig(tx_pin, rx_pin);
  
  //���ڲ�������
  UART_InitStructure.UART_BaudRate = baudrate;
  UART_InitStructure.UART_WordLength = UART_WordLength_8b;
  UART_InitStructure.UART_StopBits = UART_StopBits_1;
  UART_InitStructure.UART_Parity = UART_Parity_No;
  UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  UART_InitStructure.UART_Mode = UART_Mode_Tx | UART_Mode_Rx;
  
  //ʹ�ܴ���
  UART_RX_IRQ_Config(UARTx,ENABLE);
  UART_Init(UARTx, &UART_InitStructure);
  UART_Cmd(UARTx, ENABLE);
  
  
}

/*************************************************************************
*  �������ƣ�void UART_RX_IRQ_Config(UART_NAME_t UART_x,u8 status)
*  ����˵�����������ڽ����ж�
*  ����˵����
* @param    UART_x       ����ͨ��
* @param    status      ʹ�ܻ��ֹ
*  �������أ��ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_RX_IRQ_Config(UART_1, ENABLE);  //��������1�����ж�
*************************************************************************/
void UART_RX_IRQ_Config(UART_TypeDef* UARTx,u8 status)
{
  UART_ITConfig(UARTx, UART_IT_RXIEN, ENABLE);
  if(UART1 == UARTx) nvic_init(UART1_IRQn, 0, 0, status);
  else if(UART2 == UARTx) nvic_init(UART2_IRQn, 0, 0, status); 
}

/*************************************************************************
*  �������ƣ�void UART_RX_IRQ_Config(UART_TypeDef* UARTx,u8 status)
*  ����˵�����������ڽ����ж�
*  ����˵����
* @param    UART_x       ����ͨ��
* @param    status      ʹ�ܻ��ֹ
*  �������أ��ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_RX_IRQ_Config(UART_1, ENABLE);  //��������1�����ж�
*************************************************************************/
void UART_TX_IRQ_Config(UART_TypeDef* UARTx,u8 status)
{
  UART_ITConfig(UARTx, UART_IT_TXIEN, ENABLE);
  if(UART1 == UARTx) nvic_init(UART1_IRQn, 0, 0, status);
  else if(UART2 == UARTx) nvic_init(UART2_IRQn, 0, 0, status);  
}
/*************************************************************************
*  �������ƣ�void UART_PutChar(UART_t  uratn, char ch)
*  ����˵����UART�����ֽں���,ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ ch    �� Ҫ��ӡ���ַ�
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutChar(UART0, 'a');  //��ӡ�ַ�a
*************************************************************************/
void UART_PutChar(UART_TypeDef* UARTx,char ch)
{
  UART_SendData(UARTx, ch);
  while (UART_GetFlagStatus(UARTx, UART_FLAG_TXEPT) == RESET);
}

/*************************************************************************
*  �������ƣ�void UART_PutStr(UART_t  uratn, char *str)
*  ����˵����UART�����ַ�������(�� NULL ֹͣ����),ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ str   �� Ҫ��ӡ���ַ�����ַ
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutStr(UART3, "123456789"); //����9���ֽ�
*************************************************************************/
void UART_PutStr(UART_TypeDef* UARTx,char *str)
{
  while(*str)
  {
    UART_PutChar(UARTx,*str++);
  }
}
//��������վ��λ���ӿں���
void UART_PutBuff(UART_TypeDef* UARTx, u8 *buff, u16 len)
{
  while(len--)																				
  {
    UARTx->TDR = *buff++;														// ���뻺����
    while(!(UARTx->CSR & UART_CSR_TXC));						// �ȴ��������		
  }
}
/*************************************************************************
*  �������ƣ�char UART_GetChar(UART_t  uratn)
*  ����˵����UART��ȡ�ֽ� ʹ��ǰ���ȳ�ʼ����Ӧ���� ����ǰ��ȷ���н��յ����� �����ȴ����ݵ���
*  ����˵����uratn �� UART0 - UART3
*  �������أ���ȡ�ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_GetChar(UART3); //����һ���ַ�
*************************************************************************/
char UART_GetChar(UART_TypeDef* UARTx)
{  
  return (UART_ReceiveData(UARTx));
}


/*******************************************************************************
�˺���Ϊprintf�����ӿڣ����ò���Ϊ��
project-->options-->general options-->library configurations-->library����ѡ��full

Ҳ���Զ�Ӧ�޸ĺ�ʹ�ñ�Ĵ��ڡ�
*******************************************************************************/
int fputc(int ch, FILE *f)
{  
  UART_SendData(UART1, ch);
  while (UART_GetFlagStatus(UART1, UART_FLAG_TXEPT) == RESET);  
  
  return ch;  
} 

/*************************************************************************
*  �������ƣ�void Test_Bluetooth(void);
*  ����˵����UART���Ժ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void Test_Bluetooth(void)
{  
  UART_InitConfig(UART1,115200,UART1_TX_A9,UART1_RX_A10); //��ʼ������1 ������ 115200 ����żУ�� 1ֹͣλ ʹ�ùܽ�
  UART_PutStr(UART1," UART1 LongQiu \r\n"); //�����ַ�������λ��
  while(1)
  {
    UART_PutChar(UART1,'L');                     //���� �ֽڵ�UART��
    delayms(500);                                  //��ʱ�ȴ�
    UART_PutChar(UART1,'Q');                      //���� �ֽڵ�UART��
    
    UART_PutStr(UART1,"UART1 LongQiu \r\n");      //�����ַ�������λ��
    
    LED_Ctrl(LED0,RVS);        //��ƽ��ת,LED��˸
    delayms(500);              //��ʱ�ȴ�
  }
}

//
