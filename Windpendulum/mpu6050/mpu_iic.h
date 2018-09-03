#ifndef __MPU_IIC_H
#define __MPU_IIC_H

#include "system.h"
#include "msp430f1611.h"
#define MPU_SCL_OUT             P2DIR |=  BIT1
#define MPU_SDA_OUT             P2DIR |=  BIT0
#define MPU_SDA_IN              P2DIR &= ~BIT0
 
#define MPU_IIC_SCL_0           P2OUT &= ~BIT1
#define MPU_IIC_SCL_1           P2OUT |=  BIT1
#define MPU_IIC_SDA_0           P2OUT &= ~BIT0
#define MPU_IIC_SDA_1           P2OUT |=  BIT0

#define MPU_READ_SDA            (P2IN & BIT0)

void MPU_IIC_Delay(void);
void MPU_IIC_Init(void);			 
void MPU_IIC_Start(void);
void MPU_IIC_Stop(void);
void MPU_IIC_Send_Byte(u8 txd);
u8 MPU_IIC_Read_Byte(unsigned char ack);
u8 MPU_IIC_Wait_Ack(void);
void MPU_IIC_Ack(void);
void MPU_IIC_NAck(void);

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	 

#endif
















