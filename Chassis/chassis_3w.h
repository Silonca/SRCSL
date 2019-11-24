#ifndef CHASSIS_3w_H_INCLUDED
#define CHASSIS_3w_H_INCLUDED

#include <stdint.h>

#include "../Motor/motor.h"
#include "chassis.h"

enum CHASSIS_3W_HEADING_MODE{ WHEEL_3W_HEADING_MOTOR, WHEEL_3W_HEADING_BETWEEN_MOTOR};

typedef struct 
{
    Motor motors[3];
    uint32_t heading_mode;
    float vx,vy,vyaw;
    float vx_max,vy_max,vyaw_max;
    float chassis_width,chassis_length;
} Chassis_3w;


void Chassis_3w_Init( Chassis_3w *chassis, float w, float l, float vx_max, float vy_max, float vyaw_max);
void Chassis_3w_Motor_Init( Chassis_3w *chassis, uint32_t encoder_type); 
void Chassis_3w_Speed_PID_Init( Chassis_3w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_3w_Position_PID_Init( Chassis_3w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

//Suppose the CW dirction is the motors' default dirtion
//void Chassis_3w_Regular_Ctrl( Chassis_3w *chassis, float vx, float vyaw);
void Chassis_3w_Omni_Ctrl( Chassis_3w *chassis, uint8_t heading_mode, float vx, float vy, float vyaw);
void Chassis_3w_Omni_Headless_Ctrl( Chassis_3w *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle);
void Chassis_3w_Omni_Swing_Ctrl( Chassis_3w *chassis, float vx, float vy, float vyaw, float swing_angle);
void Chassis_3w_Omni_Rotate_Ctrl( Chassis_3w *chassis, float vx, float vy, float vyaw);

void Chassis_3w_Arrive( Chassis_3w *chassis, float x, float y, float vxa_max, float vya_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));


#endif      