#include "config.h"
#include "LCD1602.h"

#define LED_ON 0
#define LED_OFF 1

/******************* 报警状态机变量 *******************/
static bit alarm_active = 0;		// 报警是否激活
static unsigned char alarm_status;	// 当前警报类型（STATUS_NORMAL|HIGH|LOW）
static unsigned char alarm_tick;	// tick计数器（用于LED闪烁）
static unsigned char alarm_timeout;	// 警报持续tick数（2秒 = 40tick）
static unsigned char blink_speed;	// LED翻转间隔
static bit led_state;				// LED当前电平

/*
 * 报警参数说明（50ms per tick）：
 *   高温：LED 100ms周期(2 tick翻转)
 *   低温：LED 400ms周期(8 tick翻转)
 *   持续时间均为 2秒（40 tick）
 */
 
 /**
 * @brief  启动报警（主循环调用，立即返回不阻塞）
   * @param  status STATUS_HIGH|LOW
   * @retval  无
   */
void Alarm_Update(unsigned char status)
{
	if(status == STATUS_NORMAL)
	{
		// 正常状态：关闭所有警报
		alarm_active = 0;
		LED = LED_OFF;
		LCD_ShowString(1,13,"    ");
		return;
	}
	
	alarm_active = 1;
	alarm_status = status;
	alarm_tick = 0;
	alarm_timeout = TICK_2S;			// 持续2秒
	led_state = LED_OFF;
	
	// 关闭LED，准备开始闪烁
	LED = LED_OFF;
	
	if(status == STATUS_HIGH)
	{
		blink_speed = 2;				// 100ms(快闪)
		LCD_ShowString(1,13,"HIGH");
	}
	else
	{
		blink_speed = 8;				// 400ms(慢闪)
		LCD_ShowString(1,13,"LOW ");
	}
}

/**
  * @brief  报警Tick处理（定时器ISR每50ms调用一次）
			负责LED闪烁节奏
  * @param  无
  * @retval  无
  */
void Alarm_TickHandler()
{
	if(!alarm_active)	return;
	alarm_tick++;
	
	// LED翻转
	if(alarm_tick%blink_speed == 0)
	{
		led_state = !led_state;
		LED = led_state;
	}
	
	// 超时关闭
	if(alarm_tick >= alarm_timeout)
	{
		alarm_active = 0;
		LED = LED_OFF;
		LCD_ShowString(1,13,"    ");
	}
}
