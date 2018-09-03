/*
 * tarsk.c
 *
 *  Created on: 2016-5-17
 *      Author: Administrator
 */


#include"msp430F1611.h"
#include "system.h"
#include "PWM.h"
#include "LCD12864.h"
#include "mpu6050.h"
#include"inv_mpu.h"
#include "key-16.h"
#include "timerA.h"
#include "motor_control.h"
#include "PID.h"
float r=0;
double k=0;
void tarsk_100Hz(void)
{
	LCD_WriteNums(1,2,pitch,1,0);
	LCD_WriteNums(2,2,roll,1,0);
	LCD_WriteNums(1,6,FYPID.Proportion,1,0);
	//
	LCD_WriteNums(3,4,FX.PWM,2,0);
	LCD_WriteNums(4,4,FY.PWM,2,0);
}
void ShowInit(void)
{
	LCD_Show(1, 1,"P:");
	LCD_Show(2, 1,"R:");
	LCD_Show(1, 5,"k:");
	LCD_Show(2, 5,"R:");
	LCD_Show(3, 1,"FXPWM:");
	LCD_Show(4, 1,"FYPWM:");
}
void tarsk_50Hz(void)
{
	unsigned char key;
	key = KYE_value();
	 if(key)
	 {
		switch(key)
		{
			case 1:FY.PWM += 10;if(FY.PWM>PWM_MAX)FY.PWM=PWM_MAX;break;
			case 2:FY.PWM -= 10;if(FY.PWM<-PWM_MAX)FY.PWM=-PWM_MAX;break;
			case 3:FX.PWM += 10;if(FX.PWM>PWM_MAX)FX.PWM=PWM_MAX;break;
			case 4:FX.PWM -= 10;if(FX.PWM<-PWM_MAX)FX.PWM=-PWM_MAX;break;
			case 5:FY.PWM += 50;if(FY.PWM>PWM_MAX)FY.PWM=PWM_MAX;break;
			case 6:FY.PWM -= 50;if(FY.PWM<-PWM_MAX)FY.PWM=-PWM_MAX;break;
			case 7:FX.PWM += 50;if(FX.PWM>PWM_MAX)FX.PWM=PWM_MAX;break;
			case 8:FX.PWM -= 50;if(FX.PWM<-PWM_MAX)FX.PWM=-PWM_MAX;break;
			case 9:FY.PWM += 100;if(FY.PWM>PWM_MAX)FY.PWM=PWM_MAX;break;
			case 10:FY.PWM -= 100;if(FY.PWM<-PWM_MAX)FY.PWM=-PWM_MAX;break;
			case 11:FX.PWM += 100;if(FX.PWM>PWM_MAX)FX.PWM=PWM_MAX;break;
			case 12:FX.PWM -=100;if(FX.PWM<-PWM_MAX)FX.PWM=-PWM_MAX;break;
			case 13:FY.PWM += 500;if(FY.PWM>PWM_MAX)FY.PWM=PWM_MAX;break;
			case 14:FY.PWM -= 500;if(FY.PWM<-PWM_MAX)FY.PWM=-PWM_MAX;break;
			case 15:FX.PWM += 500;if(FX.PWM>PWM_MAX)FX.PWM=PWM_MAX;break;
			case 16:FX.PWM -=500;if(FX.PWM<-PWM_MAX)FX.PWM=-PWM_MAX;break;
//			case 1:r += 1;if(r>20)r=20;break;
//			case 2:r -= 1;if(r<-20)r=-20;break;
//			case 3:r += 5;if(r>20)r=20;break;
//			case 4:r -= 5;if(r<-20)r=-20;break;
//			case 5:k += 0.1;if(k>10)k=10;break;
//			case 6:k -= 0.1;if(k<=0)k=0;break;
//			case 7:k += 1;if(k>10)k=10;break;
//			case 8:k -= 1;if(k<=0)k=0;break;
//			case 9:k += 5;if(k>10)k=10;break;
//			case 10:k -= 5;if(k<=0)k=0;break;
		}
		MotorMove(FX.PWM,FY.PWM);
		//PID_SetKp(&FYPID,k);
		//PID_SetPoint(&FYPID,r);  				//设置期望值
                tarsk_100Hz();
		while(KYE_value());
	 }

}
