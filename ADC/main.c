#include<lpc21xx.h>
#include"../lcdheader.h"
int main()
{
	lcd_init();
	PINSEL1=1<<24;			//Alternate Function
	ADCR|=1<<1;					//Selects Channel 1 
	ADCR|=1<<21;				//Disable ADC Power-Down mode(In the sense Activate ADC)
	ADCR|=1<<16;				//Enable Burst mode(continuous conversion) 
	ADCR|=4<<8;					//Prescalar 	//Pclk/(4+1)=3MHz(Should be less than 4.5MHz for this ADC)	//Pclk=15MHz
	int res,ch;
	while(1)
	{
		int var=1;
		while(!(ADDR & var<<31));	//Wait till the conversion is done.
		ch=ADDR & (7<<24);				//7=111		//4 channel ADC
		ch>>=24;									//Store the channel number
		res=ADDR & (1023<<6);			//1023=1111111111		//10 bit ADC
		res>>=6;									//Store the result of ADC Conversion
		
		led_cmd(0x01);
		lcd_str("Channel");
		led_cmd(0x88);
		lcd_num(ch);
		led_cmd(0xc0);
		lcd_str("Temp is");
		led_cmd(0xc8);
		lcd_num(res*0.32);
		delay(3000);
	}
}
