#include <REGX52.H>
#include <INTRINS.H>

#define LED P2
#define KEY P3_1

#define PRESSED 0
#define LED_ON 0x00
#define LED_OFF 0xFF

#define PASSWORD 5
#define MAXTIME1 5000
#define MAXTIME2 3000


void Delay(unsigned int xms)	//@11.0592MHz
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

//待机状态
void LED_SlowBlink()
{
	unsigned int time = 500;
	LED = LED_ON;
	while(time--)
	{
		Delay(1);
		if(KEY == PRESSED)
		{
			Delay(20);
			if(KEY == PRESSED)
				return;
				
		}
	}
	time = 500;
	LED = LED_OFF;
	while(time--)
	{
		Delay(1);
		if(KEY == PRESSED)
		{
			Delay(20);
			if(KEY == PRESSED)
				return;
		}
	}
}

//密码错误
void LED_QuickBlink()
{
	LED = LED_ON;
	Delay(200);
	LED = LED_OFF;
	Delay(200);
}

void main()
{
	
	while(1)
	{
		//简易计时器
		unsigned int timer = 0;
		//按键次数
		unsigned char key_count = 0;
		
		//待机状态
		LED_SlowBlink();
		
		//如果按动按键
		if(KEY == PRESSED)
		{
			Delay(20);//消抖
			if(KEY == PRESSED)
			{
				while(KEY == PRESSED){};
				Delay(20);
				key_count++;//有效按动
				while(KEY == PRESSED){};
				Delay(20);

				//计时5秒
				while(timer<MAXTIME1)
				{
					if(KEY == PRESSED)
					{
						Delay(20);
						if(KEY == PRESSED&&timer<MAXTIME1)
						{
							while(KEY == PRESSED&&timer<MAXTIME1)
							{
								Delay(1);
								timer++;
							}
							if(timer>MAXTIME1)
								break;
							key_count++;//有效按动
							Delay(20);
							timer+=20;
						}
						else
						{
							Delay(1);
							timer++;
						}
						
					}
					Delay(1);
					timer++;
				}
				//判断密码是否正确
				if(key_count != PASSWORD)//密码错误 
				{
					unsigned char i = 0;
					for(i = 0;i<10;i++)
						LED_QuickBlink();
					continue;
				}
				else//密码正确
				{
					unsigned char i = 0;
					for(i = 0;i<3;i++)
						LED_QuickBlink();
					LED = LED_ON;
					while(1)
					{
						timer = 0;
						if(KEY == PRESSED)
						{
							Delay(20);
							if(KEY == PRESSED)
							{
								while(KEY == PRESSED)
								{
									timer++;
									Delay(1);
								}
								
								if(timer>=MAXTIME2)
								{
									LED = LED_OFF;
									Delay(200);
									break;
								}
									
							}
							
						}
					}
					
				}
				
			}
			
		}
		
		
	}
}