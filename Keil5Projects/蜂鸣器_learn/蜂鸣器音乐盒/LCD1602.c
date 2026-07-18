#include <REGX52.H>

/* 引脚定义 — 普中科技开发板标准接线 */
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;
#define LCD_DataPort P0

/**
  * @brief  LCD1602 内部延时
  */
void LCD_Delay()
{
	unsigned char i, j;
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602 写命令
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
  * @brief  LCD1602 写数据
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
  * @brief  LCD1602 设置光标位置
  * @param  Line  行位置 1~2
  * @param  Column 列位置 1~16
  */
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if(Line == 1)
		LCD_WriteCommand(0x80 | (Column - 1));
	else if(Line == 2)
		LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
}

/**
  * @brief  LCD1602 初始化
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);		// 8-bit 数据接口, 2 行, 5×7 点阵
	LCD_WriteCommand(0x0C);		// 显示开, 光标关, 闪烁关
	LCD_WriteCommand(0x06);		// 写入后光标右移, 画面不动
	LCD_WriteCommand(0x01);		// 清屏
}

/**
  * @brief  在指定位置显示一个字符
  */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

/**
  * @brief  在指定位置显示字符串
  */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  返回 X 的 Y 次方
  */
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for(i = 0; i < Y; i++)
		Result *= X;
	return Result;
}

/**
  * @brief  在指定位置显示无符号数字
  * @param  Number 0~65535
  * @param  Length 显示位数 1~5
  */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(10, i - 1) % 10 + '0');
	}
}
