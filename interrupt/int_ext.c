#include<lpc21xx.h>
void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1000;j++);
}

void ext_int(void)__irq
{
	IOSET0=1<<11;
	delay();
  IOCLR0=1<<11;
	delay();
	VICVectAddr=0;			//Reset Vector table
	EXTINT=1<<1;				//Reset external inturrupt
}

int main()
{
	IODIR1=15<<17;
	IODIR0=1<<11;
	PINSEL0=1<<29;								//SELECT EXT1
	VICIntEnable=1<<15;						//TO ENABLE EXT1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	VICVectAddr3 = (long)ext_int;	//ADDRESS OF ISR (3 IS PRIORITY that we have to give 0-15)
	VICVectCntl3 = 15	| 1<<5;			//ENABLE VECTORED IRQ(BIT 5) (3 IS PRIORITY)(15 for ext1)
	
	while(1)
	{
		IOSET1=(15<<17);
		delay();
		IOCLR1=15<<17;
		delay();
	}
		
}



