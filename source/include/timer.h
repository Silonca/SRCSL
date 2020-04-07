#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

enum STETAPLAYER_MODE{ PLAYER_MODE_DOWAIT, PLAYER_MODE_WAITDO};


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
    uint16_t list_process;                      //character progress

    uint8_t mode;

    uint8_t pause_flag;
    uint8_t timer_start_flag;
    uint8_t processing_index;                   //segment progress
    uint32_t processing_action;
    uint32_t processing_time;

    Timer timer;

    int32_t repeat_time;
    int32_t repear_time_set;

    uint8_t transition_flag;
    uint32_t processing_action_last;

    uint8_t ( *analyse_func)( void *);
    void ( *act_func)(int32_t state_code);     //Must be a non-blocking function
} StatePlayer;


void player_init( StatePlayer *player, uint8_t mode, char *list, void ( *act_func)( uint8_t action_code));

void player_start( StatePlayer *player);                       //Start and Continue
void player_pause( StatePlayer *player);                       //Pause
void player_stop( StatePlayer *player);                        //Stop
void player_restart( StatePlayer *player);                     //Restart

void player_jump_seq( StatePlayer *player, uint8_t seq);       //Jump to a specified frame
void player_jump_time( StatePlayer *player, uint32_t time);    //Jump to the frame after the given time

uint8_t player_get_progress(StatePlayer *player);
uint8_t player_get_length(StatePlayer *player);

void player_set_repeat( StatePlayer *player, int32_t times);
int32_t player_get_repeat_time( StatePlayer *player);

void player_set_transition( StatePlayer *player, uint8_t flag);         //transition mode will turn to do_wait mode!!!

void player_server( StatePlayer *player);                      //Server Function, must run periodically

void player_set_analyse_func( StatePlayer *player, uint8_t ( *analyse_func)(void *));



#ifdef __cplusplus
}
#endif




#endif
