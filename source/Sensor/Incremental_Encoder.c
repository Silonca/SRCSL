#include "incremental_encoder.h"

void incremental_encoder_init( Incremental_Encoder *encoder, uint32_t range)
{
    //encoder->angle_abs = angle_abs;
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}




void incremental_encoder_updata( Incremental_Encoder *encoder, uint32_t delta)
{
    encoder->d_value = delta;
    encoder->angle_sum += encoder->d_value;

    encoder->rounds = encoder->angle_sum / encoder->range;
    encoder->angle = encoder->angle_sum % encoder->range;
}


uint32_t incremental_encoder_get_angle_abs( Incremental_Encoder *encoder)
{
    return encoder->angle;
}

int32_t incremental_encoder_get_angle_total( Incremental_Encoder *encoder)
{
    return encoder->angle_sum;
}

int32_t incremental_encoder_get_d_value( Incremental_Encoder *encoder)
{
    return encoder->d_value;
}

