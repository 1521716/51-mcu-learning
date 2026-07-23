#ifndef __ALARM_H__
#define __ALARM_H__

void Alarm_Update(unsigned char status);	// 更新报警状态（主循环调用）
void Alarm_TickHandler();					// 报警Tick处理（定时器ISR调用，每50ms）

#endif
