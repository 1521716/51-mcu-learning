#include <REGX52.H>
#include <LCD1602.h>

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(2,1,12,3);
	LCD_ShowSignedNum(2,5,-99,2);
	while(1)
	{
		
	}
}
