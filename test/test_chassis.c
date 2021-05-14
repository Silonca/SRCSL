#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_chassis.h"

SrcslChassis chassis;

//extern void motor_run(int motor_code,int32_t set);

void motor_run(int motor_code, int32_t set) {}


void test_chassis_init()
{
	SrcslMotor motor[4];
	SrcslEncoder encoder;
	SrcslPID speed_pid, pos_pid;
	srcsl_pid_init(&speed_pid, SRCSL_PID_POSITION, 10000, 5000, 10, 0, 0);
	srcsl_pid_init(&pos_pid, SRCSL_PID_POSITION, 3000, 1000, 3, 0.5, 0.5);
	srcsl_encoder_init(&encoder, SRCSL_ENCODER_ABSOLUTE, 8192);
	for (int a = 0; a < 4; ++a) {
		srcsl_motor_init(motor + a, &encoder, &speed_pid, &pos_pid);
	}
	srcsl_chassis_init(&chassis, motor, 4, NULL, 0);

}

void test_chassis_run(float x, float y, float yaw) {
	srcsl_chassis_ctrl_calc_4w_mecanum(&chassis, x, y, yaw);
	for (int a = 0; a < 4; ++a) {
		motor_run(a, chassis.motor[a].out);
	}
}

