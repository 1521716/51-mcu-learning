#include <REGX52.H>

#define LED P2


void main()
{
	LED = ~((0x01<<1)|(0x01<<7));
	while(1){};
}
