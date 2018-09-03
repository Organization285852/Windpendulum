/*
 * PID.c
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */
#include "PID.h"
/*------------------------------------------
 函数功能:初始化PID结构体参数
 函数说明:
------------------------------------------*/
void PID_Init(struct PIDTypdDef *pid)
{

	pid->LastError  = 0;			//Error[-1]
	pid->PrevError  = 0;			//Error[-2]
	pid->Proportion = 0;			//比例常数 Proportional Const
	pid->Integral   = 0;			//积分常数 Integral Const
	pid->Derivative = 0;			//微分常数 Derivative Const
	pid->SetPoint   = 0;
	pid->SumError   = 0;
}
/*------------------------------------------
 函数功能:设置PID期望值
 函数说明:
------------------------------------------*/
void PID_SetPoint(struct PIDTypdDef *pid,float setpoint)
{
	pid->SetPoint = setpoint;
}

/*------------------------------------------
 函数功能:设置PID比例系数
 函数说明:浮点型
------------------------------------------*/
void PID_SetKp(struct PIDTypdDef *pid,float dKpp)
{
	pid->Proportion = dKpp;
}
/*------------------------------------------
 函数功能:设置PID积分系数
 函数说明:浮点型
------------------------------------------*/
void PID_SetKi(struct PIDTypdDef *pid,float dKii)
{
	pid->Integral = dKii;
}
/*------------------------------------------
 函数功能:设置PID微分系数
 函数说明:浮点型
------------------------------------------*/
void PID_SetKd(struct PIDTypdDef *pid,float dKdd)
{
	pid->Derivative = dKdd;
}
/*------------------------------------------
 函数功能: 位置式PID计算
 函数说明:	使用前设置好期望值
参数说明：	PID结构体，被测值
------------------------------------------*/
float PID_PosLocCalc(struct PIDTypdDef *pid,float NextPoint)
{
    register float  iError,dError;

	iError = pid->SetPoint - NextPoint;        // 偏差
	pid->SumError += iError;				    // 积分
	if(pid->SumError > SE_limit)					//积分限幅2300
		pid->SumError = SE_limit;
	else if(pid->SumError < -SE_limit)
		pid->SumError = -SE_limit;
	dError = iError - pid->LastError; 			// 当前微分
	pid->LastError = iError;

	return(float)(  pid->Proportion * iError           	// 比例项
          		    + pid->Integral   * pid->SumError 		// 积分项
          		    + pid->Derivative * dError);
}
