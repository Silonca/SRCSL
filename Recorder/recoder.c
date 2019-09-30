#include "recoder.h"

void Recoder(void *data,uint32_t length, void newdata)
{
    for(uint32_t i = 0; i < length - 1; ++i)
    {
        data[i + 1] = data[i];
    }

    data[0] = newdata;
}