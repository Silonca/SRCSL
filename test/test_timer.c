#include <stdio.h>

#include "../source/auxilliary/timer.h"


int main(void)
{
    Timer timer,cnt;
    uint32_t set_time = 0;
    timer_set(&cnt);      //timer_cnt is a static var, so get its value by this way

    while(1)
    {
        system("clr");
        timer_updata();

        printf("time_cnt:%d\n",timer_get(&cnt));
        printf("time set at: %d\n", set_time);
        switch( getchar())
        {
            case 's':timer_set( &timer);set_time = timer_get( &cnt);break;
            case 'g':printf("timer_get:%d\n",timer_get( &timer));break;
            default:printf("timer.time:%d\n",timer.time);
        }
            

    }

    return 0;
}