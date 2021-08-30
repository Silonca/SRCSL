#ifndef SRCSL_MOTOR_H_INCLUDED
#define SRCSL_MOTOR_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

#include "srcsl_pid.h"
#include "srcsl_encoder.h"



///�����ת״̬
enum SRCSL_STALL_STATE 
{
	SRCSL_STALL,				//!< �����ת
	SRCSL_NOT_STALL				//!< ���δ��ת
};
///����г�״̬
enum SRCSL_RANGE_STATE 
{
	SRCSL_RANGE_NO,				//!< �г�δȷ��
	SRCSL_RANGE_ONEEND_OK,		//!< �г�һ����ȷ��
	SRCSL_RANGE_OK				//!< �г���ȷ��
};


///���ģ��
typedef struct 
{
    SrcslPID speed_pid;				//!< ����ٶȻ�pid
    SrcslPID position_pid;			//!< ���λ�û�pid

    SrcslEncoder encoder;

	int32_t out;					//!< pid������

    int32_t range_begin;			//!< �г���㣨ӦΪ��Сֵ��
    int32_t range_end;				//!< �г��յ㣨ӦΪ�ϴ�ֵ��
    int32_t range_state;			//!< �г�״̬

    int32_t relative_zero;			//!< ���������

    void ( *motor_rotation_func)(float srcsl_pid_out);		//!< �����ת�����������г̲ⶨ������

} SrcslMotor;


/**
* @brief �����󲽽�����
* @attention Ӧ��������������src
* @par ����
* @code
*	src = srcsl_motor_ctrl_step( des, src, step);
* @encode
* @param des	Ŀ��ֵ
* @param src	��ǰֵ
* @param step	���������ֵ
* @return �˴�Ӧ�������ֵ
*/
int32_t srcsl_motor_ctrl_step(int32_t des, int32_t src, int32_t step);

/**
* @brief �����ʼ�����󶨱�������pid��
* @param *motor			���ģ��ʵ����ָ��
* @param *encoder		������ʵ����ָ��
* @param *speed_pid		�ٶȻ�pidʵ����ָ��
* @param *pos_pid		λ�û�pidʵ����ָ��
*/
void srcsl_motor_init( SrcslMotor *motor, SrcslEncoder *encoder, SrcslPID *speed_pid, SrcslPID *pos_pid);  

/**
* @brief ������������ݸ���
* @param *motor			���ģ��ʵ����ָ��
* @param angle			�µı���������
*/
void srcsl_motor_encoder_updata(SrcslMotor *motor, uint32_t angle);


/**
* @brief ���������㣨���ԽǶȿ���ʱ���ڰ�װ�����������������ܲ���Ԥ��λ�ã�����������������������⣩
* @param *motor	���ģ��ʵ����ָ��
* @param zero	������
*/
void srcsl_motor_set_relative_zero( SrcslMotor *motor, int32_t zero);


/**
* @brief ����ٶȿ��Ƽ��㺯��
* @param *motor	���ģ��ʵ����ָ��
* @param speed	�����Ŀ���ٶ�
* @return �ٶȻ�pid���ֵ
*/
int32_t srcsl_motor_speed_ctrl_calc( SrcslMotor *motor, float speed);


/**
* @brief ���λ�ã����ԽǶȣ����Ƽ��㺯������ͽ���λ���������Ӱ�죩
* @param *motor		���ģ��ʵ����ָ��
* @param position	�����Ŀ��λ��
* @return ˫��pid���ֵ
*/
int32_t srcsl_motor_position_abs_ctrl_calc( SrcslMotor *motor, float position);			

/**
* @brief ���λ�ã��ۻ��Ƕȣ����Ƽ��㺯��
* @param *motor		���ģ��ʵ����ָ��
* @param position	�����Ŀ��λ��
* @return ˫��pid���ֵ
*/
int32_t srcsl_motor_position_sum_ctrl_calc(SrcslMotor *motor, float position);				


/**
* @brief �����ת���
* @param *motor ���ģ��ʵ����ָ��
*/
uint32_t srcsl_motor_stall_test(SrcslMotor *motor);


/**
* @brief ����г��趨
* @param *motor			���ģ��ʵ����ָ��
* @param range_begin	���ת����Χ
* @param range_end		���ת����Χ
*/
void srcsl_motor_range_set(SrcslMotor *motor, int32_t range_begin, int32_t range_end);		

/**
* @brief ����г̲���
* @param *motor	���ģ��ʵ����ָ��
* @param step	�����г�ʱ����Ĳ���ֵ�����٣�
*/
void srcsl_motor_range_get( SrcslMotor *motor, int32_t step);								


/**
* @brief �趨�����ת�����������г̲ⶨ������
* @param *motor					���ģ��ʵ����ָ��
* @param *motor_rotation_func	�����ת����
*/
void srcsl_motor_rotation_func_init(SrcslMotor *motor, void(*srcsl_motor_rotation_func)(float srcsl_pid_out));


//���ģ��
typedef struct 
{
    void ( *servo_set_func)(uint32_t );

    uint32_t origin_range_begin;
    uint32_t origin_range_end;

    int32_t range_begin;
    int32_t range_end;
} SrcslServo;


/**
* @brief ���ģ���ʼ��
* @param *servo				���ʵ����ָ��
* @param *servo_set_func	�������������ָ��
*/
void srcsl_motor_servo_init(SrcslServo *servo, void ( *servo_set_func)(uint32_t ));

/**
* @brief ���ת����Χӳ�䣨���罫�����pwm�ź���������ӳ��Ϊ��������ʹ�õĽǶ�ֵ��
* @param *servo					���ʵ����ָ��
* @param origin_range_begin		ԭʼ��Χ
* @param origin_range_end		ԭʼ��Χ
* @param range_begin			�·�Χ
* @param range_end				�·�Χ
*/
void srcsl_motor_servo_range_set( SrcslServo * servo, uint32_t origin_range_begin, uint32_t origin_range_end, int32_t range_begin, int32_t range_end);

/**
* @brief �������
* @param *servo ���ʵ����ָ��
* @param set	���Ӧת����λ��
*/
void srcsl_motor_servo_set( SrcslServo *servo, int32_t set);

#ifdef __cplusplus
}
#endif

#endif
