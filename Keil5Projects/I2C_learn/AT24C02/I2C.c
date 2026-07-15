#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


/**
  * @brief  I2C开始
  * @param  无
  * @retval  无
  */
void I2C_Start()
{
	I2C_SCL = 1;//因为不知道前面的程序将SCL置为什么，所以函数开始直接释放SCL，确保正确开始
	I2C_SDA = 1;//开始时SCL与SDA均为高位
	I2C_SDA = 0;//SDA下拉，产生下降沿，此时变成功开始了
	I2C_SCL = 0;//因为开始后后续操作一般SCL一般是低位，为了后续方便，再次拉低SCL
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval  无
  */
void I2C_Stop()
{
	I2C_SDA = 0;//确保SDA为低位
	I2C_SCL = 1;//释放SCL
	I2C_SDA = 1;//释放SDA，产生上升沿，成功停止
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte	要发送的字节
  * @retval  无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);//SCL为低位时，根据Byte来更改SDA
		I2C_SCL = 1;//更改完SDA，拉升SCL
		I2C_SCL = 0;//在拉低SCL，获取数据
	}
	I2C_SDA = 1;//一字节数据传输完成后，SDA要释放，否则可能影响后续程序
}

/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval  unsigned char接收到的一个字节数据
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte = 0x00,i;
	I2C_SDA = 1;//先释放SDA，确保可以正常由从机操作
	for(i = 0;i<8;i++)
	{
		I2C_SCL = 1;//SCL在高位时才能获取准确数据
		if(I2C_SDA){Byte|=(0x80>>i);}//根据数据给Byte赋值
		I2C_SCL = 0;//拉低SCL
	}

	return Byte;
}

/**
  * @brief  I2C发送应答
  *	@param  AckBit 应答位，0为应答，1为非应答
  * @retval  无
  */
void I2C_SendAck(bit AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
  * @brief  I2C接收应答
  * @param  无
  * @retval  bit	接收到的应答位，0为应答，1为非应答
  */
bit I2C_ReceiveAck()
{
	bit AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;

	return AckBit;
}