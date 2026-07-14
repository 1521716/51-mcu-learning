#include <REGX52.H>
#include "LCD1602.h"

unsigned int Count;

void Timer0_Init()
{
	TMOD = 0x01;		//定时器0的模式设置：16位|定时器|只由TR0控制
	TF0 = 0;			//初始未溢出（不初始化也可以，默认为0）
	TR0 = 1;			//开启定时器0
	TH0 = 64535/256;	//提前设置高低位，达成每1ms中断一次
	TL0 = 64535%256+1;
	ET0 = 1;			//中断控制
	EA = 1;
	PT0 = 0;			//最低优先级中断
	
	/*与或配置法：适用于配置某些配置而不影响其余配置
	TMOD = TMOD&0xF0;	//前四位不变，后四位置0
	TMOD = TMOD|0x01;	//前四位不变，按需配置后四位
	*/
}

void main()
{
	Timer0_Init();
	LCD_Init();
	while(1)
	{
		LCD_ShowNum(1,1,Count/1000,3);
	}
}


//中断发生执行函数
void Timer0_Routine()	interrupt 1
{
	TH0 = 64535/256;	//手动重装初始值
	TL0 = 64535%256;
	Count++;
}
