#ifndef SRCSL_ENCODER_H_INCLUDED
#define SRCSL_ENCODER_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

///编码器类型
enum SRCSL_ENCODER_TYPE 
{
	SRCSL_ENCODER_ABSOLUTE,				//!< 绝对编码器
	SRCSL_ENCODER_INCREMENTAL			//!< 增量编码器
};

///编码器模块
typedef struct
{
    uint32_t encoder_type;

    int32_t angle_abs;				//!< 绝对角度（对于增量式编码器，相对于开始时的位置）
    int32_t angle_sum;				//!< 累计角度
    int32_t rounds;					//!< 圈数
    int32_t d_value;				//!< 两次获取值的差值
    int32_t range;					//!< 角度范围

} SrcslEncoder;

/**
* @brief 编码器初始化
* @param *encoder		编码器实例的指针
* @param encoder_type	编码器类型
* - SRCSL_ENCODER_ABSOLUTE		绝对编码器
* - SRCSL_ENCODER_INCREMENTAL	增量编码器
* @param range			编码范围
*/
void srcsl_encoder_init( SrcslEncoder *encoder, uint32_t encoder_type, uint32_t range);

/**
* @brief 设置编码器绝对角度
* @param *encoder	编码器实例的指针
* @param angle_abs	绝对角度
*/
void srcsl_encoder_set_angle_abs( SrcslEncoder *encoder, int32_t angle_abs);

/**
* @brief 更新编码器数据
* @param *encoder	编码器实例的指针
* @param angle		获取到的实际编码器角度
*/
void srcsl_encoder_updata( SrcslEncoder *encoder, uint32_t angle);

/**
* @brief 获取编码器绝对角度
* @param *encoder 编码器实例的指针
*/
uint32_t srcsl_encoder_get_angle_abs( SrcslEncoder *encoder);

/**
* @brief 获取编码器累积角度
* @param *encoder 编码器实例的指针
*/
int32_t srcsl_encoder_get_angle_sum( SrcslEncoder *encoder);

/**
* @brief 获取编码器变化量
* @param *encoder 编码器实例的指针
*/
int32_t srcsl_encoder_get_d_value( SrcslEncoder *encoder);

/**
* @brief 克隆编码器（复制参数）
* @param *des 目标编码器的指针
* @param *scr 源编码器的指针
*/
void srcsl_encoder_clone( SrcslEncoder *des, SrcslEncoder *src);

#ifdef __cplusplus
}
#endif

#endif
