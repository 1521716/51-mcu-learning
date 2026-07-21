#include <REGX52.H>
#include "NiXie.h"
#include "Delay.h"



void NiXie(unsigned char Location,unsigned char Number)
{
	LED = 0x00;
	switch(Location)
	{
		case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
		case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
	}
	LED = smg_duan[Number];
}