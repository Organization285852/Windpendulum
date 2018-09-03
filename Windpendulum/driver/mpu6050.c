/******************** (C) COPYRIGHT 2015 Air Nano Team ***************************
 * 文件名  ：mpu6050.c
 * 描述    ：mpu6050配置         
 * 实验平台：HT-Hawk开源飞控
 * 库版本  ：ST3.5.0
 * 作者    ：Air Nano Team 
 * 论坛    ：http://www.airnano.cn
 * 淘宝    ：http://hentotech.taobao.com   
**********************************************************************************/
#include "IIC.h"
#include "MPU6050.h"
#include "msp430F1611.h"
#include "system.h"

u8	mpu6050_buffer[14];					//iic读取后存放数据
struct _sensor sensor;

/*====================================================================================================*/
/*====================================================================================================*
**函数 : InitMPU6050
**功能 : 初始化MPU6050
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
u8 InitMPU6050(void)
{
	u8 ack;
	IIC_Init();
	ack = Single_Read(MPU6050_ADDRESS, WHO_AM_I);
	if (!ack)
     return 0;
	
	Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	//解除休眠状态
	Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);     
	Single_Write(MPU6050_ADDRESS, CONFIGL, MPU6050_DLPF);              //低通滤波
	Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, MPU6050_GYRO_FS_1000);  //陀螺仪量程 +-1000
	Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, MPU6050_ACCEL_FS_4);   //加速度量程 +-4G
	return 1;
}

//**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器,更新MPU6050_Last
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
/**************************实现函数********************************************
//将iic读取到加速度计和陀螺仪得数据分拆,放入相应寄存器
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
//				//cnt_a = 1;//将下面的++往上提了，目的是照顾校准完成后别再加++了
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
//					EE_SAVE_ACC_OFFSET();//保存数据
//					//return;
//				}
//			}
//	 if(flag.calibratingG)
//	 {
//		 Gyro_OFFSET();//自己添加的用于陀螺仪清零位
//	 }
}
/*====================================================================================================*/
/*====================================================================================================*
**函数 : Gyro_Calculateoffest
**功能 : 计算陀螺仪零偏
**输入 : 
**输出 : None
**使用 : Hto_Gyro_Calculateoffest();
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
**函数 : Gyro_OFFSET
**功能 : 陀螺仪静态采集
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/

/*void Gyro_OFFSET(void)
{
	static u8 over_flag=0;
	u8  i,cnt_g = 0;
	float Integral[3] = {0,0,0};
	float tempg[3]={0,0,0};
	float gx_last=0,gy_last=0,gz_last=0;
	over_flag=0;//因为定义的是static，如果不自己赋值，下次进来时over_flag就不会被赋值0了，保持为上一次校准完时赋值的1
	while(!over_flag)	//此循环是确保四轴处于完全静止状态
	{
		if(cnt_g < 200)
		{
			MPU6050_Read();
			sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
			sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
			sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
			//MPU6050_Dataanl();//这是原来的

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
			// 未校准成功
			if(Integral[0]>=GYRO_GATHER || Integral[1]>=GYRO_GATHER || Integral[2]>= GYRO_GATHER){
				cnt_g = 0;
				for(i=0;i<3;i++){
					tempg[i]=Integral[i]=0;
				}
			}
			// 校准成功 
			else{				
				   Gyro_Caloffest(tempg[0],tempg[1],tempg[2],200);
				   over_flag = 1;
				flag.calibratingG = 0;//成功后清楚校准标记
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
////单字节读取*****************************************
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
