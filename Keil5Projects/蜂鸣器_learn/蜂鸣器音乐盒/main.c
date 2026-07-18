#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "KeyMatrix.h"

sbit Buzzer = P2^5;

/*==========================================================================
 * 音符频率表 (Timer0 重装值, 11.0592MHz / 12T 模式)
 * 36 个半音覆盖 3 个八度
 * 重装值 = 65536 - 460800 / f  (因为 ISR 每次翻转蜂鸣器 = 半周期)
 *==========================================================================*/
unsigned int code FreqTable[] = {
	63775,63874,63967,64055,64138,64217,64291,64360,64426,64489,64548,64603,
	64655,64705,64751,64795,64837,64876,64913,64948,64981,65012,65042,65069,
	65096,65120,65144,65166,65187,65206,65225,65242,65259,65274,65289,65303
};

/* 音符别名 — FreqTable 索引 */
#define RST 0xFF		// 休止符
#define L1 0	#define L2 2	#define L3 4	#define L4 5	#define L5 7	#define L6 9	#define L7 11
#define M1 12	#define M2 14	#define M3 16	#define M4 17	#define M5 19	#define M6 21	#define M7 23
#define H1 24	#define H2 26	#define H3 28	#define H4 29	#define H5 31	#define H6 33	#define H7 35

/*==========================================================================
 * 歌曲数据结构
 *==========================================================================*/
typedef struct {
	unsigned char note;		// FreqTable 索引 / RST
	unsigned int  ms;		// 持续时间 (毫秒)
} SongNote;

#define SONG_END {0xFF, 0xFFFF}

/*---------- 生日快乐 ----------*/
SongNote code HappyBirthday[] = {
	{M5,400},{M5,400},{M6,800},{M5,800},{H1,800},{M7,1200},
	{M5,400},{M5,400},{M6,800},{M5,800},{H2,800},{H1,1200},
	{M5,400},{M5,400},{H3,800},{H1,800},{M7,800},{M6,1200},
	{M4,400},{M4,400},{H3,800},{H1,800},{H2,800},{H1,1600},
	SONG_END
};

/*---------- 两只老虎 ----------*/
SongNote code TwoTigers[] = {
	{M1,500},{M2,500},{M3,500},{M1,500},
	{M1,500},{M2,500},{M3,500},{M1,500},
	{M3,500},{M4,500},{M5,1000},
	{M3,500},{M4,500},{M5,1000},
	{M5,300},{M6,300},{M5,300},{M4,300},{M3,500},{M1,500},
	{M5,300},{M6,300},{M5,300},{M4,300},{M3,500},{M1,500},
	{M1,600},{L5,600},{M1,1000},
	{M1,600},{L5,600},{M1,1000},
	SONG_END
};

/*==========================================================================
 * 全局状态
 *==========================================================================*/
#define SONG_COUNT 2
SongNote* code SongList[SONG_COUNT] = {HappyBirthday, TwoTigers};
char* code SongNames[SONG_COUNT] = {"Happy Birthday  ", "Two Tigers      "};

unsigned char currSong   = 0;		// 当前歌曲
unsigned int  noteIdx    = 0;		// 当前音符索引
unsigned int  noteMs     = 0;		// 当前音符已播放毫秒数
unsigned char isPlaying  = 0;		// 播放/暂停标志
bit noteDone = 0;					// 音符到时标志 (ISR → main 同步)

/*==========================================================================
 * 播放指定音符
 *==========================================================================*/
void PlayNote(unsigned char note)
{
	if(note == RST)
	{
		ET0 = 0;			// 关 Timer0 中断, 停止翻转蜂鸣器
		Buzzer = 0;
	}
	else
	{
		ET0 = 0;			// 短暂关中断, 安全装载重装值
		TL0 = FreqTable[note] % 256;
		TH0 = FreqTable[note] / 256;
		TF0 = 0;
		ET0 = 1;			// 开 Timer0 中断
	}
}

/*==========================================================================
 * 播放控制
 *==========================================================================*/
