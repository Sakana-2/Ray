#include <Vec.hpp>

class AABB
{
private:
    Vec3 _pMin;
    Vec3 _pMax;

public:
    AABB(const Vec3 &min, const Vec3 &max);
    Vec3 pMin() const;
    Vec3 pMax() const;
};

AABB merge(const AABB &a, const AABB &b);
