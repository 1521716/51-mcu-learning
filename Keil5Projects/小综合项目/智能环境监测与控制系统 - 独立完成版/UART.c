#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "AT24C02.h"


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
		AT24C02_WriteByte(20,TH);
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
		AT24C02_WriteByte(21,TL);
	}
	else if(strstr(cmd,"QUERY"))
	{
		printf("T:%.1f,H:%.1f,L:%.1f",T,TH,TL);//发送状态到电脑
		if(T<=TH&&T>=TL)	printf("S:NORMAL\n");
		else if(T<TL)	printf("S:LOW\n");
		else	printf("S:HIGH\n");
	}
	else if(strstr(cmd,"HISTORY"))
	{
		unsigned char pos = front;
		printf("History:");
		while(pos != tail)
		{
			int val = AT24C02_ReadInt(HISTORY_BASE + pos * 2);	//读取2字节温度×10
			printf("%.1f ", val / 10.0);						//还原真实温度
			pos = (pos + 1) % MAXSIZE;
		}
		printf("\n");
	}
	else
		printf("The command is error!\n");
}
