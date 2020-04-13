#include "include/timer.h"

#include <stdlib.h>

static volatile uint32_t timer_cnt = 0;

enum { SET, RESET};

uint8_t player_list_analyse( StatePlayer *player);


void timer_updata()
{
    ++timer_cnt;
}


void timer_set( Timer *timer)
{
    timer->time = timer_cnt;
}


uint32_t timer_get( Timer *timer)
{
    return timer_cnt - timer->time;
}



//------------------------------------------------------------



void ramp_set(Ramp *ramp)
{
	timer_set(&(ramp->timer));
}




float ramp_calc(Ramp *ramp, uint32_t time, uint8_t dir)
{
	uint32_t diff;

	diff = timer_get(&(ramp->timer));
	timer_set(&(ramp->timer));

	switch (dir)
	{
	case RAMP_UP:
		ramp->ramp_out += (float)diff / (float)time;
		break;
	case RAMP_DOWN:
		ramp->ramp_out -= (float)diff / (float)time;
		break;
	}


	if (ramp->ramp_out > 1.0f)
	{
		ramp->ramp_out = 1.0f;
		return 1.0f;
	}
	if (ramp->ramp_out < 0.0f)
	{
		ramp->ramp_out = 0.0f;
		return 0.0f;
	}

	return ramp->ramp_out;


}





//------------------------------------------------------------

void player_init( StatePlayer *player, uint8_t mode, char *list, void ( *act_func)( int32_t action_code))
{
    player->list = list;

    player->pause_flag = SET;
    player->timer_start_flag = RESET;
    player->processing_index = 0;
    player->processing_action = 0;
    player->processing_time = 0;
    
    player->mode = mode;

    player->analyse_func = player_list_analyse;
    player->act_func = act_func;
}


void player_start( StatePlayer *player)
{
    player->pause_flag = RESET;
    player->timer_start_flag = SET;
}


void player_pause( StatePlayer *player)
{
    player->pause_flag = SET;
}


void player_stop( StatePlayer *player)
{
    player->pause_flag = SET;
    player->processing_index = 0;
}


void player_restart( StatePlayer *player)
{
    player->processing_index = 0;
    player->pause_flag = RESET;
    player->timer_start_flag = SET;
}


void player_jump_seq( StatePlayer *player, uint8_t seq)
{
    uint8_t a;
    player_restart( player);
    for( a = 0; a < seq; ++a)
    {
        player_list_analyse( player);
        ++player->processing_index;
    }
}


void player_jump_time( StatePlayer *player, uint32_t time)
{
    uint32_t time_sum = 0;
    player_restart( player);
    do
    {
        player_list_analyse( player);
        ++player->processing_index;
        time_sum += player->processing_time;
    }
    while( time_sum < time);
}

uint8_t player_list_analyse( StatePlayer *player)
{
    int32_t num_1 = 0, num_2 = 0;

    //get the 1st parameter
    num_1 = atoi( player->list + player->list_process);
    //find the "," and next pending subscript index
    for( ++player->list_process; player->list[ player->list_process] != ','; ++player->list_process)
    {
        if( player->list[ player->list_process] != '\0')
        {
            player_stop( player);
            return PLAYER_LIST_END;
        }
    }

    //get the 2nd parameter
    num_2 = atoi( player->list + player->list_process);
    //find the ";" and next pending subscript index
    for( ++player->list_process; player->list[ player->list_process] != ';'; ++player->list_process)
    {
        if( player->list[ player->list_process] != '\0')
        {
            player_stop( player);
            return PLAYER_LIST_END;            
        }

    }

    //handling malformed
    if( num_1 == -1 || num_2 == -1)
    {
        player_stop( player);
        return PLAYER_LIST_FORMAT_ERROR;
    }

    //do-wait mode parameter position swap
    if( player->mode == PLAYER_MODE_DOWAIT)
    {
        //swap num_1 and num_2
        num_1 = num_1 + num_2;
        num_2 = num_1 - num_2;
        num_1 = num_1 - num_2;
    }
    
    //get the next action from the string
    player->processing_action_last = player->processing_action;         
    player->processing_action = num_1;

    //get the next latency from the string
    player->processing_time = num_2;
    

    return 0;
}


void player_server( StatePlayer *player)
{
    if( player->pause_flag == RESET)
    {
        if( player->timer_start_flag == SET)
        {
            if( player->mode == PLAYER_MODE_DOWAIT)
            {
                //do once before wait
                switch( player->analyse_func( player)/*player_list_analyse( player)*/)
                {
                    case PLAYER_LIST_END:
                        if( player->repeat_time++ < player->repear_time_set)
                            player_restart( player);
                        break;
                    case PLAYER_LIST_FORMAT_ERROR:
                        break;
                    default:
                        break;
                }
                player->act_func( player->processing_action);                
            }

            timer_set( &( player->timer));
            player->timer_start_flag = RESET;
        }

        if( timer_get( &( player->timer)) % player->processing_time == 0)
        {
            /*if( player_list_analyse( player) == -1)
            {
                //some code to handle the malformed input
            }*/
            switch( player->analyse_func( player)/*player_list_analyse( player)*/)
            {
                case PLAYER_LIST_END:
                    if( player->repeat_time++ < player->repear_time_set)
                        player_restart( player);
                    break;
                case PLAYER_LIST_FORMAT_ERROR:
                    break;
                default:
                    break;
            }
            player->act_func( player->processing_action);
            
        }
        else if( player->transition_flag == SET)        //transition support
        {
            player->act_func( player->processing_action
                            + ( player->processing_action - player->processing_action_last)
                            * ( timer_get( &( player->timer)) / player->processing_time));
        }
    }
    else 
    {
        ++player->processing_index;
    }
    
}


uint8_t player_get_progress(StatePlayer *player)
{
    return player->processing_index;
}

uint8_t player_get_length(StatePlayer *player)
{
    uint8_t cnt = 0;
    uint32_t a;
    for( a = 0; player->list[a] != '\0'; ++a)
    {
        if( player->list[a] == ';')
            ++cnt;
    }

    return cnt;
}

void player_set_repeat( StatePlayer *player, int32_t times)
{
    player->repear_time_set = times;
}

int32_t player_get_repeat_time( StatePlayer *player)
{
    return player->repeat_time;
}

void player_set_transition( StatePlayer *player, uint8_t flag)
{
    player->transition_flag = flag;
    player->mode = PLAYER_MODE_DOWAIT;
}


void player_set_analyse_func( StatePlayer *player, uint8_t ( *analyse_func)(void *))
{
    player->analyse_func = analyse_func;
}

