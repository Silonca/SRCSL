/**
* @file srcsl_motor.c
* @brief 电机和舵机的控制
* @author Silonca
*/
#include "include/srcsl_motor.h"

#define ABS(X)	( ( (X) > 0) ? ( X) : ( -(X)))			


int32_t srcsl_motor_ctrl_step(int32_t des, int32_t src, int32_t step)
{
	int32_t delta = des - src;
	int32_t tar;
	if (delta == 0) return 0;
	if (delta > 0) {
		tar = src + step;
		tar = tar > des ? des : tar;
	}
	else {
		tar = src - step;
		tar = tar < des ? des : tar;
	}
	return tar;
}



void srcsl_motor_init( SrcslMotor *motor, SrcslEncoder *encoder, SrcslPID *speed_pid, SrcslPID *pos_pid)
{
    motor->range_begin = 0;
    motor->range_end = 0;
    motor->range_state = SRCSL_RANGE_NO;
    motor->relative_zero = 0;

    srcsl_encoder_clone( &(motor->encoder), encoder);
    srcsl_pid_clone( &(motor->speed_pid), speed_pid);
    srcsl_pid_clone( &(motor->position_pid), pos_pid);
}



void srcsl_motor_encoder_updata(SrcslMotor * motor, uint32_t angle)
{
	srcsl_encoder_updata(&(motor->encoder), angle);
}

void srcsl_motor_set_relative_zero(SrcslMotor *motor, int32_t zero)
{
	if (motor->encoder.encoder_type == SRCSL_ENCODER_ABSOLUTE)
		motor->relative_zero = zero;
}



void srcsl_motor_rotation_func_init( SrcslMotor *motor, void ( *motor_rotation_func)(float srcsl_pid_out))
{
    motor->motor_rotation_func = motor_rotation_func;
}

uint32_t srcsl_motor_stall_test(SrcslMotor *motor)
{
	//当输出和积分项输出均大于一定比例，认为发生了堵转
    if( motor->speed_pid.out > motor->speed_pid.max_out * STALL_SRCSL_PID_OUT_RATIO 
        && motor->speed_pid.iout > motor->speed_pid.max_iout * STALL_SRCSL_PID_IOUT_RATIO)
    {
        return SRCSL_STALL;        
    }
    else
    {
        return SRCSL_NOT_STALL;
    }
        
}



int32_t srcsl_motor_speed_ctrl_calc(SrcslMotor *motor, float speed)
{
    float get = (float)srcsl_encoder_get_d_value( &(motor->encoder));
	motor->out = (int32_t)srcsl_pid_calc(&(motor->speed_pid), get, speed);
    
    return motor->out;
}


int32_t srcsl_motor_position_abs_ctrl_calc(SrcslMotor *motor, float position)
{
    float speed_get, position_get, delta;

    speed_get = (float)srcsl_encoder_get_d_value( &(motor->encoder));
    position_get = (float)srcsl_encoder_get_angle_abs(&(motor->encoder));

	//计算实际应旋转角度
	delta = position - position_get;
	delta = ABS(delta) * 2 > motor->encoder.range ? delta - motor->encoder.range : delta;
	//计算pid
    srcsl_pid_calc( &(motor->position_pid), 0, delta + motor->relative_zero);
    srcsl_pid_calc( &(motor->speed_pid), speed_get, motor->position_pid.out);

	motor->out = (int32_t)motor->speed_pid.out;
    return motor->out;
}


int32_t srcsl_motor_position_sum_ctrl_calc(SrcslMotor *motor, float position)
{
	float speed_get, position_get;

	speed_get = (float)srcsl_encoder_get_d_value(&(motor->encoder));
	position_get = (float)srcsl_encoder_get_angle_sum(&(motor->encoder));

	//行程控制
	if (motor->range_state == SRCSL_RANGE_OK)
	{
		position = position < motor->range_begin ? motor->range_begin : position;
		position = position > motor->range_end ? motor->range_end : position;
	}

	srcsl_pid_calc(&(motor->position_pid), position_get, position + motor->relative_zero);
	srcsl_pid_calc(&(motor->speed_pid), speed_get, motor->position_pid.out);

	motor->out = (int32_t)motor->speed_pid.out;
	return motor->out;
}


void srcsl_motor_range_set(SrcslMotor *motor, int32_t range_begin, int32_t range_end)
{
	motor->range_begin = range_begin;
	motor->range_end = range_end;
	motor->range_state = SRCSL_RANGE_OK;
}



void srcsl_motor_range_get(SrcslMotor *motor, int32_t step)
{
    float position_get;

    if( motor->range_state == SRCSL_RANGE_OK)
        return ;

    position_get = (float)srcsl_encoder_get_angle_abs(&(motor->encoder));
    
	//寻找行程起点
    if( motor->range_state == SRCSL_RANGE_NO)
    {
        if( srcsl_motor_stall_test( motor) == SRCSL_STALL )        
        {
			//堵转时角度为最终可达位置
            motor->range_begin = (int32_t)position_get;
            motor->range_state = SRCSL_RANGE_ONEEND_OK;

            srcsl_pid_clear( &(motor->position_pid));
            srcsl_pid_clear( &(motor->speed_pid));
			
			//反向旋转开始寻找另一端
            srcsl_motor_position_sum_ctrl_calc( motor, (float)(motor->range_begin + step));		
            motor->motor_rotation_func( motor->position_pid.out);   
            return ;
        }

        motor->range_begin = (int32_t)position_get - step;
		srcsl_motor_position_sum_ctrl_calc( motor, (float)motor->range_begin);
        motor->motor_rotation_func( motor->position_pid.out);   
               
    }
	//寻找行程终点
    else if( motor->range_state == SRCSL_RANGE_ONEEND_OK ) 
    {
        if( srcsl_motor_stall_test( motor) == SRCSL_STALL )        
        {
            motor->range_end = (int32_t)position_get;
            motor->range_state = SRCSL_RANGE_OK;

            srcsl_pid_clear( &(motor->position_pid));
            srcsl_pid_clear( &(motor->speed_pid));

			//反向旋转避免继续堵转
			srcsl_motor_position_sum_ctrl_calc( motor, (float)(motor->range_end - step));
            motor->motor_rotation_func( motor->position_pid.out); 
            return ;
        }

        motor->range_end = (int32_t)position_get + step;
		srcsl_motor_position_sum_ctrl_calc( motor, (float)motor->range_end);
        motor->motor_rotation_func( motor->position_pid.out);   
    }

}




//---------------------------------------------

void srcsl_motor_servo_init(SrcslServo *servo, void ( *servo_set_func)(uint32_t ))
{
    servo->servo_set_func = servo_set_func;
}


void srcsl_motor_servo_range_set( SrcslServo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end)
{
    servo->origin_range_begin = origin_range_begin;
    servo->origin_range_end = origin_range_end;
    servo->range_begin = range_begin;
    servo->range_end = range_end;
}



void srcsl_motor_servo_set( SrcslServo *servo, int32_t set)
{
    int32_t temp = (int32_t)((float)set / (float)(servo->range_end - servo->range_begin)
                     * ( servo->origin_range_end - servo->origin_range_begin) 
                     + servo->origin_range_begin);
    servo->servo_set_func( temp);
}