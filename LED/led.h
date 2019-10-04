#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include <stdint.h>


enum LED_STATES { LED_SWITCH_ON, LED_SWITCH_OFF};		//LED状态


typedef struct 
{
    uint32_t led_state;

    void ( *led_on_func)();
    void ( *led_off_func)();
} LED;

void LED_Init(LED led);							//LED初始化（全部关闭）
void LED_Ctrl( LED led, uint32_t led_state);	//LED控制（颜色，开关）
void LED_Ctrl_Switch(LED led);				    //LED开关状态反转





#endif // LED_H_INCLUDED
