#include <REGX52.H>
#include "Delay.h"

#define LED P2
#define KEY P3_2

#define LEDNUM 8
#define KEY_PRESSED 0

volatile unsigned char k = 0;
bit flag = 0;
unsigned char LED_smg[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};


void Timer0_Init()
{
	TMOD = 0x01;
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void INT0_Init()
{
	IT0 = 0;//由下降沿触发中断
	EX0 = 1;//允许INT0外部中断
	EA = 1;
}

void main()
{
	unsigned char i = 0;
	Timer0_Init();
	INT0_Init();
	LED = LED_smg[i];
	while(1)
	{
		if(flag)
		{
			flag = 0;
			i = (i+1)%LEDNUM;
			LED = LED_smg[i];
			
		}
	}
}

void Timer0_ISR()	interrupt 1
{
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	k++;
	if(k>=20)
	{
		k = 0;
		flag = 1;
	}
	
}

void INT0_ISR()	interrupt 0
{
	Delay(20);
	if(KEY == KEY_PRESSED)
	{
		TR0 = ~TR0;
	}
	
}