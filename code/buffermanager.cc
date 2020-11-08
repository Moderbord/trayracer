/*
* This is a personal academic project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "buffermanager.h"

void BufferManager::addMaterialBuffer(Buffer<Material>* buffer) 
{
    _materials = buffer;
}

void BufferManager::addTransformBuffer(Buffer<Transform>* buffer) 
{
    _transforms = buffer;
}

void BufferManager::addObjectBuffer(Buffer<Object>* buffer) 
{
    _objects = buffer;
}
const Transform& BufferManager::getTransform(const Object& object) const
{
    return *(_transforms->data + object.id);
}

const Material& BufferManager::getMaterial(const Object& object) const
{
    return *(_materials->data + object.id);
}

const vec3& BufferManager::getColor(const Object& object) const
{
    return (_materials->data + object.id)->color;
}

