#include <REGX52.H>
#include "I2C.h"
#include "AT24C02.h"



//写下一个字节数据
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
	
}
//读取一个字节数据
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