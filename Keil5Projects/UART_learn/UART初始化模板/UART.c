#include <REGX52.H>
#include <stdio.h>
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
	/*
	ET1 = 1;
	ES = 1;
	EA = 1;
	*/
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
/*串口回显函数
void UART_ISR()	interrupt 4
{
	unsigned char temp = 0;
	if(RI == 1)
	{
		temp = SBUF;
		RI = 0;
		SBUF = temp;
		while(TI == 0);
		TI = 0;
	}
}*/