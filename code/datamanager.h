#pragma once
#include <vector>
#include <map>
#include <string.h>

struct Material;
struct Transform;

typedef uint8_t Buffer;

class DataManager
{
public:
    DataManager(){};

    void genMaterialBuffer(Buffer& handle, const unsigned int& size, Material* buffer);
    void genTransformBuffer(Buffer& handle, const unsigned int& size, Transform* buffer);

    // const Transform& getTransform(const unsigned int& index) const;
    // const Material& getMaterial(const unsigned int& index) const;
    // const vec3& DataManager::getColor(const unsigned int& objectID) const;

    std::vector<Material> _materials;
    std::vector<Transform> _transforms;

private:

    Buffer _idQueue = 0;
    std::map<unsigned int, Buffer> _bufferMap;

};

// const Material& DataManager::getMaterial(const unsigned int& objectID) const
// {
//     return _materials.at(_bufferMap.find(objectID));
// }

// const vec3& DataManager::getColor(const unsigned int& objectID) const
// {
//     return _materials.at(_bufferMap.find(objectID));
// }



