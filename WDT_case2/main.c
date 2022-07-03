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
	WDMOD=3<<0;
	WDTC=0xffffff;
	
	IOSET0=1<<11;
	delay();
	IOCLR0=1<<11;
	delay();
	
	WDFEED=0xaa;
	WDFEED=0x55;
	
	while(1)
	{
		if(WDTV<=0x800000)
		{
			WDFEED=0xaa;
			WDFEED=0x55;
		}
		IOSET1=0xff<<17;
		delay();
		IOCLR1=0xff<<17;
		delay();
	}
}
