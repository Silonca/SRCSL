#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "../algorithm/pid.h"
#include "../sensor/encoder.h"


#define STALL_PID_OUT_RATIO  (0.7f)
#define STALL_PID_IOUT_RATIO (0.7f)


enum STALL_STATE { STALL, NOT_STALL};
enum RANGE_STATE { RANGE_START, RANGE_BEGIN_OK, RANGE_END_OK};


typedef struct 
{
    PID speed_pid;
    PID position_pid;

    Encoder encoder;

    int32_t range_begin;
    int32_t range_end;
    int32_t range_state;

    int32_t relative_zero;

    void ( *motor_rotation_func)(float pid_out);

} Motor;


void motor_init( Motor *motor, Encoder *encoder, PID *speed_pid, PID *pos_pid);          

int32_t motor_speed_ctrl_calc( Motor *motor, float speed);
int32_t motor_position_ctrl_calc( Motor *motor, float position);
int32_t motor_relative_position_ctrl_calc( Motor *motor, float position);

uint32_t motor_stall_test(Motor *motor);

void motor_range_get( Motor *motor, int32_t step);
void motor_set_relative_zero( Motor *motor, int32_t zero);

void motor_rotation_func_init( void ( *motor_rotation_func)(float pid_out));
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
