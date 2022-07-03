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
	T0MR2=6000000;		//Functions will run according to T0MCR if TC == 5000000
	T0MR1=2000000;
	T0MCR=1<<6|1<<7|1<<3;	//Functions are Reset TC and Enable Inturrupt
	while(1)
	{
		if(T0IR&(1<<2))
		{
			IOCLR1 |= (0XFF<<17);
			T0IR |= (1<<2);
		} 
		else if(T0IR&(1<<1))
		{
			IOSET1 |= (0XFF<<17);
			T0IR |= (1<<1);
		}
	}
	
}
