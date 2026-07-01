#include <REGX52.H>
#include <LCD1602.h>
#include <Delay.h>
#include <MatrixKey.h>

unsigned char KeyNumber;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"HelloWorld");
	while(1)
	{
		KeyNumber = MatrixKey();
		if(KeyNumber)
		{
			LCD_ShowNum(2,1,KeyNumber,2);
		}
	}
}
