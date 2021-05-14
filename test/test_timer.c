#include <stdio.h>
#include <stdlib.h>
#include "include/srcsl_timer.h"
    
static SrcslTimer t1,t2;

static void updata()
{
	srcsl_timer_updata();
	printf("updata\n");
}

static void set()
{
	srcsl_timer_set(&t1);
	printf("-----------------\n");
	printf("t1 set\n");
}

static void get()
{
	printf("t1 get:%d\n", srcsl_timer_get(&t1));
}

static void set2()
{
	srcsl_timer_set(&t2);
	printf("-----------------\n");
	printf("t2 set\n");
}

static void get2()
{
	printf("t2 get:%d\n", srcsl_timer_get(&t2));
}


int test_timer(void)
{
    
	set();
	set2();

	updata();
	updata();
	updata();
	get();
	get2();

	updata();
	updata();
	set2();

	updata();
	updata();
	get();
	get2();

	set();
	set2();

	updata();
	updata();
	updata();
	updata();

	get();
	get2();

    return 0;
}


static SrcslActionPlayer player;
static char* list = "1,1;2,2;3,0;4,0;1,2;3,4;5,6;7,8;9,10;";

static void updata_player()
{
	srcsl_timer_updata();
	srcsl_player_server(&player);
	printf("player updata\n");
}

static void act_func(int32_t code)
{
	printf("action:%d,time:%d\n", code, player.processing_time);
}
static void start() {
	srcsl_player_start(&player);
	printf("start\n");
}
static void restart() {
	srcsl_player_restart(&player);
	printf("restart\n");
}
static void stop() {
	srcsl_player_stop(&player);
	printf("stop\n");
}
static void pause() {
	srcsl_player_pause(&player);
	printf("pause\n");
}

void test_actionplayer()
{
	srcsl_player_init(&player, list, act_func);
	start();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();

	start();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	restart();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	pause();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	start();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	restart();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	stop();
	updata_player();
	updata_player();
	updata_player();
	updata_player();
	updata_player();

}


