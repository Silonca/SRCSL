#ifndef CHASSIS_H_INCLUDED
#define CHASSIS_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#include "motor.h"

enum CHASSIS_4W { WHEEL_4W_LF, WHEEL_4W_LR, WHEEL_4W_RF, WHEEL_4W_RR};
enum CHASSIS_3W { WHEEL_3W_ONE, WHEEL_3W_TWO, WHEEL_3W_THREE};
enum CHASSIS_2W { WHEEL_2W_LEFT, WHEEL_2W_RIGHT};

enum CHASSIS_3W_HEADING_MODE{ WHEEL_3W_HEADING_MOTOR, WHEEL_3W_HEADING_BETWEEN_MOTOR};

enum CHASSIS_ROTATION { CHASSIS_CW, CHASSIS_CCW};

enum CHASSIS_DIRECTION { CHASSIS_FORWARD, CHASSIS_REVERSE};

typedef struct 
{
    Motor *motor;
    uint8_t motor_num;

    Servo *servo;
    uint8_t servo_num;

    float v_x_max[2], v_y_max[2];
    float v_yaw_max[2];

} Chassis;

//Initialize chassis
void chassis_init( Chassis *chassis, Motor *motor, uint8_t motor_num, Servo *servo, uint8_t servo_num);
/*void chassis_init_motor( Chassis *chassis);
void chassis_init_speed_pid( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void chassis_init_position_pid( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

void chassis_init_servo( Chassis *chassis);
*/
//set maximum velocity
void chassis_set_v_max( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);
void chassis_set_v_max_reverse( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);               //Please use function Chassis_Set_V_Max() first, it will cover the effect.


//inititialize certain motor of chassis
//void chassis_motor_init( Chassis *chassis, uint8_t motor_code, uint32_t encoder_type);
//void chassis_motor_init_speed_pid( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
//void chassis_motor_init_position_pid( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d);


//chassis control calc functions
void chassis_ctrl_calc_2w( Chassis *chassis, float vx, float vyaw);

void chassis_ctrl_calc_3w_omni( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw);
void chassis_ctrl_calc_3w_omni_headless( Chassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle);

void chassis_ctrl_calc_4w_regular( Chassis *chassis, float vx, float vyaw);
void chassis_ctrl_calc_4w_mecanum( Chassis *chassis, float vx, float vy, float vyaw);
void chassis_ctrl_calc_4w_omni( Chassis *chassis, float vx, float vy, float vyaw);
void chassis_ctrl_calc_4w_mecanum_headless( Chassis *chassis, float vx, float vy, float vyaw, float angle);
void chassis_ctrl_calc_4w_omni_headless( Chassis *chassis, float vx, float vy, float vyaw, float angle);
void chassis_ctrl_calc_4w_mecanum_off_center( Chassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate);

void chassis_ctrl_calc_car( Chassis *chassis, float v, float caster_angle);

//void chassis_arrive( Chassis *chassis, float x, float y, float vxa_max, float vayaw_max, int32_t ( *isArrived)(float x,float y));

#ifdef __cplusplus
}
#endif

#endif
