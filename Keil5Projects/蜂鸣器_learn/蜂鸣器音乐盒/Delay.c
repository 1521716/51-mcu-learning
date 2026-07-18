#include "Delay.h"

/**
  * @brief  软件延时 N ms (不精确, 约 1ms @ 11.0592MHz / 12T)
  * @param  ms 延时毫秒数
  * @retval 无
  */
void Delay(unsigned int ms)
{
	unsigned char i, j;
	while(ms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

/**
  * @brief  20ms 消抖延时
  * @param  无
  * @retval 无
  */
void Delay20ms()
{
	unsigned char i, j;
	i = 20;
	j = 219;
	do
	{
		while (--j);
	} while (--i);
}
