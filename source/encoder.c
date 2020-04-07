#include "include/encoder.h"

void encoder_init( Encoder *encoder, uint32_t encoder_type, uint32_t range)
{
    encoder->enocder_type = encoder_type;
    
    //abgle_abs of absolute enocder should always be positive,for this reason, it should be initialized to a negative number to ensure it's set
    encoder->angle_abs = encoder_type == ENCODER_ABSOLUTE ? -1 : 0;         
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}

void encoder_set_angle_abs( Encoder *encoder, int32_t angle_abs)
{
    if( encoder->enocder_type == ENCODER_ABSOLUTE && encoder->angle_abs < 0)
        encoder->angle_abs = angle_abs;
}


void encoder_updata( Encoder *encoder, uint32_t angle)
{
    switch( encoder->enocder_type)
    {
        case ENCODER_ABSOLUTE:
        {
            encoder->d_value = angle - encoder->angle_abs;

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

            encoder->angle_abs = angle;
            encoder->angle_sum += encoder->d_value;               
        }break;

        
        case ENCODER_INCREMENTAL:
        {
                encoder->d_value = angle;
                encoder->angle_sum += encoder->d_value;

                encoder->rounds = encoder->angle_sum / encoder->range;
                encoder->angle_abs = encoder->angle_sum % encoder->range;
        }break;
     
    }
}


/*
void absolute_encoder_init( Encoder *encoder, uint32_t range, uint32_t angle_abs)
{
    encoder->enocder_type = ENCODER_ABSOLUTE;

    encoder->angle_abs = angle_abs;
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}


void absolute_encoder_updata( Encoder *encoder, uint32_t angle_abs)
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
    encoder->angle_sum += encoder->d_value;
}

void incremental_encoder_init( Encoder *encoder, uint32_t range)
{
    encoder->enocder_type = ENCODER_INCREMENTAL;

    encoder->angle_abs = 0;
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}




void incremental_encoder_updata( Encoder *encoder, uint32_t delta)
{
    encoder->d_value = delta;
    encoder->angle_sum += encoder->d_value;

    encoder->rounds = encoder->angle_sum / encoder->range;
    encoder->angle_abs = encoder->angle_sum % encoder->range;
}

*/

uint32_t encoder_get_angle_abs( Encoder *encoder)
{
    return encoder->angle_abs;
}

int32_t encoder_get_angle_total( Encoder *encoder)
{
    return encoder->angle_sum;
}

int32_t encoder_get_d_value( Encoder *encoder)
{
    return encoder->d_value;
}



void encoder_clone( Encoder *des, Encoder *src)
{
    encoder_init( des, src->enocder_type, src->range);
}

