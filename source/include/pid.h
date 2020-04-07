#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

enum PID_MODE
{
    PID_POSITION,
    PID_DELTA
};




typedef struct
{
    uint8_t pid_mode;

	float p;
    float i;
    float d;
    
    float set;						    //The target value
    float get;						    //The feedback value
	  
    float pout;							//Proportion output
    float iout;							//Integral output
    float dout;							//Differential output
    float out;                          //Total output

    float max_out;					    //Limit the max value of the output
    float max_iout;	                    //Limit the max value of the integral output
	float max_error;                    //Limit the max value of the error value
	float deadband;						//Limit the min value of the error value
	
    float error[3];						//The error value
			
    
} PID;



void  pid_init( PID *pid, uint8_t mode, float max_out, float max_iout, float p, float i, float d);	
void  pid_clear( PID *pid);				
float pid_calc( PID *pid, float get, float set);																					
void  pid_reset( PID *pid, float kp, float ki, float kd);																			

void pid_set_maxerror( PID *pid, float max_error);                  
void pid_set_deadband( PID *pid, float deadband);

void pid_clone( PID *des, PID *src);

#ifdef __cplusplus
}
#endif

#endif // PID_H_INCLUDED
