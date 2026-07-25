#include <REGX52.H>

unsigned int Num = 0;		// 计数器

/**
  * @brief  INT0初始化
  * @param  无
  * @retval  无
  */
void INT0_Init()
{
	IT0 = 1;		// 下降沿触发
	IE0 = 0;		
	EX0 = 1;		// 使能INT0开启
	EA = 1;			// 使能总开启
	PX0 = 1;		// 设置较高优先级，因为红外信号us级
}
