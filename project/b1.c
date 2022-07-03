#include<lpc21xx.h>
#include"../lcdheader.h"
char a[2];
void send(int raw)
{
	a[1]=(raw>>8);
	a[0]= 
	for(i=0;i<2;i++)
		{
			while(!(U0LSR & 1<<5));
			U0THR=a[i];
		}
}

int main()
{
	
	PINSEL0=1<<0|1<<2;			//step1: Select uart pins
	U0LCR=3<<0|1<<7;				//step2: Select word length and Enable access to divisor latch register
	U0DLL=97;								//step3: Set Baud rate
	U0LCR=3;					//step4: Disable access to divisor latch
	lcd_init();
	
	
	while(1)
	{
		
	}
}