#include "timer.h"

static volatile uint32_t timer_cnt = 0;

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

