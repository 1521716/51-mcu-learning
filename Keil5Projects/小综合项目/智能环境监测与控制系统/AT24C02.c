#include "config.h"
#include "Delay.h"
#include "I2C.h"

#define AT24C02 0xA0

/**
  * @brief  AT24C02写一个字节
  * @param  WordAddress 字地址（0-255）
			Data 要写入的数据
  * @retval  无
  */
void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();		
	Delay(5);										// 等待EEPROM内部写入完成
}

/**
  * @brief  AT24C02读一个字节
  * @param  WordAddress 字地址（0-255）
  * @retval  读出的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();									// 重复起始信号，切换为读操作
	I2C_SendByte(AT24C02|0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();						// 读取数据
	I2C_SendAck(1);									// 发送NACK，通知从机结束
	I2C_Stop();
	return Data;
}

/**
  * @brief  写入2字节（高字节在前，低字节在后）
  * @param  addr 起始字地址；val 16位有符号整数
  * @retval  无
  */
void AT24C02_WriteInt(unsigned char addr, int val)
{
	AT24C02_WriteByte(addr,     (val >> 8) & 0xFF);	//高字节
	AT24C02_WriteByte(addr + 1,  val       & 0xFF);	//低字节
}

/**
  * @brief  读取2字节（高字节在前，低字节在后）
  * @param  addr 起始字地址
  * @retval  16位有符号整数
  */
int AT24C02_ReadInt(unsigned char addr)
{
	int val;
	val  = AT24C02_ReadByte(addr) << 8;				//高字节
	val |= AT24C02_ReadByte(addr + 1);				//低字节
	return val;
}
