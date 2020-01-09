#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include <stdint.h>

#include "../Timer/timer.h"

enum LED_STATES { LED_SWITCH_ON, LED_SWITCH_OFF};		//LED状态

enum LEDS_ACTIONS { LEDS_NONE, LEDS_SWITCH_ON, LEDS_SWITCH_OFF, LEDS_SWITCH};

typedef struct 
{
    uint32_t led_state;

    void ( *led_on_func)();
    void ( *led_off_func)();
} LED;

void LED_Init(LED *led, void ( *led_on_func)(), void ( *led_off_func)());				//LED初始化（全部关闭）
void LED_On(LED *led);
void LED_Off(LED *led);
void LED_Ctrl( LED *led, uint32_t led_state);	                                        //LED控制（颜色，开关）
void LED_Ctrl_Switch(LED *led);				                                            //LED开关状态反转

typedef struct 
{
    uint8_t led_sum;
    uint8_t led_state[8];

    uint8_t list[8];
    uint8_t processing_sum;
    uint8_t processing_index;
    uint8_t processing_action;
    uint8_t processing_flag;
    uint32_t processing_interval;

    Timer timer;

    void ( *leds_on_func)(uint8_t index);
    void ( *leds_off_func)(uint8_t index);

} LEDs;

void LEDS_Init( LEDs *leds, uint8_t sum, void ( *leds_on_func)(uint8_t index), void ( *leds_off_func)(uint8_t index));

void LEDS_On_All( LEDs *leds);
void LEDS_Off_All( LEDs *leds);
void LEDS_Switch_All( LEDs *leds);
void LEDS_On( LEDs *leds, uint8_t index);
void LEDS_Off( LEDs *leds, uint8_t index);
void LEDS_Switch( LEDs *leds, uint8_t index);
void LEDS_On_Orderly( LEDs *leds, uint8_t *list, uint8_t sum);
void LEDS_Off_Orderly( LEDs *leds, uint8_t *list, uint8_t sum);
void LEDS_Switch_Orderly( LEDs *leds, uint8_t *list, uint8_t sum);


void LEDS_Server( LEDs *leds);              //In order to support this function, you must call function Timer_Updata()
#endif // LED_H_INCLUDED
