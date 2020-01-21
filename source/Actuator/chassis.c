#include "chassis.h"


void Chassis_Init( Chassis *chassis)
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
}


void Chassis_Init_Motor( Chassis *chassis, Motor *motor, uint8_t motor_num, uint32_t encoder_type)
{
    chassis->motor = motor;
    chassis->motor_num = motor_num;

    for( int a = 0; a < motor_num; ++a)
    {
       Motor_Init( &(chassis->motor[a]), encoder_type);
    } 
}


void Chassis_Init_Speed_PID( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < chassis->motor_num; ++a)
    {
        Motor_Speed_PID_Init( &(chassis->motor[a]), mode, max_out, max_iout, p, i, d);
    } 
}


void Chassis_Init_Position_PID( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < chassis->motor_num; ++a)
    {
        Motor_Position_PID_Init( &(chassis->motor[a]), mode, max_out, max_iout, p, i, d);
    }   
}


void Chassis_Init_Servo( Chassis *chassis, Servo *servo, uint8_t servo_num)
{
    chassis->servo = servo;
    chassis->servo_num = servo_num;
}


void Chassis_Set_V_Max( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)
{
    chassis->v_x_max[CHASSIS_FORWARD] = v_x_max;
    chassis->v_y_max[CHASSIS_FORWARD] = v_y_max;
    chassis->v_yaw_max[CHASSIS_FORWARD] = v_yaw_max;

    chassis->v_x_max[CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[CHASSIS_REVERSE] = v_yaw_max;
}

//Please use function Chassis_Set_V_Max() first, it will cover the effect.
void Chassis_Set_V_Max_Reverse( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max)        
{
    chassis->v_x_max[CHASSIS_REVERSE] = v_x_max;
    chassis->v_y_max[CHASSIS_REVERSE] = v_y_max;
    chassis->v_yaw_max[CHASSIS_REVERSE] = v_yaw_max;
}



void Chassis_Motor_Init( Chassis *chassis, uint8_t motor_code, uint32_t encoder_type)
{
    Motor_Init( &(chassis->motor[ motor_code]), encoder_type);
}


void Chassis_Motor_Init_Speed_PID( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Speed_PID_Init( &(chassis->motor[ motor_code]), mode, max_out, max_iout, p, i, d);
}


void Chassis_Motor_Init_Position_PID( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Position_PID_Init( &(chassis->motor[ motor_code]), mode, max_out, max_iout, p, i, d);
}







void Chassis_Ctrl_2w( Chassis *chassis, float vx, float vyaw)
{
    float speed[2];

    speed[ WHEEL_2W_LEFT] = -(vx - vyaw);
    speed[ WHEEL_2W_RIGHT] = vx + vyaw;
    
    for( int a = 0; a < 2; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}

void Chassis_Ctrl_3w_Omni( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw)
{
    float speed[3];

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



    for( int a = 0; a < 3; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}


void Chassis_Ctrl_3w_Omni_Headless( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle)
{
    float speed[3];
    float v_x,v_y;

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



    for( int a = 0; a < 3; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}



void Chassis_Ctrl_4w_Regular( Chassis *chassis, float vx, float vyaw)
{
    float speed[4];

    speed[ WHEEL_4W_LF] = -(vx - vyaw);
    speed[ WHEEL_4W_LR] = -(vx - vyaw);
    speed[ WHEEL_4W_RF] = vx + vyaw;
    speed[ WHEEL_4W_RR] = vx + vyaw;
    
    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}


void Chassis_Ctrl_4w_Mecanum( Chassis *chassis, float vx, float vy, float vyaw)
{
    float speed[4];

    speed[ WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}



void Chassis_Ctrl_4w_Omni( Chassis *chassis, float vx, float vy, float vyaw)
{
    Chassis_Ctrl_4w_Mecanum( chassis, vx, vy, vyaw);
}



void Chassis_Ctrl_4w_Mecanum_Off_Center( Chassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate)
{
    float speed[4];

    if( width_rate > 1 || width_rate < 0 || length_rate > 1 || length_rate < 0)
        return ;

    speed[ WHEEL_4W_LF] = vy + vx + vyaw * sqrtf( width_rate * length_rate / 0.5f / 0.5f);
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw * sqrtf( width_rate * ( 1 - length_rate) / 0.5f / 0.5f));
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw * sqrtf( ( 1 - width_rate) * length_rate / 0.5f / 0.5f));
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw * sqrtf( ( 1- width_rate) * ( 1 - length_rate) / 0.5f / 0.5f));

    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }
}

void Chassis_Ctrl_4w_Mecanum_Headless( Chassis *chassis, float vx, float vy, float vyaw, float angle)
{
    float speed[4];
    float v_x,v_y;

    v_x = vx * cos( angle) - vy * sin( -angle);
    v_y = -vx * sin( angle) + vy * cos( -angle);

    vx = v_x;
    vy = v_y;

    speed[ WHEEL_4W_LF] = vy + vx + vyaw;
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw);
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw);
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw);

    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motor[a]), speed[a]);
    }    
}

void Chassis_Ctrl_4w_Omni_Headless( Chassis *chassis, float vx, float vy, float vyaw, float angle)
{
    Chassis_4w_Mecanum_Headless_Ctrl( chassis, vx, vy, vyaw, angle);
}



void Chassis_Ctrl_car( Chassis *chassis, float v, float caster_angle)
{
    Motor_Speed_Ctrl_Calc( &( chassis->motor[0]), v);
    Motor_Servo_Set( &( chassis->servo[0]), caster_angle);
}
