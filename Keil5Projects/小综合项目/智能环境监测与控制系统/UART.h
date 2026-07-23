#ifndef __UART_H__
#define __UART_H__


void UART_Init();							// 初始化串口（9600bps）
void UART_SendByte(unsigned char ch);		// 发送一个字节(主循环调用)
void UART_ParseCmd(unsigned char *cmd);			// 解析串口命令

/* 环形缓冲区（中断与主循环共享） */
extern unsigned char idata rx_buf[20];
extern unsigned char rx_index;
extern bit rx_ready; 

#endif
