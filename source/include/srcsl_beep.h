#ifndef SRCSL_BEEP_H_INCLUDED
#define SRCSL_BEEP_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"
#include "srcsl_timer.h"

//蜂鸣器开关状态
enum SRCSL_BEEP_STATES 
{ 
	SRCSL_BEEP_SWITCH_ON,		//!< 蜂鸣器开
	SRCSL_BEEP_SWITCH_OFF		//!< 蜂鸣器关
};


typedef struct 
{
    uint32_t beep_state;						//!< 蜂鸣器状态
    uint32_t default_freq;						//!< 蜂鸣器默认频率
												
    void ( *freq_set_func)(int32_t freq);		//!< 蜂鸣器频率设置函数的指针
} SrcslBeep;


/**
* @brief 蜂鸣器初始化
* @param *beep				蜂鸣器逻辑实体指针
* @param *freq_set_func		蜂鸣器频率设置函数指针
* @param default_freq		默认频率
*/
void srcsl_beep_init( SrcslBeep *beep, void ( *freq_set_func)(int32_t freq), uint32_t default_freq);			

/**
* @brief 蜂鸣器开
* @param *beep	蜂鸣器逻辑实体指针
*/
void srcsl_beep_on(SrcslBeep *beep);						    

/**
* @brief 蜂鸣器关
* @param *beep	蜂鸣器逻辑实体指针
*/
void srcsl_beep_off(SrcslBeep *beep);					        

/**
* @brief 蜂鸣器播放状态控制
* @param *beep					蜂鸣器逻辑实体指针
* @param beep_state				蜂鸣器状态
* @ref SRCSL_BEEP_SWITCH_ON		蜂鸣器开
* @ref SRCSL_BEEP_SWITCH_OFF	蜂鸣器关
*/
void srcsl_beep_ctrl(SrcslBeep *beep, int beep_state);			

/**
* @brief 蜂鸣器播放状态反转
* @param *beep	蜂鸣器逻辑实体指针
*/
void srcsl_beep_switch(SrcslBeep *beep);					    


//-----------------------------------------------------------------------------------------

//蜂鸣器音乐
typedef struct
{
	SrcslActionPlayer player;

	int current_tone_freq;			//!< 当前音调
	float current_time;				//!< 当前音调时长
	int dead_time;					//!< 音之间的停顿时间（改善播放效果）（ms）
	
} SrcslBeepMusic;

/**
* @brief 设置要播放的曲谱
* @param *beep_music	蜂鸣器音乐指针
* @param *beep			已初始化的蜂鸣器指针
* @param *music			编写好的乐谱
*/
void srcsl_music_init(SrcslBeepMusic *beep_music, SrcslBeep *beep,const char *music);			       

/**
* @brief 蜂鸣器音乐音符间隔时间设置，适当的间隔时间可以改善播放效果
* @param *beep_music	蜂鸣器音乐指针
* @param dead_time		间隔时间
*/
void srcsl_music_set_deadtime( SrcslBeepMusic *beep_music, int dead_time);

/**
* @brief 蜂鸣器音乐播放开始
* @param *beep_music 蜂鸣器音乐指针
*/
void srcsl_music_start( SrcslBeepMusic *beep_music);

/**
* @brief 蜂鸣器音乐暂停
* @param *beep_music 蜂鸣器音乐指针
*/
void srcsl_music_pause( SrcslBeepMusic *beep_music);

/**
* @brief 蜂鸣器音乐终止
* @param *beep_music 蜂鸣器音乐指针
*/
void srcsl_music_stop( SrcslBeepMusic *beep_music);                        

/**
* @brief 蜂鸣器音乐重新开始播放
* @param *beep_music 蜂鸣器音乐指针
*/
void srcsl_music_restart( SrcslBeepMusic *beep_music);                    

/**
* @brief 蜂鸣器音乐服务函数
* @param *beep_music 蜂鸣器音乐指针
*/
void srcsl_music_server(SrcslBeepMusic *beep_music);			


#ifdef __cplusplus
}
#endif

#endif // BEEP_H_INCLUDED
