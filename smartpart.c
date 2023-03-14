#include<AT89S52.h>//imporing the AT89S52 micro-comtroller header file
#define DATABUS P0 //defining the macro DATABUS as P0
#define RS P2_0//defining the macro RS P2_0 
#define RW P2_1//defining the macro RW P2_1
#define EN P2_2//defining the macro EN P2_2
#include<LCD.h>//including the LCD header file
int count = 0;//declaring the integer count as '0'
int car=99,h,t;//declaring the integers car to '99',h,t
char input[12];//creating an array 
int veri=0;
char ch;
char tag1[]="0B002841E381";
char tag2[]="5900D4D42A73";
char rxdata(void);
void main(void)
{
unsigned char cmd[]={0x38,0x01,0x06,0x0c,0x80};
int i;
TMOD=0x20;
SCON=0x50;
TH1=0xfd;
TR1=1;
lcd_init();
lcd_print("RFID card Number");
while(1)
{
count=0;
while(count<12)
{
input[count]=rxdata();
if(input[count]==tag1[count] || input[count]==tag2[count])
{

veri++;

}

count++;

}

lcd_cmd(0x01);
lcd_print("VERIFYIG...");

13

lcd_cmd(0x01);
if(veri==12)
{

lcd_print("Verified");
delay(500);
car--;
lcd_cmd(0x01);
lcd_print("AVAILABLE CAR SLOTS:");
h=car/10;
t=car%10;
lcd_data(h|0x30);
lcd_data(t|0x30);
veri=0;

}
else
{
lcd_print("Not Allowed");
delay(500);

lcd_cmd(0x01);
lcd_print("AVAILABLE CAR SLOTS:");
h=car/10;
t=car%10;
lcd_data(h|0x30);
lcd_data(t|0x30);

veri=0;
}
}
}
char rxdata()
{
while(RI==0);
RI=0;
ch=SBUF;
return ch;
}
