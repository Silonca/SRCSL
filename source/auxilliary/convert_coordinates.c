#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include "convert_coordinates.h"





Cartesian_Coordinates convert_P2C( Polar_Coordinates polar)
{
    Cartesian_Coordinates temp;

    temp.x = polar.distance * cos( polar.angle);
    temp.y = polar.distance * sin( polar.angle);

    return temp;
}


Polar_Coordinates convert_C2P( Cartesian_Coordinates cartesian)
{
    Polar_Coordinates temp;

    temp.angle = atan2( cartesian.y, cartesian.x);
    temp.distance = sqrt( cartesian.x * cartesian.x + cartesian.y * cartesian.y);

    return temp;
}


Polar_Coordinates vector_P2P( Polar_Coordinates polar_begin, Polar_Coordinates polar_end)
{
    Polar_Coordinates temp;

    temp.angle = polar_end.angle - polar_begin.angle;
    while( temp.angle > M_PI_2) temp.angle -= M_PI;
    while( temp.angle < -M_PI_2) temp.angle += M_PI;
    temp.distance = polar_end.distance - polar_begin.distance;

    return temp;
}



Cartesian_Coordinates vector_C2C( Cartesian_Coordinates cartesian_begin, Cartesian_Coordinates cartesian_end)
{
    Cartesian_Coordinates temp;

    temp.x = cartesian_end.x - cartesian_begin.x;
    temp.y = cartesian_end.y - cartesian_begin.y;

    return temp;
}