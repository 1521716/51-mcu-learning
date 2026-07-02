#include <REGX52.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "Delay.h"
#include "Key.h"

unsigned char KeyNumber,LEDMode;

void main()
{
	P2 = 0xFE;
	Timer0_Init();
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber)
		{
			if(KeyNumber == 1)
				LEDMode = ~LEDMode;
		}
	}
}

//定时器中断函数模板
void Timer0_Routine()	interrupt 1
{
	static unsigned int T0Count = 0;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count = 0;
		if(LEDMode == 0)
		{
			P2 = _cror_(P2,1);
		}
		else
			P2 = _crol_(P2,1);
	}
	
		
}