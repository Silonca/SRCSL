#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#include <stdint.h>

enum PID_MODE
{
    PID_POSITION,
    PID_DELTA
};




typedef struct
{
    uint8_t PID_mode;

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



void  PID_Init( PID *pid, uint8_t mode, float max_out, float max_iout, float p, float i, float d);	
void  PID_Clear( PID *pid);				
float PID_Calc( PID *pid, float get, float set);																					
void  PID_Reset( PID *pid, float kp, float ki, float kd);																			

void PID_Set_MaxError( PID *pid, float max_error);                  
void PID_Set_DeadBand( PID *pid, float deadband);



#endif // PID_H_INCLUDED
