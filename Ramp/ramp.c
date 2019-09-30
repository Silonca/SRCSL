#include "ramp.h"


static volatile uint32_t ramp_cnt = 0;		


void Ramp_Updata()
{
	++ramp_cnt;
}


void Ramp_Set( Ramp *ramp)
{
	ramp->time = ramp_cnt;
}




float Ramp_Calc( Ramp *ramp, u32 time, u8 dir)
{
	uint32_t diff;
	
	diff = ramp_cnt - ramp->time;
	ramp->time = ramp_cnt;
	
	switch( dir)
	{
		case RAMP_UP:
			ramp->ramp_out += ( float)diff / ( float)time;
		break;
		case RAMP_DOWN:
			ramp->ramp_out -= ( float)diff / ( float)time;
		break;
	}
	
	
	if( ramp->ramp_out > 1.0f)
	{
		ramp->ramp_out = 1.0f;
		return 1.0f;	
	}
	if( ramp->ramp_out < 0.0f)
	{
		ramp->ramp_out = 0.0f;
		return 0.0f;
	}
		
	return ramp->ramp_out;
	

}





