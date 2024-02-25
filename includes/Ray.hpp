#pragma once
#include "Vec.hpp"

class Ray
{
private:
    Vec3 _origin;
    Vec3 _direction;
public:
    Ray();
    Ray(const Vec3& o,const Vec3& dir);
    Vec3 origin() const;
    Vec3 direction() const;
    Vec3 at(float t) const;
};

