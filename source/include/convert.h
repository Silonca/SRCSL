#ifndef SRCSL_CONVERT_H_INCLUDED
#define SRCSL_CONVERT_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>


typedef struct
{
    float angle;
    float distance;
} Polar;


typedef struct 
{
    float x;
    float y;
} Cartesian;

Cartesian convert_P2C( Polar polar);
Polar convert_C2P( Cartesian cartesian);

Polar vector_P2P( Polar polar_begin, Polar polar_end);
Cartesian vector_C2C( Cartesian cartesian_begin, Cartesian cartesian_end);

#ifdef __cplusplus
}
#endif

#endif
