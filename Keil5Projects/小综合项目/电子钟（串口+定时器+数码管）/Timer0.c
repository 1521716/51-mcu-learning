#include <REGX52.H>
#include "UART.h"

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TR0 = 1;
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	ET0 = 1;
}

void Timer0_ISR()	interrupt 1
{
	static unsigned char Timer0Count = 0;
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	Timer0Count++;
	if(Timer0Count>=20)
	{
		Timer0Count = 0;
		Sec++;
		if(Sec>=60)
		{
			Sec = 0;
			Min++;
			if(Min>=60)
			{
				Min = 0;
				Hou++;
				if(Hou>=24)
				{
					Hou = 0;
				}
			}
		}
	}
}