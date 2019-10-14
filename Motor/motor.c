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

void Motor_Rotation_Func_Init( Motor *motor, void ( *motor_rotation_func)(float pid_out))
{
    motor->motor_rotation_func = motor_rotation_func;
}

uint32_t Motor_Stall_Test(Motor *motor)
{
    if( motor->speed_pid.out > motor->speed_pid.max_out * STALL_PID_OUT_RATIO 
        && motor->speed_pid.iout > motor->speed_pid.max_iout * STALL_PID_IOUT_RATIO)
    {
        return STALL;        
    }
    else
    {
        return NOT_STALL;
    }
        
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

int32_t Motor_Relative_Position_Ctrl_Calc(Motor *motor, float position)
{
    Motor_Position_Ctrl_Calc( motor, position + motor->relative_zero);
}



void Motor_Range_Get(Motor *motor, int32_t step, void ( *motor_rotation_func)(float pid_out))
{
    if( motor->range_state == RANGE_END_OK)
        return ;

    float position_get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        position_get = Absolute_Encoder_Get_Angle_Abs(&(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        position_get = Incremental_Encoder_Get_Angle_Abs(&(motor->encoder.incremental));
    }

    if( motor->range_state == RANGE_START)
    {
        if( Motor_Stall_Test( motor) == STALL )        
        {
            motor->range_begin = position_get;
            motor->range_state = RANGE_BEGIN_OK;

            PID_Clear( &(motor->position_pid));
            PID_Clear( &(motor->speed_pid));
            Motor_Position_Ctrl_Calc( motor, motor->range_begin + step);
            motor_rotation_func( motor->position_pid.out);   
            return ;
        }

        motor->range_begin = position_get - step;
        Motor_Position_Ctrl_Calc( motor, motor->range_begin);
        motor_rotation_func( motor->position_pid.out);   
               
    }
    else if( motor->range_state == RANGE_BEGIN_OK ) 
    {
        if( Motor_Stall_Test( motor) == STALL )        
        {
            motor->range_end = position_get;
            motor->range_state = RANGE_END_OK;

            PID_Clear( &(motor->position_pid));
            PID_Clear( &(motor->speed_pid));
            Motor_Position_Ctrl_Calc( motor, motor->range_end - step);
            motor_rotation_func( motor->position_pid.out); 
            return ;
        }

        motor->range_end = position_get + step;
        Motor_Position_Ctrl_Calc( motor, motor->range_end);
        motor_rotation_func( motor->position_pid.out);   
    }

}

void Motor_Set_Relative_Zero( Motor *motor, int32_t zero)
{
    motor->relative_zero = zero;
}


void Motor_Rotation( Motor *motor)
{
    motor->motor_rotation_func( motor->speed_pid.out);
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