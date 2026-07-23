#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init();			// 初始化Timer0(50ms中断)

/* 定时器驱动的事件标志 */
extern bit flag_Updatedata;		// 2秒到：刷新温度
extern bit flag_Updatestatus;	// 2秒到：刷新状态
extern bit flag_Save;			// 2秒到：保存历史温度

#endif
