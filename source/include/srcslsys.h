#ifndef SRCSL_SRCSLSYS_H_INCLUDED
#define SRCSL_SRCSLSYS_H_INCLUDED

#include <stdint.h>
//stdint.hΪC99���룬���ȱ�ٸ��ļ��������б�д����ע�Ͳ������ݣ�������һ��ȥ��
/*
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
*/



enum { SRCSL_SET, SRCSL_RESET };
enum { SRCSL_FALSE, SRCSL_TRUE };


///��ת���ϵ�������motor.c srcsl_motor_stall_test(...)��
#define STALL_SRCSL_PID_OUT_RATIO  (0.7f)
#define STALL_SRCSL_PID_IOUT_RATIO (0.7f)

///��־��������С
#define SRCSL_STRING_LENGTH_MAX 101

///vector��ʼ����
#define SRCSL_VECTOR_INITIAL_CAPACITY 8


#endif 

