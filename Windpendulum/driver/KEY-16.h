/*
 * KEY-16.h
 *  Created on: 2014-7-12
 *      Author: yipeng
 *   �����ò�ͬ��IO��ʱ��ֻ�轫P1�ڸ�һ�¾Ϳ�����
 */

#ifndef KEY_16_H_
#define KEY_16_H_

#include"system.h"

#define   KEY_DIR    P5DIR
#define   KEY_OUT    P5OUT
#define   KEY_REN    P5REN
#define   KEY_IN     P5IN

u16 get_low(void);         //ȡ����λ
u16 get_high(void);        //ȡ����λ
u16 KYE_value(void);      //������ֵ����
void key_scan(void);

#endif /* KEY_16_H_ */
