#include "include/recoder.h"

void recoder(uint8_t *data,uint32_t length, uint8_t newdata)
{
    uint32_t i;
    for( i = 0; i < length - 1; ++i)
    {
        data[i + 1] = data[i];
    }

    data[0] = newdata;
}