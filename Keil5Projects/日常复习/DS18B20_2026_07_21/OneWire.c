#include <REGX52.H>

sbit DQ = P3^7;

//初始化
unsigned char OneWire_Init()
{
	unsigned char i,AckBit;
	DQ = 1;
	DQ = 0;
	i = 230;while (--i);//延迟500us
	DQ = 1;
	i = 34;while (--i);//延迟75us
	AckBit = DQ;
	i = 230;while (--i);//延迟500us
	return AckBit;
}
//发送一个比特位
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	DQ = 0;
	i = 4;while (--i);//延迟10us
	DQ = Bit;
	i = 23;while (--i);//延迟50us	
	DQ = 1;
}
//接收一个比特位
unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit;
	DQ = 0;
	i = 2;while (--i);//延迟5us
	DQ = 1;//释放DQ，让从机控制以发送数据
	i = 2;while (--i);//延迟5us
	Bit = DQ;
	i = 23;while (--i);//延迟50us	
	return Bit;
}
//发送一个字节
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

//接受一个字节
unsigned char OneWire_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	for(i = 0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}

