#include<lpc21xx.h>
#include"../lcdheader.h"
void data(char d)
{
	I2DAT=d;
	while(!(I2CONSET & 1<<3));
	I2CONCLR=1<<3;
}
void start()
{
	I2CONCLR=1<<3;
	I2CONSET=1<<5;
	while(!(I2CONSET & 1<<3));
	I2CONCLR=1<<3;
	I2CONCLR=1<<5;
}
int main()
{
	PINSEL0=1<<4|1<<6;							//pinselect for sda,scl
	char b;
	lcd_init();
	I2CONSET=1<<6;									//I2C interface Enable
	I2SCLL=75;											//setting the frequency
	I2SCLH=75;
	start();
	data(0xa0);											//0xa0 for write //0xa1 for read
	I2CONCLR=1<<3;									//clearing SI flag(interrupt flag)
	data(0x48);											//initialize address on eeprom
	data(0x01);											//initializing address on eeprom
	data('k');
	data('a');
	data('r');
	I2CONSET=1<<4;									//to stop
	delay(1000);
	
	
	start();
	data(0xa0);
	data(0x50);
	data(0x01);
	
	start();
	data(0xa1);
	
	I2CONSET=1<<2;							/*asset ack(compulsary for read)(if not written only first chararcter is read*/
	
	I2CONCLR=1<<3;
	
	/*read from data1*/
	while(!(I2CONSET & 1<<3));
	b=I2DAT;
	I2CONCLR=1<<3;
	led_data(b);
	
	/*read from data2*/
	while(!(I2CONSET & 1<<3));
	b=I2DAT;
	I2CONCLR=1<<3;
	led_data(b);
	
	/*read from data3*/
	while(!(I2CONSET & 1<<3));
	b=I2DAT;
	I2CONCLR=1<<3;
	led_data(b);
	
	I2CONCLR=1<<4;
}
