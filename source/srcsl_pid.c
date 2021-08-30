/**
* @file srcsl_pid.c
* @brief pid和模糊pid自整定功能
* @author Silonca
*/

#include "include/srcsl_pid.h"

#define ABS(X)	( ( (X) > 0) ? ( X) : ( -(X)))			

//限制绝对值的最大值
#define LimitMaxAbs(input, max)		\
		{							\
			if (input > max)		\
				input = max;		\
			else if (input < -max)	\
				input = -max;		\
		}

//pid模块初始化
void srcsl_pid_init( SrcslPID *pid, uint8_t mode, float max_out, float max_iout, float p, float i, float d)
{
	pid->max_iout = max_iout;
	pid->max_out = max_out;
	pid->srcsl_pid_mode = mode;
	pid->deadband = 0;
	pid->max_error = 0;	

	srcsl_pid_reset(pid, p, i, d);
}

//重新设定pid参数
void srcsl_pid_reset( SrcslPID *pid, float p, float i, float d)
{
	pid->p = p;
	pid->i = i;
	pid->d = d;
	
	srcsl_pid_clear(pid);	
}

//将pid实例的计算结果清空
void srcsl_pid_clear( SrcslPID *pid)
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


//pid计算
float srcsl_pid_calc( SrcslPID *pid, float get, float set)
{
	//局部枚举
	enum
	{
		LLAST = 0,
		LAST = 1,
		NOW = 2,
	};


	pid->get = get;
	pid->set = set;
	pid->error[NOW] = set - get;
	
	//检测差值是否合理
	if( pid->max_error != 0 && ABS( pid->error[NOW]) > pid->max_error)
		return 0;

	//检测是否处于pid死区
	if( pid->deadband != 0 && ABS( pid->error[NOW]) < pid->deadband)
		return 0;
	
	//位置式pid
	if( pid->srcsl_pid_mode == SRCSL_PID_POSITION)
	{
		pid->pout = pid->p * pid->error[NOW];
        pid->iout += pid->i * pid->error[NOW];
        pid->dout = pid->d * (pid->error[NOW] - pid->error[LAST] );
        LimitMaxAbs(pid->iout, pid->max_iout);
        pid->out = pid->pout + pid->iout + pid->dout;
        LimitMaxAbs(pid->out, pid->max_out);	
	}
	//增量式pid
	else if(pid->srcsl_pid_mode == SRCSL_PID_DELTA)
    {
        pid->pout = pid->p * (pid->error[NOW] - pid->error[LAST]);
        pid->iout = pid->i * pid->error[NOW];
        pid->dout = pid->d * (pid->error[NOW] - 2.0f * pid->error[LAST] + pid->error[LLAST]);  
        LimitMaxAbs(pid->iout, pid->max_iout);
        pid->out += pid->pout + pid->iout + pid->dout;
        LimitMaxAbs(pid->out, pid->max_out);
    }

	//记录历史数据
	pid->error[LLAST] = pid->error[LAST];
    pid->error[LAST]  = pid->error[NOW];

    return pid->out;
}

//设置允许的最大差值
void srcsl_pid_set_maxerror( SrcslPID *pid, float max_error)             
{
	pid->max_error = max_error;
}


//设置pid死区时间
void srcsl_pid_set_deadband( SrcslPID *pid, float deadband)
{
	pid->deadband = deadband;
}


//克隆pid（将参数复制给另一个pid实例）
void srcsl_pid_clone( SrcslPID *des, SrcslPID *src)
{
	srcsl_pid_init( des, src->srcsl_pid_mode, src->max_out, src->max_iout, src->p, src->i, src->d);
	
	des->max_error = src->max_error;
	des->deadband = src->deadband;
}
