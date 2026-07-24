#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <REGX52.H>

/*************************** 引脚定义 **************************/
/* LCD1602 */
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

/*************************** 系统常量 **************************/
/* 红外遥控键码 */
#define IR_POWER					0x45
#define IR_MODE						0x46
#define IR_MUTE						0x47
#define IR_START_STOP				0x44
#define IR_PREVIOUS					0x40
#define IR_NEXT						0x43
#define IR_EQ						0x07
#define IR_VOL_MINUS				0x15
#define IR_VOL_ADD					0x09
#define IR_0						0x16
#define IR_RPT						0x19
#define IR_USD						0x0D
#define IR_1						0x0C
#define IR_2						0x18
#define IR_3						0x5E
#define IR_4						0x08
#define IR_5						0x1C
#define IR_6						0x5A
#define IR_7						0x42
#define IR_8						0x52
#define IR_9						0x4A

#endif
