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


void Absolute_Encoder_Init( Absolute_Encoder *encoder, uint32_t range, uint32_t angle_abs);
void Absolute_Encoder_Updata( Absolute_Encoder *encoder, uint32_t angle_abs);
uint32_t Absolute_Encoder_Get_Angle_Abs( Absolute_Encoder *encoder);
int32_t Absolute_Encoder_Get_Angle_Total( Absolute_Encoder *encoder);
int32_t Absolute_Encoder_Get_D_Value( Absolute_Encoder *encoder);
#endif
