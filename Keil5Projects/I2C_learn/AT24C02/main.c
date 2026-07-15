#include <REGX52.H>
#include "Delay.h"
#include "I2C.h"
#include "Key.h"
#include "LCD1602.h"
#include "AT24C02.h"

unsigned int Num;
unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		else if(KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		else if(KeyNum == 3)
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);
			AT24C02_WriteByte(1,Num/256);
			Delay(5);
			LCD_ShowString(2,1,"Write OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
		else if(KeyNum == 4)
		{
			Num = AT24C02_ReadByte(1);
			Num = Num<<8;
			Num|= AT24C02_ReadByte(0);
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(2,1,"Read  OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
	}
}
