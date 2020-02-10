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


void gimbal_init( Gimbal *gimbal, float yaw_limit, float pitch_limit, float roll_limit);

void gimbal_set_yaw_zero( Gimbal *gimbal, float angle);
void gimbal_set_pitch_zero( Gimbal *gimbal, float angle);
void gimbal_set_roll_zero( Gimbal *gimbal, float angle);

void gimbal_yaw_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void gimbal_yaw_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void gimbal_pitch_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void gimbal_pitch_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void gimbal_roll_speed_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void gimbal_roll_position_pid_init( Gimbal *gimbal, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

void gimbal_ctrl( Gimbal *gimbal, float angle_yaw, float angle_pitch, float angle_roll);
void gimbal_yaw_ctrl( Gimbal *gimbal, float angle);
void gimbal_pitch_Ctrl( Gimbal *gimbal, float angle);
void gimbal_roll_ctrl( Gimbal *gimbal, float angle);


#endif
