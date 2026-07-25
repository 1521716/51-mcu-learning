#ifndef __IR_H__
#define __IR_H__

/******************* 红外遥控键码 ***********************/
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

/******************** 标志位及辅助变量 **************************/
extern unsigned int IR_Time;		// 该信号时长
extern unsigned char IR_State;		// 当前状态 0=空闲状态 1=判断开始或重发 2=需要解码数据
extern unsigned char IR_Data[4];	// 四个unsigned char 类型数据，储存32位信息
extern unsigned char IR_pData;		// 辅助每一位的写入
extern bit IR_DataFlag;				// 数据是否接收标志位
extern bit IR_RepeatFlag;			// 重发标志位
extern unsigned char IR_Address;	// 地址码
extern unsigned char IR_Command;	// 命令码

void IR_Init();
unsigned char IR_GetDataFlag();
unsigned char IR_GetRepeatFlag();
unsigned char IR_GetAddress();
unsigned char IR_GetCommand();


#endif