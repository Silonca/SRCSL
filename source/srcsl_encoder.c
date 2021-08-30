/**
* @file srcsl_encoder.c
* @brief 编码器模块
* @author Silonca
*/

#include "include/srcsl_encoder.h"


//编码器初始化
void srcsl_encoder_init( SrcslEncoder *encoder, uint32_t encoder_type, uint32_t range)
{
    encoder->encoder_type = encoder_type;
    
    encoder->angle_abs = 0;         
    encoder->angle_sum = 0;
    encoder->d_value = 0;
    encoder->range = range;
    encoder->rounds = 0;
}


//设置编码器绝对角度
void srcsl_encoder_set_angle_abs( SrcslEncoder *encoder, int32_t angle_abs)
{
    if( encoder->encoder_type == SRCSL_ENCODER_ABSOLUTE)
        encoder->angle_abs = angle_abs;
}


//更新编码器数据
void srcsl_encoder_updata( SrcslEncoder *encoder, uint32_t angle)
{
    switch( encoder->encoder_type)
    {
        case SRCSL_ENCODER_ABSOLUTE:
        {
            encoder->d_value = angle - encoder->angle_abs;

            //过零点检测
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


//获取编码器绝对角度
uint32_t srcsl_encoder_get_angle_abs( SrcslEncoder *encoder)
{
    return encoder->angle_abs;
}

//获取编码器累积角度
int32_t srcsl_encoder_get_angle_sum( SrcslEncoder *encoder)
{
    return encoder->angle_sum;
}

//获取编码器变化量
int32_t srcsl_encoder_get_d_value( SrcslEncoder *encoder)
{
    return encoder->d_value;
}

//克隆编码器（复制参数）
void srcsl_encoder_clone( SrcslEncoder *des, SrcslEncoder *src)
{
    srcsl_encoder_init( des, src->encoder_type, src->range);
}

