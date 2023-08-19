#include<reg51.h>

void LCD_Init();
void LCD_GoToXY(char,char);
void LCD_CmdWrite(char);
void LCD_DataWrite(char);
void LCD_DisplayString(char *string_ptr);
void LCD_DisplayNumber(unsigned int);
void delay_ms(unsigned int);
void delay_us(unsigned int);
void blink_led();

sbit rs=P2^2;
sbit en=P2^3;


sbit sensor1 = P0^6; //
sbit sensor2 = P0^5; //
sbit relay = P0^0;
sbit led=P1^0;

#define databus P2   // LCD databus connected to PORT2

#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
#define BlankSpace ' '

#define son 1
#define soff 0
#define lon 0
#define loff 1

unsigned char count=0;
void main()
{
   P0=0xf0;
   
    LCD_Init();
  LCD_DisplayString("People Count: ");
  LCD_DisplayNumber(count);
  LCD_GoToXY(1,0);
  LCD_DisplayString("     Lights :OFF");
  delay_ms(1000);
relay=0;
 
   while(1)
   {
if(sensor1==son)
{
while(sensor2==soff);
while(sensor2==son);
if(count<99)
{ count++;
LCD_GoToXY(0,14);
LCD_DisplayNumber(count);
if(count==1)
{ relay=1;
LCD_GoToXY(1,13);
  LCD_DisplayString(" ON");
}
}
blink_led();
delay_ms(100);
}
if(sensor2==son)
{
while(sensor1==soff);
while(sensor1==son);
if(count>0)
{ count--;
LCD_GoToXY(0,14);
LCD_DisplayNumber(count);
if(count==0)
{ relay=0;
LCD_GoToXY(1,13);
  LCD_DisplayString("OFF");
}
}
blink_led();
delay_ms(100);
}

}
}
void blink_led()
{ led=lon;
delay_ms(200);
led=loff;
}
void LCD_Init()
{ databus=0x00;
   delay_us(5000);
   LCD_CmdWrite(0x02);
   LCD_CmdWrite(0x28);
   LCD_CmdWrite(0x0E);
   LCD_CmdWrite(0x01);
   LCD_CmdWrite(0x80);

}
void LCD_GoToXY(char row, char col)
{
   char pos;

    if(row<LCDMaxLines)
      {
pos= LineOne | (row << 6);
                         

   if(col<LCDMaxChars)
  pos= pos+col;            
                         

LCD_CmdWrite(pos);      
       }
     


   databus=(cmd & 0xf0);      
     rs=0;
     en=1;
delay_us(1);
     en=0;

   delay_us(10);

   databus=((cmd<<4) & 0xf0);  
     rs=0;
     en=1;
delay_us(1);
     en=0;

   delay_ms(1);
}
void LCD_DataWrite( char dat)
{


   databus=(dat & 0xf0);  
     rs=1;
     en=1;
delay_us(1);
     en=0;

   delay_us(10);        // wait for some time.

   databus=((dat <<4) & 0xf0);
     rs=1;
     en=1;
delay_us(1);
     en=0;

   delay_ms(1);

}
void LCD_DisplayString(char *string_ptr)
{
   while(*string_ptr)
    LCD_DataWrite(*string_ptr++);
}
void LCD_DisplayNumber(unsigned int num)
{
//   LCD_DataWrite((num/10000)+0x30);
   num=num%10000;

//   LCD_DataWrite((num/1000)+0x30);
   num=num%1000;

//   LCD_DataWrite((num/100)+0x30);
   num=num%100;

 }

void delay_ms(unsigned int ms_count)


   }
void delay_us(unsigned int us_count)
 {
    while(us_count!=0)
      {
us_count--;
  }
  }
