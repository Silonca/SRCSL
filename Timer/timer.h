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


//----------------------------------------------------------


#define ACT_REPEAT_COUNTLESS -1
#define ACT_LIST_END -1
#define ACT_LIST_FORMAT_ERROR -2


typedef struct
{
    char *list;                                 //Frame format: action_code(1~255),latency(1~2^32)
    uint16_t list_process;

    uint8_t pause_flag;
    uint8_t timer_start_flag;
    uint8_t processing_index;                   //It seems to be useless
    uint8_t processing_action;
    uint32_t processing_time;

    Timer timer;

    int32_t repeat_time;
    int32_t repear_time_set;

    uint8_t transition_flag;

    void ( *act_func)(uint8_t action_code);     //Must be a non-blocking function
} Act_Orderly;


void Act_Init( Act_Orderly *ao, char *list, void ( *act_func)( uint8_t action_code));

void Act_Start( Act_Orderly *ao);                       //Start and Continue
void Act_Pause( Act_Orderly *ao);                       //Pause
void Act_Stop( Act_Orderly *ao);                        //Stop
void Act_Restart( Act_Orderly *ao);                     //Restart

void Act_Jump_Seq( Act_Orderly *ao, uint8_t seq);       //Jump to a specified frame
void Act_Jump_Time( Act_Orderly *ao, uint32_t time);    //Jump to the frame after the given time

uint8_t Act_Get_progress(Act_Orderly *ao);
uint8_t Act_Get_Length(Act_Orderly *ao);

void Act_Set_Repeat( Act_Orderly *ao, int32_t times);
int32_t Act_Get_Repeat_Time( Act_Orderly *ao);

void Act_Set_Transition( Act_Orderly *ao, uint8_t flag);

void Act_Server( Act_Orderly *ao);                      //Server Function, must run periodically



#endif
