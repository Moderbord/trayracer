#pragma once
#include "vec3.h"

//------------------------------------------------------------------------------
/**
*/
struct Ray
{
    Ray(){};
    Ray(const vec3& startpoint, const vec3& dir) :
        b(startpoint),
        m(dir)
    {

    }
    
    vec3 PointAt(const float& t) const
    {
        return {b + m * t};
    }

    // beginning of ray
    vec3 b;
    // magnitude and direction of ray
    vec3 m;
};