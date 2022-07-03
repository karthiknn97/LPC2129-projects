#include<lpc21xx.h>
#include<stdlib.h>
#include"../lcdheader.h"
char uart_rx(void);
int cmd1,data1,cmd2,cmd3,cmd4;
int a[2];
char str[4],str1[3],str2[4],str3[4],str4[4];
void send_data(int data)
{
	IOCLR0=1<<7;
	S0SPDR=data;
	while(!(S0SPSR&(1<<7)));
	IOSET0=1<<7;
}
int main()
{
	PINSEL0|=1<<8|1<<10|1<<12;
	IODIR0|=1<<7;
	IOSET0|=1<<7;
	S0SPCR|=1<<2|1<<3|1<<4|1<<5;
	S0SPCCR=14;
	IODIR1|=255<<17;
	PINSEL0|=1<<16|1<<18;
	U1LCR|=3<<0|1<<7;	
	U1DLL=97;			
	U1LCR=3;	
	int i;
	//int reraw[8],j;
	lcd_init();
	lcd_str("RX");
	while(1)
	{
			for(i=0;i<4;i++)	str[i] = uart_rx();
		
			for(i=0;i<4;i++)  str2[i] = uart_rx();
		
			for(i=0;i<4;i++)  str3[i] = uart_rx();
			
			for(i=0;i<4;i++)	str4[i] = uart_rx();
		
			for(i=0;i<3;i++)	str1[i] = uart_rx();
		
		break;
	}
	cmd1=atoi(str);
	cmd2=atoi(str2);
	cmd3=atoi(str3);
	cmd4=atoi(str4);
	data1=atoi(str1);
	led_cmd(0x01);
	led_cmd(0x80);
	lcd_num(cmd1);
	led_cmd(0x85);
	lcd_num(cmd2);
	led_cmd(0x8A);
	lcd_num(cmd3);
	led_cmd(0xc0);
	lcd_num(cmd4);
	
	led_cmd(0xc5);
	lcd_num(data1);
//	send_data(cmd1);
//	send_data(cmd2);
//	send_data(cmd3);
//	send_data(cmd4);
//	send_data(data1);
	
	
//	while(1)
//	{
//		for(j=0;j<8;j++)
//		{
//			for(i=0;i<2;i++)
//			{
//				while(!(U1LSR & 1<<0));
//				a[i]=U1RBR;
//				//led_data(a[i]);
//			}
//			reraw[j]=(a[1]<<8)+(a[0]);
//			lcd_num(reraw[j]);
//			lcd_str("*");
//		}
//		//lcd_num(reraw);
//		for(j=0;j<8;j++)
//		{
//			send_data(reraw[j]);
//			IOSET1=j<<17;
//			delay(10000);
//		}
//	}
	
}

char uart_rx(void)
{
	while(!(U1LSR & 1 << 0));
	return U1RBR;
}

