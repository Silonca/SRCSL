#include "log.h"

#include <stdio.h>
#include <string.h>

void Log_Init( Log *log)
{
    for( uint32_t a = 0; a < MSG_SUM_MAX; ++a)
    {
        for( uint32_t b = 0; b < STRING_LENGTH_MAX + 1; ++b)
        {
            log->msg[a][b] = 0;
        }
    }
    log->index = 0;
}



void Log_Add( Log *log, int8_t *fmt, ...)
{
    va_list list;
    va_start( list, fmt);

    vsnprintf( log->msg[ log->index++], STRING_LENGTH_MAX, fmt, list);
    
    if( log->index >= MSG_SUM_MAX)
    {
        log->index = 0;
    }

    va_end(list);
}


int8_t Log_Find( Log *log, const int8_t *msg)
{
    for( uint8_t a = 0; a < MSG_SUM_MAX; ++a)
    {
        if( strcmp( log->msg[a], msg) == 0)
        {
            return a;
        }
    }

    return -1;
}


void Log_Out( Log *log, void ( *output_func)(int8_t *msg))
{
    for( int8_t a = log->index + 1; a < MSG_SUM_MAX; ++a)
    {
        if( strlen(log->msg[a]) != 0)
        {
            output_func( log->msg[a]);
        }
    }
    for( int8_t a = 0; a < log->index + 1; ++a)
    {
        if( strlen(log->msg[a]) != 0)
        {
            output_func( log->msg[a]);
        }
    }
}