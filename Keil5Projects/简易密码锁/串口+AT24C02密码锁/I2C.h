#ifndef __I2C_H__
#define __I2C_H__

sbit SCL = P2^1;
sbit SDA = P2^0;

void I2C_Start();
void I2C_Stop();
void I2C_SendByte(unsigned char Data);
unsigned char I2C_ReceiveByte();
void I2C_SendAck(bit Ack);
bit I2C_ReceiveAck();

#endif
