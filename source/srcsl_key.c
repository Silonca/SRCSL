/**
* @file srcsl_key.c
* @brief 按键模块
* @author Silonca
*/
#include "include/srcsl_key.h"


//按键模块初始化
void srcsl_key_init( SrcslKey *key)
{
    key->state = SRCSL_KEY_STATE_UNPRESS;
    key->last_real_state = SRCSL_KEY_STATE_UNPRESS;
    key->action = SRCSL_KEY_ACTION_NONE;
}


//按键更新
void srcsl_key_update( SrcslKey *key, uint8_t newstate)
{
	//两次检测到相同数值，说明按键稳定
	if (key->last_real_state == SRCSL_KEY_STATE_UNPRESS && newstate == SRCSL_KEY_STATE_UNPRESS)
	{
		key->last_state = key->state;
        key->state = SRCSL_KEY_STATE_UNPRESS;
	}
	if (key->last_real_state == SRCSL_KEY_STATE_PRESS && newstate == SRCSL_KEY_STATE_PRESS)
	{
		key->last_state = key->state;
        key->state = SRCSL_KEY_STATE_PRESS;
	}
  
    key->last_real_state = newstate;

    if( key->last_state == SRCSL_KEY_STATE_UNPRESS && key->state == SRCSL_KEY_STATE_PRESS)
    {
        key->action = SRCSL_KEY_ACTION_PRESS;
    }
    if( key->last_state == SRCSL_KEY_STATE_PRESS && key->state == SRCSL_KEY_STATE_UNPRESS)
    {
        key->action = SRCSL_KEY_ACTION_UNPRESS;
    }
    if( key->last_state == key->state)
    {
        key->action = SRCSL_KEY_ACTION_NONE;
    }
}

//获取按键状态
uint8_t srcsl_key_get_state( SrcslKey *key)
{
    return key->state;
}

//获取按键动作
uint8_t srcsl_key_get_action( SrcslKey *key)
{
    return key->action;
}



