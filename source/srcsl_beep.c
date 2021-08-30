/**
* @file srcsl_beep.c
* @brief 蜂鸣器驱动及扩展的乐谱播放功能
* @author Silonca
*/
#include "include/srcsl_beep.h"

///1=C5频率
static const int freq_C[7] = {523,587,659,698,784,880,988};		


/**
* @brief 曲谱解析函数
* @param *beep_music	蜂鸣器音乐模块指针
*/
static uint8_t music_analysis(SrcslBeepMusic *beep_music);

//蜂鸣器初始化
void srcsl_beep_init( SrcslBeep *beep, void ( *freq_set_func)(int32_t freq), uint32_t default_freq)
{
	beep->beep_state = SRCSL_BEEP_SWITCH_OFF;
	beep->default_freq = default_freq;
	beep->freq_set_func = freq_set_func;
	beep->freq_set_func(0);
}

//蜂鸣器开
void srcsl_beep_on(SrcslBeep *beep)
{
	if( beep->beep_state == SRCSL_BEEP_SWITCH_ON)
		return ;
	beep->freq_set_func( beep->default_freq);
	beep->beep_state = SRCSL_BEEP_SWITCH_ON;
}

//蜂鸣器关
void srcsl_beep_off(SrcslBeep *beep)
{	
	if( beep->beep_state == SRCSL_BEEP_SWITCH_OFF)
		return ;
	beep->freq_set_func(0);
	beep->beep_state = SRCSL_BEEP_SWITCH_OFF;
}

//蜂鸣器播放状态控制
void srcsl_beep_ctrl(SrcslBeep *beep, int beep_state)
{
	if( beep_state == SRCSL_BEEP_SWITCH_ON)
	{
		beep->freq_set_func( beep->default_freq);
		beep->beep_state = SRCSL_BEEP_SWITCH_ON;	
	}
	else if(beep_state == SRCSL_BEEP_SWITCH_OFF)
	{
		beep->freq_set_func(0);
		beep->beep_state = SRCSL_BEEP_SWITCH_OFF;	
	}
}

//蜂鸣器播放状态反转
void srcsl_beep_switch(SrcslBeep *beep)
{
	if( beep->beep_state == SRCSL_BEEP_SWITCH_ON)
	{
		beep->freq_set_func(0);
		beep->beep_state = SRCSL_BEEP_SWITCH_OFF;
	}
	else if(beep->beep_state == SRCSL_BEEP_SWITCH_OFF)
	{
		beep->freq_set_func( beep->default_freq);
		beep->beep_state = SRCSL_BEEP_SWITCH_ON;		
	}
}




//曲谱解析函数
static uint8_t music_analysis( SrcslBeepMusic *beep_music)
{
	const char *music = beep_music->player.list;
	uint16_t *progress = &( beep_music->player.list_process);

	//设置间隔时间，通过正负交替实现插入间隔以控制播放动作
	beep_music->dead_time = 0 - beep_music->dead_time;
	if( beep_music->dead_time > 0)
	{
		
		beep_music->player.processing_action = 0;
		beep_music->player.processing_time = (uint32_t)(beep_music->dead_time);
		return SRCSL_PLAYER_LIST_FRAME_OK;
	}
	
	beep_music->current_time = 1;
	
	//播放完毕
	if( music[*progress] == '\0')
		return SRCSL_PLAYER_LIST_END;
	
	//设置音调0的频率
	if( music[*progress] == '0') beep_music->current_tone_freq = 0;
	
	//获取音调1~7的频率
	if( music[*progress] >= '1' && music[*progress] <= '7')
		beep_music->current_tone_freq = freq_C[ music[ *progress] - '1'];
	
	//解析曲谱
	for( *progress+=1; music[*progress] != '\0' && !(music[*progress] >= '0' && music[*progress] <= '7'); ++*progress)
	{
		switch( music[*progress])
		{
			//频率
			case '*': beep_music->current_tone_freq 	*=2;	break;		//频率*2，变高一阶
			case '/': beep_music->current_tone_freq 	/=2;	break;		//频率/2，变低一阶
			case '#': beep_music->current_tone_freq = 
				(int)((float)beep_music->current_tone_freq * 1.059463094359295); break;		//升半音
			case 'b': beep_music->current_tone_freq = 
				(int)((float)beep_music->current_tone_freq / 1.059463094359295); break;		//降半音
			//时间
			case '-': beep_music->current_time 			+=1;	break;		//时间+1s
			case '_': beep_music->current_time 			/=2.0f;	break;	    //时间/2
			case '.': beep_music->current_time 			+=0.5f;	break;	    //时间+0.5s
			//格式
			case ' ':case'\n':case '\r':break;
			//其余字符视为格式错误
			default: return SRCSL_PLAYER_LIST_FORMAT_ERROR;
		}
	}


	beep_music->player.processing_action = beep_music->current_tone_freq;
	beep_music->player.processing_time = (uint32_t)(beep_music->current_time * 1000.0f);		//换算为毫秒

	return SRCSL_PLAYER_LIST_FRAME_OK;
}


//设置要播放的曲谱
void srcsl_music_init(SrcslBeepMusic *beep_music, SrcslBeep *beep, const char *music)
{
	beep_music->current_tone_freq = 0;
	beep_music->current_time = 0;
	beep_music->dead_time = 0;

	srcsl_player_init(&(beep_music->player), music, beep->freq_set_func);
	srcsl_player_set_analyse_func(&(beep_music->player), music_analysis);
}

//蜂鸣器音乐音符间隔时间设置，适当的间隔时间可以改善播放效果
void srcsl_music_set_deadtime(SrcslBeepMusic *beep_music, int dead_time)
{
	beep_music->dead_time = dead_time;
}


//蜂鸣器音乐服务函数
void srcsl_music_server(SrcslBeepMusic *beep_music)
{	
	srcsl_player_server( &(beep_music->player));
}

//蜂鸣器音乐播放开始
void srcsl_music_start( SrcslBeepMusic *beep_music)
{
	srcsl_player_start( &( beep_music->player));
}

//蜂鸣器音乐播放暂停
void srcsl_music_pause( SrcslBeepMusic *beep_music)
{
	srcsl_player_pause( &( beep_music->player));
}

//蜂鸣器音乐终止
void srcsl_music_stop( SrcslBeepMusic *beep_music)
{
	srcsl_player_stop( &( beep_music->player));
}

//蜂鸣器音乐重新开始播放
void srcsl_music_restart( SrcslBeepMusic *beep_music)
{
	srcsl_player_restart( &( beep_music->player));
}


