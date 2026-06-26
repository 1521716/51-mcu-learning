#include <REGX52.H>
#include <INTRINS.H>

#define LED P0
#define KEY P3_1

#define PRESSED 0

#define PASSWORD 3
#define LED_COUNT 4
#define MAXTIME1 5000
#define MAXTIME2 3000

//延时函数
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

//选择LED位置
void SelectLED(unsigned char p)
{
	switch(p)
	{
		case 1:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 2:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 3:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 4:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
		
	}
}

//待机状态
void Status_Standby()
{
	unsigned char i = 1;
	while(KEY != PRESSED)
	{
		SelectLED(i++);
		LED = 0x40;
		Delay(1);
		LED = 0x00;
		if(i == 5) i = 1;
	}
	
}

//密码正确
void Status_PASS()
{
	SelectLED(1);
	LED = 0x73;
	Delay(1);
	LED = 0x00;
	SelectLED(2);
	LED = 0x77;
	Delay(1);
	LED = 0x00;
	SelectLED(3);
	LED = 0x6D;
	Delay(1);
	LED = 0x00;
	SelectLED(4);
	LED = 0x6D;
	Delay(1);
	LED = 0x00;
}
//密码错误
void Status_false()
{
	SelectLED(1);
	LED = 0x71;
	Delay(1);
	LED = 0x00;
	SelectLED(2);
	LED = 0x77;
	Delay(1);
	LED = 0x00;
	SelectLED(3);
	LED = 0x06;
	Delay(1);
	LED = 0x00;
	SelectLED(4);
	LED = 0x38;
	Delay(1);
	LED = 0x00;
}

void main()
{
	unsigned char key_count = 0;
	unsigned char status = 0;
	unsigned int timer = 0;
	while(1)
	{
		timer = 0;
		switch(status)
		{
			case 0:
			{
				Status_Standby();
				Delay(20);//消抖
				if(KEY == PRESSED)//有效按键
				{
					while(KEY == PRESSED);
					Delay(20);//按键松开并消抖
					
					key_count = 1;//次数加一
					status = 1;//变为输入状态
					
					while(KEY == PRESSED);
					Delay(20);//再次确认按键松开并消抖
				}
				else//无效按键，继续待机
					break;
				break;
			}
			case 1:
			{
				unsigned char i = 1;//激活输入状态已经按过一次按键
				while(timer<MAXTIME1)//在5秒内
				{
					//没有按按键，则动态扫描数码管，显示已按次数
					if(KEY != PRESSED)
					{
						
						SelectLED(i++);
						if(i > key_count) i = 1;
						LED = 0x40;
						Delay(1);
						LED = 0x00;
						timer++;
						
					}
					else
					{
						Delay(20);//消抖
						if(KEY == PRESSED&&timer<MAXTIME1)//有效按键
						{
							//等待松手并计时
							while(KEY == PRESSED&&timer<MAXTIME1)
							{
								
								SelectLED(i++);
								if(i > key_count) i = 1;
								LED = 0x40;
								Delay(1);
								LED = 0x00;
								timer++;
							}
							Delay(20);
							timer+=20;
							
							key_count++;
							if(key_count>LED_COUNT)
							{
								status = 3;
								break;
							}
							
						}
					}
				}
				
				//5秒结束，检测按键次数
				if(key_count == PASSWORD)
					status = 2;
				else
					status = 3;
				break;
			}
			case 2:
			{
				//重置时间迭代器（重新设置一个也可以）
				timer = 0;
				LED = 0x00;
				key_count = 0;
				P2 = 0x00;//LED常亮
				
				//没有按下按键则常亮
				while(KEY!=PRESSED)
				{
					Status_PASS();
				}
				Delay(20);//消抖
				if(KEY == PRESSED)//有效按键
				{
					while(KEY == PRESSED)
					{
						Status_PASS();
						Delay(1);
						timer+=5;
					}//等待松手并计时
					Delay(20);
					if(timer<MAXTIME2)//超过3秒则进入待机状态
						status = 2;
					else
						status = 0;
				}
				else//无效按键继续常亮
					status = 2;
				
				break;
			}
			case 3:
			{
				
				unsigned char blink;
                for(blink = 0; blink < 10; blink++)
                {
                    unsigned int t;
                    for(t = 0; t < 200; t++)
                    {
                        Status_false();  
						P2 = 0x00;
                    }
                    LED = 0x00; 
					P2 = 0xFF;
                    for(t = 0; t < 200; t++) { Delay(1); }
                }
                status = 0;
				key_count = 0;
				
				break;
			}
		}
	}
}