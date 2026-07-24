/*
实现红外遥控基本功能：
	显示当前遥控地址码、当前按下按键键码、设置一简易计数器验证按键可用
*/

#include "config.h"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "INT0.h"
#include "IR.h"

/****************** 全局变量 **********************/
unsigned int Time;
unsigned char Address;
unsigned char Command; 

/****************** 函数声明 **********************/
static void Sys_Init();
static void Task();

/****************** 主循环 ***********************/
void main()
{
	Sys_Init();
	
	while(1)
	{
		Task();
	}
}

/****************** 函数定义 ***********************/
static void Sys_Init()
{
	// 外设初始化
	LCD_Init();
	IR_Init();
	
	// LCD显示
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	LCD_ShowString(2,1,"00    00   000");
	
}

static void Task()
{
	if(IR_GetDataFlag() || IR_GetRepeatFlag())
	{
		Address = IR_GetAddress();
		Command = IR_GetCommand();
		
		
		LCD_ShowHexNum(2,1,Address,2);
		LCD_ShowHexNum(2,7,Command,2);
		
		if(Command == IR_VOL_MINUS)
			Num--;
		if(Command == IR_VOL_ADD)
			Num++;
		
		LCD_ShowNum(2,12,Num,3);
	}
}