void StopMusic()
{
	ET0 = 0;
	Buzzer = 0;
	isPlaying = 0;
	noteMs = 0;
}

void StartMusic()
{
	noteIdx = 0;
	noteMs  = 0;
	noteDone = 0;
	isPlaying = 1;
	PlayNote(SongList[currSong][0].note);
	LCD_ShowString(1, 1, SongNames[currSong]);
	LCD_ShowNum(2, 1, (unsigned int)(noteIdx + 1), 4);
	LCD_ShowString(2, 5, "/               ");
	LCD_ShowString(2, 9, "Playing ");
}

void NextSong()
{
	StopMusic();
	currSong++;
	if(currSong >= SONG_COUNT) currSong = 0;
	StartMusic();
}

void PrevSong()
{
	StopMusic();
	if(currSong == 0) currSong = SONG_COUNT;
	currSong--;
	StartMusic();
}

/*==========================================================================
 * 按键处理
 * S1: 播放/暂停  S2: 下一首  S3: 上一首  S4: 停止
 *==========================================================================*/
void HandleKeys()
{
	unsigned char key = KeyScan();
	if(key == 0) return;

	switch(key)
	{
		case 1:		// S1: 播放/暂停
			if(isPlaying)
			{
				ET0 = 0;
				Buzzer = 0;
				isPlaying = 0;
				LCD_ShowString(2, 9, "Paused  ");
			}
			else
			{
				isPlaying = 1;
				PlayNote(SongList[currSong][noteIdx].note);
				LCD_ShowString(2, 9, "Playing ");
			}
			break;

		case 2:		// S2: 下一首
			NextSong();
			break;

		case 3:		// S3: 上一首
			PrevSong();
			break;

		case 4:		// S4: 停止 (回到开头)
			StopMusic();
			noteIdx = 0;
			LCD_ShowString(2, 1, "Stopped         ");
			break;

		default:
			break;
	}
}

/*==========================================================================
 * 主函数
 *==========================================================================*/
void main()
{
	Timer0_Init();
	Timer1_Init();		// 1ms 时基
	LCD_Init();

	LCD_ShowString(1, 1, "Music Box v1.0  ");
	LCD_ShowString(2, 1, "S1 Play/Pause   ");
	Delay(2000);

	/* 默认加载第一首歌 (暂停状态) */
	LCD_ShowString(1, 1, SongNames[0]);
	LCD_ShowString(2, 1, "S1:Play S2:Next ");

	while(1)
	{
		HandleKeys();

		/* 音符到时 → 切换到下一个音符 */
		if(noteDone)
		{
			noteDone = 0;
			noteMs = 0;
			noteIdx++;

			/* 歌曲结束 → 循环 */
			if(SongList[currSong][noteIdx].ms == 0xFFFF)
			{
				noteIdx = 0;
			}

			PlayNote(SongList[currSong][noteIdx].note);

			/* 更新 LCD */
			LCD_ShowNum(2, 1, (unsigned int)(noteIdx + 1), 4);
		}
	}
}

/*==========================================================================
 * Timer0 ISR — 翻转蜂鸣器产生音频方波
 *==========================================================================*/
void Timer0_ISR() interrupt 1
{
	/* 重装初值已由硬件自动完成 (Mode 1), 但 51 需要手动重装 */
	/* 重装值在 PlayNote() 中设置了 TH0/TL0, 这里不做改动 */
	Buzzer = ~Buzzer;		// 翻转 = 半周期
}

/*==========================================================================
 * Timer1 ISR — 1ms 时基, 用于音符时值计时
 *==========================================================================*/
void Timer1_ISR() interrupt 3
{
	/* 1ms 重装值 @ 11.0592MHz */
	TL1 = 0x66;
	TH1 = 0xFC;

	if(isPlaying)
	{
		noteMs++;
		/* 比较当前音符的持续时间 */
		if(noteMs >= SongList[currSong][noteIdx].ms)
		{
			noteMs = 0;
			noteDone = 1;
		}
	}
}
