#include "key.h"



void Key_Init( Key *key)
{
    key->state = KEY_STATE_UNPRESS;
    key->last_state = KEY_STATE_UNPRESS;
    key->action = KEY_ACTION_NONE;
}


//key_state is the state that has clear up the quiver
void Key_Update( Key *key, uint8_t key_state)
{
    key->last_state = key->state;
    key->state = key_state;

    if( key->last_state == KEY_STATE_UNPRESS && key->state == KEY_STATE_PRESS)
    {
        key->action = KEY_ACTION_PRESS;
    }
    if( key->last_state == KEY_STATE_PRESS && key->state == KEY_STATE_UNPRESS)
    {
        key->action = KEY_ACTION_UNPRESS;
    }
    if( key->last_state == key->state)
    {
        key->action = KEY_ACTION_NONE;
    }
}

//this function deal with the origin key state
void Key_Update_WithQuiver( Key *key, uint8_t key_state)
{
    if( key->last_state == KEY_ACTION_UNPRESS && key_state == KEY_STATE_PRESS)
    {
        key->state = KEY_STATE_PRESS;
    }
    else key->state = KEY_STATE_UNPRESS;

    if( key->last_state == KEY_STATE_PRESS && key_state == KEY_STATE_UNPRESS)
    {
        key->state = KEY_STATE_UNPRESS;
    }
    else key->state = KEY_STATE_PRESS;

    key->last_state = key_state;

    if( key->last_state == KEY_STATE_UNPRESS && key->state == KEY_STATE_PRESS)
    {
        key->action = KEY_ACTION_PRESS;
    }
    if( key->last_state == KEY_STATE_PRESS && key->state == KEY_STATE_UNPRESS)
    {
        key->action = KEY_ACTION_UNPRESS;
    }
    if( key->last_state == key->state)
    {
        key->action = KEY_ACTION_NONE;
    }
}


uint8_t Key_Get_State( Key *key)
{
    return key->state;
}


uint8_t Key_Get_Action( Key *key)
{
    return key->action;
}



