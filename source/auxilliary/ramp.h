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

void ramp_updata();										//please run this function in 1000hz
void ramp_set( Ramp *ramp);								//Run this to start the ramp
float ramp_calc( Ramp *ramp, uint32_t time, uint8_t dir);			//Run this to get the ramp value( the unit of time is ms)


#endif

