#include "chassis_4w.h"


void Chassis_4w_Init( Chassis_4w *chassis, float w, float l, float vx_max, float vy_max, float vyaw_max)
{
    chassis->chassis_width = w;
    chassis->chassis_length = l;
    chassis->vx_max = vx_max;
    chassis->vy_max = vy_max;
    chassis->vyaw_max = vyaw_max;
    chassis->vx = 0;
    chassis->vy = 0;
    chassis->vyaw = 0;
}


void Chassis_4w_Motor_Init( Chassis_4w *chassis, uint32_t encoder_type)
{
    for( int a = 0; a < 4; ++a)
    {
       Motor_Init( &(chassis->motors[a]), encoder_type);
    } 
}


void Chassis_4w_Speed_PID_Init( Chassis_4w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    } 
}
void Chassis_4w_Position_PID_Init( Chassis_4w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 4; ++a)
    {
        Motor_Position_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    }
}


void Chassis_4w_Regular_Ctrl( Chassis_4w *chassis, float vx, float vyaw)
{
    float speed[4];

    speed[ WHEEL_4W_LF] = -(vx - vyaw);
    speed[ WHEEL_4W_LR] = -(vx - vyaw);
    speed[ WHEEL_4W_RF] = vx + vyaw;
    speed[ WHEEL_4W_RR] = vx + vyaw;
    
    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motors[a]), speed[a]);
    }
}


void Chassis_4w_Mecanum_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw)
{
    float speed[4];

    speed[ WHEEL_4W_LF] = vy + vx + vyaw * ( chassis->chassis_width + chassis->chassis_length);
    speed[ WHEEL_4W_LR] = -(vy - vx - vyaw * ( chassis->chassis_width + chassis->chassis_length));
    speed[ WHEEL_4W_RF] = (vy - vx + vyaw * ( chassis->chassis_width + chassis->chassis_length));
    speed[ WHEEL_4W_RR] = -(vy + vx - vyaw * ( chassis->chassis_width + chassis->chassis_length));

    for( int a = 0; a < 4; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motors[a]), speed[a]);
    }
}



void Chassis_4w_Omni_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw)
{
    Chassis_4w_Mecanum_Ctrl( chassis, vx, vy, vyaw);
}

void Chassis_4w_Arrive( Chassis_4w *chassis, float x, float y, float vxa_max, float vya_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));


