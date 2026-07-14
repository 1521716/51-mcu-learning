#include <REGX52.H>
#include "Timer1.h"
#define LED P2_0

void main()
{
	Timer1_Init();
	LED = 1;
	while(1)
	{
		
	}
}

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
