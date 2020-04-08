#include "include/chassis.h"
#include <math.h>

void chassis_init( Chassis *chassis, Motor *motor, uint8_t motor_num, Servo *servo, uint8_t servo_num)
{
    chassis->motor = NULL;
    chassis->motor_num = 0;
    
    chassis->servo = NULL;
    chassis->servo_num = 0;

    chassis->v_x_max[CHASSIS_FORWARD] = 0;
    chassis->v_y_max[CHASSIS_FORWARD] = 0;
    chassis->v_yaw_max[CHASSIS_FORWARD] = 0;
    chassis->v_x_max[CHASSIS_REVERSE] = 0;
    chassis->v_y_max[CHASSIS_REVERSE] = 0;
    chassis->v_yaw_max[CHASSIS_REVERSE] = 0;

    chassis->motor = motor;
    chassis->motor_num = motor_num;
    chassis->servo = servo;
    chassis->servo_num = servo_num;
}


/*void chassis_init_motor( Chassis *chassis, Motor *motor, uint8_t motor_num)
{
    chassis->motor = motor;
    chassis->motor_num = motor_num;

    for( int a = 0; a < motor_num; ++a)
    {
       motor_init( &(chassis->motor[a]));
    } 
}


void chassis_init_speed_pid( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < chassis->motor_num; ++a)
    {
        motor_speed_pid_init( &(chassis->motor[a]), mode, max_out, max_iout, p, i, d);
    } 
}


void Chassis_init_position_pid( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < chassis->motor_num; ++a)
    {
        motor_position_pid_init( &(chassis->motor[a]), mode, max_out, max_iout, p, i, d);
    }   
}


void chassis_init_servo( Chassis *chassis, Servo *servo, uint8_t servo_num)
{
    chassis->servo = servo;
    chassis->servo_num = servo_num;
}
*/

void chassis_set_v_max( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)
{
    chassis->v_x_max[CHASSIS_FORWARD] = v_x_max;
    chassis->v_y_max[CHASSIS_FORWARD] = v_y_max;
    chassis->v_yaw_max[CHASSIS_FORWARD] = v_yaw_max;

    chassis->v_x_max[CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[CHASSIS_REVERSE] = v_yaw_max;
}

//Please use function Chassis_Set_V_Max() first, it will cover the effect.
void chassis_set_v_max_reverse( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)        
{
    chassis->v_x_max[CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[CHASSIS_REVERSE] = v_yaw_max;
}


/*
void chassis_motor_init( Chassis *chassis, uint8_t motor_code, uint32_t encoder_type)
{
    motor_init( &(chassis->motor[ motor_code]), encoder_type);
}
*/

void chassis_motor_init_speed_pid( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    pid_init( &(chassis->motor[ motor_code].speed_pid), mode, max_out, max_iout, p, i, d);
}


void chassis_motor_init_position_pid( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    pid_init( &(chassis->motor[ motor_code].position_pid), mode, max_out, max_iout, p, i, d);
}







void chassis_ctrl_calc_2w( Chassis *chassis, float vx, float vyaw)
{
    float speed[2];
    int a;

    speed[ WHEEL_2W_LEFT] = -(vx - vyaw);
    speed[ WHEEL_2W_RIGHT] = vx + vyaw;
    
    for( a = 0; a < 2; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}

void chassis_ctrl_calc_3w_omni( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw)
{
    float speed[3];
    int a;

    //untested !!!
    if( heading_mode == WHEEL_3W_HEADING_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);        
    }
    else if( heading_mode == WHEEL_3W_HEADING_BETWEEN_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);    
    }



    for( a = 0; a < 3; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}


void chassis_ctrl_calc_3w_omni_headless( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle)
{
    float speed[3];
    float v_x,v_y;
    int a;

    v_x = vx * cos( angle) - vy * sin( -angle);
    v_y = -vx * sin( angle) + vy * cos( -angle);

    vx = v_x;
    vy = v_y;

    //untested !!!
    if( heading_mode == WHEEL_3W_HEADING_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);        
    }
    else if( heading_mode == WHEEL_3W_HEADING_BETWEEN_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);    
    }



    for( a = 0; a < 3; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}



void chassis_ctrl_calc_4w_regular( Chassis *chassis, float vx, float vyaw)
{
    float speed[4];
    int a;

    speed[ WHEEL_4W_LF] = -(vx - vyaw);
    speed[ WHEEL_4W_LR] = -(vx - vyaw);
    speed[ WHEEL_4W_RF] = vx + vyaw;
    speed[ WHEEL_4W_RR] = vx + vyaw;
    
    for( a = 0; a < 4; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}


void chassis_ctrl_calc_4w_mecanum( Chassis *chassis, float vx, float vy, float vyaw)
{
    float speed[4];
    int a;

    speed[ WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( a = 0; a < 4; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}



void chassis_ctrl_calc_4w_omni( Chassis *chassis, float vx, float vy, float vyaw)
{
    chassis_ctrl_calc_4w_mecanum( chassis, vx, vy, vyaw);
}



void chassis_ctrl_calc_4w_mecanum_off_center( Chassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate)
{
    float speed[4];
    int a;

    if( width_rate > 1 || width_rate < 0 || length_rate > 1 || length_rate < 0)
        return ;

    speed[ WHEEL_4W_LF] = vy + vx + vyaw * sqrtf( width_rate * length_rate / 0.5f / 0.5f);
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw * sqrtf( width_rate * ( 1 - length_rate) / 0.5f / 0.5f));
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw * sqrtf( ( 1 - width_rate) * length_rate / 0.5f / 0.5f));
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw * sqrtf( ( 1- width_rate) * ( 1 - length_rate) / 0.5f / 0.5f));

    for( a = 0; a < 4; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }
}

void chassis_ctrl_calc_4w_mecanum_headless( Chassis *chassis, float vx, float vy, float vyaw, float angle)
{
    float speed[4];
    float v_x,v_y;
    int a;

    v_x = vx * cos( angle) - vy * sin( -angle);
    v_y = -vx * sin( angle) + vy * cos( -angle);

    vx = v_x;
    vy = v_y;

    speed[ WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( a = 0; a < 4; ++a)
    {
        motor_speed_ctrl_calc( &( chassis->motor[a]), speed[a]);
    }    
}

void chassis_ctrl_calc_4w_omni_headless( Chassis *chassis, float vx, float vy, float vyaw, float angle)
{
	chassis_ctrl_calc_4w_mecanum_headless( chassis, vx, vy, vyaw, angle);
}



void chassis_ctrl_calc_car( Chassis *chassis, float v, float caster_angle)
{
    motor_speed_ctrl_calc( &( chassis->motor[0]), v);
    motor_servo_set( &( chassis->servo[0]), caster_angle);
}
