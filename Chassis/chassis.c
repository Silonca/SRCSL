#include "chassis.h"


void Chassis_Init( Chassis *chassis)
{
    chassis->motor = NULL;
    chassis->motor_num = 0;
/*
    chassis->v_x = 0;
    chassis->v_y = 0;
    chassis->v_yaw = 0;
 */
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


//void Chassis_Init_Ctrl( Chassis *chassis, );


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



void Chassis_Ctrl( Chassis *chassis, float v_x, float v_y, float v_yaw)
{

}
