#include <REGX52.H>
#include "UART.h"

#define LED P2


void main()
{
	UART_Init();
	LED = 0;
	while(1)
	{
		
	}
}

void UART_ISR()	interrupt 4
{
	unsigned char temp = 0;
	if(RI == 1)
	{
		temp = SBUF;
		RI = 0;
		LED = ~temp;
		SBUF = temp;
		while(TI == 0);
		TI = 0;
	}
}
