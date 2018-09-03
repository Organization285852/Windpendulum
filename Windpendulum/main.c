/*
 * main.c
 *
 *  Created on: 2016-5-15
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
extern const char page6[];
extern const char page1[];
extern const char page2[];
u8 key;
void main(void)
{
  
  WDTCTL=WDTPW + WDTHOLD;    //关闭看门狗定时器
	ClkInit();
	LCD_Init();
	PWM_Init();
	delay_ms(100);
	MPU_Init();
    while(mpu_dmp_init())
    {
        LCD_Show(1, 1, "MPU6050 Error   ");

        delay_ms(200);
    }
	TimerInit();
	PINIT();
	ShowInit();
	SetMode1PID();
        Mode1Set();
        Mode2Set();
	 while(1)
	 {
          	loop();
//              tarsk_100Hz();        
//		
	 }
}


