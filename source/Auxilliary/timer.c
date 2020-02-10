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

void act_init( Act_Orderly *ao, char *list, void ( *act_func)( uint8_t action_code))
{
    ao->list = list;

    ao->pause_flag = SET;
    ao->timer_start_flag = RESET;
    ao->processing_index = 0;
    ao->processing_action = 0;
    ao->processing_time = 0;

    ao->act_func = act_func;
}


void act_start( Act_Orderly *ao)
{
    ao->pause_flag = RESET;
    ao->timer_start_flag = SET;
}


void act_pause( Act_Orderly *ao)
{
    ao->pause_flag = SET;
}


void act_stop( Act_Orderly *ao)
{
    ao->pause_flag = SET;
    ao->processing_index = 0;
}


void act_restart( Act_Orderly *ao)
{
    ao->processing_index = 0;
    ao->pause_flag = RESET;
    ao->timer_start_flag = SET;
}


void act_jump_seq( Act_Orderly *ao, uint8_t seq)
{
    act_restart( ao);
    for( uint8_t a = 0; a < seq; ++a)
    {
        act_list_analyse( ao);
        ++ao->processing_index;
    }
}


void act_jump_time( Act_Orderly *ao, uint32_t time)
{
    uint32_t time_sum = 0;
    act_restart( ao);
    do
    {
        act_list_analyse( ao);
        ++ao->processing_index;
        time_sum += ao->processing_time;
    }
    while( time_sum < time);
}

uint8_t act_list_analyse( Act_Orderly *ao)
{
    //get the next action from the string
    ao->processing_action = atoi( ao->list + ao->list_process);
    //handling malformed
    if( ao->processing_action == -1 || ao->processing_action == 0)
    {
        act_stop( ao);
        return ACT_LIST_FORMAT_ERROR;
    }

    //find the "," and next pending subscript index
    for( ++ao->list_process; ao->list[ ao->list_process] != ','; ++ao->list_process)
    {
        if( ao->list[ ao->list_process] != '\0')
        {
            act_stop( ao);
            return ACT_LIST_END;
        }
    }

    //get the next latency from the string
    ao->processing_time = atoi( ao->list + ao->list_process);
    //handling malformed input
    if( ao->processing_time == -1 || ao->processing_time == 0)
    {
        act_stop( ao);
        return ACT_LIST_FORMAT_ERROR;
    }

    //find the ";" and next pending subscript index
    for( ++ao->list_process; ao->list[ ao->list_process] != ';'; ++ao->list_process)
    {
        if( ao->list[ ao->list_process] != '\0')
        {
            act_stop( ao);
            return ACT_LIST_END;            
        }

    }
    return 0;
}

void act_server( Act_Orderly *ao)
{
    if( ao->pause_flag == RESET)
    {
        if( ao->timer_start_flag == SET)
        {
            timer_set( &( ao->timer));
            ao->timer_start_flag = RESET;
        }

        if( timer_get( &( ao->timer)) % ao->processing_time == 0)
        {
            /*if( Act_List_Analyse( ao) == -1)
            {
                //some code to handle the malformed input
            }*/
            switch( act_list_analyse( ao))
            {
                case ACT_LIST_END:
                    if( ao->repeat_time++ < ao->repear_time_set)
                        act_restart( ao);
                    break;
                case ACT_LIST_FORMAT_ERROR:
                    break;
                default:
                    break;
            }
            ao->act_func( ao->processing_action);
        }
    }
    else 
    {
        ++ao->processing_index;
    }
    
}



uint8_t act_get_progress(Act_Orderly *ao)
{
    return ao->processing_index;
}

uint8_t act_get_length(Act_Orderly *ao)
{
    uint8_t cnt = 0;
    for( uint32_t a = 0; ao->list[a] != '\0'; ++a)
    {
        if( ao->list[a] == ';')
            ++cnt;
    }

    return cnt;
}

void act_set_repeat( Act_Orderly *ao, int32_t times)
{
    ao->repear_time_set = times;
}

int32_t act_get_repeat_time( Act_Orderly *ao)
{
    return ao->repeat_time;
}

void act_set_transition( Act_Orderly *ao, uint8_t flag)
{
    ao->transition_flag = flag;
}


