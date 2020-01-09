#ifndef CHASSIS_CAR_H_INCLUDED
#define CHASSIS_CAR_H_INCLUDED

#include <stdint.h>

#include "../Motor/motor.h"
#include "chassis.h"

typedef struct 
{
    Motor motor;
    Servo servo;

    float caster_angle;
    float speed; 

    float caster_angle_max;
    float speed_forward_max, speed_revering_max;

} Chassis_car;



void Chassis_car_Init( Chassis_car *chassis, float speed_forward_max, float speed_revering_max, float caster_angle_max);
void Chassis_car_Motor_Init( Chassis_car *chassis, uint32_t encoder_type);
void Chassis_car_Motor_Servo_Init( Chassis_car *chassis, void ( *servo_set_func)(uint32_t ), uint32_t origin_range_begin, uint32_t origin_range_end);
void Chassis_car_Speed_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_car_Position_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);


void Chassis_car_Ctrl( Chassis_car *chassis, float v, float caster_angle);

void Chassis_car_Arrive( Chassis_car *chassis, float x, float y, float v_max, float caster_angle_max, int32_t ( *isArrived)(float x,float y));




#endif
