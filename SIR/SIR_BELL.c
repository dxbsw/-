#include "SIR_BELL.h"

/*
���������� void SIR_BELL_Init(  )
����  �ܡ� ��������ʼ��
������ֵ�� pin ��gpio�ܽ�
������ֵ�� �� 
�������¡� 2021��1��22�� 
������汾�� V1.0
������������ SIR_BELL_Init()
*/
void SIR_BELL_Init()
{
  PIN_InitConfig(PD6, GPO, 1,GPIO_Mode_Out_PP);
}
