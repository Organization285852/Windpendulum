#ifndef __LCD12864_H
#define __LCD12864_H

#include "system.h"
#include "stdio.h"
#include "string.h"
#include "msp430f1611.h"
#define   Use_Serial_Communication      1   
#define   Use_Parallel_Communications   0   

#define    LCD_CMDOut    {P2DIR |= BIT4 + BIT5 + BIT6 + BIT7;}      //P2口的高四位设置为输出

#if   Use_Serial_Communication

#define    CS_1          P2OUT |=  BIT4     //P2.4
#define    CS_0          P2OUT &= ~BIT4     //P2.4
#define    SID_1         P2OUT |=  BIT5     //P2.5
#define    SID_0         P2OUT &= ~BIT5     //P2.5
#define    CLK_1         P2OUT |=  BIT6     //P2.6
#define    CLK_0         P2OUT &= ~BIT6     //P2.6
#define    PSB_1         P2OUT |=  BIT7     //P2.7
#define    PSB_0         P2OUT &= ~BIT7     //P2.7

#endif


#if   Use_Parallel_Communications

#define    LCD_ReadByte        P4DIR=0x00    //数据口方向设置为输入
#define    LCD_WriteByte       P4DIR=0xff    //数据口方向设置为输出
#define    LCD2MCU_Byte        P4IN
#define    MCU2LCD_Byte        P4OUT
#define    RS_1                P3OUT |=  BIT0     //P3.0
#define    RS_0                P3OUT &= ~BIT0     //P3.0
#define    RW_1                P3OUT |=  BIT1     //P3.1
#define    RW_0                P3OUT &= ~BIT1     //P3.1
#define    EN_1                P3OUT |=  BIT2     //P3.2
#define    EN_0                P3OUT &= ~BIT2     //P3.2
/*
#define    PSB_1         P1OUT|=BIT3      //P1.3
*/
#endif

#define    page_1      1
#define    page_2      2
#define    page_3      3
#define    page_4      4
#define    page_5      5
#define    page_6      6
#define    page_8      8

#define    Num_Left     1
#define    Num_Right    2

#define    Show_Plus_Sign       1

void LCD_Init(void);
void LCD_ClearScreen(void);
u8 LCD_CheckBusy(void);
void LCD_WriteCmd(u8 Cmd);
void LCD_WriteData(u8 Data);
void LCD_Write_Byte(u8 byte);
u8 LCD_ReadData(void);
void LCD_AddrCheck(u8 y, u8 x);
void LCD_Show(u8 y,u8 x, const char *str);
void LCD_WriteStr(u8 y, u8 x, u8 *str);
void LCD_WriteNums(u8 y, u8 x, double num, u8 preci, u8 dir);
void LCD_WriteOneNum(char num);
void LCD_ShowPage(u8 page);

#endif




