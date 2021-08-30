#ifndef SRCSL_FILTER_H_INCLUDED
#define SRCSL_FILTER_H_INCLUDED

#include "srcslsys.h"

typedef struct SrcslFilterKalman {
	float process_noise;			//!< ��������Э���� 
	float ob_noise;					//!< �۲�����Э����
	float last;						//!< �ϴι���Э���� 
	float now;						//!< ��ǰ����Э���� ��ʼ��ֵΪ0
	float kalman_gain;				//!< ���������� ��ʼ��ֵΪ0
	float out;						//!< �������˲������ ��ʼ��ֵΪ0
} SrcslFilterKalman;

/**
* @brief �������˲���
* @param *kal	�������˲���ʵ��ָ��
* @param input	����
* @return �˲������
*/
float srcsl_filter_kalman(SrcslFilterKalman * kal, float input);


//---------------------------------------------------------------------


typedef struct SrcslFilterLowPass {
	float last;						//!< �ϴ����
	float a;						//!< �˲�ϵ��
	float out;						//!< ���
} SrcslFilterLowPass;
/**
* @brief һ�׵�ͨ�����ԣ��˲���
* @param *lowpass	һ�׵�ͨ�˲���ʵ��ָ��
* @param input	����
* @return �˲������
*/
float srcsl_filter_lowpass(SrcslFilterLowPass * lowpass, float input);

//---------------------------------------------------------------------


typedef struct SrcslFilterMean {
	float *values;					//!< ǰn�����루��Ҫ����һ����ֵΪ0�����飩
	uint8_t size;					//!< ������г���
	uint8_t index;					//!< ��ǰ���������
	float sum;						//!< �ۼ�ֵ
	float out;						//!< ���
} SrcslFilterMean;
/**
* @brief ��ֵ�˲���
* @param *mean	��ֵ�˲���ʵ��ָ��
* @param input	����
* @return �˲������
*/
float srcsl_filter_mean(SrcslFilterMean * mean, float input);






#endif