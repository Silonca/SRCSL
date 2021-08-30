#ifndef SRCSL_CHASSIS_H_INCLUDED
#define SRCSL_CHASSIS_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"
#include "srcsl_motor.h"

///���ֵ�������
enum SRCSL_CHASSIS_4W 
{ 
	SRCSL_WHEEL_4W_LF,		//!< ��ǰ��(left front)
	SRCSL_WHEEL_4W_LR, 		//!< �����(left rear)
	SRCSL_WHEEL_4W_RF, 		//!< ��ǰ��(right front)
	SRCSL_WHEEL_4W_RR		//!< �Һ���(right rear)
};

///���ֵ������ӣ���ʱ���ţ�
enum SRCSL_CHASSIS_3W 
{ 
	SRCSL_WHEEL_3W_ONE,		//!< һ����
	SRCSL_WHEEL_3W_TWO,		//!< ������
	SRCSL_WHEEL_3W_THREE	//!< ������
};

///���ֵ�������
enum SRCSL_CHASSIS_2W 
{ 
	SRCSL_WHEEL_2W_LEFT,	//!< ����
	SRCSL_WHEEL_2W_RIGHT	//!< ����
};

///���ֵ�����������
enum SRCSL_CHASSIS_3W_HEADING_MODE
{ 
	SRCSL_WHEEL_3W_HEADING_MOTOR,				//!< һ�����ӷ���Ϊ������
	SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR		//!< ����������֮�䷽��Ϊ������
};

///������ת����
enum SRCSL_CHASSIS_ROTATION 
{
	SRCSL_CHASSIS_CW,			//!< ˳ʱ�뷽��
	SRCSL_CHASSIS_CCW			//!< ��ʱ�뷽��
};

///���̷���
enum SRCSL_CHASSIS_DIRECTION 
{
	SRCSL_CHASSIS_FORWARD,		//!< ǰ��
	SRCSL_CHASSIS_REVERSE		//!< ����
};

///��������ģ��
typedef struct 
{
    SrcslMotor *motor;					//!< �������
    uint8_t srcsl_motor_num;			//!< �������

    SrcslServo *servo;					//!< �������
    uint8_t servo_num;					//!< �������

	//��δʵ�����ƣ���������
    float v_x_max[2];					//!< ǰ��������ٶȣ���xΪǰ+��-
	float v_y_max[2];					//!< ���ҷ�������ٶȣ���yΪ��-��+
    float v_yaw_max[2];					//!< ˳+��-

} SrcslChassis;

/**
* @brief ����ģ���ʼ��
* @param *chassis	����ģ��ʵ����ָ��
* @param *motor		�ѳ�ʼ���ĵ������
* @param motor_num	���������
* @param *servo		�ѳ�ʼ���Ķ������
* @param servo_num	���������
*/
void srcsl_chassis_init( SrcslChassis *chassis, SrcslMotor *motor, uint8_t srcsl_motor_num, SrcslServo *servo, uint8_t servo_num);

/**
* @brief ���õ�������ٶ�
* @param *chassis	����ģ��ʵ����ָ��
* @param v_x_max	ǰ�������ٶ�
* @param v_y_max	���������ٶ�
* @param v_yaw_max	��ת�ٶ�
*/
void srcsl_chassis_set_v_max( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);

/**
* @brief ���õ�����������ٶ�
* @attition ���ڵ���srcsl_chassis_set_v_max()���ٵ��øú�������Ϊ���Ḳ�����������Ч��
* @param *chassis	����ģ��ʵ����ָ��
* @param v_x_max	�����ٶ�
* @param v_y_max	�����ٶ�
* @param v_yaw_max	��ʱ����ת�ٶ�
*/
void srcsl_chassis_set_v_max_reverse( SrcslChassis *chassis, float v_x_max, float v_y_max, float v_yaw_max);    


/**
* @brief ���ֵ�������
* @param *chassis	����ģ��ʵ����ָ��
* @param vx			ǰ�������ٶ�
* @param vyaw		��ת�ٶ�
*/
void srcsl_chassis_ctrl_calc_2w( SrcslChassis *chassis, float vx, float vyaw);


/**
* @brief ��ȫ���ֵ���
* @param *chassis		����ģ��ʵ����ָ��
* @param heading_mode	����ǰ������ģʽ
* - SRCSL_WHEEL_3W_HEADING_MOTOR			һ�����ӷ���Ϊ������
* - SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR	����������֮��Ϊ������
* @param vx				ǰ�������ٶ�
* @param vy				�����ƶ��ٶ�
* @param vyaw			��ת�ٶ�
*/
void srcsl_chassis_ctrl_calc_3w_omni( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw);

/**
* @brief ��ȫ���ֵ��̣���ͷģʽ��
* @param *chassis		����ģ��ʵ����ָ��
* @param heading_mode	����ǰ������ģʽ
* - SRCSL_WHEEL_3W_HEADING_MOTOR			һ�����ӷ���Ϊ��ʼ������
* - SRCSL_WHEEL_3W_HEADING_BETWEEN_MOTOR	����������֮��Ϊ��ʼ������
* @param vx				ǰ�������ٶ�
* @param vy				�����ƶ��ٶ�
* @param vyaw			��ת�ٶ�
* @param angle			�����������ĽǶ�
*/
void srcsl_chassis_ctrl_calc_3w_omni_headless( SrcslChassis *chassis, uint8_t heading_mode, float vx, float vy, float vyaw, float angle);

/**
* @brief ���ֵ���
* @param *chassis		����ģ��ʵ����ָ��
* @param vx				ǰ�������ٶ�
* @param vyaw			��ת�ٶ�
*/
void srcsl_chassis_ctrl_calc_4w_regular( SrcslChassis *chassis, float vx, float vyaw);

/**
* @brief ���������ķ�ֵ���
* @param *chassis	����ģ��ʵ����ָ��
* @param vx			ǰ���ƶ��ٶ�
* @param vy			�����ƶ��ٶ�
* @param vyaw		��ת�ٶ�
*/
void srcsl_chassis_ctrl_calc_4w_mecanum( SrcslChassis *chassis, float vx, float vy, float vyaw);


/**
* @brief ���������ķ�ֵ��̣�������ת��
* @param *chassis		����ģ��ʵ����ָ��
* @param vx				ǰ���ƶ��ٶ�
* @param vy				�����ƶ��ٶ�
* @param vyaw			��ת�ٶ�
* @param width_rate		��ת�������������߼��λ�ã����������Ϊ0��
* @param length_rate	��ת������ǰ�����߼��λ�ã�������ǰ��Ϊ0��
*/
void srcsl_chassis_ctrl_calc_4w_mecanum_off_center( SrcslChassis *chassis, float vx, float vy, float vyaw, float width_rate, float length_rate);

/**
* @brief ���������ķ�ֵ��̣���ͷģʽ��
* @param *chassis	����ģ��ʵ����ָ��
* @param vx			ǰ���ƶ��ٶ�
* @param vy			�����ƶ��ٶ�
* @param vyaw		��ת�ٶ�
* @param angle		������������ĽǶ�
*/
void srcsl_chassis_ctrl_calc_4w_mecanum_headless( SrcslChassis *chassis, float vx, float vy, float vyaw, float angle);



/**
* @brief ��������̿���
* @param *chassis		����ģ��ʵ����ָ��
* @param v				�˶��ٶ�
* @param caster_angle	ת��Ƕ�
*/
void srcsl_chassis_ctrl_calc_car( SrcslChassis *chassis, float v, int32_t caster_angle);


#ifdef __cplusplus
}
#endif

#endif
