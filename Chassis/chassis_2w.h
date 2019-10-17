#ifndef CHASSIS_2W_H_INCLUDED
#define CHASSIS_2W_H_INCLUDED

#include <stdint.h>

#include "../Motor/motor.h"
#include "chassis.h"


typedef struct 
{
    Motor motors[2];
    float vx, vyaw;
    float vx_max, vyaw_max;
} Chassis_2w;


void Chassis_2w_Init( Chassis_2w *chassis, float vx_max, float vyaw_max);
void Chassis_2w_Motor_Init( Chassis_2w *chassis, uint32_t encoder_type); 
void Chassis_2w_Speed_PID_Init( Chassis_2w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_2w_Position_PID_Init( Chassis_2w *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);


void Chassis_2w_Ctrl( Chassis_2w *chassis, float vx, float vyaw);

void Chassis_2w_Arrive( Chassis_2w *chassis, float x, float y, float vxa_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));


#endif      