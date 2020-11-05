/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
//Dutt
#include "raytracer.h"
#include <pthread.h>
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
    // empty Dutt
    static int leet = 1337;
    std::mt19937 generator (leet++);
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Pre calculate ray distribution
    for (int i = 0; i < this->rpp; i++) 
    {
        distX.push_back(dis(generator));
        distY.push_back(dis(generator));
    }

    num_rays = w * h * rpp;
    aspectRatio = float(h) / float(w);
    fracWidth = 1.0f / this->width;
    fracHeight = 1.0f / this->height;
    sampleFraction = 1.0f / this->rpp;
}

struct thread_info
{
    unsigned start;
    unsigned end;
    Raytracer* context;
};

void* th_raytrace(void *arg)
{
    thread_info *thread = (thread_info *)arg;
    Raytracer* context = thread->context;

    const mat4& mat_view = context->view;
    const mat4& mat_frustrum = context->frustum;

    const unsigned& row_width = context->width;
    const unsigned& rpp = context->rpp;
    const unsigned& ray_bounces = context->bounces;
    const unsigned& width = context->width;
    const float& fraction_width = context->fracWidth;
    const float& fraction_height = context->fracHeight;
    const float& sample_fraction = context->sampleFraction;
    const float& aspect_ratio = context->aspectRatio;

    std::vector<float>* ray_dist_x = &context->distX;
    std::vector<float>* ray_dist_y = &context->distY;

    vec3* pixel = &(&context->frameBuffer)->at(thread->start);
    Ray ray;

    float u;
    float v;

    for (int j = thread->start; j < thread->end; j++)
    {
        for (int i = 0; i < rpp; i++)
        {
            u = ((float(j % width + ray_dist_x->at(i)) * fraction_width) * 2.0f) - 1.0f;
            v = ((float(j / width + ray_dist_y->at(i)) * fraction_height) * 2.0f) - 1.0f;

            ray.origin = get_position(mat_view);
            ray.direction = transform({u, v * aspect_ratio, -1.0f}, mat_frustrum);
            *pixel += context->TracePath(ray, ray_bounces);
        }
        // average color over pixel
        *pixel *= sample_fraction;
        // increment pointer
        pixel++;
    }  

    pthread_exit(EXIT_SUCCESS);
};

//------------------------------------------------------------------------------
/**
*/
void
Raytracer::Raytrace()
{
    unsigned num_threads = 8;
    unsigned pixels_per_thread = this->width * this->height / num_threads;
    pthread_t tID[num_threads];
    thread_info th_info[num_threads];

    // give threads info
    for (int i = 0; i < num_threads; i++)
    {
        th_info[i] = {i * pixels_per_thread, i * pixels_per_thread + pixels_per_thread, this};
    }
    // last thread receives remaining pixels
    th_info[num_threads - 1].end += this->width * this->height % num_threads;


    //------------ Create threads ------------------//
    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_create(&tID[i], NULL, th_raytrace, &(th_info[i])) != 0)
        {
            perror("pthread_create() error");
        }
    }

    //------------ Join threads ------------------//
    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_join(tID[i], NULL) != 0)
        {
            perror("pthread_join() error");
        }
        //printf("thread raytrace done\n");
    }
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

    while (n-- > 0) // count down
    {
        if (Raycast(ray, hitPoint, hitNormal, distance, hitObject))
        {
            material = bm._materials->data + hitObject.id;
            color *= material->color;

            ray.origin = hitPoint;
            BSDF(*material, ray, hitNormal);
            num_rays++;
            
            continue; // Ray bounce
        }
        return color *= this->Skybox(ray.direction); // Ray hits skybox
    }
    return {0.0f, 0.0f, 0.0f}; // Ray hits maximum bounces
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

    Object* obj = bm._objects->data;
    Transform* trans = bm._transforms->data;

    for (int i = 0; i < bm._objects->n; i++)
    {
        if (IntersectSphere(hit, ray, closestHit.t, *trans))
        {
            closestHit = hit;
            closestHit.object = *obj;
            isHit = true;
        }

        obj++;  // only works cause objects are in order
        trans++;
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

// void Raytracer::ScatterRay(const Ray& ray, const vec3& point, const vec3& normal, const Object& object) 
// {
//     BSDF(bm.getMaterial(object), ray, point, normal);
// }