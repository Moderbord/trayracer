/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "material.h"
#include "pbr.h"
#include "mat4.h"
#include "object.h"
#include "random.h"

//------------------------------------------------------------------------------
/**
*/
void
BSDF(const Material& material, Ray& ray, const vec3& normal)
{
    float cosTheta = -dot(normalize(ray.direction), normalize(normal));
    float r = RandomFloat();

    if (material.type != Dielectric)
    {
        float F0 = 0.04f;
        if (material.type == Conductor)
        {
            F0 = 0.95f;
        }

        // probability that a ray will reflect on a microfacet
        float F = FresnelSchlick(cosTheta, F0, material.roughness);

        if (r < F)
        {
            mat4 basis = TBN(normal);
            // importance sample with brdf specular lobe
            vec3 H = ImportanceSampleGGX_VNDF(RandomFloat(), RandomFloat(), material.roughness, ray.direction, basis);
            ray.direction = normalize({reflect(ray.direction, H)});
        }
        else
        {
            ray.direction = normalize(normalize(normal) + random_point_on_unit_sphere());
        }
    }
    else
    {
        vec3 outwardNormal;
        vec3 refracted;
        float niOverNt;
        float reflect_prob = 1.0f;
        float cosine;
        const vec3& rayDir = ray.direction;

        if (cosTheta <= 0)
        {
            outwardNormal = -normal;
            niOverNt = material.refractionIndex;
            cosine = cosTheta * niOverNt / len(rayDir);
        }
        else
        {
            outwardNormal = normal;
            niOverNt = 1.0 / material.refractionIndex;
            cosine = cosTheta / len(rayDir);
        }

        if (Refract(normalize(rayDir), outwardNormal, niOverNt, refracted))
        {
            // fresnel reflectance at 0 deg incidence angle
            float F0 = powf(material.refractionIndex - 1, 2) / powf(material.refractionIndex + 1, 2);
            reflect_prob = FresnelSchlick(cosine, F0, material.roughness);
        }

        if (r < reflect_prob)
        {
            ray.direction = reflect(rayDir, normal);
        }
        else
        {
            ray.direction = refracted;
        }
    }
}