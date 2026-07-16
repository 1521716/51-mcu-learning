#include <REGX52.H>
#include "AT24C02.h"

#define LED P2

void main()
{
	unsigned char LEDKey = 0;
	//AT24C02_WriteByte(0,0x02);
	LEDKey = AT24C02_ReadByte(0);
	LED = LEDKey;
	while(1)
	{
		
	}
}