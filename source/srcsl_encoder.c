/**
* @file srcsl_encoder.c
* @brief ������ģ��
* @author Silonca
*/

#include "include/srcsl_encoder.h"


//��������ʼ��
void srcsl_encoder_init( SrcslEncoder *encoder, uint32_t encoder_type, uint32_t range)
{
    encoder->encoder_type = encoder_type;
    
    encoder->angle_abs = 0;         
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}


//���ñ��������ԽǶ�
void srcsl_encoder_set_angle_abs( SrcslEncoder *encoder, int32_t angle_abs)
{
    if( encoder->encoder_type == SRCSL_ENCODER_ABSOLUTE)
        encoder->angle_abs = angle_abs;
}


//���±���������
void srcsl_encoder_updata( SrcslEncoder *encoder, uint32_t angle)
{
    switch( encoder->encoder_type)
    {
        case SRCSL_ENCODER_ABSOLUTE:
        {
            encoder->d_value = angle - encoder->angle_abs;

            //�������
            if( encoder->d_value > encoder->range / 2)
            {
                encoder->d_value -= encoder->range;
                encoder->rounds--;
            }
            else if( encoder->d_value < -encoder->range / 2)
            {
                encoder->d_value += encoder->range;
                encoder->rounds++;
            }

            encoder->angle_abs = angle;
            encoder->angle_sum += encoder->d_value;               
        }break;

        
        case SRCSL_ENCODER_INCREMENTAL:
        {
                encoder->d_value = angle;

                encoder->angle_sum += encoder->d_value;
                encoder->angle_abs = encoder->angle_sum % encoder->range;
                encoder->rounds = encoder->angle_sum / encoder->range;
        }break;
     
    }
}


//��ȡ���������ԽǶ�
uint32_t srcsl_encoder_get_angle_abs( SrcslEncoder *encoder)
{
    return encoder->angle_abs;
}

//��ȡ�������ۻ��Ƕ�
int32_t srcsl_encoder_get_angle_sum( SrcslEncoder *encoder)
{
    return encoder->angle_sum;
}

//��ȡ�������仯��
int32_t srcsl_encoder_get_d_value( SrcslEncoder *encoder)
{
    return encoder->d_value;
}

//��¡�����������Ʋ�����
void srcsl_encoder_clone( SrcslEncoder *des, SrcslEncoder *src)
{
    srcsl_encoder_init( des, src->encoder_type, src->range);
}

