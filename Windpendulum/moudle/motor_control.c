/*
 * motor_control.c
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */
#include"PID.h"
#include"PWM.h"
#include"motor_control.h"
#include"inv_mpu.h"
#include"math.h"
#include"lcd12864.h"
struct PIDTypdDef FXPID;
struct PIDTypdDef FYPID;
unsigned int MoveTimeCnt ;
FTypeDef FX,FY;
struct TRACKTypeDef track1;
struct TRACKTypeDef track2;
struct TRACKTypeDef track3;
float x,y;
float pitch,roll,yaw;
unsigned int fy[13]={0,700,1170,1350,1540,1840,2070,2220,2520,2770,2970,3240,3340};
unsigned int fx[13]={0,940,1190,1490,1680,1990,2190,2380,2730,2980,3230,3230,3230};
void PINIT(void)
{
	FX.PWM = FY.PWM = 0;
}
void Mode_1(void)
{
	double set_x = 0.0;
	float A = 15;
	float Normalization = 0.0;
	float Omega = 0.0;
        P1OUT ^= BIT2;
	Normalization = (float)(MoveTimeCnt/(priod*1.0));	 //对单摆周期归一化
	Omega = 2.0*3.14159*Normalization;			 //对2π进行归一化处理
//	A = atan((R/88.0f))*57.2958f;		
                                        //根据摆幅求出角度A,88为摆杆距离地面长度cm
	set_x = sin((double)Omega);       ///(2.0*R)                 //计算出当前摆角
        set_x=set_x *A/(2.0*R);
    
        x=2*asin(set_x)*57.2958f;
  // LCD_WriteNums(2,5,d,3,0);
    PID_SetPoint(&FXPID,x);                      //设置期望值
    PID_SetPoint(&FYPID,x);
} 
void TrackControl(struct TRACKTypeDef *track)
{
  float Normalization = 0.0;
  float Omega = 0.0;
  double set_x = 0.0,set_y=0.0,temp;
  Normalization = (float)(MoveTimeCnt/(track->X_T*1.0));	 //对单摆周期归一化
  Omega = 2.0*3.14159*Normalization*track->X_a;	
  set_x = sin((double)Omega);
  temp = set_x *track->X_A/(2.0*R);
  x=set_x=2*asin(temp)*57.2958f;
  
  Normalization = (float)(MoveTimeCnt/(track->Y_T*1.0));	 //对单摆周期归一化
  Omega = 2.0*3.14159*Normalization*track->Y_a;
  set_y = sin((double)(Omega+ track->phase));
  temp = set_y *track->Y_A/(2.0*R) ;
  y=set_y=2*asin(temp)*57.2958f;
  PID_SetPoint(&FXPID,set_x);                      //设置期望值
  PID_SetPoint(&FYPID,set_y);
}
void Mode1Set(void)
{
  track1.phase = 0;
  track1.X_A = 0;
  track1.Y_A = 15;
  track1.X_a = 1;
  track1.Y_a = 1;
  track1.X_T = priod;
  track1.Y_T = priod;
}
void Mode2Set(void)
{
  track2.phase = 4.7123f;   //
  track2.X_A = 10;
  track2.Y_A = 10;
  track2.X_a = 1;
  track2.Y_a = 1;
  track2.X_T = priod;
  track2.Y_T = priod;
}
void F_Control(void)
{
	double temp;
	mpu_dmp_get_data(&pitch,&roll,&yaw);
	temp = PID_PosLocCalc(&FXPID,pitch);
	FX.PWM = temp *15 + ymohu(&FXPID);
//	FY.PWM = G/sin(temp);
	temp = PID_PosLocCalc(&FYPID,roll);
//	FX.PWM = G/sin(temp);
	FY.PWM = temp *15 + ymohu(&FYPID);
	if(FX.PWM > F_MAX)  FX.PWM =  F_MAX;
	if(FX.PWM < -F_MAX) FX.PWM = -F_MAX;

	if(FY.PWM > F_MAX)  FY.PWM = F_MAX;
	if(FY.PWM < -F_MAX) FY.PWM = -F_MAX;

	MotorMove(FX.PWM,FY.PWM);
}
void SetMode1PID(void)
{
	PID_SetKp(&FXPID,0.89);
	PID_SetKi(&FXPID,0);
	PID_SetKd(&FXPID,0);
	PID_SetKp(&FYPID,0.83);
	PID_SetKi(&FYPID,0);
	PID_SetKd(&FYPID,0);
}
int ymohu(struct PIDTypdDef *pid)
{
   unsigned char n;
   int temp;
   if(pid->SetPoint>0)
   {
     n=(unsigned char)(pid->SetPoint/2);
     temp = fy[n];
   }
   else
   {
      n=(unsigned char)(-pid->SetPoint/2);
      temp =-fy[n];
   }
   return temp;
}
int xmohu(struct PIDTypdDef *pid)
{
   unsigned char n;
   int temp;
   if(pid->SetPoint>0)
   {
     n=(unsigned char)(pid->SetPoint/2);
     if(n==0)
       temp =0;
      else
        temp = fx[n-1];
   }
   else
   {
      n=(unsigned char)(-pid->SetPoint/2);
      temp =-fx[n];
   }
   return temp;
}