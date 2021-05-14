#ifndef SRCSL_TIMER_H_INCLUDED
#define SRCSL_TIMER_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

/**
* @struct SrcslTimer
* @brief 计时器
*/
typedef struct
{
    uint32_t time;			//!< 储存srcsl_timer_set的调用时间
} SrcslTimer;

/**
* @brief 更新全局时间
*/
void srcsl_timer_updata(void);                                   

/**
* @brief 计时开始
* @param 计时器模块指针
*/
void srcsl_timer_set( SrcslTimer *timer);						 

/**
* @brief 获取自开始以来的时间
* @param 计时器模块指针
* @return 上次调用srcsl_timer_set以来的时间
*/
uint32_t srcsl_timer_get( SrcslTimer *timer);					 




//-----------------------------------------------------------


enum SRCSL_PLAYER_LIST
{
	SRCSL_PLAYER_LIST_FRAME_OK,					//!< 播放器列表解析帧解析正常结束
	SRCSL_PLAYER_LIST_END,						//!< 播放器列表解析到末尾
	SRCSL_PLAYER_LIST_FORMAT_ERROR,				//!< 播放器列表解析格式错误
};


enum SRCSL_PLAYER_STATE
{
	SRCSL_PLAYER_PLAYING,						//!< 播放器正常工作中
	SRCSL_PLAYER_PAUSE,							//!< 播放器暂停
	SRCSL_PLAYER_STOP							//!< 播放器终止
};


/**
* @struct SrcslActionPlayer
* @brief 动作播放器
*/
typedef struct
{
    SrcslTimer timer;							//!< 计时器
    const char *list;                           //!< 帧格式: 动作编码(1~255),延迟(1~2^32);

    uint8_t player_state;						//!< 播放器状态
	uint8_t analyse_state;						//!< 解析状态
    uint8_t timer_flag;							//!< 计时器工作标志
    uint16_t list_process;						//!< 正在解析的字符的位置
    uint32_t processing_action;					//!< 解析的动作
    uint32_t processing_time;					//!< 解析的时间

    uint8_t ( *analyse_func)( void *);			//!< 解析list的函数
    void ( *act_func)(int32_t action_code);		//!< 执行操作的函数（必须是非堵塞型函数）
} SrcslActionPlayer;


/**
* @brief 动作播放器初始化
* @param *player	动作播放器模块指针
* @param *list		工作流程描述
* @param *act_func	执行动作的函数的指针
*/
void srcsl_player_init( SrcslActionPlayer *player, const char *list, void ( *act_func)( int32_t action_code));

/**
* @brief 动作播放解析函数设置，用于自定义解析
* @param 动作播放器模块指针
* @param 自定义的解析函数的指针
*/
void srcsl_player_set_analyse_func( SrcslActionPlayer *player, uint8_t ( *analyse_func)(void *));


/**
* @brief 动作播放器开始播放和继续播放
* @param 动作播放器模块指针
*/
void srcsl_player_start( SrcslActionPlayer *player);                       

/**
* @brief 动作播放暂停（再次开始会直接跳转到下一帧）
* @param 动作播放器模块指针
*/
void srcsl_player_pause( SrcslActionPlayer *player);                       

/**
* @brief 动作播放终止
* @param 动作播放器模块指针
*/
void srcsl_player_stop( SrcslActionPlayer *player);                        

/**
* @brief 动作播放重新开始
* @param 动作播放器模块指针
*/
void srcsl_player_restart( SrcslActionPlayer *player);                     


/**
* @brief 动作播放器服务函数，需要周期性运行
* @param 动作播放器模块指针
* @return 解析情况
* @retval SRCSL_PLAYER_LIST_FRAME_OK		 播放器列表解析帧解析正常结束
* @retval SRCSL_PLAYER_LIST_END				 播放器列表解析到末尾
* @retval SRCSL_PLAYER_LIST_FORMAT_ERROR	 播放器列表解析格式错误
*/
uint8_t srcsl_player_server( SrcslActionPlayer *player);                      

#ifdef __cplusplus
}
#endif


#endif
