

#include "include.h"


// ͼ��ԭʼ���ݴ�� //
unsigned char Image_Data[IMAGEH][IMAGEW];

// ѹ����֮�����ڴ����Ļ��ʾ���� 
unsigned char Image_Use[LCDH][LCDW];

// ��ֵ��������OLED��ʾ������ 
unsigned char Bin_Image[LCDH][LCDW];

uint8_t labelBuffer[LCDW*LCDH]={0};//��Ǿ���
int area_map[100]={0};

unsigned char Camera_Flag=0;
int16_t OFFSET0 = 0;      //��Զ������������ֵ�ۺ�ƫ����
int16_t OFFSET1 = 0;      //�ڶ���
int16_t OFFSET2 = 0;      //�����������
int16_t TXV = 0;          //���ε���߶ȣ��Ҹ߶�


/*************************************************************************
*  �������ƣ�void Test_CAMERA (void)
*  ����˵��������ͷ��������
*  ����˵����void
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ע����Ҫʹ��  ������Ű棨��ɫ��ת�����������°�����ͷģ��
*************************************************************************/
void Test_CAMERA (void)
{
  
  TFTSPI_Init(0);               //TFT1.8��ʼ��0:����  1������
  TFTSPI_CLS(u16BLUE);          //����
  
  // ����ͷ��ʼ�� //
  CAMERA_Init(100);
  
  while (1)
  {
    if (Camera_Flag == 1)
    {
      // �������ͷ�ɼ���ɱ�־λ  �����������򲻻��ٴβɼ����� 
      Camera_Flag = 0;       
      
      // ��ȡ����ʹ�õ�����
      Get_Use_Image();    
      
#if 1 //��ʾԭʼͼ��
      //TFT1.8��̬��ʾ����ͷͼ��
      TFTSPI_Road(0, 0, LCDH, LCDW, (unsigned char *)Image_Use);
      
#else //��ʾ��ֵ��ͼ��
      
      // ��ֵ�� //
      Get_Bin_Image(0);
      
      // ��ʾ����ͷͼ��            
      TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char *) Bin_Image);             
#endif
      
      //�ϱ����ݸ���λ�� �����ٶȱȽ��� ע����λ��ͼ��������Ϊ120*188
      //CAMERA_Reprot();  //ɽ����λ����ʾ  
      
      LED_Ctrl(LED0, RVS);
    }
    LED_Ctrl(LED2, RVS);
  }
}
/*************************************************************************
*  �������ƣ�void CAMERA_Reprot (void)
*  ����˵���������ϱ���λ��
*  ����˵����void
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ע����λ����֡ͷ������������
*************************************************************************/
void CAMERA_Reprot (void)
{
  short j, i;
  
//  UART_PutChar(UART1,0x01);  //ɽ����λ��֡ͷ0x01
//  UART_PutChar(UART1,0xFE);  //ɽ����λ��֡ͷ0xFE
  
  UART_PutChar(UART1,0xFE);  //��Դ��λ��֡ͷ0xef
  UART_PutChar(UART1,0xEF);  //��Դ��λ��֡ͷ0xfe
  
  for (i = 0; i < IMAGEH; i++)
  {
    for (j = 0; j < IMAGEW; j++)
    {
      if (Image_Data[i][j] == 0xfe)  //��ֹ������֡β
      {
        Image_Data[i][j] = 0xff;
      }
      UART_PutChar(UART1,Image_Data[i][j]); //��������
    }
  }
  UART_PutChar(UART1,0xEF);  //��Դ��λ��֡β
  UART_PutChar(UART1,0xFE);  //��Դ��λ��֡β
  
//  UART_PutChar(UART1,0xFE);  //ɽ����λ��֡ͷ0x01
//  UART_PutChar(UART1,0x01);  //ɽ����λ��֡ͷ0xFE
}

