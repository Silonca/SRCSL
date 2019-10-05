#include "Absolute_Encoder.h"

void Absolute_Encoder_Init( Absolute_Encoder *encoder, uint32_t range, uint32_t angle_abs)
{
    encoder->angle_abs = angle_abs;
    //encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}


void Absolute_Encoder_Updata( Absolute_Encoder *encoder, uint32_t angle_abs)
{
    encoder->d_value = angle_abs - encoder->angle_abs;

    //Zero-crossing detection
    if( encoder->d_value > encoder->range / 2)
    {
        encoder->d_value = encoder->d_value - encoder->range;
        encoder->rounds--;
    }
    else if( encoder->d_value < -encoder->range / 2)
    {
        encoder->d_value = encoder->d_value + encoder->range;
        encoder->rounds++;
    }

    encoder->angle_abs = angle_abs;
    //encoder->angle_sum += encoder->d_value;
}


uint32_t Absolute_Encoder_Get_Angle_Abs( Absolute_Encoder *encoder)
{
    return encoder->angle_abs;
}

int32_t Absolute_Encoder_Get_Angle_Total( Absolute_Encoder *encoder)
{
    return encoder->rounds * encoder->range + encoder->angle_abs;
}

int32_t Absolute_Encoder_Get_D_Value( Absolute_Encoder *encoder)
{
    return encoder->d_value;
}