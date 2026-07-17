#include <REGX52.H>
#include "Key.h"

#define LED P2

unsigned char KeyNumber = 0;

void main()
{
	LED = 0xFF;
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber)
		{
			LED = ~(0x01<<(KeyNumber-1));
		}
	}
}
