#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit Buzzer = P2^5;

unsigned int FreqTable[] = {
	63775,63874,63967,64055,64138,64217,64291,64360,64426,64489,64548,64603,
	64655,64705,64751,64795,64837,64876,64913,64948,64981,65012,65042,65069,
	65096,65120,65144,65166,65187,65206,65225,65242,65259,65274,65289,65303
};
unsigned char FreqSelect = 0;

void main()
{
	Timer0_Init();
	while(1)
	{
		FreqSelect++;
		Delay(500);
	}
}

void Timer0_Routine()	interrupt 1
{
	TL0 = FreqTable[FreqSelect]%256;				
	TH0 = FreqTable[FreqSelect]/256;				
	Buzzer = ~Buzzer;
}