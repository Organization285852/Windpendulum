/*
 * PWM.c
 *
 *  Created on: 2016-5-15
 *      Author: Administrator
 */
#include "msp430f1611.h"
#include "system.h"
#include "PWM.h"
#include "math.h"
void PWM_Init(void)
{
  P4DIR |= BIT1 + BIT2 + BIT3 + BIT4;       // P1.2 and P1.3 output
  P4SEL |= BIT1 + BIT2 + BIT3 + BIT4;       // P1.2 and P1.3 TB otions
  TBCCR0 = PWM_T;                           // PWM Period
  TBCCTL1 = OUTMOD_7;  			    		// CCR1 reset/set
  TBCCR1 = 8000;                              // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_7;  			    		// CCR2 reset/set
  TBCCR2 = 8000;
  TBCCTL3 = OUTMOD_7;  			    		// CCR3 reset/set
  TBCCR3 = 8000;                              // CCR3 PWM duty cycle
  TBCCTL4 = OUTMOD_7;  			    		// CCR4 reset/set
  TBCCR4 = 8000;                              // CCR4 PWM duty cycle
  TBCTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
}

void PWM_Change(unsigned char n,unsigned int duty)
{
	u16 temp;
	temp = duty;//*TBCCR0/100
	switch(n)
	{
		case 1:TBCCR1 = temp;break;
		case 2:TBCCR2 = temp;break;
		case 3:TBCCR3 = temp;break;
		case 4:TBCCR4 = temp;break;
	}
}
void MotorMove(int pwmx,int pwmy)
{
	if(pwmx>=0)
	{
		PWM_Change(2,pwmx+PWM_MIN);
		PWM_Change(1,PWM_MIN);
	}
	else
	{
		PWM_Change(1,(u16)(0-pwmx)+PWM_MIN);
		PWM_Change(2,PWM_MIN);
	}
	if(pwmy>=0)
	{
		PWM_Change(3,pwmy+PWM_MIN);
		PWM_Change(4,PWM_MIN);
	}
	else
	{
		PWM_Change(4,(u16)(0-pwmy)+PWM_MIN);
		PWM_Change(3,PWM_MIN);
	}
}

