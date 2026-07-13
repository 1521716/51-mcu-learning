#include <REGX52.H>
#include "Timer0.h"

void Timer0_Init()
{
	//配置定时器0的TMOD，同时不更改定时器1的配置（不可位寻址）
	TMOD &= 0xF0;//先将定时器0的所有寄存器置0
	TMOD |= 0x01;//将定时器0设置为不由INT0控制，用作定时器，采用16位定时器
	//配置定时器0的TCON（位寻址）
	TR0 = 1;//启用定时器0
	//配置初值，控制定时时长
	TL0 = 64536%256;//低位
	TH0 = 64536/256;//高位
	
	//配置中断权限
	ET0 = 1;
	EA = 1;
	
}

/*
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
	}
}
*/