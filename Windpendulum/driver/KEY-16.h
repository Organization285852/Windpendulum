/*
 * KEY-16.h
 *  Created on: 2014-7-12
 *      Author: yipeng
 *   但在用不同的IO口时，只需将P1口改一下就可以了
 */

#ifndef KEY_16_H_
#define KEY_16_H_

#include"system.h"

#define   KEY_DIR    P5DIR
#define   KEY_OUT    P5OUT
#define   KEY_REN    P5REN
#define   KEY_IN     P5IN

u16 get_low(void);         //取低四位
u16 get_high(void);        //取高四位
u16 KYE_value(void);      //读按键值函数
void key_scan(void);

#endif /* KEY_16_H_ */
