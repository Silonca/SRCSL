/**
* @file srcsl_chassis.c
* @brief 常见轮式底盘驱动逻辑
* @author Silonca
*/
#include "include/srcsl_chassis.h"
#include <math.h>

static const float sqrt3 = 1.732050807568877f;


void srcsl_chassis_init( SrcslChassis *chassis, SrcslMotor *motor, uint8_t motor_num, SrcslServo *servo, uint8_t servo_num)
{
    chassis->v_x_max[SRCSL_CHASSIS_FORWARD] = 0;
    chassis->v_y_max[SRCSL_CHASSIS_FORWARD] = 0;
    chassis->v_yaw_max[SRCSL_CHASSIS_FORWARD] = 0;
    chassis->v_x_max[SRCSL_CHASSIS_REVERSE] = 0;
    chassis->v_y_max[SRCSL_CHASSIS_REVERSE] = 0;
    chassis->v_yaw_max[SRCSL_CHASSIS_REVERSE] = 0;

    chassis->motor = motor;
    chassis->srcsl_motor_num = motor_num;
    chassis->servo = servo;
    chassis->servo_num = servo_num;
}


void srcsl_chassis_set_v_max( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)
{
    chassis->v_x_max[SRCSL_CHASSIS_FORWARD] = v_x_max;
    chassis->v_y_max[SRCSL_CHASSIS_FORWARD] = v_y_max;
    chassis->v_yaw_max[SRCSL_CHASSIS_FORWARD] = v_yaw_max;

    chassis->v_x_max[SRCSL_CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[SRCSL_CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[SRCSL_CHASSIS_REVERSE] = v_yaw_max;
}




void srcsl_chassis_set_v_max_reverse( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)        
{
    chassis->v_x_max[SRCSL_CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[SRCSL_CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[SRCSL_CHASSIS_REVERSE] = v_yaw_max;
}




void srcsl_chassis_ctrl_calc_2w( SrcslChassis *chassis, float vx, float vyaw)
{
    float speed[2];
    int a;

    speed[ SRCSL_WHEEL_2W_LEFT] = -(vx - vyaw);
    speed[ SRCSL_WHEEL_2W_RIGHT] = vx + vyaw;
    
    for( a = 0; a < 2; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}




void srcsl_chassis_ctrl_calc_3w_omni( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw)
{
	float speed[3] = {0};
    int a;


    //untested !!!
    if( heading_mode == SRCSL_WHEEL_3W_HEADING_MOTOR)
    {
        speed[ SRCSL_WHEEL_3W_ONE]    = vy + vyaw;
        speed[ SRCSL_WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt3 / 2 * vx - vyaw);
        speed[ SRCSL_WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt3 / 2 * vx + vyaw);        
    }
	//实际为另一个模式的反向
    else if( heading_mode == SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR)
    {
        speed[ SRCSL_WHEEL_3W_ONE]    = -(vy + vyaw);
        speed[ SRCSL_WHEEL_3W_TWO]    = ( 0.5f * vy - sqrt3 / 2 * vx - vyaw);
        speed[ SRCSL_WHEEL_3W_THREE]  = -( 0.5f * vy - sqrt3 / 2 * vx + vyaw);    
    }



    for( a = 0; a < 3; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}



void srcsl_chassis_ctrl_calc_3w_omni_headless( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle)
{
    float v_x,v_y;

    v_x = vx * cosf( angle) - vy * sinf( -angle);
    v_y = -vx * sinf( angle) + vy * cosf( -angle);

	srcsl_chassis_ctrl_calc_3w_omni(chassis, heading_mode, v_x, v_y, vyaw);
}




void srcsl_chassis_ctrl_calc_4w_regular( SrcslChassis *chassis, float vx, float vyaw)
{
    float speed[4];
    int a;

    speed[ SRCSL_WHEEL_4W_LF] = -(vx - vyaw);
    speed[ SRCSL_WHEEL_4W_LR] = -(vx - vyaw);
    speed[ SRCSL_WHEEL_4W_RF] = vx + vyaw;
    speed[ SRCSL_WHEEL_4W_RR] = vx + vyaw;
    
    for( a = 0; a < 4; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}





void srcsl_chassis_ctrl_calc_4w_mecanum( SrcslChassis *chassis, float vx, float vy, float vyaw)
{
    float speed[4];
    int a;

    speed[ SRCSL_WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ SRCSL_WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ SRCSL_WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ SRCSL_WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( a = 0; a < 4; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}




void srcsl_chassis_ctrl_calc_4w_mecanum_off_center( SrcslChassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate)
{
    float speed[4];
    int a;

    if( width_rate > 1 || width_rate < 0 || length_rate > 1 || length_rate < 0)
        return ;

    speed[ SRCSL_WHEEL_4W_LF] = vy + vx + vyaw * sqrtf( width_rate * length_rate / 0.5f / 0.5f);
    speed[ SRCSL_WHEEL_4W_LR] = -(vy - vx - vyaw * sqrtf( width_rate * ( 1 - length_rate) / 0.5f / 0.5f));
    speed[ SRCSL_WHEEL_4W_RF] = (vy - vx + vyaw * sqrtf( ( 1 - width_rate) * length_rate / 0.5f / 0.5f));
    speed[ SRCSL_WHEEL_4W_RR] = -(vy + vx - vyaw * sqrtf( ( 1- width_rate) * ( 1 - length_rate) / 0.5f / 0.5f));

    for( a = 0; a < 4; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}





void srcsl_chassis_ctrl_calc_4w_mecanum_headless( SrcslChassis *chassis, float vx, float vy, float vyaw, float angle)
{
    float speed[4];
    float v_x,v_y;
    int a;

    v_x = vx * cosf( angle) - vy * sinf( -angle);
    v_y = -vx * sinf( angle) + vy * cosf( -angle);

    vx = v_x;
    vy = v_y;

    speed[ SRCSL_WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ SRCSL_WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ SRCSL_WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ SRCSL_WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( a = 0; a < 4; ++a)
    {
        srcsl_motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }    
}





void srcsl_chassis_ctrl_calc_car( SrcslChassis *chassis, float v, int32_t caster_angle)
{
    srcsl_motor_speed_ctrl_calc( &( chassis->motor[0]), v);
    srcsl_motor_servo_set( &( chassis->servo[0]), caster_angle);
}
