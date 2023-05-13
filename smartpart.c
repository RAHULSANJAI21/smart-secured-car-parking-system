#include<AT89S52.h>//imporing the AT89S52 micro-comtroller header file
#define DATABUS P0 //defining the macro DATABUS as P0
#define RS P2_0//defining the macro RS P2_0 
#define RW P2_1//defining the macro RW P2_1
#define EN P2_2//defining the macro EN P2_2
#include<LCD.h>//including the LCD header file
int count = 0;//declaring the integer count as '0'
int car=99,h,t;//declaring the integers car to '99',h,t
char input[12];//creating an array named input
int veri=0;//creating a variable veri initialed with zero it can be used as verification flag
char ch;//creating as char which is used to read the byte of data from SBUF
char tag1[]="0B002841E381";//Creating a tag1 array which cointains the valid RFID card number
char tag2[]="5900D4D42A73";//Creating a tag2 array which cointains the valid RFID card number
char rxdata(void);//creating a function rxdata
void main(void)//main function
{
unsigned char cmd[]={0x38,0x01,0x06,0x0c,0x80};//creating a unsigned char cmd which contains the lcd commands
int i;//creating a integer i
lcd_init();//calling the lcd_init() function to initialze the lcd
lcd_print("RFID card Number");//printing the message in the lcd using lcd_print
while(1)//creating a while loop that runs infinite
{
count=0;//initializing the count to 0
while(count<12)//as the RFID tag contains 12 bytes of data the loop run until count becomes 12
{
input[count]=rxdata();//store the received byte of data in input array with count as index
if(input[count]==tag1[count] || input[count]==tag2[count])//comparing the input current index value with tag1 0r tag2 same index value
{

veri++;//if any one matches increment veri

}

count++;//incrementing the count

}

lcd_cmd(0x01);//clearing the lcd using lcd command
lcd_print("VERIFYIG...");//print the message using lcd_print function

lcd_cmd(0x01);//clearing the lcd using the lcd commands
if(veri==12)//check whether the veri is equal to 12
{

lcd_print("Verified");//printing the message using lcd_print function
delay(500);//delay for 500ms
car--;//decreasing car count
lcd_cmd(0x01);//clear lcd
lcd_print("AVAILABLE CAR SLOTS:");//print the availaple slots
h=car/10;
t=car%10;
lcd_data(h|0x30);//displaying the slots in number
lcd_data(t|0x30);
veri=0;

}
else
{
lcd_print("Not Allowed");//displaying not allowed
delay(500);

lcd_cmd(0x01);
lcd_print("AVAILABLE CAR SLOTS:");//displaying available slots
h=car/10;
t=car%10;
lcd_data(h|0x30);
lcd_data(t|0x30);

veri=0;//making veri equal to zero 
}
}
}
char rxdata()//rxdata function
{
while(RI==0);//while loop run till RI bit in scon becomes zero
RI=0;//if RI becomes one making it zero
ch=SBUF;//1 byte SBUF data is copied to ch
return ch;//return ch
}
