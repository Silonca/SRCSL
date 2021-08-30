#ifndef SRCSL_FILTER_H_INCLUDED
#define SRCSL_FILTER_H_INCLUDED

#include "srcslsys.h"

typedef struct SrcslFilterKalman {
	float process_noise;			//!< 过程噪声协方差 
	float ob_noise;					//!< 观测噪声协方差
	float last;						//!< 上次估算协方差 
	float now;						//!< 当前估算协方差 初始化值为0
	float kalman_gain;				//!< 卡尔曼增益 初始化值为0
	float out;						//!< 卡尔曼滤波器输出 初始化值为0
} SrcslFilterKalman;

/**
* @brief 卡尔曼滤波器
* @param *kal	卡尔曼滤波器实例指针
* @param input	输入
* @return 滤波器输出
*/
float srcsl_filter_kalman(SrcslFilterKalman * kal, float input);


//---------------------------------------------------------------------


typedef struct SrcslFilterLowPass {
	float last;						//!< 上次输出
	float a;						//!< 滤波系数
	float out;						//!< 输出
} SrcslFilterLowPass;
/**
* @brief 一阶低通（惯性）滤波器
* @param *lowpass	一阶低通滤波器实例指针
* @param input	输入
* @return 滤波器输出
*/
float srcsl_filter_lowpass(SrcslFilterLowPass * lowpass, float input);

//---------------------------------------------------------------------


typedef struct SrcslFilterMean {
	float *values;					//!< 前n次输入（需要传入一个初值为0的数组）
	uint8_t size;					//!< 输入队列长度
	uint8_t index;					//!< 当前处理的索引
	float sum;						//!< 累计值
	float out;						//!< 输出
} SrcslFilterMean;
/**
* @brief 均值滤波器
* @param *mean	均值滤波器实例指针
* @param input	输入
* @return 滤波器输出
*/
float srcsl_filter_mean(SrcslFilterMean * mean, float input);






#endif