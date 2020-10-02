#pragma once

struct Color
{
    float r = 0;
    float g = 0;
    float b = 0;

    void operator+=(const Color& rhs)
    {
        this->r += rhs.r;
        this->g += rhs.g;
        this->b += rhs.b;
    }

    Color operator+(const Color& rhs)
    {
        return {this->r + rhs.r,
                this->g + rhs.g,
                this->b + rhs.b};
    }

    Color operator*(const Color& rhs)
    {
        return {this->r * rhs.r,
                this->g * rhs.g,
                this->b * rhs.b};
    }
};
