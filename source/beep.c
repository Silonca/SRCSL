#include "include/beep.h"



static int freq_C[7] = {523,587,659,698,784,880,988};		//C调中音频率

enum { SET, RESET};

void player_set_analyse_func( uint8_t ( *analyse_func)(void *));


//蜂鸣器初始化

void beep_init( Beep *beep, void ( *freq_set_func)(uint32_t freq), uint32_t default_freq)
{
	beep->beep_state = BEEP_SWITCH_OFF;
	beep->default_freq = default_freq;
	beep->freq_set_func = freq_set_func;
	beep->freq_set_func(0);
}

//蜂鸣器开
void beep_on(Beep *beep)
{
	if( beep->beep_state == BEEP_SWITCH_ON)
		return ;
	beep->freq_set_func( beep->default_freq);
	beep->beep_state = BEEP_SWITCH_ON;
}

//蜂鸣器关
void beep_off(Beep *beep)
{	
	if( beep->beep_state == BEEP_SWITCH_OFF)
		return ;
	beep->freq_set_func(0);
	beep->beep_state = BEEP_SWITCH_OFF;
}


//蜂鸣器播放状态控制
void beep_ctrl(Beep *beep, int beep_state)
{
	if( beep_state == BEEP_SWITCH_ON)
	{
		beep->freq_set_func( beep->default_freq);
		beep->beep_state = BEEP_SWITCH_ON;	
	}
	else if(beep_state == BEEP_SWITCH_OFF)
	{
		beep->freq_set_func(0);
		beep->beep_state = BEEP_SWITCH_OFF;	
	}
}

//蜂鸣器播放状态反转
void beep_switch(Beep *beep)
{
	if( beep->beep_state == BEEP_SWITCH_ON)
	{
		beep->freq_set_func(0);
		beep->beep_state = BEEP_SWITCH_OFF;
	}
	else if(beep->beep_state == BEEP_SWITCH_OFF)
	{
		beep->freq_set_func( beep->default_freq);
		beep->beep_state = BEEP_SWITCH_ON;		
	}
}





//设置要播放的曲谱
void music_init(BeepMusic *beep_music, Beep *beep, char *music)
{
	beep_music->current_tone_freq	= 0;
	beep_music->current_time 		= 0;
	beep_music->dead_time			= 0;

	player_init( &(beep_music->player), PLAYER_MODE_DOWAIT, beep->freq_set_func, music);
	player_set_analyse_func( &(beep_music->player), music_analysis);
}


//解析曲谱
static void music_analysis( BeepMusic *beep_music)
{
	char *music = beep_music->player.list;
	uint16_t *progress = &( beep_music->player.list_process);

	//set dead-time
	beep_music->dead_time = 0 - beep_music->dead_time;
	if( beep_music->dead_time > 0)
	{
		beep_music->player.processing_action = 0;
		beep_music->player.processing_time = beep_music->dead_time * 1000;
		return ;
	}
	
	beep_music->current_time = 1;
	
	//播放完毕
	if( music[*progress] == '\0')
		return ;
	
	//设置音调0的频率
	if( music[*progress] == '0') beep_music->current_tone_freq = 0;
	
	//获取音调1~7的频率
	if( music[*progress] >= '1' && music[*progress] <= '7')
		beep_music->current_tone_freq = freq_C[ music[ *progress] - '1'];
	
	//解析曲谱
	for( *progress+=1; music[*progress] != '\0' && !(music[*progress] >= '1' && music[*progress] <= '7'); ++*progress)
	{
		switch( music[*progress])
		{
			//freq
			case '*': beep_music->current_tone_freq 	*=2;	break;		//频率*2，变高一阶
			case '/': beep_music->current_tone_freq 	/=2;	break;		//频率/2，变低一阶
			//time
			case '-': beep_music->current_time 			+=1;	break;		//时间+1s
			case '_': beep_music->current_time 			/=2.0f;	break;	    //时间/2
			case '.': beep_music->current_time 			+=0.5f;	break;	    //时间+0.5s
			//error
			default:
		}

	}


	beep_music->player.processing_action = beep_music->current_tone_freq;
	beep_music->player.processing_time = beep_music->current_time * 1000;
}



//蜂鸣器音乐服务函数
void beep_music_server(BeepMusic *beep_music)
{	
	player_server( &(beep_music->player));
}

void music_start( BeepMusic *beep_music)
{
	player_start( &( beep_music->player));
}


void music_pause( BeepMusic *beep_music)
{
	player_pause( &( beep_music->player));
}


void music_stop( BeepMusic *beep_music)
{
	player_stop( &( beep_music->player));
}



void music_restart( BeepMusic *beep_music)
{
	player_restart( &( beep_music->player));
}



void music_jump_time( BeepMusic *beep_music, uint32_t time)
{
	player_jump_time( &( beep_music->player), time);
}


void music_set_repeat( BeepMusic *beep_music, int32_t times)
{
	player_set_repeat( &( beep_music->player), times);
}


uint8_t music_get_progress(BeepMusic *beep_music)
{
	return player_get_progress( &( beep_music->player));
}


uint8_t music_get_length(BeepMusic *beep_music)
{
	return player_get_length( &( beep_music->player));
}


int32_t music_get_repeat_time( BeepMusic *beep_music)
{
	return player_get_repeat_time( &( beep_music->player));
}

void music_set_deadtime( BeepMusic *beep_music, int dead_time)
{
	beep_music->dead_time = dead_time;
}



