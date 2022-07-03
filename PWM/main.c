#include<lpc21xx.h>
void delay(void)
{
	int i,j;
	for(i=0;i<10000;i++)
	for(j=0;j<1000;j++);
}

int main()
{
	PINSEL0=1<<17;					//select pwm4 functionality
	PWMMCR=1<<1;					//reset counter
	PWMPCR=1<<12|1<<4;				//enable pwm4 output
	PWMPR=14;
	PWMMR0=10000;					//Period T
	PWMLER=1<<0;					//Latch enable register or shadow register to uptade pwm match registers
	PWMTCR=1<<0|1<<3;
	while(1)
	{
		PWMMR4=1000;				//Duty cycle=pwmm4/pwmm0; //T on time
		PWMMR5=9000;
		PWMLER|=1<<4|1<<5;
		delay();
		PWMMR4=4000;				//Duty cycle=pwmm4/pwmm0; //T on time
		PWMMR5=6000;
		PWMLER|=1<<4|1<<5;
		delay();
	}
}
