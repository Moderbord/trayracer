#include "datamanager.h"

struct Material;
struct Transform;

void DataManager::genMaterialBuffer(Buffer& handle, const unsigned int& size, Material* buffer) 
{
    _materials.resize(size);
    memcpy(_materials.data(), buffer, sizeof(Material) * size);
    handle = _idQueue++;
}

void DataManager::genTransformBuffer(Buffer& handle, const unsigned int& size, Transform* buffer) 
{
    _transforms.resize(size);
    memcpy(_transforms.data(), buffer, sizeof(Transform) * size);
    handle = _idQueue++;
}

// const Material& DataManager::getMaterial(const unsigned int& objectID) const
// {
//     return _materials.at(_bufferMap.find(objectID));
// }

// const vec3& DataManager::getColor(const unsigned int& objectID) const
// {
//     return _materials.at(_bufferMap.find(objectID));
// }



