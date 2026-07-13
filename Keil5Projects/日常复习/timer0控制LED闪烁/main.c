#include <REGX52.H>
#include "Timer0.h"

#define LED P2_0

void main()
{
	//初始化定时器
	Timer0_Init();
	//初始化LED
	LED = 1;//灭
	while(1)
	{
		
	}
}

void timer0_interrupt()	interrupt 1
{
	static unsigned int Timer0Count = 0;
	
	//重置高低位
	TL0 = 64536%256;//低位
	TH0 = 64536/256;//高位
	
	Timer0Count++;
	
	if(Timer0Count>=500)
	{
		Timer0Count = 0;
		LED = ~LED;
	}
}