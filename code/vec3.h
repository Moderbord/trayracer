#pragma once
#include <cmath>
#include <initializer_list>
#include <assert.h>
#include <float.h>

#define MPI 3.14159265358979323846

class vec3
{
public:
    vec3() : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
    {
    }

    vec3(const vec3& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    
    ~vec3()
    {
    }
    
    vec3& operator=(const vec3& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
        return *this;
    }

    vec3& operator+=(const vec3& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    vec3& operator*=(const vec3& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }

    vec3& operator*=(const float& f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }

    vec3 operator+(const vec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z};}
    vec3 operator-(const vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z};}
    vec3 operator-() const { return {-x, -y, -z};}
    vec3 operator*(const vec3& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z};}
    vec3 operator*(const float& c) const { return {x * c, y * c, z * c};}

    float x, y, z;
};

// Get length of 3D vector
inline float len(const vec3& v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Get normalized version of v
inline vec3 normalize(const vec3& v)
{
    float l = 1.0f / len(v);
    return {v.x * l, v.y * l, v.z * l};
}

// piecewise multiplication between two vectors
inline vec3 mul(const vec3& a, const vec3& b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z};
}

// piecewise add between two vectors
inline vec3 add(const vec3& a, const vec3& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline float dot(const vec3& a, const vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - n * (2 * dot(v, n));
}

inline vec3 cross(const vec3& a, const vec3& b)
{
    return { a.y * b.z - a.z * b.y,
             a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x, };
}