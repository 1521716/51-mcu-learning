#include <REGX52.H>
#include "I2C.h"
#include "Delay5us.h"

void I2C_Start()
{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;
}

void I2C_Stop()
{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
	Delay5us();
}

bit I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		SDA = Byte&(0x80>>i);
		SCL = 1;
		Delay5us();
		SCL = 0;
	}
	SDA = 1;//释放SDA，使从机可以传输应答位
	SCL = 1;//获取应答位
	Delay5us();
	if(SDA){
		SCL = 0;
		return 0;
	}
	SCL = 0;
	return 1;
}

unsigned char I2C_ReceiveByte()
{
	unsigned char i,Data = 0x00;
	SDA = 1;
	for(i = 0;i<8;i++)
	{
		Data<<=1;
		SCL = 1;
		Delay5us();
		if(SDA) Data |= 0x01;
		SCL = 0;
	}
	return Data;
}

void I2C_SendAck(bit AckByte)
{
	SDA = AckByte;
	SCL = 1;
	Delay5us();
	SCL = 0;
}

