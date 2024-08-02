
#include "include.h"


//ֱ��������
extern pid_param_t Gyro_PID,Angle_PID,BalSpeed_PID,BalDirgyro_PID,BalDir_PID;

extern int16_t aacx, aacy, aacz;
extern int16_t gyrox, gyroy, gyroz;

// ��й�һ��ƫ����
  
extern float Dir_Error;
extern uint8_t labelcount;
int bell_flag=1;
extern int16_t targetSpeed1;

unsigned short Threshold = 0;
volatile uint8_t dotcnt=0;
volatile uint8_t dotlie[10000];
volatile uint8_t dothang[10000];
volatile int sumlie=0,sumhang=0;
volatile uint8_t batchargeflg = 1;
volatile uint8_t beaconFlashCnt= 1;

uint8_t shang=0,xia=0,zuo=0,you=0;

/*************************************************************************
*  �������ƣ�void Balance_CAR(void)
*  ����˵����ֱ����ֱ������
-->����PID����ֱ�������ٶȻ�Ϊ�ڻ����ǶȻ�Ϊ�⻷
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2021��04��01��
*  ��    ע��ֱ����Ҫʱ����ƣ��轫����Ķ�ʱ���жϺ�������ԭ��ʱ���жϺ���
*************************************************************************/
void Balance_CAR (void)
{ 
  uint16_t cnt=0;
  char  txt[10];
  CAMERA_Init(100);          // ����ͷ��ʼ�� 
  EncInit();            // ��ʼ������������  ������2�ͱ�����3
  MotorInit(12500);     // ���������PWMΪ12.5Khz  ʹ��PC6��PC7���Ƶ��1��PC8��PC9���Ƶ��2
  TFTSPI_Init(0);        //LCD��ʼ��  0:����  1������
  SOFT_IIC_Init();            //IIC��ʼ��   6050�����ǳ�ʼ��
  ICM20689_Init();            //icm20689��ʼ�� SPI CS-PE10  SCK-PE12 MISO-PE13 MOSI-PE14 
  LQ_DMP_Init();            //MPU6050DMP();   
  GPIO_KEY_Init();  
  PidInit(&Gyro_PID);     //ֱ���ڻ�������ʼ��
  PidInit(&Angle_PID);    //ֱ���⻷������ʼ��
  PidInit(&BalSpeed_PID);    //�ٶȻ�������ʼ��
  PidInit(&BalDirgyro_PID);   //�����ڻ�������ʼ��
  PidInit(&BalDir_PID);       //�����⻷������ʼ��
  
  PID_init();//�����
  
  //PID ������Ҫ���е��� 
  //λ��
  //ֱ���ڻ�������ֵ  ���ٶ�
    float PID_k=0.8;//����ֱ����Ӳ�̶ȣ�����ʱĬ��Ϊ1
    
  Gyro_PID.kp = -3*PID_k;
  Gyro_PID.ki = -0;          
  Gyro_PID.kd = -2.05*PID_k;
  //λ��
  //ֱ���⻷������ֵ   �Ƕ�
  Angle_PID.kp = -296.8*PID_k;
  Angle_PID.ki = -0;         
  Angle_PID.kd = -82*PID_k;
  

  //����
  //�ٶȻ�������ֵ
                                    
  BalSpeed_PID.kp = 0.08;
  BalSpeed_PID.ki = 0.003;
  BalSpeed_PID.kd = 0;
 
    //λ��
  //�����ڻ�������ֵ  ���ٶ�
  BalDirgyro_PID.kp = 0.38;       
  BalDirgyro_PID.ki = 0;
  BalDirgyro_PID.kd = 0.015;
  //λ��
  BalDir_PID.kp = 130;           //�����⻷������ֵ  ����ƫ��
  BalDir_PID.ki = 0;
  BalDir_PID.kd = 60;
  Camera_Flag = 1;
  delayms(100);
  TIMER_InitConfig(TIMER_6, 5);// ��ȡPID��ʱ�ж�5ms
  TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ  
  int eyes;
  while (1)
  {
    // �ű��ʶ��
    if (Camera_Flag == 1)
    {
      // �������ͷ�ɼ���ɱ�־λ  �����������򲻻��ٴβɼ����� 
      Camera_Flag = 0;          
      // ��ȡ����ʹ�õ�����
      Get_Use_Image();    
      // ��ֵ�� //
      //��ֵѡ��1���(������)��2���Ⱦ�ֵ��3�̶���ֵ
      Get_Bin_Image(1);
      
      
//ͼ�����޸Ĵ�
		
//��������ʱʹ��,��������ͬʱʹ��
//      ConnectedComponentLabeling((unsigned char *) Bin_Image ,labelBuffer);   //��ͨ�����
//      quanzhong_light_panduan();//ͨ����ͨ��õ���ͼ������ж�
//      quanzhong_light();//����Ŀ��λ����Ϣ
		
// �ж��ű��λ��(�򵥰�)����������ʱʹ��
      Seek_Beacon();

    }
    //�˴���ѡһ
    //Test_EEPROM();  //flash�����޸ĺ���
    TFT_show();   //tft��ʾ����
  }
}

  
// TFT��Ļ��Ϣ��ʾ
void TFT_show(void)//��Ļ��ʾ
{
  static int last_KeyValue,Now_KeyValue;
  uint16_t cnt=0;
  char  txt[64];
  last_KeyValue = Now_KeyValue;
  Now_KeyValue = KEY_Read_All();
  // ��Ļ��Ϣ��ʾ
  
  
  switch(Now_KeyValue)
  {
  case 1://��ʾ��ģ�����
    {
      if(last_KeyValue != 1&&Now_KeyValue ==1)      TFTSPI_CLS(u16WHITE);//��ֹ�������
      
      sprintf((char*)txt,"Roll:%.2f", Roll);         // ��ʾС��ƽ����ֵ
      TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLACK);
      sprintf(txt, "Lamp(%03d,%03d)", sumhang, sumlie);
      TFTSPI_P8X16Str(0, 2, txt, u16RED, u16BLUE);     // ��ʾ�����ű������Ļ�ϵ�ƫ�����
      
      // ����ͱ�����������ʾ
      sprintf(txt, "M1:%04d, M2:%04d ", MotorDuty2, MotorDuty1);
      TFTSPI_P8X16Str(0, 4, txt, u16RED, u16BLUE);     // ���1-2��ֵ
      sprintf(txt, "E1:%04d, E2:%04d ", ECPULSE1, ECPULSE2);
      TFTSPI_P8X16Str(0, 5, txt, u16RED, u16BLUE);     // ������1-2��ֵ
      sprintf(txt, "BAL_OUT:%.2f", BALANCE_OUT);
      TFTSPI_P8X16Str(0, 6, txt, u16RED, u16BLUE);     // IR�Ƶľ�ֵ��������ֵ
      sprintf(txt, "Bal:%.2f ",SPEED_OUT);
      TFTSPI_P8X16Str(0, 7, txt, u16RED, u16BLUE);  
            bell_flag=0;

      
    }break;
  case 2:  //����K1��
    {
      // ��ʾ��ֵ��ͼ�� 
      if(last_KeyValue != 2&&Now_KeyValue ==2)      TFTSPI_CLS(u16WHITE);
      TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char *) Bin_Image);  
      sprintf(txt, "bal:%.2f", BalDir_out);
      TFTSPI_P6X8Str(0, 15, txt, u16RED, u16BLUE);     // IR�Ƶľ�ֵ��������ֵ
      sprintf(txt, "error:%.2f", Dir_Error);
      TFTSPI_P8X8Str(10, 15, txt, u16RED, u16BLUE);
            bell_flag=0;

    }break;
  case 3:  //����ͷԭͼ��
    {
      TFTSPI_Road(0, 0, LCDH, LCDW, (unsigned char *)Image_Use);
      bell_flag=1;
    }break;
    
  }
}


