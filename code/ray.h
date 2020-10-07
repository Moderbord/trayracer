#pragma once
#include "vec3.h"

//------------------------------------------------------------------------------
/**
*/
struct Ray
{
    Ray(){};
    Ray(const vec3& startpoint, const vec3& dir) :
        origin(startpoint),
        direction(dir)
    {

    }

    vec3 PointAt(const float& step) const
    {
        return {origin + direction * step};
    }

    // beginning of ray
    vec3 origin;
    // magnitude and direction of ray
    vec3 direction;
    
};