#ifndef __DS18B20_H__
#define __DS18B20_H__

bit OneWire_Init();
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit();
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte();
void DS18B20_CONVERT();
float DS18B20_ReadT();

#endif
