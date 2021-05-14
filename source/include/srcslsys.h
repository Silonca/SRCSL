#ifndef SRCSL_SRCSLSYS_H_INCLUDED
#define SRCSL_SRCSLSYS_H_INCLUDED

#include <stdint.h>
//stdint.h为C99引入，如果没有，请自行编写以下注释部分内容，并将上一行去掉
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


///堵转检测系数（详见motor.c srcsl_motor_stall_test(...)）
#define STALL_SRCSL_PID_OUT_RATIO  (0.7f)
#define STALL_SRCSL_PID_IOUT_RATIO (0.7f)

///日志缓存区大小
#define SRCSL_STRING_LENGTH_MAX 101

///vector初始容量
#define SRCSL_VECTOR_INITIAL_CAPACITY 8


#endif 

