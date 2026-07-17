#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "NiXie.h"
#include "Buzzer.h"


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
unsigned char KeyNum;

void main()
{
	NiXie(1,0);
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			Buzzer_Timer(500);
			NiXie(1,KeyNum);
		}
	}
}