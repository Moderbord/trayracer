#pragma once
#include "vec3.h"
#include "ray.h"
#include "random.h"

struct Transform
{
    vec3 position;
    unsigned int size;
};

struct Object
{
    unsigned int id;
};

//------------------------------------------------------------------------------
/**
*/
struct HitResult
{
    // hit point
    vec3 p;
    // normal
    vec3 normal;
    // hit object, or nullptr
    Object object;
    // intersection distance
    float t = FLT_MAX;
};

inline bool IntersectSphere(HitResult& hit, const Ray& ray, const float& maxDist, const Transform& transform)
{
    const vec3 oc = ray.origin - transform.position;
    const vec3& dir = ray.direction;
    const float b = dot(oc, dir);

    // early out if sphere is "behind" ray
    if (b > 0)
        return false;

    const float a = dot(dir, dir);
    const float c = dot(oc, oc) - transform.size * transform.size;
    const float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        const float minDist = 0.001f;
        const float div = 1.0f / a;
        const float sqrtDisc = sqrt(discriminant);
        const float temp = (-b - sqrtDisc) * div;
        const float temp2 = (-b + sqrtDisc) * div;

        if (temp < maxDist && temp > minDist)
        {
            hit.p = ray.PointAt(temp);
            hit.normal = (hit.p - transform.position) * (1.0f / transform.size);
            hit.t = temp;
            return true;
        }
        if (temp2 < maxDist && temp2 > minDist)
        {
            hit.p = ray.PointAt(temp2);
            hit.normal = (hit.p - transform.position) * (1.0f / transform.size);
            hit.t = temp2;
            return true;
        }
    }

    return false;
}

// returns a random point on the surface of a unit sphere
inline vec3 random_point_on_unit_sphere()
{
    return normalize({RandomFloatNTP(), RandomFloatNTP(), RandomFloatNTP()});
}