#include <REGX52.H>
#include "I2C.h"

void I2C_Start()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void I2C_Stop()
{
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

void I2C_SendByte(unsigned char Data)
{
	unsigned char i = 0;
	SDA = 1;
	for(i = 0;i<8;i++)
	{
		SDA = Data&(0x80>>i);
		SCL = 1;
		SCL = 0;
	}
	SDA = 1;
}

unsigned char I2C_ReceiveByte()
{
	unsigned char Data = 0x00,i = 0;
	SDA = 1;
	for(i = 0;i<8;i++)
	{
		
		SCL = 1;
		if(SDA)	Data|=(0x80>>i);
		SCL = 0;
	}
	SDA = 1;
	return Data;
}

void I2C_SendAck(bit Ack)
{
	SDA = Ack;
	SCL = 1;
	SCL = 0;
}

bit I2C_ReceiveAck()
{
	bit Ack;
	SDA = 1;
	SCL = 1;
	Ack = SDA;
	SCL = 0;
	
	return Ack;
}
