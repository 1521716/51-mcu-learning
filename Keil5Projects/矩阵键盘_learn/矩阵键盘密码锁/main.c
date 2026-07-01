#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

#define Password 1716
#define KEY_CONFIRM 11
#define KEY_CLEAR   12
#define PWD_MAXLEN  4

unsigned char KeyNumber,Count;
unsigned int Inputword;


void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Inputword:");
	
	while(1)
	{
		KeyNumber = MatrixKey();
		if(KeyNumber)
		{
			if(KeyNumber<=10)							//按下s1 - s10，输入密码
			{
				if(Count<PWD_MAXLEN)					//如果输入次数小于4
				{
					Inputword*=10;						//密码左移一位
					Inputword+=KeyNumber%10;			//获取一位密码
					Count++;							//计次加一
				}
				LCD_ShowString(1,1,"Inputword:      ");	//将上次OK或ERR残留刷新
				LCD_ShowNum(2,1,Inputword,4);			//更新显示
			}
			
			if(KeyNumber == KEY_CONFIRM)				//如果s11按键按下，确认
			{
				if(Inputword == Password)				//如果密码正确，显示OK
				{	
					LCD_ShowString(1,14,"OK");	
					Inputword = 0;						//输入密码清零
					Count = 0;							//计次清零
					LCD_ShowNum(2,1,Inputword,4);		//更新显示
				}
				else									//否则显示ERROR
				{
					LCD_ShowString(1,14,"ERR");
					Inputword = 0;						//输入密码清零
					Count = 0;							//计次清零
					LCD_ShowNum(2,1,Inputword,4);		//更新显示
				}
			}
				if(KeyNumber == KEY_CLEAR)				//如果s12按键按下，清空
				{	
				Inputword = 0;							//输入密码清零
				Count = 0;								//计次清零
				LCD_ShowNum(2,1,Inputword,4);			//更新显示
			}
			
		}
		
		
	}
}