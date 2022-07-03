#include<lpc21xx.h>
//#include<lpc214x.h>
void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1000;j++);
}

int main()
{
	IODIR1=0XFF<<17;
	
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0CTCR=0X00;
	T0MR0=1000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T0MCR=3<<0;	//Fuctions are Reset TC and Enable Inturrupt
	
	PINSEL0=1<<7;					//SELECT EXT1
	T0EMR=1<<4|1<<5|1<<0;
	while(1)
	{
			IOSET1 = (0XFF<<17);
			delay();
			IOCLR1 = 0xff<<17;
			delay();
			T0IR = (1<<2);
	}
}