/*************************************************************************
* @brief    ����ͷMT9V034���ж�
* @date     2020/4/8
*************************************************************************/
void MT9V034_DMA_START(void)
{
  MT9V034_DMA_CH->CNDTR = MT9V034_IMAGEH * MT9V034_IMAGEW;     //DMA��������ͷ���ݵ�����Ϊ����ͷ�ֱ��ʡ�
  MT9V034_DMA_CH->CCR |= DMA_CCR1_EN;                          //��ʼ
}
/*************************************************************************
* @brief    MT9V03X����ͷDMA����ж�
* @note
* @see
* @date     2020/4/8
*************************************************************************/
void MT9V034_DMA_CLS(void)
{
  MT9V034_DMA_CH->CCR &= (u16)(~DMA_CCR1_EN);   //�ر�DMA1
  Camera_Flag = 1;                              //һ��ͼ��Ӳɼ���ʼ���ɼ�������ʱ3.8MS����(50FPS��188*120�ֱ���)  
}
/*************************************************************************
*  �������ƣ�void CAMERA_Init (unsigned char fps)
*  ����˵��������ͷ��ʼ��
*  ����˵����fps:  ֡��
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*  ����ͷ��һЩ��������LQ_MT9V034.c�еĺ궨�����޸�
*  CAMERA_Init(50);   //��ʼ��MT9V034  50֡ V2�������ͷע��ʹ�ð�ɫ������Ű�ת����,
*************************************************************************/
void CAMERA_Init (unsigned char fps)
{ 
  // ��ʼ������ͷ ����IO
  PIN_InitConfig(PF0, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF1, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF2, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF3, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF4, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF5, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF6, GPI, 0,GPIO_Mode_FLOATING);
  PIN_InitConfig(PF7, GPI, 0,GPIO_Mode_FLOATING);
  
  // ���۳�ʼ��
  MT9V034_Init(fps);   
  
  // ����ͷDMA��ʼ������ʱ������DMA�������ݰ���    
  DMA_CameraInitConfig(MT9V034_DMA_CH,(u32)GPIOF_BYTE0, (u32)Image_Data, IMAGEH*IMAGEW);
  
  // PLCK���ų�ʼ��������ʱ����ͨ��DMA�������ݰ���
  DMA_CameraTriggerTimerInit(TIMER_1, MT9V034_PCLK_PIN); //GPIO����TIM��ֻ�����Ź̶��ļ�������ѡ��  
  
  // VSYNC��ʼ�� ���жϳ�ʼ�� G1
  PIN_Exti(MT9V034_VSYNC_PIN, EXTI_Trigger_Falling, GPIO_Mode_FLOATING,0,0); 
  
}
/*************************************************************************
*  �������ƣ�void Get_Use_Image (void)
*  ����˵����������ͷ�ɼ���ԭʼͼ�����ŵ�����ʶ�������С
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2022��3��28��
*  ��    ע��  IMAGEWΪԭʼͼ��Ŀ�ȣ�����Ϊ188��OV7725Ϊ320
*       IMAGEHΪԭʼͼ��ĸ߶ȣ�����Ϊ120��OV7725Ϊ240
*************************************************************************/
void Get_Use_Image(void)
{
  short i = 0, j = 0, row = 0, line = 0;
  
  for (i = 0; i < LCDH; i++)          //���۸� 120 
  {
    for (j = 14; j <= LCDW+14; j++)     //���ۿ�188
    {
      Image_Use[row][line] = Image_Data[i][j];
      line++;
    }
    line = 0;
    row++;
  }
}

