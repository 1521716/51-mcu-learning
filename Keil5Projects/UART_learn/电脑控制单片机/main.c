#include <REGX52.H>
#include <string.h>
#include <stdio.h>
#include "UART.h"
#include "parse_command.h"

unsigned char rx_buf[32];
unsigned char rx_index = 0;
bit cmd_ready = 0;

void main()
{
	UART_Init();
	while(1)
	{
		if(cmd_ready)
		{
			cmd_ready = 0;
			parse_command(rx_buf);
		}
	}
}

void UART_ISR()	interrupt 4
{
	if(RI == 1)
	{
		unsigned char ch = SBUF;
		RI = 0;
		
		if(ch == '\n'||ch == '\r')
		{
			rx_buf[rx_index] = '\0';
			rx_index = 0;
			cmd_ready = 1;
		}
		else
		{
			if(rx_index>=30)	return;//防止溢出
			rx_buf[rx_index++] = ch;
			
		}
	}
}
