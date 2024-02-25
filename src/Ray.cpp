#include "Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(const Vec3 &o, const Vec3 &dir) : _origin(o), _direction(dir)
{
}

Vec3 Ray::origin() const{
    return _origin;
}

Vec3 Ray::direction() const{
    return _direction;
}

Vec3 Ray::at(float t) const{
    return _origin + t * _direction;
}