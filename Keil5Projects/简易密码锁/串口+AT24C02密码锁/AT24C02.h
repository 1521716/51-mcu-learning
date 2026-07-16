#ifndef __AT24C02_H__
#define __AT24C02_H__

#define AT24C02 0xA0

void AT24C02_SendByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT24C02_ReceiveByte(unsigned char WordAddress);

#endif
