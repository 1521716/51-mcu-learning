/******************************************************************************
 * 智能环境监测与控制系统
 *
 * 功能：
 *   1. DS18B20每2秒采集温度，LCD1602实时显示
 *   2. 温度阈值管理（默认上限35.0°C / 下限5.0°C），EEPROM掉电保存
 *   3. 超限报警：LED闪烁(快慢频闪区分超上下限)
 *   4. 串口远程监控：定时上报 + 接收命令（TH:/TL:/QUERY/HISTORY）
 *   5. 温度历史记录（环形队列，EEPROM存储10笔）
 *
 * 硬件平台：STC89C52RC @ 11.0592MHz
 * 编译器：  Keil C51
 ******************************************************************************/

#include "config.h"
#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "Delay.h"
#include "DS18B20.h"
#include "Timer0.h"
#include "UART.h"
#include "AT24C02.h"
#include "Alarm.h"

/************************* 全局系统状态 ********************************/
SystemState g_Sys = {
	0.0,				// temperature	
	DEFAULT_TH,			// temp_high
	DEFAULT_TL,			// temp_low
	STATUS_NORMAL,		// status
	0,0					// hist_front,hist_tail
};

unsigned char echo_ch;	// 待回显字符
bit flag_echo = 0;		// 回显标志
int val = 0;			// 辅助变量，储存温度

/************************** 函数声明 **********************/
static void System_Init();					// 系统初始化
static void Task_UpdateData();				// 温度更新+LCD显示+串口上报
static void Task_UpdateStatus();			// 阈值判断+报警
static void Task_SaveHistory();				// 保存温度历史到EEPROM
static void Task_EchoHandler();				// 串口回显
static void Task_CmdHandler();				// 串口命令解析	

/**************************** 主函数 *********************************/
void main()
{
	System_Init();
	
	while(1)
	{
		Task_UpdateData();
		Task_UpdateStatus();
		Task_SaveHistory();
		Task_EchoHandler();
		Task_CmdHandler();
	}
}

/*************************** 函数定义 *********************************/
/* 系统初始化 */
static void System_Init()
{
	// 外设初始化
	UART_Init();
	LCD_Init();
	Timer0_Init();
	
	// 从EEPROM读取阈值
	g_Sys.temp_high = AT24C02_ReadByte(EE_ADDR_TH);
	g_Sys.temp_low = AT24C02_ReadByte(EE_ADDR_TL);
	
	// 阈值合法性校验：上限>下限,且在合理预设范围（此为0-60）
	if(g_Sys.temp_high > 60 || g_Sys.temp_low > 60 ||
		g_Sys.temp_high <= g_Sys.temp_low)
	{
		g_Sys.temp_high = DEFAULT_TH;
		g_Sys.temp_low = DEFAULT_TL;
		AT24C02_WriteByte(EE_ADDR_TH,DEFAULT_TH);
		AT24C02_WriteByte(EE_ADDR_TL,DEFAULT_TL);
	}
	
	// 首次温度读取
	DS18B20_ConvertT();
	Delay(1000);
	g_Sys.temperature = DS18B20_ReadT();
	
	// LCD初始显示
	LCD_ShowString(1,1,"Temp:    C");
	LCD_ShowString(2,1,"TH:   C  TL:   C");
	
	// 初始状态判断
	if(g_Sys.temperature > g_Sys.temp_high)
		g_Sys.status = STATUS_HIGH;
	else if(g_Sys.temperature < g_Sys.temp_low)
		g_Sys.status = STATUS_LOW;
	else 
		g_Sys.status = STATUS_NORMAL;
	
	Alarm_Update(g_Sys.status);
	
}
	
