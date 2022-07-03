#include<lpc21xx.h>
#include"../lcdheader.h"
#define row 15<<17
#define col 15<<21
#define r1 0x1c0000
#define r2 0x1a0000
#define r3 0x160000
#define r4 0x0e0000
#define c1 0x1c00000
#define c2 0x1a00000
#define c3 0x1600000
#define c4 0x0e00000

int main()
{
	lcd_init();
	while(1)
	{
		IODIR1=row;
		IOCLR1=row;
		int c=IOPIN1 & col;
		if(c!= 0x1e00000)
		{
			if(c==c1)
			{
				IODIR1=col;
				IOCLR1=col;
				led_cmd(0x01);
				led_cmd(0x80);
				int r=IOPIN1 & row;
				if(r!=0x01e0000)
				{
					if(r==r1) lcd_str("1"); 
					if(r==r2) lcd_str("2");
					if(r==r3) lcd_str("3");
					if(r==r4) lcd_str("+");
				}
				delay(2000);
			}
			if(c==c2)
			{
				IODIR1=col;
				IOCLR1=col;
				led_cmd(0x01);
				led_cmd(0x80);
				int r=IOPIN1 & row;
				if(r!=0x01e0000)
				{
					if(r==r1) lcd_str("4");
					if(r==r2) lcd_str("5");
					if(r==r3) lcd_str("6");
					if(r==r4) lcd_str("-");
				}
			}
			if(c==c3)
			{
				IODIR1=col;
				IOCLR1=col;
				led_cmd(0x01);
				led_cmd(0x80);
				int r=IOPIN1 & row;
				if(r!=0x01e0000)
				{
					if(r==r1) lcd_str("7");
					if(r==r2) lcd_str("8");
					if(r==r3) lcd_str("9");
					if(r==r4) lcd_str("*");
				}
			}
			if(c==c4)
			{
				IODIR1=col;
				IOCLR1=col;
				led_cmd(0x01);
				led_cmd(0x80);
				int r=IOPIN1 & row;
				if(r!=0x01e0000)
				{
					if(r==r1) lcd_str("#");
					if(r==r2) lcd_str("%");
					if(r==r3) lcd_str("=");
					if(r==r4) lcd_str("/");
				}
			}
			
		}
	}
}
