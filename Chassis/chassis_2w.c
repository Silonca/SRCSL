#include "chassis_2w.h"


void Chassis_2w_Init( Chassis_2w *chassis, float vx_max, float vyaw_max)
{
    chassis->vx_max = vx_max;
    chassis->vyaw_max = vyaw_max;
    chassis->vx = 0;
    chassis->vyaw = 0;
}



void Chassis_2w_Motor_Init( Chassis_2w *chassis, uint32_t encoder_type);
{
    for( int a = 0; a < 2; ++a)
    {
       Motor_Init( &(chassis->motors[a]), encoder_type);
    } 
}



void Chassis_2w_Speed_PID_Init( Chassis_2w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 2; ++a)
    {
        Motor_Speed_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    } 
}




void Chassis_2w_Position_PID_Init( Chassis_2w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 2; ++a)
    {
        Motor_Position_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    }    
}


void Chassis_2w_Ctrl( Chassis_2w *chassis, float vx, float vyaw)
{
    float speed[2];

    speed[ WHEEL_2W_LEFT] = -(vx - vyaw);
    speed[ WHEEL_2W_RIGHT] = vx + vyaw;
    
    for( int a = 0; a < 2; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motors[a]), speed[a]);
    }
}




void Chassis_2w_Arrive( Chassis_2w *chassis, float x, float y, float vxa_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));
