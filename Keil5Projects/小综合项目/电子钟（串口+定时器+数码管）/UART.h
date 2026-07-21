#ifndef __UART_H__
#define __UART_H__

extern volatile unsigned char Sec,Min,Hou;
extern unsigned char str_cmd[30];
extern unsigned char index;
extern bit flag;


void UART_Init();
void prase_cmd(unsigned char *cmd);
char putchar(char ch);
#endif
