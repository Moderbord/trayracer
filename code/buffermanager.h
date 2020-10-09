#pragma once
#include "object.h"
#include "material.h"
#include <vector>
#include <map>
#include <string.h>

typedef uint8_t BufferID;

template <typename T>
class Buffer
{
public:
    T* data;
    unsigned n;

    Buffer(T* src, const unsigned& length) : n(length) 
    {
        size_t size = (sizeof(T) * length);
        data = (T*) malloc(size);
        if (data == NULL) 
        {
            fprintf(stderr, "Failed to allocate buffer memory");
        }
        memcpy(data, src, size);
    };

    ~Buffer()
    {
        free(data);
    }
};


class BufferManager
{
public:
    BufferManager(){};

    void addMaterialBuffer(Buffer<Material>* buffer);
    void addTransformBuffer(Buffer<Transform>* buffer);
    void addObjectBuffer(Buffer<Object>* buffer);

    const Transform& getTransform(const Object& object) const;
    const Material& getMaterial(const Object& object) const;
    const vec3& getColor(const Object& object) const;

    Buffer<Material>* _materials;
    Buffer<Transform>* _transforms;
    Buffer<Object>* _objects;

private:

    BufferID _bufferIDQueue = 0;
};
