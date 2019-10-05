#include "motor.h"

void Motor_Init( Motor *motor, uint32_t encoder_type)
{
    motor->encoder_type = encoder_type;

}


void Motor_Speed_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    PID_Init( &(motor->speed_pid), mode, max_out, max_iout, p, i, d);
}



void Motor_Position_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    PID_Init( &(motor->position_pid), mode, max_out, max_iout, p, i, d);
}



uint32_t Motor_Stall_Test(Motor *motor)
{

}



int32_t Motor_Speed_Ctrl_Calc(Motor *motor, float speed)
{
    float get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        get = Absolute_Encoder_Get_D_Value( &(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        get = Incremental_Encoder_Get_D_Value( &(motor->encoder.incremental));
    }
    return PID_Calc( &(motor->speed_pid), get, speed);
}


int32_t Motor_Position_Ctrl_Calc(Motor *motor, float position)
{
    float speed_get, position_get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        speed_get = Absolute_Encoder_Get_D_Value( &(motor->encoder.absolute));
        position_get = Absolute_Encoder_Get_Angle_Abs(&(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        speed_get = Incremental_Encoder_Get_D_Value( &(motor->encoder.incremental));
        position_get = Incremental_Encoder_Get_Angle_Abs(&(motor->encoder.incremental));
    }

    PID_Calc( &(motor->position_pid), position_get, position);
    PID_Calc( &(motor->speed_pid), speed_get, motor->position_pid.out);

    return motor->speed_pid.out;
}


void Motor_Range_Set(Motor *motor, int32_t begin, int32_t end)
{
    motor->range_begin = begin;
    motor->range_end = end;
    //motor->range_mode = SET;
}


void Motor_Range_Calibration(Motor *motor)
{

}



//---------------------------------------------

void Motor_Servo_Init(Servo *servo, void ( *servo_set_func)(uint32_t ))
{
    servo->servo_set_func = servo_set_func;
}


void Motor_Servo_Range_set( Servo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end)
{
    servo->origin_range_begin = origin_range_begin;
    servo->origin_range_end = origin_range_end;
    servo->range_begin = range_begin;
    servo->range_end = range_end;
}



void Motor_Servo_Set( Servo *servo, int32_t set)
{
    int32_t temp = (float)set / (float)(servo->range_end - servo->range_begin)
                     * ( servo->origin_range_end - servo->origin_range_begin) 
                     + servo->origin_range_begin;
    servo->servo_set_func( temp);
}