#ifndef SRCSL_FILTER_H_INCLUDED
#define SRCSL_FILTER_H_INCLUDED

typedef struct SrcslFilterKalman {
	float process_noise;			//过程噪声协方差 
	float ob_noise;					//观测噪声协方差
	float last;						//上次估算协方差 
	float now;						//当前估算协方差 初始化值为0
	float kalman_gain;				//卡尔曼增益 初始化值为0
	float out;						//卡尔曼滤波器输出 初始化值为0
} SrcslFilterKalman;

/**
* @brief 卡尔曼滤波器
* @param *kal	卡尔曼滤波器实例指针
* @param input	输入
* @return 滤波器输出
*/
float srcsl_filter_kalman(SrcslFilterKalman * kal, float input);




#endif