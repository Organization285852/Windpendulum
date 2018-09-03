/******************** (C) COPYRIGHT 2015 Air Nano Team ***************************
 * �ļ���  ��mpu6050.c
 * ����    ��mpu6050����         
 * ʵ��ƽ̨��HT-Hawk��Դ�ɿ�
 * ��汾  ��ST3.5.0
 * ����    ��Air Nano Team 
 * ��̳    ��http://www.airnano.cn
 * �Ա�    ��http://hentotech.taobao.com   
**********************************************************************************/
#include "IIC.h"
#include "MPU6050.h"
#include "msp430F1611.h"
#include "system.h"

u8	mpu6050_buffer[14];					//iic��ȡ��������
struct _sensor sensor;

/*====================================================================================================*/
/*====================================================================================================*
**���� : InitMPU6050
**���� : ��ʼ��MPU6050
**���� : None
**ݔ�� : None
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/
u8 InitMPU6050(void)
{
	u8 ack;
	IIC_Init();
	ack = Single_Read(MPU6050_ADDRESS, WHO_AM_I);
	if (!ack)
     return 0;
	
	Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	//�������״̬
	Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);     
	Single_Write(MPU6050_ADDRESS, CONFIGL, MPU6050_DLPF);              //��ͨ�˲�
	Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, MPU6050_GYRO_FS_1000);  //���������� +-1000
	Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, MPU6050_ACCEL_FS_4);   //���ٶ����� +-4G
	return 1;
}

//**************************ʵ�ֺ���********************************************
//��iic��ȡ�������ݷֲ�,������Ӧ�Ĵ���,����MPU6050_Last
//******************************************************************************
void MPU6050_Read(void)
{
	mpu6050_buffer[0]=Single_Read(MPU6050_ADDRESS, 0x3B);
	mpu6050_buffer[1]=Single_Read(MPU6050_ADDRESS, 0x3C);
	mpu6050_buffer[2]=Single_Read(MPU6050_ADDRESS, 0x3D);
	mpu6050_buffer[3]=Single_Read(MPU6050_ADDRESS, 0x3E);
	mpu6050_buffer[4]=Single_Read(MPU6050_ADDRESS, 0x3F);
	mpu6050_buffer[5]=Single_Read(MPU6050_ADDRESS, 0x40);
	mpu6050_buffer[8]=Single_Read(MPU6050_ADDRESS, 0x43);
	mpu6050_buffer[9]=Single_Read(MPU6050_ADDRESS, 0x44);
	mpu6050_buffer[10]=Single_Read(MPU6050_ADDRESS, 0x45);
	mpu6050_buffer[11]=Single_Read(MPU6050_ADDRESS, 0x46);
	mpu6050_buffer[12]=Single_Read(MPU6050_ADDRESS, 0x47);
	mpu6050_buffer[13]=Single_Read(MPU6050_ADDRESS, 0x48);
}
/**************************ʵ�ֺ���********************************************
//��iic��ȡ�����ٶȼƺ������ǵ����ݷֲ�,������Ӧ�Ĵ���
*******************************************************************************/
void MPU6050_Dataanl(void)
{
	MPU6050_Read();
	
	sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - sensor.acc.quiet.x;
	sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - sensor.acc.quiet.y;
	sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]);

	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
  
	sensor.gyro.radian.x = sensor.gyro.origin.x - sensor.gyro.quiet.x;
	sensor.gyro.radian.y = sensor.gyro.origin.y - sensor.gyro.quiet.y;
	sensor.gyro.radian.z = sensor.gyro.origin.z - sensor.gyro.quiet.z;

