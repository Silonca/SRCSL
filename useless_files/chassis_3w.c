#include "chassis_3w.h"



void Chassis_3w_Init( Chassis_3w *chassis, float w, float l, float vx_max, float vy_max, float vyaw_max)
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


void Chassis_3w_Motor_Init( Chassis_3w *chassis, uint32_t encoder_type)
{
    for( int a = 0; a < 3; ++a)
    {
       Motor_Init( &(chassis->motors[a]), encoder_type);
    } 
}



void Chassis_3w_Speed_PID_Init( Chassis_3w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 3; ++a)
    {
        Motor_Speed_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    } 
}




void Chassis_3w_Position_PID_Init( Chassis_3w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
    for( int a = 0; a < 3; ++a)
    {
        Motor_Position_PID_Init( &(chassis->motors[a]), mode, max_out, max_iout, p, i, d);
    }
}



void Chassis_3w_Omni_Ctrl( Chassis_3w *chassis, uint8_t heading_mode, float vx, float vy, float vyaw)
{
    float speed[3];

    //untested !!!
    if( heading_mode == WHEEL_3W_HEADING_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);        
    }
    else if( heading_mode == WHEEL_3W_HEADING_BETWEEN_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);    
    }



    for( int a = 0; a < 3; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motors[a]), speed[a]);
    }
}


void Chassis_3w_Omni_Headless_Ctrl( Chassis_3w *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle)
{
    float speed[3];
    float v_x,v_y;

    v_x = vx * cos( angle) - vy * sin( -angle);
    v_y = -vx * sin( angle) + vy * cos( -angle);

    vx = v_x;
    vy = v_y;

    //untested !!!
    if( heading_mode == WHEEL_3W_HEADING_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);        
    }
    else if( heading_mode == WHEEL_3W_HEADING_BETWEEN_MOTOR)
    {
        speed[ WHEEL_3W_ONE]    = vy + vyaw;
        speed[ WHEEL_3W_TWO]    = -( 0.5f * vy - sqrt(3) / 2 * vx - vyaw);
        speed[ WHEEL_3W_THREE]  = ( 0.5f * vy - sqrt(3) / 2 * vx + vyaw);    
    }



    for( int a = 0; a < 3; ++a)
    {
        Motor_Speed_Ctrl_Calc( &( chassis->motors[a]), speed[a]);
    }
}



void Chassis_3w_Omni_Swing_Ctrl( Chassis_3w *chassis, float vx, float vy, float vyaw, float swing_angle);
void Chassis_3w_Omni_Rotate_Ctrl( Chassis_3w *chassis, float vx, float vy, float vyaw);

void Chassis_3w_Arrive( Chassis_3w *chassis, float x, float y, float vxa_max, float vya_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));
