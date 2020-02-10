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


void motor_init( Motor *motor, uint32_t encoder_type);          
void motor_speed_pid_init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void motor_position_pid_init( Motor *motor, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void motor_rotation_func_init( void ( *motor_rotation_func)(float pid_out));

uint32_t motor_stall_test(Motor *motor);

int32_t motor_speed_ctrl_calc( Motor *motor, float speed);
int32_t motor_position_ctrl_calc( Motor *motor, float position);
int32_t motor_relative_position_ctrl_calc( Motor *motor, float position);

void motor_range_get( Motor *motor, int32_t step);
void motor_set_relative_zero( Motor *motor, int32_t zero);

void motor_rotation( Motor *motor);

//Servo
typedef struct 
{
    void ( *servo_set_func)(uint32_t );

    uint32_t origin_range_begin;
    uint32_t origin_range_end;

    int32_t range_begin;
    int32_t range_end;
} Servo;


void motor_servo_init(Servo *servo, void ( *servo_set_func)(uint32_t ));
void motor_servo_range_set( Servo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end);
void motor_servo_set( Servo *servo, int32_t set);

#endif
