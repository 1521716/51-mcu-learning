#ifndef __UART_H__
#define __UART_H__

extern unsigned char PASSWORD[4];
extern unsigned char index;
extern unsigned char Input[4];
extern unsigned char rx_buf[30];
extern bit rx_ready;

void UART_Init();
void parse_cmd(unsigned char *cmd);

#endif
