/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@��    д������Ƽ�
@E-mail  ��chiusir@163.com
@����IDE��IAR7.8 KEIL5.24�����ϰ汾
@ʹ��ƽ̨�������������ܿƼ�F3277���İ��ĸ��
@SYS  PLL��120MHz Ƶ��̫�߿����޷�����system_mm32f327x.c
@�����£�2022��02��22�գ��������£����ע���°棡
@���ܽ��ܣ�flash
@�����Ϣ�ο����е�ַ
@��    վ��http://www.lqist.cn
@�Ա����̣�http://longqiu.taobao.com
@
@����汾��V1.0 ��Ȩ���У���λʹ��������ϵ��Ȩ
@����������Ƶ��ַ��https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "HAL_conf.h"
#include "HAL_device.h"
#include "HAL_flash.h"
#include "LQ_FLASH.h"
void pid(pid_param_t * pid,int i,float numb);

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������u16 LQFLASH_ReadByte(u32 faddr)
����  �ܡ���ȡָ����ַ�İ���(16λ����)
������ֵ��faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
������ֵ����Ӧ��ַ������.
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������buf=LQFLASH_ReadByte(faddr)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
u16 LQFLASH_ReadByte(u32 faddr)
{
  return *(vu16*)faddr; 
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void LQFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
����  �ܡ�������д��(16λ����)
������ֵ��riteAddr:��ʼ��ַ
������ֵ��pBuffer:����ָ��
������ֵ��NumToWrite:����(16λ)��   
������ֵ����
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������buf=LQFLASH_ReadByte(faddr)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
  u16 i;
  for(i=0;i<NumToWrite;i++)
  {
    FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
    WriteAddr+=2;//��ַ����2.
  }  
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void LQFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
����  �ܡ���ָ����ַ��ʼд��ָ�����ȵ�����
������ֵ��WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
������ֵ��pBuffer:����ָ��
������ֵ��NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
������ֵ����
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������buf=LQFLASH_ReadByte(faddr)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#if LQ_FLASH_SIZE<256
#define LQ_SECTOR_SIZE 1024 //�ֽ�
#else 
#define LQ_SECTOR_SIZE	2048
#endif		 
u16 LQFLASH_BUF[LQ_SECTOR_SIZE/2];//�����2K�ֽ�

void LQFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
  u32 secpos;	   //������ַ
  u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
  u16 secremain;   //������ʣ���ַ(16λ�ּ���)	   
  u16 i;    
  u32 offaddr;     //ȥ��0X08000000��ĵ�ַ
  if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=(FLASH_BASE_ADDR+1024*FLASH_SIZE)))return;//�Ƿ���ַ
  FLASH_Unlock();						//����
  offaddr=WriteAddr-FLASH_BASE_ADDR;		//ʵ��ƫ�Ƶ�ַ.
  secpos=offaddr/LQ_SECTOR_SIZE;			//������ַ  0~127 for LQF103RBT6
  secoff=(offaddr%LQ_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
  secremain=LQ_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
  if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
  while(1) 
  {	
    LQFLASH_Read(secpos*LQ_SECTOR_SIZE+FLASH_BASE_ADDR,LQFLASH_BUF,LQ_SECTOR_SIZE/2);//������������������
    for(i=0;i<secremain;i++)//У������
    {
      if(LQFLASH_BUF[secoff+i]!=0XFFFF) break;//��Ҫ����  	  
    }
    if(i<secremain)//��Ҫ����
    {
      FLASH_ErasePage(secpos*LQ_SECTOR_SIZE+FLASH_BASE_ADDR);//�����������
      for(i=0;i<secremain;i++)//����
      {
        LQFLASH_BUF[i+secoff]=pBuffer[i];	  
      }
      LQFLASH_Write_NoCheck(secpos*LQ_SECTOR_SIZE+FLASH_BASE_ADDR,LQFLASH_BUF,LQ_SECTOR_SIZE/2);//д����������  
    }else LQFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
    if(NumToWrite==secremain)break;//д�������
    else//д��δ����
    {
      secpos++;				//������ַ��1
      secoff=0;				//ƫ��λ��Ϊ0 	 
      pBuffer+=secremain;  	//ָ��ƫ��
      WriteAddr+=secremain;	//д��ַƫ��	   
      NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
      if(NumToWrite>(LQ_SECTOR_SIZE/2))secremain=LQ_SECTOR_SIZE/2;//��һ����������д����
      else secremain=NumToWrite;//��һ����������д����
    }	 
  };	
  FLASH_Lock();//����
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void LQFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
����  �ܡ���ָ����ַ��ʼ����ָ�����ȵ�����
������ֵ��ReadAddr:��ʼ��ַ
������ֵ��pBuffer:����ָ��
������ֵ��NumToWrite:����(16λ)��
������ֵ����
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������buf=LQFLASH_ReadByte(faddr)
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
  u16 i;
  for(i=0;i<NumToRead;i++)
  {
    pBuffer[i]=LQFLASH_ReadByte(ReadAddr);//��ȡ2���ֽ�.
    ReadAddr+=2;//ƫ��2���ֽ�.	
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void Test_EEPROM(void)
����  �ܡ�����FLASH��д��ͨ���������в���
������ֵ����
������ֵ����
����  �ߡ�L Q
�������¡�2021��1��22�� 
������汾��V1.0
������������
---------------------------------------------------------------
//����ĸ����KEY0������д�뵱ǰ������ָ����ַ
//����ĸ����KEY2��������ȡָ����ַ���ݵ���Ļ
//��λ��Ƭ���������Ȼ�ܶ�ȡ��ԭ��д������ݣ�˵������ɹ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

float TEXT_Buffer[15]={-4.8,0,-1.55,-355,0,-100,0.35,0,0,0.4,0,0,120,0,80};
#define SIZE sizeof(TEXT_Buffer)	 	//���鳤��
#define FLASH_SAVE_ADDR  0X08070000 		//����FLASH �����ַ(����Ϊż��)
float datatemp[SIZE];
u8 cnt=1,pid_flag=0;
u8 key; 
char txt[16];
extern float PID_k=0.55;

extern pid_param_t Gyro_PID,Angle_PID,BalSpeed_PID,BalDirgyro_PID,BalDir_PID;

void Test_EEPROM(void)
{	
  
  LQFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);   //��ȡָ����ַ����
  TEXT_Buffer[0] = datatemp[0];         //-3.8
  TEXT_Buffer[1] = datatemp[1];  
  TEXT_Buffer[2] = datatemp[2];          //-1
  TEXT_Buffer[3] = datatemp[3];         //-3.8
  TEXT_Buffer[4] = datatemp[4];  
  TEXT_Buffer[5] = datatemp[5];          //-1
  TEXT_Buffer[6] = datatemp[6];         //-3.8
  TEXT_Buffer[7] = datatemp[6];  
  TEXT_Buffer[8] = datatemp[8];          //-1
  
  TEXT_Buffer[9] = datatemp[9];         //-3.8
  TEXT_Buffer[10] = datatemp[10];  
  TEXT_Buffer[11] = datatemp[11];          //-1
  TEXT_Buffer[12] = datatemp[12];         //-3.8
  TEXT_Buffer[13] = datatemp[13];  
  TEXT_Buffer[14] = datatemp[14];          //-1
  
  Gyro_PID.kp = TEXT_Buffer[0]*PID_k;         //-3.8
  Gyro_PID.ki = TEXT_Buffer[1]*PID_k;  
  Gyro_PID.kd = TEXT_Buffer[2]*PID_k;          //-1
  
  Angle_PID.kp = TEXT_Buffer[3]*PID_k;         //-3.8
  Angle_PID.ki = TEXT_Buffer[4]*PID_k;  
  Angle_PID.kd = TEXT_Buffer[5]*PID_k;          //-1
  
  BalSpeed_PID.kp = TEXT_Buffer[6];         //-3.8
  BalSpeed_PID.ki = TEXT_Buffer[6]/150;  
  BalSpeed_PID.kd = TEXT_Buffer[8];          //-1
  
  BalDirgyro_PID.kp = TEXT_Buffer[9];       
  BalDirgyro_PID.ki = TEXT_Buffer[10];
  BalDirgyro_PID.kd = TEXT_Buffer[11];
  //λ��
  BalDir_PID.kp = TEXT_Buffer[12];           //�����⻷������ֵ  ����ƫ��
  BalDir_PID.ki = TEXT_Buffer[13];
  BalDir_PID.kd = TEXT_Buffer[14];
  
  
  if(KEY_Read(DSW0)==0&&KEY_Read(DSW1)==0)
  {
    TFTSPI_CLS(u16WHITE);
    pid(&BalDirgyro_PID,3,0.01);//pid
    pid_TFT_show(3);
    sprintf(txt, "error:%.2f", Dir_Error);
    TFTSPI_P8X8Str(0, 10, txt, u16RED, u16BLUE);
    
  }
  
  if(KEY_Read(DSW0)==0&&KEY_Read(DSW1)==1)
  {
    pid(&BalDir_PID,4,1);//pid
    pid_TFT_show(4);
    sprintf(txt, "error:%.2f", Dir_Error);
    TFTSPI_P8X8Str(0, 10, txt, u16RED, u16BLUE);
    
  }
  
  if(KEY_Read(DSW0)==1&&KEY_Read(DSW1)==1)
  {
    pid(&BalSpeed_PID,2,0.01);//pid
    pid_TFT_show(2);
    sprintf(txt, "error:%.2f", Dir_Error);
    TFTSPI_P8X8Str(0, 10, txt, u16RED, u16BLUE);
  }
  
  if(KEY_Read(DSW0)==1&&KEY_Read(DSW1)==0)
  {
    
    sprintf((char*)txt,"Roll:%.2f", Roll);         // ��ʾС��ƽ����ֵ
    TFTSPI_P8X8Str(0,9,txt,u16RED,u16BLUE);
    sprintf(txt, "error:%.2f", Dir_Error);
    TFTSPI_P8X8Str(0, 10, txt, u16RED, u16BLUE);
      
      // ����ͱ�����������ʾ
//      sprintf(txt, "M1:%04d, M2:%04d ", MotorDuty1, MotorDuty2);
//      TFTSPI_P8X8Str(0, 11, txt, u16RED, u16BLUE);     // ���1-2��ֵ
//      sprintf(txt, "E1:%04d, E2:%04d ", ECPULSE1, ECPULSE2);
//      TFTSPI_P8X8Str(0, 12, txt, u16RED, u16BLUE);     // ������1-2��ֵ
//      sprintf(txt, "Dirgyro:%.2f", BalDirgyro_out);
//      TFTSPI_P8X8Str(0, 13, txt, u16RED, u16BLUE);     // IR�Ƶľ�ֵ��������ֵ
//      sprintf(txt, "Dirgyro:%.2f", BALANCE_OUT);
//      TFTSPI_P8X8Str(0, 14, txt, u16RED, u16BLUE);     // IR�Ƶľ�ֵ��������ֵ
      
    }
    

}
/*pid��������flash*/
void pid(pid_param_t * pid,int i,float numb)
{
  key=KEY_Scan(1);
  switch(key)
  {
  case 1:
    {
      switch(cnt)
      {
      case 1: TEXT_Buffer[0+i*3]=pid->kp+numb;break;
      case 2: TEXT_Buffer[1+i*3]=pid->ki+numb;break;
      case 3: TEXT_Buffer[2+i*3]=pid->kd+numb;break;
      }
      LQFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);//д�뵱ǰ������ָ����ַ	
      LQFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);   //��ȡָ����ַ����
      pid->kp = datatemp[0+i*3];         //-3.8
      pid->ki = datatemp[1+i*3];  
      pid->kd = datatemp[2+i*3];          //-1
    }break;
    
  case 2:
    {
      switch(cnt)
      {
      case 1: TEXT_Buffer[0+i*3]=pid->kp-numb;break;
      case 2: TEXT_Buffer[1+i*3]=pid->ki-numb;break;
      case 3: TEXT_Buffer[2+i*3]=pid->kd-numb;break;
      }                               //�䶯��ֵ���Ա�۲��д�Ƿ�ɹ�
      LQFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);//д�뵱ǰ������ָ����ַ	
      LQFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);   //��ȡָ����ַ����
      pid->kp = datatemp[0+i*3];         //-3.8
      pid->ki = datatemp[1+i*3];  
      pid->kd = datatemp[2+i*3];          //-1
    }break;
    
  case 3:
    {
      cnt++;
      delayms(100);
      if(cnt>3)cnt=1;
    }break;
  }
}