/************************************************************************
*  �������ƣ�void Get_Bin_Image (unsigned char mode)
*  ����˵����ͼ���ֵ����Bin_Image[][]
*  ����˵����mode  ��
*    0��ʹ�ô����ֵ
*    1��ʹ��ƽ����ֵ
*    2: sobel ���ӸĽ���  �ֶ���ֵ��ͬʱ�����Ϊ��ȡ���ص�ͼ��
*    3��sobel ���ӸĽ���   ��̬��ֵ��ͬʱ�����Ϊ��ȡ���ص�ͼ��
*  �������أ���
*  �޸�ʱ�䣺2022��3��29��
*  ��    ע��  Get_Bin_Image(0); //ʹ�ô�򷨶�ֵ��
************************************************************************/
void Get_Bin_Image (unsigned char mode)
{
  unsigned short i = 0, j = 0;
  unsigned short Threshold = 0;
  unsigned long tv = 0;
  //char txt[16];
  
  if (mode == 0)
  {
    Threshold = GetOSTU(Image_Use);  //�����ֵ
  }
  if (mode == 1)
  {
    //�ۼ�
    for (i = 0; i < LCDH; i++)
    {
      for (j = 0; j < LCDW; j++)
      {
        tv += Image_Use[i][j];   //�ۼ�
      }
    }
    Threshold =(unsigned short)(tv / LCDH / LCDW);   //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100
    Threshold = Threshold+10;      //�˴���ֵ���ã����ݻ����Ĺ������趨
  }
  else if (mode == 2)
  {
    Threshold = 80;                          //�ֶ�������ֵ
    lq_sobel(Image_Use, Bin_Image, (unsigned char) Threshold);
    
    return;
    
  }
  else if (mode == 3)
  {
    lq_sobelAutoThreshold(Image_Use, Bin_Image);  //��̬������ֵ
    return;
  }
  /*
#ifdef USEOLED
  sprintf(txt,"%03d",Threshold);//��ʾ��ֵ
  OLED_P6x8Str(80,0,txt);
#else
  sprintf(txt, "%03d", Threshold);  //��ʾ��ֵ
  TFTSPI_P6X8Str(0,7, txt, u16RED, u16BLUE);
#endif
  */
  /* ��ֵ�� */
  for (i = 0; i < LCDH; i++)
  {
    for (j = 0; j < LCDW; j++)
    {
      if (Image_Use[i][j] > Threshold) //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
        Bin_Image[i][j] = 1;
      else
        Bin_Image[i][j] = 0;
    }
  }
}
/************************************************************************
*  �������ƣ�short GetOSTU (unsigned char tmImage[LCDH][LCDW])
*  ����˵�����������ֵ��С
*  ����˵����tmImage �� ͼ������
*  �������أ���
*  �޸�ʱ�䣺2022��3��29��
*  ��    ע��  GetOSTU(Image_Use);//�����ֵ
Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ���� 1
4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��
�ı���w0��        ��ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����
������)  * ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
6) i++��ת��4)��ֱ��iΪ256ʱ��������
7) �����g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
************************************************************************/
short GetOSTU (unsigned char tmImage[LCDH][LCDW])
{
  signed short i, j;
  unsigned long Amount = 0;
  unsigned long PixelBack = 0;
  unsigned long PixelshortegralBack = 0;
  unsigned long Pixelshortegral = 0;
  signed long PixelshortegralFore = 0;
  signed long PixelFore = 0;
  float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
  signed short MinValue, MaxValue;
  signed short Threshold = 0;
  unsigned char HistoGram[256];              //
  
  for (j = 0; j < 256; j++)
    HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ
  
  for (j = 0; j < LCDH; j++)
  {
    for (i = 0; i < LCDW; i++)
    {
      HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    }
  }
  
  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ
  
  if (MaxValue == MinValue)
    return MaxValue;         // ͼ����ֻ��һ����ɫ
  if (MinValue + 1 == MaxValue)
    return MinValue;        // ͼ����ֻ�ж�����ɫ
  
  for (j = MinValue; j <= MaxValue; j++)
    Amount += HistoGram[j];        //  ��������
  
  Pixelshortegral = 0;
  for (j = MinValue; j <= MaxValue; j++)
  {
    Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
  }
  SigmaB = -1;
  for (j = MinValue; j < MaxValue; j++)
  {
    PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
    PixelFore = Amount - PixelBack;           //�������ص���
    OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
    OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
    PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
    PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
    MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
    MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
    if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
    {
      SigmaB = Sigma;
      Threshold = j;
    }
  }
  return Threshold+30;                        //���������ֵ;
}
/*************************************************************************
*  �������ƣ�lq_sobel
*  ����˵��������soble���ؼ�����ӵ�һ�ֱ��ؼ��
* @param    imageIn    ��������
*           imageOut   �������      ����Ķ�ֵ����ı�����Ϣ
*           Threshold  ��ֵ
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע����
*************************************************************************/
void lq_sobel (unsigned char imageIn[LCDH][LCDW], unsigned char imageOut[LCDH][LCDW], unsigned char Threshold)
{
  //* ����˴�С //
  short KERNEL_SIZE = 3;
  short xStart = KERNEL_SIZE / 2;
  short xEnd = LCDW - KERNEL_SIZE / 2;
  short yStart = KERNEL_SIZE / 2;
  short yEnd = LCDH - KERNEL_SIZE / 2;
  short i, j, k;
  short temp[4];
  for (i = yStart; i < yEnd; i++)
  {
    for (j = xStart; j < xEnd; j++)
    {
      // ���㲻ͬ�����ݶȷ�ֵ  //
      temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
        - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]        // {-1, 0, 1},
          - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];    // {-1, 0, 1}};
      
      temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
        - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]       // { 0,  0,  0},
          - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];    // { 1,  1,  1}};
      
      temp[2] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j - 1]       //  0, -1, -1
        - (short) imageIn[i][j + 1] + (short) imageIn[i + 1][j]       //  1,  0, -1
          - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j - 1];    //  1,  1,  0
      
      temp[3] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j + 1]       // -1, -1,  0
        - (short) imageIn[i][j - 1] + (short) imageIn[i + 1][j]       // -1,  0,  1
          - (short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j + 1];    //  0,  1,  1
      
      temp[0] = abs(temp[0]);
      temp[1] = abs(temp[1]);
      temp[2] = abs(temp[2]);
      temp[3] = abs(temp[3]);
      
      // �ҳ��ݶȷ�ֵ���ֵ  //
      for (k = 1; k < 4; k++)
      {
        if (temp[0] < temp[k])
        {
          temp[0] = temp[k];
        }
      }
      
      if (temp[0] > Threshold)
      {
        imageOut[i][j] = 1;
      }
      else
      {
        imageOut[i][j] = 0;
      }
    }
  }
}

