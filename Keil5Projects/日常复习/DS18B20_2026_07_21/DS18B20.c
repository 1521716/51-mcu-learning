#include <REGX52.H>
#include "OneWire.h"

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

void DS18B20_CONVERT()
{
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(CONVERT_T);
}

float DS18B20_ReadT()
{
	float T;
	unsigned char TLSB,TMSB;
	int Temp;
	OneWire_Init();
	OneWire_SendByte(SKIP_ROM);
	OneWire_SendByte(READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	Temp = (TMSB<<8)|TLSB;
	T = Temp/16.0;
	
	return T;
}

