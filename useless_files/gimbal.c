#include "gimbal.h"



void gimbal_init( Gimbal *gimbal, float yaw_limit, float pitch_limit, float roll_limit)
{
    for( int a = 0; a < 3; ++a)
    {
        gimbal->angle[a] = 0;
        gimbal->motors[a].encoder_type = ABSOLUTE_ENCODER;
    }
    gimbal->angle_limition[GIMBAL_AXIS_YAW] = yaw_limit;
    gimbal->angle_limition[GIMBAL_AXIS_PITCH] = pitch_limit;
    gimbal->angle_limition[GIMBAL_AXIS_ROLL] = roll_limit;
}




void gimbal_set_yaw_zero( Gimbal *gimbal, float angle)
{
    motor_set_relative_zero( &(gimbal->motors[ GIMBAL_AXIS_YAW]), angle);
}

void gimbal_set_pitch_zero( Gimbal *gimbal, float angle)
{
    motor_set_relative_zero( &(gimbal->motors[ GIMBAL_AXIS_PITCH]), angle);
}

void gimbal_set_roll_zero( Gimbal *gimbal, float angle)
{
    motor_set_relative_zero( &(gimbal->motors[ GIMBAL_AXIS_ROLL]), angle);
}





void gimbal_yaw_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_speed_pid_init( &( gimbal->motors[ GIMBAL_AXIS_YAW]), mode, max_out, max_iout, p, i, d);
}

void gimbal_yaw_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_position_pid_init( &( gimbal->motors[ GIMBAL_AXIS_YAW]), mode, max_out, max_iout, p, i, d);
}

void gimbal_pitch_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_speed_pid_init( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), mode, max_out, max_iout, p, i, d);
}
void gimbal_pitch_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_position_pid_init( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), mode, max_out, max_iout, p, i, d);
}

void gimbal_roll_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_speed_pid_init( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), mode, max_out, max_iout, p, i, d);
}

void gimbal_roll_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    motor_position_pid_init( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), mode, max_out, max_iout, p, i, d);
}




void gimbal_ctrl_calc( Gimbal *gimbal, float angle_yaw, float angle_pitch, float angle_roll)
{
    gimbal_yaw_ctrl_calc( gimbal, angle_yaw);
    gimbal_pitch_ctrl_calc( gimbal, angle_pitch);
    gimbal_roll_ctrl_calc( gimbal, angle_roll);
}
void gimbal_yaw_ctrl_calc( Gimbal *gimbal, float angle)
{
    motor_position_ctrl_calc( &( gimbal->motors[ GIMBAL_AXIS_YAW]), angle);
}
void gimbal_pitch_ctrl_calc( Gimbal *gimbal, float angle)
{
    motor_position_ctrl_calc( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), angle);
}
void gimbal_roll_ctrl_calc( Gimbal *gimbal, float angle)
{
    motor_position_ctrl_calc( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), angle);
}
