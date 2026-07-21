#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "UART.h"

void UART_Init()
{
	SCON = 0x50;
	PCON &= 0x80;
	TMOD &= 0x0F;
	TMOD |= 0X20;
	TR1 = 1;
	TL1 = 0xFD;//9600波特率
	TH1 = 0xFD;

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
	if(strstr(cmd,"TH:"))
	{
		unsigned char i = 3,temp = 0;
		while(cmd[i]>='0'&&cmd[i]<='9')
		{
			temp = temp*10+(cmd[i]-'0');
			i++;
		}
		TH = temp;
	}
	else if(strstr(cmd,"TL:"))
	{
		unsigned char i = 3,temp = 0;
		while(cmd[i]>='0'&&cmd[i]<='9')
		{
			temp = temp*10+(cmd[i]-'0');
			i++;
		}
		TL = temp;
	}
	else if(strstr(cmd,"QUERY"))
	{
		printf("T:%.1f,H:%.1f,L:%.1f",T,TH,TL);//发送状态到电脑
		if(T<=TH&&T>=TL)	printf("S:NORMAL\n");
		else if(T<TL)	printf("S:LOW\n");
		else	printf("S:HIGH\n");
	}
	else
		printf("The command is error!\n");
}