////////////////////////////////////////////////////
//    	The calibration  of  acc        //
////////////////////////////////////////////////////	
//	 if(flag.calibratingA)
//	 {
//		 static int32_t	tempax=0,tempay=0,tempaz=0;
//		 static uint8_t cnt_a=0;
//		 if(cnt_a==0)
//		 {
//				sensor.acc.quiet.x = 0;
//				sensor.acc.quiet.y = 0;
//				sensor.acc.quiet.z = 0;
//				tempax = 0;
//				tempay = 0;
//				tempaz = 0;
//				//cnt_a = 1;//�������++�������ˣ�Ŀ�����չ�У׼��ɺ���ټ�++��
//		 }
//				tempax+= sensor.acc.origin.x;
//				tempay+= sensor.acc.origin.y;
//				tempaz+= sensor.acc.origin.z;
//				cnt_a++;
//				if(cnt_a==200)
//				{
//					sensor.acc.quiet.x = tempax/cnt_a;
//					sensor.acc.quiet.y = tempay/cnt_a;
//					sensor.acc.quiet.z = tempaz/cnt_a;
//					cnt_a = 0;
//					flag.calibratingA = 0;
//					EE_SAVE_ACC_OFFSET();//��������
//					//return;
//				}
//			}
//	 if(flag.calibratingG)
//	 {
//		 Gyro_OFFSET();//�Լ���ӵ���������������λ
//	 }
}
/*====================================================================================================*/
/*====================================================================================================*
**���� : Gyro_Calculateoffest
**���� : ������������ƫ
**���� : 
**��� : None
**ʹ�� : Hto_Gyro_Calculateoffest();
**====================================================================================================*/
/*====================================================================================================*/
void Gyro_Caloffest(float x,float y,float z,u16 amount)
{
   sensor.gyro.quiet.x = x/amount;
	 sensor.gyro.quiet.y = y/amount;
	 sensor.gyro.quiet.z = z/amount;
}

/*====================================================================================================*/
/*====================================================================================================*
**���� : Gyro_OFFSET
**���� : �����Ǿ�̬�ɼ�
**���� : None
**ݔ�� : None
**��ע : None
**====================================================================================================*/
/*====================================================================================================*/

/*void Gyro_OFFSET(void)
{
	static u8 over_flag=0;
	u8  i,cnt_g = 0;
	float Integral[3] = {0,0,0};
	float tempg[3]={0,0,0};
	float gx_last=0,gy_last=0,gz_last=0;
	over_flag=0;//��Ϊ�������static��������Լ���ֵ���´ν���ʱover_flag�Ͳ��ᱻ��ֵ0�ˣ�����Ϊ��һ��У׼��ʱ��ֵ��1
	while(!over_flag)	//��ѭ����ȷ�����ᴦ����ȫ��ֹ״̬
	{
		if(cnt_g < 200)
		{
			MPU6050_Read();
			sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
			sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
			sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
			//MPU6050_Dataanl();//����ԭ����

			tempg[0] += sensor.gyro.origin.x;
			tempg[1] += sensor.gyro.origin.y;
			tempg[2] += sensor.gyro.origin.z;

			Integral[0] += absu16(gx_last - sensor.gyro.origin.x);
			Integral[1] += absu16(gy_last - sensor.gyro.origin.y);
			Integral[2] += absu16(gz_last - sensor.gyro.origin.z);

			gx_last = sensor.gyro.origin.x;
			gy_last = sensor.gyro.origin.y;
			gz_last = sensor.gyro.origin.z;
		}
		else{
			// δУ׼�ɹ�
			if(Integral[0]>=GYRO_GATHER || Integral[1]>=GYRO_GATHER || Integral[2]>= GYRO_GATHER){
				cnt_g = 0;
				for(i=0;i<3;i++){
					tempg[i]=Integral[i]=0;
				}
			}
			// У׼�ɹ� 
			else{				
				   Gyro_Caloffest(tempg[0],tempg[1],tempg[2],200);
				   over_flag = 1;
				flag.calibratingG = 0;//�ɹ������У׼���
			}
		}
		cnt_g++;
	}
}
*/
//u16 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
//{
//	u8 TxBuff[2];
//	UCB0I2CSA = SlaveAddress;
//	USCI_I2C_Tx_Init();
//	TxBuff[0] = REG_Address;
//	TxBuff[1] = REG_data;
//	if(PreSet_Tx_Frame(TxBuff,2)==1)
//		return 1;
//	else
//		return 0;
//}
////���ֽڶ�ȡ*****************************************
//unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
//{
//	u8 RxBuff[2];
//	USCI_I2C_Tx_Init();
//	UCB0I2CSA = SlaveAddress;
//	PreSet_Tx_Frame(REG_Address,1);
//	USCI_I2C_Rx_Init();
//	PreSet_Rx_Frame(RxBuff,1);
//	return RxBuff[0];
//}
