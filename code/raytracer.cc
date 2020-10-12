/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "raytracer.h"
#include <random>

//------------------------------------------------------------------------------
/**
*/
Raytracer::Raytracer(const unsigned& w, const unsigned& h, std::vector<vec3>& frameBuffer, const unsigned& rpp, const unsigned& bounces, const BufferManager& bm) :
    frameBuffer(frameBuffer),
    rpp(rpp),
    bounces(bounces),
    width(w),
    height(h),
    view(identity()),
    frustum(identity()),
    bm(bm)
{
    // empty
    static int leet = 1337;
    std::mt19937 generator (leet++);
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Pre calculate ray distribution
    for (int i = 0; i < this->rpp; ++i) 
    {
        distX.push_back(dis(generator));
        distY.push_back(dis(generator));
    }

    fracWidth = 1.0f / this->width;
    fracHeight = 1.0f / this->height;
}

//------------------------------------------------------------------------------
/**
*/
void
Raytracer::Raytrace()
{
    float fracWidth = 1.0f / this->width;
    float fracHeight = 1.0f / this->height;
    float sampleFraction = 1.0f / this->rpp;

    Ray ray;
    vec3 color;


    for (int x = 0; x < this->width; ++x)
    {
        for (int y = 0; y < this->height; ++y)
        {
            color = {0.0f, 0.0f, 0.0f};
            for (int i = 0; i < this->rpp; ++i)
            {
                float u = ((float(x + distX[i]) * fracWidth) * 2.0f) - 1.0f;
                float v = ((float(y + distY[i]) * fracHeight) * 2.0f) - 1.0f;

                ray = Ray(get_position(this->view), transform({u, v, -1.0f}, this->frustum));
                numras++;
                color += this->TracePath(ray, this->bounces);
            }

            // divide by number of samples per pixel, to get the average of the distribution
            color *= sampleFraction;

            this->frameBuffer[y * this->width + x] += color;
        }
    }
}

vec3
Raytracer::RaytracePixel(const float& x, const float& y)
{
    vec3 color;
    for (int i = 0; i < this->rpp; ++i)
    {
        float u = ((float(x + distX[i]) * fracWidth) * 2.0f) - 1.0f;
        float v = ((float(y + distY[i]) * fracHeight) * 2.0f) - 1.0f;

        vec3 direction = vec3(u, v, -1.0f);
        direction = transform(direction, this->frustum);
        
        Ray ray = Ray(get_position(this->view), direction);
        color += this->TracePath(ray, 0);
    }
    return color;
}

//------------------------------------------------------------------------------
/**
 * @parameter n - the current bounce level
*/
vec3
Raytracer::TracePath(Ray& ray, unsigned n)
{
    vec3 hitPoint;
    vec3 hitNormal;
    Object hitObject;
    float distance = FLT_MAX;

    vec3 color {1.0f, 1.0f, 1.0f};
    Material* material;

    while (n > 0) // count down
    {
        if (Raycast(ray, hitPoint, hitNormal, distance, hitObject))
        {
            material = bm._materials->data + hitObject.id;
            color *= material->color;

            ray = BSDF(*material, ray, hitPoint, hitNormal);
            numras++;
            
            n--;
            continue;
        }
        return color *= this->Skybox(ray.direction);
    }
    return color *= {0.0f, 0.0f, 0.0f};
}

//------------------------------------------------------------------------------
/**
*/
bool
Raytracer::Raycast(const Ray& ray, vec3& hitPoint, vec3& hitNormal, float& distance, Object& hitObject)
{
    bool isHit = false;
    HitResult closestHit;
    HitResult hit;

    Object* obj;
    Transform* trans;

    for (int i = 0; i < bm._objects->n; i++)
    {
        obj = (bm._objects->data + i);
        trans = (bm._transforms->data + i);

        if (IntersectSphere(hit, ray, closestHit.t, *trans))
        {
            closestHit = hit;
            closestHit.object = *obj;
            isHit = true;
        }
    }

    hitPoint = closestHit.p;
    hitNormal = closestHit.normal;
    hitObject = closestHit.object;
    distance = closestHit.t;
    
    return isHit;
}


//------------------------------------------------------------------------------
/**
*/
void
Raytracer::Clear()
{
    for (auto& color : this->frameBuffer)
    {
        color.x = 0.0f;
        color.y = 0.0f;
        color.z = 0.0f;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Raytracer::UpdateMatrices()
{
    mat4 inverseView = inverse(this->view); 
    mat4 basis = transpose(inverseView);
    this->frustum = basis;
}

//------------------------------------------------------------------------------
/**
*/
vec3
Raytracer::Skybox(const vec3& direction)
{
    float t = 0.5f*(direction.y + 1.0f);
    float u = 1.0f - t;
    return {0.5f * t + u, 0.7f * t + u, 1.0f * t + u};
}

Ray Raytracer::ScatterRay(const Ray& ray, const vec3& point, const vec3& normal, const Object& object) 
{
    return BSDF(bm.getMaterial(object), ray, point, normal);
}