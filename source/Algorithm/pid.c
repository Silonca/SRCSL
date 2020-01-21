#include "pid.h"



#define LimitMaxAbs(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }


void PID_Init( PID *pid, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
	pid->max_iout = max_iout;
	pid->max_out = max_out;
	pid->PID_mode = mode;
	pid->deadband = 0;
	pid->max_error = 0;	

	pid->p = p;
	pid->i = i;
	pid->d = d;
	
	PID_Clear(pid);
}




void PID_Reset( PID *pid, float kp, float ki, float kd)
{
	pid->p = kp;
	pid->i = ki;
	pid->d = kd;
	
	PID_Clear(pid);	
}

void PID_Clear( PID *pid)
{
	pid->pout = 0;
	pid->iout = 0;
	pid->dout = 0;
	pid->out  = 0;

	pid->error[0] = 0;
	pid->error[1] = 0;
	pid->error[2] = 0;

	pid->get = 0;
	pid->set = 0;
}



float PID_Calc( PID *pid, float get, float set)
{
	enum
	{
		LLAST = 0,
		LAST = 1,
		NOW = 2,
	};

	if ( pid == NULL)
	{
		return 0;
	}

	pid->get = get;
	pid->set = set;

	pid->error[NOW] = set - get;
	
	if( pid->max_error != 0 && ABS( pid->error[NOW]) > pid->max_error)
		return 0;

	if( pid->deadband != 0 && ABS( pid->error[NOW]) < pid->deadband)
		return 0;
	

	if( pid->PID_mode == PID_POSITION)
	{
		pid->pout = pid->p * pid->error[NOW];
        pid->iout += pid->i * pid->error[NOW];
        pid->dout = pid->d * (pid->error[NOW] - pid->error[LAST] );
        LimitMaxAbs(pid->iout, pid->max_iout);
        pid->out = pid->pout + pid->iout + pid->dout;
        LimitMaxAbs(pid->out, pid->max_out);	
	}
	else if(pid->PID_mode == PID_DELTA)
    {
        pid->pout = pid->p * (pid->error[NOW] - pid->error[LAST]);
        pid->iout = pid->i * pid->error[NOW];
        pid->dout = pid->d * (pid->error[NOW] - 2.0f * pid->error[LAST] + pid->error[LLAST]);  
        LimitMaxAbs(pid->iout, pid->max_iout);
        pid->out += pid->pout + pid->iout + pid->dout;
        LimitMaxAbs(pid->out, pid->max_out);
    }

	pid->error[LLAST] = pid->error[LAST];
    pid->error[LAST]  = pid->error[NOW];

    return pid->out;
}



void PID_Set_MaxError( PID *pid, float max_error)             
{
	if( pid == NULL)
		return ;

	pid->max_error = max_error;
}

void PID_Set_DeadBand( PID *pid, float deadband)
{
	if( pid == NULL)
		return ;
	
	pid->deadband = deadband;
}


