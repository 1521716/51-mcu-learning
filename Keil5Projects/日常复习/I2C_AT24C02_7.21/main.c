#include <REGX52.H>
#include "AT24C02.h"

#define LED P2

void main()
{
	LED = 0xFF;
	//AT24C02_WriteByte(0xAA);
	//写入有写入周期，这里只是演示，故不在加Delay
	LED = AT24C02_ReadByte();
	while(1)
	{
		
	}
}
