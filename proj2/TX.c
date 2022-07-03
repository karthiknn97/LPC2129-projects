#include<lpc21xx.h>
#include"../lcdheader.h"
char a[2];
int i;
void send_data(char raw)
{
	
//	a[1]=(raw>>8);
//	a[0]= raw;
//	for(i=0;i<2;i++)
//		{
	while(!(U1LSR & 1<<5));
	U1THR=raw;
	//			U1THR=a[i];
			//led_data(a[i]);
//		}
}

void convert(int num)
{
	if(num)
	{
		convert(num/10);
		send_data((num%10)+'0');
	}
}


int main()
{
	IODIR1=255<<17;
	PINSEL0=1<<16|1<<18;
	U1LCR=(1<<7);	
	U1DLL=97;	
	U1LCR=3;					
	lcd_init();
	lcd_str("TX");
	led_cmd(0xc0);
	
	convert(3073);
	delay(2000);
	convert(2319);
	delay(2000);
	convert(2575);
	delay(2000);
	convert(2819);
	delay(2000);
	lcd_num(3073);
	delay(3000);
	convert(261);		
	
	
//send_data(0x0C01);
//	send_data(3073);								//normal operation(0:stutdowm,1:normal operation)
//	delay(10000);
//	send_data(2319);								//decode
//	delay(10000);
//	send_data(2575);								//Intensity
//	delay(10000);
//	send_data(2819);								//no of 7 segments
//	delay(10000);
//	
//	send_data(261);
//	delay(10000);
//	send_data(517);
//	delay(10000);
//	send_data(777);
//	delay(10000);
//	send_data(1025);	
}

