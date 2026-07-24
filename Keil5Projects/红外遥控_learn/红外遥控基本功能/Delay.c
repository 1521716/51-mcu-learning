#include <INTRINS.H>

/**
  * @brief  毫秒级延迟函数
  * @param  xms 延时的毫秒数
  * @retval  无 
  * @note   晶振频率 11.0592MHz
  */
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
