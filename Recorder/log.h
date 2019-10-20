#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdint.h>
#include <stdarg.h>

#define MSG_SUM_MAX 32
#define STRING_LENGTH_MAX 31

typedef struct 
{
    int8_t msg[MSG_SUM_MAX][STRING_LENGTH_MAX + 1];
    uint8_t index;
} Log;


void Log_Init( Log *log);
void Log_Add( Log *log, int8_t *fmt, ...);
int8_t Log_Find( Log *log, const int8_t *msg);
void Log_Out( Log *log, void ( *output_func)(int8_t *msg));


#endif
