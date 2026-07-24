#include <REGX52.H>
#include "NiXie.h"
#include "Timer1.h"

void Timer1_Init()
{
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TR1 = 1;
	TL1 = 0x9C;
	TH1 = 0xFF;
	EA = 1;
	ET1 = 1;
}
/*
void Timer1_ISR()	interrupt 3
{
	TL0 = 0x9C;
	TH0 = 0xFF;
}*/





