#include <REGX52.H>
#include "NiXie.h"
#include "Delay.h"

unsigned char code smg_duan[] = {
	0x3F, // 0: 00111111
    0x06, // 1: 00000110
    0x5B, // 2: 01011011
    0x4F, // 3: 01001111
    0x66, // 4: 01100110
    0x6D, // 5: 01101101
    0x7D, // 6: 01111101
    0x07, // 7: 00000111
    0x7F, // 8: 01111111
    0x6F, // 9: 01101111
	0x40
};

void main()
{
	NiXie(1,0);
	while(1)
	{
		unsigned char i = 0;
		for(i = 0;i<10;i++)
		{
			NiXie(1,i);
			Delay(1000);
		}
	}
}