/* 温度更新+LCD显示+串口上报 */
static void Task_UpdateData()
{
	if(!flag_Updatedata)	return;
	flag_Updatedata = 0;
	
	// 温度采集
	DS18B20_ConvertT();													//启动下次转换
	g_Sys.temperature = DS18B20_ReadT();								//读取上次转换结果
	
	// LCD第一行：当前温度
	LCD_ShowNum(1,6,(unsigned int)g_Sys.temperature,3);
	LCD_ShowChar(1,9,'.');
	LCD_ShowNum(1,10,(unsigned long)(g_Sys.temperature*10)%10,1);
	
	// LCD第二行：阈值
	LCD_ShowNum(2,4,(unsigned int)g_Sys.temp_high,3);
	LCD_ShowChar(2,7,'.');
	LCD_ShowNum(2,8,(unsigned long)(g_Sys.temp_high*10)%10,1);
	LCD_ShowNum(2,12,(unsigned int)g_Sys.temp_low,3);
	LCD_ShowChar(2,15,'.');
	LCD_ShowNum(2,16,(unsigned long)(g_Sys.temp_low*10)%10,1);

	// 串口上报
	printf("T:%.1f,H:%.1f,L:%.1f",
			g_Sys.temperature,g_Sys.temp_high,g_Sys.temp_low);			
}

/* 阈值判断+串口上报状态+报警（2秒一次） */
static void Task_UpdateStatus()
{
	if(!flag_Updatestatus)	return;
	flag_Updatestatus = 0;
	
	// 判断当前状态
	if(g_Sys.temperature > g_Sys.temp_high)
		g_Sys.status = STATUS_HIGH;
	else if(g_Sys.temperature < g_Sys.temp_low)
		g_Sys.status = STATUS_LOW;
	else
		g_Sys.status = STATUS_NORMAL;
	
	//串口发送状态
	printf("S:%s\n",
	g_Sys.status == STATUS_NORMAL ? "NORMAL" : 
	g_Sys.status == STATUS_HIGH ? "HIGH" : "LOW");
	
	//触发报警
	Alarm_Update(g_Sys.status);
}

/* 保存历史温度到EEPROM（每2秒一次）
	环形队列：最多10条，存满覆盖旧纪录 */
static void Task_SaveHistory()
{
	if(!flag_Save)	return;
	flag_Save = 0;
	
	val = (int)(g_Sys.temperature*10);								//温度*10变为16位整数
	
	if((g_Sys.hist_tail+1)%MAXSIZE == g_Sys.hist_front)
	{
		// 队列已满，覆盖旧纪录
		AT24C02_WriteInt(HISTORY_BASE + g_Sys.hist_tail*2,val);
		g_Sys.hist_tail = g_Sys.hist_front;
		g_Sys.hist_front = (g_Sys.hist_front+1)%MAXSIZE;
	}
	else
	{
		// 队列未满，正常追加
		AT24C02_WriteInt(HISTORY_BASE + g_Sys.hist_tail * 2,val);
		g_Sys.hist_tail = (g_Sys.hist_tail + 1) % MAXSIZE;
	}
}

/* 串口回显 */
static void Task_EchoHandler()
{
	if(!flag_echo)	return;
	flag_echo = 0;
	
	UART_SendByte(echo_ch);											// 主循环中发送（忙等在UART_SendByte内部）
}

/* 串口命令处理 */
static void Task_CmdHandler()
{
	if(!rx_ready)	return;
	rx_ready = 0;
	
	UART_ParseCmd(rx_buf);											// 解析并执行命令
}

/* UART中断服务函数 */
void UART_ISR()	interrupt 4
{
	unsigned char ch;
	if(RI == 1)
	{
		ch = SBUF;
		RI = 0;
		
		// 回显
		echo_ch = ch;
		flag_echo = 1;
		
		// 接收：以'\n'为结束
		if(ch == '\n')
		{
			rx_buf[rx_index] = '\0';								// 字符串结尾
			rx_index = 0;
			rx_ready = 1;											// 通知主循环处理
		}
		else
		{
			rx_buf[rx_index] = ch;
			rx_index++;
			if(rx_index >= 19)	rx_index = 19;						// 防溢出，丢弃超长数据
		}
	}
}