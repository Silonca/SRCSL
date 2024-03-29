/**
* @file srcsl_filter.c
* @brief 各种滤波器
* @author Silonca
*/
#include "include/srcsl_filter.h"

//卡尔曼滤波器
float srcsl_filter_kalman(SrcslFilterKalman * kal, float input)
{
	//预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
	kal->now = kal->last + kal->process_noise;
	//卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
	kal->kalman_gain = kal->now / (kal->now + kal->ob_noise);

	kal->last = (1 - kal->kalman_gain) * kal->now;
	kal->out = kal->out + kal->kalman_gain * (input - kal->out);
	return kal->out;

}

//一阶低通滤波器
float srcsl_filter_lowpass(SrcslFilterLowPass * lowpass, float input)
{
	lowpass->out = lowpass->a * input + (1.0f - lowpass->a) * lowpass->last;
	lowpass->last = lowpass->out;
	return lowpass->out;
}


//均值滤波器
float srcsl_filter_mean(SrcslFilterMean * mean, float input)
{
	mean->sum = mean->sum - mean->values[mean->index] + input;
	mean->index = (mean->index + 1) % mean->size;
	mean->out = mean->sum / (float)mean->size;
	return mean->out;
}

