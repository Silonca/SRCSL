#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "../Algorithm/pid.h"
#include "../Sensor/Absolute_Encoder.h"
#include "../Sensor/Incremental_Encoder.h"

#define STALL_PID_OUT_RATIO  (0.7f)
#define STALL_PID_IOUT_RATIO (0.7f)

enum ENCODER_TYPE { ABSOLUTE_ENCODER, INCREMENTAL_ENCODER};
enum STALL_STATE { STALL, NOT_STALL};
enum RANGE_STATE { RANGE_START, RANGE_BEGIN_OK, RANGE_END_OK};

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

    int32_t range_begin;
    int32_t range_end;
    int32_t range_state;

    int32_t relative_zero;

    void ( *motor_rotation_func)(float pid_out);

} Motor;


void Motor_Init( Motor *motor, uint32_t encoder_type);          
void Motor_Speed_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Motor_Position_PID_Init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Motor_Rotation_Func_Init( void ( *motor_rotation_func)(float pid_out));

uint32_t Motor_Stall_Test(Motor *motor);

int32_t Motor_Speed_Ctrl_Calc(Motor *motor, float speed);
int32_t Motor_Position_Ctrl_Calc(Motor *motor, float position);
int32_t Motor_Relative_Position_Ctrl_Calc(Motor *motor, float position);

void Motor_Range_Get( Motor *motor, int32_t step);
void Motor_Set_Relative_Zero( Motor *motor, int32_t zero);

void Motor_Rotation( Motor *motor);

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
