#include "absolute_encoder.h"

void absolute_encoder_init( Absolute_Encoder *encoder, uint32_t range, uint32_t angle_abs)
{
    encoder->angle_abs = angle_abs;
    //encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}


void absolute_encoder_updata( Absolute_Encoder *encoder, uint32_t angle_abs)
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


uint32_t absolute_encoder_get_angle_abs( Absolute_Encoder *encoder)
{
    return encoder->angle_abs;
}

int32_t absolute_encoder_get_angle_total( Absolute_Encoder *encoder)
{
    return encoder->rounds * encoder->range + encoder->angle_abs;
}

int32_t absolute_encoder_get_d_value( Absolute_Encoder *encoder)
{
    return encoder->d_value;
}