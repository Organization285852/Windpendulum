/*
 * timerA.c
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */
#include"msp430f1611.h"
#include"timerA.h"
#include"motor_control.h"
#include"lcd12864.h"
#include"KEY-16.h"
#include"tarsk.h"
#include"PID.h"
#include"PWM.h"
#include"inv_mpu.h"
TARSKTypdDef tarsk;
void ClkInit(void)
{
	unsigned int iq0;
	BCSCTL1 &=~XT2OFF;
 	 do
	{
		IFG1 &= ~OFIFG;							// 清除振荡器失效标志
	    for (iq0 = 0xFF; iq0 > 0; iq0--);	   // 延时，等待XT2起振
	}
	while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振
	BCSCTL2 =SELM1+SELS;                // MCLK,SMCLK时钟为XT2
}
void TimerInit(void)
{
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 = 8000;
	TACTL = TASSEL_2 + MC_1;  // SMCLK, upmode
	P1DIR |= BIT2;
	_EINT();
}

#pragma vector=TIMERA0_VECTOR   //1ms进入一次中断，
__interrupt void Timer_A (void)
{
	tarsk.count_500hz++;
	tarsk.count_200hz++;
	tarsk.count_100hz++;
	tarsk.count_50hz++;
        MoveTimeCnt++;
        if(MoveTimeCnt>priod)
          MoveTimeCnt=0;
	if(tarsk.count_500hz>=2)
	{
		tarsk.flag_500hz = 1;
		tarsk.count_500hz = 0;
	}
	if(tarsk.count_200hz>=5)
	{
		tarsk.flag_200hz = 1;
		tarsk.count_200hz = 0;
	}
	if(tarsk.count_100hz>=10)
	{
		tarsk.flag_100hz = 1;
		tarsk.count_100hz = 0;
	}
	if(tarsk.count_50hz>=400)
	{
		tarsk.flag_50hz = 1;
		tarsk.count_50hz = 0;
	}
}
void loop(void)
{
	if(tarsk.flag_500hz)
	{
		tarsk.flag_500hz=0;
	}
	if(tarsk.flag_200hz)
	{
		tarsk.flag_200hz=0;

		mpu_dmp_get_data(&pitch,&roll,&yaw);
	}
	if(tarsk.flag_100hz)
	{
		tarsk.flag_100hz=0;
	//   Mode_1();
                TrackControl(&track2);
           F_Control();
              
	}
	if(tarsk.flag_50hz)//100ms
	{
		tarsk.flag_50hz=0;
		tarsk_50Hz();
             //  tarsk_100Hz();
	}
}
