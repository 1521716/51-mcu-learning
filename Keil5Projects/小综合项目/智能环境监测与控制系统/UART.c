#include "config.h"
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "AT24C02.h"

unsigned char idata rx_buf[20];
unsigned char rx_index = 0;
bit rx_ready = 0;

/**
  * @brief  串口初始化：9600bps,8位
  * @param  无
  * @retval  无
  */
void UART_Init()
{
	SCON = 0x50;		// 模式1（8位UART），允许接收
	PCON &= 0x80;		// SMOD = 0（不加倍）
	TMOD &= 0x0F;		// 不干扰Timer0,只配置Timer1
	TMOD |= 0X20;		// Timer1:模式2（8位自动重装）
	TR1 = 1;			// 启动Timer1
	TL1 = 0xFD;			// 9600bps @11.0592MHz
	TH1 = 0xFD;

	ES = 1;				// 使能串口中断
}

/**
  * @brief  发送一个字节（主循环调用，非ISR）
  * @param  ch 要发送的字节
  * @retval  发送的字节
  */
void UART_SendByte(unsigned char ch)
{
	SBUF = ch;
	while(TI == 0);			// 等待发送完成
	TI = 0;
}

/**
  * @brief  putchar重定向（printf依赖此函数）
  */
char putchar(char ch)
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
	return ch;
}

/**
  * @brief  解析串口命令
  * @param  cmd 接收到的字符串
  * @retval  无
  */
void UART_ParseCmd(unsigned char *cmd)
{
	// 设置上限：TH：
	if(strstr(cmd,"TH:"))
	{
		unsigned char i = 3,temp = 0;
		while(cmd[i]>='0'&&cmd[i]<='9')
		{
			temp = temp*10+(cmd[i]-'0');
			i++;
		}
		g_Sys.temp_high = temp;
		AT24C02_WriteByte(EE_ADDR_TH,(unsigned char)g_Sys.temp_high);
		printf("TH set to %d\n", temp);
	}
	// 设置下限：TL：
	else if(strstr(cmd,"TL:"))
	{
		unsigned char i = 3,temp = 0;
		while(cmd[i]>='0'&&cmd[i]<='9')
		{
			temp = temp*10+(cmd[i]-'0');
			i++;
		}
		g_Sys.temp_low = temp;
		AT24C02_WriteByte(EE_ADDR_TH,(unsigned char)g_Sys.temp_low);
		printf("TL set to %d\n", temp);
	}	
	// 查询状态：OUERY 
	else if(strstr(cmd,"QUERY"))
	{
		printf("T:%.1f,H:%.1f,L:%.1f",
				g_Sys.temperature,g_Sys.temp_high,g_Sys.temp_low);//发送状态到电脑
		if(g_Sys.status == STATUS_NORMAL)	printf("S:NORMAL\n");
		else if(g_Sys.status == STATUS_LOW)	printf("S:LOW\n");
		else	printf("S:HIGH\n");
	}
	// 历史记录：HISTORY
	else if(strstr(cmd,"HISTORY"))
	{
		unsigned char pos = g_Sys.hist_front;
		printf("History:");
		while(pos != g_Sys.hist_tail)
		{
			int val = AT24C02_ReadInt(HISTORY_BASE + pos * 2);	//读取2字节温度×10
			printf("%.1f ", val / 10.0);						//还原真实温度
			pos = (pos + 1) % MAXSIZE;
		}
		printf("\n");
	}
	// 未识别命令
	else
		printf("Error:Unknow command\n");
}
