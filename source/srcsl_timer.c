/**
* @file srcsl_timer.c
* @brief 实现计时器和计时执行动作功能
* @author Silonca
*/
#include "include/srcsl_timer.h"

#include <stdlib.h>

/// @var timer_cnt 全局时间，计时器各项功能的基础，32位无符号整型以毫秒为单位可以计时49.7天，在单片机上无需担心溢出
static volatile uint32_t timer_cnt = 0;

/**
* @brief 动作播放器播放内容解析（默认解析函数，不提供对外接口）
* @param 动作播放器模块指针
* @return 解析状态
* @retval SRCSL_PLAYER_LIST_FRAME_OK		 播放器列表解析帧解析正常结束
* @retval SRCSL_PLAYER_LIST_END				 播放器列表解析到末尾
* @retval SRCSL_PLAYER_LIST_FORMAT_ERROR	 播放器列表解析格式错误
*/
static uint8_t srcsl_player_list_analyse( SrcslActionPlayer *player);



void srcsl_timer_updata(void)
{
    ++timer_cnt;
}

void srcsl_timer_set( SrcslTimer *timer)
{
    timer->time = timer_cnt;
}

uint32_t srcsl_timer_get( SrcslTimer *timer)
{
    return timer_cnt - timer->time;
}


//------------------------------------------------------------



void srcsl_player_init( SrcslActionPlayer *player, const char *list, void ( *act_func)( int32_t action_code))
{
    player->list = list;

    player->player_state = SRCSL_PLAYER_PAUSE;
    player->timer_flag = SRCSL_RESET;
    player->processing_action = 0;
    player->processing_time = 0;
    

    player->analyse_func = srcsl_player_list_analyse;
    player->act_func = act_func;
}



void srcsl_player_set_analyse_func(SrcslActionPlayer *player, uint8_t (*analyse_func)(void *))
{
	player->analyse_func = analyse_func;
}



void srcsl_player_start( SrcslActionPlayer *player)
{
	//正常播放状态无动作
	if (player->player_state == SRCSL_PLAYER_PLAYING)
		return;

    player->player_state = SRCSL_PLAYER_PLAYING;
    player->timer_flag = SRCSL_RESET;
}


void srcsl_player_pause( SrcslActionPlayer *player)
{
    player->player_state = SRCSL_PLAYER_PAUSE;
}


void srcsl_player_stop( SrcslActionPlayer *player)
{
    player->player_state = SRCSL_PLAYER_STOP;
	player->timer_flag = SRCSL_RESET;
	player->processing_action = 0;
	player->processing_time = 0;
	player->list_process = 0;
}


void srcsl_player_restart( SrcslActionPlayer *player)
{
	srcsl_player_stop(player);
	srcsl_player_start(player);
}



uint8_t srcsl_player_server( SrcslActionPlayer *player)
{
	//是否暂停
	if (player->player_state == SRCSL_PLAYER_PAUSE || player->player_state == SRCSL_PLAYER_STOP)
	{
		return SRCSL_PLAYER_PAUSE;
	}

	//定时器处于不工作状态（即“等”状态完毕）时，开始下一轮解析和动作
	if (player->timer_flag == SRCSL_RESET)
    {
		//解析
		do
		{ 
			player->analyse_state = player->analyse_func(player);
			switch(player->analyse_state)
			{
				//处理格式错误
				case SRCSL_PLAYER_LIST_FORMAT_ERROR:
					srcsl_player_stop( player);
					break;
			}
			player->act_func( player->processing_action);                
        //如果等待时间为0，就再次解析
		} while (player->processing_time == 0);

		srcsl_timer_set( &( player->timer));
		player->timer_flag = SRCSL_SET;
    }
	//等待时间-1，减去本次时间
	if (player->timer_flag == SRCSL_SET && srcsl_timer_get(&(player->timer)) == player->processing_time - 1) {
		player->timer_flag = SRCSL_RESET;
		//解析到末尾且延时结束，认为播放结束
		if (player->analyse_state == SRCSL_PLAYER_LIST_END)
		{
			srcsl_player_stop(player);
			return SRCSL_PLAYER_STOP;
		}
	}
	
	return player->player_state;
}


static uint8_t srcsl_player_list_analyse(SrcslActionPlayer *player)
{
	int32_t num_1 = 0, num_2 = 0;

	//获取第一个参数
	num_1 = atoi(player->list + player->list_process);

	//找“,”
	for (; player->list[player->list_process] != ','; ++player->list_process)
	{
		//提前遇到字符串结尾，说明格式错误
		if (player->list[player->list_process] == '\0')
		{
			//srcsl_player_stop(player);
			return SRCSL_PLAYER_LIST_FORMAT_ERROR;
		}
	}
	++player->list_process;

	//获取第二个参数
	num_2 = atoi(player->list + player->list_process);

	//寻找“;”
	for (; player->list[player->list_process] != ';'; ++player->list_process)
	{
		//提前遇到字符串结尾，说明格式错误
		if (player->list[player->list_process] == '\0')
		{
			//srcsl_player_stop(player);
			return SRCSL_PLAYER_LIST_FORMAT_ERROR;
		}
	}
	++player->list_process;

	//数值错误
	if (num_1 == -1 || num_2 == -1)
	{
		//srcsl_player_stop(player);
		return SRCSL_PLAYER_LIST_FORMAT_ERROR;
	}

	//读取动作       
	player->processing_action = num_1;
	//读取延迟时间
	player->processing_time = num_2;


	//正常解析到list结尾
	if (player->list[player->list_process + 1] == '\0')
	{
		return SRCSL_PLAYER_LIST_END;
	}

	//帧解析正常
	return SRCSL_PLAYER_LIST_FRAME_OK;
}

