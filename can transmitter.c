#include<lpc21xx.h>
#include "can_h.h"
#include "lcd_h.h"
void can_tx(struct can_msg);
int main()
{
int flag=0,temp=0,res=0;
struct can_msg m1;
can_init();
lcd_init();
command(0x82);
string("BODY CONTROL");
command(0xc5);
string("MODULE");
while(1)
{
if(((IOPIN0>>14)&1)==0)
{
delay_ms(100);
while(((IOPIN0>>14)&1)==0);
flag=!flag;
if(flag==1)
{
command(0xc0);
command(0x01);
string("left ON");
m1.id=0x01;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
if(flag==0)
{
command(0xc0);
command(0x01);
string("left OFF");
m1.id=0x02;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
}
else if(((IOPIN0>>15)&1)==0)
{
delay_ms(100);
while(((IOPIN0>>15)&1)==0);
temp=!temp;
if(temp==1)
{
command(0xc0);
command(0x01);
string("right ON");
m1.id=0x03;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
if(temp==0)
{
command(0xc0);
command(0x01);
string("right OFF");
m1.id=0x04;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
}
else if(((IOPIN0>>16)&1)==0)
{
delay_ms(100);
while(((IOPIN0>>16)&1)==0);
res=!res;
if(res==1)
{
command(0xc0);
command(0x01);
string("MOTOR ON");
m1.id=0x05;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
 if(res==0)
{
command(0xc0);
command(0x01);
string("MOTOR OFF");
m1.id=0x06;
m1.rtr=0;
m1.dlc=0;
m1.byteA=0;
m1.byteB=0;
can_tx(m1);
}
}
}
}
void can_tx(struct can_msg m1)
{
C2TID1=m1.id;
C2TFI1=(m1.dlc<<16);
if(m1.rtr==0)
{
C2TFI1&=~(1<<30);
C2TDA1=m1.byteA;
C2TDB1=m1.byteB;
}
else
C2TFI1|=(1<<30);

C2CMR=((1<<0)|(1<<5));
while((C2GSR&(1<<3))==0);
//command(0xc0);
}
