#include <REGX52.H>
#include "KeyMatrix.h"

/**
  * @brief  矩阵键盘扫描 — 返回按键编号 1~16, 无按键返回 0
  *         行列式: P1 口高 4 位 = 行, 低 4 位 = 列
  *         带软件消抖 (20ms)
  * @param  无
  * @retval 按键编号 (1~16) 或 0
  */
unsigned char KeyScan()
{
	unsigned char row, col, key = 0;

	/* 快速扫描: 逐行拉低, 读列值 */
	P1 = 0x0F;				// 行全 0, 列全 1
	if(P1 != 0x0F)			// 有键按下?
	{
		Delay20ms();		// 消抖
		if(P1 != 0x0F)		// 再次确认
		{
			/* 逐行扫描 */
			for(row = 0; row < 4; row++)
			{
				P1 = ~(0x10 << row);	// 拉低第 row 行, 其余行拉高, 列全 1
				col = P1 & 0x0F;		// 读列值
				if(col != 0x0F)
				{
					/* 确定列号 */
					if(col == 0x0E) col = 0;
					else if(col == 0x0D) col = 1;
					else if(col == 0x0B) col = 2;
					else if(col == 0x07) col = 3;

					key = row * 4 + col + 1;	// 计算键值 1~16

					/* 等待释放 */
					while((P1 & 0x0F) != 0x0F);
					Delay20ms();				// 释放消抖

					return key;
				}
			}
		}
	}
	return 0;
}
