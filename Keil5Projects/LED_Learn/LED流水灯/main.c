#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms>0)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
	
}


void main()
{
	unsigned char i;
	while(1) 
	{
		for(i = 0; i < 8; i++) 
		{
       P2 = ~(0x01 << i);  
       Delay1ms(500);
		}
	}
	
}