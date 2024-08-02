
#include "include.h"


static int key_flag = 0;
/*************************************************************************
*  �������ƣ�void GPIO_KEY_Init(void)
*  ����˵����GPIO��ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void GPIO_KEY_Init(void)
{
  PIN_InitConfig(PD0, GPI, 1,GPIO_Mode_IPU);
  PIN_InitConfig(PD1, GPI, 1,GPIO_Mode_IPU);
  PIN_InitConfig(PD2, GPI, 1,GPIO_Mode_IPU);
  PIN_InitConfig(PD3, GPI, 1,GPIO_Mode_IPU);    
  PIN_InitConfig(PD4, GPI, 1,GPIO_Mode_IPU);
  PIN_InitConfig(PA2, GPI, 1,GPIO_Mode_IPU);    
}

/*************************************************************************
*  �������ƣ�int KEY_Read_All(void)
*  ����˵������ȡ����״̬
*  ����˵����
*  �������أ�����״̬��0/1
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
int KEY_Read_All(void)
{
  static int s1=0,s2 =0,s3=0;
  static int Ls1=0,Ls2=0,Ls3=0;

  Ls1=s1,Ls2=s2,Ls3=s3;
  s1 = PIN_Read(KEY0p);//���水ť
  s2 = PIN_Read(KEY1p);//�м䰴ť
  s3 = PIN_Read(KEY2p);//���水ť
  
    if(Ls1==1&&s1==0)//���水ť
  {
   delayms(10);
   if(s1==0)
   {
    key_flag=1;//����
   }
  }
  else if(Ls2==1&&s2==0)//�м䰴ť
  {
   delayms(10);
   if(s2 == 0)
   {
    key_flag=2;//�м�
   }
  }
  else if(Ls3==1&&s3==0)//���水ť
  {
   delayms(10);
   if(s3 == 0)
   {
    key_flag=3;//����
   }
  }
  return key_flag;
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@�������ƣ�u8 KEY_Scan(u8 mode)
@����˵��������������
@����˵����mode��0��֧����������1֧��������
@�������أ���
@�޸�ʱ�䣺2022/02/24
@��    ע������״̬������ʾ
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u8 KEY_Scan(u8 mode)
{	 
  static u8 key_up=1;//�����ɿ���־λ
  if(mode)key_up=1;  //֧������	  
  if(key_up&&(KEY_Read(KEY0)==0||KEY_Read(KEY1)==0||KEY_Read(KEY2)==0))
  {
    delayms(10); 
    key_up=0;
    if(KEY_Read(KEY0)==0)return 1;
    else if(KEY_Read(KEY1)==0)return 2;
    else if(KEY_Read(KEY2)==0)return 3;
    else if(KEY_Read(KEY0)==0&&KEY_Read(KEY1)==0)return 4;
    else if(KEY_Read(KEY2)==0&&KEY_Read(KEY1)==0)return 5;

  }else if(KEY_Read(KEY0)==1&&KEY_Read(KEY1)==1&&KEY_Read(KEY2)==1)key_up=1; 
  
  return 0;
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@�������ƣ�unsigned char KEY_Read(KEYn_e KEYno)
@����˵������ȡ����״̬
@����˵����KEYn_e KEYno�������
@�������أ�����״̬��0/1
@�޸�ʱ�䣺2022/02/24
@��    ע��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
unsigned char KEY_Read(KEYn_e KEYno)
{
  switch(KEYno)
  {
  case KEY0:
    return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4 );//ĸ���ϰ���0
    //break;    
  case KEY1:
    return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2 );//ĸ���ϰ���1
    //break;   
  case KEY2:
    return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3);//ĸ���ϰ���2
    //break;    
  case DSW0:
    return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0 );//ĸ���ϲ��뿪��0
    //break;
  case DSW1:
    return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1 );//ĸ���ϲ��뿪��1
    //break;
  default:
    return 0XFF;
  }
  //return 0;
}

