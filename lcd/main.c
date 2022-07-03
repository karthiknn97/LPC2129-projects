#include<lpc21xx.h>
#include"../lcdheader.h"
int main()
{
	lcd_init();
	while(1)
	{
		lcd_str("HII HII POOJITHA");
		led_cmd(0x01);
	}
	/*led_cmd(0xc0);
	lcd_str("");*/
}
