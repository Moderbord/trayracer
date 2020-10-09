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

