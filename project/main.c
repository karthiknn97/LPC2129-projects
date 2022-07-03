#include<lpc21xx.h>
#include"../lcdheader.h"
/*void send_data(int data)
{
	IOCLR0=1<<7;
	S0SPDR=data;
	while(!(S0SPSR&(1<<7)));
	IOSET0=1<<7;
}*/
int a[2];
int main()
{
	PINSEL1=255<<17;
	IODIR1=255<<17;
	int i,reraw;
	PINSEL0=1<<16|1<<18;			//step1: Select uart pins
	U1LCR=3<<0|1<<7;				//step2: Select word length and Enable access to divisor latch register
	U1DLL=97;								//step3: Set Baud rate
	U1LCR=3;					//step4: Disable access to divisor latch
	IOSET1=1<<17;
	lcd_init();
	
	/*PINSEL0=1<<8|1<<10|1<<12;
	IODIR0=1<<7;
	IOSET0=1<<7;
	S0SPCR=1<<2|1<<3|1<<4|1<<5;
	S0SPCCR=14;	*/											//speed sp0clk=PCLK/(S0CPCCR+1)
	while(1)
	{
		for(i=0;i<2;i++)
		{
			IOSET1=1<<18;
			while(!(U1LSR & 1<<0));
			//b=U1RBR;
			a[i]=U1RBR;
		  IOSET1=1<<19;
		}
		reraw=(a[1]<<8)+(a[0]);
		lcd_num(reraw);
		//send_data(reraw);
	}
	
}



