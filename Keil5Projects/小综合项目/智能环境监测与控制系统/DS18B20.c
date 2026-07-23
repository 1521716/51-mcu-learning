#include "config.h"

#define SKIP_ROM 			0xCC	// 跳过ROM匹配
#define CONVERT_T			0x44	// 启动温度转换
#define READ_SCRATCHPAD 	0xBE	// 读取暂存器

/********************************* OneWire 底层 *************************/

/**
  * @brief  OneWire总线初始化（复位脉冲+检测存在脉冲）
  * @param  无
  * @retval  0=器件应答，1=无器件
  */
bit OneWire_Init()
{
	unsigned char i;
	bit Ack;
	DQ = 1;						// 总线空闲
	DQ = 0;						// 拉低总线
	i = 230;while (--i);		// 延时约500us
	DQ = 1;						// 释放总线	
	i = 34;while (--i);			// 延时约75us
	Ack = DQ;					// 采样存在脉冲
	i = 230;while (--i);		// 延时约500us
	DQ = 1;						// 总线恢复空闲	
	return Ack;
}

/**
  * @brief  OneWire发送一个比特位
  * @param  Bit 要发送的比特位
  * @retval  无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	DQ = 1;						// 总线空闲
	DQ = 0;						// 拉低总线
	i = 4;while (--i);			// 延时约10us（拉低）
	DQ = Bit;					// 输出数据位
	i = 22;while (--i);			// 延时约50us（保持）
	DQ = 1;						// 释放总线
}

/**
  * @brief  OneWire接收一个比特位
  * @param  无
  * @retval  接收到的比特位
  */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit = 0;
	DQ = 1;
	DQ = 0;
	i = 2;while (--i);			// 延时约5us
	DQ = 1;						// 释放总线
	i = 2;while (--i);			// 延时约5us
	Bit = DQ;					// 采样数据线
	i = 22;while (--i);			// 延时约50us
	DQ = 1;
	return Bit;
}

/**
  * @brief  OneWire发送一个字节（低位在前）
  * @param  Byte 要发送的字节
  * @retval  无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  OneWire 接收一个字节（低位在前）
  * @param  无
  * @retval  Byte 接收到的字节
  */
unsigned char OneWire_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	for(i = 0;i<8;i++)
	{
		if(OneWire_ReceiveBit())	{Byte|=(0x01<<i);}
	}
	return Byte;
}

/********************************* DS18B20 应用层 **********************/

/**
  * @brief  启动DS18B20温度转换
  * @param  无
  * @retval  无
  */
void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(CONVERT_T);
}

/**
  * @brief  读取DS18B20温度值
  * @param  无
  * @retval  T 温度值（摄氏度，浮点数）
  * @note   调用前确保转换已完成（>=750ms）
  */
float DS18B20_ReadT()
{
	float T;
	int Temp;
	unsigned char TLSB,TMSB;
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();			// 低字节
	TMSB = OneWire_ReceiveByte();			// 高字节（含符号位）
	
	Temp = (TMSB<<8)|TLSB;					// 拼接16位补码
	T = Temp/16.0;							// DS18B20默认12位分辨率
	
	return T;
}
