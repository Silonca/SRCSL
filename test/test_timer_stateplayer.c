#include <stdio.h>

#include "timer.h"

enum {SET, RESET};

void act_func(uint8_t action_code)
{
    printf("action:%d\n", action_code);
}

int test_timer_stateplayer(void)
{
    uint32_t time = 0;
    StatePlayer player;
    char *list = "";
    player_init( &player, PLAYER_MODE_DOWAIT, list, act_func);
    player_start( &player);
    while(1)
    {
        char c = getchar();
        if ( c == 'q')
            break;
        if( c == 'r')
            player_restart( &player);
        if( c == 'p')
            player_pause( &player);
        if( c == 's')
            player_stop( &player);

        ++time;

        timer_updata();
        player_server( &player);

        system("clr");
        printf("time:%d\n\n",time);
        if( player.pause_flag == SET)
            printf("pause\t");
;
        printf("\n\n");
        printf("repeat_time:%d,set:%d\n",player.repeat_time, player.repear_time_set);
        printf("player_progress:%d\n", player_get_progress( &player));
        printf("player_length:%d\n", player_get_length( &player));
        printf("processing_time:%d\n",player.processing_time);
        


    }
    system("pause");

    return 0;
}



