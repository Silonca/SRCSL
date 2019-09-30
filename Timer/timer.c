#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <stdint.h>

typedef struct
{
    uint32_t time;
} Timer;


void Timer_Updata();                                                    //Please run this function in 1000Hz
void Timer_Set( Timer *timer);                                          //Run this function to start a timer
uint32_t Timer_Get( Timer *timer);                                      //Run this function to get the time from Timer_Set() till now






#endif
