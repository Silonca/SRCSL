#ifndef GIMBAL_H_INCLUDED
#define GIMBAL_H_INCLUDED

#include <stdint.h>

#include "motor.h"

enum GIMBAL_AXIS { GIMBAL_AXIS_YAW, GIMBAL_AXIS_PITCH, GIMBAL_AXIS_ROLL};

typedef struct
{
    Motor motors[3];
    
    float angle[3];
    float angle_limition[3];
} Gimbal;


void Gimbal_Init( Gimbal *gimbal, float yaw_limit, float pitch_limit, float roll_limit);

void Gimbal_Set_Yaw_Zero( Gimbal *gimbal, float angle);
void Gimbal_Set_Pitch_Zero( Gimbal *gimbal, float angle);
void Gimbal_Set_Roll_Zero( Gimbal *gimbal, float angle);

void Gimbal_Yaw_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Gimbal_Yaw_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Gimbal_Pitch_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Gimbal_Pitch_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Gimbal_Roll_Speed_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Gimbal_Roll_Position_PID_Init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

void Gimbal_Ctrl( Gimbal *gimbal, float angle_yaw, float angle_pitch, float angle_roll);
void Gimbal_Yaw_Ctrl( Gimbal *gimbal, float angle);
void Gimbal_Pitch_Ctrl( Gimbal *gimbal, float angle);
void Gimbal_Roll_Ctrl( Gimbal *gimbal, float angle);


#endif
