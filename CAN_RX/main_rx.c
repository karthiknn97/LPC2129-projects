#include<lpc21xx.h>
#include"../prototype.h"
unsigned char test()
{
	
	while(!(RX_in_CAN1()==1));
	led_cmd(0x01);
	lcd_str("IGNITION ON");
	delay(3000);
	led_cmd(0x01);
	lcd_str("CHECKING STATUS FROM MODULES");
	delay(3000);
	if(RX_in_CAN1()==2)
	{
		led_cmd(0x01);
		lcd_str("BREAK TEST PASS");
		delay(3000);
		led_cmd(0x01);
		lcd_str("SEAT BELT PASS");
		delay(3000);
		led_cmd(0x01);
		lcd_str("VEHICLE ON");
		delay(3000);
		return 1;
	}
	else //if(RX_in_CAN1()==3)
	{
		led_cmd(0x01);
		lcd_str("BREAK TEST FAIL");
		delay(3000);
		led_cmd(0x01);
		lcd_str("SEAT BELT FAIL");
		delay(3000);
		led_cmd(0x01);
		lcd_str("TURN ON IGNITION");
		delay(3000);
		return 0;
	}
}
int main()
{
	unsigned char res;
	//unsigned int a,b,key;
	lcd_init();
	can_init();
	led_cmd(0x01);
	lcd_str("CAN TEST CODE");
	delay(2000);
	led_cmd(0x01);
	while(1)
	{
		test:
		res=test();
		if(res==0)	goto test;
	}
}
