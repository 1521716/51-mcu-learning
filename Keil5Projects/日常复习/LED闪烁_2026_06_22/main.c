#include <REGX52.H>
#include <INTRINS.H>

#define LED P2_0

#define LED_ON 0
#define LED_OFF 1

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
	
}


void main()
{
	while(1)
	{
		LED = LED_ON;
		Delay(500);
		LED = LED_OFF;
		Delay(500);
	}
}
