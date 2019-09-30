#ifndef INCREMENTAL_ENCODER_H_INCLUDED
#define INCREMENTAL_ENCODER_H_INCLUDED

#include <stdint.h>

typedef struct 
{
    uint32_t angle;
    int32_t angle_sum;
    int32_t rounds;  
    int32_t d_value;                   
    uint32_t range;
} Incremental_Encoder;



void Incremental_Encoder_Init( Incremental_Encoder *encoder, uint32_t range);
void Incremental_Encoder_Updata( Incremental_Encoder *encoder, uint32_t delta);
uint32_t Incremental_Encoder_Get_Angle_Abs( Incremental_Encoder *encoder);
int32_t Incremental_Encoder_Get_Angle_Total( Incremental_Encoder *encoder);



#endif
