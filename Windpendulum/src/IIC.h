/*
 * IIC.h
 *
 *  Created on: 2014-7-12
 *      Author: ¡ıº—
 */

#ifndef IIC_H_
#define IIC_H_
#include "system.h"
#include "msp430g2553.h"

#define IIC_IO_OUT	P2OUT
#define IIC_IO_IN	P2IN
#define IIC_IO_DIR	P2DIR	
#define IIC_IO_REN	P2REN	

#define IIC_CLK		BIT1		
#define IIC_SDK 	BIT0		


void IIC_Init(void);	
void Start_IIC(void);	
void Stop_IIC(void);	
u8 IIC_Send_Byte(u8 data);	
u8 IIC_Read_Byte(void);		
void IIC_Ack(u8 ack);		
u16 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
#endif /* IIC_H_ */
