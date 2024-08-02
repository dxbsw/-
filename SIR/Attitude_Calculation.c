#include "include.h"

void Get_Car_Angle(void)           //��ȡ�����ǽǶȣ���ɣ�
{
    static uint8 IsAttitudeinit = 0;
    BMX055_DataRead(&BMX055_data, 0);
    GYRO_Speed_Z=(BMX055_data.GYROZdata - GyroOffset.Zdata);
    BMX055_data.GYROXdata = (BMX055_data.GYROXdata - GyroOffset.Xdata) * 0.030517578;   //���������ξ��ǵ�λ����
    BMX055_data.GYROYdata = (BMX055_data.GYROYdata - GyroOffset.Ydata) * 0.030517578;
    BMX055_data.GYROZdata = (BMX055_data.GYROZdata - GyroOffset.Zdata) * 0.030517578;
  ///////1000 / 32768     //////BMX055������Ʈ�������Ժ��Բ��ƣ����ǰ�ȫ������ǽ���һ��
    BMX055_data.ACCXdata *= 0.001953125;    ///////4 / 2048
    BMX055_data.ACCYdata *= 0.001953125;
    BMX055_data.ACCZdata *= 0.001953125;
   
    Acc.Xdata = BMX055_data.ACCXdata;
    Acc.Ydata = BMX055_data.ACCYdata;
    Acc.Zdata = BMX055_data.ACCZdata;
    Gyro.Xdata = BMX055_data.GYROXdata;
    Gyro.Ydata = BMX055_data.GYROYdata;
    Gyro.Zdata = BMX055_data.GYROZdata;  
    if(IsAttitudeinit == 0)
    {
      Quaternion_init();                    ////��̬�����ʼ��        
      IsAttitudeinit = 1;
    }
    else
    {
      Attitude_UpdateGyro();                /////���ٸ���
      Attitude_UpdateAcc();                 /////����ںϸ���
      SystemAttitude.Pitch = -EulerAngle.Roll / PI * 180;         ////תΪ�Ƕ�
      SystemAttitude.Roll = EulerAngle.Pitch / PI * 180;
      SystemAttitude.Yaw = EulerAngle.Yaw / PI * 180;
      SystemAttitudeRate.Pitch = -EulerAngleRate.Roll/ PI * 180;
      SystemAttitudeRate.Roll = EulerAngleRate.Pitch / PI * 180;
      SystemAttitudeRate.Yaw = EulerAngleRate.Yaw / PI * 180;//��������Ҫ����оƬ�ڷ��޸�   
    }
      Negative_treatment();//�ѽǶ�ת��0~360��ԭ����-180 ~ 180��
    
}
