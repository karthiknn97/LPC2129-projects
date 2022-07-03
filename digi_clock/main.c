#include<lpc21xx.h>
#include<lcdheader.h>
void lcd_num(int num)
{
	if(num)
	{
		lcd_num(num/10);
		led_data((num%10)+0x30);
	}
}
int h=0,m=0,s=0;
int main()
{
	T0TCR=1<<0;				//COUNTER ENABLE
	T0PR=14;					//TC will increment after (14+1) cycles
	T0MR0=1000000;
	T0MCR=3<<0;	//Fuctions are Reset TC and Enable Inturrupt
	lcd_init();
	lcd_str("00:00:00");
	while(1)
	{
		
		if(T0IR & 1<<0)
		{
			//led_cmd(0x01);
		 // lcd_str("00:00:00");
			s=s+1;
			led_cmd(0x87);
			if(s<10) lcd_num(s);
			else if (s<60)
			{
				led_cmd(0x86);
				lcd_num(s);
			}
			else
			{
				s=0;
				led_cmd(0x86);
				lcd_str("00");
				m=m+1;
				led_cmd(0x84);
				if(m<10) lcd_num(m);
				else if (m<60)
				{
					led_cmd(0x83);
					lcd_num(m);
				}
				else
				{
					m=0;
					led_cmd(0x83);
					lcd_str("00");
					h=h+1;
					led_cmd(0x81);
					if(h<10) lcd_num(h);
					else if (h<24)
					{
						led_cmd(0x80);
						lcd_num(h);
					}
				}
			}
			T0IR=1<<0;
		}
	}
}
