#ifndef SRCSL_CHASSIS_H_INCLUDED
#define SRCSL_CHASSIS_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"
#include "srcsl_motor.h"

///四轮底盘轮子
enum SRCSL_CHASSIS_4W 
{ 
	SRCSL_WHEEL_4W_LF,		//!< 左前轮
	SRCSL_WHEEL_4W_LR, 		//!< 左后轮
	SRCSL_WHEEL_4W_RF, 		//!< 右前轮
	SRCSL_WHEEL_4W_RR		//!< 右后轮
};
///三轮底盘轮子
enum SRCSL_CHASSIS_3W 
{ 
	SRCSL_WHEEL_3W_ONE,		//!< 一号轮
	SRCSL_WHEEL_3W_TWO,		//!< 二号轮
	SRCSL_WHEEL_3W_THREE	//!< 三号轮
};
///二轮底盘轮子
enum SRCSL_CHASSIS_2W 
{ 
	SRCSL_WHEEL_2W_LEFT,	//!< 左轮
	SRCSL_WHEEL_2W_RIGHT	//!< 右轮
};

///三轮底盘正方向朝向
enum SRCSL_CHASSIS_3W_HEADING_MODE
{ 
	SRCSL_WHEEL_3W_HEADING_MOTOR,				//!< 一号轮子方向为正方向
	SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR		//!< 二三号轮子之间方向为正方向
};

///底盘旋转方向
enum SRCSL_CHASSIS_ROTATION 
{
	SRCSL_CHASSIS_CW,			//!< 顺时针方向
	SRCSL_CHASSIS_CCW			//!< 逆时针方向
};

///底盘方向
enum SRCSL_CHASSIS_DIRECTION 
{
	SRCSL_CHASSIS_FORWARD,		//!< 前进
	SRCSL_CHASSIS_REVERSE		//!< 后退
};

///底盘驱动模块
typedef struct 
{
    SrcslMotor *motor;					//!< 电机数组
    uint8_t srcsl_motor_num;			//!< 电机数量

    SrcslServo *servo;					//!< 舵机数组
    uint8_t servo_num;					//!< 舵机数量

	//暂未实际限制！！！！！
    float v_x_max[2];					//!< 前后方向最大速度，设x为前+后-
	float v_y_max[2];					//!< 左右方向最大速度，设y为左-右+
    float v_yaw_max[2];					//!< 顺+逆-

} SrcslChassis;

/**
* @brief 底盘模块初始化
* @param *chassis	底盘模块实例的指针
* @param *motor		已初始化的电机数组
* @param motor_num	电机的数量
* @param *servo		已初始化的舵机数组
* @param servo_num	舵机的数量
*/
void srcsl_chassis_init( SrcslChassis *chassis, SrcslMotor *motor, uint8_t srcsl_motor_num, SrcslServo *servo, uint8_t servo_num);

/**
* @brief 设置底盘最大速度
* @param *chassis	底盘模块实例的指针
* @param v_x_max	前进后退速度
* @param v_y_max	左移右移速度
* @param v_yaw_max	旋转速度
*/
void srcsl_chassis_set_v_max( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);

/**
* @brief 设置底盘最大逆向速度
* @attition 请在调用srcsl_chassis_set_v_max()后再调用该函数，因为它会覆盖这个函数的效果
* @param *chassis	底盘模块实例的指针
* @param v_x_max	后退速度
* @param v_y_max	左移速度
* @param v_yaw_max	逆时针旋转速度
*/
void srcsl_chassis_set_v_max_reverse( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);    


/**
* @brief 二轮底盘驱动
* @param *chassis	底盘模块实例的指针
* @param vx			前进后退速度
* @param vyaw		旋转速度
*/
void srcsl_chassis_ctrl_calc_2w( SrcslChassis *chassis, float vx, float vyaw);


/**
* @brief 三全向轮底盘
* @param *chassis		底盘模块实例的指针
* @param heading_mode	底盘前进方向模式
* - SRCSL_WHEEL_3W_HEADING_MOTOR			一号轮子方向为正方向
* - SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR	二三号轮子之间为正方向
* @param vx				前进后退速度
* @param vy				左右移动速度
* @param vyaw			旋转速度
*/
void srcsl_chassis_ctrl_calc_3w_omni( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw);

/**
* @brief 三全向轮底盘
* @param *chassis		底盘模块实例的指针
* @param heading_mode	底盘前进方向模式
* - SRCSL_WHEEL_3W_HEADING_MOTOR			一号轮子方向为初始正方向
* - SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR	二三号轮子之间为初始正方向
* @param vx				前进后退速度
* @param vy				左右移动速度
* @param vyaw			旋转速度
* @param angle			相对于正方向的角度
*/
void srcsl_chassis_ctrl_calc_3w_omni_headless( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle);

/**
* @brief 四轮底盘
* @param *chassis		底盘模块实例的指针
* @param vx				前进后退速度
* @param vyaw			旋转速度
*/
void srcsl_chassis_ctrl_calc_4w_regular( SrcslChassis *chassis, float vx, float vyaw);

/**
* @brief 四轮麦克纳姆轮底盘
* @param *chassis	底盘模块实例的指针
* @param vx			前后移动速度
* @param vy			左右移动速度
* @param vyaw		旋转速度
*/
void srcsl_chassis_ctrl_calc_4w_mecanum( SrcslChassis *chassis, float vx, float vy, float vyaw);


/**
* @brief 四轮麦克纳姆轮底盘（离心旋转）
* @param *chassis		底盘模块实例的指针
* @param vx				前后移动速度
* @param vy				左右移动速度
* @param vyaw			旋转速度
* @param width_rate		旋转中心在左右两边间的位置（比例，左边为0）
* @param length_rate	旋转中心在前后两边间的位置（比例，前边为0）
*/
void srcsl_chassis_ctrl_calc_4w_mecanum_off_center( SrcslChassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate);

/**
* @brief 四轮麦克纳姆轮底盘（无头模式）
* @param *chassis	底盘模块实例的指针
* @param vx			前后移动速度
* @param vy			左右移动速度
* @param vyaw		旋转速度
* @param angle		车身与正方向的角度
*/
void srcsl_chassis_ctrl_calc_4w_mecanum_headless( SrcslChassis *chassis, float vx, float vy, float vyaw, float angle);



/**
* @brief 汽车类底盘控制
* @param *chassis		底盘模块实例的指针
* @param v				运动速度
* @param caster_angle	转向角度
*/
void srcsl_chassis_ctrl_calc_car( SrcslChassis *chassis, float v, int32_t caster_angle);


#ifdef __cplusplus
}
#endif

#endif
