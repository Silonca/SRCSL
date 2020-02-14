#include "timer.h"

#include <stdlib.h>

static volatile uint32_t timer_cnt = 0;

enum { SET, RESET};

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

void player_init( State_Player *player, char *list, void ( *act_func)( uint8_t action_code))
{
    player->list = list;

    player->pause_flag = SET;
    player->timer_start_flag = RESET;
    player->processing_index = 0;
    player->processing_action = 0;
    player->processing_time = 0;

    player->act_func = act_func;
}


void player_start( State_Player *player)
{
    player->pause_flag = RESET;
    player->timer_start_flag = SET;
}


void player_pause( State_Player *player)
{
    player->pause_flag = SET;
}


void player_stop( State_Player *player)
{
    player->pause_flag = SET;
    player->processing_index = 0;
}


void player_restart( State_Player *player)
{
    player->processing_index = 0;
    player->pause_flag = RESET;
    player->timer_start_flag = SET;
}


void player_jump_seq( State_Player *player, uint8_t seq)
{
    player_restart( player);
    for( uint8_t a = 0; a < seq; ++a)
    {
        player_list_analyse( player);
        ++player->processing_index;
    }
}


void player_jump_time( State_Player *player, uint32_t time)
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

uint8_t player_list_analyse( State_Player *player)
{
    //get the next action from the string
    player->processing_action = atoi( player->list + player->list_process);
    //handling malformed
    if( player->processing_action == -1 || player->processing_action == 0)
    {
        player_stop( player);
        return PLAYER_LIST_FORMAT_ERROR;
    }

    //find the "," and next pending subscript index
    for( ++player->list_process; player->list[ player->list_process] != ','; ++player->list_process)
    {
        if( player->list[ player->list_process] != '\0')
        {
            player_stop( player);
            return PLAYER_LIST_END;
        }
    }

    //get the next latency from the string
    player->processing_time = atoi( player->list + player->list_process);
    //handling malformed input
    if( player->processing_time == -1 || player->processing_time == 0)
    {
        player_stop( player);
        return PLAYER_LIST_FORMAT_ERROR;
    }

    //find the ";" and next pending subscript index
    for( ++player->list_process; player->list[ player->list_process] != ';'; ++player->list_process)
    {
        if( player->list[ player->list_process] != '\0')
        {
            player_stop( player);
            return PLAYER_LIST_END;            
        }

    }
    return 0;
}

void player_server( State_Player *player)
{
    if( player->pause_flag == RESET)
    {
        if( player->timer_start_flag == SET)
        {
            timer_set( &( player->timer));
            player->timer_start_flag = RESET;
        }

        if( timer_get( &( player->timer)) % player->processing_time == 0)
        {
            /*if( player_list_analyse( player) == -1)
            {
                //some code to handle the malformed input
            }*/
            switch( player_list_analyse( player))
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
    }
    else 
    {
        ++player->processing_index;
    }
    
}



uint8_t player_get_progress(State_Player *player)
{
    return player->processing_index;
}

uint8_t player_get_length(State_Player *player)
{
    uint8_t cnt = 0;
    for( uint32_t a = 0; player->list[a] != '\0'; ++a)
    {
        if( player->list[a] == ';')
            ++cnt;
    }

    return cnt;
}

void player_set_repeat( State_Player *player, int32_t times)
{
    player->repear_time_set = times;
}

int32_t player_get_repeat_time( State_Player *player)
{
    return player->repeat_time;
}

void player_set_transition( State_Player *player, uint8_t flag)
{
    player->transition_flag = flag;
}


