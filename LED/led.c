#include "led.h"

enum { SET, RESET};


void LED_Init(LED led, void ( *led_on_func)(), void ( *led_off_func)())
{
	led.led_state = LED_SWITCH_OFF;
    led.led_on_func = led_on_func;
    led.led_off_func = led_off_func;

    led.led_off_func();
}


//LED开关
void LED_Ctrl( LED led, uint32_t led_state)
{
    if( led_state == LED_SWITCH_ON)
    {
        led.led_on_func();
        led.led_state = LED_SWITCH_ON;
    }
    else if( led_state == LED_SWITCH_OFF)
    {
        led.led_off_func();
        led.led_state = LED_SWITCH_OFF;
    }

}



//LED状态翻转
void LED_Ctrl_Switch(LED led)
{
    if( led.led_state == LED_SWITCH_ON)
    {
        led.led_off_func();
        led.led_state = LED_SWITCH_OFF;
    }
    else if( led.led_state == LED_SWITCH_OFF)
    {
        led.led_on_func();
        led.led_state = LED_SWITCH_ON;
    }
}


