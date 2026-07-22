#include <REGX52.H>

#define SKIP_ROM 0xCC
#define CONVERT 0x44
#define READ_SCRATCHPAD 0xBE

sbit DQ = P3^7;

//OneWire
//开始
bit OneWire_Init()
{
	unsigned char i;
	bit Ack;
	DQ = 1;
	DQ = 0;
	i = 230;while (--i);//500us
	DQ = 1;
	i = 34;while (--i);//75us
	Ack = DQ;
	i = 230;while (--i);//500us
	DQ = 1;	
	return Ack;
}
//发送一个比特位
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	DQ = 1;
	DQ = 0;
	i = 4;while (--i);//10us
	DQ = Bit;
	i = 22;while (--i);//50us
	DQ = 1;
}
//接收一个比特位
unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit = 0;
	DQ = 1;
	DQ = 0;
	i = 2;while (--i);//5us
	DQ = 1;
	i = 2;while (--i);//5us
	Bit = DQ;
	i = 22;while (--i);//50us
	DQ = 1;
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
//接收一个字节
unsigned char OneWire_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	for(i = 0;i<8;i++)
	{
		if(OneWire_ReceiveBit())	{Byte|=(0x01<<i);}
	}
	return Byte;
}
//DS18B20
//温度转换
void DS18B20_CONVERT()
{
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(CONVERT);
}

//读取温度
float DS18B20_ReadT()
{
	float T;
	int Temp;
	unsigned char TLSB,TMSB;
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	
	Temp = (TMSB<<8)|TLSB;
	T = Temp/16.0;
	
	return T;
}
