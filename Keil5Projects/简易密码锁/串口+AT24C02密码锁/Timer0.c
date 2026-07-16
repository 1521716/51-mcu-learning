#include <REGX52.H>
#include "NiXie.h"
#include "Timer0.h"

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TR0 = 1;
	TL0 = (65536-1000)%256;
	TH0 = (65536-1000)/256;
	EA = 1;
	ET0 = 1;
}

void Timer0_ISR()	interrupt 1
{
	static unsigned char pos = 0;
	TL0 = (65536-1000)%256;
	TH0 = (65536-1000)/256;
	pos++;
	if(pos > 4) pos = 1;
	NiXie(pos, Input[pos-1]);
}





