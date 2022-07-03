#include<lpc21xx.h>
#include"../lcdheader.h"
int main()
{
	int a;
	PINSEL0=1<<0|1<<2;		//step1: Select uart pins
	U0LCR=3<<0|1<<7;			//step2: Select word length and Enable access to divisor latch register
	U0DLL=97;							//step3: Set Baud rate
	U0LCR=3;							//step4: Disable access to divisor latch
	lcd_init();
	while(1)
	{
		while(!(U0LSR & 1<<0));		//wait untill RX Buffer is Non-empty
		a=U0RBR;									//Store the RX Buffer Register in a variable
		
		led_cmd(0x01);
		led_data(a);
		
		while(!(U0LSR & 1<<5));		//wait untill TX Buffer is Empty
		U0THR=a;									//Fill the TX Holding Register
	}
}