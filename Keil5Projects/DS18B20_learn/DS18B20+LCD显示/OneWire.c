#include <REGX52.H>


sbit OneWire_DQ = P3^7;

/**
  * @brief  OneWire初始化
  * @param  无
  * @retval  为0表示有从机响应，为1表示无从机响应
  */
unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 230;while (--i);//延迟500us
	OneWire_DQ = 1;
	i = 0;i = 34;while (--i);//延迟75us
	AckBit = OneWire_DQ;
	i = 230;while (--i);//延迟500us
	return AckBit;
}

/**
  * @brief  发送一个Bit数据
  * @param  Bit 要发送的数据
  * @retval  无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0;
	i = 4;while (--i);//延迟10us
	OneWire_DQ = Bit;
	i = 23;while (--i);//延迟50us
	OneWire_DQ = 1;
}

/**
  * @brief  接收一个Bit数据
  * @param  无
  * @retval  接收到的数据
  */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ = 0;
	i = 2;while (--i);//延迟5us
	OneWire_DQ = 1;
	i = 2;while (--i);//延迟5us
	Bit = OneWire_DQ;
	i = 23;while (--i);//延迟50us
	return Bit;
}

/**
  * @brief  发送一个字节的数据
  * @param  Byte 要发送的数据
  * @retval  无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  接收一个字节的数据
  * @param  无
  * @retval  接收到的数据
  */
unsigned char OneWire_ReceiveByte()
{
	unsigned char Byte = 0x00;
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}