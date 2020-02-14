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


#define PLAYER_REPEAT_COUNTLESS -1
#define PLAYER_LIST_END -1
#define PLAYER_LIST_FORMAT_ERROR -2


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

    void ( *act_func)(uint8_t state_code);     //Must be a non-blocking function
} State_Player;


void player_init( State_Player *player, char *list, void ( *act_func)( uint8_t action_code));

void player_start( State_Player *player);                       //Start and Continue
void player_pause( State_Player *player);                       //Pause
void player_stop( State_Player *player);                        //Stop
void player_restart( State_Player *player);                     //Restart

void player_jump_seq( State_Player *player, uint8_t seq);       //Jump to a specified frame
void player_jump_time( State_Player *player, uint32_t time);    //Jump to the frame after the given time

uint8_t player_get_progress(State_Player *player);
uint8_t player_get_Length(State_Player *player);

void player_set_repeat( State_Player *player, int32_t times);
int32_t player_get_repeat_time( State_Player *player);

void player_set_transition( State_Player *player, uint8_t flag);

void player_server( State_Player *player);                      //Server Function, must run periodically



#endif
