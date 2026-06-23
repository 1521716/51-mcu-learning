#include <REGX52.H>
#include <INTRINS.H>

#define LED P2
#define KEY P3_1

#define PRESSED 0
#define LONG_PRESS_TIME 2000
#define LED_COUNT 8 

//延时函数
void Delay1ms(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{
	//计数器:记录按键次数
	unsigned char count = 0;
	//计算按键时长
	unsigned int SecondNum = 0;
	//初始LED状态
	LED = 0xFF;
	
	while(1)
	{
		//清零秒数
		SecondNum = 0;
		//如果按下按键
		if(KEY == PRESSED)
		{
			//消抖
			Delay1ms(20);
			//消抖完成后如果仍为按下状态，说明为有效按
			if(KEY == PRESSED)
			{
				//记录按键时长（ms）
				while(KEY == PRESSED)
				{
					Delay1ms(1);
					SecondNum++;
				}
				Delay1ms(20);
				//如果时间超过两秒，则清零
				if(SecondNum>=LONG_PRESS_TIME)
				{
					count = 0;
					LED = 0xFF;
				}
				//时间没有超过两秒，则计数器+1
				else
				{
					LED = ~((0x01)<<count);
					count++;
					if(count>=LED_COUNT)
						count = 0;
				}
			}
		}
	}
}
