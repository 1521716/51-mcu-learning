#include <REGX52.H>

sbit SCL = P2^1;
sbit SDA = P2^0;

//开始
void I2C_Start()
{
	SCL = 1;//因为不知道前面的操作使其为低电平还是高电平，所以先拉高
	SDA = 1;
	SDA = 0;//SCL高电平时拉低SDA，表示开始
	SCL = 0;//为了后续操作方便，在此拉低SCL
}
//终止
void I2C_Stop()
{
	SDA = 0;//前面操作不知道将SDA置为什么电平，先将SDA拉低
	SCL = 1;//拉高SCL
	SDA = 1;//在SCL高电平时拉高SDA，结束
	
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
//接收一个字节
unsigned char I2C_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	SDA = 1;
	for(i = 0;i<<8;i++)
	{
		SCL = 1;
		if(SDA == 1)	{Byte|=(0x80>>i);}
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
	SDA = 1;
	SCL = 1;
	AckBit = SDA;
	SCL = 0;
	return AckBit;
}
