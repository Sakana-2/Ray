#pragma once
#include "Vec.hpp"
#include "Ray.hpp"

class Camera
{
private:
    Vec3 _origin;
    Vec3 _uvw[3];

public:
    Camera();
    Camera(const Vec3 &u, const Vec3 &v, const Vec3 &w);
    Camera(const Vec3 &lookfrom, const Vec3 &lookat, const Vec3 &vup, float vfov, float aspect);
    Vec3 origin() const;
    Ray emitRay(float u, float v) const;
};
