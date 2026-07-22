#include <REGX52.H>
#include "Delay.h"
#include "I2C.h"

#define AT24C02 0xA0

//写一个字节
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
	Delay(5);
}
//读一个字节
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02|0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}

//写入2字节（高字节在前，低字节在后）
void AT24C02_WriteInt(unsigned char addr, int val)
{
	AT24C02_WriteByte(addr,     (val >> 8) & 0xFF);	//高字节
	AT24C02_WriteByte(addr + 1,  val       & 0xFF);	//低字节
}

//读取2字节（高字节在前，低字节在后）
int AT24C02_ReadInt(unsigned char addr)
{
	int val;
	val  = AT24C02_ReadByte(addr) << 8;				//高字节
	val |= AT24C02_ReadByte(addr + 1);					//低字节
	return val;
}