/*************************************************************************
*  �������ƣ�void Seek_Beacon (void)
*  ����˵����ʶ���ű��(�򵥰�,�������޸��Ż�����)
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2022��1��19��
*  ��    ע��
*************************************************************************/
void Seek_Beacon (void)
{
  uint8_t tm=0;
  uint8_t nr=0; //��
  uint8_t nc=0; //��
  
  dotcnt=0;
  for (nr = 1; nr < LCDH - 1; nr++)
  {
    for (nc = 1; nc < LCDW - 1; nc++)
    {
      // 188*120�ֱ����£������������׵㣬����Ϊ�ǿ��ܵ��ű��
      if ((Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] > 1))
      {
        dothang[dotcnt]=nr;     // ��¼���еİ׵�ˮƽ����λ��Ҳ��������ƫ��
        dotlie[dotcnt++]=nc;    // ��¼���еİ׵�ˮ��ֱ��λ��Ҳ����Զ��
      }
    }
  }
  if(dotcnt) // �����аװ�
  {
    sumlie=0,sumhang=0;         // ����ϴεĽ��
    for(tm=0;tm<dotcnt;tm++)
    {
      sumlie+=dotlie[tm];     // ���а׵�����ƫ��ֵ���
      sumhang+=dothang[tm];   // ���а׵�����ƫ��ֵ��ͣ���ʱû�õ�
    }
    sumlie =sumlie/dotcnt;      // �Ƶ��������ĵ�
    sumhang=sumhang/dotcnt;     // �Ƶ�Զ�����ĵ㣬��ʱû�õ�
    eye_show();
  }
  return;
}



