#include<lpc21xx.h>
int a;
void delay(void)
{
	int i;
	for(i=0;i<1000000;i++);
}
void uart(void)__irq
{
	a=U0RBR;
	while(!(U0LSR & (1<<5)));
	U0THR=a;
	IOSET0=1<<11;
	delay();
	IOCLR0=1<<11;
	delay();
	VICVectAddr=0;
}

int main()
{
	IODIR0=1<<11;
	PINSEL0=1<<0|1<<2;			//step1: Select uart pins
	U0LCR=3<<0|1<<7;				//step2: Select word length and Enable access to divisor latch register
	U0DLL=97;								//step3: Set Baud rate
	U0LCR=(1<<1)|(1<<0)|(0<<7);					//step4: Disable access to divisor latch
	U0IER=1;
	VICIntEnable=1<<6;
	VICVectAddr7=(long)uart;
	VICVectCntl7=6|1<<5;
	while(1);
}
