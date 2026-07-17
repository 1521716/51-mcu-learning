#include <REGX52.H>
#include "NiXie.h"
#include "Timer0.h"

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TR0 = 1;
	TL0 = 0x9C;
	TH0 = 0xFF;
	EA = 1;
	ET0 = 1;
}
/*
void Timer0_ISR()	interrupt 1
{
	TL0 = 0x9C;
	TH0 = 0xFF;
}*/





