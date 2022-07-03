#include<lpc21xx.h>
void delay(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1500;j++);
}
int main()
{
	IODIR1=0XFF<<17;
	IODIR0=1<<11;
	while(1)
	{
	 int i,j;
		for(i=17,j=24;i<21;i++,j--)
		{
			IOSET1|=1<<i|1<<j;
			//IOSET1|=1<<j;
			delay();
			IOCLR1|=1<<i|1<<j;
			//IOCLR1|=1<<j;
			delay();
			
		}
			  
			
				
	}
}
