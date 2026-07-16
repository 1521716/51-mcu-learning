#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "Key.h"
#include "NiXie.h"
#include "UART.h"
#include "Timer0.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char code smg_duan[] = {
	0x3F, // 0: 00111111
    0x06, // 1: 00000110
    0x5B, // 2: 01011011
    0x4F, // 3: 01001111
    0x66, // 4: 01100110
    0x6D, // 5: 01101101
    0x7D, // 6: 01111101
    0x07, // 7: 00000111
    0x7F, // 8: 01111111
    0x6F, // 9: 01101111
	0x40
};

unsigned char PASSWORD[4] = {1,2,3,4};
unsigned char Input[4] = {0,0,0,0};
unsigned char Count = 0,index = 0;
unsigned char rx_buf[30];
bit rx_ready = 0;
unsigned char flag = 0;


void main()
{
	
	unsigned char KeyNumber = 0,j = 0;
	Timer0_Init();
	UART_Init();
	for(j = 0;j<4;j++)
	{
		if(AT24C02_ReceiveByte(j)>9)//第一次默认密码设置：
		{
			PASSWORD[0] = 1;
			PASSWORD[1] = 2;
			PASSWORD[2] = 3;
			PASSWORD[3] = 4;
			break;
		}
		PASSWORD[j] = AT24C02_ReceiveByte(j); 
		
	}
		
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber>0&&KeyNumber<=9)
		{
			if(Count>=4)
				;
			else	
				Input[Count++] = KeyNumber%10;
			
		}
		else if(KeyNumber == 11)
		{
			unsigned char i = 0;
			if(flag)//密码刚刚已经正确，现在设置密码
			{
				flag = 0;
				AT24C02_SendByte(0,Input[0]);Delay(5);
				AT24C02_SendByte(1,Input[1]);Delay(5);
				AT24C02_SendByte(2,Input[2]);Delay(5);
				AT24C02_SendByte(3,Input[3]);Delay(5);
			}
			for(i = 0;i<4;i++)
			{
				if(PASSWORD[i] != Input[i])
					break;
			}
			if(i == 4)	flag = 1;
			if(flag == 0)
					printf("%s","The PassWord is error");
			else
			{
				printf("%s","Please input new Code");
				Count = 0;
				for(i = 0;i<4;i++)
				{
					Input[i] = 0;
				}
				
			}
			
			
		}
		else if(KeyNumber == 12)
		{
			Count = 0;
			Input[0] = 0;Input[1] = 0;Input[2] = 0;Input[3] = 0;
		}
		if(rx_ready)
		{
			rx_ready = 0;
			parse_cmd(rx_buf);
		}
	}
}






