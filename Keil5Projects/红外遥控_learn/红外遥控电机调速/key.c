#include <REGX52.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char KeyNumber = 0;
	
	if(P3_1 == 0){Delay(20);if(P3_1 == 0){while(P3_1 == 0);Delay(20);KeyNumber = 1;}}
	return KeyNumber;
}
