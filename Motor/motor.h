#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "../PID/pid.h"
#include "../Encoder/Absolute_Encoder.h"
#include "../Encoder/Incremental_Encoder.h"

enum ENCODER_TYPE { ABSOLUTE_ENCODER, INCREMENTAL_ENCODER};


union Encoder
{
    Absolute_Encoder absolute;
    Incremental_Encoder incremental;
};

typedef struct 
{
    PID speed_pid;
    PID position_pid;

    union Encoder encoder;

    uint32_t encoder_type;
    //uint32_t pid_type;
    //uint32_t range_mode;

    int32_t range_begin;
    int32_t range_end;

} Motor;


void Motor_Init( Motor *motor, uint32_t encoder_type);          
void Motor_Speed_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Motor_Position_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

//uint32_t Motor_Online_Test(Motor *motor);
uint32_t Motor_Stall_Test(Motor *motor);

int32_t Motor_Speed_Ctrl_Calc(Motor *motor, float speed);
int32_t Motor_Position_Ctrl_Calc(Motor *motor, float position);
void Motor_Range_Set(Motor *motor);
void Motor_Range_Calibration(Motor *motor);


//Servo
typedef struct 
{
    void ( *servo_set_func)(uint32_t );

    uint32_t origin_range_begin;
    uint32_t origin_range_end;

    int32_t range_begin;
    int32_t range_end;
} Servo;


void Motor_Servo_Init(Servo *servo, void ( *servo_set_func)(uint32_t ));
void Motor_Servo_Range_set( Servo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end);
void Motor_Servo_Set( Servo *servo, int32_t set);

#endif
