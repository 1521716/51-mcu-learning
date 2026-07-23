#include "config.h"
#include "Alarm.h"

bit flag_Updatedata = 0;		// 2秒到：刷新温度
bit flag_Updatestatus = 0;		// 2秒到：刷新状态
bit flag_Save = 0;				// 2秒到：保存历史温度

/**
  * @brief  Timer0初始化：模式1（16位），50ms中断一次
  晶振11.0592MHz,机器周期12T
  * @param  无
  * @retval  无
  */
void Timer0_Init()
{
	TMOD &= 0xF0;				// 清零Timer0配置位
	TMOD |= 0x01;				// Timer0:模式1（16位）
	TR0 = 1;					// 启动Timer0
	TL0 = (65536-50000)%256;	// 重装值低字节（50ms）
	TH0 = (65536-50000)/256;	// 重装值高字节（50ms）
	
	EA = 1;						// 开启总中断	
	ET0 = 1;					// 使能Timer0中断
}

/**
  * @brief  Timer0中断服务函数（每50ms触发一次）
  * @param  无
  * @retval  无
  */
void Timer0_ISR()	interrupt 1
{
	static unsigned char tick_count = 0;		// 2秒计时计数器
	
	// 重装初值
	TL0 = (65536 - 50000) % 256;
	TH0 = (65536 / 50000) / 256;
	
	// 报警LED（每tick更新一次）
	Alarm_TickHandler();
	
	// 2秒事件
	tick_count++;
	if(tick_count>=TICK_2S)
	{
		tick_count = 0;
		flag_Updatedata = 1;
		flag_Updatestatus = 1;
		flag_Save = 1;
	}
}


