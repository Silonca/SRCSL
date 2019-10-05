#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#include "Absolute_Encoder.h"
#include "Incremental_Encoder.h"



typedef struct 
{
    uint32_t encoder_type;

    uint32_t angle;
    int32_t angle_sum;
    int32_t rounds;  
    int32_t d_value;                   
    uint32_t range;
} Encoder;


void Encoder_Init( Encoder *encoder, uint32_t range);
void Encoder_Updata( Encoder *encoder, uint32_t delta);
uint32_t Encoder_Get_Angle_Abs( Encoder *encoder);
int32_t Encoder_Get_Angle_Total( Encoder *encoder);

void Incremental_Encoder_Init( Incremental_Encoder *encoder, uint32_t range);
void Incremental_Encoder_Updata( Incremental_Encoder *encoder, uint32_t delta);
uint32_t Incremental_Encoder_Get_Angle_Abs( Incremental_Encoder *encoder);
int32_t Incremental_Encoder_Get_Angle_Total( Incremental_Encoder *encoder);

void Absolute_Encoder_Init( Absolute_Encoder *encoder, uint32_t range, uint32_t angle_abs);
void Absolute_Encoder_Updata( Absolute_Encoder *encoder, uint32_t angle_abs);
uint32_t Absolute_Encoder_Get_Angle_Abs( Absolute_Encoder *encoder);
int32_t Absolute_Encoder_Get_Angle_Total( Absolute_Encoder *encoder);





#endif
