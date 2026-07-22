#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <REGX52.H>

/*************************** 引脚定义 **************************/
/* I2C */
sbit SCL = P2^1;
sbit SDA = P2^0;

/* LCD1602 */
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

/* DS18B20 */
sbit DQ = P3^7;

/* 报警 */
sbit LED = P2^4;				//高低温报警LED（快慢闪）

/*************************** 系统常量 **************************/
/* EEPROM地址分配 */
#define EE_ADDR_TH		20		//上限阈值（1字节）
#define EE_ADDR_TL		21		//下限阈值（1字节）
#define HISTORY_BASE	40		//历史温度起始地址（每笔2字节）
#define HISTORY_SIZE	10		//历史温度最大记录数
#define MAXSIZE			11		//环形队列槽位数

/* 定时器 */
#define TICK_MS			50		//定时器周期
#define TICK_2S			40		//2秒 = 40个tick(50ms*40)

/* 默认阈值 */
#define DEFAULT_TH		35		//默认上限
#define DEFAULT_TL		5		//默认下限

/* 系统状态枚举 */
#define STATUS_NORMAL	0		//正常
#define STATUS_HIGH		1		//超上限
#define STATUS_LOW		2		//超下限

/************************ 系统状态结构体 *************************/
typedef struct{
	float temperature;			// 当前温度
	float temp_high;			// 上限阈值
	float temp_low;				// 下限阈值
	unsigned char status;		// 0=正常 1=超上限 2=超下限
	unsigned char hist_front;	// 环形队列头指针
	unsigned char hist_tail;	// 环形队列尾指针
} SystemState;

extern SystemState g_Sys;

#endif
