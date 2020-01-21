#include "gimbal.h"



void Gimbal_Init( Gimbal *gimbal, float yaw_limit, float pitch_limit, float roll_limit)
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




void Gimbal_Set_Yaw_Zero( Gimbal *gimbal, float angle)
{
    Motor_Set_Relative_Zero( &(gimbal->motors[ GIMBAL_AXIS_YAW]), angle);
}

void Gimbal_Set_Pitch_Zero( Gimbal *gimbal, float angle)
{
    Motor_Set_Relative_Zero( &(gimbal->motors[ GIMBAL_AXIS_PITCH]), angle);
}

void Gimbal_Set_Roll_Zero( Gimbal *gimbal, float angle)
{
    Motor_Set_Relative_Zero( &(gimbal->motors[ GIMBAL_AXIS_ROLL]), angle);
}





void Gimbal_Yaw_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Speed_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_YAW]), mode, max_out, max_iout, p, i, d);
}

void Gimbal_Yaw_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Position_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_YAW]), mode, max_out, max_iout, p, i, d);
}

void Gimbal_Pitch_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Speed_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), mode, max_out, max_iout, p, i, d);
}
void Gimbal_Pitch_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Position_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), mode, max_out, max_iout, p, i, d);
}

void Gimbal_Roll_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Speed_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), mode, max_out, max_iout, p, i, d);
}

void Gimbal_Roll_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    Motor_Position_PID_Init( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), mode, max_out, max_iout, p, i, d);
}




void Gimbal_Ctrl( Gimbal *gimbal, float angle_yaw, float angle_pitch, float angle_roll)
{
    Gimbal_Yaw_Ctrl( gimbal, angle_yaw);
    Gimbal_Pitch_Ctrl( gimbal, angle_pitch);
    Gimbal_Roll_Ctrl( gimbal, angle_roll);
}
void Gimbal_Yaw_Ctrl( Gimbal *gimbal, float angle)
{
    Motor_Position_Ctrl_Calc( &( gimbal->motors[ GIMBAL_AXIS_YAW]), angle);
}
void Gimbal_Pitch_Ctrl( Gimbal *gimbal, float angle)
{
    Motor_Position_Ctrl_Calc( &( gimbal->motors[ GIMBAL_AXIS_PITCH]), angle);
}
void Gimbal_Roll_Ctrl( Gimbal *gimbal, float angle)
{
    Motor_Position_Ctrl_Calc( &( gimbal->motors[ GIMBAL_AXIS_ROLL]), angle);
}
