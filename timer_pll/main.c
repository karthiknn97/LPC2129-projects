#include<lpc21xx.h>
//#include<lpc214x.h>
void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1000;j++);
}

void tim_int(void)__irq
{
	IOSET0 = (1<<11);
	delay();
	IOCLR0 = 1<<11;
	T0IR = (1<<2);
	VICVectAddr=0;
}
void pll_36MHz(void)
{
	PLLCON=1;											//PLL enable
	PLLCFG=2|2<<5;								//M=3,P=4
	PLLFEED=0XAA;									//Refersh control and config registers
	PLLFEED=0X55;
	while(!(PLLSTAT&(1<<10)));		//wait for pll to lock the target frequency
	PLLCON|=1<<1;									//CONNECT
	PLLFEED=0xaa;									//Refersh control and config registers
	PLLFEED=0x55;
}

int main()
{
	IODIR0 = 1 << 11;
	IODIR1=0XFF<<17;
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0CTCR=0X00;
	T0MR2=1000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T0MCR=1<<6|1<<7;	//Fuctions are Reset TC and Enable Inturrupt
	
	//PINSEL1=3<<24;					//SELECT EXT1
	VICIntEnable=1<<4;			//TO ENABLE EXT1 INTURRUPT (REFER VECTOR TABLE FOR VIC CHANNEL NUMBER)
	VICIntSelect=0<<4;       // fiq or irq
	VICVectAddr5=(long)tim_int;				//ADDRESS OF ISR (5 IS PRIORITY that we have to give 0-15)
	VICVectCntl5= 4	| 1<<5;	//ENABLE VECTORED IRQ IN BIT 5 AND ADDRESS(5 IS PRIORITY)
	pll_36MHz();
	while(1)
	{
			IOSET1 = (0XFF<<17);
			delay();
			IOCLR1 = 0xff<<17;
			delay();
	}
}
