#ifndef RECODER_H_INCLUDED
#define RECODER_H_INCLUDED

#include <stdint.h>

void Recoder(void *data,uint32_t length, uint8_t newdata);



#define RECODER(TYPE,LENGTH) \
struct RECODER_TYPE\
{\
    (TYPE) data[LENGTH];\
}


#define RECODER_FUNC(TYPE,LENGTH,NEWDATA)\
Recoder_TYPE Recoder_TYPE_Func( RECODER(TYPE,LENGTH) *DATA, TYPE NEWDATA)\
{\
    for( uint32_t a = 0; a < LENGTH - 1; ++a)\
    {\
        DATA[a + 1] = DATA[a];\
    }\
    DATA[0] = NEWDATA;\
}

#endif
