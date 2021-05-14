#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_beep.h"



void freq_set(int32_t freq)
{
	printf("freq:%d\n", freq);
}

int test_beep()
{
	SrcslBeep beeper;
	srcsl_beep_init(&beeper, freq_set, 1000);
	
	printf("beep_on\n");
	srcsl_beep_on(&beeper); 
	printf("beep_off\n");
	srcsl_beep_off(&beeper);
	printf("beep_on\n");
	srcsl_beep_on(&beeper);
	printf("beep_off\n");
	srcsl_beep_off(&beeper);
	printf("beep_switch_on\n");
	srcsl_beep_ctrl(&beeper,SRCSL_BEEP_SWITCH_ON); 
	printf("beep_switch_off\n");
	srcsl_beep_ctrl(&beeper, SRCSL_BEEP_SWITCH_OFF);
	printf("beep_switch_on\n");
	srcsl_beep_ctrl(&beeper, SRCSL_BEEP_SWITCH_ON);
	printf("beep_switch_off\n");
	srcsl_beep_ctrl(&beeper, SRCSL_BEEP_SWITCH_OFF);
	printf("beep_switch\n");
	srcsl_beep_switch(&beeper);
	printf("beep_switch\n");
	srcsl_beep_switch(&beeper);
	printf("beep_switch\n");
	srcsl_beep_switch(&beeper);
	printf("beep_switch\n");
	srcsl_beep_switch(&beeper);
	return 0;
}


static const char music_test[] =
"\
1234567\
1-2-\
1--2--\
1.2.\
1..2..\
1_2_\
1__2__\
0\
\
1*2*\
1**2**\
1/2/\
1//2//\
1#2#\
1##2##\
1b2b\
1bb2bb\
0\
\
1*-2*-\
1**--2**--\
1/_2/_\
1#.2#.\
1b..2b..\
";

SrcslBeepMusic music;

static void music_server() {
	srcsl_timer_updata();
	srcsl_music_server(&music);
	//printf("music server\n");
	//printf("freq:%d,time:%d\n",music.current_tone_freq, music.current_time*1000);
}
static void mstart() {
	srcsl_music_start(&music);
	printf("music start\n");
}
static void mstop() {
	srcsl_music_stop(&music);
	printf("music stop\n");
}
static void mrestart() {
	srcsl_music_restart(&music);
	printf("music restart\n");
}
static void mpause() {
	srcsl_music_pause(&music);
	printf("music pause\n");
}

void test_beep_music()
{
	SrcslBeep beep;

	srcsl_beep_init(&beep, freq_set, 1000);
	srcsl_music_init(&music, &beep, music_test);

	mstart();
	srcsl_music_set_deadtime(&music, 100);
	for (int a = 0; a < 10000; ++a)
		music_server();
	mrestart();
	for (int a = 0; a < 10000; ++a)
		music_server();
	mpause();
	for (int a = 0; a < 100000; ++a)
		music_server();
	mstart();
	for (int a = 0; a < 10000; ++a)
		music_server();
	mrestart();
	for (int a = 0; a < 10000; ++a)
		music_server();
	mstop();
	for (int a = 0; a < 10000; ++a)
		music_server();
	mstart();
	for (int a = 0; a < 100000; ++a)
		music_server();
}

