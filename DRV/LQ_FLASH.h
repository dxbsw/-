/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@��    д������Ƽ�
@E-mail  ��chiusir@163.com
@����IDE��IAR7.8 KEIL5.24�����ϰ汾
@ʹ��ƽ̨�������������ܿƼ�F3277���İ��ĸ��
@SYS  PLL��120MHz Ƶ��̫�߿����޷�����system_mm32f327x.c
@�����£�2022��02��22�գ��������£����ע���°棡
@���ܽ��ܣ�
@�����Ϣ�ο����е�ַ
@��    վ��http://www.lqist.cn
@�Ա����̣�http://longqiu.taobao.com
@
@����汾��V1.0 ��Ȩ���У���λʹ��������ϵ��Ȩ
@����������Ƶ��ַ��https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_FLASH_h
#define _LQ_FLASH_h
#include <stdint.h>

#define FLASH_SIZE 512 	 		  //FLASH������С(��λΪK)

#define FLASH_BASE_ADDR             (0x08000000)        //FALSH��ʼ��ַ
#define FLASH_PAGE_SIZE             1024                //ÿҳ1K�ֽ�
#define FLASH_SECTION_SIZE          (FLASH_PAGE_SIZE*4) //ÿ����4K�ֽ�

//��16������ÿ����4K��
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
#define PAGE_WRITE_START_ADDR  ((uint32_t)0x0800F000) //��60K��ʼ
#define PAGE_WRITE_END_ADDR    ((uint32_t)0x08010000) //63K����

#define FLASH_PAGES_TO_BE_PROTECTED FLASH_WRProt_Pages60to63

typedef enum
{
  FLASH_PAGE_0,
  FLASH_PAGE_1,
  FLASH_PAGE_2,
  FLASH_PAGE_3,
}FLASH_PAGE_enum;

u16   LQFLASH_ReadByte(u32 faddr);		                        //����һ���ֽ� 
u32   LQFLASH_ReadLenByte(u32 ReadAddr,u16 Len);			//ָ����ַ��ʼ��ȡָ����������
void LQFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
void LQFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void LQFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
void pid_TFT_show(char i); //��Ļ��ʾ

void Test_EEPROM(void);

#endif
