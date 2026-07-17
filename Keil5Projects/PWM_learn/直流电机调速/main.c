#include <REGX52.H>
#include "Delay.h"
#include "key.h"
#include "NiXie.h"
#include "Timer0.h"

sbit Motor = P1^0;
unsigned char Counter,Compare;
unsigned char KeyNum,Speed;
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
	Timer0_Init();
	
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			Speed++;
			Speed%=4;
			if(Speed == 0)	Compare = 0;
			if(Speed == 1)	Compare = 50;
			if(Speed == 2)	Compare = 75;
			if(Speed == 3)	Compare = 100;
		}
		NiXie(1,Speed);
	}
}

void Timer0_ISR()	interrupt 1
{
	TL0 = 0x9C;
	TH0 = 0xFF;
	Counter++;
	Counter%=100;
	if(Counter<Compare)	Motor = 1;
	else	Motor = 0;
}