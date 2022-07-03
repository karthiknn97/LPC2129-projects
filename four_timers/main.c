#include<lpc21xx.h>
#include"../lcdheader.h"
int main()
{
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0MR3=4000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T0MR2=3000000;
	T0MR1=2000000;
	T0MR0=1000000;
	T0MCR=1<<6|1<<3|1<<0|1<<9;	//Fuctions are Reset TC and Enable Inturrupt
	
	T1TCR=1<<0;				//COUNTER ENABLE
	T1PR=14;					//TC will increment after (14+1) cycles
	T1MR3=8000000;		//Fuctions will run according to T0MCR if TC == 5000000
	T1MR2=7000000;
	T1MR1=6000000;
	T1MR0=5000000;
	T1MCR=1<<6|1<<3|1<<0|3<<9;
	lcd_init();
	while(1)
	{
		if(T0IR & 1<<0)
		{
			led_cmd(0x01);
			lcd_str("hi");
			T0IR=1<<0;
		}
		if(T0IR & 1<<1)
		{
			led_cmd(0x01);
			lcd_str("hello");
			T0IR=1<<1;
		}
		if(T0IR & 1<<2)
		{
			led_cmd(0x01);
			lcd_str("hero");
			T0IR=1<<2;
		}
		if(T0IR & 1<<3)
		{
			led_cmd(0x01);
			lcd_str("bye");
			T0IR=1<<3;
		}
		if(T1IR & 1<<0)
		{
			led_cmd(0x01);
			lcd_str(" abdul");
			T1IR=1<<0;
		}
		if(T1IR & 1<<1)
		{
			led_cmd(0x01);
			lcd_str("karthik gay");
			T1IR=1<<1;
		}
		if(T1IR & 1<<2)
		{
			led_cmd(0x01);
			lcd_str("nagraj");
			T1IR=1<<2;
		}
		if(T1IR & 1<<3)
		{
			led_cmd(0x01);
			lcd_str("uday");
			T1IR=1<<3;
		}
	}
}
