#define LCD 0X0F<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
void delay_ms(unsigned int);
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(char);
void LCD_STR(char*);
void LCD_INTEGER(int );
void LCD_INIT(void)
{
	IODIR1=LCD|RW|RS|E;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0c);
	LCD_COMMAND(0X28);
	LCD_COMMAND(0X80);
}
void LCD_COMMAND(unsigned char CMD)
{
	IOCLR1=LCD;
	IOSET1=(CMD&0XF0)<<16;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=LCD;
	IOSET1=(CMD&0X0F)<<20;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void LCD_DATA(char D)
{
	 IOCLR1=LCD;
	IOSET1=(D&0XF0)<<16;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=LCD;
	IOSET1=(D&0X0F)<<20;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}

void delay_ms(unsigned int sec)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<sec);
	T0TCR=0X03;
	T0TCR=0X00;
}
void LCD_STR(char*p)
{
while(*p)
LCD_DATA(*p++);
}
void LCD_INTEGER(int n)
{
unsigned char a[5];
signed char i=0;
if(n==0)
LCD_DATA('0');
else
{
if(n<0)
{
LCD_DATA('-');
n=-n;
}
while(n>0)
{
a[i++]=n%10;
n=n/10;
}
for(--i;i>=0;i--)
LCD_DATA(a[i]+48);
}
}
