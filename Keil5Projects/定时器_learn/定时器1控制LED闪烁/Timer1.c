#include <REGX52.H>


void Timer1_Init()
{
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TR1 = 1;
	TL1 = 64536%256;
	TH1 = 64536/256;
	ET1 = 1;
	EA = 1;
}
/*
void Timer1_ISR()	interrupt 3
{
	static unsigned int Timer1Count = 0;	
	Timer1Count++;
	TL1 = 64536%256;
	TH1 = 64536/256;
	if(Timer1Count>=500)
	{
		Timer1Count = 0;
		LED = ~LED;
	}
}
*/