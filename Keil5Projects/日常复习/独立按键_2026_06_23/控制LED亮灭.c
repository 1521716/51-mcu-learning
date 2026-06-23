#include <REGX52.H>
#include <INTRINS.H>

#define LED P2_0
#define KEY P3_1

#define LED_ON 0
#define LED_OFF 1
#define PRESSED 0

void Delay1ms(unsigned int xms)	//@11.0592MHz
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
		if(KEY == PRESSED)
		{
			Delay1ms(20);
			if(KEY == PRESSED)
			{
				LED = LED_ON;
			}
		}
		else
			LED = LED_OFF;
	}
}
