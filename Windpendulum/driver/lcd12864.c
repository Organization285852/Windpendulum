#include "lcd12864.h"

const char page1[] = {
"星期一    天气晴"
"    年  月  日  "
"    时  分  秒  "
"气温：20.3℃    "
};

const char page2[] = {
"按键次数:   次  "
};

const char page3[] = {
"按下的是第  个键"
};

const char page4[] = {
" --ultra test-- "
"distance=      m"
};

const char page5[] = {
"--DS18B20 Test--"
"Temp =        ℃"
};

const char page6[] = {
"--- ADC Test ---"
"VOL =           "
};

const char page8[] = {
" --DHT11 TEST-- "
"温度 =    ℃    "
"湿度 =    %     "
};

u16 year = 2016, month =  4, day = 23;
u8  hour =   23, min  =  59, sec = 55;

void LCD_ShowPage(u8 page)
{
    switch(page)
    {
        case page_1: LCD_Show(1, 1, page1);
                     LCD_WriteNums(2, 1, year, 0, -1); LCD_WriteNums(2, 4, month, 0, -1); LCD_WriteNums(2, 6, day, 0, -1); 
                     LCD_WriteNums(3, 2, hour, 0, -1); LCD_WriteNums(3, 4,   min, 0, -1); LCD_WriteNums(3, 6, sec, 0, -1);
                     break;
                     
        case page_2: LCD_Show(1, 1, page2);
                     break;
                     
        case page_3: LCD_Show(1, 1, page3);
                     break;
                    
        case page_4: LCD_Show(1, 1, page4);
                     break;
                     
        case page_5: LCD_Show(1, 1, page5);
                     break;
                     
        case page_6: LCD_Show(1, 1, page6);
                     break;
                     
        case page_8: LCD_Show(1, 1, page8);
                     break;
                     
        default: LCD_Show(2, 1, "所选页面暂不存在");
                 LCD_Show(3, 1, "请选择正确的页面");
                 while(1);
    }
}

/*************************************
向LCD指定位置写入一个字符串
*************************************/
void LCD_Show(u8 y, u8 x, const char *str)
{
    u8 cnt = 0;
    
    LCD_AddrCheck(y, x);
    
    x--;
    y--;
    
    switch(y)
    {
        case 0: LCD_WriteCmd(0x80 + x); break;
        case 1: LCD_WriteCmd(0x90 + x); break;				
        case 2: LCD_WriteCmd(0x88 + x); break;
        case 3: LCD_WriteCmd(0x98 + x); break;
        default: break;
    }
    
    while(*str > 0)
    {
        if( (x*2 + cnt) == 16 || (x*2 + cnt) == 32 ||(x*2 + cnt) == 48 )
        {
            y++;
        
            switch(y)
            {
                case 1: LCD_WriteCmd(0x90); break;				
                case 2: LCD_WriteCmd(0x88); break;
                case 3: LCD_WriteCmd(0x98); break;
                default: break;
            }
        }
          
        LCD_WriteData(*str);
        str++;
        cnt++;
    }
}

void LCD_WriteStr(u8 y, u8 x, u8 *str)
{
    LCD_AddrCheck(y, x);
    
    x--;
    y--;
    
    switch(y)
    {
        case 0: LCD_WriteCmd(0x80 + x); break;
        case 1: LCD_WriteCmd(0x90 + x); break;				
        case 2: LCD_WriteCmd(0x88 + x); break;
        case 3: LCD_WriteCmd(0x98 + x); break;
        default: break;
    }
    
    while(*str > 0)
    {
        LCD_WriteData(*str);
        str++;
    }
}

void LCD_WriteOneNum(char num)
{
    LCD_WriteData(0x30 + num); 
}

void LCD_WriteNums(u8 y, u8 x, double number, u8 preci, u8 dir)
{
    char   preciBuf;
    long   integ;
    double decim, digits = 0.1; 

    
    LCD_AddrCheck(y, x);        
    
    x--;
    y--;
    
    switch(y)
    {
        case 0: LCD_WriteCmd(0x80 + x); break;
        case 1: LCD_WriteCmd(0x90 + x); break;				
        case 2: LCD_WriteCmd(0x88 + x); break;
        case 3: LCD_WriteCmd(0x98 + x); break;
        default: break;
    }
    
    if(preci > 9) preci = 9;
    
    integ = (long)number;   

    if(integ < 0)
    {
        decim =  integ - number;
        integ = -integ;
    }
    else
    {
        decim =  number - integ;     
    }

    decim += 0.0000000001;      //精度补偿,IAR的double类型数据默认是32位的,这里选择了64位的精度
                                //具体配置是在工程文件的:Options-->General Options-->
                                //Target-->Floating point中勾选64 bits选项即可达到16位小数的精度
                                //但由于算法的原因,最多达到9位小数的精度,因此通常把变量decim补偿到第10位小数
    if(integ != 0)
    {  
        while(1)
        {
            if(integ < digits)
                break;
            else
                digits *= 10;
        }
        
        digits /= 10;

        if(number < 0)
        {
            LCD_WriteData('-');
        }
        
#if Show_Plus_Sign
        
        if(number > 0)
        {
            LCD_WriteData('+');            
        }
#endif  
        if(dir == Num_Right) LCD_WriteData(' ');
        
        while(digits >= 1)
        {       
            LCD_WriteOneNum((char)(integ / digits));
            integ  = integ % (long)digits;
            digits /= 10;
        }
    }
    
    else
    {
#if Show_Plus_Sign
            
            LCD_WriteData('+');         
#endif    
        if(dir == Num_Right)
        {
           
            LCD_WriteData(' ');   
        }
        LCD_WriteOneNum(0);
    }
    
    digits = 0.1;           //重新初始化
    
    if(preci > 0)      
    {
        LCD_WriteData('.');
        
        preciBuf = preci;
        
        while(1)
        {  
            if(preci)
            {
                decim *= 10;
                digits *= 10 ;
                preci--;
            }
            else break;
        }
        
        preci = preciBuf;
        
        while(digits >= 1 && preci > 0)  
        {
            LCD_WriteOneNum((char)(decim / digits));
            decim  = (long)decim % (long)digits;
            digits /= 10;
            preci--;       
        }
    }
}

