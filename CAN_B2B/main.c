#include<lpc21xx.h>
#include"../prototype.h"
unsigned int a,b,key;
void can_init(void)
{
	VPBDIV =0x02;
	PINSEL1 |= (1<<22) | (1<<24) |(1<<26) |(1<<28) |(1<<18) |(1<<16) |(1<<14) ;
//	C1MOD=1<<0;			//RESET MODE 
//	C1BTR=1<<20|1<<19|1<<18|2;
//	C1MOD=0;
	
	C2MOD=1<<0;
	C2BTR=1<<20|1<<19|1<<18|2;
	C2MOD=0;
}

void TX_from_CAN2(unsigned int ch)
{
	while((C2SR&0x00000004)!=0x00000004);
	C2TFI1=1<<18;
	C2TDA1=ch;
	C2TID1=0x45;																//MESSAGE ID (OUR CHOICE)
	C2CMR=1<<0|1<<5;
	while((C2GSR&0x00000008)!=0x00000008);
//	led_cmd(0x01);
//	lcd_str("TX SUCCESSFUL");
//	delay(5000);
}
void test()
{
	test:
	key=IOPIN1;
	key=(1<<25) & key;
	if(key)
	{
		TX_from_CAN2(1);
		up:
		a=IOPIN0;
		a=(0x00000010 & a);
		b=IOPIN0;
		b=(0x00000040 & b);
		
		if(a==0 && b==0)
		{
			TX_from_CAN2(2);
		}
		else
		{
			TX_from_CAN2(3);
			goto up;
		}
	}
	else
	{
		goto test;
	}
	
}
int main()
{
//	int res;
	can_init();
	test();

}