/*************************************************************************
*  �������ƣ�lq_sobel
*  ����˵��������soble���ؼ�����ӵ�һ���Զ���ֵ���ؼ��
* @param    imageIn    ��������
*           imageOut   �������      ����Ķ�ֵ����ı�����Ϣ *
*  �������أ�void
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ע����Ҫʹ��  ������Ű棨��ɫ��ת�����������°�����ͷģ��
*************************************************************************/
void lq_sobelAutoThreshold (unsigned char imageIn[LCDH][LCDW], unsigned char imageOut[LCDH][LCDW])
{
  //* ����˴�С //
  short KERNEL_SIZE = 3;
  short xStart = KERNEL_SIZE / 2;
  short xEnd   = LCDW - KERNEL_SIZE / 2;
  short yStart = KERNEL_SIZE / 2;
  short yEnd   = LCDH - KERNEL_SIZE / 2;
  short i, j, k;
  short temp[4];
  for (i = yStart; i < yEnd; i++)
  {
    for (j = xStart; j < xEnd; j++)
    {
      // ���㲻ͬ�����ݶȷ�ֵ  //
      temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
        - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]       // {-1, 0, 1},
          - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];    // {-1, 0, 1}};
      
      temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
        - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]       // { 0,  0,  0},
          - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];    // { 1,  1,  1}};
      
      temp[2] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j - 1]       //  0, -1, -1
        - (short) imageIn[i][j + 1] + (short) imageIn[i + 1][j]       //  1,  0, -1
          - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j - 1];    //  1,  1,  0
      
      temp[3] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j + 1]       // -1, -1,  0
        - (short) imageIn[i][j - 1] + (short) imageIn[i + 1][j]       // -1,  0,  1
          - (short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j + 1];    //  0,  1,  1
      
      temp[0] = abs(temp[0]);
      temp[1] = abs(temp[1]);
      temp[2] = abs(temp[2]);
      temp[3] = abs(temp[3]);
      
      // �ҳ��ݶȷ�ֵ���ֵ  //
      for (k = 1; k < 4; k++)
      {
        if (temp[0] < temp[k])
        {
          temp[0] = temp[k];
        }
      }
      
      // ʹ�����ص����������ص�֮�͵�һ������    ��Ϊ��ֵ  //
      temp[3] = (short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j] + (short) imageIn[i - 1][j + 1]
        + (short) imageIn[i][j - 1] + (short) imageIn[i][j] + (short) imageIn[i][j + 1]
          + (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j] + (short) imageIn[i + 1][j + 1];
      
      if (temp[0] > temp[3] / 12.0f)
      {
        imageOut[i][j] = 1;
      }
      else
      {
        imageOut[i][j] = 0;
      }
      
    }
  }
}

