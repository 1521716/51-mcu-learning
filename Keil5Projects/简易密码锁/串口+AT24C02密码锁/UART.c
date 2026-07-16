#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "AT24C02.h"
#include "Delay.h"


void UART_Init()
{
	//串口配置
	SCON = 0x50;
	PCON = 0x80;
	//定时器1配置
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TR1 = 1;
	//初值
	TL1 = 0xF4;
	TH1 = 0xF4;
	//中断
	ES = 1;
}

char putchar(char ch)
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
	return ch;
}

void parse_cmd(unsigned char *cmd)
{
	if(strstr(cmd,"RESET"))
	{
		PASSWORD[0] = 1;
		PASSWORD[1] = 2;
		PASSWORD[2] = 3;
		PASSWORD[3] = 4;
		AT24C02_SendByte(0,PASSWORD[0]);Delay(5);
		AT24C02_SendByte(1,PASSWORD[1]);Delay(5);
		AT24C02_SendByte(2,PASSWORD[2]);Delay(5);
		AT24C02_SendByte(3,PASSWORD[3]);Delay(5);
	}
	else if(strstr(cmd,"SHOW"))
	{
		unsigned char k = 0;
		for(k = 0;k<4;k++)
			Input[k] = PASSWORD[k];
	}
	else
		printf("%s\n","ERROR");
}

void UART_ISR()	interrupt 4
{
	unsigned char ch = 0;
	if(RI)
	{
		ch = SBUF;
		RI = 0;
		SBUF = ch;
		while(TI ==0);
		TI = 0;
		
		if(ch == '\n')
		{
			rx_buf[index] = '\0';
			index = 0;
			rx_ready = 1;
		}
		else 
		{
			if(index>29)	return;
			rx_buf[index] = ch;
			index++;
		}
	}
}
