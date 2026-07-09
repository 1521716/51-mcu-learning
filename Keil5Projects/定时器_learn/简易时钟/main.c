#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"

unsigned char Sec,Min,Hou;


void main()
{
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		LCD_ShowNum(2,1,Hou,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
		
	}
}

void Timer0_Routine()		interrupt 1
{
	static unsigned int Timer0_Count = 0;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	
	Timer0_Count++;
	
	if(Timer0_Count>=1000)
	{
		Timer0_Count = 0;
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
