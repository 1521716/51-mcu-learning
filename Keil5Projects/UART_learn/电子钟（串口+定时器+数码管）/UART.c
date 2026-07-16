#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "UART.h"

/**
  * @brief  串口初始化函数
  * @param  无
  * @retval  无
  本初始化函数为4800bps@11.0592MHz
  */
void UART_Init()//4800bps@11.0592MHz
{
	//串口配置
	SCON = 0x50;		//启用模式1：8位UART，可变波特率；允许接收；
	PCON |= 0x80;		//无检验位，8位；波特率加倍
	//定时器1配置
	TMOD &= 0x0F;		//定时器1寄存器全部清零
	TMOD |= 0x20;		//配置定时器1模式：计时器，8位自动重载
	TR1 = 1;			//打开计时器1
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断(按需开启)
	ES = 1;
	EA = 1;
	/*
	ET1 = 1;
	*/
}

/**
  * @brief  解析接收到的命令
  * @param  cmd	字符串缓冲区，用于接收命令
  * @retval  无
  */
void prase_cmd(unsigned char *cmd)
{
	if(strstr(cmd,"QUERY"))
	{
		printf("%d:%d:%d\n",(unsigned int)Hou,(unsigned int)Min,(unsigned int)Sec);
	}
	else if(strstr(cmd,"TIME"))
	{
		Hou = cmd[5]-'0';
		Hou *= 10;
		Hou += cmd[6]-'0';
		Min = cmd[8]-'0';
		Min *= 10;
		Min += cmd[9]-'0';
		Sec = cmd[11]-'0';
		Sec *= 10;
		Sec += cmd[12]-'0';
		
	}
}


/**
  * @brief  串口向电脑发送一字节数据（printf重定向）
  * @param  ch 要发送的一字节数据
  * @retval  ch 本次发送的数据
  */
char putchar(char ch)
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
	return ch;
}

void UART_ISR()	interrupt 4
{
	unsigned char ch = 0;
	if(RI == 1)
	{
		ch = SBUF;
		RI = 0;
		SBUF = ch;
		while(TI == 0);
		TI = 0;
		if(ch =='\n')
		{
			str_cmd[index] = '\0';
			flag = 1;
			index = 0;
		}
		else
		{
			str_cmd[index] = ch;
			index++;
			if(index>=30)	return;
			
		}
	}
}