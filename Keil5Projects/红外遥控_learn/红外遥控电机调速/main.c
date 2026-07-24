#include <REGX52.H>
#include "Delay.h"
#include "key.h"
#include "NiXie.h"
#include "Motor.h"
#include "IR.h"


unsigned char Command,Speed;
unsigned char code smg_duan[] = {
	0x3F,					// 0: 00111111
    0x06,					// 1: 00000110
    0x5B, 					// 2: 01011011
    0x4F, 					// 3: 01001111
    0x66, 					// 4: 01100110
    0x6D, 					// 5: 01101101
    0x7D, 					// 6: 01111101
    0x07, 					// 7: 00000111
    0x7F, 					// 8: 01111111
    0x6F, 					// 9: 01101111
	0x40
};

void main()
{
	Motor_Init();
	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag())
		{
			Command = IR_GetCommand();
			if(Command == IR_0)	Speed = 0;
			if(Command == IR_1)	Speed = 1;			
			if(Command == IR_2)	Speed = 2;
			if(Command == IR_3)	Speed = 3;
			
			if(Speed == 0)	Motor_SetSpeed(0);
			if(Speed == 1)	Motor_SetSpeed(50);
			if(Speed == 2)	Motor_SetSpeed(75);
			if(Speed == 3)	Motor_SetSpeed(100);
		}
		NiXie(1,Speed);
	}
}

