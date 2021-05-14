/**
* @file srcsl_log.c
* @brief 简易的日志功能，用于重定向和格式化输出
* @author Silonca
*/

#include "include/srcsl_log.h"

#include <stdio.h>
#include <string.h>



void srcsl_log_init( SrcslLog *log, void(*output_func)(int8_t *msg))
{
	log->output_func = output_func;
}



void srcsl_log_write( SrcslLog *log, int8_t *fmt, ...)
{
    va_list list;
    va_start( list, fmt);

    vsnprintf( log->msg, SRCSL_STRING_LENGTH_MAX, fmt, list);
    
    va_end(list);

	log->output_func(log->msg);
}


