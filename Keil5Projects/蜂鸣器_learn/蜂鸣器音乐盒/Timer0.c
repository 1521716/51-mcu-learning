#include <REGX52.H>

/**
  * @brief  Timer0 初始化 — 用于蜂鸣器频率生成
  *         模式 1 (16-bit), 具体重装值由 PlayNote() 动态设置
  * @param  无
  * @retval 无
  */
void Timer0_Init()
{
	TMOD &= 0xF0;		// 清零 Timer0 模式位
	TMOD |= 0x01;		// Timer0: Mode 1 (16-bit)
	TL0 = 0x00;
	TH0 = 0x00;
	TF0 = 0;
	TR0 = 1;			// 启动 Timer0
	ET0 = 1;			// 开 Timer0 中断
	PT0 = 1;			// 高优先级 (音频不能断)
}

/**
  * @brief  Timer1 初始化 — 1ms 时基, 用于音符时值计时
  *         模式 1 (16-bit), 11.0592MHz
  *         计数 = 1000μs / (12/11.0592)μs ≈ 922
  *         重装值 = 65536 - 922 = 64614 = 0xFC66
  * @param  无
  * @retval 无
  */
void Timer1_Init()
{
	TMOD &= 0x0F;		// 清零 Timer1 模式位
	TMOD |= 0x10;		// Timer1: Mode 1 (16-bit)
	TL1 = 0x66;
	TH1 = 0xFC;
	TF1 = 0;
	TR1 = 1;			// 启动 Timer1
	ET1 = 1;			// 开 Timer1 中断
	PT1 = 0;			// 低优先级
	EA  = 1;			// 开总中断
}
