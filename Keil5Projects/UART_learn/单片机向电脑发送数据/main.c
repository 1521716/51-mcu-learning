#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
void main()
{
	unsigned char num = 0;
	UART_Init();
	while(1)
	{
		putchar(num);
		Delay(1000);
		num++;
	}
}

