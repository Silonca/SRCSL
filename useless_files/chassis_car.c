#include "chassis_car.h"




void Chassis_car_Init( Chassis_car *chassis, float speed_forward_max, float speed_revering_max, float caster_angle_max)
{
    chassis->caster_angle = 0;
    chassis->caster_angle_max = caster_angle_max;
    chassis->speed = 0;
    chassis->speed_forward_max = speed_forward_max;
    chassis->speed_revering_max = speed_revering_max;
}



void Chassis_car_Motor_Init( Chassis_car *chassis, uint32_t encoder_type)
{
    Motor_Init( &(chassis->motor), encoder_type);
}

void Chassis_car_Motor_Servo_Init( Chassis_car *chassis, void ( *servo_set_func)(uint32_t ), uint32_t origin_range_begin, uint32_t origin_range_end)
{
    Motor_Servo_Init( &( chassis->servo), servo_set_func);
    Motor_Servo_Range_set( &( chassis->servo), origin_range_begin,origin_range_end, -90, 90);
}

void Chassis_car_Speed_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Speed_PID_Init( &( chassis->motor), mode, max_out, max_iout, p, i, d);
}


void Chassis_car_Position_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Position_PID_Init( &( chassis->motor), mode, max_out, max_iout, p, i, d);
}


void Chassis_car_Ctrl( Chassis_car *chassis, float v, float caster_angle)
{
    Motor_Speed_Ctrl_Calc( &( chassis->motor), v);
    Motor_Servo_Set( &( chassis->servo), caster_angle);
}

void Chassis_car_Arrive( Chassis_car *chassis, float x, float y, float v_max, float caster_angle_max, int32_t ( *isArrived)(float x,float y));



