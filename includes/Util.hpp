#pragma once

#include <random>
#include <memory>

#define PI 3.14159265359f
#define NUM_THREAD 8
#define GAMMA_FACTOR 2.2f

class Material;
typedef std::shared_ptr<Material> MaterialPtr;

class Shape;
typedef std::shared_ptr<Shape> ShapePtr;


inline float radian(float f)
{
    return f * PI / 180;
}

inline float drand48()
{
    return float(((double)(std::rand()) / (RAND_MAX)));
}