/*
 * motor_control.h
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include"stdint.h"
#define R	57         //��λcm
#define G   50
#define F_MAX	6000

#define priod       2000.0  //��������(����)
/*------------------------------------------
 				F���ṹ��
------------------------------------------*/
typedef struct
{
	float Offset;	  //����ƫ����
	float CurPos;
	float PrevPos;
	float CurAcc;
	float PrevSpeed;

	volatile float SetXPos;	  //�趨λ��
	volatile float SetYPos;	  //�趨λ��
	volatile float SetSpeed;  //�趨�ٶ�

	volatile float CurXPos;	  //��ǰλ��
	volatile float CurYPos;	  //��ǰλ��
	volatile float CurSpeed;  //��ǰ�ٶ�ʸ��

	volatile int32_t  PWM;	      //PWM
	volatile uint8_t  ShootFlag;
	volatile uint8_t  AdjustFlag;
	volatile uint8_t  ErrFlag;

	volatile uint32_t SetMaxPos;	  //����趨���λ��
	volatile uint32_t SetMaxPower;	  //����趨�������
	volatile int32_t  SetMaxSpeed;	  //����趨����ٶ�

}FTypeDef;

struct TRACKTypeDef{
  unsigned int X_A;
  unsigned int Y_A; //��������cm
  unsigned int X_a;
  unsigned int Y_a;
  double phase;//��λx-y,������
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
