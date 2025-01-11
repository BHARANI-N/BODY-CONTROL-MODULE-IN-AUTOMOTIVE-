#include<lpc21xx.h>
#include"can_h.h"
#include"lcd_h.h"
void can_rx(struct can_msg*);
void led_blink(void);
void delay_sec(int);
void timer_0(void)__irq;
struct can_msg m1;
int flag=0;
//struct can_msg m2;
int main()
{
//int count=0;
IODIR0 |=1<<17;
IOSET0 |=1<<17;
can_init();
lcd_init();
string("receive node");
while(1)
{
can_rx(&m1);
if(m1.id==0x01)
{
command(0x01);
command(0x80);
string("LEFT ON");
T0MCR=0X03;
T0MR0=600-1;

VICIntSelect=0;
 
VICVectCntl0=(1<<5)|4;
VICVectAddr0=(int)timer_0;

VICIntEnable=1<<4;
T0TCR=0X01;
}
else if(m1.id==0x02)
{
command(0x01);
string("left off");
IOSET0 |=1<<17;
}
}
}
void can_rx(struct can_msg *m1)
{
while((C2GSR&(0x1))==0);
m1->id=C2RID;
m1->dlc=(C2RFS>>16)&0XF;
m1->rtr=(C2RFS>>30)&0X1;
if(m1->rtr==0)
{
m1->byteA=C2RDA;
m1->byteB=C2RDB;
}
C2CMR=(1<<2);
}
void timer_0(void)__irq
{
T0IR=0X01;
if(flag==0)
{
IOCLR0 =1<<17;
//delay_ms(500);
flag=1;
}
else
{
IOSET0 =1<<17;
//delay_ms(500);
flag=0;
}
VICVectAddr=0;
}
/*void led_blink(void)
{
command(0xc0);
command(0x01);
string("left ON");
while(1)
{
IOCLR0 |=1<<17;
delay_sec(500);
IOSET0 |=1<<17;
delay_sec(500);
can_rx(&m1);
if(m1.id==0x02)
break;
}
command(0xc0);
command(0x01);
string("left OFF");
IOSET0 |=1<<17;
}
void delay_sec(int i)
{
T0PR=15000-1;
T0TCR=0X01;
while(T0TC<i);
T0TCR=0X03;
T0TCR=0X00;
} */


