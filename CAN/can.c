#include<lpc21xx.h>
#include"../prototype.h"
unsigned int MSG[4];
unsigned int RX_in_CAN1(void)
{
	while((C1SR&0x01));
	MSG[0]=C1RID;
	MSG[1]=C1RDA;
	MSG[2]=C1RDB;                                      
	C1CMR=1<<2;
	return MSG[1];
}




void TX_from_CAN2(unsigned int ch)
{
	while((C2SR&0x00000004)!=0x00000004);
	C2TFI1=1<<18;
	C2TDA1=ch;
	C2TID1=0x45;																//MESSAGE ID (OUR CHOICE)
	C2CMR=1<<0|1<<5;
	while((C2GSR&0x00000008)!=0x00000008);
}





unsigned char can_test(void)
{
	unsigned int a,b,key;
	test:
	led_cmd(0x01);
	lcd_str("turn on ignition");
	delay(3000);
	key=IOPIN1;
	key=(1<<25) & key;
	if(key)
	{
		led_cmd(0x01);
		lcd_str("KEY PASS");
		delay(2000);
		TX_from_CAN2(2);
		while(!(RX_in_CAN1()==2));
		led_cmd(0x01);
		lcd_str("IGNITION ON");
		delay(3000);
		led_cmd(0x01);
		lcd_str("CHECKING STATUS FROM MODULES");
		delay(3000);
		a=IOPIN0;
		a=(0x00000010 & a);
		b=IOPIN0;
		b=(0x00000040 & b);
		if(a==0 && b==0)
		{
			TX_from_CAN2(2);
			while(!(RX_in_CAN1()==2));
			led_cmd(0x01);
			lcd_str("BREAK TEST PASS");
			delay(3000);
			
			TX_from_CAN2(2);
			while(!(RX_in_CAN1()==2));
			
			led_cmd(0x01);
			lcd_str("SEAT BELT PASS");
			delay(3000);
			return 1;
		}
		else if(a!=0 && b!=1)
		{
			led_cmd(0x01);
			delay(1000);
			lcd_str("WEAR SEAT BELT");
			delay(5000);
			return 0;
		}
		else if(a!=1 && b!=0)
		{
			led_cmd(0x01);
			delay(1000);
			lcd_str("RELEASE HAND BRAKE");
			delay(5000);
			return 0;
		}
		else {
			led_cmd(0x01);
			delay(1000);	
			lcd_str("MODULE TEST FAIL");
			delay(3000);
			return 0;
		}
	}
	else{
		goto test;
	}
}


void can_init(void)
{
	VPBDIV =0x02;
	PINSEL1 |= (1<<22) | (1<<24) |(1<<26) |(1<<28) |(1<<18) |(1<<16) |(1<<14) ;
	C1MOD=1<<0;			//RESET MODE 
	C1BTR=1<<20|1<<19|1<<18|2;
	C1MOD=0;
	
	C2MOD=1<<0;
	C2BTR=1<<20|1<<19|1<<18|2;
	C2MOD=0;
}
