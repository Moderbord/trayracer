#pragma once
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <string>

//------------------------------------------------------------------------------
/**
*/
enum TYPE
{
    Lambertian,
    Dielectric,
    Conductor
};
struct Material

{
    /*
        type can be "Lambertian", "Dielectric" or "Conductor".
        Obviously, "lambertian" materials are dielectric, but we separate them here
        just because figuring out a good IOR for ex. plastics is too much work
    */
    TYPE type = Lambertian;
    vec3 color = {0.5f,0.5f,0.5f};
    float roughness = 0.75;

    // this is only needed for dielectric materials.
    float refractionIndex = 1.44;
};

//------------------------------------------------------------------------------
/**
    Scatter ray against material
*/
Ray BSDF(const Material& material, const Ray& ray, const vec3& point, const vec3& normal);