/*---------------------------------------------------------------
����    ����Bin_Image_Filter
����    �ܡ��������
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Bin_Image_Filter (void)
{
  int16_t nr; //��
  int16_t nc; //��
  
  for (nr = 1; nr < LCDH - 1; nr++)
  {
    for (nc = 1; nc < LCDW - 1; nc = nc + 1)
    {
      if ((Bin_Image[nr][nc] == 0)
          && (Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] > 2))
      {
        Bin_Image[nr][nc] = 1;
      }
      else if ((Bin_Image[nr][nc] == 1)
               && (Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] < 2))
      {
        Bin_Image[nr][nc] = 0;
      }
    }
  }
}

/**************************************************************************
*                                                                          *
*  �������ƣ�Seek_Road(void)                                           *
*  ����˵����Ѱ�Ұ�ɫ����ƫ��ֵ                                            *
*  ����˵������                                                            *
*  �������أ�ֵ�Ĵ�С                                                      *
*  �޸�ʱ�䣺2017-07-16                                                    *
*  ��    ע�����м�Ϊ0������һ���Ҳ��һ����ֵ����1�����                *
*            ��������ӵ�һ�п�ʼ�������ڶ��н�����                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ��ߣ�                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ�ұߡ�                        *
**************************************************************************/
void Seek_Road (void)
{
    int16_t nr; //��
    int16_t nc; //��
    int16_t temp = 0; //��ʱ��ֵ
    //for(nr=1; nr<MAX_ROW-1; nr++)
    temp = 0;
    for (nr = 8; nr < 40; nr++)
    {
        for (nc = MAX_COL / 2; nc < MAX_COL; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp;
            }
        }
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                --temp;
            }
        }
    }
    OFFSET0 = temp;
    temp = 0;
    for (nr = 40; nr < 80; nr++)
    {
        for (nc = MAX_COL / 2; nc < MAX_COL; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp;
            }
        }
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                --temp;
            }
        }
    }
    OFFSET1 = temp;
    temp = 0;
    for (nr = 80; nr < 110; nr++)
    {
        for (nc = MAX_COL / 2; nc < MAX_COL; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp;
            }
        }
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                --temp;
            }
        }
    }
    OFFSET2 = temp;
    return;
}

