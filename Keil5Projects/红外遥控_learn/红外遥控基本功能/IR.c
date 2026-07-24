#include "config.h"
#include "INT0.h"
#include "Timer0.h"

unsigned int IR_Time;		// 该信号时长
unsigned char IR_State;		// 当前状态 0=空闲状态 1=判断开始或重发 2=需要解码数据
unsigned char IR_Data[4];	// 四个unsigned char 类型数据，储存32位信息
unsigned char IR_pData;		// 辅助每一位的写入
bit IR_DataFlag;			// 数据是否接收标志位
bit IR_RepeatFlag;			// 重发标志位
unsigned char IR_Address;	// 地址码
unsigned char IR_Command;	// 命令码

/**
  * @brief  IR红外遥控初始化
  * @param  无
  * @retval  无
  */
void IR_Init()
{
	Timer0_Init();
	INT0_Init();
}

/**
  * @brief  返回是否接收到数据标志（面向对象思想）
  * @param  无
  * @retval  0=未接受到数据，1=接收到了数据
  */
unsigned char IR_GetDataFlag()
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief  返回是否重发标志（面向对象思想）
  * @param  无
  * @retval  0=不重发，1=重发
  */
unsigned char IR_GetRepeatFlag()
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief  获取地址码
  * @param  无
  * @retval  地址码
  */
unsigned char IR_GetAddress()
{
	return IR_Address;
}

/**
  * @brief  获取命令码
  * @param  无
  * @retval  命令码
  */
unsigned char IR_GetCommand()
{
	return IR_Command;
}

/**
  * @brief  INT0中断处理函数，用于接收数据
  * @param  无
  * @retval  无
  */
void INT0_ISR()	interrupt 0
{
	if(IR_State == 0)
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		
		if(IR_Time>=12442-500 && IR_Time<=12442+500)		// 开始
		{
			IR_State = 2;
		}
		else if(IR_Time>=10369-500 && IR_Time<=10369+500)	// 重发
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}
		else
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		
		if(IR_Time>=1032-500 && IR_Time<=1032+500)			// 0
		{
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));
			IR_pData++;
		}
		else if(IR_Time>=2074-500 && IR_Time<=2074+500)		// 1
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));
			IR_pData++;
		}
		else 												// 错误
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData>=32)
		{
			IR_pData = 0;
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))		// 成功收到正确数据
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);
			IR_State = 0;
		}
	}
}

