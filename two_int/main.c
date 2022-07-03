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
	VICVectAddr=0;			//reset vector table
	EXTINT=1<<1;				//reset external inturrupt
}

void tim_int(void)__irq
{
	IOSET0=1<<11;
	delay();
  IOCLR0=1<<11;
	delay();
	VICVectAddr=0;			//reset vector table
	T0IR = (1<<2);			//reset timer inturrupt
}

int main()
{
	IODIR1=15<<17;
	IODIR0=1<<11;
	PINSEL0=1<<29;							//SELECT EXT1
	VICIntEnable=1<<15;					//TO ENABLE EXT1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	VICVectAddr5=(long)ext_int;	//ADDRESS OF ISR (5 IS PRIORITY that we have to give 0-15)
	VICVectCntl5=15	| 1<<5;			//ENABLE VECTORED IRQ IN BIT 5 AND ADDRESS(5 IS PRIORITY)
	IODIR0 = 1 << 11;
	IODIR1=0XFF<<17;
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0MR2=6000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T0MCR=1<<6|1<<7;	//Fuctions are Reset TC and Enable Inturrupt
	
	VICIntEnable=1<<4;					//TO ENABLE Timer1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	VICVectAddr9=(long)tim_int;	//ADDRESS OF ISR (9 IS PRIORITY that we have to give 0-15)
	VICVectCntl9= 4	| 1<<5;			//ENABLE VECTORED IRQ IN BIT 5 AND ADDRESS(9 IS PRIORITY)
	 while(1);
}