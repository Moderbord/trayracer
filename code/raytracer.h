#pragma once
#include "vec3.h"
#include "mat4.h"
#include "ray.h"
#include "buffermanager.h"
#include <vector>
#include <float.h>

//------------------------------------------------------------------------------
/**
*/
class Raytracer
{
public:
    Raytracer(const unsigned& w, const unsigned& h, std::vector<vec3>& frameBuffer, const unsigned& rpp, const unsigned& bounces, const BufferManager& bm);
    ~Raytracer()
    { 
    }

    // start raytracing!
    void Raytrace();

    // single raycast, find object
    bool Raycast(const Ray& ray, vec3& hitPoint, vec3& hitNormal, float& distance, Object& hitObject);

    // set camera matrix
    void SetViewMatrix(const mat4& val);

    // clear screen
    void Clear();

    // update matrices. Called automatically after setting view matrix
    void UpdateMatrices();

    // trace a path and return intersection color
    // n is bounce depth
    vec3 TracePath(Ray& ray, unsigned n);

    // get the color of the skybox in a direction
    vec3 Skybox(const vec3& direction);

    //void ScatterRay(const Ray& ray, const vec3& point, const vec3& normal, const Object& object);

    std::vector<vec3>& frameBuffer;
    
    // rays per pixel
    unsigned rpp;
    // max number of bounces before termination
    unsigned bounces = 5;

    // width of framebuffer
    const unsigned width;
    // height of framebuffer
    const unsigned height;
    
    const vec3 lowerLeftCorner = { -2.0f, -1.0f, -1.0f };
    const vec3 horizontal = { 4.0f, 0.0f, 0.0f };
    const vec3 vertical = { 0.0f, 2.0f, 0.0f };
    const vec3 origin = { 0.0f, 2.0f, 10.0f };

    // view matrix
    mat4 view;
    // Go from canonical to view frustum
    mat4 frustum;

    size_t num_rays;
    BufferManager bm;

    std::vector<float> distX, distY;
    float fracWidth, fracHeight;
    float sampleFraction;
    float aspectRatio;
};

inline void Raytracer::SetViewMatrix(const mat4& val)
{
    this->view = val;
    this->UpdateMatrices();
}
