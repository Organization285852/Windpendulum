/*
 * KEY-16.c
 *  Created on: 2014-7-12
 *      Author: yipeng
 *矩阵键盘程序，有P1口控制
 *P1.0，P1.1，P1.2，P1.3分别控制“横轴"1,2,3,4.
 *P1.4，P1.5，P1.6，P1.7分别控制"纵轴”1,2,3,4.
 *需将主程序放入while（）里，进行     行扫描
 */
#include"msp430f1611.h"
#include"KEY-16.h"
#include"system.h"
//#include"LCD_12864.h"
u16 switch_1;    //按键的返回值
u8 count=0;
//u8 tablea[] = "                ";
//u8 table0[] = "数控恒流直流源  ";
//u8 table1[] = "指导老师:         ";
//u8 table2[] = "伍宗富  梅彬运    ";
//
//u8 table3[] = "数控恒流直流源  ";
//u8 table4[] = "组员：孟祥伟  ";
//u8 table5[] = "匡叶覃  蒋基海        ";
//
//u8 table6[] = "输出交流电压   V";
//u8 table7[] = "输出直流电压   V";
//u8 table8[] = "理论电流值    mA";
//u8 table9[] = "实际电压值    mA";
//u16 key_flag=0x00;
u16 get_low(void)         //取低四位
{
	u16 low=0x0f;
	WDTCTL=WDTPW + WDTHOLD;    //关闭看门狗定时器
	KEY_DIR =0xf0;         //配置P1口的高四位为输出模式，低四位是输入
	KEY_OUT =0x00;         //P1口的高四位输出低电平
//	KEY_REN =0x0f;         //使能低四位引脚的(上拉\下拉)电阻器
    KEY_OUT =0x0f;          //在P1REN=0x000f的基础上，配置低四位引脚上拉。
//    P1DIR=0X0000;         //输入寄存器是只读的，用户不能对它写入，配置为输入
 //   P1IN &=0x000f;
    if(0x0f != KEY_IN)
    	  low &= KEY_IN;
    return low;
}

u16 get_high(void)        //取高四位
{
	u16 high=0xf0;
	KEY_DIR =0x0f;         //配置P1口的低四位为输出模式，高四位是输入
	KEY_OUT =0xF0;         //P1口的低四位输出低电平
//	KEY_REN =0xf0;         //使能高四位引脚的(上拉\下拉)电阻器
//    KEY_OUT =0xf0;          //在P1REN=0x00f0的基础上，配置高四位引脚上拉。
    if(0xf0 != KEY_IN)
    	  high &= KEY_IN;
    return high;
}

u16 KYE_value(void)      //读按键值函数
{

	//WDTCTL=WDTPW + WDTHOLD;    //关闭看门狗定时器

        switch( get_low() | get_high())
             {
                 case 0x7e: switch_1=1;break;
        		 case 0xbe: switch_1=2;break;
        	 	 case 0xde: switch_1=3;break;
        	 	 case 0xee: switch_1=4;break;
        	 	 case 0x7d: switch_1=5;break;
        		 case 0xbd: switch_1=6;break;
        		 case 0xdd: switch_1=7;break;
        		 case 0xed: switch_1=8;break;
        		 case 0x7b: switch_1=9;break;
        		 case 0xbb: switch_1=10;break;
        		 case 0xdb: switch_1=11;break;
      		     case 0xeb: switch_1=12;break;
        		 case 0x77: switch_1=13;break;
        		 case 0xb7: switch_1=14;break;
        		 case 0xd7: switch_1=15;break;
        		 case 0xe7: switch_1=16;break;
       		     default:switch_1=0;break;
             }
	 return switch_1;
}
//void menu_1(void)
//{
//	Write_char_12864(1,1,table0);
//	Write_char_12864(2,1,table1);
//	Write_char_12864(3,1,table2);
//	Write_char_12864(4,1,tablea);
//}
//void menu_2(void)
//{
//	Write_char_12864(1,1,table3);
//	Write_char_12864(2,1,table4);
//	Write_char_12864(3,1,table5);
//	Write_char_12864(4,1,tablea);
//}
//void menu_3(void)
//{
//	Write_char_12864(1,1,table6);
//	Write_char_12864(2,1,table7);
//	Write_char_12864(3,1,table8);
//	Write_char_12864(4,1,table9);
//}
//void key_scan(void)
//{
//	u16 key_flag;
//	key_flag = KYE_value();      //读按键值函数
//	if(key_flag != 0)
//    {
////		delay_ms(5);
//		if(key_flag == 1)
//		{
//		      menu_1();
//		}
//		if(key_flag == 2)
//		{
//		      menu_2();
//		}
//		if(key_flag == 3)
//		{
//		      menu_3();
//		}
//	}
//}

