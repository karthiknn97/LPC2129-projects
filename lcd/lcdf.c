#include<lpc21xx.h>
#include"../lcdheader.h"
void delay(int T)
{
	int i,j;
	for(i=0;i<T;i++)
	for(j=0;j<1000;j++);
}

void led_cmd(unsigned char c)
{
	IOCLR0=0XFF<<15;
	IOSET0 = c << 15;
	
	IOCLR0=RS;
	IOCLR0=RW;
	IOSET0=EN;
	delay(10);
	IOCLR0=EN;
}

void led_data(char d)
{
	IOCLR0=0XFF << 15;
	IOSET0=d<<15;
	
	IOSET0=RS;
	IOCLR0=RW;
	IOSET0=EN;
	delay(10);
	IOCLR0=EN;
}

void lcd_str(char *ch)
{
	int i=0;
	while(*ch)
	{
		led_data(*ch);
		ch++;
		i++;
		if (i>16)
		{
			led_cmd(0x18);
			delay(3000);
		}
	}
}

void lcd_init(void)
{
	IODIR0 = DATA|EN|RS|RW;
	led_cmd(0x38);
	led_cmd(0x01);
	led_cmd(0x0E);
	led_cmd(0x80);
}
