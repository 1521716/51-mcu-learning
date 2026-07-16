#include <REGX52.H>
#include "I2C.h"
#include "AT24C02.h"
#include "Delay.h"

void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02);
	I2C_SendByte(WordAddress);
	I2C_SendByte(Data);
	I2C_Stop();
	Delay(5);
}

unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02);
	I2C_SendByte(WordAddress);
	I2C_Start();
	I2C_SendByte(AT24C02|0x01);
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
	
}
