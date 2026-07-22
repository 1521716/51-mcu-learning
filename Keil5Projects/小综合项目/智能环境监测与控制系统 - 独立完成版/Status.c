#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

#define LED P2_3

#define LED_ON 0
#define LED_OFF 1

static bit blink_active = 0;
static unsigned char blink_tick;    // tick 累加
static unsigned char blink_speed;   // 翻转间隔（tick数）
static unsigned char blink_timeout; // 总时长（tick数）

/*
   * 定时器 50ms 一个 tick
   * 高温快闪: 2个tick(100ms)翻转, 持续40个tick(2秒)
   * 低温慢闪: 8个tick(400ms)翻转, 持续40个tick(2秒)
   */

void Status_High()
{
	
	LCD_ShowString(1,13,"HIGH");
	blink_active = 1;
	blink_tick = 0;
	blink_speed = 2;
	blink_timeout = 40;
}

void Status_Low()
{
	LCD_ShowString(1,13,"LOW ");
	blink_active = 1;
	blink_tick = 0;
	blink_speed = 8;
	blink_timeout = 40;
	
}

void Status_BlinkHandler()
{
	if(!blink_active)	return;
	
	blink_tick++;
	
	if(blink_tick%blink_speed == 0)
		LED = ~LED;
	if(blink_tick>=blink_timeout)
	{
		blink_active = 0;
		LED = LED_OFF;
		LCD_ShowString(1,13,"    ");
	}
}

