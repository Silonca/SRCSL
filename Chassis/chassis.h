#ifndef CHASSIS_H_INCLUDED
#define CHASSIS_H_INCLUDED

#include <stdint.h>

#include "../Motor/motor.h"

enum CHASSIS_4W { WHEEL_4W_LF, WHEEL_4W_LR, WHEEL_4W_RF, WHEEL_4W_RR};
enum CHASSIS_3W { WHEEL_3W_ONE, WHEEL_3W_TWO, WHEEL_3W_THREE};
enum CHASSIS_2W { WHEEL_2W_LEFT, WHEEL_2W_RIGHT};
enum CHASSIS_ROTATION { CHASSIS_CW, CHASSIS_CCW};

enum CHASSIS_DIRECTION { CHASSIS_FORWARD, CHASSIS_REVERSE};

typedef struct 
{
    Motor *motor;
    uint8_t motor_num;

//    float v_x, v_y;
//    float v_yaw;

    float v_x_max[2], v_y_max[2];
    float v_yaw_max[2];

    
} Chassis;

//Initialize chassis
void Chassis_Init( Chassis *chassis);
void Chassis_Init_Motor( Chassis *chassis, Motor *motor, uint8_t motor_num, uint32_t encoder_type);
void Chassis_Init_Speed_PID( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_Init_Position_PID( Chassis *chassis, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
//void Chassis_Init_Ctrl( Chassis *chassis, );

//Set maximum velocity
void Chassis_Set_V_Max( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);
void Chassis_Set_V_Max_Reverse( Chassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);               //Please use function Chassis_Set_V_Max() first, it will cover the effect.


//Inititialize certain motor of chassis
void Chassis_Motor_Init( Chassis *chassis, uint8_t motor_code, uint32_t encoder_type);
void Chassis_Motor_Init_Speed_PID( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d);
void Chassis_Motor_Init_Position_PID( Chassis *chassis, uint8_t motor_code, uint8_t mode, float max_out, float max_iout, float p, float i, float d);

void Chassis_Ctrl( Chassis *chassis, float v_x, float v_y, float v_yaw);


#endif
