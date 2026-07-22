#include <REGX52.H>

sbit SCL = P2^1;
sbit SDA = P2^0;

//开始
void I2C_Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}
//停止
void I2C_Stop()
{
	SDA = 0;
	SCL = 1;
	SDA = 1;
}
//发送一个字节
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		SDA = Byte&(0x80>>i);
		SCL = 1;
		SCL = 0;
	}
	SDA = 1;
}
//接受一个字节
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte = 0x00,i;
	for(i = 0;i<8;i++)
	{
		SCL = 1;
		if(SDA)	{Byte|=(0x80>>i);}
		SCL = 0;
	}
	return Byte;
}
//发送应答
void I2C_SendAck(bit AckBit)
{
	SDA = AckBit;
	SCL = 1;
	SCL = 0;
}
//接收应答
bit I2C_ReceiveAck()
{
	bit AckBit;
	SCL = 1;
	AckBit = SDA;
	SCL = 0;
	return AckBit;
}
