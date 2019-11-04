#ifndef CHASSIS_4W_H_INCLUDED
#define CHASSIS_4W_H_INCLUDED

#include <stdint.h>

#include "../Motor/motor.h"
#include "chassis.h"


typedef struct 
{
    Motor motors[4];
    float vx,vy,vyaw;
    float vx_max,vy_max,vyaw_max;
} Chassis_4w;


void Chassis_4w_Init( Chassis_4w *chassis, float vx_max, float vy_max, float vyaw_max);
void Chassis_4w_Motor_Init( Chassis_4w *chassis, uint32_t encoder_type); 
void Chassis_4w_Speed_PID_Init( Chassis_4w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_4w_Position_PID_Init( Chassis_4w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

//Suppose the CW dirction is the motors' default dirtion
void Chassis_4w_Regular_Ctrl( Chassis_4w *chassis, float vx, float vyaw);
void Chassis_4w_Mecanum_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw);
void Chassis_4w_Omni_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw);

void Chassis_4w_Mecanum_Headless_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw, float angle);
void Chassis_4w_Omni_Headless_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw, float angle);

void Chassis_4w_Mecanum_Swing_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw, float swing_angle);
void Chassis_4w_Omni_Swing_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw, float swing_angle);

void Chassis_4w_Mecanum_Rotate_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw);
void Chassis_4w_Omni_Rotate_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw);

void Chassis_4w_Arrive( Chassis_4w *chassis, float x, float y, float vxa_max, float vya_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));

void Chassis_4w_Mecanum_Off_Center_Ctrl( Chassis_4w *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate);

#endif      