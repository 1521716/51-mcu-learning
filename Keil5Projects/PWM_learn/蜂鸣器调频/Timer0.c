#include <REGX52.H>

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;	// Timer0, Mode1 16-bit
	TR0 = 0;		// 初始关闭
	TL0 = 0x00;
	TH0 = 0x00;
	EA = 1;
	ET0 = 1;
}
