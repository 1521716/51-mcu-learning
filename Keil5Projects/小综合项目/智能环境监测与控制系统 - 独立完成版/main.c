#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "Delay.h"
#include "DS18B20.h"
#include "Timer0.h"
#include "UART.h"
#include "AT24C02.h"
#include "Status.h"

volatile float T,TH = 35.0,TL = 5.0;
unsigned char idata rx_buf[20],index = 0,S;
bit rx_ready = 0;
bit upData_flag = 0,upStatus_flag = 0,Save_flag = 0;
unsigned char front = 0,tail = 0;
int temp_int;					//温度×10的临时变量（Keil C51须在开头声明）
bit echo_flag = 0;              // 新增：有字节待回显
unsigned char echo_ch;          // 新增：待回显的字节


void main()
{

	UART_Init();
	DS18B20_CONVERT();
	TH = AT24C02_ReadByte(20);
	if(TH>125||TH<-55)	TH = 35.0;
	TL = AT24C02_ReadByte(21);
	if(TL>125||TL<-55)	TL = 5.0;
	AT24C02_WriteByte(20,TH);
	AT24C02_WriteByte(21,TL);
	Delay(1000);
	T = DS18B20_ReadT();
	LCD_Init();
	LCD_ShowString(1,1,"Temp:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	Timer0_Init();


	while(1)
	{
		if(upData_flag)
		{
			upData_flag = 0;
			DS18B20_CONVERT();//更新温度
			T = DS18B20_ReadT();
			printf("T:%.1f,H:%.1f,L:%.1f\n",T,TH,TL);//发送状态到电脑
			LCD_ShowNum(1,6,T,3);
			LCD_ShowChar(1,9,'.');
			LCD_ShowNum(1,10,(unsigned long)(T*10)%10,1);
			LCD_ShowNum(2,4,TH,3);
			LCD_ShowChar(2,7,'.');
			LCD_ShowNum(2,8,(unsigned long)(TH*10)%10,1);
			LCD_ShowNum(2,12,TL,3);
			LCD_ShowChar(2,15,'.');
			LCD_ShowNum(2,16,(unsigned long)(TL*10)%10,1);
		}
		if(upStatus_flag)
		{
			upStatus_flag = 0;
			if(T<=TH&&T>=TL)	printf("S:NORMAL\n");
			else if(T<TL)
			{
				printf("S:LOW\n");
				Status_Low();

			}
			else
			{
				printf("S:HIGH\n");
				Status_High();
			}

		}
		if(Save_flag)
		{
			Save_flag = 0;
			temp_int = (int)(T * 10);						//温度×10转16位整数（如25.6→256）
			if((tail + 1) % MAXSIZE == front)				//队列已满→覆盖最旧数据
			{
				AT24C02_WriteInt(HISTORY_BASE + tail * 2, temp_int);
				tail = front;
				front = (front + 1) % MAXSIZE;
			}
			else											//队列空或不满→正常追加
			{
				AT24C02_WriteInt(HISTORY_BASE + tail * 2, temp_int);
				tail = (tail + 1) % MAXSIZE;
			}
		}
		if(echo_flag)
		{
			echo_flag = 0;
			SBUF = echo_ch;
			while(TI == 0);   // 忙等挪到主循环，不干扰中断时序
			TI = 0;
		}

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
		upData_flag = 1;
		upStatus_flag = 1;
		Save_flag = 1;

	}
	Status_BlinkHandler();
}
void UART_ISR()	interrupt 4
{
	unsigned char ch;
	if(RI == 1)
	{
		ch = SBUF;
		RI = 0;
		// 不再在 ISR 里回显！改为通知主循环
          echo_ch = ch;
          echo_flag = 1;

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
			if(index>=19)	return;
		}
	}

}
