/*
 * system.h
 *
 *  Created on: 2016-5-15
 *      Author: Administrator
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/*
 * system.h
 *
 *  Created on: 2015-5-9
 *      Author: Administrator
 */


//#include"msp430F1611.h"
//#include "system.h"
//#include "PWM.h"
//#include "LCD12864.h"
//#include "mpu6050.h"
//#include"inv_mpu.h"
//#include "key-16.h"
//#include "timerA.h"
//#include "motor_control.h"
#define CPU_F             ((double)8000000)
#define delay_us(x)       __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)       __delay_cycles((long)(CPU_F*(double)x/1000.0))

typedef unsigned long u32;
typedef unsigned int u16;
typedef unsigned char u8;
//#define u32 unsigned long
//#define u16 unsigned int
//#define u8 unsigned char




#endif /* SYSTEM_H_ */
