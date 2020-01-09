#ifndef BEEP_H_INCLUDED
#define BEEP_H_INCLUDED

#include <stdint.h>



enum BEEP_STATES { BEEP_SWITCH_ON, BEEP_SWITCH_OFF};


typedef struct 
{
    uint32_t beep_state;
    uint32_t server_state;

    void ( *beep_on_func)();
    void ( *beep_off_func)();
    void ( *freq_set_func)(uint32_t freq);

	//用于设定
	uint32_t beep_ms;
	uint32_t beep_times;
	uint32_t beep_interval;
	//用于实现
	uint32_t ms;
	uint32_t times;
	uint32_t interval;
} Beep;


//蜂鸣器音乐
typedef struct
{
	char *music;						//谱子
	int progress;						//播放进度（数组下标）
	int current_tone_freq;				//当前音调
	float current_time;					//当前音调时长
} Beep_Music;


void Beep_Init( Beep *beep, void ( *beep_on_func)(), void ( *beep_off_func)());			//Beep初始化
void Beep_On(Beep *beep);						    //开启Beep
void Beep_Off(Beep *beep);					        //关闭Beep
void Beep_Ctrl(Beep *beep, int beep_state);			//控制Beep开关
void Beep_Switch(Beep *beep);					    //反转Beep状态

void Beep_Set( Beep *beep, uint32_t ms, uint32_t times, uint32_t interval);		//设置Beep时间，次数及间隔
void Beep_Server(Beep *beep);												    //Beep_Set服务函数


void Music_Set(Beep_Music *beep_music, char *music);			        //音乐曲谱设置
void Beep_Music_Server( Beep *beep, Beep_Music *beep_music);			//蜂鸣器音乐服务


#endif // BEEP_H_INCLUDED
