CAN HEADER
#include<lpc21xx.h>
void can_init(void);
struct can_msg
{
int id;
int rtr;
int dlc;
int byteA;
int byteB;
};
void can_init(void)
{
PINSEL1 |=0X00014000;
VPBDIV=1;//to set pclock =60mhz
C2MOD=0X01; //to set can as reset mode ,to select baudrate and acceptance filter
AFMR=0X02;//TO Accept all messages
C2BTR=0X001C001D; //to select can baud rate
C2MOD=0X00; // can to normal mode
}
