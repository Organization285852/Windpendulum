/*
 * KEY-16.c
 *  Created on: 2014-7-12
 *      Author: yipeng
 *������̳�����P1�ڿ���
 *P1.0��P1.1��P1.2��P1.3�ֱ���ơ�����"1,2,3,4.
 *P1.4��P1.5��P1.6��P1.7�ֱ����"���ᡱ1,2,3,4.
 *�轫���������while���������     ��ɨ��
 */
#include"msp430f1611.h"
#include"KEY-16.h"
#include"system.h"
//#include"LCD_12864.h"
u16 switch_1;    //�����ķ���ֵ
u8 count=0;
//u8 tablea[] = "                ";
//u8 table0[] = "���غ���ֱ��Դ  ";
//u8 table1[] = "ָ����ʦ:         ";
//u8 table2[] = "���ڸ�  ÷����    ";
//
//u8 table3[] = "���غ���ֱ��Դ  ";
//u8 table4[] = "��Ա������ΰ  ";
//u8 table5[] = "��Ҷ��  ������        ";
//
//u8 table6[] = "���������ѹ   V";
//u8 table7[] = "���ֱ����ѹ   V";
//u8 table8[] = "���۵���ֵ    mA";
//u8 table9[] = "ʵ�ʵ�ѹֵ    mA";
//u16 key_flag=0x00;
u16 get_low(void)         //ȡ����λ
{
	u16 low=0x0f;
	WDTCTL=WDTPW + WDTHOLD;    //�رտ��Ź���ʱ��
	KEY_DIR =0xf0;         //����P1�ڵĸ���λΪ���ģʽ������λ������
	KEY_OUT =0x00;         //P1�ڵĸ���λ����͵�ƽ
//	KEY_REN =0x0f;         //ʹ�ܵ���λ���ŵ�(����\����)������
    KEY_OUT =0x0f;          //��P1REN=0x000f�Ļ����ϣ����õ���λ����������
//    P1DIR=0X0000;         //����Ĵ�����ֻ���ģ��û����ܶ���д�룬����Ϊ����
 //   P1IN &=0x000f;
    if(0x0f != KEY_IN)
    	  low &= KEY_IN;
    return low;
}

u16 get_high(void)        //ȡ����λ
{
	u16 high=0xf0;
	KEY_DIR =0x0f;         //����P1�ڵĵ���λΪ���ģʽ������λ������
	KEY_OUT =0xF0;         //P1�ڵĵ���λ����͵�ƽ
//	KEY_REN =0xf0;         //ʹ�ܸ���λ���ŵ�(����\����)������
//    KEY_OUT =0xf0;          //��P1REN=0x00f0�Ļ����ϣ����ø���λ����������
    if(0xf0 != KEY_IN)
    	  high &= KEY_IN;
    return high;
}

u16 KYE_value(void)      //������ֵ����
{

	//WDTCTL=WDTPW + WDTHOLD;    //�رտ��Ź���ʱ��

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
//	key_flag = KYE_value();      //������ֵ����
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

