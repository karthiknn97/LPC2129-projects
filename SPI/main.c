#include<lpc21xx.h>
#include"../lcdheader.h"
void send_data(int data)
{
	//led_data(data);
	IOCLR0=1<<7;
	S0SPDR=data;
	while(!(S0SPSR&(1<<7)));
	IOSET0=1<<7;
}
int main()
{
	PINSEL0=1<<8|1<<10|1<<12;
	IODIR0=1<<7;
	IOSET0=1<<7;
	//lcd_init();
	S0SPCR=1<<2|1<<3|1<<4|1<<5;
	S0SPCCR=14;									//speed sp0clk=PCLK/(S0CPCCR+1)
	send_data(0x0C01);								//normal operation(0:stutdowm,1:normal operation)
	send_data(0x0900);								//decode
	send_data(0x0a0f);								//Intensity
	send_data(0x0b03);								//no of 7 segments
	
	send_data(0x014f);
	send_data(0x024e);
	send_data(0x0337);
	send_data(0x047e);
}
