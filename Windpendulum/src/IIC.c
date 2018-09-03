/*
 * IIC.c
 *
 *  Created on: 2014-7-12
 *      Author:刘佳
 */
#include "IIC.h"
#include "system.h"

#define IIC_OUT()	{IIC_IO_DIR |=IIC_SDK;}//IIC_IO_OUT &=~IIC_SDK;}
#define IIC_IN()	{IIC_IO_DIR &=~IIC_SDK;}//IIC_IO_REN |=IIC_SDK;IIC_IO_OUT |=IIC_SDK;}
#define IIC_SDK_L	IIC_IO_OUT &=~IIC_SDK	
#define IIC_SDK_H	IIC_IO_OUT |= IIC_SDK	
#define IIC_CLK_L	IIC_IO_OUT &=~IIC_CLK		
#define IIC_CLK_H	IIC_IO_OUT |= IIC_CLK		
#define IIC_IN_Data IIC_IO_IN & IIC_SDK			

void IIC_Init(void)
{
	IIC_IO_DIR |=IIC_CLK;	
}

void Start_IIC(void)
{
	IIC_OUT();
	IIC_SDK_H;		
	delay_us(1);
	IIC_CLK_H;		
	delay_us(5);
	IIC_SDK_L;		
	delay_us(5);
	IIC_CLK_L;		
}

void Stop_IIC(void)
{
	IIC_OUT();
	IIC_SDK_L;		
	delay_us(1);
	IIC_CLK_H;		
	delay_us(5);
	IIC_SDK_H;		
	delay_us(5);
	IIC_SDK_L;		
}

u8 IIC_Send_Byte(u8 data)
{
	u8 i;
	u8 IIC_ACK=0;	
	IIC_OUT();
	for(i=0;i<8;i++)	
	{
		if((data<<i)&0x80)	
			IIC_SDK_H;
		else
			IIC_SDK_L;
		delay_us(1);
		IIC_CLK_H;		
		delay_us(5);
		IIC_CLK_L;
		delay_us(1);
	}
	delay_us(1);
	IIC_IN();	
	delay_us(1);
	IIC_CLK_H;
	delay_us(1);
	if(IIC_IN_Data)
		IIC_ACK=0;
	else
		IIC_ACK=1;
	delay_us(2);
	IIC_CLK_L;		
	return IIC_ACK;	
}

u8 IIC_Read_Byte(void)
{
	u8 Data=0 , i;
	IIC_IN();
	for(i=0;i<8;i++)
	{
		delay_us(1);
		IIC_CLK_L;		
		delay_us(5);
		IIC_CLK_H;		
		delay_us(2);
		Data<<=1;
		if(IIC_IN_Data)
			Data++;
		delay_us(2);
	}
	IIC_CLK_L;
	delay_us(2);
	return Data;
}

void IIC_Ack(u8 ack)
{
	IIC_OUT();
	if(ack)
		IIC_SDK_H;
	else
		IIC_SDK_L;
	delay_us(2);
	IIC_CLK_H;
	delay_us(5);
	IIC_CLK_L;	
	delay_us(2);
}



unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{
	unsigned char REG_data;
	Start_IIC();
    IIC_Send_Byte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址
    IIC_Ack(1);
    IIC_Send_Byte((u8) REG_Address);   //设置低起始地址
    IIC_Ack(1);
    Start_IIC();
    IIC_Send_Byte(SlaveAddress+1);
    IIC_Ack(1);
	REG_data= IIC_Read_Byte();
    IIC_Ack(0);
    Stop_IIC();
	return REG_data;
}

u16 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	Start_IIC();
    IIC_Send_Byte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址
    IIC_Ack(1);
    IIC_Send_Byte(REG_Address );   //设置低起始地址
    IIC_Ack(1);
    IIC_Send_Byte(REG_data);
    IIC_Ack(1);
    Stop_IIC();
    delay_ms(5);
    return 1;
}











