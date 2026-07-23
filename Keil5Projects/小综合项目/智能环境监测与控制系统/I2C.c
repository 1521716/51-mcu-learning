#include "config.h"

/**
  * @brief  I2C起始信号：SCL高电平时SDA由高到低
  * @param  无
  * @retval  无
  */
void I2C_Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

/**
  * @brief  I2C停止信号：SCL高电平时SDA由低到高
  * @param  无
  * @retval  无
  */
void I2C_Stop()
{
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

/**
  * @brief  I2C发送一个字节（高位在前）
  * @param  Byte 要发送的字节
  * @retval  无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
		SDA = Byte&(0x80>>i);	// 从最高位开始发送
		SCL = 1;				// 拉高时钟，数据被从机采样
		SCL = 0;
	}
	SDA = 1;					// 释放SDA，准备接收应答
}

/**
  * @brief  I2C接收一个字节（高位在前）
  * @param  无
  * @retval  接收到的字节
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte = 0x00,i;
	for(i = 0;i<8;i++)
	{
		SCL = 1;				// 拉高时钟，从机输出数据
		if(SDA)	{Byte|=(0x80>>i);}
		SCL = 0;
	}
	return Byte;
}

/**
  * @brief  I2C发送应答位
  * @param  AckBit 0=应答（ACK），1=非应答(NACK)
  * @retval  
  */
void I2C_SendAck(bit AckBit)
{
	SDA = AckBit;				// 主机输出应答电平
	SCL = 1;					// 产生应答时钟脉冲
	SCL = 0;
}

/**
  * @brief  I2C接收从机应答
  * @param  无
  * @retval 0=从机应答（ACK），1=从机未应答（NACK） 
  */
bit I2C_ReceiveAck()
{
	bit AckBit;
	SCL = 1;
	AckBit = SDA;				// 采样SDA线上的应答位
	SCL = 0;
	return AckBit;
}
