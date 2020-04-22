#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include "include/convert.h"





Cartesian convert_P2C( Polar polar)
{
    Cartesian temp;

    temp.x = polar.distance * cosf( polar.angle);
    temp.y = polar.distance * sinf( polar.angle);

    return temp;
}


Polar convert_C2P( Cartesian cartesian)
{
    Polar temp;

    temp.angle = atan2f( cartesian.y, cartesian.x);
    temp.distance = sqrtf( cartesian.x * cartesian.x + cartesian.y * cartesian.y);

    return temp;
}


Polar vector_P2P( Polar polar_begin, Polar polar_end)
{
    Polar temp;

    temp.angle = polar_end.angle - polar_begin.angle;
    while( temp.angle > M_PI_2) temp.angle -= (float)M_PI;
    while( temp.angle < -M_PI_2) temp.angle += (float)M_PI;
    temp.distance = polar_end.distance - polar_begin.distance;

    return temp;
}



Cartesian vector_C2C( Cartesian cartesian_begin, Cartesian cartesian_end)
{
    Cartesian temp;

    temp.x = cartesian_end.x - cartesian_begin.x;
    temp.y = cartesian_end.y - cartesian_begin.y;

    return temp;
}