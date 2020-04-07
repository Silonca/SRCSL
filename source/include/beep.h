#ifndef BEEP_H_INCLUDED
#define BEEP_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#include "timer.h"


enum BEEP_STATES { BEEP_SWITCH_ON, BEEP_SWITCH_OFF};


typedef struct 
{
    uint32_t beep_state;
    uint32_t default_freq;

    void ( *freq_set_func)(int32_t freq);
} Beep;



void beep_init( Beep *beep, void ( *freq_set_func)(int32_t freq), uint32_t default_freq);			//Beep初始化
void beep_on(Beep *beep);						    //开启Beep
void beep_off(Beep *beep);					        //关闭Beep
void beep_ctrl(Beep *beep, int beep_state);			//控制Beep开关
void beep_switch(Beep *beep);					    //反转Beep状态




//蜂鸣器音乐
typedef struct
{
	StatePlayer player;

	int current_tone_freq;				//当前音调
	float current_time;					//当前音调时长
	float dead_time;						//停顿时间（改善播放效果）（ms）
	
} BeepMusic;


void music_init(BeepMusic *beep_music, Beep *beep, char *music);			        //音乐曲谱设置
void music_set_deadtime( BeepMusic *beep_music, int dead_time);

void music_start( BeepMusic *beep_music);
void music_pause( BeepMusic *beep_music);
void music_stop( BeepMusic *beep_music);                        //Stop
void music_restart( BeepMusic *beep_music);                     //Restart

void music_jump_time( BeepMusic *beep_music, uint32_t time);    //Jump to the frame after the given time
void music_set_repeat( BeepMusic *beep_music, int32_t times);

uint8_t music_get_progress(BeepMusic *beep_music);
uint8_t music_get_Length(BeepMusic *beep_music);
int32_t music_get_repeat_time( BeepMusic *beep_music);

void music_server( BeepMusic *beep_music);			//蜂鸣器音乐服务

#ifdef __cplusplus
}
#endif

#endif // BEEP_H_INCLUDED
