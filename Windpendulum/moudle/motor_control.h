/*
 * motor_control.h
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include"stdint.h"
#define R	57         //单位cm
#define G   50
#define F_MAX	6000

#define priod       2000.0  //单摆周期(毫秒)
/*------------------------------------------
 				F机结构体
------------------------------------------*/
typedef struct
{
	float Offset;	  //允许偏差量
	float CurPos;
	float PrevPos;
	float CurAcc;
	float PrevSpeed;

	volatile float SetXPos;	  //设定位置
	volatile float SetYPos;	  //设定位置
	volatile float SetSpeed;  //设定速度

	volatile float CurXPos;	  //当前位置
	volatile float CurYPos;	  //当前位置
	volatile float CurSpeed;  //当前速度矢量

	volatile int32_t  PWM;	      //PWM
	volatile uint8_t  ShootFlag;
	volatile uint8_t  AdjustFlag;
	volatile uint8_t  ErrFlag;

	volatile uint32_t SetMaxPos;	  //软件设定最大位置
	volatile uint32_t SetMaxPower;	  //软件设定最大力量
	volatile int32_t  SetMaxSpeed;	  //软件设定最大速度

}FTypeDef;

struct TRACKTypeDef{
  unsigned int X_A;
  unsigned int Y_A; //最大振幅，cm
  unsigned int X_a;
  unsigned int Y_a;
  double phase;//相位x-y,幅度制
  double X_T;
  double Y_T;
};
extern struct TRACKTypeDef track1;
extern struct TRACKTypeDef track2;
extern struct TRACKTypeDef track3;
extern unsigned int MoveTimeCnt;
void PINIT(void);
void Mode_1(void);
void F_Control(void);
void SetMode1PID(void);
int ymohu(struct PIDTypdDef *pid);
int xmohu(struct PIDTypdDef *pid);
void Mode1Set(void);

void Mode2Set(void);
void TrackControl(struct TRACKTypeDef *track);
extern float pitch,roll,yaw;
extern FTypeDef FX,FY;
extern struct PIDTypdDef FXPID;
extern struct PIDTypdDef FYPID;
#endif /* MOTOR_CONTROL_H_ */
