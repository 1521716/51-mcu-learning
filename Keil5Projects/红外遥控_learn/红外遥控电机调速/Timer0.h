#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init();			// 初始化Timer0
void Timer0_SetCounter(unsigned int Value);
unsigned int Timer0_GetCounter();
void Timer0_Run(bit Flag);

#endif
