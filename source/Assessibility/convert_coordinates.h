#ifndef CONVERT_COORDINATES_H_INCLUDED
#define CONVERT_COORDINATES_H_INCLUDED

#include <stdint.h>


typedef struct
{
    float angle;
    float distance;
} Polar_Coordinates;


typedef struct 
{
    float x;
    float y;
} Cartesian_Coordinates;

Cartesian_Coordinates Convert_P2C( Polar_Coordinates polar);
Polar_Coordinates Convert_C2P( Cartesian_Coordinates cartesian);

Polar_Coordinates Vector_P2P( Polar_Coordinates polar_begin, Polar_Coordinates polar_end);
Cartesian_Coordinates Vector_C2C( Cartesian_Coordinates cartesian_begin, Cartesian_Coordinates cartesian_end);

#endif
