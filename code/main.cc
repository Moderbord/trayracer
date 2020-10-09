/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include <stdio.h>
#include <chrono>
//#include "window.h"
#include "raytracer.h"

#include "getopt.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define degtorad(angle) ((angle) * MPI / 180)

unsigned int width = 200;
unsigned int height = 150;
unsigned int raysPerPixel = 1;
unsigned int maxBounces = 5;
bool verbose = false;
char* filepath;

int render()
{
    // -------------------------- 
    Material mats[6] = 
    {
        {{Lambertian},{0.5f,0.5f,0.5f},{0.3f},{1.44f}},
        {{Conductor},{1.0f,1.0f,1.0f},{0.3f},{1.44f}},
        {{Lambertian},{0.0f,0.4f,0.6f},{0.2f},{1.44f}},
        {{Dielectric},{1.0f,0.8f,0.7f},{1.65f},{1.44f}},
        {{Lambertian},{1.0f,0.0f,0.2f},{0.04f},{1.44f}},
        {{Lambertian},{1.0f,1.0f,1.0f},{0.0f},{1.44f}}
    };

    Transform trans[6] =
    {
        {{0.0f,-1000.0f,-1.0f}, 1000},
        {{0.0f,1.0f,0.0f}, 1},
        {{-4.0f,1.0f,0.0f}, 1},
        {{-4.0f,1.0f,2.0f}, 1},
        {{1.0f,1.0f,-3.0f}, 1},
        {{4.0f,1.0f,0.0f}, 1},
    };

    Object objs[6] = {0, 1, 2, 3, 4, 5};
    // -------------------------- 

    Buffer<Material> bMats(mats, 6);
    Buffer<Transform> bTrans(trans, 6);
    Buffer<Object> bObjs(objs, 6);

    BufferManager storage;
    storage.addMaterialBuffer(&bMats);
    storage.addTransformBuffer(&bTrans);
    storage.addObjectBuffer(&bObjs);

    std::vector<vec3> framebuffer;
    framebuffer.resize(width * height);
    Raytracer rt = Raytracer(width, height, framebuffer, raysPerPixel, maxBounces, storage);

    mat4 view { 1,  0,  0,  0,
                0,  1,  0,  0,
                0,  0,  1,  0,
                0,  1,  10,  1 };
    rt.SetViewMatrix(view);

    // Timepoint 1
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

    // Render
    rt.Raytrace();

    // Timepoint 2
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = t1 - t0;
    // Time
    size_t numRays = width * height * raysPerPixel;
    double numMRays = (double)rt.numras / 1000000;
    double mRaysSec = numMRays / duration.count();
    
    printf("Completed in [%f] seconds, with a total of [%zu] rays, [%f] MRays/s \n", duration.count(), rt.numras, mRaysSec);

    // Export to file
    if (filepath != nullptr)
    {
        uint8_t* pixels = new uint8_t[width * height * 3]; // Initiate pixel buffer

        size_t index = 0;
        for (size_t i = 0; i < width * height; i++) 
        {
            pixels[index++] = 255.0f * framebuffer[i].x;
            pixels[index++] = 255.0f * framebuffer[i].y;
            pixels[index++] = 255.0f * framebuffer[i].z;
        }
        
        stbi_flip_vertically_on_write(1);

        if(stbi_write_png(filepath, width, height, 3, pixels, width * 3) == 0)
        {
            fprintf(stderr, "Failed to write to file %s\n", filepath);
        }
        else
        {
            printf("Wrote to file %s\n", filepath);
        }
        delete[] pixels;
        pixels = nullptr;
    }

    if (verbose)
    {
        printf("Image dimensions: %ux%u\n", width, height);
        printf("Rays per pixel: %u\n", raysPerPixel);
        printf("Max bounces per ray: %u\n", maxBounces);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int opt = 0;

    while ((opt = getopt(argc, argv, "vs:o:r:b:t")) != -1)
    {
        switch(opt) 
        {
            case 'v': // Verbose, time consumed and MRays/s
                verbose = true;
                break;

            case 's': // Size of rendered image (width*height)
                {   
                    std::string s = optarg;
                    std::string sWidth = s.substr(0, s.find_first_of("x"));
                    std::string sheight = s.substr(s.find_first_of("x") + 1, s.find_first_of("\0"));
                    width = atoi(sWidth.c_str());
                    height = atoi(sheight.c_str());
                }
                break;

            case 'o': // Output to file
                filepath = optarg;
                break;

            case 'r': // Number of rays per pixel
                raysPerPixel = atoi(optarg);
                break;

            case 'b': // Bumber of bounces per ray
                maxBounces = atoi(optarg);
                break;

            case 't': // Test setting
                printf("Tracing using pre-defined test settings..\n");
                width = 1000;
                height = 500;
                raysPerPixel = 20;
                maxBounces = 5;
                break;

            case '?':
                if (optopt == 's') 
                    printf("\nSpecify size of rendered image, <width>x<height>\n");

                else if (optopt == 'o') 
                    printf("\nSpecify filepath\n");

                else if (optopt == 'r') 
                    printf("\nSpecify number of rays per pixel\n");

                else if (optopt == 'b') 
                    printf("\nSpecify number of bounces per pixel\n");

                else 
                    printf("\nInvalid option received\n");

                return 0;
        }
    }

    render();

    return 0;  
} 