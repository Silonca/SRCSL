#include "led.h"

enum { SET, RESET};


void LED_Init(LED *led, void ( *led_on_func)(), void ( *led_off_func)())
{
	led->led_state = LED_SWITCH_OFF;
    led->led_on_func = led_on_func;
    led->led_off_func = led_off_func;

    led->led_off_func();
}


void LED_On(LED *led)
{
    led->led_on_func();
    led->led_state = LED_SWITCH_ON;
}


void LED_Off(LED *led)
{
    led->led_off_func();
    led->led_state = LED_SWITCH_OFF;
}


//LED开关
void LED_Ctrl( LED *led, uint32_t led_state)
{
    if( led_state == LED_SWITCH_ON)
    {
        led->led_on_func();
        led->led_state = LED_SWITCH_ON;
    }
    else if( led_state == LED_SWITCH_OFF)
    {
        led->led_off_func();
        led->led_state = LED_SWITCH_OFF;
    }

}



//LED状态翻转
void LED_Ctrl_Switch(LED *led)
{
    if( led->led_state == LED_SWITCH_ON)
    {
        led->led_off_func();
        led->led_state = LED_SWITCH_OFF;
    }
    else if( led->led_state == LED_SWITCH_OFF)
    {
        led->led_on_func();
        led->led_state = LED_SWITCH_ON;
    }
}




//---------------------------------------------------------

void LEDS_Init( LEDs *leds, uint8_t sum, void ( *leds_on_func)(uint8_t index), void ( *leds_off_func)(uint8_t index))
{
    leds->led_sum = sum;
    leds->processing_sum = 0;
    leds->processing_index = 0;
    leds->processing_action = LEDS_NONE;
    leds->processing_flag = RESET;
    leds->processing_interval = 0;

    for( uint8_t temp = 0; temp < 8; ++temp)
    {
        leds->led_state[temp] = 0;
        leds->list[temp] = 0;       
    }
    
    leds->leds_on_func = leds_on_func;
    leds->leds_off_func = leds_off_func;
}


void LEDS_On( LEDs *leds, uint8_t index)
{
    leds->leds_on_func(index);
    leds->led_state[index] = LED_SWITCH_ON;
}



void LEDS_Off( LEDs *leds, uint8_t index)
{

    leds->leds_off_func(index);
    leds->led_state[index] = LED_SWITCH_OFF;

}



void LEDS_Switch( LEDs *leds, uint8_t index)
{
    if( leds->led_state[index] == LED_SWITCH_ON)
    {
        leds->leds_off_func(index);
        leds->led_state[index] = LED_SWITCH_OFF;
    }
    else if( leds->led_state[index] == LED_SWITCH_OFF)
    {
        leds->leds_on_func(index);
        leds->led_state[index] = LED_SWITCH_ON;
    } 
}


void LEDS_On_All( LEDs *leds)
{
    for( uint8_t temp = 0; temp < 8; ++temp)
    {
        leds->leds_on_func(temp);
        leds->led_state[temp] = LED_SWITCH_ON;
    }
}



void LEDS_Off_All( LEDs *leds)
{
    for( uint8_t temp = 0; temp < 8; ++temp)
    {
        leds->leds_off_func(temp);
        leds->led_state[temp] = LED_SWITCH_OFF;
    }
}



void LEDS_Switch_All( LEDs *leds)
{
    for( uint8_t temp = 0; temp < 8; ++temp)
    {
        if( leds->led_state[temp] == LED_SWITCH_ON)
        {
            leds->leds_off_func(temp);
            leds->led_state[temp] = LED_SWITCH_OFF;
        }
        else if( leds->led_state[temp] == LED_SWITCH_OFF)
        {
            leds->leds_on_func(temp);
            leds->led_state[temp] = LED_SWITCH_ON;
        }
    }
}



void LEDS_Act_Orderly( LEDs *leds, uint8_t *list, uint8_t sum, uint8_t action, uint32_t interval)
{
    for( uint8_t temp = 0; temp < sum; ++temp)
    {
        leds->list[temp] = list[temp];
    }

    leds->processing_sum = sum;
    leds->processing_flag = SET;
    leds->processing_action = action;
    leds->processing_interval = interval;
    leds->processing_index = 0;
}


void LEDS_Server( LEDs *leds)
{
    if( leds->processing_flag == SET)
    {
        Timer_Set( &(leds->timer));
        leds->processing_flag = RESET;
    }

    if( Timer_Get( &(leds->timer)) % leds->processing_interval == 0 && leds->processing_index < leds->processing_sum)
    {
        switch( leds->processing_action)
        {
            case LEDS_SWITCH_ON:
                LEDS_On( leds, leds->processing_index);
                break;
            case LEDS_SWITCH_OFF:
                LEDS_Off( leds, leds->processing_index);
                break;
            case LEDS_SWITCH:
                LEDS_Switch( leds, leds->processing_index);
                break;
        }

        ++leds->processing_index;
    }
}