/*
 * PWM.h
 *
 *  Created on: 2016-5-15
 *      Author: Administrator
 */

#ifndef PWM_H_
#define PWM_H_

#define PWM_T		20000
#define PWM_MAX		(18500 - PWM_MIN) //D不能大于1900
#define PWM_MIN		10500
void PWM_Init(void);
void PWM_Change(unsigned char n,unsigned int duty);
void MotorMove(int pwmx,int pwmy);
#endif /* PWM_H_ */
