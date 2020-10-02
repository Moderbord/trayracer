#pragma once
#include "vec3.h"

//------------------------------------------------------------------------------
/**
*/
class Ray
{
public:
    Ray(const vec3& startpoint, const vec3& dir) :
        b(startpoint),
        m(dir)
    {

    }

    ~Ray()
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