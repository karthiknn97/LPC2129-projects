#include<lpc21xx.h>
#include<stdlib.h>
#include"../lcdheader.h"
int a[2];
void send_data(int data)
{
	IOCLR0=1<<7;
	S0SPDR=data;
	while(!(S0SPSR&(1<<7)));
	IOSET0=1<<7;
}
int main()
{
	PINSEL0|=1<<8|1<<10|1<<12;
	IODIR0|=1<<7;
	IOSET0|=1<<7;
	S0SPCR|=1<<2|1<<3|1<<4|1<<5;
	S0SPCCR=14;
	IODIR1|=255<<17;
	PINSEL0|=1<<16|1<<18;
	U1LCR|=3<<0|1<<7;	
	U1DLL=97;			
	U1LCR=3;	
	int i;
	int reraw[8],j;
	lcd_init();
	lcd_str("RX");

	while(1)
	{
		for(j=0;j<8;j++)
		{
			for(i=0;i<2;i++)
			{
				while(!(U1LSR & 1<<0));
				a[i]=U1RBR;
				//led_data(a[i]);
			}
			reraw[j]=(a[1]<<8)+(a[0]);
			lcd_num(reraw[j]);
			lcd_str("*");
		}
		for(j=0;j<8;j++)
		{
			send_data(reraw[j]);
			IOSET1=j<<17;
			delay(10000);
		}
	}
	
}