/*************************************************************************
*  �������ƣ�void eye_show(void)
*  ����˵�������ӻ�ʶ������ű�Ƶ�λ�ã�����ʾ��ʮ��׼��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2022��3��31��
*  ��    ע��  Bin_Image[LCDH][LCDW]; ��ֵ����ͼ������
*************************************************************************/
void eye_show (void)//��ʾʮ��
{
  for(int i = 1 ;i<LCDH-1;i++)
  {
      Bin_Image[i][sumlie] = 1;
  }
  for(int i = 1 ;i<LCDW-1;i++)
  {
      Bin_Image[sumhang][i] = 1;
  }
    return;
}

/*************************************************************************
*  �������ƣ�float Square_detection (int x,int y)
*  ����˵������Ŀ����м򵥵ĳ����ж�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2022��7��11��
*  ��    ע��  Bin_Image[LCDH][LCDW]; ��ֵ����ͼ������
*************************************************************************/
float Square_detection (int x,int y)
{
    uint8_t tm=0;
    uint8_t nr=x; //��
    uint8_t nc=y; //��
    shang=0,xia=0,zuo=0,you=0;  //��������
    dotcnt=0;
    
    
    if((Bin_Image[nr][nc] == 1) || (Bin_Image[nr + 1][nc] + Bin_Image[nr + 3][nc]+ Bin_Image[nr - 1][nc] +Bin_Image[nr - 3][nc] +
      Bin_Image[nr][nc + 1] +Bin_Image[nr][nc + 3]+Bin_Image[nr][nc -3] +Bin_Image[nr][nc - 1] >= 4) )
    {
        while (Bin_Image[nr - shang][nc] ==1)
        {
            shang++;
        }
        while (Bin_Image[nr + xia][nc] == 1)
        {
            xia++;
        }
        while (Bin_Image[nr][nc - zuo] == 1)
        {
            zuo++;
        }
        while (Bin_Image[nr][nc + you] == 1)
        {
            you++;
        }
        //�󳤿����        
        return (abs(zuo+you)/2.0) / (abs(shang+xia)/2.0);
        
    }
}



/********************************************
����Ȩ���ж�
        ���--�߶�      ����      ��״
����  0~1500   0~120   0~255       0~
���->С  �߶�->��  ���Ŷ�->��
���->��  �߶�->��  ���Ŷ�->��

����->��->���Ŷȸ�
��״->��->���Ŷȸ�
*********************************************/
int quanzhi_weight[100];
void quanzhong_light_panduan(void)
{
    float zz_return;
    memset(quanzhi_weight,0,100);
    for(int i=2;i<=labelcount+2;i++)
    {
        zz_return = Square_detection(Connected_x[i],Connected_y[i]);
        if(zz_return<0.8)//��������
        {
            quanzhi_weight[i]=0;
            continue;
        }
        if(Connected_x[i]<30 && area_map[i]>30)//Զ��̫��
        {
            quanzhi_weight[i]=0;
            continue;
        }
        if(Connected_x[i]>90 && area_map[i]<10)//����̫С
        {
            quanzhi_weight[i]=0;
            continue;
        }
        //Ȩ��ֵԽ�����ű�Ƶĸ���Խ��
        //120��1500Ϊ��ǰʹ�þ�ͷ�µĲ�������ͬ��ͷ��Ҫ�����޸�
        //120Ϊͼ�����¸߶ȣ�1500Ϊͼ��Ĭ������¿��ܳ��ֵ�������
        quanzhi_weight[i]= (int) ((Connected_x[i]*1.0/120)*(1-area_map[i]*1.0/1500)*1000+Connected_light[i]*2+zz_return*100);

    }
    
    
}
//Ѱ�����Ȩ��ֵ
int find_max(void)
{
    int maxx=quanzhi_weight[2];
    int wei=2;
    for(int i=3;i<=labelcount+2;i++)
    {
        if(quanzhi_weight[i]>maxx)
        {
            maxx = quanzhi_weight[i];
            wei=i;
        }
    }
    return wei;
}
//�������Ȩ��Ŀ��λ��
void quanzhong_light(void)
{
    dotcnt=0;
    int zxc=find_max();
    
    if(quanzhi_weight[zxc]!=0)
    {
        sumlie = Connected_y[zxc];
        sumhang = Connected_x[zxc];
        dotcnt++;
        
        eye_show();        
    }
}
