#include<lpc21xx.h>
void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1000;j++);
}

void def_isr(void)__irq
{
	IOSET0=1<<11;
	delay();
  IOCLR0=1<<11;
	delay();
	VICVectAddr=0;
	EXTINT=1<<1;
	T0IR=1<<2;
}

int main()
{
	IODIR1=15<<17;
	IODIR0=1<<11;
	PINSEL0=1<<29;					//SELECT EXT1
	VICIntEnable=1<<15;			//TO ENABLE EXT1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	IODIR0 = 1 << 11;
	IODIR1=0XFF<<17;
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0CTCR=0X00;
	T0MR2=6000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T0MCR=1<<6|1<<7;	//Fuctions are Reset TC and Enable Inturrupt
	
	//PINSEL1=3<<24;					//SELECT EXT1
	VICIntEnable=1<<4;			//TO ENABLE EXT1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	VICIntSelect=0<<4;       // fiq or irq
	VICDefVectAddr=(long)def_isr;

	 while(1);
}
