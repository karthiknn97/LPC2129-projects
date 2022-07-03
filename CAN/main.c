#include<lpc21xx.h>
#include"../prototype.h"
int main()
{
	unsigned char res;
	lcd_init();
	can_init();
	led_cmd(0x01);
	lcd_str("CAN TEST CODE");
	delay(2000);
	led_cmd(0x01);
	TEST:
	res =can_test();
	if(res!=1)
		goto TEST;
	delay(2000);
	while(1)
	{
		led_cmd(0x01);
		lcd_str("VEHICLE ONNNN!!!");
		delay(1000);
	}
}
