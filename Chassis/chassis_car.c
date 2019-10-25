#include "chassis_car.h"




void Chassis_car_Init( Chassis_car *chassis, float speed_forward_max, float speed_revering_max, float caster_angle_max)
{
    chassis->caster_angle = 0;
    chassis->caster_angle_max = caster_angle_max;
    chassis->speed = 0;
    chassis->speed_forward_max = speed_forward_max;
    chassis->speed_revering_max = speed_revering_max;
}



void Chassis_car_Motor_Init( Chassis_car *chassis, uint32_t encoder_type);
void Chassis_car_Speed_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_car_Position_PID_Init( Chassis_car *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);


void Chassis_car_Ctrl( Chassis_car *chassis, float v, float caster_angle);

void Chassis_car_Arrive( Chassis_car *chassis, float x, float y, float v_max, float caster_angle_max, int32_t ( *isArrived)(float x,float y));