void pid_TFT_show(char i)//��Ļ��ʾ
{
  if(i==0)
  {
    switch(cnt)
    {
    case 1:
      sprintf(txt,"Gyro_P:%.2f",Gyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_I:%.2f",Gyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_D:%.2f",Gyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 2:
      sprintf(txt,"Gyro_P:%.2f",Gyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_I:%.2f",Gyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_D:%.2f",Gyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 3:
      sprintf(txt,"Gyro_P:%.2f",Gyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_I:%.2f",Gyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Gyro_D:%.2f",Gyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      break;
    }
  }
  
  if(i==1)
  {
    switch(cnt)
    {
    case 1:
      sprintf(txt,"Angle_P:%.2f",Angle_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_I:%.2f",Angle_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_D:%.2f",Angle_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 2:
      sprintf(txt,"Angle_P:%.2f",Angle_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_I:%.2f",Angle_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_D:%.2f",Angle_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 3:
      sprintf(txt,"Angle_P:%.2f",Angle_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_I:%.2f",Angle_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Angle_D:%.2f",Angle_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      break;
    }
  }
  
  if(i==2)
  {
    switch(cnt)
    {
    case 1:
      sprintf(txt,"Speed_P:%.2f",BalSpeed_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_I:%.3f",BalSpeed_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_D:%.2f",BalSpeed_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 2:
      sprintf(txt,"Speed_P:%.2f",BalSpeed_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_I:%.3f",BalSpeed_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_D:%.2f",BalSpeed_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 3:
      sprintf(txt,"Speed_P:%.2f",BalSpeed_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_I:%.3f",BalSpeed_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Speed_D:%.2f",BalSpeed_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      break;
    }
  }
  
  if(i==3)
  {
    switch(cnt)
    {
    case 1:
      sprintf(txt,"Dirgyro_P:%.2f",BalDirgyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_I:%.2f",BalDirgyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_D:%.2f",BalDirgyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 2:
      sprintf(txt,"Dirgyro_P:%.2f",BalDirgyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_I:%.2f",BalDirgyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_D:%.2f",BalDirgyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 3:
      sprintf(txt,"Dirgyro_P:%.2f",BalDirgyro_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_I:%.2f",BalDirgyro_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"Dirgyro_D:%.2f",BalDirgyro_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      break;
    }
  }
  
  if(i==4)
  {
    switch(cnt)
    {
    case 1:
      sprintf(txt,"BalDir_P:%.2f",BalDir_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_I:%.2f",BalDir_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_D:%.2f",BalDir_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 2:
      sprintf(txt,"BalDir_P:%.2f",BalDir_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_I:%.2f",BalDir_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_D:%.2f",BalDir_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      break;
    case 3:
      sprintf(txt,"BalDir_P:%.2f",BalDir_PID.kp);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,1,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_I:%.2f",BalDir_PID.ki);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);             //��Ļ��ʾ����
      sprintf(txt,"BalDir_D:%.2f",BalDir_PID.kd);                  //ת��Ϊ�ַ������Ա���Ļ��ʾ����
      TFTSPI_P8X8Str(1,5,txt,u16GREEN,u16BLUE);             //��Ļ��ʾ����
      break;
    }
  }
}
