#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


int test_timer(void)
{
    Timer timer,cnt;
    uint32_t set_time = 0;
    timer_set(&cnt);      //timer_cnt is a static var, so get its value by this way

    while(1)
    {
        //system("cls");
        //timer_updata();

        printf("time_cnt:%d\n",timer_get(&cnt));
        printf("time set at: %d\n", set_time);
		printf("timer.time:%d\n", timer.time);
        switch( getchar())
        {
            case 's':timer_set( &timer);set_time = timer_get( &cnt);break;
            case 'g':printf("timer_get:%d\n",timer_get( &timer));break;
			case 'u':timer_updata(); printf("updata\n"); break;
			default:; 
        }
		
		getchar();
            

    }

    return 0;
}