/*****************************************************************************
*�������ƣ�void PushQueue(Queue *queue,int data)
*����˵�������
*����˵������
*�������أ���
*�޸�ʱ�䣺2022��4��3��
*��    ע�����,�������ǶԶ�β�Ĵ���,�����ڴ�����β
******************************************************************************/
void PushQueue(Queue *queue,int data)
{
    QNode *p=NULL;//*p�Ƕ��нڵ�ָ�� QNode�Ƕ������ڽڵ����Ե�˵��
    p=(QNode*)malloc(sizeof(QNode));//����һ�����н��(p��������ڵ�ĵ�ַ)
    p->data=data;
    if(queue->first==NULL)//����ʱδָ�����׺Ͷ�β ����λ��һ����� �������㶨Ϊ���׺Ͷ�β
    {
     queue->first=p;
     queue->last=p;
     p->next=NULL;
    }
    else
    {
     p->next=NULL;//���µĽ����ڶ�βΪ��
     queue->last->next=p;//�ɵĶ��н�β����һ����P
     queue->last=p;//�µĶ��н�β
    }
}
/*****************************************************************************
*�������ƣ�int PopQueue(Queue *queue)
*����˵��������
*����˵������
*�������أ���
*�޸�ʱ�䣺2022��4��3��
*��    ע������,�������ǶԶ��׵Ĵ���,�ͷ��ڴ浯������
******************************************************************************/
int PopQueue(Queue *queue)
{
    QNode *p=NULL;
    int data;
    if(queue->first==NULL)//�ӿ���popʧ�ܷ���-1
    {
     return -1;
    }
     p=queue->first;//ָ��Pָ�����
     data=p->data;//��ȡ���׵�����
    if(queue->first->next == NULL)//��Ϊ���һ�����
    {
     queue->first=NULL;
     queue->last=NULL;
    }
    else
    {
     queue->first=p->next;
    }
    free(p);//�����׽�㵯�����ͷſռ�
    return data;
}
/*****************************************************************************
*�������ƣ�void SearchNeighbor_4(unsigned char *bitmap, unsigned char *labelmap,uint16 labelIndex,uint16 pixelIndex, Queue *queue)
*����˵����������������
*����˵����bitmap:�����ͼ��  labelmap:��Ǿ���
*�������أ���
*�޸�ʱ�䣺2022��4��3��
*��    ע��
******************************************************************************/
int area;//��¼��ͨ��Ŀ���ͨ�����
int Connected_x[100];
int Connected_y[100];
int32_t Connected_light[100];//��ÿ�������ƽ������



