#ifndef SRCSL_KEY_H_INCLUDED
#define SRCSL_KEY_H_INCLUDED


#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

///按键状态
enum SRCSL_KEY_STATE 
{
	SRCSL_KEY_STATE_PRESS,			//!< 按键按下状态
	SRCSL_KEY_STATE_UNPRESS			//!< 按键抬起状态
};
///按键动作
enum SRCSL_KEY_ACTION 
{
	SRCSL_KEY_ACTION_NONE,			//!< 按键无动作
	SRCSL_KEY_ACTION_PRESS,			//!< 按键按下动作
	SRCSL_KEY_ACTION_UNPRESS		//!< 按键抬起动作
};

///按键处理模块
typedef struct
{
    uint8_t state;					//!< 按键状态
	uint8_t last_state;				//!< 上一次的按键状态
    uint8_t action;					//!< 按键动作
    uint8_t last_real_state;		//!< 上一次的实际按键状态
} SrcslKey;

/**
* @brief 按键模块初始化
* @param *key 按键模块实例的指针
*/
void srcsl_key_init( SrcslKey *key);


/**
* @brief 按键更新（通过记录状态消抖，调用间隔应大于20ms以确保消抖效果）
* @param *key		按键模块实例的指针
* @param key_state	按键状态（从硬件获取的原始数据）
*/
void srcsl_key_update( SrcslKey *key, uint8_t newstate);

/**
* @brief 获取按键状态
* @param *key 按键模块实例的指针
*/
uint8_t srcsl_key_get_state( SrcslKey *key);

/**
* @brief 获取按键动作
* @param *key 按键模块实例的指针
*/
uint8_t srcsl_key_get_action( SrcslKey *key);


#ifdef __cplusplus
}
#endif


#endif

