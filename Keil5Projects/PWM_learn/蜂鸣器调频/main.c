#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "key.h"
#include "Timer0.h"

sbit Buzzer = P2^5;

unsigned char KeyNum, Freq = 0;
unsigned char Count = 0, Compare = 4;		// 4/8 = 50%占空比
unsigned char TH0_Reload, TL0_Reload;

/*
	PWM频率 = 921600 / (8 × (65536 - reload))
	档位1: ~500Hz,  reload=0xFF1A (230步)
	档位2: ~1000Hz, reload=0xFF8D (115步)
	档位3: ~2000Hz, reload=0xFFC6 (58步)
	档位3 ISR间隔=58周期，ISR~20周期，CPU有喘息空间
*/

void SetGear(unsigned char gear)
{
	TR0 = 0;
	switch(gear)
	{
		case 0:
			Buzzer = 0;
			LCD_ShowString(1, 1, "Gear:0 OFF      ");
			break;
		case 1:
			TH0_Reload = 0xFF;
			TL0_Reload = 0x1A;
			Count = 0;
			TR0 = 1;
			LCD_ShowString(1, 1, "Gear:1 500Hz    ");
			break;
		case 2:
			TH0_Reload = 0xFF;
			TL0_Reload = 0x8D;
			Count = 0;
			TR0 = 1;
			LCD_ShowString(1, 1, "Gear:2 1000Hz   ");
			break;
		case 3:
			TH0_Reload = 0xFF;
			TL0_Reload = 0xC6;
			Count = 0;
			TR0 = 1;
			LCD_ShowString(1, 1, "Gear:3 2000Hz   ");
			break;
	}
}

void main()
{
	Timer0_Init();
	LCD_Init();
	SetGear(0);
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			Freq++;
			if(Freq > 3) Freq = 0;
			SetGear(Freq);
		}
	}
}

void Timer0_ISR() interrupt 1
{
	TL0 = TL0_Reload;
	TH0 = TH0_Reload;
	Count++;
	Count &= 0x07;			// %8，位与比取模快很多
	if(Count < Compare)
		Buzzer = 1;
	else
		Buzzer = 0;
}
