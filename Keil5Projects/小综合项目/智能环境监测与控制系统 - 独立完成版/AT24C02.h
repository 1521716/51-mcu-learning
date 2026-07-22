#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);
void AT24C02_WriteInt(unsigned char addr, int val);		//2字节写入（高字节在前）
int  AT24C02_ReadInt(unsigned char addr);				//2字节读取

#endif
