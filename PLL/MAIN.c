#include<lpc21xx.h>
#include<lcdheader.h>
/*PLL 	calculation
Fclk = Crystal oscillator frequency
Cclk = Desired frequency
Fcco = current controlled osc frequency
Step1: Calculate the value of M(Multiplier) and put M-1 in MSEL Bits	(Range of MSEL = 0-31)
				M = Cclk/Fclk
Step2: Calculate the value of P(Divisor) and put corresponding PSEL Bits from Table

Table: PLL Divider values
PSEL Bits (PLLCFG bits [6:5]) 		Value of P
00 																1
01 																2
10 																4
11 																8

(Fcco-min/2*Cclk) < P < (Fcco-max/2*Cclk);
where Fcco-min = 160MHz
			Fcco-max = 320MHz (i.e., 160MHz < Fcco < 320MHz)
			
Step3: Put MSEL and PSEL values in PLLCNG register.
*/
void pll_36MHz(void)
{
	PLLCON=1;											//PLL enable
	PLLCFG=2|2<<5;								//M=3 so MSEL=M-1=2, P=4 so PSEL=01=2 according to table 
	PLLFEED=0XAA;									//Update control and config registers
	PLLFEED=0X55;
	while(!(PLLSTAT&(1<<10)));		//wait for pll to lock at target frequency
	PLLCON|=1<<1;									//CONNECT
	PLLFEED=0xaa;									//Uptade control and config registers
	PLLFEED=0x55;
}
void pll_12MHz(void)
{
	PLLCON=1;											//PLL enable
	PLLCFG=0|3<<5;								//M=1,P=8
	PLLFEED=0XAA;									//Update control and config registers
	PLLFEED=0X55;
	while(!(PLLSTAT&(1<<10)));		//wait for pll to lock at target frequency
	PLLCON|=1<<1;									//CONNECT
	PLLFEED=0xaa;									//Update control and config registers
	PLLFEED=0x55;
}

int main()
{
	IODIR1=255<<17;
	int i=0;
	while(1)
	{
		IOSET1=255<<17;
		delay(1000);
		IOCLR1=255<<17;
		delay(1000);
		i++;
		if(i>5&&i<10) pll_36MHz();
		else if(i>10) pll_12MHz();
	}
}
