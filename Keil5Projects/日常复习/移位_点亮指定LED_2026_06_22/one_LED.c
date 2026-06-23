#include <REGX52.H>

#define LED P2

void main()
{
	LED = ~(0x01<<3);
	while(1){};
}