#include<lpc21xx.h>
void delay(void)
{
	int i;
	for(i=0;i<1000000;i++);
}
int main()
{
	PLLCFG=2|2<<5;
	PLLCON=1;
	PLLFEED=0XAA;
	PLLFEED=0X55;
	while(!(PLLSTAT & (1<<10)));
	PLLCON |= 1<<1;
	PLLFEED=0XAA;
	PLLFEED=0X55;
	IODIR1=0xff<<17;
	IOSET1=0xff<<17;
	delay();
	IOCLR1=0xff<<17;
	delay();
}
