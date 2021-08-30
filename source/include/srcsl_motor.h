#ifndef SRCSL_MOTOR_H_INCLUDED
#define SRCSL_MOTOR_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

#include "srcsl_pid.h"
#include "srcsl_encoder.h"



///电机堵转状态
enum SRCSL_STALL_STATE 
{
	SRCSL_STALL,				//!< 电机堵转
	SRCSL_NOT_STALL				//!< 电机未堵转
};
///电机行程状态
enum SRCSL_RANGE_STATE 
{
	SRCSL_RANGE_NO,				//!< 行程未确定
	SRCSL_RANGE_ONEEND_OK,		//!< 行程一端已确定
	SRCSL_RANGE_OK				//!< 行程已确定
};


///电机模块
typedef struct 
{
    SrcslPID speed_pid;				//!< 电机速度环pid
    SrcslPID position_pid;			//!< 电机位置环pid

    SrcslEncoder encoder;

	int32_t out;					//!< pid计算结果

    int32_t range_begin;			//!< 行程起点（应为较小值）
    int32_t range_end;				//!< 行程终点（应为较大值）
    int32_t range_state;			//!< 行程状态

    int32_t relative_zero;			//!< 电机相对零点

    void ( *motor_rotation_func)(float srcsl_pid_out);		//!< 电机旋转函数（用于行程测定函数）

} SrcslMotor;


/**
* @brief 电机最大步进限制
* @attention 应当将计算结果付给src
* @par 例：
* @code
*	src = srcsl_motor_ctrl_step( des, src, step);
* @encode
* @param des	目标值
* @param src	当前值
* @param step	最大允许步进值
* @return 此次应当到达的值
*/
int32_t srcsl_motor_ctrl_step(int32_t des, int32_t src, int32_t step);

/**
* @brief 电机初始化（绑定编码器和pid）
* @param *motor			电机模块实例的指针
* @param *encoder		编码器实例的指针
* @param *speed_pid		速度环pid实例的指针
* @param *pos_pid		位置环pid实例的指针
*/
void srcsl_motor_init( SrcslMotor *motor, SrcslEncoder *encoder, SrcslPID *speed_pid, SrcslPID *pos_pid);  

/**
* @brief 电机编码器数据更新
* @param *motor			电机模块实例的指针
* @param angle			新的编码器数据
*/
void srcsl_motor_encoder_updata(SrcslMotor *motor, uint32_t angle);


/**
* @brief 设置相对零点（绝对角度控制时由于安装问题电机编码器零点可能不在预期位置，设置相对零点来解决这类问题）
* @param *motor	电机模块实例的指针
* @param zero	相对零点
*/
void srcsl_motor_set_relative_zero( SrcslMotor *motor, int32_t zero);


/**
* @brief 电机速度控制计算函数
* @param *motor	电机模块实例的指针
* @param speed	电机的目标速度
* @return 速度环pid输出值
*/
int32_t srcsl_motor_speed_ctrl_calc( SrcslMotor *motor, float speed);


/**
* @brief 电机位置（绝对角度）控制计算函数（会就近归位，不受零点影响）
* @param *motor		电机模块实例的指针
* @param position	电机的目标位置
* @return 双环pid输出值
*/
int32_t srcsl_motor_position_abs_ctrl_calc( SrcslMotor *motor, float position);			

/**
* @brief 电机位置（累积角度）控制计算函数
* @param *motor		电机模块实例的指针
* @param position	电机的目标位置
* @return 双环pid输出值
*/
int32_t srcsl_motor_position_sum_ctrl_calc(SrcslMotor *motor, float position);				


/**
* @brief 电机堵转检测
* @param *motor 电机模块实例的指针
*/
uint32_t srcsl_motor_stall_test(SrcslMotor *motor);


/**
* @brief 电机行程设定
* @param *motor			电机模块实例的指针
* @param range_begin	电机转动范围
* @param range_end		电机转动范围
*/
void srcsl_motor_range_set(SrcslMotor *motor, int32_t range_begin, int32_t range_end);		

/**
* @brief 电机行程测量
* @param *motor	电机模块实例的指针
* @param step	测量行程时电机的步进值（控速）
*/
void srcsl_motor_range_get( SrcslMotor *motor, int32_t step);								


/**
* @brief 设定电机旋转函数（用于行程测定函数）
* @param *motor					电机模块实例的指针
* @param *motor_rotation_func	电机旋转函数
*/
void srcsl_motor_rotation_func_init(SrcslMotor *motor, void(*srcsl_motor_rotation_func)(float srcsl_pid_out));


//舵机模块
typedef struct 
{
    void ( *servo_set_func)(uint32_t );

    uint32_t origin_range_begin;
    uint32_t origin_range_end;

    int32_t range_begin;
    int32_t range_end;
} SrcslServo;


/**
* @brief 舵机模块初始化
* @param *servo				舵机实例的指针
* @param *servo_set_func	舵机驱动函数的指针
*/
void srcsl_motor_servo_init(SrcslServo *servo, void ( *servo_set_func)(uint32_t ));

/**
* @brief 舵机转动范围映射（比如将舵机的pwm信号驱动参数映射为易于理解和使用的角度值）
* @param *servo					舵机实例的指针
* @param origin_range_begin		原始范围
* @param origin_range_end		原始范围
* @param range_begin			新范围
* @param range_end				新范围
*/
void srcsl_motor_servo_range_set( SrcslServo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end);

/**
* @brief 舵机控制
* @param *servo 舵机实例的指针
* @param set	舵机应转到的位置
*/
void srcsl_motor_servo_set( SrcslServo *servo, int32_t set);

#ifdef __cplusplus
}
#endif

#endif
