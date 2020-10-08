#pragma once
// #include "ray.h"
// #include "color.h"
// #include <float.h>
// #include <string>


struct Transform
{
    vec3 position;
    unsigned int size;
};

//------------------------------------------------------------------------------
/**
*/
// class Object
// {

// public:
//     Object() 
//     {
//     }

//     virtual bool Intersect(HitResult& hit, const Ray& ray, const float& maxDist);
//     vec3 GetColor() const;
//     Ray ScatterRay(const Ray& ray, const vec3& point, const vec3& normal);
// };

// vec3 Object::GetColor() const
// {
    
// }

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
    //Object* object = nullptr;
    // intersection distance
    float t = FLT_MAX;
};

// bool IntersectSphere(HitResult& hit, const Ray& ray, const float& maxDist, const Transform& transform)
//     {
//         const vec3 oc = ray.origin - transform.position;
//         const vec3& dir = ray.direction;
//         const float b = dot(oc, dir);
    
//         // early out if sphere is "behind" ray
//         if (b > 0)
//             return false;

//         const float a = dot(dir, dir);
//         const float c = dot(oc, oc) - transform.size * transform.size;
//         const float discriminant = b * b - a * c;

//         if (discriminant > 0)
//         {
//             const float minDist = 0.001f;
//             const float div = 1.0f / a;
//             const float sqrtDisc = sqrt(discriminant);
//             const float temp = (-b - sqrtDisc) * div;
//             const float temp2 = (-b + sqrtDisc) * div;

//             if (temp < maxDist && temp > minDist)
//             {
//                 hit.p = ray.PointAt(temp);
//                 hit.normal = (hit.p - transform.position) * (1.0f / transform.size);
//                 hit.t = temp;
//                 return true;
//             }
//             if (temp2 < maxDist && temp2 > minDist)
//             {
//                 hit.p = ray.PointAt(temp2);
//                 hit.normal = (hit.p - transform.position) * (1.0f / transform.size);
//                 hit.t = temp2;
//                 return true;
//             }
//         }

//         return false;
//     }
