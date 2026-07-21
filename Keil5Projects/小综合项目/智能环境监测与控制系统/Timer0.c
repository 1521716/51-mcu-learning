#include <REGX52.H>

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TR0 = 1;
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	
	EA = 1;
	ET0 = 1;
}