void LCD_AddrCheck(u8 y, u8 x)
{
    char x_error = 0, y_error = 0, xE[2], yE[2];
    
    if( (x<1) || (x>8) )
    {
        x_error = 2;
        LCD_Show(1, 1, "    列数错误    ");  
        LCD_Show(2, 1, "列数不能为第  列");
        sprintf(xE, "%d", x);
        LCD_Show(2, 7,(const char*) xE);
    }
    
    if( (y<1) || (y>4) )
    {
        y_error = 1;
        LCD_Show(1 + x_error, 1, "    行数错误    ");  
        LCD_Show(2 + x_error, 1, "行数不能为第  行");
        sprintf(yE, "%d", y);
        LCD_Show(2 + x_error, 7, (const char*)yE);
    }
    
    if(x_error || y_error) while(1);
}

void LCD_ClearScreen(void)
{
    LCD_WriteCmd(0x01);
    delay_us(72);
    LCD_WriteCmd(0x02);
    delay_us(72);    
}

/*************************************
如果使用并行通信
**************************************/
#if   Use_Parallel_Communications

void LCD_Init(void)
{
    LCD_CMDOut;
    PSB_1;
    LCD_WriteCmd(0x30);
    delay_us(72);
    LCD_WriteCmd(0x0c);
    delay_us(72);
    LCD_WriteCmd(0x01);
    delay_us(72);
    LCD_WriteCmd(0x06);
    delay_us(72);
}

uchar LCD_CheckBusy(void)
{
    u8 busy;
    
    LCD_WriteByte;
    MCU2LCD_Byte = 0xff;
    RS_0;
    RW_1;
    EN_1;
    delay_us(1);
    busy = MCU2LCD_Byte & 0x80;
    EN_0;
    
    return busy;
}


/*************************************
LCD并行读指令函数
**************************************/
void LCD_WriteCmd(u8 Cmd)
{
    while(LCD_CheckBusy());
    
    RS_0;
    RW_0;
    EN_1;
    
    LCD_WriteByte;
    MCU2LCD_Byte = Cmd;
    
    delay_us(1);
    
    EN_0;
}

/*************************************
LCD并行写数据函数
**************************************/
void LCD_WriteData(u8 Data)
{
    while(LCD_CheckBusy());
    
    RS_1;
    RW_0;
    EN_1;
    
    LCD_WriteByte;
    MCU2LCD_Byte = Data;
    
    delay_us(1);
    
    EN_0;
}

/*************************************
LCD并行读数据函数
**************************************/
uchar LCD_ReadData(void)
{
    u8 temp;
    
    while(LCD_CheckBusy());
    
    LCD_WriteByte;    
    MCU2LCD_Byte = 0xff;
    
    RS_1;
    RW_1;
    EN_1;
    
    LCD_ReadByte;
    temp = LCD2MCU_Byte;
    
    delay_us(1);
    
    EN_0;
    
    return temp;
}

#endif


/*************************************
如果使用串行通信
**************************************/
#if Use_Serial_Communication

void LCD_Init(void)
{
    LCD_CMDOut;
    PSB_0;
    LCD_WriteCmd(0x30);
    delay_us(72);
    LCD_WriteCmd(0x0c);
    delay_us(72);
    LCD_WriteCmd(0x01);
    delay_us(72);
    LCD_WriteCmd(0x06);
    delay_us(72);
}

void LCD_Show_XY(u8 x, u8 y)
{
    if(x == 1) x = 0x80;
    if(x == 2) x = 0x90;
    if(x == 3) x = 0x88;
    if(x == 4) x = 0x98;
    
    LCD_WriteCmd(x + y);
}

/*************************************
LCD串行写指令函数
**************************************/
void LCD_WriteCmd(u8 Cmd)
{
    CS_1;

    LCD_Write_Byte(0xf8);
    delay_us(600);
    LCD_Write_Byte(Cmd & 0xf0);
    delay_us(200);
    LCD_Write_Byte((Cmd << 4) & 0xf0);
    delay_us(200);
    
    CS_0;
}

/*************************************
LCD串行写数据函数
**************************************/
void LCD_WriteData(u8 Data)
{
    CS_1;
    
    LCD_Write_Byte(0xfa); 
    delay_us(600);
    LCD_Write_Byte(Data & 0xf0);
    delay_us(200);
    LCD_Write_Byte((Data << 4) & 0xf0);
    delay_us(200);
    
    CS_0;
}

/*************************************
LCD串行写一个字节函数
**************************************/
void LCD_Write_Byte(u8 byte)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        CLK_0;
        delay_us(1);
        if(byte & 0x80) {
            SID_1;
        }
        else SID_0;
        
        CLK_1;
        byte <<= 1;
    }
    CLK_0;
}

#endif







