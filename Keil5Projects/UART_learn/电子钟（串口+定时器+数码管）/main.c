#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "Timer0.h"

#define LED P0

volatile unsigned char Sec = 0,Min = 0,Hou = 0;
unsigned char str_cmd[30];
unsigned char index = 0;
bit flag = 0;

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



void NiXie(unsigned char Location,unsigned char Number)
{
	LED = 0x00;
	switch(Location)
	{
		case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
		case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
	}
	LED = smg_duan[Number];
}

void main()
{
	Timer0_Init();
	UART_Init();
	while(1)
	{
		if(flag)
		{
			flag = 0;
			prase_cmd(str_cmd);
		}
		NiXie(1,Hou/10);Delay(1);NiXie(2,Hou%10);Delay(1);NiXie(4,Min/10);Delay(1);
		NiXie(5,Min%10);Delay(1);NiXie(7,Sec/10);Delay(1);NiXie(8,Sec%10);Delay(1);
		NiXie(3,10);Delay(1);NiXie(6,10);Delay(1);
	}
}
