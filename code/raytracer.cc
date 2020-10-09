/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "raytracer.h"
#include <random>

//------------------------------------------------------------------------------
/**
*/
Raytracer::Raytracer(const unsigned& w, const unsigned& h, std::vector<vec3>& frameBuffer, const unsigned& rpp, const unsigned& bounces, const BufferManager& dm) :
    frameBuffer(frameBuffer),
    rpp(rpp),
    bounces(bounces),
    width(w),
    height(h),
    view(identity()),
    frustum(identity()),
    dm(dm)
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
            color = {0, 0, 0};
            for (int i = 0; i < this->rpp; ++i)
            {
                float u = ((float(x + distX[i]) * fracWidth) * 2.0f) - 1.0f;
                float v = ((float(y + distY[i]) * fracHeight) * 2.0f) - 1.0f;

                ray = Ray(get_position(this->view), transform({u, v, -1.0f}, this->frustum));
                numras++;
                color += this->TracePath(ray, 0);
            }

            // divide by number of samples per pixel, to get the average of the distribution
            color.x *= sampleFraction;
            color.y *= sampleFraction;
            color.z *= sampleFraction;

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
Raytracer::TracePath(const Ray& ray, const unsigned& n)
{
    vec3 hitPoint;
    vec3 hitNormal;
    Object hitObject;
    float distance = FLT_MAX;

    if (Raycast(ray, hitPoint, hitNormal, distance, hitObject))
    {
        Ray scatteredRay = Ray(ScatterRay(ray, hitPoint, hitNormal, hitObject));
        numras++;
        if (n < this->bounces)
        {
            return dm.getColor(hitObject) * this->TracePath(scatteredRay, n + 1);
        }

        if (n == this->bounces)
        {
            return {0,0,0};
        }
    }

    return this->Skybox(ray.direction);
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
    
    for (int i = 0; i < dm._objects->n; i ++)
    {
        Object& obj = *(dm._objects->data + i);
        if (IntersectSphere(hit, ray, closestHit.t, dm.getTransform(obj)))
        {
            closestHit = hit;
            closestHit.object = obj;
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
Raytracer::Skybox(const vec3& direction) // wtf?
{
    float t = 0.5*(direction.y + 1.0);
    vec3 vec = vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t; // predefine? neccessary?
    return {vec.x, vec.y, vec.z};
}


Ray Raytracer::ScatterRay(const Ray& ray, const vec3& point, const vec3& normal, const Object& object) 
{
    return BSDF(dm.getMaterial(object), ray, point, normal);
}