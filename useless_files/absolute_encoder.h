#ifndef ABSOLUTE_ENCODER_H_INCLUDED
#define ABSOLUTE_ENCODER_H_INCLUDED

#include <stdint.h>

typedef struct
{
    uint32_t angle_abs;
    //int32_t angle_sum;
    int32_t rounds;  
    int32_t d_value;               //diffence between two angle    
    uint32_t range;      

} Absolute_Encoder;


void absolute_encoder_init( Absolute_Encoder *encoder, uint32_t range, uint32_t angle_abs);
void absolute_encoder_updata( Absolute_Encoder *encoder, uint32_t angle_abs);
uint32_t absolute_encoder_get_angle_abs( Absolute_Encoder *encoder);
int32_t absolute_encoder_get_angle_total( Absolute_Encoder *encoder);
int32_t absolute_encoder_get_d_value( Absolute_Encoder *encoder);
#endif
