#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_log.h"


void output( int8_t *msg)
{
    printf("---output : %s\n", msg);
}

int test_log(void)
{
    SrcslLog log;
    char s[SRCSL_STRING_LENGTH_MAX];
    int index = 0;

    srcsl_log_init( &log, output);
    for(int a=0;a<50;++a)
    {
		srcsl_log_write(&log, "index:%d", index++);
    }
    return 0;
}