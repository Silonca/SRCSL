#include "motor.h"

void motor_init( Motor *motor, uint32_t encoder_type)
{
    motor->encoder_type = encoder_type;

}


void motor_speed_pid_init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    pid_init( &(motor->speed_pid), mode, max_out, max_iout, p, i, d);
}



void motor_position_pid_init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    pid_init( &(motor->position_pid), mode, max_out, max_iout, p, i, d);
}

void motor_rotation_func_init( Motor *motor, void ( *motor_rotation_func)(float pid_out))
{
    motor->motor_rotation_func = motor_rotation_func;
}

uint32_t motor_stall_test(Motor *motor)
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



int32_t motor_speed_ctrl_calc(Motor *motor, float speed)
{
    float get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        get = absolute_encoder_get_d_value( &(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        get = incremental_encoder_get_d_value( &(motor->encoder.incremental));
    }
    return pid_calc( &(motor->speed_pid), get, speed);
}


int32_t motor_position_ctrl_calc(Motor *motor, float position)
{
    float speed_get, position_get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        speed_get = absolute_encoder_get_d_value( &(motor->encoder.absolute));
        position_get = absolute_encoder_get_angle_abs(&(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        speed_get = incremental_encoder_get_d_value( &(motor->encoder.incremental));
        position_get = incremental_encoder_get_angle_abs(&(motor->encoder.incremental));
    }

    pid_calc( &(motor->position_pid), position_get, position);
    pid_calc( &(motor->speed_pid), speed_get, motor->position_pid.out);

    return motor->speed_pid.out;
}

int32_t motor_relative_position_ctrl_calc(Motor *motor, float position)
{
    motor_position_ctrl_calc( motor, position + motor->relative_zero);
}



void motor_range_get(Motor *motor, int32_t step, void ( *motor_rotation_func)(float pid_out))
{
    if( motor->range_state == RANGE_END_OK)
        return ;

    float position_get;
    if( motor->encoder_type == ABSOLUTE_ENCODER)
    {
        position_get = absolute_encoder_get_angle_abs(&(motor->encoder.absolute));
    }
    else if( motor->encoder_type == INCREMENTAL_ENCODER)
    {
        position_get = incremental_encoder_get_angle_abs(&(motor->encoder.incremental));
    }

    if( motor->range_state == RANGE_START)
    {
        if( motor_stall_test( motor) == STALL )        
        {
            motor->range_begin = position_get;
            motor->range_state = RANGE_BEGIN_OK;

            pid_clear( &(motor->position_pid));
            pid_clear( &(motor->speed_pid));
            motor_position_ctrl_calc( motor, motor->range_begin + step);
            motor_rotation_func( motor->position_pid.out);   
            return ;
        }

        motor->range_begin = position_get - step;
        motor_position_ctrl_calc( motor, motor->range_begin);
        motor_rotation_func( motor->position_pid.out);   
               
    }
    else if( motor->range_state == RANGE_BEGIN_OK ) 
    {
        if( motor_stall_test( motor) == STALL )        
        {
            motor->range_end = position_get;
            motor->range_state = RANGE_END_OK;

            pid_clear( &(motor->position_pid));
            pid_clear( &(motor->speed_pid));
            motor_position_ctrl_calc( motor, motor->range_end - step);
            motor_rotation_func( motor->position_pid.out); 
            return ;
        }

        motor->range_end = position_get + step;
        motor_position_ctrl_calc( motor, motor->range_end);
        motor_rotation_func( motor->position_pid.out);   
    }

}

void motor_set_relative_zero( Motor *motor, int32_t zero)
{
    motor->relative_zero = zero;
}


void motor_rotation( Motor *motor)
{
    motor->motor_rotation_func( motor->speed_pid.out);
}


//---------------------------------------------

void motor_servo_init(Servo *servo, void ( *servo_set_func)(uint32_t ))
{
    servo->servo_set_func = servo_set_func;
}


void motor_servo_range_set( Servo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end)
{
    servo->origin_range_begin = origin_range_begin;
    servo->origin_range_end = origin_range_end;
    servo->range_begin = range_begin;
    servo->range_end = range_end;
}



void motor_servo_set( Servo *servo, int32_t set)
{
    int32_t temp = (float)set / (float)(servo->range_end - servo->range_begin)
                     * ( servo->origin_range_end - servo->origin_range_begin) 
                     + servo->origin_range_begin;
    servo->servo_set_func( temp);
}