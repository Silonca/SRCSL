#ifndef SRCSL_LOG_H_INCLUDED
#define SRCSL_LOG_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"
#include <stdarg.h>


/// 日志模块
typedef struct 
{
    int8_t msg[SRCSL_STRING_LENGTH_MAX];			//!< 用于暂存信息
	void (*output_func)(int8_t *msg);				//!< 输出函数的指针
} SrcslLog;

/**
* @brief 日志模块实例初始化
* @param *log			日志模块实例的指针
* @param *output_func	自定义的输出函数的指针，通过这个函数可实现统一的输出格式及输出重定向
*/
void srcsl_log_init( SrcslLog *log, void ( *output_func)(int8_t *msg));

/**
* @brief 用自定义的输出函数将内容输出
* @param *log	日志模块实例的指针
* @param *fmt	要输出内容的格式（同printf）
* @param ...	要格式化的量（同printf）
*/
void srcsl_log_write( SrcslLog *log, int8_t *fmt, ...);




#ifdef __cplusplus
}
#endif

#endif
