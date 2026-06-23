#include <REGX52.H>
#include <INTRINS.H>

#define LED P2

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
	unsigned char LEDNum = 0;
	while(1)
	{
		
		while(LEDNum < 8)
		{
			LED = ~(0x01<<LEDNum);
			Delay1ms(500);
			LEDNum++;
		}
		while(LEDNum > 0)
		{
			LEDNum--;
			LED = ~(0x01<<LEDNum);
			Delay1ms(500);
		}
	}
}
