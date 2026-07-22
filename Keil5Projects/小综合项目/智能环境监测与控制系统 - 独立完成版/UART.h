#ifndef __UART_H__
#define __UART_H__

#define MAXSIZE 11		//环形队列槽位数（最多存10个历史温度）
#define HISTORY_BASE 40	//历史温度在EEPROM的起始地址（槽0→40,41; 槽1→42,43; ...）


extern volatile float T,TH,TL;
extern unsigned char idata rx_buf[20],index,S;
extern bit rx_ready;
extern unsigned char front,tail;


void UART_Init();
void parse_cmd(unsigned char *cmd);

#endif
