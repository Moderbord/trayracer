#include <stdio.h>
#include "window.h"
#include "vec3.h"
#include "raytracer.h"
#include "sphere.h"
#include "getopt.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define degtorad(angle) angle * MPI / 180

unsigned int width = 200;
unsigned int height = 100;
unsigned int raysPerPixel = 1;
unsigned int maxBounces = 5;
bool verbose = false;
bool outputToFile = false;
std::string filepath = "../out/image";

int render()
{
    if (verbose)
    {
        //if (outputToFile)
        printf("Rendering to %s with following settings:\n", filepath.c_str());

        printf("Image dimensions: %ux%u\n", width, height);
        printf("Rays per pixel: %u\n", raysPerPixel);
        printf("Max bounces per ray: %u\n\n", maxBounces);
    }

    std::vector<Color> framebuffer;
    framebuffer.resize(width * height);

    Raytracer rt = Raytracer(width, height, framebuffer, raysPerPixel, maxBounces);

    // Create some objects
    Material* mat = new Material();
    mat->type = "Lambertian";
    mat->color = { 0.5,0.5,0.5 };
    mat->roughness = 0.3;
    Sphere* ground = new Sphere(1000, { 0,-1000, -1 }, mat);
    rt.AddObject(ground);
    
    mat = new Material();
    mat->type = "Conductor";
    mat->color = {1,1,1};
    mat->roughness = 0.2f;
    Sphere* test = new Sphere(1, { 0,1,0 }, mat);
    rt.AddObject(test);

    mat = new Material();
    mat->type = "Lambertian";
    mat->color = { 0,0.4,0.6 };
    mat->roughness = 0.2;
    test = new Sphere(1, { -4,1,0 }, mat);
    rt.AddObject(test);

    mat = new Material();
    mat->type = "Dielectric";
    mat->color = { 1,0.8,0.7 };
    mat->roughness = 0.95;
    mat->refractionIndex = 1.65;
    test = new Sphere(1, { -4,1, 2 }, mat);
    rt.AddObject(test);

    mat = new Material();
    mat->type = "Lambertian";
    mat->color = { 1,0,0.2 };
    mat->roughness = 0.04;
    test = new Sphere(1, { 1,1, -3 }, mat);
    rt.AddObject(test);

    mat = new Material();
    mat->type = "Lambertian";
    mat->color = { 1,1,1 };
    mat->roughness = 0.0;
    test = new Sphere(1, { 4,1, 0 }, mat);
    rt.AddObject(test);


    mat4 view { 1,  0,  0,  0,
                0,  1,  0,  0,
                0,  0,  1,  0,
                0,  1,  10,  1 };
    rt.SetViewMatrix(view);
    rt.Raytrace();


    
    //stbi_write_jpg(filepath.c_str(), width, height, 3, (float*)&framebuffer[0], 100);
    stbi_write_bmp(filepath.c_str(), width, height, 3, (float*)&framebuffer[0]);

    return 0;
}

int main(int argc, char *argv[])
{
    int opt = 0;

    while ((opt = getopt(argc, argv, "vs:o:r:b:")) != -1)
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
                outputToFile = true;
                filepath = optarg;
                break;

            case 'r': // Number of rays per pixel
                raysPerPixel = atoi(optarg);
                break;

            case 'b': // Bumber of bounces per ray
                maxBounces = atoi(optarg);
                break;

            case '?':
                if (optopt == 's') 
                    printf("\nSpecify size of rendered image, <width>x<height>\n");

                else if (optopt == 'o') 
                    printf("\nSpecify filepath and filename\n");

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