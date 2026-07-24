#include "config.h"

/**
  * @brief  Timer0初始化：模式1（16位），  晶振11.0592MHz,机器周期12T
  * @param  无
  * @retval  无
  */
void Timer0_Init()
{
	TMOD &= 0xF0;				// 清零Timer0配置位
	TMOD |= 0x01;				// Timer0:模式1（16位）
	TR0 = 0;					// 按需启动Timer0
	TL0 = 0;					// 重装值低字节（50ms）
	TH0 = 0;					// 重装值高字节（50ms）
}

/**
  * @brief  设置计数器重装值
  * @param  Value 设置的重装值
  * @retval  无
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value/256;
	TL0 = Value%256;
}

/**
  * @brief  获取从开始计时到现在的us数
  * @param  无
  * @retval  获取到的us数
  */
unsigned int Timer0_GetCounter()
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  设置计时器0是否开启
  * @param  Flag 0=关闭，1=开启
  * @retval  无
  */
void Timer0_Run(bit Flag)
{
	TR0 = Flag;
}



