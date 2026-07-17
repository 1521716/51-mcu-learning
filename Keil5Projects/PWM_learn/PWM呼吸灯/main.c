#include <REGX52.H>

#define TIME 100

sbit LED = P2^0;


void Delay(unsigned int ms)
{
	while(ms--);
}

void main()
{
	
	while(1)
	{
		unsigned char i = 0;
		for(i = 0;i<TIME;i++)//控制每个完整波形的占空比，即LED亮度
		{
			unsigned char j = 0;
			for(j = 0;j<20;j++)//让每个波形循环20次，使肉眼可见
			{
				LED = 0;
				Delay(i);
				LED = 1;
				Delay(TIME-i);
			}
		}
		for(i = 100;i>0;i--)
		{
			unsigned char j = 0;
			for(j = 0;j<20;j++)
			{
				LED = 0;
				Delay(i);
				LED = 1;
				Delay(TIME-i);
			}
		}
		
	}
}
