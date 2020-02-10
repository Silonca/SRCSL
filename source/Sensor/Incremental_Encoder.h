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



void incremental_encoder_init( Incremental_Encoder *encoder, uint32_t range);
void incremental_encoder_updata( Incremental_Encoder *encoder, uint32_t delta);
uint32_t incremental_encoder_get_angle_abs( Incremental_Encoder *encoder);
int32_t incremental_encoder_get_angle_total( Incremental_Encoder *encoder);
int32_t incremental_encoder_get_d_value( Incremental_Encoder *encoder);



#endif
