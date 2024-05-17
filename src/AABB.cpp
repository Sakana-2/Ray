#include <AABB.hpp>

AABB::AABB()
{
}

AABB::AABB(const Vec3 &min, const Vec3 &max) : _pMin(min), _pMax(max)
{
}

Vec3 AABB::pMin() const
{
    return _pMin;
}

Vec3 AABB::pMax() const
{
    return _pMax;
}

AABB merge(const AABB &a, const AABB &b)
{
    return AABB(min(a.pMin(), b.pMin()), max(a.pMax(), b.pMax()));
}
