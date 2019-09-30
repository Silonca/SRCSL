#ifndef RAMP_H_INCLUDED
#define RAMP_H_INCLUDED

#include <stdint.h>

#define RAMP_UP		1			
#define RAMP_DOWN	2			


typedef struct
{
	uint32_t time;
	float ramp_out;
} Ramp;

void Ramp_Updata();										//Please run this function in 1000Hz
void Ramp_Set( Ramp *ramp);								//Run this to start the ramp
float Ramp_Calc( Ramp *ramp, u32 time, u8 dir);			//Run this to get the ramp value( the unit of time is ms)


#endif

