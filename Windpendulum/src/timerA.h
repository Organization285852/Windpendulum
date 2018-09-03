/*
 * timerA.h
 *
 *  Created on: 2016-5-16
 *      Author: Administrator
 */

#ifndef TIMERA_H_
#define TIMERA_H_
typedef struct
{
	unsigned int flag_200hz;
	unsigned int flag_1000hz;
	unsigned int flag_500hz;
	unsigned int flag_100hz;
	unsigned int flag_50hz;
	unsigned int count_500hz;
	unsigned int count_100hz;
	unsigned int count_50hz;
	unsigned int count_200hz;

}TARSKTypdDef;
void ClkInit(void);
void TimerInit(void);
void loop(void);
#endif /* TIMERA_H_ */
