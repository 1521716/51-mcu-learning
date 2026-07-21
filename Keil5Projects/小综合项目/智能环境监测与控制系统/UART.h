#ifndef __UART_H__
#define __UART_H__

extern volatile float T,TH,TL;
extern unsigned char idata rx_buf[30],index,s;
extern bit rx_ready;
extern unsigned char code Status[3][30];


void UART_Init();
void parse_cmd(unsigned char *cmd);

#endif
