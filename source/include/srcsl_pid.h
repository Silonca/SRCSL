#ifndef SRCSL_PID_H_INCLUDED
#define SRCSL_PID_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"
#include "srcsl_timer.h"

/// pid计算模式
enum SRCSL_PID_MODE
{
    SRCSL_PID_POSITION,					//!< 位置式pid
    SRCSL_PID_DELTA						//!< 增量式pid
};



///pid模块
typedef struct
{
    uint8_t srcsl_pid_mode;				//!< pid计算模式

	float p;							//!< 比例
    float i;							//!< 积分
    float d;							//!< 微分
    
    float set;						    //!< 目标值
    float get;						    //!< 反馈值
	  
    float pout;							//!< 比例项输出
    float iout;							//!< 积分项输出
    float dout;							//!< 微分项输出
    float out;                          //!< 总输出

    float max_out;					    //!< 限制输出的最大值
    float max_iout;	                    //!< 限制积分项输出的最大值
	float max_error;                    //!< 限制误差的最大值
	float deadband;						//!< 死区大小（限制误差的最小值）
	
    float error[3];						//!< 历史误差值
			
} SrcslPID;


/**
* @brief pid模块初始化
* @param *pid		pid模块实例的指针
* @param mode		pid工作模式
* - SRCSL_PID_POSITION	位置式pid
* - SRCSL_PID_DELTA		增量式pid
* @param max_out	最大输出
* @param max_iout	积分项最大输出
* @param p,i,d		p，i，d的值
*/
void  srcsl_pid_init( SrcslPID *pid, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

/**
* @brief 将pid实例的计算结果清空
* @param *pid pid模块实例的指针
*/
void  srcsl_pid_clear( SrcslPID *pid);

/**
* @brief pid计算
* @param *pid	pid模块实例的指针
* @param get	获取值
* @param set	设定值
* @return pid计算结果
*/
float srcsl_pid_calc( SrcslPID *pid, float get, float set);

/**
* @brief 重新设定pid参数
* @param *pid	pid模块实例的指针
* @param p,i,d	p，i，d的值
*/
void  srcsl_pid_reset( SrcslPID *pid, float p, float i, float d);																			


/**
* @brief 设置允许的最大差值
* @param *pid		pid模块实例的指针
* @param max_error	允许的最大差值（两次获取值的差值不可能突变）
*/
void srcsl_pid_set_maxerror( SrcslPID *pid, float max_error);  

/**
* @brief 设置pid死区时间
* @param *pid pid模块实例的指针
* @param deadband 死区的大小
*/
void srcsl_pid_set_deadband( SrcslPID *pid, float deadband);

/**
* @brief 克隆pid（将参数复制给另一个pid实例）
* @param *des 复制的目标
* @param *scr 复制的来源
*/
void srcsl_pid_clone( SrcslPID *des, SrcslPID *src);



#ifdef __cplusplus
}
#endif

#endif // SRCSL_PID_H_INCLUDED
