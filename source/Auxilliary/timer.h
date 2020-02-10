#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <stdint.h>



typedef struct
{
    uint32_t time;
} Timer;


void timer_updata();                                                    //Please run this function in 1000Hz
void timer_set( Timer *timer);                                          //Run this function to start a timer
uint32_t timer_get( Timer *timer);                                      //Run this function to get the time from Timer_Set() till now


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


void act_init( Act_Orderly *ao, char *list, void ( *act_func)( uint8_t action_code));

void act_start( Act_Orderly *ao);                       //Start and Continue
void act_pause( Act_Orderly *ao);                       //Pause
void act_stop( Act_Orderly *ao);                        //Stop
void act_restart( Act_Orderly *ao);                     //Restart

void act_jump_seq( Act_Orderly *ao, uint8_t seq);       //Jump to a specified frame
void act_jump_time( Act_Orderly *ao, uint32_t time);    //Jump to the frame after the given time

uint8_t act_get_progress(Act_Orderly *ao);
uint8_t act_get_Length(Act_Orderly *ao);

void act_set_repeat( Act_Orderly *ao, int32_t times);
int32_t act_get_repeat_time( Act_Orderly *ao);

void act_set_transition( Act_Orderly *ao, uint8_t flag);

void act_server( Act_Orderly *ao);                      //Server Function, must run periodically



#endif
