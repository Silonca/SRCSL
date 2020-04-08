#include <stdio.h>
#include <stdlib.h>

#include "log.h"


void output( int8_t *msg)
{
    printf("---output : %s\n", msg);
}

int test_log(void)
{
    Log log;
    int log_cnt = 0;
    char ch;
    char s[STRING_LENGTH_MAX];
    int num;
    int index = -1;

    log_init( &log);
    while(1)
    {
        system("clr");
        printf("a:add\nf:find\no:out\nq:quit");
        switch(ch = getchar())
        {
            case 'a':
                printf("add num:\n");
                scanf("%d", &num);
                getchar();      //to eat the '\n'
                for( int temp = 0; temp < num; ++temp)
                {
                    log_add( &log, "log cnt:%d",log_cnt);
                    printf("add msg: log cnt:%d\n",log_cnt);
                    printf("current index : %d, max index: %d",log.index, MSG_SUM_MAX);
                    log_cnt++;
                }
                break;
            case 'f':
                printf("find what?\n");
                scanf("%s",s );
                getchar();
                index = log_find( &log, s);
                if(index == -1)
                    printf("can not find\n");
                else printf("find in index %d : %s\n", index, log.msg[index]);
                break;
            case 'o':
                printf("now log out:\n");
                log_out( &log, output);
                printf("out end.\n");
                break;

        }
        if( ch == 'q')
        break;
    }

    system("pause");

    return 0;
}