//����������
static int NeighborDirection[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
void SearchNeighbor_4(unsigned char *bitmap, unsigned char *labelmap,uint16_t labelIndex,uint16_t pixelIndex, Queue *queue,int x,int y,unsigned char *lightmap)
{
  int searchIndex,i,length; 
  int qx,qy;
  labelmap[pixelIndex]=labelIndex;//��ʼλ�õı����
  length=LCDW*LCDH;//����ά����ת��Ϊһά����������ݸ���
  for(i=0;i<4;i++)
  {
   searchIndex=pixelIndex+NeighborDirection[i][0]*LCDW+NeighborDirection[i][1];//��ά����ת��Ϊһά����
   if(searchIndex >= 0 && searchIndex <length && bitmap[searchIndex] == 1 && labelmap[searchIndex] == 0)//������޳�ͼ��Χ,��8������δ�����İ׵����
   {
     labelmap[searchIndex]=labelIndex;//��������������ģ���е��������
     area++;
     
     qy=y;
     qx=(int)((searchIndex-y)/(LCDW));
     Connected_x[labelIndex]+=qx;
     Connected_y[labelIndex]+=qy;
     Connected_light[labelIndex]+=lightmap[searchIndex];
     
     
     //��ֹ���������������
     if(area>=65535) area=65535;
     PushQueue(queue,searchIndex);//����������δ���������İ׵���� ��������Ϊ������
   }
  } 
}
/*****************************************************************************
*�������ƣ�void ConnectedComponentLabeling(unsigned char *bitmap, unsigned char * labelmap)
*����˵������ͨ�����,���ű���ж�
*����˵����bitmap:�����ͼ��  labelmap:��Ǿ���
*�������أ������ܵ��������
*�޸�ʱ�䣺2022��4��3��
*��    ע����
*ʹ��˵����ֻ�����������鼴�ɣ�i��2��ʼ
          area_map[i]Ϊÿ��������������
          Connected_x[i],Connected_y[i],Ϊÿ���������������
          Connected_light[i]��Ϊÿ�����������ƽ��ֵ
******************************************************************************/
//��Ƶ���ͨ�����ʮһ������
uint16_t areamax=0;//���Χ��ͨ��Ŀ���ͨ����� 
uint8_t labelmax=0,labeldel[100]={0},labelcount=0;//���Χ��ͨ���� ����ͨ��С��3����ͨ������ �ܵ���ͨ�����


//bitmap:�����ͼ��  labelmap:��Ǿ���
void ConnectedComponentLabeling(unsigned char *bitmap, unsigned char * labelmap)
{
  uint8_t i,j,labelIndex=1,del=0,x=1;
  int index,popIndex;
  Queue *queue = NULL;
  queue = (Queue*)malloc(sizeof(Queue));
  queue->first = NULL;
  queue->last = NULL;
  memset(labelmap,0,LCDW*LCDH);//��ձ�Ǿ���,ÿ����0����Ҫ
  memset(labeldel,0,100);//���ͨ��С��3����ͨ������
  memset(area_map,0,100);
  memset(Connected_x,0,100);
  memset(Connected_y,0,100);
  memset(Connected_light,0,100);
  areamax=0;
  labelcount=0;
  labelmax=1;
  int flag_1;
  int last_labelIndex=0;
  
  for(i = 1; i <=LCDH-1 ; i++)
  {
    for(j = 1; j <=LCDW-1 ; j++)
    {
      index=i*(LCDW)+j;//�����ĵ� ��ά������һά����洢 �����ķ�ʽ
      if(bitmap[index]==1 && labelmap[index]==0)//�׵���δ�����
      {
        labelIndex++;//�������  
        SearchNeighbor_4(bitmap,labelmap,labelIndex,index,queue,i,j,(unsigned char *)Image_Use);//������������� ������ģ���ϼ���������
        popIndex=PopQueue(queue);//ȷ����һ��������������
        while(popIndex>-1)// pop��ͬʱ ����������������Ƿ����µİ׵㲢�����һֱ�ظ�  һֱpopֱ��������û�н���ʱ�������Ϊ������
        {
          SearchNeighbor_4(bitmap,labelmap,labelIndex,popIndex,queue,i,j,(unsigned char *)Image_Use);//�����а׵���������һ�����������
          popIndex = PopQueue(queue);//������������������Ϊ��һ�ε�������ʼλ��,֪��������������������,��������������
        }
      }
      flag_1=labelIndex - last_labelIndex;
      last_labelIndex = labelIndex;
      
      if(flag_1==1)
      {
          area_map[labelIndex]=area; //������ͨ������
          
          Connected_x[labelIndex]=(int)(Connected_x[labelIndex]/area);  //��ͨ������x
          Connected_y[labelIndex]=(int)(Connected_y[labelIndex]/area);  //��ͨ������y
          Connected_light[labelIndex]=(int)(Connected_light[labelIndex]/area);
          
          
          flag_1 = 0;
      }
      
 
      if(x!=labelIndex)//��ֹһ����ͨ����
      { 
        x=labelIndex;//X�������м�����ͨ����
        if(area>areamax)//ȷ�����Χ����ͨ��
        {
          areamax=area;
          labelmax=labelIndex;
        }
        
        if(area<=1)//     �������ж�,���п���
        {
          labeldel[del]=labelIndex;
          del++;
          if(del>=9) del=9;
        }
        
        area=0;
      }
    }
  }
  free(queue);//һ��ͼ�������ͷŶ��пռ�
  
  //�����ܵ��������
  labelcount=labelIndex-1;
  
}
