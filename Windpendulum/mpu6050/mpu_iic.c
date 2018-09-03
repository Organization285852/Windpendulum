#include "mpu_iic.h"


void MPU_IIC_Delay(void)
{
    delay_us(2);
}

void MPU_IIC_Init(void)
{				
    MPU_SCL_OUT;
    MPU_SDA_OUT;
    MPU_IIC_SCL_1;
    MPU_IIC_SDA_1;
}

void MPU_IIC_Start(void)
{
    MPU_SDA_OUT;
    MPU_IIC_SDA_1;	  	  
    MPU_IIC_SCL_1;
    MPU_IIC_Delay();
    MPU_IIC_SDA_0;
    MPU_IIC_Delay();
    MPU_IIC_SCL_0;
}	  

void MPU_IIC_Stop(void)
{
    MPU_SDA_OUT;
    MPU_IIC_SCL_0;
    MPU_IIC_SDA_0;
    MPU_IIC_Delay();
    MPU_IIC_SCL_1; 
    MPU_IIC_SDA_1;
    MPU_IIC_Delay();							   	
}

u8 MPU_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    MPU_SDA_IN; 
    
    MPU_IIC_SDA_1;
    MPU_IIC_Delay();	   
    
    MPU_IIC_SCL_1;
    MPU_IIC_Delay();	 
    
    while(MPU_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            MPU_IIC_Stop();
            return 1;
        }
    }
    MPU_IIC_SCL_0;	   
    return 0;  
} 

void MPU_IIC_Ack(void)
{
    MPU_IIC_SCL_0;
    MPU_SDA_OUT;
    MPU_IIC_SDA_0;
    MPU_IIC_Delay();
    MPU_IIC_SCL_1;
    MPU_IIC_Delay();
    MPU_IIC_SCL_0;
}

void MPU_IIC_NAck(void)
{
    MPU_IIC_SCL_0;
    MPU_SDA_OUT;
    MPU_IIC_SDA_1;
    MPU_IIC_Delay();
    MPU_IIC_SCL_1;
    MPU_IIC_Delay();
    MPU_IIC_SCL_0;
}					 				     
		  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    MPU_SDA_OUT; 	    
    MPU_IIC_SCL_0;
    for(t=0;t<8;t++)
    {              
        if( (txd&0x80)>>7 == 0)
        {
            MPU_IIC_SDA_0;
        }
        else MPU_IIC_SDA_1;

        txd<<=1; 	  
        MPU_IIC_SCL_1;
        MPU_IIC_Delay(); 
        MPU_IIC_SCL_0;	
        MPU_IIC_Delay();
    }	 
} 	    
 
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    
    MPU_SDA_IN;
    
    for(i=0;i<8;i++ )
    {
        MPU_IIC_SCL_0; 
        MPU_IIC_Delay();
        MPU_IIC_SCL_1;
        receive <<= 1;
        if(MPU_READ_SDA)receive++;   
        MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();
    else
        MPU_IIC_Ack();  
    return receive;
}