#include "timer.h"

#include <stdlib.h>

static volatile uint32_t timer_cnt = 0;

enum { SET, RESET};

void Timer_Updata()
{
    ++timer_cnt;
}


void Timer_Set( Timer *timer)
{
    timer->time = timer_cnt;
}


uint32_t Timer_Get( Timer *timer)
{
    return timer_cnt - timer->time;
}



//------------------------------------------------------------

void Act_Init( Act_Orderly *ao, char *list, void ( *act_func)( uint8_t action_code))
{
    ao->list = list;

    ao->pause_flag = SET;
    ao->timer_start_flag = RESET;
    ao->processing_index = 0;
    ao->processing_action = 0;
    ao->processing_time = 0;

    ao->act_func = act_func;
}


void Act_Start( Act_Orderly *ao)
{
    ao->pause_flag = RESET;
    ao->timer_start_flag = SET;
}


void Act_Pause( Act_Orderly *ao)
{
    ao->pause_flag = SET;
}


void Act_Stop( Act_Orderly *ao)
{
    ao->pause_flag = SET;
    ao->processing_index = 0;
}


void Act_Restart( Act_Orderly *ao)
{
    ao->processing_index = 0;
    ao->pause_flag = RESET;
    ao->timer_start_flag = SET;
}


void Act_Jump_Seq( Act_Orderly *ao, uint8_t seq)
{
    Act_Restart( ao);
    for( uint8_t a = 0; a < seq; ++a)
    {
        Act_List_Analyse( ao);
        ++ao->processing_index;
    }
}


void Act_Jump_Time( Act_Orderly *ao, uint32_t time)
{
    uint32_t time_sum = 0;
    Act_Restart( ao);
    do
    {
        
        Act_List_Analyse( ao);
        ++ao->processing_index;
        time_sum += ao->processing_time;
    }
    while( time_sum < time);
}

uint8_t Act_List_Analyse( Act_Orderly *ao)
{
    //get the next action from the string
    ao->processing_action = atoi( ao->list + ao->list_process);
    //handling malformed
    if( ao->processing_action == -1 || ao->processing_action == 0)
    {
        Act_Stop( ao);
        return ACT_LIST_FORMAT_ERROR;
    }

    //find the "," and next pending subscript index
    for( ++ao->list_process; ao->list[ ao->list_process] != ','; ++ao->list_process)
    {
        if( ao->list[ ao->list_process] != '\0')
        {
            Act_Stop( ao);
            return ACT_LIST_END;
        }
    }

    //get the next latency from the string
    ao->processing_time = atoi( ao->list + ao->list_process);
    //handling malformed input
    if( ao->processing_time == -1 || ao->processing_time == 0)
    {
        Act_Stop( ao);
        return ACT_LIST_FORMAT_ERROR;
    }

    //find the ";" and next pending subscript index
    for( ++ao->list_process; ao->list[ ao->list_process] != ';'; ++ao->list_process)
    {
        if( ao->list[ ao->list_process] != '\0')
        {
            Act_Stop( ao);
            return ACT_LIST_END;            
        }

    }
    return 0;
}

void Act_Server( Act_Orderly *ao)
{
    if( ao->pause_flag == RESET)
    {
        if( ao->timer_start_flag == SET)
        {
            Timer_Set( &( ao->timer));
            ao->timer_start_flag = RESET;
        }

        if( Timer_Get( &( ao->timer)) % ao->processing_time == 0)
        {
            /*if( Act_List_Analyse( ao) == -1)
            {
                //some code to handle the malformed input
            }*/
            switch( Act_List_Analyse( ao))
            {
                case ACT_LIST_END:
                    if( ao->repeat_time++ < ao->repear_time_set)
                        Act_Restart( ao);
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



uint8_t Act_Get_progress(Act_Orderly *ao)
{
    return ao->processing_index;
}

uint8_t Act_Get_Length(Act_Orderly *ao)
{
    uint8_t cnt = 0;
    for( uint32_t a = 0; ao->list[a] != '\0'; ++a)
    {
        if( ao->list[a] == ';')
            ++cnt;
    }

    return cnt;
}

void Act_Set_Repeat( Act_Orderly *ao, int32_t times)
{
    ao->repear_time_set = times;
}

int32_t Act_Get_Repeat_Time( Act_Orderly *ao)
{
    return ao->repeat_time;
}

void Act_Set_Transition( Act_Orderly *ao, uint8_t flag)
{
    ao->transition_flag = flag;
}


