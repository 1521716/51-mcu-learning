#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "Delay.h"
#include "DS18B20.h"
#include "Timer0.h"
#include "UART.h"


volatile float T,TH = 35.0,TL = 5.0;
unsigned char idata rx_buf[30],index = 0,s;
bit rx_ready = 0;
unsigned char code Status[3][30] = {"NORMAL","HIGH","LOW"};


void main()
{
	UART_Init();
	DS18B20_CONVERT();
	Delay(1000);
	T = DS18B20_ReadT();
	LCD_Init();
	LCD_ShowString(1,1,"Temp:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	Timer0_Init();
	
	
	while(1)
	{
		LCD_ShowNum(1,6,T,3);
		LCD_ShowChar(1,9,'.');
		LCD_ShowNum(1,10,(unsigned long)(T*10)%10,1);
		LCD_ShowNum(2,4,TH,3);
		LCD_ShowChar(2,7,'.');
		LCD_ShowNum(2,8,(unsigned long)(TH*10)%10,1);
		LCD_ShowNum(2,12,TL,3);
		LCD_ShowChar(2,15,'.');
		LCD_ShowNum(2,16,(unsigned long)(TL*10)%10,1);
		
		if(rx_ready)
		{
			rx_ready = 0;
			parse_cmd(rx_buf);
		}
		
		
	}
}

void Timer0_ISR()	interrupt 1
{
	static unsigned char Timer0_Count = 0;
	TL0 = (65536-50000)%256;
	TH0 = (65536-50000)/256;
	Timer0_Count++;
	if(Timer0_Count>=40)//每2秒执行一次温度并且向电脑发送
	{
		Timer0_Count = 0;
		DS18B20_CONVERT();//更新温度
		T = DS18B20_ReadT();
		printf("T:%.1f,H:%.1f,L:%.1f",T,TH,TL);//发送状态到电脑
		if(T<=TH&&T>=TL)	printf("S:NORMAL\n");
		else if(T<TL)	printf("S:LOW\n");
		else	printf("S:HIGH\n");
		
	}
}
void UART_ISR()	interrupt 4
{
	unsigned char ch;
	if(RI == 1)
	{
		ch = SBUF;
		RI = 0;
		SBUF = ch;
		while(TI == 0);
		TI = 0;
		
		if(ch =='\n')
		{
			rx_buf[index] = '\0';
			index = 0;
			rx_ready = 1;
		}
		else
		{
			rx_buf[index] = ch;
			index++;
			if(index>=29)	return;
		}
	}
}
