#include "include/motor.h"

void motor_init( Motor *motor, Encoder *encoder, PID *speed_pid, PID *pos_pid)
{
    motor->range_begin = 0;
    motor->range_end = 0;
    motor->range_state = 0;
    motor->relative_zero = 0;

    encoder_clone( &(motor->encoder), encoder);
    pid_clone( &(motor->speed_pid), speed_pid);
    pid_clone( &(motor->position_pid), pos_pid);
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

    get = (float)encoder_get_d_value( &(motor->encoder));
    
    return (int32_t)pid_calc( &(motor->speed_pid), get, speed);
}


int32_t motor_position_ctrl_calc(Motor *motor, float position)
{
    float speed_get, position_get;

    speed_get = (float)encoder_get_d_value( &(motor->encoder));
    position_get = (float)encoder_get_angle_abs(&(motor->encoder));

    pid_calc( &(motor->position_pid), position_get, position);
    pid_calc( &(motor->speed_pid), speed_get, motor->position_pid.out);

    return (int32_t)motor->speed_pid.out;
}

int32_t motor_relative_position_ctrl_calc(Motor *motor, float position)
{
    return motor_position_ctrl_calc( motor, position + motor->relative_zero);
}



void motor_range_get(Motor *motor, int32_t step)
{
    if( motor->range_state == RANGE_END_OK)
        return ;

    float position_get;

    position_get = (float)encoder_get_angle_abs(&(motor->encoder));
    

    if( motor->range_state == RANGE_START)
    {
        if( motor_stall_test( motor) == STALL )        
        {
            motor->range_begin = (int32_t)position_get;
            motor->range_state = RANGE_BEGIN_OK;

            pid_clear( &(motor->position_pid));
            pid_clear( &(motor->speed_pid));
            motor_position_ctrl_calc( motor, (float)(motor->range_begin + step));
            motor->motor_rotation_func( motor->position_pid.out);   
            return ;
        }

        motor->range_begin = (int32_t)position_get - step;
        motor_position_ctrl_calc( motor, (float)motor->range_begin);
        motor->motor_rotation_func( motor->position_pid.out);   
               
    }
    else if( motor->range_state == RANGE_BEGIN_OK ) 
    {
        if( motor_stall_test( motor) == STALL )        
        {
            motor->range_end = (int32_t)position_get;
            motor->range_state = RANGE_END_OK;

            pid_clear( &(motor->position_pid));
            pid_clear( &(motor->speed_pid));
            motor_position_ctrl_calc( motor, (float)(motor->range_end - step));
            motor->motor_rotation_func( motor->position_pid.out); 
            return ;
        }

        motor->range_end = (int32_t)position_get + step;
        motor_position_ctrl_calc( motor, (float)motor->range_end);
        motor->motor_rotation_func( motor->position_pid.out);   
    }

}

void motor_set_relative_zero( Motor *motor, int32_t zero)
{
    if( motor->encoder.enocder_type == ENCODER_ABSOLUTE)
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
    int32_t temp = (int32_t)((float)set / (float)(servo->range_end - servo->range_begin)
                     * ( servo->origin_range_end - servo->origin_range_begin) 
                     + servo->origin_range_begin);
    servo->servo_set_func( temp);
}