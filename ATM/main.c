#include<lpc21xx.h>
#include"../lcdheader.h"
#include<string.h>
int main()
{
	char str[10];
	int i,j;
	char pass[10]="qwerty";
	PINSEL0=1<<0|1<<2;			//step1: Select uart pins
	U0LCR=3<<0|1<<7;				//step2: Select word length and Enable access to divisor latch register
	U0DLL=97;								//step3: Set Baud rate
	U0LCR=(1<<1)|(1<<0)|(0<<7);					//step4: Disable access to divisor latch
	lcd_init();
	while(1)
	{
	for(i=0;i<6;i++)
	{
		while(!(U0LSR & 1<<0));
		led_cmd(0x01);
		str[i]=U0RBR;
		for(j=1;j<i+2;j++) 
		{
			lcd_str("*");
		}
	}
		if(strcmp(pass,str)==0) lcd_str("Correct");
		else lcd_str("Incorrect");
	}
}
