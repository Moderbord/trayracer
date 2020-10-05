#pragma once
#include "object.h"
#include <stdlib.h>
#include <time.h>
#include "mat4.h"
#include "pbr.h"
#include "random.h"
#include "ray.h"
#include "material.h"

// returns a random point on the surface of a unit sphere
inline vec3 random_point_on_unit_sphere()
{
    float x = RandomFloatNTP();
    float y = RandomFloatNTP();
    float z = RandomFloatNTP();
    vec3 v( x, y, z );
    return normalize(v);
}

// a spherical object
class Sphere : public Object
{
public:
    float radius;
    vec3 center;
    Material material;

    Sphere(float radius, vec3 center, Material& material) : 
        radius(radius),
        center(center),
        material(material)
    {

    }

    ~Sphere() override
    {

    }

    vec3 GetColor() const override
    {
        return material.color;
    }

    bool Intersect(HitResult& hit, const Ray& ray, const float& maxDist) override
    {
        const vec3 oc = ray.b - this->center;
        const vec3& dir = ray.m;
        const float b = dot(oc, dir);
    
        // early out if sphere is "behind" ray
        if (b > 0)
            return false;

        const float a = dot(dir, dir);
        const float c = dot(oc, oc) - this->radius * this->radius;
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
                hit.normal = (hit.p - this->center) * (1.0f / this->radius);
                hit.t = temp;
                return true;
            }
            if (temp2 < maxDist && temp2 > minDist)
            {
                hit.p = ray.PointAt(temp2);
                hit.normal = (hit.p - this->center) * (1.0f / this->radius);
                hit.t = temp2;
                return true;
            }
        }

        return false;
    }

    Ray ScatterRay(const Ray& ray, const vec3& point, const vec3& normal) override
    {
        return BSDF(material, ray, point, normal);
    }

};