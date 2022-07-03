#include<lpc21xx.h>
void delay()
{
	int i;
	for(i=0;i<1000000;i++);
}
int main()
{
	IODIR1=0xff<<17;
	IODIR0=1<<11;
	WDMOD=3<<0;					//(3<<0) for RESET mode and (2<<0) for INTURRUPT mode
	WDTC=0xffffff;			//Time-out value
	
	IOSET0=1<<11;
	delay();
	IOCLR0=1<<11;
	delay();
	
	WDFEED=0xaa;				//Resets the timer
	WDFEED=0x55;
	
	while(1)
	{
		IOSET1=0xff<<17;
		delay();
		IOCLR1=0xff<<17;
		delay();
	}
}
