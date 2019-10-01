#include "Incremental_Encoder.h"

void Incremental_Encoder_Init( Incremental_Encoder *encoder, uint32_t range)
{
    //encoder->angle_abs = angle_abs;
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}




void Incremental_Encoder_Updata( Incremental_Encoder *encoder, uint32_t delta)
{
    encoder->d_value = delta;
    encoder->angle_sum += encoder->d_value;

    encoder->rounds = encoder->angle_sum / encoder->range;
    encoder->angle = encoder->angle_sum % encoder->range;
}


uint32_t Incremental_Encoder_Get_Angle_Abs( Incremental_Encoder *encoder)
{
    return encoder->angle;
}

int32_t Incremental_Encoder_Get_Angle_Total( Incremental_Encoder *encoder)
{
    return encoder->angle_sum;
}

